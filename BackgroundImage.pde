class BackgroundImage {

  PImage img;
  int[] colorValues= new int[(width*height)]; // array holding color values loaded from image

  //Constructor:
  BackgroundImage() {

  } // end of constructor 

  void init() {
    img = loadImage("leaves.jpg");

    for (int x = 0; x < width; x++) {
      for (int y = 0; y < height; y++) {
        colorValues[x+y*width] = int( img.pixels[x+y*width] );    
      }
    }

  } // end loadimage method

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
  
} // end class BackgroundImage
