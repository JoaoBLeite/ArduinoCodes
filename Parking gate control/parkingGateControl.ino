/* 
Exercicios LIP
PUC Minas - P. Liberdade
Joao Pedro Barbosa Leite - 690857
*/
#include <Servo.h>

// dados globais:
int cm = 0;
int vagas = 5;
const int nrLed = 5;
int vtLed[nrLed] = {10, 2, 3, 4, 5};

// metodo para acender todos os 5 Leds:
void LedHIGH ( ) {
  int c = 5;
  for ( int i = 0, c = 5; i < 5; i++, c-- ) {
    digitalWrite( c, HIGH );
  }
}

// metodo para apagar todos os 5 Leds:
void LedLOW ( ) {
  int c = 5;
  for ( int i = 0, c = 5; i < 5; i++, c-- ) {
    digitalWrite( c, LOW );
  }
}

// metodo de entrar um carro:
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

// metodo de sair um carro:
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

// funcao para calcular distancia:
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
  // Botão:
  pinMode(13, INPUT);

}

void loop()
{
  // Calcular distancia em cm:
  cm = 0.01723 * readUltrasonicDistance(7, 7);
  Serial.println(cm);
  delay(200);
  // verificar se ha vagas:
  if ( vagas > 0 ) {
    // carro entrando:
    if ( cm <= 50 ) {
      servo_9.write(90);
      vagas = vagas - 1;
      entrou ( );
      delay(1000);
      servo_9.write(-90);
      delay(5000); 
    } else { // carro nao entrando:
      servo_9.write(0);
    }
  }
  
  // verificar se ha carros nas vagas:
  if ( vagas < 5 ) {
    // carro saindo:
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