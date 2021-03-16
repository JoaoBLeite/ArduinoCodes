/**
 * Arduino - Genius Game
 *
 * @author: JohnyStudent
 * @date: 8 Jun 2020
 * @version: v3.1
 */

// Global Data:
	// LEDs Vector:
	const int nrLed  = 4;
	int vtLed[nrLed] = {13, 12, 11, 10};
	// Player Vextor:
	const int nrTotal = 8;
	int vtPlayer[nrTotal] = {7, 7, 7, 7, 7, 7, 7, 7};
	// Game Vector:
	int vtGenius[nrTotal] = {7, 7, 7, 7, 7, 7, 7, 7};

// Method to turn on all 4 leds:
void LedHIGH ( ) {
  for ( int i = 0; i < nrLed; i++ ) {
    digitalWrite( vtLed[i], HIGH );
  }
}

// Method to turn off all 4 leds:
void LedLOW ( ) {
  for ( int i = 0; i < nrLed; i++ ) {
    digitalWrite( vtLed[i], LOW );
  }
}

// Method for flashing certain led:
void piscar ( int x ) {
  digitalWrite( vtLed[x], HIGH );
  delay(1000);
  digitalWrite( vtLed[x], LOW );
}

// Method for receiving the player's response:
int getResposta ( ) {
  int resp = 13;
  while ( resp == 13 ) {	
    if ( digitalRead(7) == HIGH ) {
      piscar(0);
      resp = 0;
      Serial.println("bnt-Red");
    }
    if ( digitalRead(6) == HIGH ) {
      piscar(1);
      resp = 1;
      Serial.println("bnt-Blue");
    }
    if ( digitalRead(5) == HIGH ) {
      piscar(2);
      resp = 2;
      Serial.println("bnt-Yellow");
    }
    if ( digitalRead(4) == HIGH ) {
      piscar(3);
      resp = 3;
      Serial.println("bnt-Green");
    }
  }
  return resp;
}

// Method to check
int verificar ( int array[], int vetor[], int num ) {
  int cc = 0;
  for ( int i = 0; i < num; i++ ) {
    if ( array[i] != vetor[i] ) {
      cc++;
    }
  }
  return cc;
}

// Method for victory
void vitoria ( ) {
  int x = 0;
  while ( x < 3 ) {
  	LedHIGH ( );
  	delay(500);
  	LedLOW ( );
  	delay(500);
    x++;
  }
}

// Method for opening:
void abertura ( ) {
  LedLOW ( );
  digitalWrite( vtLed[0], HIGH );
  delay(500);
  digitalWrite( vtLed[1], HIGH );
  delay(500);
  digitalWrite( vtLed[0], LOW );
  digitalWrite( vtLed[2], HIGH );
  delay(500);
  digitalWrite( vtLed[1], LOW );
  digitalWrite( vtLed[3], HIGH );
  delay(500);
  digitalWrite( vtLed[2], LOW );
  delay(500);
  digitalWrite( vtLed[3], LOW );
  delay(500);
  LedHIGH ( );
  LedLOW( );
}

// =============== GAME MODE 01 ===============

void game01 ( ) {

  // Local Data:
  int c      = 0;
  int ledzin = 0;
  int T      = 1;
  int verif  = 0;
  int respp  = 0;
  int a = 0;
  
  // Game:
  while ( T < 9 ) {
    for ( int i = 0; i < T; i++ ) {
      respp = 0;
      // Store data:
      c = random ( 0, nrLed );
      vtGenius[i] = c;
      // Flash led:
      for ( int j = 0; j < T; j++ ) {
        ledzin = vtGenius[j];
        piscar(ledzin);
        delay(500);
      } 
      // Get answer:
      for ( int p = 0; p < T; p = p + 1 ) {
        Serial.println("Player - give your answer");
      	respp = getResposta ( );
      	vtPlayer[p] = respp;
        // If the player misses during a stage:
        if ( vtPlayer[p] != vtGenius[p] ) {
          for ( int u = 0; u < 3; u++ ) {
            piscar(vtGenius[p]);
            delay(300);
          }
          LedHIGH ( );
          delay (2000);
          LedLOW ( );
          delay (1000);
          Serial.println("Missed the stage");
          loop( );
        }
      }  
      // Check the final answer:
      verif = verificar( vtPlayer, vtGenius, T );
      if ( verif == 0 ) {
        // Right answer:
        T++;
        a++;
        Serial.println("You got this stage");
        if ( a == 8 ) {
          Serial.println("CONGRATULATIONS, the victory is yours");
  		  vitoria( );
          loop ( );
        }
      } else {
        // Wrong answer:
        LedHIGH ( );
        delay (2000);
        LedLOW ( );
        delay (1000);
        Serial.println("You lose");
        loop ( );
      }
    }
  }

}

