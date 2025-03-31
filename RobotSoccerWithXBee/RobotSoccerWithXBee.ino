#include <SoftwareSerial.h>

SoftwareSerial XBee(2, 3);

#include <Servo.h>
  #define RMOTORD   4
  #define RMOTORS   5
  #define LMOTORD   7
  #define LMOTORS   6
  #define SERVOP    3

  #define ENCODER_LEFT A0  // Analog pin for the left encoder
#define THRESHOLD 50     // Adjust based on encoder signal range

int minValue = 0;    // Minimum encoder reading (calibrate this)
int maxValue = 1023; // Maximum encoder reading (calibrate this)
float revolutionCount = 0.0; // Tracks total revolutions

  float WHEEL_RADIUS = 3.2; //cm
  float WHEEL_DIAMETER = 6.4; //cm

  int MAIN_SPEED   = 75;
  int targetSpeed = 150;
  int leftSPEED = 255; 
  int rightSPEED = 255;

  int Lerror = 0;
  int speedL = 0;
  int Rerror = 0;
  int speedR = 0;

  const float DISTANCE_PER_UNIT = 0.01;

  float integral = 0;
  float prevError = 0;


 /////////// Left motor parameters //////////////

  unsigned long LprevTime = 0;
  unsigned long LcurrentTime = 0;
  int LcurrentPosition = 0;
  int LprevPosition = 0;
  int Lrpm = 0.0; // Motor speed in RPM

 /////////// Right motor parameters //////////////

  unsigned long RprevTime = 0;
  unsigned long RcurrentTime = 0;
  int RcurrentPosition = 0;
  int RprevPosition = 0;
  int Rrpm = 0.0; // Motor speed in RPM

void setup() {
  pinMode(RMOTORD,OUTPUT);
  pinMode(LMOTORD,OUTPUT);
  XBee.begin(9600);

}

//////////////////////////////////////////////////////////////////// Functions ///////////////////////////////////////////////////////////////////////////////

void MOVE(int left,int right,int leftSPEED,int rightSPEED)
{
  digitalWrite(RMOTORD,right);
  analogWrite(RMOTORS,rightSPEED);
  digitalWrite(LMOTORD,left);
  analogWrite(LMOTORS,leftSPEED);
}

void PRINT(int Lerror, int speedL, int Rerror, int speedR) {
  Serial.print(Lerror);    // Left motor speed
  Serial.print(",");
  Serial.print(speedL);    // Left motor PID speed
  Serial.print(",");
  Serial.print(Rerror);    // Right motor speed
  Serial.print(",");
  Serial.println(speedR);  // Right motor PID speed
}
int computePID(int currentRPM, float dt) 
{ // error (RPM) dt (RPM)
    // PID gains (tune these as needed)
    float Kp = 1;  
    float Ki = 0.01;  
    float Kd = 0.001;  
    int error = dt - currentRPM;
    // Proportional term
    float P = Kp * error;

    // Integral term (accumulates error over time)
    integral += error * dt;
    float I = Ki * integral;

    // Derivative term (rate of change of error)
    float D = Kd * ((error - prevError) / dt);

    // Compute output speed
    int Speed = P + I + D;

    // Update previous error
    prevError = error;

    // Constrain speed within a valid range (optional)
    Speed = constrain(Speed, 0, 255); // Assuming a motor speed range

    return Speed;
}

int MEASURE_LEFT_SPEED()
{
  LcurrentPosition = analogRead(A1); // Returns a value between 0 and 1023
  // Get the current time
  LcurrentTime = millis();
  // Calculate time difference in sec
  float deltaTime = (LcurrentTime - LprevTime) / 1000.0;
  // Calculate position difference
  if (deltaTime < 0.001) { // 1 millisecond threshold
      deltaTime = 0.001;  // Prevent division issues
  }
  int deltaPosition = LcurrentPosition - LprevPosition;
  // for values that go over 1024 or under 0
  if (deltaPosition > 1024 / 2) 
  {
    deltaPosition -= 1024; // Adjust for 1023 - 0 
  }   
  else if (deltaPosition < -1024 / 2) 
  {
    deltaPosition += 1024; // Adjust for 0 - 1023 
  }
  // Calculate RPM
  Lrpm = (deltaPosition / deltaTime) * (60.0/1024);
  // Update previous values
  LprevPosition = LcurrentPosition;
  LprevTime = LcurrentTime;
  
  if (abs(deltaPosition) < 2) 
  { // Ignore minor fluctuations
    return Lrpm;  // Keep last valid RPM value
  }

}


