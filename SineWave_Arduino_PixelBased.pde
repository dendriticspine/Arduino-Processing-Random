import processing.serial.*;      // import the serial library

// Playing with Processing...
// Pixel-based sine wave, object oriented;
// Armin H. ix-2009

float periods = 4;        // how many periods per window width (will be controlled by number keys)
int incrementValue = 5;   // controlled by serial input from Arduino
int sineToggle = 1;
SineWave sine;          // declare SineWave object:
SpatialNoise spatialnoise; 
Serial myPort;          // create serial port

void setup () {
  //size(screen.width,screen.height);
  size(800,600);

  smooth();  // anti-aliasing
  frameRate(30);  // set frame rate
  println(Serial.list());    // List all the available serial ports
  // Open whatever port is the one the Arduino is using:
  myPort = new Serial(this, Serial.list()[0], 9600);

  // initialize SineWave object:
  sine = new SineWave(periods);
  spatialnoise = new SpatialNoise();
  sine.init();           // initialize sine wave
  spatialnoise.init(random(0.005,0.03)); // initialize noise object
  sine.display();       // show the sine wave
}

void draw() {
  //incrementValue = int (map(mouseX, 0,width, -10,10));   // mouse X position determines sine wave
  if (sineToggle==1) {
    sine.increment(incrementValue);                          // increment the array by the value passed here
    sine.display();                                         // show the wave
  }
  else {
    spatialnoise.increment(incrementValue);
    spatialnoise.display();
  }
}

void serialEvent(Serial myPort) { 
  int sensorValue = myPort.read();                  // get the sensor value
  incrementValue = int( map(sensorValue, 0, 255, -((width/20)-1), (width/20)-1 ) );  // update the increment value (map incoming 0-255 to speed range)
  println(incrementValue);  // print out the increment value 
}

// pressing keys 1 to 0 causes sine wave's period to change:
void keyPressed() {

  if (key=='s') {
    sineToggle = 1;
  }
  if(key=='n') {
    sineToggle=0;  // switch to other pattern
  }


  if (sineToggle==1) {
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

  if(sineToggle==0){
    if(key=='x'){
      spatialnoise.init(random(0.005,0.03)); 
    }
  }
}








