
/** 
 * Configuration 
 */

const int gatePin = 2; 
const int redPin = 3; 
const int yellowPin = 4; 
const int greenPin = 5; 
const int statusPin = 6; 
const int cycleInterval = 800;    // in ms
const int hysteresis = 6;         // in cycles
const int changeLightDelay = 900; // in ms
const int turnOffDelay = 2500;    // in ms
const int interruptedState = LOW; // what state describes interrupted
const int ledHIGH = HIGH; 
const int ledLOW = LOW; 
const bool enableStatus = false; 

bool someoneEntered = false; 
bool isOccupied = false; 
int cycleCount = 0; 

void printStatus() {
	Serial.print("someoneEntered: "); 
	Serial.print(someoneEntered); 

	Serial.print("\tisOccupied: "); 
	Serial.print(isOccupied); 

	Serial.print("\tcycleCount: "); 
	Serial.println(cycleCount); 
}

void printConfig() {
	Serial.println("==> Configuration"); 
	Serial.print("gatePin: "); 
	Serial.println(gatePin); 
	Serial.print("redPin: "); 
	Serial.println(redPin); 
	Serial.print("yellowPin: "); 
	Serial.println(yellowPin); 
	Serial.print("redPin: "); 
	Serial.println(redPin); 
	Serial.print("statusPin: "); 
	Serial.print(statusPin); 
	Serial.print(", enabled: "); 
	Serial.println(enableStatus); 

	Serial.print("cycleInterval (ms): "); 
	Serial.println(cycleInterval); 
	Serial.print("hysteresis (cycles): "); 
	Serial.println(hysteresis); 
	Serial.print("changeLightDelay (ms): "); 
	Serial.println(changeLightDelay); 
	Serial.print("interruptedState: "); 
	Serial.println(interruptedState); 
	Serial.print("ledHIGH: "); 
	Serial.print(ledHIGH); 
	Serial.print(", ledLOW: "); 
	Serial.println(ledLOW); 

	Serial.println("\n === Start obervation now === \n"); 
}

void setup() {
	Serial.begin(9600); 

	printConfig(); 
	
	pinMode(redPin, OUTPUT); 
	pinMode(yellowPin, OUTPUT); 
	pinMode(greenPin, OUTPUT); 
	pinMode(statusPin, OUTPUT); 

	pinMode(gatePin, INPUT); 
}

void reset() {
	digitalWrite(redPin, ledLOW); 
	digitalWrite(yellowPin, ledLOW); 
	digitalWrite(greenPin, ledLOW); 
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

	digitalWrite(greenPin, ledHIGH); 
	delay(changeLightDelay); 
	digitalWrite(greenPin, ledLOW); 
	delay(changeLightDelay); 
	digitalWrite(greenPin, ledHIGH); 
	delay(changeLightDelay); 
	digitalWrite(greenPin, ledLOW); 
	digitalWrite(yellowPin, ledHIGH); 
	delay(changeLightDelay); 
	digitalWrite(yellowPin, ledLOW); 
	digitalWrite(redPin, ledHIGH); 
}

void runLeaveSequence() {
	reset(); 

	digitalWrite(redPin, ledHIGH); 
	delay(changeLightDelay); 
	digitalWrite(yellowPin, ledHIGH); 
	delay(changeLightDelay); 
	digitalWrite(redPin, ledLOW); 
	digitalWrite(yellowPin, ledLOW); 
	digitalWrite(greenPin, ledHIGH); 

	delay(turnOffDelay); 
	reset(); 
}

void triggerStatus() {
	if(!enableStatus) 
		return; 

	digitalWrite(statusPin, HIGH); 
	delay(100); 
	digitalWrite(statusPin, LOW); 
}

void loop() {
	readGateSensor(); 
	printStatus(); 

	if(someoneEntered && !isOccupied) {
		isOccupied = true; 
		Serial.println("\n==> Running enter sequence\n"); 
		runEnterSequence(); 
	}

	if(!someoneEntered && isOccupied) {
		isOccupied = false; 
		Serial.println("\n==> Running leave sequence\n"); 
		runLeaveSequence(); 
	}
	
	triggerStatus(); 
	delay(cycleInterval); 
}

