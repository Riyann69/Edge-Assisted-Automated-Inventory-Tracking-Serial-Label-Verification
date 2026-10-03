// Label verification station indicator (Review 2 output layer)
// Bytes from the PC:  G = PASS -> green LED   R = MISMATCH -> red LED   E = ERROR -> buzzer (re-capture)
const int GREEN = 8, RED = 9, BUZZ = 10;

void setup() {
  pinMode(GREEN, OUTPUT); pinMode(RED, OUTPUT); pinMode(BUZZ, OUTPUT);
  Serial.begin(9600);
  for (int i = 0; i < 2; i++) { digitalWrite(GREEN, HIGH); digitalWrite(RED, HIGH); delay(150);
                                digitalWrite(GREEN, LOW);  digitalWrite(RED, LOW);  delay(150); }
  Serial.println("READY");
}

void beep(int n, int onMs, int offMs) {
  for (int i = 0; i < n; i++) { digitalWrite(BUZZ, HIGH); delay(onMs); digitalWrite(BUZZ, LOW); delay(offMs); }
}

void loop() {
  if (!Serial.available()) return;
  char c = Serial.read();
  digitalWrite(GREEN, LOW); digitalWrite(RED, LOW);
  switch (c) {
    case 'G': digitalWrite(GREEN, HIGH); delay(1500); digitalWrite(GREEN, LOW); break;
    case 'R': digitalWrite(RED, HIGH);   delay(1500); digitalWrite(RED, LOW);   break;
    case 'E': beep(3, 120, 120); break;
  }
  Serial.write('A');   // ack
}
