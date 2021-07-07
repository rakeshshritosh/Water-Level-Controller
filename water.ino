//Rakesh Bisu(19CH10034) & Sanjay Bisu(20MI10047)
//"REMOTE MONITORING AND CONTROL OF WATER LEVEL IN A TANK"
#define vccPin 8 //The pins of sensor are connected to consecutive pins on arduino for efficient space management & integration
#define trigPin 9
#define echoPin 10
#define gndPin 11
#define relay_gnd 12
const int H=31; //here the height of the water tank is entered
const int h_max=25; //here the maximum water level beyond which pump should be switched off is entered
const int h_min=8; //here the minimum water level below which pump should be switched on is entered
long duration; // variable for the duration of sound wave travel
int distance; // distance of water level from sensor
int water_level; // height of water level from bottom of tank
void setup() {
// put your setup code here, to run once:
pinMode(trigPin, OUTPUT);
pinMode(vccPin, OUTPUT);
pinMode(gndPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(12,OUTPUT);
pinMode(13,OUTPUT);
Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
Serial.println("THIS IS THE MESSAGE TO BE DISPLAYED WHEN SERIAL MONITOR OPENS");
//HOWEVER IN THIS PARTICULAR PROJECT WE INTEND TO USE NODE-RED AS USER INTERFACE NOT THE ARDUINO IDE SERIAL MONITOR
}
void loop() {
digitalWrite(relay_gnd,LOW);
digitalWrite(vccPin, HIGH);
digitalWrite(gndPin, LOW);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10); // Sets trigPin HIGH (ACTIVE) for 10 microseconds
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH); // Reads the echoPin. Returns the sound wave travel time in microseconds
// Calculating the distance
distance = ((duration * 0.034 / 2)+2); // Speed of sound wave divided by 2 (go and back).
//Here speed of sound is taken as 340 m/s.
//Please note that our HCSR04 sensor was having some error in measurement, we had to add 2 to correct it
// Calculating water level
water_level=(H-distance);
//Instructions as to when the pump should remain ON/OFF
if(water_level>=h_max){
digitalWrite(13,LOW);
}
else if(water_level<h_min){
digitalWrite(13,HIGH);
}
//Data to be transferred to the computer via serial port. It will be displayed in Node-Red dashboard
Serial.print(water_level);
Serial.print(", ");
Serial.println(digitalRead(13)); //digital state of pin 13 indicates whether the pump is on or off
delay(2000);
}
