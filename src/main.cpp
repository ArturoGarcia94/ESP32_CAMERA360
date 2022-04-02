#include <Arduino.h>
#include <AccelStepper.h>
AccelStepper stepperX(1, 14, 27);

#define home_switch 34 

long TravelX;  
int move_finished=1;  
long initial_homing=-1;  

void setup() {
   Serial.begin(9600); 
   pinMode(home_switch, INPUT_PULLDOWN);
   stepperX.setMaxSpeed(1800.0);      
   stepperX.setAcceleration(1800.0);

  Serial.print("Stepper is Homing . . . . . . . . . . . ");
  while (digitalRead(home_switch)) {  
    stepperX.moveTo(initial_homing);  
    initial_homing--;  
    stepperX.run();  
    delay(5);
  }
  stepperX.setCurrentPosition(0);
  stepperX.setMaxSpeed(1800.0);      
  stepperX.setAcceleration(1800.0);  
  initial_homing=1;

  while (!digitalRead(home_switch)) { 
    stepperX.moveTo(initial_homing);  
    stepperX.run();
    initial_homing++;
    delay(5);
  }
  stepperX.setCurrentPosition(0);
  Serial.println("Homing Completed");
  Serial.println("");
  stepperX.setMaxSpeed(1800.0);      
  stepperX.setAcceleration(1800.0);
  Serial.println("Ingresar angulo de camara (Negativo o Positivo)");
}
void loop() {
 while (Serial.available()>0)  { 
  move_finished=0;  
    TravelX= Serial.parseInt();  
  if (TravelX < 0 || TravelX > 3000) {  
    Serial.println("");
    Serial.println("Ajuste el angulo de referencia de la camara");
    Serial.println("");
  } else {
    Serial.print("Moviendo camara...... ");
    Serial.println(TravelX);
    stepperX.moveTo(TravelX);  
    delay(1000);  
  }
  }
  if (TravelX >= 0 && TravelX <= 3000) {
    if ((stepperX.distanceToGo() != 0)) {
      stepperX.run();
  }

  if ((move_finished == 0) && (stepperX.distanceToGo() == 0)) {
    Serial.println("Angulo de camara confirmado");
    Serial.println("");
    Serial.println("Ingresar angulo de camara (Negativo o Positivo)");
    move_finished=1; 
  }
  }
}