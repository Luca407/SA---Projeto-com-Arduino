#include <Servo.h>
#include <LiquidCrystal.h> // Incluindo a biblioteca do LCD

// LED RGB 
const int GREEN = 5;
const int BLUE = 4;
const int RED = 3;

// SERVO
Servo myservo;
int pinoServo = 6; // Declare pinoServo and assign a value

// SENSOR
const int SonarTrigger = 7;
const int SonarEcho = 2;

// LCD
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); // Conexões do LCD

// Variável para armazenar a distância anterior
float distanciaAnterior = -1;

// Função para medir distância
float medirDistancia() {
  digitalWrite(SonarTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(SonarTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(SonarTrigger, LOW);
  long duracao = pulseIn(SonarEcho, HIGH);
  return duracao * 0.034 / 2; // Calcula a distância em centímetros
}

void setup() {
  myservo.attach(pinoServo); // Anexa o pino do servo
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(SonarTrigger, OUTPUT);
  pinMode(SonarEcho, INPUT);
  
  lcd.begin(16, 2); // Inicializa o LCD
  Serial.begin(9600);
}

void loop() {
  float distancia = medirDistancia();

  // Verifica se a distância mudou
  if (distancia != distanciaAnterior) {
    // Controlar o LED e o LCD com base na nova distância
    if (distancia >= 1 && distancia < 70) { // PAPEL
      acenderLED(0, 0, 255);
      atualizarLCD("Papel");
    } else if (distancia >= 75 && distancia < 145) { // METAL
      acenderLED(255, 255, 0);
      atualizarLCD("Metal");
    } else if (distancia >= 150 && distancia < 195) { // PLASTICO
      acenderLED(255, 0, 0);
      atualizarLCD("Plastico");
    } else if (distancia >= 200 && distancia < 245) { // VIDRO
      acenderLED(0, 255, 0);
      atualizarLCD("Vidro");
    } else if (distancia >= 250 && distancia < 295) { // ORGANICO
      acenderLED(139, 69, 19);
      atualizarLCD("Organico");
    } else if (distancia >= 300 && distancia < 325) { // NAO SE RECICLA
      acenderLED(128, 128, 128);
      atualizarLCD("Nao se recicla");
    }

    // Gira o servo 180 graus
    myservo.write(180); // Gira para 180 graus
    delay(1000); // Aguarda 1 segundo
    myservo.write(0); // Retorna para 0 graus
    delay(800); // Aguarda 1 segundo

    // Atualiza a distância anterior
    distanciaAnterior = distancia;
  }

  delay(10000); // Adiciona um pequeno atraso
}

void acenderLED(int r, int g, int b) {
  analogWrite(RED, r);
  analogWrite(GREEN, g);
  analogWrite(BLUE, b);
}

void atualizarLCD(String material) {
  lcd.clear(); // Limpa o LCD
  lcd.setCursor(0, 0); // Define o cursor na primeira linha
  lcd.print(material); // Exibe o material correspondente
}
