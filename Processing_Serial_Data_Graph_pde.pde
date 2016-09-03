import processing.serial.*;
 
Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
 
void setup () {
  size(800, 800);        // set the window size:
  println(Serial.list());
  // I know that the first port in the serial list on my mac
  // is always my  Arduino, so I open Serial.list()[0].
  // Open whatever port is the one you're using.
  myPort = new Serial(this, Serial.list()[0], 57600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  background(0);        // set inital background:
}
 
void draw () {
  // everything happens in the serialEvent()
}
 
void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');    // get the ASCII string:

  if (inString != null) {
    inString = trim(inString);      // trim off any whitespace:
    float inByte = float(inString);   // convert to an int and map to the screen height:
    inByte = map(inByte, 0, 1023, 0, height);
  
    stroke(127,34,255);    // draw the line:
    line(xPos, height, xPos, height - inByte);
  
    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0); 
    } 
    else {
      // increment the horizontal position:
    xPos++;
    }
  }
}
