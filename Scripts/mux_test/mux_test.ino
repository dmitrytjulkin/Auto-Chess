const int S0_PIN   = A11;
const int S1_PIN   = A9;
const int S2_PIN   = A10;
const int S3_PIN   = 45;

const int SIG_PIN  = A3;
const int TEST_PIN = A4;

void setup() {
  Serial.begin(9600);

  pinMode(S0_PIN, OUTPUT);
  pinMode(S1_PIN, OUTPUT);
  pinMode(S2_PIN, OUTPUT);
  pinMode(S3_PIN, OUTPUT);

  pinMode(TEST_PIN, OUTPUT);
  pinMode(SIG_PIN, INPUT);

  digitalWrite(TEST_PIN, HIGH);
}

void loop() {
  int values[16];

  for (int ch = 0; ch < 16; ch++) {
    digitalWrite(S0_PIN, (ch & 0x01) ? HIGH : LOW);
    digitalWrite(S1_PIN, (ch & 0x02) ? HIGH : LOW);
    digitalWrite(S2_PIN, (ch & 0x04) ? HIGH : LOW);
    digitalWrite(S3_PIN, (ch & 0x08) ? HIGH : LOW);

    delay(2);
    values[ch] = digitalRead(SIG_PIN);
  }

\
  Serial.println("_____________");
  Serial.println("|   |   |   |");

  Serial.print("| ");
  Serial.print(values[1]);
  Serial.print(" | ");
  Serial.print(values[2]);
  Serial.print(" | ");
  Serial.print(values[0]);
  Serial.println(" |");
  
  Serial.println("|   |   |   |");
  Serial.println("_____________");  

  delay(500);
}