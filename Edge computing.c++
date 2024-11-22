#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>


// Inicializa o LCD e RTC
LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc;

const int potPin = A0; // Pino do potenciômetro
const int ledPin = 2;  // Pino do LED
const int buzzerPin = 3; // Pino do Buzzer

const int maxConsumption = 70; // Limite de consumo em %

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.backlight();

  // Verificar se o RTC está conectado
  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("RTC Nao encontrado");
    while (1); // Para o código caso o RTC falhnão funcione
  }

  // Ajustar o rtc para o horário atual 
  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Ajusta para a data/hora do compilador
  }
}

void loop() {
  // Lê o valor do potenciômetro
  int potValue = analogRead(potPin);
  int percentage = map(potValue, 0, 1023, 0, 100); // Converter para %

  // Texto
  lcd.setCursor(0, 0);
  if (percentage > maxConsumption) {
    lcd.print("ALTO CONSUMO!!  ");
    digitalWrite(ledPin, HIGH);  // Liga o LED
    tone(buzzerPin, 1000);       // ativa o buzzer
  } else {
    lcd.print("Consumo Normal  ");
    digitalWrite(ledPin, LOW);   // desligarr o led
    noTone(buzzerPin);           // desligar o buzzer
  }

  // Para exibir o horário atual
  DateTime now = rtc.now();
  lcd.setCursor(0, 1);
  if (now.hour() < 10) lcd.print("0"); // Adicionar zero antes das horas
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0"); 
  lcd.print(now.minute());
  lcd.print(":");
  if (now.second() < 10) lcd.print("0"); 
  lcd.print(now.second());

  delay(5000); // Atualiza a cada 5 segundos
}