int MEASURE_RIGHT_SPEED()
{
  RcurrentPosition = analogRead(A0); // Returns a value between 0 and 1023
  // Get the current time
  RcurrentTime = millis();
  // Calculate time difference in sec
  float deltaTime = (RcurrentTime - RprevTime) / 1000.0;
  // Calculate position difference
  // Ensure deltaTime is never too small
  if (deltaTime < 0.001) { // 1 millisecond threshold
      deltaTime = 0.001;  // Prevent division issues
  }
  int deltaPosition = RcurrentPosition - RprevPosition;
  // for values that go over 1024 or under 0
  if (deltaPosition > 1024 / 2) 
  {
    deltaPosition -= 1024; // Adjust for 1023 - 0 
  } 
  else if (deltaPosition < -1024 / 2) 
  {
    deltaPosition += 1024; // Adjust for 0 - 1023 
  }
  // Calculate RPM
  Rrpm = (deltaPosition / deltaTime) * (60.0/1024);
  // Update previous values
  RprevPosition = RcurrentPosition;
  RprevTime = RcurrentTime;
  if (abs(deltaPosition) < 2) 
  { // Ignore minor fluctuations
    return Rrpm;  // Keep last valid RPM value
  }

}
float countLRevolutions() {
    int currentValue = analogRead(A0);

    // Normalize the encoder value to a 0-1 range
    float positionInRevolution = (float)(currentValue - minValue) / (maxValue - minValue);

    // Handle edge case where the encoder completes a full cycle
    if (positionInRevolution >= 0.95){
        revolutionCount += 1.0;
        positionInRevolution = 0.2; // Reset position within revolution
    }

    // Combine full revolutions with current position
    return revolutionCount + positionInRevolution;
}
float countRRevolutions() {
    int currentValue = analogRead(A1);

    // Normalize the encoder value to a 0-1 range
    float positionInRevolution = (float)(currentValue - minValue) / (maxValue - minValue);

    // Handle edge case where the encoder completes a full cycle
    if (positionInRevolution >= 0.95){
        revolutionCount += 1.0;
        positionInRevolution = 0.2; // Reset position within revolution
    }

    // Combine full revolutions with current position
    return revolutionCount + positionInRevolution;
}


///////////////////////////////////////////////////////// void loop /////////////////////////////////////////////////////////////

