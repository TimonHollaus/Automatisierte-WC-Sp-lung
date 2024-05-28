#include <Servo.h>

Servo myservo;
const int buttonPin = 5; 
int buttonState = 0;  
boolean goofy = true;   //Deckeloffen? boolean

void setup() {
  myservo.attach(2);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  myservo.write(0);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  Serial.print("buttonstate: ");
  Serial.println(buttonState);
  //Serial.print("Servoposition: ");
  //Serial.println(myservo.read());
  if (buttonState == 1) {
      goofy = true;
  }
  if(goofy){
    if (digitalRead(buttonPin) == 0) {
      Serial.print("Warten 1 ");
      Serial.println(digitalRead(buttonPin));
      delay(2500);
      
      if(digitalRead(buttonPin) == 0){
        Serial.print("Warten 2 ");
        Serial.println(digitalRead(buttonPin));
        delay(2500);
        
        if(digitalRead(buttonPin) == 0){
          goofy = false;
          Serial.println("SPÜLUNG!");
          for (int pos = 0; pos <= 120; pos += 1) {
            myservo.write(pos);
            delay(15);
          }
          delay(1000);
          for (int pos = 120; pos >= 0; pos -= 1) {
            myservo.write(pos);
            delay(10);
          }
          
        }
       }
     }
   }
  delay(100);
}
