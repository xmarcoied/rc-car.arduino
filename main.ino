#include <NewPing.h>

// Ultrasonic related 
#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 450 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// Base Motors  
int pso1 = 22  ; int pso2 = 24  ; int psos = 2 ; //pso=pin shemal odam  .. psos pin shemal odam speed (pwm to control speed).. (let 1 be forwards  direction and 2 backwards direction )
int psw1 = 26  ; int psw2 = 28  ; int psws = 3 ; //pin shemal wara
int pyo1 = 30  ; int pyo2 = 32  ; int pyos = 4 ; //pin yemen odam
int pyw1 = 34  ; int pyw2 = 36  ; int pyws = 5 ; // pin yemen wara
int irs;

// Sound related
int soundDetectedPin = 10; // Use Pin 10 as our Input
int soundDetectedVal = HIGH; // This is where we record our Sound Measurement
boolean bAlarm = false;
unsigned long lastSoundDetectTime; // Record the time that we measured a sound


// Flame-sensor related
// lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

// Mangetic-sensor related 
const int switchPin = 2;

void setup() {
  Serial.begin(115200);
  // Motor pins
  pinMode (pso1, OUTPUT); pinMode (pso2, OUTPUT);
  pinMode (psw1, OUTPUT); pinMode(psw2, OUTPUT);
  pinMode (pyo1, OUTPUT); pinMode(pyo2, OUTPUT);
  pinMode (pyw1, OUTPUT); pinMode(pyw2, OUTPUT);
  pinMode (52  ,  INPUT); pinMode (13  , OUTPUT);

  // Sound related
  pinMode (soundDetectedPin, INPUT) ; // input from the Sound Detection Module
  // Magnetic-sensor related
  pinMode(switchPin, INPUT);
}
//1,0,1,0 backwards >> 0,1,0,1 forwards
//shemal odam,shemal wara,yemen odam ,yemen wara speed
void speedcontrol ( int pwm1, int pwm2, int pwm3 , int pwm4) {
    analogWrite ( psos, pwm1); analogWrite (psws , pwm2);
    analogWrite (pyos, pwm3) ; analogWrite (pyws, pwm4);
}
//front backwards,front forwards,back backwards , back forwards
void leftwheels (int dir01, int dir02, int dirw1 , int dirw2 ) {
  digitalWrite (pso1, dir01); digitalWrite (pso2, dir02);
  digitalWrite (psw1, dirw1) ; digitalWrite (psw2, dirw2);
}
void rightwheels ( int dir01, int dir02 , int dirw1 , int dirw2) {
  digitalWrite(pyo1, dir01); digitalWrite(pyo2, dir02);
  digitalWrite (pyw1, dirw1); digitalWrite(pyw2, dirw2);
}

void fastforward (){
  speedcontrol(255, 255, 255, 255); leftwheels(0, 1, 0, 1);
  rightwheels (0, 1, 0, 1);
}
void forward (){
  speedcontrol (128, 128, 128, 128);
  leftwheels(0, 1, 0, 1);
  rightwheels(0, 1, 0, 1);
}
void fastbackwards (){
  speedcontrol(255, 255, 255, 255) ;
  leftwheels(1, 0, 1, 0);
  rightwheels(1, 0, 1, 0);
}
void backwards (){
  speedcontrol(128, 128, 128, 128);
  leftwheels(1, 0, 1, 0);
  rightwheels(1, 0, 1, 0);
}
void rightwards (){
  speedcontrol (255, 255, 255, 255);
  leftwheels(0, 1, 0, 1); rightwheels(1, 0, 1, 0);
}
void leftwards(){
  speedcontrol(255, 255, 255, 255);
  leftwheels(1, 0, 1, 0);
  rightwheels(0, 1, 0, 1);
}

void STOP (){
  speedcontrol(0, 0, 0, 0);
}
void slowrightwards(){
  speedcontrol (200, 200, 200, 200);
  leftwheels(0, 1, 0, 1); rightwheels(1, 0, 1, 0);
}




void loop() {
  // Mangetic-sensor related
  if(digitalRead(switchPin) == LOW){
   	digitalWrite(ledPin, LOW);
   }
  else{
	digitalWrite(ledPin, HIGH);
  }
  delay(1000);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  int foo = sonar.ping_cm();
  if(foo < 10){
    STOP();
    delay(5000);
  }
  // read the sensor on analog A0:
  int sensorReading = analogRead(A0);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  // range value:
  switch (range) {
    case 0:    // A fire closer than 1.5 feet away.
      Serial.println("** Close Fire **");
      break;
    case 1:    // A fire between 1-3 feet away.
      Serial.println("** Distant Fire **");
      break;
    case 2:    // No fire detected.
      Serial.println("No Fire");
      break;
  }
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  { char  blut = Serial.read() ;
    if (blut != 'S') {
      if (blut == 'F') fastforward() ;
      else if (blut == 'f') forward();
      else if (blut == 'B') fastbackwards();
      else if (blut == 'b') backwards();
      else if (blut == 'R') rightwards();
      else if (blut == 'L') leftwards();
      else STOP() ;
    }
  }

 // Sound realted fn
  soundDetectedVal = digitalRead (soundDetectedPin) ; // read the sound alarm time
  
  if (soundDetectedVal == LOW) // If we hear a sound
  {
  
    lastSoundDetectTime = millis(); // record the time of the sound alarm
    // The following is so you don't scroll on the output screen
    if (!bAlarm){
      Serial.println("LOUD, LOUD");
      bAlarm = true;
    }
  }
  else
  {
    if( (millis()-lastSoundDetectTime) > soundAlarmTime  &&  bAlarm){
      Serial.println("quiet");
      bAlarm = false;
    }
  }

 // -------------------
 irs = digitalRead(52)  ;
  if(irs==LOW) {
   STOP();
   delay(2000);
  } 
}
