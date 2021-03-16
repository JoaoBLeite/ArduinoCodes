/**
 * Arduino - Parking gate control
 *
 * @author: JohnyStudent
 * @date: 13 Jun 2020
 * @version: v1.0
 */

#include <Servo.h>

// Global data:
int cm = 0;
int vagas = 5;
const int nrLed = 5;
int vtLed[nrLed] = {10, 2, 3, 4, 5};

// Method turn on 5 leds:
void LedHIGH ( ) {
  int c = 5;
  for ( int i = 0, c = 5; i < 5; i++, c-- ) {
    digitalWrite( c, HIGH );
  }
}

// Method turn off 5 leds:
void LedLOW ( ) {
  int c = 5;
  for ( int i = 0, c = 5; i < 5; i++, c-- ) {
    digitalWrite( c, LOW );
  }
}

// Car entry method:
void entrou ( ) {
  int i = 0;
  for ( i = 0; i < nrLed; i++ ) {
    if ( i <= vagas - 1 ) {
      digitalWrite( vtLed[i], LOW );
    } else {
      digitalWrite( vtLed[i], HIGH );
    }
  }
}

// Car exit method:
void saiu ( ) {
  int i = 0;
  for ( i = 0; i < nrLed; i++ ) {
    if ( i <= vagas - 1 ) {
      digitalWrite( vtLed[i], LOW );
    } else {
      digitalWrite( vtLed[i], HIGH );
    }
  }
}

// Function to calculate the distance with the car:
long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

Servo servo_9;

void setup()
{
  Serial.begin(9600);
  // Servo:
  servo_9.attach(9);
  // LEDs:
  pinMode(10, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  // Btn:
  pinMode(13, INPUT);

}

void loop()
{
  // Calculate distance in cm:
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  Serial.println(cm);
  delay(200);
  // check for a parking space:
  if ( vagas > 0 ) {
    // car entering:
    if ( cm <= 50 ) {
      servo_9.write(90);
      vagas = vagas - 1;
      entrou ( );
      delay(1000);
      servo_9.write(-90);
      delay(5000); 
    } else { // car not entering:
      servo_9.write(0);
    }
  }
  
  // check for cars in the vacancies:
  if ( vagas < 5 ) {
    // carro going out:
    if ( digitalRead(13) == HIGH ) {
      servo_9.write(90);
      vagas = vagas + 1;
      saiu ( );
      delay(1000);
      servo_9.write(-90);
      delay(5000); 
    }
  }
  
  
  //delay(5000); 
}
