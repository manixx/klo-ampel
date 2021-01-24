/**
 * Klo-Ampel Code 
 */

/** 
 * Configuration 
 */

const int lightPin = A0; 
const int gatePin = A1; 
const int redPin = 10; 
const int yellowPin = 9; 
const int greenPin = 8; 

const int lightThreshold = 512; 
const int gateTThreshold = 512; 

const int cycleInterval = 200; // in ms 
const int restCount = 10; 

/** 
 * Sequences 
 */

const int[][4] enterSequence = [
/* R    Y    G     cycles */
	[LOW, LOW, HIGH, 10],	
	[LOW, LOW, LOW, 10],	
	[LOW, LOW, HIGH, 10],	
	[LOW, HIGH, LOW, 20],	
	[HIGH, LOW, LOW, 20],	
]; 
const int[][4] leaveSequence = [
/* R     Y    G    cycles */
	[HIGH, LOW, LOW, 20],	
	[HIGH, HIGH, LOW, 20],	
	[LOW, LOW, HIGH, 20],	
	[LOW, LOW, LOW, 10],	
]; 

/**
 * Application code 
 */

int gateValue = 0; 
int lightValue = 0; 
int cycleCount = 0; 

void reset() {
	digitalWrite(redPin, LOW); 
	digitalWrite(yellowPin, LOW); 
	digitalWrite(greenPin, LOW); 
}

bool someoneEntered() {
	if(gateValue == LOW && 
	return false; 
}

bool switchedLightOn() {
	return false; 
}

bool isLightOn() {
	return lightValue > lightThreshold; 
}

bool isGateInterrupted() {
	return gateValue > gateTThreshold;
}

void setup() {
	Serial.begin(9600); 

	pinMode(redPin, OUTPUT); 
	pinMode(yellowPin, OUTPUT); 
	pinMode(greenPin, OUTPUT); 
	reset();
}

void loop() {

	delay(cycleInterval); 
}