void loop() {

  // In loop() we continously check to see if a command has been
  //  received.
  if (XBee.available()) {
    char c = XBee.read();
    switch (c) {
      case 'w':       // If received 'w'
      case 'W':       // or 'W'        
        Lerror = MEASURE_LEFT_SPEED();
        speedL = computePID(abs(Lerror),MAIN_SPEED);
        Rerror = MEASURE_RIGHT_SPEED();
        speedR = computePID(abs(Rerror),MAIN_SPEED);
        PRINT(Lerror,speedL,Rerror,speedR);
        MOVE(1, 1, speedL, speedR);
      break;
      case 'a':       // If received 'a'
      case 'A':       // or 'A'
        Lerror = MEASURE_LEFT_SPEED();
        speedL = computePID(abs(Lerror),MAIN_SPEED);
        Rerror = MEASURE_RIGHT_SPEED();
        speedR = computePID(abs(Rerror),MAIN_SPEED);
        PRINT(Lerror,speedL,Rerror,speedR);
        MOVE(0, 0, speedL, speedR);
        break;
      case 's':       // If received 's'
      case 'S':       // or 'S'
        Lerror = MEASURE_LEFT_SPEED();
        speedL = computePID(abs(Lerror),MAIN_SPEED);
        Rerror = MEASURE_RIGHT_SPEED();
        speedR = computePID(abs(Rerror),MAIN_SPEED);
        PRINT(Lerror,speedL,Rerror,speedR);
        MOVE(1, 0, speedL, speedR);
        break;
      case 'd':       // If received 'd'
      case 'D':       // or 'D'
        Lerror = MEASURE_LEFT_SPEED();
        speedL = computePID(abs(Lerror),MAIN_SPEED);
        Rerror = MEASURE_RIGHT_SPEED();
        speedR = computePID(abs(Rerror),MAIN_SPEED);
        PRINT(Lerror,speedL,Rerror,speedR);
        MOVE(0, 1, speedL, speedR);
        break;
      case 'x':       // If received 'x'
      case 'X':       // or 'X'
        MOVE(0, 0, 0, 0);
      break;
      
    }
  }

}
// Write Digital Pin
// Send a 'd' or 'D' to enter.
// Then send a pin #
//   Use numbers for 0-9, and hex (a, b, c, or d) for 10-13
// Then send a value for high or low
//   Use h, H, or 1 for HIGH. Use l, L, or 0 for LOW
void writeDPin() {
  while (XBee.available() < 2)
    ;  // Wait for pin and value to become available
  char pin = XBee.read();
  char hl = ASCIItoHL(XBee.read());

  // Print a message to let the control know of our intentions:
  XBee.print("Setting pin ");
  XBee.print(pin);
  XBee.print(" to ");
  XBee.println(hl ? "HIGH" : "LOW");

  pin = ASCIItoInt(pin);  // Convert ASCCI to a 0-13 value
  pinMode(pin, OUTPUT);   // Set pin as an OUTPUT
  digitalWrite(pin, hl);  // Write pin accordingly
}

// Write Analog Pin
// Send 'w' or 'W' to enter
// Then send a pin #
//   Use numbers for 0-9, and hex (a, b, c, or d) for 10-13
//   (it's not smart enough (but it could be) to error on
//    a non-analog output pin)
// Then send a 3-digit analog value.
//   Must send all 3 digits, so use leading zeros if necessary.
void writeAPin() {
  while (XBee.available() < 4)
    ;                                         // Wait for pin and three value numbers to be received
  char pin = XBee.read();                     // Read in the pin number
  int value = ASCIItoInt(XBee.read()) * 100;  // Convert next three
  value += ASCIItoInt(XBee.read()) * 10;      // chars to a 3-digit
  value += ASCIItoInt(XBee.read());           // number.
  value = constrain(value, 0, 255);           // Constrain that number.

  // Print a message to let the control know of our intentions:
  XBee.print("Setting pin ");
  XBee.print(pin);
  XBee.print(" to ");
  XBee.println(value);

  pin = ASCIItoInt(pin);    // Convert ASCCI to a 0-13 value
  pinMode(pin, OUTPUT);     // Set pin as an OUTPUT
  analogWrite(pin, value);  // Write pin accordingly
}

// ASCIItoHL
// Helper function to turn an ASCII value into either HIGH or LOW
int ASCIItoHL(char c) {
  // If received 0, byte value 0, L, or l: return LOW
  // If received 1, byte value 1, H, or h: return HIGH
  if ((c == '0') || (c == 0) || (c == 'L') || (c == 'l'))
    return LOW;
  else if ((c == '1') || (c == 1) || (c == 'H') || (c == 'h'))
    return HIGH;
  else
    return -1;
}

// ASCIItoInt
// Helper function to turn an ASCII hex value into a 0-15 byte val
int ASCIItoInt(char c) {
  if ((c >= '0') && (c <= '9'))
    return c - 0x30;  // Minus 0x30
  else if ((c >= 'A') && (c <= 'F'))
    return c - 0x37;  // Minus 0x41 plus 0x0A
  else if ((c >= 'a') && (c <= 'f'))
    return c - 0x57;  // Minus 0x61 plus 0x0A
  else
    return -1;
}
