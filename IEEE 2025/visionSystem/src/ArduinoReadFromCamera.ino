/*code to programt the Xiao Seeed Sense Esp32 board + camera for apriltag sensing tags 0-4.
  send the reading over uart TX pin
*/ 
/* Untested functions to read off of RX1 line on the Arduino.
	The esp32 camera module is powered off the arduino 3.3V. GND.
	Connect Mega's TX1 line to ESP RX line 
	Connect Mega's RX1 line to ESP TX line
*/

void setup() {
  Serial.begin(9600);	//debug
  Serial1.begin(9600);

}

/* returns the most detected reading after a period of tallying
	tries an inputted amount of times to get a correct tag value,
	i'm thinking 3 tries. -1 is invalid result, 0-5 are valid results
	*/
int ReadTag(int tries){
  // counters array
  int vals[6] = {0,0,0,0,0,0};
  //debug print vals
  
  // try to get a valid tag value 
  
  // for loop of tries to read tag
  for(int j = 0; i < tries;i++){
	  // result from sampling
	  int tagVal = -1;
	  
	  // read numerous values from the tag and increment the array
	  for(int i = 0; i < 25; i++){
		// get a tag reading and add one to corresponding array index if valid value
		int reading = DetectSingleTag();
		if((reading > -1) && (reading < 6)){
		  vals[reading] = vals[reading] + 1;
		//debug print vals
		}
		// find max value 
		int maxIndex = -1;
		int maxVal = 0;
		for(int i = 0; i < vals.length(); i++){
			int curVal = vals[length];
			if(curVal > maxVal){
				maxIndex = i;
				maxVal = curVal;
			}
		}
		tagVal = maxIndex;
	}
	// return tagVal is not -1, it is a intended result
	if(tagVal != -1){
		return tagVal;
	}
  }
  // exited for loop, never correctly received tag reading
   return -1;
  }

  // decide which reading was gotten most then return it

}

// returns a single tag 
int DetectSingleTag(){
  char incomingByte;
	if(Serial1.available()){
    Serial1.readBytes(&incomingByte,1);
    // Serial.println("Message Received: ");
    Serial.println(incomingByte);

    if(incomingByte == '0'){
      //Serial.println("Detecting 0, Place in slot 0");	//debug
	  return 0;
    }else if(incomingByte == '1'){
      //Serial.println("Detecting 0, Place in slot 1");	//debug
	  return 1;
    }else if(incomingByte == '2'){
      //Serial.println("Detecting 0, Place in slot 2");	//debug
	  return 2;
    }else if(incomingByte == '3'){
     // Serial.println("Detecting 0, Place in slot 3");	//debug
	  return 3;
    }else if(incomingByte == '4'){
      //Serial.println("Detecting 0, Place in slot 4");	//debug
	  return 4;
    }else {
      //Serial.println("Detecting Wall");
	  return 5;
    }
    return -1;
  }
}
int vals[6] = {0,0,0,0,0,0};
void loop() {
  
// print to serial monitor the contents of vals array
/*char buffer[100];
sprintf(buffer, "vals: 0: %d, 1: %d, 2: %d, 3: %d, 4: %d,5: %d", vals[0], vals[1], vals[2], vals[3], vals[4], vals[5]);
  Serial.println(buffer); */
  char incomingByte;
	if(Serial1.available()){
    Serial1.readBytes(&incomingByte,1);
    // Serial.println("Message Received: ");
    Serial.println(incomingByte);

    if(incomingByte == '0'){
      Serial.println("Detecting 0, Place in slot 0");	//debug
	  return 0;
    }else if(incomingByte == '1'){
      Serial.println("Detecting 0, Place in slot 1");	//debug
	  return 1;
    }else if(incomingByte == '2'){
      Serial.println("Detecting 0, Place in slot 2");	//debug
	  return 2;
    }else if(incomingByte == '3'){
      Serial.println("Detecting 0, Place in slot 3");	//debug
	  return 3;
    }else if(incomingByte == '4'){
      Serial.println("Detecting 0, Place in slot 4");	//debug
	  return 4;
    }else {
      Serial.println("Detecting Wall");
	  return 5;
    }
    return -1;
  }
}

//     void setup() {

//       Serial.begin(9600);

//       Serial1.begin(9600);


//       Serial.println("Hello Computer");

//       Serial1.println("Hello Serial 1");

//     }

//     void loop() {

//       Serial1.println("Hello Serial 1");

//         Serial.println("Message Received: ");
//     Serial.println(Serial1.readString());
//     }
