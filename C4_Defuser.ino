/*
Github : github.com/Stalker-moment/C4-Bomb
Instagram : @tierkunn_
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define rxPin 0       // Pin RX untuk menerima data dari Arduino lain
#define buttonPin 3   // Pin tombol untuk memulai animasi
#define feedbackPin 4 // Pin digital untuk memberikan feedback sinyal
#define LR 5 //LED RED
#define LG 6 //LED GREEEN
#define LB 7 //LED BLUE

String dataIn;
String dt[10];
int i;
boolean parsing=false;
String Activated;

// Inisialisasi objek LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C dan ukuran LCD (16x2)

// Array untuk menyimpan karakter khusus angka
byte numberChars[10][8] = {
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x11}, // 0
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00}, // 1
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0x15, 0x17}, // 2
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x11, 0x15, 0x1F}, // 3
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x04, 0x04}, // 4
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x15, 0x1D}, // 5
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x15, 0x1D}, // 6
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x1F}, // 7
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x15, 0x1F}, // 8
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x14, 0x1F}  // 9
};

// Fungsi untuk membuat karakter khusus angka pada CGRAM
void createNumberChars() {
  for (int i = 0; i < 10; i++) {
    lcd.createChar(i, numberChars[i]);
  }
}

int targetNumber = 0;     // Angka yang akan dianimasikan
bool connected = false;  // Status koneksi dengan Arduino lain
bool animating = false;  // Status animasi sedang berjalan atau tidak

void setup() {
  lcd.init();  // Inisialisasi LCD
  lcd.backlight();

  createNumberChars(); // Membuat karakter khusus angka

  pinMode(rxPin, INPUT);         // Set pin RX sebagai input
  pinMode(buttonPin, INPUT_PULLUP);     // Set pin tombol sebagai input
  pinMode(feedbackPin, OUTPUT);  // Set pin feedback sebagai output
  digitalWrite(feedbackPin, HIGH);
  pinMode(LR, OUTPUT);
  pinMode(LG, OUTPUT);
  pinMode(LB, OUTPUT);

  digitalWrite(LR, HIGH);
  digitalWrite(LG, HIGH);
  digitalWrite(LB, HIGH);
  delay(100);
  digitalWrite(LR, LOW);
  digitalWrite(LG, LOW);
  digitalWrite(LB, LOW);
  delay(100);
  digitalWrite(LR, HIGH);
  digitalWrite(LG, HIGH);
  digitalWrite(LB, HIGH);
  delay(100);
  digitalWrite(LR, LOW);
  digitalWrite(LG, LOW);
  digitalWrite(LB, LOW);
  delay(100);
  digitalWrite(LR, HIGH);
  digitalWrite(LG, HIGH);
  digitalWrite(LB, HIGH);
  delay(100);
  digitalWrite(LR, LOW);
  digitalWrite(LG, LOW);
  digitalWrite(LB, LOW);
  delay(100);
  digitalWrite(LR, HIGH);
  digitalWrite(LG, HIGH);
  digitalWrite(LB, HIGH);

  digitalWrite(feedbackPin, HIGH);  // Mengatur output pin feedback ke LOW

  // Menampilkan tulisan "Bomb Cracker" pada baris pertama LCD
  lcd.setCursor(0, 0);
  lcd.print("Bomb Cracker");

  // Mengatur pesan pada baris kedua berdasarkan status koneksi
  lcd.setCursor(0, 1);
  if (connected) {
    lcd.print("Press To Crack");
    digitalWrite(LR, LOW);
    digitalWrite(LG, LOW);
    digitalWrite(LB, HIGH);
  } else {
    lcd.print("Connect Bomb");
    digitalWrite(LR, HIGH);
    digitalWrite(LG, LOW);
    digitalWrite(LB, LOW);
  }

  Serial.begin(9600);  // Memulai komunikasi serial dengan kecepatan 9600 bps
}

void animateDigit(int digit, int targetDigit) {
  int currentDigit = 1; // Angka saat ini untuk animasi digit
  int duration = random(1000, 2000); // Durasi animasi (1-2 detik)

  unsigned long startTime = millis(); // Waktu mulai animasi

  while (millis() - startTime < duration) {
    lcd.setCursor(digit, 1);
    lcd.print(currentDigit);
    digitalWrite(LR, LOW);
    digitalWrite(LG, HIGH);
    digitalWrite(LB, HIGH);
    delay(100); // Jeda antara setiap pembaruan angka
    digitalWrite(LR, LOW);
    digitalWrite(LG, LOW);
    digitalWrite(LB, LOW);
    currentDigit++;
    if (currentDigit > 9) {
      currentDigit = 0;
    }
  }

  lcd.setCursor(digit, 1);
  lcd.print(targetDigit);
}

void crackBomb() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Cracking Bomb...");
  animating = true;  // Mulai animasi
  digitalWrite(feedbackPin, HIGH);  // Memberikan feedback sinyal HIGH

  int digit1 = 0; // Angka untuk digit pertama
  int digit2 = 0; // Angka untuk digit kedua
  int digit3 = 0; // Angka untuk digit ketiga
  int digit4 = 0; // Angka untuk digit keempat

  while (!(digit1 == targetNumber / 1000 && digit2 == (targetNumber % 1000) / 100 && digit3 == (targetNumber % 100) / 10 && digit4 == targetNumber % 10)) {
    digitalWrite(LR, LOW);
    digitalWrite(LG, HIGH);
    digitalWrite(LB, HIGH);
    delay(500);
    digitalWrite(LR, LOW);
    digitalWrite(LG, LOW);
    digitalWrite(LB, LOW);
    delay(500);
    digitalWrite(LR, LOW);
    digitalWrite(LG, HIGH);
    digitalWrite(LB, HIGH);
    delay(500);
    digitalWrite(LR, LOW);
    digitalWrite(LG, LOW);
    digitalWrite(LB, LOW);
    delay(500);
    
    animateDigit(0, targetNumber / 1000);
    digit1 = targetNumber / 1000;

    animateDigit(1, (targetNumber % 1000) / 100);
    digit2 = (targetNumber % 1000) / 100;

    animateDigit(2, (targetNumber % 100) / 10);
    digit3 = (targetNumber % 100) / 10;

    animateDigit(3, targetNumber % 10);
    digit4 = targetNumber % 10;
  }

  digitalWrite(feedbackPin, LOW);  // Memberikan feedback sinyal LOW
  animating = false;  // Animasi selesai

  while (animating == false){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Bomb Defused");

  lcd.setCursor(0, 1);
  lcd.print("Crack Pin: ");
  lcd.print(String(targetNumber));
  digitalWrite(LR, LOW);
  digitalWrite(LG, HIGH);
  digitalWrite(LB, LOW);
  delay(500);
  digitalWrite(LR, LOW);
  digitalWrite(LG, LOW);
  digitalWrite(LB, LOW);
  delay(500);
  }
}

void loop() {
  if(Serial.available()>0) {
    char inChar = (char)Serial.read();
    dataIn += inChar;
    if (inChar == '\n') {
    parsing = true;
  }
}
 
if(parsing){
    parsingData();
    parsing=false;
    dataIn="";
  }
}

void parsingData(){
int j=0;
 
//kirim data yang telah diterima sebelumnya
Serial.print("data masuk : ");
Serial.print(dataIn);
 
//inisialisasi variabel, (reset isi variabel)
dt[j]="";
//proses parsing data
for(i=1;i<dataIn.length();i++){
//pengecekan tiap karakter dengan karakter (#) dan (,)
if ((dataIn[i] == '#') || (dataIn[i] == ','))
{
//increment variabel j, digunakan untuk merubah index array penampung
j++;
dt[j]="";       //inisialisasi variabel array dt[j]
}
else
{
//proses tampung data saat pengecekan karakter selesai.
dt[j] = dt[j] + dataIn[i];
}
}
 
//kirim data hasil parsing
Serial.print("data 1 (pass) : ");
Serial.println(dt[0]);
Serial.print("data 2 (activated) : ");
Serial.println(dt[1]);
Serial.print("\n\n");

//Wrapping data untuk di definisikan
String Tnum = dt[0];
Activated = dt[1];

targetNumber = Tnum.toInt();

  // Memeriksa status koneksi dengan Arduino lain melalui pin RX
  if (digitalRead(rxPin) == HIGH) {
    connected = true;
  } else {
    connected = false;
  }

  // Mengatur pesan pada baris kedua berdasarkan status koneksi
  if (connected) {
    lcd.setCursor(0, 0);
    lcd.print("Press To Crack");
    digitalWrite(LR, LOW);
    digitalWrite(LG, LOW);
    digitalWrite(LB, HIGH);
    delay(500);
  }


  // Memulai animasi jika tombol ditekan dan tidak ada animasi yang sedang berjalan
  if (digitalRead(buttonPin) == LOW && !animating) {
    crackBomb();
  }
}
