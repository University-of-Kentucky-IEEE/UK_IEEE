/*
 * AprilTag pose estimation demo on AI Thinker ESP32-CAM
 * Created by gvl610
 * Based on https://github.com/AprilRobotics/apriltag
 * with some modifications (for adaption and performance)
 */

// Config for pose estimation
// Tag size (in meter). See original AprilTag readme for how to measure
// You have to put your value here. This value is of NO standard and
// is just my own tag size.
#define TAG_SIZE 0.05

// Camera calibration data
// This information is obtained by calibrating your camera using software like 3DF Zephyr
// You have to calibrate and put your own values here, this value is just for my camera
// and likely not work on your camera.
#define FX 924.713610878 // fx (in pixel)
#define FY 924.713610878 // fy (in pixel)
#define CX 403.801748132 // cx (in pixel)
#define CY 305.082642826 // cy (in pixel)

// Define CAP_TO_SD to log image to SD card (for debugging)
// This will output raw 1bpp files and then you can use
// raw2img.py to convert it to readable format.
//#define CAP_TO_SD

//
// WARNING!!! PSRAM IC required for UXGA resolution and high JPEG quality
//            Ensure ESP32 Wrover Module or other board with PSRAM is selected
//            Partial images will be transmitted if image exceeds buffer size
//
//            You must select partition scheme from the board menu that has at least 3MB APP space.
//            Face Recognition is DISABLED for ESP32 and ESP32-S2, because it takes up from 15 
//            seconds to process single frame. Face Detection is ENABLED if PSRAM is enabled as well

// ===================
// Select camera model
// ===================
//#define CAMERA_MODEL_WROVER_KIT // Has PSRAM
//#define CAMERA_MODEL_ESP_EYE // Has PSRAM
//#define CAMERA_MODEL_ESP32S3_EYE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_PSRAM // Has PSRAM
//#define CAMERA_MODEL_M5STACK_V2_PSRAM // M5Camera version B Has PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_ESP32CAM // No PSRAM
//#define CAMERA_MODEL_M5STACK_UNITCAM // No PSRAM
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
//#define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM
//#define CAMERA_MODEL_XIAO_ESP32S3 // Has PSRAM
// ** Espressif Internal Boards **
//#define CAMERA_MODEL_ESP32_CAM_BOARD
//#define CAMERA_MODEL_ESP32S2_CAM_BOARD
//#define CAMERA_MODEL_ESP32S3_CAM_LCD
//#define CAMERA_MODEL_DFRobot_FireBeetle2_ESP32S3 // Has PSRAM
//#define CAMERA_MODEL_DFRobot_Romeo_ESP32S3 // Has PSRAM

// Hardware-specific headers
#include "esp_camera.h"
#include "camera_pins.h"

#ifdef CAP_TO_SD
#include "SD_MMC.h"
#include "FS.h"
#endif

// Apriltag headers
// We choose 36h11 family to use in this demo, but you can use
// any family of your choice. Note that due to memory limitation,
// you might have to reduce the number of tag in `codedata` array
// in the tag family source file.
#include "apriltag.h"
#include "tag36h11.h" // Tag family. You can change
#include "common/image_u8.h"
#include "common/zarray.h"
#include "apriltag_pose.h" // For pose estimation
#include "common/matd.h"

/*
 * Define this macro to enable debug mode
 * Level 0: Absolutely no debug at all. Suitable for
 *  production use.
 * Level 1: Simple debug messages , like simple events
 *  notifications.
 * Level 2: Low level debug messages
 * Level 3: Debug messages that in a loop
 */
#define DEBUG 2

void setup() {
  // Init serial
  Serial.begin(115200);
#if DEBUG >= 2
  Serial.setDebugOutput(true);
#endif

  // Show some signs of life
#if DEBUG >= 1
  Serial.println("AprilTag pose estimation demo on ESP32-CAM");
  Serial.print("Init PSRAM... ");
#endif

  // Init PSRAM
  psramInit();
#if DEBUG >= 1
  Serial.println("done");
  Serial.print("Memory available in PSRAM: ");
  Serial.println(ESP.getFreePsram());
#endif

  // Create camera config structure
  camera_config_t config;

  // Set camera pins (as defined in cam_pins.h)
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  // Set clock frequency
  config.xclk_freq_hz = 20000000;

  // Set frame config
  config.frame_size = FRAMESIZE_SVGA; // You can change the resolution to fit your need
  config.pixel_format = PIXFORMAT_GRAYSCALE; // Required for AprilTag processing
  config.grab_mode = CAMERA_GRAB_LATEST; // Has to be in this mode, or detection will be lag
  config.fb_location = CAMERA_FB_IN_PSRAM;
  //config.jpeg_quality = 12;
  config.fb_count = 1; // Can't afford (and also not needed) to have 2

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // Init camera
#if DEBUG >= 1
    Serial.print("Init camera... ");
#endif
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    // Cannot init camera
#if DEBUG >= 1
    Serial.printf("Camera init failed with error 0x%x\n", err);
#endif

    // Reset (cannot let it die here)
    ESP.restart();
  }

  // Specific configs for different camera
  sensor_t * s = esp_camera_sensor_get();
  // Initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1); // flip it back
    s->set_brightness(s, 1); // up the brightness just a bit
    s->set_saturation(s, -2); // lower the saturation
  }

