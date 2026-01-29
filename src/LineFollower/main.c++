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
	// uint16_t pos = QTR.readLineBlack(SensorReadings);

	// for (uint8_t i = 0; i < SensorCount; i++) {
	// 	Serial.print(SensorReadings[i]);
	// 	Serial.print('\t');
	// }
	// Serial.println(pos);
	
	delay(100);
}