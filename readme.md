**Integrantes:

Evandro Yuji Kaibara de Oliveira RM 559274
Ícaro de Oliveira Santos RM 559950
Yasmin Baracat RM 559464


Monitor de Consumo de Energia**

Desenvolvemos esse projeto que apresenta um protótipo simples para o monitoramento de consumo de energia, utilizando no Wokwi componentes eletrônicos acessíveis como potenciômetro, LED, Buzzer, display LCD e um módulo RTC (Relógio de Tempo Real). Ele exibe informações de consumo e horário atual, além de alertar o usuário em casos de consumo elevado.

Embora seja uma solução de baixo custo, este projeto pode ser aprimorado com recursos como integração com IoT para monitoramento remoto e análise de dados.

- **Funcionalidades**
- **Monitoramento de consumo:**
  - O potenciômetro simula o consumo de energia elétrica.
  - O valor é convertido para uma escala percentual (0% a 100%).
- **Alertas visuais e sonoros:**
  - Consumo normal: exibição no display com LED desligado e buzzer inativo.
  - Consumo elevado (acima de 70%): LED aceso e buzzer ativado.
- **Exibição do horário:**
  - O RTC exibe a hora atual no display LCD.

- **Requisitos**
- **Hardware:**
  - Arduino UNO ou similar
  - Módulo RTC (DS1307)
  - Display LCD com interface I2C
  - Potenciômetro (10k)
  - LED
  - Buzzer
  - Resistores apropriados
- **Software:**
  - Arduino IDE
  - Biblioteca **Wire** (para comunicação I2C)
  - Biblioteca **LiquidCrystal\_I2C** (para o LCD)
  - Biblioteca **RTClib** (para o módulo RTC)

- **Montagem**
- **Conexões principais:**
  - Conecte o LCD ao Arduino pelos pinos SDA e SCL.
  - Ligue o RTC também aos pinos SDA e SCL.
  - Conecte o potenciômetro ao pino analógico A0.
  - Conecte o LED ao pino digital 2 e o Buzzer ao pino digital 3.
- **Alimentação:**
  - Certifique-se de que todos os componentes estejam devidamente alimentados.

- **Instruções de Uso (fisicamente)**
- Conecte todos os componentes ao Arduino seguindo o esquema de montagem.
- Faça o upload do código para o Arduino usando a Arduino IDE.
- Ajuste o potenciômetro para simular diferentes níveis de consumo:
  - Abaixo de 70%: mensagem de consumo normal será exibida.
  - Acima de 70%: alerta visual (LED) e sonoro (buzzer).
- O horário atual será exibido no display LCD.

**Melhorias Futuras**

- Integração com IoT para monitoramento remoto.
- Registro de dados para análise em tempo real.
- Adição de sensores reais para medir o consumo de dispositivos.



**Código:**
#include <Wire.h>

#include <LiquidCrystal\_I2C.h>

#include <RTClib.h>

// Inicializa o LCD e RTC

LiquidCrystal\_I2C lcd(0x27, 16, 2);

RTC\_DS1307 rtc;

const int potPin = A0; // Pino do potenciômetro

const int ledPin = 2;  // Pino do LED

const int buzzerPin = 3; // Pino do Buzzer

const int maxConsumption = 70; // Limite de consumo em %

void setup() {

`  `pinMode(ledPin, OUTPUT);

`  `pinMode(buzzerPin, OUTPUT);

`  `lcd.begin(16, 2);

`  `lcd.backlight();

`  `if (!rtc.begin()) {

`    `lcd.setCursor(0, 0);

`    `lcd.print("RTC Nao encontrado");

`    `while (1);

`  `}

`  `if (!rtc.isrunning()) {

`    `rtc.adjust(DateTime(F(\_\_DATE\_\_), F(\_\_TIME\_\_)));

`  `}

}

void loop() {

`  `int potValue = analogRead(potPin);

`  `int percentage = map(potValue, 0, 1023, 0, 100);

`  `lcd.setCursor(0, 0);

`  `if (percentage > maxConsumption) {

`    `lcd.print("ALTO CONSUMO!!  ");

`    `digitalWrite(ledPin, HIGH);

`    `tone(buzzerPin, 1000);

`  `} else {

`    `lcd.print("Consumo Normal  ");

`    `digitalWrite(ledPin, LOW);

`    `noTone(buzzerPin);

`  `}

`  `DateTime now = rtc.now();

`  `lcd.setCursor(0, 1);

`  `if (now.hour() < 10) lcd.print("0");

`  `lcd.print(now.hour());

`  `lcd.print(":");

`  `if (now.minute() < 10) lcd.print("0");

`  `lcd.print(now.minute());

`  `lcd.print(":");

`  `if (now.second() < 10) lcd.print("0");

`  `lcd.print(now.second());

`  `delay(5000);

}