#if defined(CAMERA_MODEL_M5STACK_WIDE) || defined(CAMERA_MODEL_M5STACK_ESP32CAM) || defined(CAMERA_MODEL_AI_THINKER)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

#if defined(CAMERA_MODEL_ESP32S3_EYE)
  s->set_vflip(s, 1);
#endif

  // Custom camera configs should go here
  s->set_brightness(s, 0);     // -2 to 2
  s->set_contrast(s, 0);       // -2 to 2
  s->set_saturation(s, 0);     // -2 to 2
  s->set_whitebal(s, 1);       // 0 = disable , 1 = enable
  s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
  s->set_wb_mode(s, 0);        // 0 to 4 - if awb_gain enabled (0 - Auto, 1 - Sunny, 2 - Cloudy, 3 - Office, 4 - Home)
  s->set_exposure_ctrl(s, 1);  // 0 = disable , 1 = enable
  s->set_aec2(s, 1);           // 0 = disable , 1 = enable
  s->set_ae_level(s, 0);       // -2 to 2
  s->set_aec_value(s, 168);    // 0 to 1200
  s->set_gain_ctrl(s, 1);      // 0 = disable , 1 = enable
  s->set_agc_gain(s, 0);       // 0 to 30
  s->set_gainceiling(s, (gainceiling_t)0);  // 0 to 6
  s->set_bpc(s, 0);            // 0 = disable , 1 = enable
  s->set_wpc(s, 1);            // 0 = disable , 1 = enable
  s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable
  s->set_lenc(s, 1);           // 0 = disable , 1 = enable
  s->set_hmirror(s, 1);        // 0 = disable , 1 = enable
  s->set_vflip(s, 1);          // 0 = disable , 1 = enable
  s->set_dcw(s, 1);            // 0 = disable , 1 = enable

  // Done init camera
#if DEBUG >= 1
  Serial.println("done");
  Serial.print("Memory available in PSRAM: ");
  Serial.println(ESP.getFreePsram());
#endif

  // Init SD card if needed
#ifdef CAP_TO_SD
#if DEBUG >= 1
  Serial.print("Init SD card... ");
#endif

  // Mount SD card
  if (SD_MMC.begin()) {
#if DEBUG >= 1
    Serial.println("done");
#endif
  } else {
#if DEBUG >= 1
    Serial.println("failed. SD card capture will be disabled!");
#endif
  }

  // FS object
  fs::FS &fs = SD_MMC;

  // Create "apriltag_detection" directory (if it has not yet existed)
  fs.mkdir("/apriltag_detection");

  // Determine the current run ID by looking into apriltag_detection directory
  // and find the directory with the largest number. Our ID will be that + 1
  String run_id = "0";
  File apriltag_detection_dir = fs.open("/apriltag_detection");
  File run_dir;
  while (run_dir = apriltag_detection_dir.openNextFile()) {
    if (run_dir.isDirectory()) {
      run_id = run_dir.name();
    }
  }

  // Create new directory
  run_id = "/apriltag_detection/" + String(run_id.toInt() + 1);
  fs.mkdir(run_id.c_str());

#if DEBUG >= 1
  Serial.print("Images will be saved to ");
  Serial.print(run_id);
  Serial.println("/");
#endif

  // Image id counter
  uint32_t frame_id = 0;
#endif

  // Setup AprilTag detection
#if DEBUG >= 1
  Serial.print("Init AprilTag detector... ");
#endif

  // Create tag family object
  apriltag_family_t *tf = tag36h11_create();

  // Create AprilTag detector object
  apriltag_detector_t *td = apriltag_detector_create();

  // Add tag family to the detector
  apriltag_detector_add_family(td, tf);
  
  // Tag detector configs
  // quad_sigma is Gaussian blur's sigma
  // quad_decimate: small number = faster but cannot detect small tags
  //                big number = slower but can detect small tags (or tag far away)
  td->quad_sigma = 0.0;
  td->quad_decimate = 4.0;
  td->refine_edges = 0;
  td->decode_sharpening = 0.25;
  td->nthreads = 2; // The optimal (after many tries) is 2 thread on 2 cores ESP32
  td->debug = 0;

  // Done init AprilTag detector
