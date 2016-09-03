import processing.serial.*;      // import the serial library

float periods = 4;            // how many periods per window width (will be controlled by number keys)
int incrementValue = 5;       // controlled by serial input from Arduino
SineWave sine;                // declare SineWave object
int firstscreenwidth = (int)screen.width; // width of the first screen
Serial myPort;                // create serial port

void setup () {
  size(640,480, P2D);                 // note that this sets the "width" variable, in this case, width = 640.
  frame.setLocationRelativeTo(null);  // centers the frame on the screen
  frameRate(90);    // set frame rate (limit seems to be around 90 fps. 
                    // The frame rate changes the effect of the increment value passed from the Arduino code. 
  
  println(Serial.list());    // List all the available serial ports
  // Open whatever port is the one the Arduino is using and set Baud rate:
  myPort = new Serial(this, Serial.list()[0], 115200);

  // initialize pattern classes:
  sine = new SineWave(periods);

  sine.init();                             // initialize sine wave
  sine.display();                          // show the sine wave when program opens
}


void draw() {
    sine.increment(incrementValue);                          // increment the array by the value passed here
    sine.display();                                         // show the wave
}
 
void serialEvent(Serial myPort) { 
  int sensorValue = myPort.read();                  // get the sensor value
  incrementValue = int( map(sensorValue, 0, 255, -((width/20)-1), (width/20)-1 ) );  // update the increment value (map incoming 0-255 to speed range)
}
 
 
void keyPressed() {
  if (key=='q') {
    exit();
  }
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
    }
    sine.init(); // initialize sine wave with new periods
}
