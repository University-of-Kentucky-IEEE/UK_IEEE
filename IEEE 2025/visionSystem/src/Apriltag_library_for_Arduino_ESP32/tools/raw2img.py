#!/usr/bin/python3
# Convert raw 1bpp grayscale image dumped from ESP32-CAM to modern formats (default png, but you can change)
# Default size is 640x480. If you use different size, you have to change size variables below
# Usage:
# For converting all `.raw` images in current directory: raw2img.py
# For converting specific file: raw2img.py input.raw output.png
# You can replace `png` with any file extension you would like
# For example, change it to `output.jpg` will create jpg image

# Import libraries
import sys
import os
import numpy as np
import cv2

# Image resolution. Change to fit your own
IMG_WIDTH = 640
IMG_HEIGHT = 480

# Convert numpy array (in case you want to use it in your own code)
def convert_buf(input_arr):
    return input_arr.reshape((IMG_HEIGHT, IMG_WIDTH))

# Open a single file and convert it to an image array
def open_raw_file(input_file_name):
    f = open(input_file_name, 'rb')
    one_d_array = np.fromfile(f, dtype=np.uint8, count=IMG_WIDTH*IMG_HEIGHT)
    im = convert_buf(one_d_array)
    f.close()
    return im

def convert_file(input_file_name, output_file_name):
    print("Converting", input_file_name, "to", output_file_name + "...", end=" ")
    cv2.imwrite(output_file_name, open_raw_file(input_file_name))
    print("done!")

# Check arguments
if __name__ == "__main__":
    if len(sys.argv) == 3:
        # Convert specific file
        convert_file(sys.argv[1], sys.argv[2])
    else:
        # Convert all `raw` files in directory
        files = [i for i in os.listdir() if i[-4:] == ".raw"]
        for i in files:
            convert_file(i, i[0:-3] + "png")
