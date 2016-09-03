class SineWave {

  // sine wave's variables:
  float scaleVal = 100;      // max value for the resulting sine wave (255 = white)
  float sine_phase = PI;     
  float sineValue;         // holds the result of the sine wave  for each position
  int[] colorValue = new int[width]; // array that holds greyscale values
  int loc; // pixel index

  //Constructor:
  SineWave(float temp_periods) {
    periods = temp_periods;
  } // end of constructor

  void init() {
    for (int x = 0; x < colorValue.length; x++) { 
      float xValue = x/float(width)*periods;    // location along x axis
      colorValue[x] = int(( (sin(2*PI*xValue + sine_phase) * scaleVal) + scaleVal ) / 2.0);   // calculate grey value for each x position
    }
  }

  void display() {
    loadPixels();
    for (int x=0; x<width; x++) {

      for (int y=0; y<height; y++) {
        loc = x + y*width;  // get pixel location
        pixels[loc] = color(colorValue[x]);
      }
    }
    updatePixels();
  }  

  void increment(int incrementValue) {
    int[] tempValue = new int[width]; // temporary array for folding colorArray over
    
    if (incrementValue > 0) {
      // deal with pixels above increment value:
      for(int i=incrementValue;i<width;i++) {
        tempValue[i] = colorValue[i-incrementValue];
      }
      for(int i=0;i<incrementValue;i++) {
        tempValue[i] = colorValue[width-incrementValue+i];
      }
      // reassign values back to original color array:
      for(int i=0;i<width;i++) {
        colorValue[i] = tempValue[i];
      }
    } // end if

    if ( incrementValue < 0) {
      incrementValue=abs(incrementValue);
      for(int i=incrementValue;i<width;i++){
        tempValue[i-incrementValue] = colorValue[i];
      }
      for(int i=0;i<incrementValue;i++) {
        tempValue[width-incrementValue+i] = colorValue[i];
      }
      // reassign values back to original color array:
      for(int i=0;i<width;i++) {
        colorValue[i] = tempValue[i];
      }
    }
  } // end of increment method

} // end of class

