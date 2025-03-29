int VisionResponse(){
    int validTag = -1;
    const unsigned long period = 10000; // how long to wait and try to get valid value
    unsigned long startMillis = millis();
    while(millis() - startMillis < period){
      validTag = ReadTag();
    if((validTag != -1) && (validTag < 5)){
      //Serial.print("Read valid tag: "); // debug, notice of valid response
      //Serial.println(validTag);
      return(validTag);
    }
    }
    // exited while, failed to read tag
    //Serial.println("failed to read tag"); // debug, message said even when response valid
    return(validTag);
  }
  
  int ReadTag(){
    // counters array
    int vals[5] = {0,0,0,0,0};
    //debug print vals
    
    // try to get a valid tag value 
    
    // for loop of tries to read tag
    for(int j = 0; j < 10;j++){
        // result from sampling
        int tagVal = -1;
        
        // read numerous values from the tag and increment the array
        for(int i = 0; i < 1000; i++){
        // get a tag reading and add one to corresponding array index if valid value
        int reading = DetectSingleTag();
        if((reading > -1) && (reading < 5)){
          vals[reading] = vals[reading] + 1;
        //debug print vals
          }
      }
          // find max value 
          int maxIndex = -1;
          int maxVal = 0;
          for(int i = 0; i < 5; i++){
              int curVal = vals[i];
              if(curVal > maxVal){
                  maxIndex = i;
                  maxVal = curVal;
              }
          }
          tagVal = maxIndex;
      
      // return tagVal is not -1, it is a intended result
      if(tagVal != -1){
          return tagVal;
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