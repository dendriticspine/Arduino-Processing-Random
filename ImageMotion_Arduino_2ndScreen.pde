import processing.serial.*;      // import the serial library

// Playing with Processing...
// Pixel-based imiage motion, object oriented;
// 
// Armin H. ix-2009

float periods = 4;            // how many periods per window width (will be controlled by number keys)
int incrementValue = 5;       // controlled by serial input from Arduino
int patternID = 1;            // which pattern to play (1 = sinusoidal grating, 2 = Perlin noise, 3 = background image)
SineWave sine;                // declare SineWave object
SpatialNoise spatialnoise;    // declare Perlin noise object
BackgroundImage bgimage;      // declare background image object
int firstscreenwidth = (int)screen.width; // width of the first screen
Serial myPort;                // create serial port


void setup () {
  size(640,480, P2D);                 // has to be 640x480 for background image to work!
  frame.setLocationRelativeTo(null);  // centers the frame on the screen
   
  //frame.setLocation(firstscreenwidth-640,100);   // move viewport over to the right off the first screen, to the next screen
  frameRate(90);    // set frame rate (limit seems to be around 90 fps. 
                    // The frame rate changes the effect of the increment value passed from the Arduino code. 
  
  println(Serial.list());    // List all the available serial ports
  // Open whatever port is the one the Arduino is using and set Baud rate:
  myPort = new Serial(this, Serial.list()[0], 115200);

  // initialize pattern classes:
  sine = new SineWave(periods);
  spatialnoise = new SpatialNoise();
  bgimage = new BackgroundImage();

  sine.init();                             // initialize sine wave
  sine.display();                          // show the sine wave when program opens
}


void draw() {
  //incrementValue = int (map(mouseX, 0,width, -10,10));   // mouse X position determines sine wave (debugging w/out Arduino)
  if (patternID==1) {
    sine.increment(incrementValue);                          // increment the array by the value passed here
    sine.display();                                         // show the wave
  }
  else if(patternID==0) {
    spatialnoise.increment(incrementValue);
    spatialnoise.display();
  }
  else {
    bgimage.increment(incrementValue);
    bgimage.display();
  }
}
 
void serialEvent(Serial myPort) { 
  int sensorValue = myPort.read();                  // get the sensor value
  incrementValue = int( map(sensorValue, 0, 255, -((width/20)-1), (width/20)-1 ) );  // update the increment value (map incoming 0-255 to speed range)
  //println(incrementValue);  // print out the increment value 
}
 
 
void keyPressed() {
 
  if (key=='s') {
    patternID = 1;     // switch to sine pattern
  }
  if(key=='n') {
    patternID=0;       // switch to noise pattern
    spatialnoise.init(random(0.005,0.03));   // initialize noise object
  }
  if (key=='i') {
    patternID=2;    // switch to background image
    bgimage.init();
  }
  if (key=='q') {
    exit();
  }
 
  // in Perlin noise mode, pressing 'x' re-initializes the noise array: 
  if(patternID==0){
    if(key=='x'){
      spatialnoise.init(random(0.005,0.03)); 
    }
  }
 
  // In sine wave mode, pressing keys 1 to 0 causes sine wave's period to change:
  if (patternID==1) {
    switch(key) {
    case '1':
      periods = 1;
      println("1 periods/width");
      break;
    case '2':
      periods = 2;
      println("2 periods/width");
      break;
    case '3':
      periods = 3;
      println("3 periods/width");
      break;    
    case '4':
      periods = 4;
      println("4 periods/width");
      break;   
    case '5':
      periods = 5;
      println("5 periods/width");
      break;
    case '6':
      periods = 6;
      println("6 periods/width");
      break;
    case '7':
      periods = 7;
      println("7 periods/width");
      break;
    case '8':
      periods = 8;
      println("8 periods/width");
      break;
    case '9':
      periods = 9;
      println("5 periods/width");
      break;    
    case '0':
      periods = 10;
      println("10 periods/width");
      break;       
    }
    sine.init(); // initialize sine wave with new periods
  }
}
