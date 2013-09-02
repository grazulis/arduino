#include <Servo.h>

Servo myservo;

void setup()
{
  myservo.attach(8);  // attaches the servo to digital pin 9
}


void loop()
{     
    myservo.write(90);  //tells the servo to go to the center position      
}
