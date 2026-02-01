#include <Arduino.h>
#include <QTRSensors.h>
#include <Preferences.h>
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

#define CTRL 9

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

QTRSensors QTR;

int error = 0;
int lastError = 0;
long long integral = 0;
long long derivative = 0;

double Kp = 0.06; //0.065
double Ki = 0.0;
double Kd = 0.11;

double drive = 0;

const int baseSpeed = 50;
const int maxSpeed  = 80;

const uint8_t SensorCount = 8;
const uint8_t SensorPins[SensorCount] = {A0, A1, A2, A3, A4, A5, A6, A7};
uint16_t SensorReadings[SensorCount];

void setup() {
	Serial.begin(115200);

	QTR.setTypeAnalog();
	QTR.setSensorPins(SensorPins, SensorCount);
	QTR.setEmitterPin(CTRL);

	delay(500);

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

	pinMode(STBY, OUTPUT);
	digitalWrite(STBY, LOW);

	Serial.println("\n=== CALIBRATING SENSORS ===");

	for (uint16_t i = 0; i < 400; i++) {
		QTR.calibrate();
	}

	digitalWrite(LED_BUILTIN, LOW);
	Serial.println("Calibration done!\n");

	digitalWrite(STBY, HIGH);
	delay(500);

	setMotor(0, 0);
}

void loop() {
	// uint16_t position = QTR.readLineBlack(SensorReadings);
	uint16_t position = QTR.readLineWhite(SensorReadings);

	int target = 3500;
	error = target - position;

	integral += error;
	derivative = error - lastError;

	drive = Kp * error + Ki * integral + Kd * derivative;

	lastError = error;

		float factor = 1.0 - min(abs(error) / 7000.0, 0.25);
		int slowBase = baseSpeed * factor;

	int leftSpeed  = slowBase + drive;
	int rightSpeed = slowBase - drive;

	setMotor(leftSpeed, rightSpeed);

	for (uint8_t i = 0; i < SensorCount; i++) {
		Serial.print(SensorReadings[i]);
		Serial.print('\t');
	}

	Serial.print(position);
	Serial.print('\t');
	Serial.print(error);
	Serial.print('\t');
	Serial.println(drive);

	delay(1);
}