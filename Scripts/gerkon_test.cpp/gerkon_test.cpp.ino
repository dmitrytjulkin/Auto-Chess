const int whitereedPin = A3; 
const int blackreedPin = A4;  


void setup() {
  Serial.begin(9600);

  pinMode(whitereedPin, INPUT_PULLUP); // включаем внутренний подтягивающий резистор
  Serial.println("Проверка геркона на A3");

  pinMode(blackreedPin, INPUT_PULLUP); // включаем внутренний подтягивающий резистор
  Serial.println("Проверка геркона на A4");
}

void loop() {
  int state_white = digitalRead(whitereedPin);
  int state_black = digitalRead(blackreedPin);

  int white_square = 0;
  int black_square = 0;

  if (state_white == LOW) {
    white_square = 1;
  }

  if (state_black == LOW)
    black_square = 1;

  for (int i = 0; i < 20; ++i)
    Serial.println("\n");

  Serial.println("_______");
  Serial.println("|     |");
  Serial.print("|  "); Serial.print(white_square); Serial.println("  |");
  Serial.println("|     |");
  Serial.println("_______");
  Serial.println("|     |");
  Serial.print("|  "); Serial.print(black_square); Serial.println("  |");
  Serial.println("|     |");
  Serial.println("_______");

  delay(500);
}


// void setup() {
//   pinMode(13, OUTPUT); // встроенный светодиод на Mega
// }

// void loop() {
//   digitalWrite(13, HIGH); // включить
//   delay(2000);
//   digitalWrite(13, LOW);  // выключить
//   delay(200);
// }




