void setup() {
  pinMode(13, OUTPUT); // пин 13 — встроенный светодиод
}

void loop() {
  digitalWrite(13, HIGH); // включить
  delay(1000);            // ждать 1 секунду
  digitalWrite(13, LOW);  // выключить
  delay(1000);            // ждать 1 секунду
}