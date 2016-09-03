import processing.serial.*;
 
Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
 
void setup () {
  size(400, 300);        
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);    // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  background(0);    // set inital background:
}

void draw () {   // everything happens in the serialEvent()
}
 
void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');    // get the ASCII string:
 
  if (inString != null) {
    inString = trim(inString);        // trim off any whitespace:
    float inByte = float(inString);   // convert to an int and map to the screen height:
    inByte = map(inByte, 0, 1023, 0, height);
 
    stroke(127,34,255);      // draw the line:
    line(xPos, height, xPos, height - inByte);
 
    // at the edge of the screen, go back to the beginning:
    if (xPos >= width) {
      xPos = 0;
      background(0); 
    } 
    else {
      xPos++;
    }
  }
}
