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

  float WHEEL_RADIUS = 3.2; //cm
  float WHEEL_DIAMETER = 6.4; //cm (UNUSED)

  int MAIN_SPEED   = 75;
  int targetSpeed = 150;
  int leftSPEED = 255; 
  int rightSPEED = 255;

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
  Serial.begin(115200);
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


///////////////////////////////////////////////////////// void loop /////////////////////////////////////////////////////////////

void loop() {
  
  static word old_command = 0;
  word command = KitRS_RemoconRead();
  if (command != 0xFFFF) 
  {
    if (old_command != command) 
    {
      old_command = command;
    }
  }
  if (command == 0x1000)      ////////// 1 key //////////
  {
    int Lerror = MEASURE_LEFT_SPEED();
    int speedL = computePID(abs(Lerror),MAIN_SPEED);
    int Rerror = MEASURE_RIGHT_SPEED();
    int speedR = computePID(abs(Rerror),MAIN_SPEED);
    PRINT(Lerror,speedL,Rerror,speedR);
    MOVE(1, 1, speedL, speedR);

  } 
  else if (command == 0x4000)  ////////// 20cm //////////
  {
    int Lerror = MEASURE_LEFT_SPEED();
    int speedL = computePID(abs(Lerror),MAIN_SPEED);
    int Rerror = MEASURE_RIGHT_SPEED();
    int speedR = computePID(abs(Rerror),MAIN_SPEED);
    PRINT(Lerror,speedL,Rerror,speedR);
    MOVE(0, 0, speedL, speedR);
  } 
  else if (command == 0x8000) ////////// 40cm //////////
  {
    MOVE(1, 0, 140, 140);
  } 
  else if (command == 0x2000) ////////// 100cm //////////
  {
    MOVE(0, 1, 140, 140);
    
  } 
  else if (command == 0x0010) ////////// SPEED 25 RPM (KEY 5)/////////////
  {
    int Lerror = MEASURE_LEFT_SPEED();
    int speedL = computePID(abs(Lerror),25);
    int Rerror = MEASURE_RIGHT_SPEED();
    int speedR = computePID(abs(Rerror),25);
    PRINT(Lerror,speedL,Rerror,speedR);
    MOVE(1, 1, speedL, speedR);
  } 
  else if (command == 0x0040) ////////// SPEED 50 RPM (KEY 6) /////////////
  {   
    int Lerror = MEASURE_LEFT_SPEED();
    int speedL = computePID(abs(Lerror),50);
    int Rerror = MEASURE_RIGHT_SPEED();
    int speedR = computePID(abs(Rerror),50);
    PRINT(Lerror,speedL,Rerror,speedR);
    MOVE(1, 1, speedL, speedR);
  } 
  else if (command == 0x0080) ////////// SPEED 75 RPM (KEY 7) /////////////
  {
    int Lerror = MEASURE_LEFT_SPEED();
    int speedL = computePID(abs(Lerror),75);
    int Rerror = MEASURE_RIGHT_SPEED();
    int speedR = computePID(abs(Rerror),75);
    PRINT(Lerror,speedL,Rerror,speedR);
    MOVE(1, 1, speedL, speedR);
  } 
  else if (command == 0x0020) ////////// SPEED 80 RPM (KEY 8) /////////////
  {
    int Lerror = MEASURE_LEFT_SPEED();
    int speedL = computePID(abs(Lerror),80);
    int Rerror = MEASURE_RIGHT_SPEED();
    int speedR = computePID(abs(Rerror),80);
    PRINT(Lerror,speedL,Rerror,speedR);
    MOVE(1, 1, speedL, speedR);
  } 
  else if (command == 0x0100) 
  {
    
  } 
  else if (command == 0x0200) 
  {

  } 
  else if (command == 0x0000) 
  {
    MOVE(1, 1, 0, 0);
  }
}



word KitRS_RemoconRead() {
  static byte Check_Remocon_Index = 0;
  static byte Remocon_Buffer[3];
  
  while (Serial.available() > 0) {
    byte ch = Serial.read();

    switch (Check_Remocon_Index) {
      case 0:  // Header 1
        if (ch == 0xAA) Check_Remocon_Index++;
        break;

      case 1:  // Header 2
        if (ch == 0x55) Check_Remocon_Index++;
        else Check_Remocon_Index = 0;
        break;

      case 5:  // Checksum
        Check_Remocon_Index = 0;
        {
          byte checksum = Remocon_Buffer[0];
          checksum += Remocon_Buffer[1];
          checksum += Remocon_Buffer[2];

          if (checksum == ch) {
            word com = Remocon_Buffer[0];
            com <<= 8;
            com |= Remocon_Buffer[1];  // Remocon_Buffer[2] is always 0x00
            return com;
          } else {
            return 0xFFFF;
          }
        }
        break;

      default:  // Case 2-4
        if (ch == 0xAA) Check_Remocon_Index = 1;
        else {
          Remocon_Buffer[Check_Remocon_Index - 2] = ch;
          Check_Remocon_Index++;
        }
        break;
    }
  }

  return 0xFFFF;
}
