// C++ code
//
int SensorDir = 0;

int SensorEsq = 0;

int pinTrig = 8; // pino usado para disparar os pulsos do sensor
int pinEcho = 9; // pino usado para ler a saida do sensor
int pinLed = 10;
float tempoEcho = 0;
// Obs. Velocidade do som = 340,29 m/s = 0.00034029 m/us
const float velocidadeSom = 0.00034029; // em metros por microsegundo



void setup()
{
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(pinTrig, OUTPUT); // configura pino TRIG como saída
  pinMode(pinEcho, INPUT); // configura pino ECHO como entrada
  pinMode(pinLed, OUTPUT);

  // Inicializa pino Trig em nível baixo
  digitalWrite(pinTrig, LOW);
  

}

void loop()
{
  gatilhoSensor(); // envia pulso trigger (gatilho) para disparar o sensor  
  tempoEcho = pulseIn(pinEcho, HIGH); // mede o tempo de duração do sinal no pino de leitura em us
  // exibe no monitor serial
  Serial.print("Distancia em metros: ");
  Serial.println(calculaDistancia(tempoEcho), 4);
  Serial.print("Distancia em centimetros: ");
  Serial.println(calculaDistancia(tempoEcho)*100);
  Serial.println("------------------------------------");
  if (calculaDistancia(tempoEcho)*100 >= 25){
  //roda seu codigo aqui
    	
	  SensorDir = analogRead(A1);
  SensorEsq = analogRead(A0);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  
  if (SensorDir < 800) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  if (SensorEsq < 800) {
    digitalWrite(2, HIGH);
  } else {
    digitalWrite(2, LOW);
  }
  Serial.println(SensorDir);
  Serial.println(SensorEsq);
  delay(10); // Delay a little bit to improve simulation performance
  }
  else {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
  }
  delay (50);
}

// Funçao para enviar o pulso de trigger
void  gatilhoSensor(){
  // Para fazer o HC-SR04 enviar um pulso ultrassonico, nos temos
  // que enviar para o pino de trigger um sinal de nivel alto
  // com pelo menos 10us de duraçao
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
}

// Função para calcular a distancia em metros
float calculaDistancia(float tempoMicrossegundos){
  return((tempoMicrossegundos*velocidadeSom)/2); // velocidade do som em m/microssegundo
}