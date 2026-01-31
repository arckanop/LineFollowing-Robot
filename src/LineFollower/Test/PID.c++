#include <Arduino.h>
#include <QTRSensors.h>
// #include <SparkFun_TB6612.h>
// #include <Wire.h>
// #include <Adafruit_BNO08x.h>

#define PWMA 8
#define AIN2 7
#define AIN1 6
#define STBY 5
#define BIN1 4
#define BIN2 3
#define PWMB 2

QTRSensors QTR;

int error = 0;
int lastError = 0;
long long integral = 0;
long long derivative = 0;

double Kp = 0.08;
double Ki = 0.0;
double Kd = 0.0;

double drive = 0;

const int baseSpeed = 70;
const int maxSpeed  = 90;

void setMotor(int leftSpeed, int rightSpeed) {
	if (leftSpeed >= 0) {
		digitalWrite(AIN1, HIGH);
		digitalWrite(AIN2, LOW);
	} else {
		digitalWrite(AIN1, LOW);
		digitalWrite(AIN2, HIGH);
		leftSpeed = -leftSpeed;
	}

	if (rightSpeed >= 0) {
		digitalWrite(BIN1, HIGH);
		digitalWrite(BIN2, LOW);
	} else {
		digitalWrite(BIN1, LOW);
		digitalWrite(BIN2, HIGH);
		rightSpeed = -rightSpeed;
	}

	leftSpeed  = constrain(leftSpeed, 0, 255);
	rightSpeed = constrain(rightSpeed, 0, 255);

	analogWrite(PWMA, leftSpeed);
	analogWrite(PWMB, rightSpeed);
}

const uint8_t SensorCount = 8;
const uint8_t SensorPins[SensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7};
uint16_t SensorReadings[SensorCount];

void setup() {
	Serial.begin(115200);

	QTR.setTypeAnalog();
	QTR.setSensorPins(SensorPins, SensorCount);

	QTR.setEmitterPin(9);

	delay(500);

	for (uint16_t i = 0; i < 400; i++) {
		QTR.calibrate();
	}

	pinMode(5, OUTPUT);
	digitalWrite(5, HIGH);
}

void loop() {
	uint16_t position = QTR.readLineBlack(SensorReadings);

	/*
	for (uint8_t i = 0; i < SensorCount; i++) {
		Serial.print(SensorReadings[i]);
		Serial.print('\t');
	}
	Serial.println(pos);
	*/

	int target = 3500;
    error = target - position;

    integral += error;
    derivative = error - lastError;

    drive = Kp * error + Ki * integral + Kd * derivative;

    lastError = error;

    int leftSpeed  = baseSpeed + drive;
    int rightSpeed = baseSpeed - drive;

    leftSpeed  = constrain(leftSpeed, -maxSpeed, maxSpeed);
    rightSpeed = constrain(rightSpeed, -maxSpeed, maxSpeed);

    setMotor(leftSpeed, rightSpeed);

    // Serial.print(position);
    // Serial.print('\t');
    // Serial.print(error);
    // Serial.print('\t');
    // Serial.println(drive);

    delay(5);
	
	// delay(100);
}