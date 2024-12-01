#include <QTRSensors.h>

#define button 2
#define QTRemitter 7
#define ledCalibrate 13
#define ledGo 13

#define motor1_A 6
#define motor1_B 5
#define motor2_A 10
#define motor2_B 9

#define maxVel 250  // Velocidad máxima
#define minVel 0    // Velocidad mínima para las curvas
#define retorno 100 // Velocidad de giro contrario de llanta para regresar a la linea
//120 - 75
//220-100
QTRSensors qtr;

const uint8_t SensorCount = 8;
uint16_t sensorValues[SensorCount];
/*

proporcional estabilidad
integral reduccion de error
derivativo velocidad de reaccion

*/

// Parámetros del controlador PID
float Kp = .05;    // seguimiento 
float Ki = 0.004;  // integral  
float Kd = 0.8;   // tolerancia  
int setpoint = 3500;

int lastError = 0;
int integral = 0;

void setup() {
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]){ A0, A1, A2, A3, A4, A5, A6, A7 }, SensorCount);
  qtr.setEmitterPin(QTRemitter);
  Serial.begin(9600);

  pinMode(button, INPUT);
  pinMode(ledCalibrate, OUTPUT);
  pinMode(ledGo, OUTPUT);

  digitalWrite(ledCalibrate, HIGH);
  while (!digitalRead(button)) {
    // Espera hasta que se presione el botón
  }

  for (uint16_t i = 0; i < 400; i++) {
    qtr.calibrate();
    digitalWrite(ledCalibrate, i % 2 == 0 ? LOW : HIGH);
  }
  digitalWrite(ledCalibrate, HIGH);
  while (!digitalRead(button)) {
    // Espera hasta que se presione el botón nuevamente
  }
  delay(500);

  digitalWrite(ledCalibrate, LOW);
  digitalWrite(ledGo, HIGH);

  delay(1000);
}

void loop() {
  uint16_t position = qtr.readLineBlack(sensorValues);
  Serial.println(position);
  int error = setpoint - position;
  int motorSpeed = Kp * error + Ki * integral + Kd * (error - lastError);

  // Ajustar la velocidad para las curvas
  int leftSpeed = maxVel - constrain(abs(motorSpeed), 0, maxVel - minVel);
  int rightSpeed = maxVel - constrain(abs(motorSpeed), 0, maxVel - minVel);

  if (motorSpeed > 0) {
    rightSpeed += motorSpeed;
  } else {
    leftSpeed -= motorSpeed;
  }

  if (position == 0) {
    /*
    hay que identificar los motores y hacer que las llantas giran hacia atras
    */
    analogWrite(motor1_A, 0);
    analogWrite(motor1_B, retorno);
    analogWrite(motor2_A, rightSpeed);
    analogWrite(motor2_B, 0);

    /*
  else if es mayor a 0 y menor a 7000 
  entran los valores pid normal
    */
  } else if (position == 7000) {
    analogWrite(motor1_A, leftSpeed);
    analogWrite(motor1_B, 0);
    analogWrite(motor2_A, 0);
    analogWrite(motor2_B, retorno);
  } else if (position > 0 && position < 7000) {
    analogWrite(motor1_A, leftSpeed);
    analogWrite(motor1_B, 0);
    analogWrite(motor2_A, rightSpeed);
    analogWrite(motor2_B, 0);
  }
  else {
    analogWrite(motor1_A, 0);
    analogWrite(motor1_B, 0);
    analogWrite(motor2_A, 0);
    analogWrite(motor2_B, 0);
  }

  lastError = error;
  integral += error;
}