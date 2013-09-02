#include <Servo.h>


// ** Setup Leg servos - only 2 DOF so Hips and Ankles only
// ** Once finalized some of these could be defines I guess but the "Limits" are handy to change on the fly for short, long, gimp, etc
Servo LeftHip;
Servo LeftAnkle;

Servo RightHip;
Servo RightAnkle;

byte LeftHipPin          = 10;           // Define the servo pins and the In / Out / Center limits
  byte LeftHipCenterLimit;              // This way you can actually change the distance / settings on the fly via code for "Shortwalk", "LongWalk", etc
  byte LeftHipInLimit;                  // See the NormalWalk() and ShortWalk() subs at the bottom of the code
  byte LeftHipOutLimit;                 // This just makes it much easier to change things although it makes it a bit more complicated
  byte LeftHipCurrent;                  // This tracks the CURRENT servo position so we know what we need to do to move through sub-steps - could use the .read() function but this was easier at the time
  float LeftHipInc;                     // This variable is used by the sub-step routine that moves the servos from current to requested position as it is called over and over
                                        // These are floats as we are dividing how far we need to go by how many possible "substeps" we have to get there
                                        // Otherwise we loose resolution and do not complete the move from my personal experience... :-/

byte RightHipPin         = 8;          // This is on an analog to keep wiring shorter based on the Baby Orangutan pin layouts
  byte RightHipCenterLimit;
  byte RightHipInLimit;
  byte RightHipOutLimit;
  byte RightHipCurrent;
  float RightHipInc;

byte LeftAnklePin        = 11;
  byte LeftAnkleCenterLimit;
  byte LeftAnkleLeftLimit;
  byte LeftAnkleRightLimit;
  byte LeftAnkleCurrent;
  float LeftAnkleInc;

byte RightAnklePin        = 9;
  byte RightAnkleCenterLimit;
  byte RightAnkleLeftLimit;
  byte RightAnkleRightLimit;
  byte RightAnkleCurrent;
  float RightAnkleInc;
int stepCount = 3;
int stageCount = 0;

void setup()
{
// *** Attach and center our legs 
  LeftHip.attach(LeftHipPin);		// config the left/right/center leg servos
  LeftAnkle.attach(LeftAnklePin);

  RightHip.attach(RightHipPin);         // config the right leg
  RightAnkle.attach(RightAnklePin);
  
  CentreLegs();
}

void loop()
{
  if(stepCount > 0 ){
    switch(stageCount){
    case 0:  //Stage zero - Tilt left ankle 
      
      RightAnklePosition(120);
      LeftAnklePosition(60);
      RightAnklePosition(90);
  
      LeftHipPosition(90);
      RightHipPosition(90);
      stageCount++;
      
      break;
    
    case 1:  //Stage one
      
      LeftAnklePosition(60);
      RightAnklePosition(60);
  
      LeftHipPosition(120);
      RightHipPosition(120);
      stageCount++;
      
      break;
    
    case 2:  //Stage two

      LeftAnklePosition(90);
      RightAnklePosition(90);
    
      LeftHipPosition(120);
      RightHipPosition(120);
      stageCount++;
      break;
      
    case 3: //Stage three
      
      LeftAnklePosition(120);
      RightAnklePosition(120);
    
      LeftHipPosition(60);
      RightHipPosition(60);
      stageCount++;
      break;
    
    case 4: //Stage four
      
      LeftAnklePosition(90);
      RightAnklePosition(90);
    
      LeftHipPosition(60);
      RightHipPosition(60);

      stepCount--;
      stageCount = 0;
      break;
    }
    
    
  }else{
    CentreLegs();
  }
  
}

void CentreLegs(){
  LeftHipCurrent     = 90;      // Save the positions at start to have our reference points
  RightHipCurrent    = 90;
  LeftAnkleCurrent   = 90;
  RightAnkleCurrent  = 90;

  LeftAnklePosition(LeftAnkleCurrent);
  RightAnklePosition(RightAnkleCurrent);

  LeftHipPosition(LeftHipCurrent);
  RightHipPosition(RightHipCurrent);
}

void LeftAnklePosition(byte ServoPosition){
    SmoothMove(LeftAnkle, ServoPosition, LeftAnkleCurrent);
    LeftAnkleCurrent = ServoPosition;
    //LeftAnkle.write(ServoPosition);
}

void RightAnklePosition(byte ServoPosition){
  SmoothMove(RightAnkle, ServoPosition, RightAnkleCurrent);  
  RightAnkleCurrent = ServoPosition;
    //RightAnkle.write(ServoPosition);
}

void LeftHipPosition(byte ServoPosition){
  SmoothMove(LeftHip, ServoPosition, LeftHipCurrent);  
  LeftHipCurrent = ServoPosition;
  //LeftHip.write(ServoPosition);
}

void RightHipPosition(byte ServoPosition){
  SmoothMove(RightHip, ServoPosition, RightHipCurrent);
    RightHipCurrent = ServoPosition;
    //RightHip.write(ServoPosition);
}

void SmoothMove(Servo servo, byte newPosition, byte currentPosition)
{
  if(currentPosition < newPosition)
  {
    for(currentPosition; currentPosition < newPosition; currentPosition += 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      servo.write(currentPosition);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
  }else{
    for(currentPosition; currentPosition > newPosition; currentPosition -= 1)  // goes from 0 degrees to 180 degrees 
    {                                  // in steps of 1 degree 
      servo.write(currentPosition);              // tell servo to go to position in variable 'pos' 
      delay(15);                       // waits 15ms for the servo to reach the position 
    } 
  }
}

