#include <CmdMessenger.h>            // CmdMessenger

const int laserTTLPin     = 0;    // Pin of laser TTL on/off signal
const int tdtTTLPin       = 1;    // Pin of TDT TTL on/off signal
const int laserModPin     = 4;    // Pin to set laser power level (requires PWM)
const int tdtModPin       = 14;   // Pin to rec analog output level on TDT
const int statusLEDPin    = 11;   // Onboard LED for debugging

float laserPower = 0;
unsigned int pulseDuration;
unsigned int numPulses = 0;
float interPulse;
int newTask = 0;

CmdMessenger cmdMessenger = CmdMessenger(Serial);    // Attach a new CmdMessenger object to the default Serial port

// This is the list of recognized commands. These can be commands that can either be sent or received. 
// In order to receive, attach a callback function to these events
enum {
  kAcknowledge,
  kError,
  kLetThereBeLight,
};

// Callbacks define on which received commands we take action
void attachCommandCallbacks() {
  cmdMessenger.attach(OnUnknownCommand);
  cmdMessenger.attach(kLetThereBeLight, OnLetThereBeLight);
}

// Called when a received command has no attached function
void OnUnknownCommand() {
  cmdMessenger.sendCmd(kError,"Command without attached callback");
}

void OnLetThereBeLight() {
  laserPower = cmdMessenger.readFloatArg();  
  pulseDuration = cmdMessenger.readIntArg();
  numPulses = cmdMessenger.readIntArg();
  interPulse = cmdMessenger.readFloatArg();
  cmdMessenger.sendCmd(kAcknowledge,numPulses);
  newTask = 1;
}

void setup() {
  Serial.begin(115200);                                             
  attachCommandCallbacks();                                         // Attach my application's user-defined callback methods
  cmdMessenger.sendCmd(kAcknowledge,"Controller has started!");     // Send status that says the controller is running
  pinMode(laserTTLPin, OUTPUT);  
  pinMode(tdtTTLPin, OUTPUT);  
  pinMode(laserModPin, OUTPUT);
  pinMode(tdtModPin, OUTPUT);
  pinMode(statusLEDPin, OUTPUT);
}

void loop() {
  cmdMessenger.feedinSerialData();      // Process incoming serial data, and perform callbacks
  delay(10);
  runLaser();
}

bool runLaser() {
  if (newTask == 1) {
    analogWrite(laserModPin, laserPower);
    analogWrite(tdtModPin, laserPower);
    delay(10);
    for (int i = 0; i < numPulses; i++) {
      digitalWrite(laserTTLPin, HIGH);
      digitalWrite(tdtTTLPin, HIGH);
      delay(pulseDuration);
      digitalWrite(laserTTLPin, LOW);
      digitalWrite(tdtTTLPin, LOW);
      delay(interPulse);
      newTask = 0;
    }
    delay(10);
    analogWrite(laserModPin, 0);
    analogWrite(tdtModPin, 0);
    cmdMessenger.sendCmd(kAcknowledge,99);
  }
}


