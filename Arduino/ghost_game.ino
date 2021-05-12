#define SERIAL_LOG

#define BUTTON_PRESS LOW

int green_led = 12;
int red_led = 13;

int input_1 = 7;
int input_2 = 8;
int input_3 = 9;

int door_num = -1;
int score = 0;
int high_score = 0;

boolean waiting_for_input = true;

void setup() {
  #ifdef SERIAL_LOG
  Serial.begin(9600);
  #endif
  
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  pinMode(input_1, INPUT);
  pinMode(input_2, INPUT);
  pinMode(input_3, INPUT);
}

void lose() {
  digitalWrite(red_led, HIGH);
  if (score > high_score) {
    #ifdef SERIAL_LOG
    Serial.println("New highscore!");
    #endif
    high_score = score;
  } else {
    #ifdef SERIAL_LOG
    Serial.print("Too bad, no new highscore. Highscore: ");
    Serial.println(high_score);
    #endif
  }
  score = 0;
  #ifdef SERIAL_LOG
  Serial.println("Lose");
  #endif
  delay(1000);
  digitalWrite(red_led, LOW);
}

void win() {
  digitalWrite(green_led, HIGH);
  score += 1;
  #ifdef SERIAL_LOG
  Serial.println("Win");
  #endif
  delay(1000);
  digitalWrite(green_led, LOW);
}

int get_random(int minr, int maxr) {
  randomSeed(millis() * 315.7);
  int i = random(minr, maxr);
  #ifdef SERIAL_LOG
  Serial.print("Generated random number: ");
  Serial.println(i);
  #endif
  return i;
}

void check_input() {
  if (digitalRead(input_1) == BUTTON_PRESS) {
    door_num = 1;
    waiting_for_input = false;
    #ifdef SERIAL_LOG
    Serial.print("Pressed button ");
    Serial.println("1");
    #endif
    return;
  }

  if (digitalRead(input_2) == BUTTON_PRESS) {
    door_num = 2;
    waiting_for_input = false;
    #ifdef SERIAL_LOG
    Serial.print("Pressed button ");
    Serial.println("2");
    #endif
    return;
  }

  if (digitalRead(input_3) == BUTTON_PRESS) {
    door_num = 3;
    waiting_for_input = false;
    #ifdef SERIAL_LOG
    Serial.print("Pressed button ");
    Serial.println("3");
    #endif
    return;
  }
}

void loop() {
  while (waiting_for_input) {
    check_input();
    delay(100);
  }

  if (door_num == get_random(1, 3)) {
    lose();
  } else {
    win();
  }

  #ifdef SERIAL_LOG
  Serial.print("Score: ");
  Serial.println(score);
  #endif

  waiting_for_input = true;
}
