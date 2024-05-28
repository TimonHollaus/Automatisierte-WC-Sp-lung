# Eigene EK - Automatisierte WC Spülung

#### Material

* Arduino uno

* Magnetsensor

* Servomotor

* Metallstab

* WC

#### Umsetzung

Gemeinsam mit meinem Vater habe ich die WC-Spülung zuhause automatisiert. Dafür habe ich hinter der Fließenabdeckung einen read Kontakt angebracht, der bei einem Magnetischen Signal eine 1 schriebt. Unter dem WC-Deckel habe ich einen Magneten montiert, sodass wenn der Deckel öffen ist ein Signal vorhanden ist. Wird er geschlossen, gibt der Sensor 0 zurück und nach einem kurzen Delay wird die Spülung von einem Servomotor ausgelöst. Dafür habe ich einen Metallstab an einem Ende an den Servo, am anderen an dem Spülungsmechanismus angebracht. Wenn der Sensor kein Signal mehr empfängt, dreht sich der Servomotor um 180°, zieht dabei den Metallstab nach oben und löst somit die Spülung aus. Kurze Zeit später dreht er sich wieder in seine Ausgangsposition. Das ganze Programm läuft auf einem Arduino Uno.

```c
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

```
