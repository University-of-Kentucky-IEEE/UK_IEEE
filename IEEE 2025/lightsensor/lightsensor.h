// senses for 10 seconds changes in light levels, then it continues with rest of following robot functions
int SenseLight(const int photoRpin);

// function to get the avg light level for the period length of seconds. 1000 = 1 sec
int LightAverage(const int pin);