// =============== GAME MODE 02 ===============

void game02 ( ) {

  // Local data:
  int c      = 0;
  int ledzin = 0;
  int T      = 1;
  int verif  = 0;
  int respp  = 0;
  int a = 0;
  
  // Game:
  while ( T < 9 ) {
    for ( int i = 0; i < T; i++ ) {
      respp = 0;
      // Store data:
      Serial.println("Challenger - Turn on one led");
      c = getResposta ( );
      vtGenius[i] = c;
      // Flash led:
        piscar( vtLed[i] );
        delay(500);
      // Get answer
      for ( int p = 0; p < T; p = p + 1 ) {
        Serial.println("Player - give your answer");
      	respp = getResposta ( );
      	vtPlayer[p] = respp;
        // If the player misses during a stage:
        if ( vtPlayer[p] != vtGenius[p] ) {
          for ( int u = 0; u < 3; u++ ) {
            piscar(vtGenius[p]);
            delay(300);
          }
          LedHIGH ( );
          delay (2000);
          LedLOW ( );
          delay (1000);
          Serial.println("Player - missed the stage");
          loop( );
        }
      }  
      // Check the final answer:
      verif = verificar( vtPlayer, vtGenius, T );
      if ( verif == 0 ) {
        // Right answer:
        T++;
        a++;
        Serial.println("You got this stage");
        if ( a == 8 ) {
          Serial.println("Player won the challenger");
  		  vitoria( );
          loop ( );
        }
      } else {
        // Wrong answer:
        LedHIGH ( );
        delay (2000);
        LedLOW ( );
        delay (1000);
        Serial.println("You lose");
        loop ( );
      }
    }
  }

}

void setup()
{
  Serial.begin(9600);
  // LEDs:
  pinMode(13, OUTPUT); // Red
  pinMode(12, OUTPUT); // Blue
  pinMode(11, OUTPUT); // Yellow
  pinMode(10, OUTPUT); // Green
  // Buttons:
  pinMode(7, INPUT); // Red
  pinMode(6, INPUT); // Blue
  pinMode(5, INPUT); // Yellow
  pinMode(4, INPUT); // Green
  
}

void loop()
{ 
  int resp;
  int c = 1;
  abertura ( );
  LedLOW( );
  delay(300);
  digitalWrite( vtLed[0], HIGH );
  digitalWrite( vtLed[3], HIGH );
  Serial.println("\nGame Menu");
  Serial.println("RED   - Game mode 01 - Solo");
  Serial.println("GREEN - Game mode 02 - 1v1");
  Serial.print("\n\nYour answer:");
  while ( c == 1 ) {
    if ( digitalRead(7) == HIGH ) {
      LedLOW ( );
      digitalWrite( vtLed[0], HIGH );
      c = 0;
      resp = 1;
      delay(1000);
    }
    if ( digitalRead(4) == HIGH ) {
      LedLOW ( );
      digitalWrite( vtLed[3], HIGH );
      c = 0;
      resp = 2;
      delay(1000);
    }
  }
  switch (resp) {
  case 1:
    LedLOW ( );
    delay (1000);
  	game01 ( );
  break;
  case 2:
    LedLOW ( );
    delay (1000);
  	game02 ( );
  break;
  default :
  Serial.println("This option does not exist! Try again:");
  }
}
