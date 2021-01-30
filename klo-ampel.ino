
/** 
 * Configuration 
 */

const int gatePin = 2; 
const int redPin = 3; 
const int yellowPin = 4; 
const int greenPin = 5; 
const int statusPin = 6; 
const int cycleInterval = 500;    // in ms
const int hysteresis = 4;         // in cycles
const int changeLightDelay = 850; // in ms
const int turnOffDelay = 2000;    // in ms
const int interruptedState = LOW; // what state describes interrupted

bool someoneEntered = false; 
bool isOccupied = false; 
int cycleCount = 0; 

void setup() {
	Serial.begin(9600); 

	pinMode(redPin, OUTPUT); 
	pinMode(yellowPin, OUTPUT); 
	pinMode(greenPin, OUTPUT); 
	pinMode(statusPin, OUTPUT); 

	pinMode(gatePin, INPUT); 
}

void reset() {
	digitalWrite(redPin, LOW); 
	digitalWrite(yellowPin, LOW); 
	digitalWrite(greenPin, LOW); 
}

void readGateSensor() {
	int sensorValue = digitalRead(gatePin); 

	if(!someoneEntered && sensorValue == interruptedState) {
		someoneEntered = true; 		
		return; 
	}

	if(someoneEntered && sensorValue != interruptedState) {
		if(cycleCount != hysteresis) {
			cycleCount++; 
			return;
		}
		someoneEntered = false; 
	}

	cycleCount = 0; 
}

void runEnterSequence() {
	reset(); 

	digitalWrite(greenPin, HIGH); 
	delay(changeLightDelay); 
	digitalWrite(greenPin, LOW); 
	delay(changeLightDelay); 
	digitalWrite(greenPin, HIGH); 
	delay(changeLightDelay); 
	digitalWrite(greenPin, LOW); 
	digitalWrite(yellowPin, HIGH); 
	delay(changeLightDelay); 
	digitalWrite(yellowPin, LOW); 
	digitalWrite(redPin, HIGH); 
}

void runLeaveSequence() {
	reset(); 

	digitalWrite(redPin, HIGH); 
	delay(changeLightDelay); 
	digitalWrite(yellowPin, HIGH); 
	delay(changeLightDelay); 
	digitalWrite(redPin, LOW); 
	digitalWrite(yellowPin, LOW); 
	digitalWrite(greenPin, HIGH); 

	delay(turnOffDelay); 
	reset(); 
}

void triggerStatus() {
	digitalWrite(statusPin, HIGH); 
	delay(100); 
	digitalWrite(statusPin, LOW); 
}

void loop() {
	readGateSensor(); 

	if(someoneEntered && !isOccupied) {
		isOccupied = true; 
		runEnterSequence(); 
	}

	if(!someoneEntered && isOccupied) {
		isOccupied = false; 
		runLeaveSequence(); 
	}
	
	triggerStatus(); 
	delay(cycleInterval); 
}