#if DEBUG >= 1
  Serial.println("done");
  Serial.print("Memory available in PSRAM: ");
  Serial.println(ESP.getFreePsram());
  Serial.println("Start detecting...");
#endif

  // Main detecting loop (we just ignore the loop() function)
  while (true) {
    // Get a frame from camera
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
#if DEBUG >= 3
      Serial.println("Failed to get frame! Retrying...");
#endif
      continue;
    }

  // Capture frame to SD card
#ifdef CAP_TO_SD
    String img_path = run_id + "/" + String(frame_id) + ".raw";

#if DEBUG >= 3
    Serial.print("Saving frame to ");
    Serial.print(img_path);
    Serial.print("... ");
#endif

    // Open file
    File frame_f = fs.open(img_path.c_str(), FILE_WRITE);

    if (!frame_f) {
#if DEBUG >= 3
      Serial.println("Failed to open file in writing mode");
#endif
    } else {
      frame_f.write(fb->buf, fb->len); // payload (image), payload length
#if DEBUG >= 3
      Serial.println("done");
#endif
    }

    // Close and increase frame_id
    frame_f.close();
    frame_id++;
#endif

    // Convert our framebuffer to detector's input format
#if DEBUG >= 3
    Serial.println("Converting frame to detector's input format... ");
#endif
    image_u8_t im = {
      .width = fb->width,
      .height = fb->height,
      .stride = fb->width,
      .buf = fb->buf
    };
#if DEBUG >= 3
    Serial.println("done");
    Serial.println("Detecting... ");
#endif

    // Detect
    zarray_t *detections = apriltag_detector_detect(td, &im);
#if DEBUG >= 3
    Serial.println("done. Result:");
#endif

    // Print result
    for (int i = 0; i < zarray_size(detections); i++) {
      // Get detection
      apriltag_detection_t *det;
      zarray_get(detections, i, &det);

      // Print tag ID
      Serial.print("ID: ");
      Serial.println(det->id);
      Serial.printf("");

      // Creating detection info object to feed into pose estimator
      apriltag_detection_info_t info;
      info.det = det;
      info.tagsize = TAG_SIZE;
      info.fx = FX;
      info.fy = FY;
      info.cx = CX;
      info.cy = CY;

      // Estimate the pose
      apriltag_pose_t pose;
      double err = estimate_tag_pose(&info, &pose);
      
      // Print result (position of the tag in the camera's coordinate system)
      //matd_print(pose.R, "%15f"); // Rotation matrix
      //matd_print(pose.t, "%15f"); // Translation matrix

      // Compute the yaw, pitch, and roll from the rotation matrix (and convert to degree)
      double yaw = atan2(MATD_EL(pose.R, 1, 0), MATD_EL(pose.R, 0, 0)) * RAD_TO_DEG;
      double pitch = atan2(-MATD_EL(pose.R, 2, 0), sqrt(pow(MATD_EL(pose.R, 2, 1), 2) + pow(MATD_EL(pose.R, 2, 2), 2))) * RAD_TO_DEG;
      double roll = atan2(MATD_EL(pose.R, 2, 1), MATD_EL(pose.R, 2, 2)) * RAD_TO_DEG;

      // Print the yaw, pitch, and roll of the camera
      printf("y,p,r: %15f, %15f, %15f\n", yaw, pitch, roll);
      
      // Compute the transpose of the rotation matrix
      matd_t *R_transpose = matd_transpose(pose.R);

      // Negate the translation vector
      for (int i = 0; i < pose.t->nrows; i++) {
          MATD_EL(pose.t, i, 0) = -MATD_EL(pose.t, i, 0);
      }

      // Compute the position of the camera in the tag's coordinate system
      matd_t *camera_position = matd_multiply(R_transpose, pose.t);
      printf("x,y,z: %15f, %15f, %15f\n", MATD_EL(camera_position, 0, 0), MATD_EL(camera_position, 1, 0), MATD_EL(camera_position, 2, 0));

      // Free the matrices
      matd_destroy(R_transpose);
      matd_destroy(camera_position);
    }

    // Cleaning up
#if DEBUG >= 3
    Serial.print("Memory available in PSRAM: ");
    Serial.println(ESP.getFreePsram());
    Serial.println("Cleaning up... ");
#endif
    // Free detection result object
    apriltag_detections_destroy(detections);

    // Return camera framebuffer to the camera driver
    esp_camera_fb_return(fb);

    // Display time needed per frame
    // And frame count (if CAP_TO_SD defined)
    float t =  timeprofile_total_utime(td->tp) / 1.0E3;
#ifdef CAP_TO_SD
    Serial.printf("t, id: %12.3f, %zu\n", t, frame_id - 1);
#else
    Serial.printf("t: %12.3f\n", t);
#endif
  }
}

void loop() {
  // Nothing here, the real loop is already at the end of setup()
}
