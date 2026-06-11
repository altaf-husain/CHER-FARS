// Pin ke driver motor
const int RPWM = 12;   // Motor maju
const int LPWM = 11;   // Motor mundur
//const int EN   = 7;   // Enable Driver (BTS7960)

// Pin relay kipas
const int relayPin = 9;  

void setup() {
  Serial.begin(9600); // Inisialisasi Serial Monitor
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  //pinMode(EN, OUTPUT);
  pinMode(relayPin, OUTPUT);

  //digitalWrite(EN, HIGH); // Aktifkan motor driver
  digitalWrite(relayPin, LOW); // Pastikan relay OFF di awal

  Serial.println("Ketik 'UP', 'DOWN', atau 'FAN' di Serial Monitor:");
}

void loop() {
  if (Serial.available() > 0) {
    String perintah = Serial.readStringUntil('\n');
    perintah.trim(); // Hilangkan spasi ekstra

    if (perintah == "DOWN") {
      Serial.println("Motor Naik!");
      motorNaik();
    }
    else if (perintah == "UP") {
      Serial.println("Motor Turun!");
      motorTurun();
    }
    else if (perintah == "FAN") {
      Serial.println("Kipas Menyala!");
      hidupkanKipas();
    }
    else {
      Serial.println("Perintah tidak dikenali!");
    }
  }
}

// Fungsi motor naik (maju)
void motorNaik() {
  analogWrite(RPWM, 255); // Kecepatan 0-255
  analogWrite(LPWM, 0);
  delay(27000);            // Gerak 3 detik
  stopMotor();
}

// Fungsi motor turun (mundur)
void motorTurun() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 255);
  delay(27000);            // Gerak 3 detik
  stopMotor();
}

// Fungsi motor berhenti
void stopMotor() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);
  Serial.println("Motor berhenti.");
}

// Fungsi hidupkan kipas
void hidupkanKipas() {
  digitalWrite(relayPin, HIGH); // Relay ON
  delay(15000);                // 10 menit = 600.000 ms
  digitalWrite(relayPin, LOW);   // Relay OFF
  Serial.println("Kipas dimatikan setelah 10 menit.");
}
