// tries to get a valid result from the camera within the span of 10 seconds
// if receives valid response, returns a value 0-4
// if invalid, returns -1
int VisionResponse();

// returns the msot common value from a sample of tag readings
int ReadTag();

// returns a single tag value
int DetectSingleTag();