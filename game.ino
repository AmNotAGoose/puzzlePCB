// these are wrong, il fix them when the pcb arrives.
const int BUT_RESET = A2;
const int BUT_1 = A0;
const int BUT_2 = A1;
const int BUT_3 = A3; 

const int LED1 = D3;
const int LED2 = D4;
const int LED3 = D5;
const int LED4 = D6;
const int LED5 = D7; 
const int LED6 = D8;

int leds[] = {LED1, LED2, LED3, LED4, LED5, LED6};
int ledStates[] = {0, 0, 0, 0, 0, 0};

int buttonMask1[] = {0, 0, 0, 0, 0, 0};
int buttonMask2[] = {0, 0, 0, 0, 0, 0};
int buttonMask3[] = {0, 0, 0, 0, 0, 0};
int* buttonMasks[] = {buttonMask1, buttonMask2, buttonMask3};
the hawk is almost done....


void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  pinMode(BUT_1, INPUT_PULLUP);
  pinMode(BUT_2, INPUT_PULLUP);
  pinMode(BUT_3, INPUT_PULLUP);
  pinMode(BUT_RESET, INPUT_PULLUP);

  randomSeed(analogRead(A4));
  playStartingAnimation();
  generateInitalState();
}

void randomizeMask() {
  for (int i = 0; i < 6; i++) {
    buttonMask1[i] = random(0, 2);
    buttonMask2[i] = random(0, 2);
    buttonMask3[i] = random(0, 2);
  }
}

void generateInitalState() {
  randomizeMask();

  int solutionLength = random(3, 6);
  int solution[solutionLength];
  
  for (int i = 0; i < 6; i++) ledStates[i] = 1;
  
  for (int i = 0; i < solutionLength; i++) {
    solution[i] = random(0, 3);
    applyLedState(buttonMasks[solution[i]]);
  }
  
  for (int i = 0; i < 6; i++) {
    digitalWrite(leds[i], ledStates[i]);
  }
}

void applyLedState(int* mask) {
  for (int i = 0; i < 6; i++) {
    if (mask[i]) {
      ledStates[i] = !ledStates[i];
      digitalWrite(leds[i], ledStates[i]);
    }
  }
}

void checkWin() {
  for (int i = 0; i < 6; i++) {
    if (!ledStates[i]) return;
  }

  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 6; i++) {
      digitalWrite(leds[i], HIGH);
      delay(80);
      digitalWrite(leds[i], LOW);
    }
    for (int i = 5; i >= 0; i--) {
      digitalWrite(leds[i], HIGH);
      delay(80);
      digitalWrite(leds[i], LOW);
    }
  }

  for (int j = 0; j < 6; j++) {
    for (int i = 0; i < 6; i++) {
      if (j % 2 == 0) {
        if (i % 2 == 0) {
          digitalWrite(leds[i], HIGH);
        }
      } else {
        if (i % 2 != 0) {
          digitalWrite(leds[i], HIGH);
        }
      }
    }

    delay(200);

    for (int i = 0; i < 6; i++) {
      digitalWrite(leds[i], LOW);
    }
  }

  
  for (int i = 0; i < 6; i++) {
    digitalWrite(leds[i], LOW);
  }
  
  delay(500);
  generateInitalState();
}

void playStartingAnimation() {
  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 6; i++) {
      digitalWrite(leds[i], HIGH);
      delay(100);
      digitalWrite(leds[i], LOW);
    }
  }
}

void playResetAnimation() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(leds[i], HIGH);
    delay(100);
  }
  for (int i = 0; i < 6; i++) {
    digitalWrite(leds[i], LOW);
    delay(50);
  }
}

void loop() {
  if (digitalRead(BUT_1) == LOW) {
    applyLedState(buttonMasks[0]);
    delay(300);
  }
  else if (digitalRead(BUT_2) == LOW) {
    applyLedState(buttonMasks[1]);
    delay(300);
  }
  else if (digitalRead(BUT_3) == LOW) {
    applyLedState(buttonMasks[2]);
    delay(300);
  }
  else if (digitalRead(BUT_RESET) == LOW) {
    playResetAnimation();
    generateInitalState();
    delay(300);
  }

  checkWin();
}
