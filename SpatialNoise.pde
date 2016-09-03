class SpatialNoise {
 
  // used: Perlin noise (http://en.wikipedia.org/wiki/Perlin_noise)
 
  int[] colorValues= new int[(width*height)];
 
  //Constructor:
  SpatialNoise() {
 
  } // end of constructor float temp_increment increment = temp_increment;
 
  // initialize a matrix with 2D noise that wraps around horizontally:
  void init(float increment) {
    // noise code from a Perlin 2D noise example:
    float xoff = random(0.0,5.0); // Start xoff at 0
 
      // For every x,y coordinate in a 2D space, calculate a noise value and produce a brightness value
    for (int x = 0; x < width/2; x++) {
      //println(x);
      xoff += increment;           // Increment xoff
      float yoff = 0.0;           // For every xoff, start yoff at 0
      for (int y = 0; y < height; y++) {
 
        yoff += increment;         // Increment yoff
        // Calculate noise, scale by 255 and fill pixel array
        colorValues[x+y*width] = int( noise(xoff,yoff)*255 );
      }
    }
    // to make it wrap around, go back when 1/2 width is reached:   
 
    for (int x = width/2; x < width; x++) {
      //println(x);
      xoff -= increment;           // Increment xoff goes back again
      float yoff = 0.0;           // For every xoff, start yoff at 0
      for (int y = 0; y < height; y++) {
        yoff += increment;         // Increment yoff
        // Calculate noise, scale by 255 and fill pixel array
        colorValues[x+y*width] = int( noise(xoff,yoff)*255 );
      }
    }
  } // end init method
 
  void display() {
    loadPixels();
    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        int bright = colorValues[x+y*width];
        pixels[x+y*width] = color(bright);
      }
    }
    updatePixels();
  } // end display method
 
  void increment(int incrementValue){
    int[] tempValue = new int[width*height]; // temporary array for folding color array over
 
    // Increments above zero (movement to the right):
    if (incrementValue > 0) {
      // deal with pixel columns above increment value:
      for(int i=incrementValue;i<width;i++) {
        for(int k=0;k<height;k++){
          tempValue[i+k*width] = colorValues[i-incrementValue+k*width];
        }
      }
      for(int i=0;i<incrementValue;i++) {
        for(int k=0;k<height;k++){
          tempValue[i+k*width] = colorValues[(width-incrementValue+i)+k*width];
        }
      }
      // reassign values back to original color array:
      for(int i=0;i<width;i++) {
        for(int k=0;k<height;k++){        
          colorValues[i+k*width] = tempValue[i+k*width];
        }
      }
    }
    // Icrements below zero (movement to the left):
    if (incrementValue < 0) {
      incrementValue=abs(incrementValue);
 
      for(int i=incrementValue;i<width;i++) {
        for(int k=0;k<height;k++){
          tempValue[i-incrementValue+k*width] = colorValues[i+k*width];
        }
      }
      for(int i=0;i<incrementValue;i++) {
        for(int k=0;k<height;k++){
          tempValue[(width-incrementValue+i)+k*width] = colorValues[i+k*width];
        }
      }
      // reassign values back to original color array:
      for(int i=0;i<width;i++) {
        for(int k=0;k<height;k++){        
          colorValues[i+k*width] = tempValue[i+k*width];
        }
      }     
    }
  } // end increment method
 
} // end class
