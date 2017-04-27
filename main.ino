const int Motor1Pin1 = 2; const int Motor1Pin2 = 3;
const int Motor2Pin1 = 4; const int Motor2Pin2 = 5;
const int Motor3Pin1 = 6; const int Motor3Pin2 = 7;
const int Motor4Pin1 = 8; const int Motor4Pin2 = 9; 
char state = 's'; 

void setup() {
  pinMode(Motor1Pin1, OUTPUT);
  pinMode(Motor1Pin2, OUTPUT);
  pinMode(Motor2Pin1, OUTPUT);
  pinMode(Motor2Pin2, OUTPUT);
  pinMode(Motor3Pin1, OUTPUT);
  pinMode(Motor3Pin2, OUTPUT);
  pinMode(Motor4Pin1, OUTPUT);
  pinMode(Motor4Pin2, OUTPUT);
  Serial.begin(9600);
} 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             

void loop() {
  if(Serial.available()>0){
    state = Serial.read();
  } 
  if(state == 'f'){
    GoForward();
  } 
  if(state == 'b'){
   GoBackward(); 
  } 
  if(state == 'r'){
    GoRight();
  } 
  if(state == 'l'){
    GoLeft();
  } 
  if(state == 's'){
    Stop();
  } 
}


void GoForward() {
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, HIGH);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, HIGH);
  digitalWrite(Motor3Pin1, HIGH);
  digitalWrite(Motor3Pin2, LOW);
  digitalWrite(Motor4Pin1, HIGH);
  digitalWrite(Motor4Pin2, LOW);
}

void GoBackward() {
  digitalWrite(Motor1Pin1, HIGH);
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor2Pin1, HIGH);
  digitalWrite(Motor2Pin2, LOW);
  digitalWrite(Motor3Pin1, LOW);
  digitalWrite(Motor3Pin2, HIGH);
  digitalWrite(Motor4Pin1, LOW);
  digitalWrite(Motor4Pin2, HIGH);
}

void GoLeft() {
  digitalWrite(Motor1Pin1, HIGH);
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, HIGH);
  digitalWrite(Motor3Pin1, HIGH);
  digitalWrite(Motor3Pin2, LOW);
  digitalWrite(Motor4Pin1, LOW);
  digitalWrite(Motor4Pin2, HIGH);
}

void GoRight() {
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, HIGH);
  digitalWrite(Motor2Pin1, HIGH);
  digitalWrite(Motor2Pin2, LOW);
  digitalWrite(Motor3Pin1, LOW);
  digitalWrite(Motor3Pin2, HIGH);
  digitalWrite(Motor4Pin1, HIGH);
  digitalWrite(Motor4Pin2, LOW);
}

void Stop() {
  digitalWrite(Motor1Pin1, LOW);
  digitalWrite(Motor1Pin2, LOW);
  digitalWrite(Motor2Pin1, LOW);
  digitalWrite(Motor2Pin2, LOW);
  digitalWrite(Motor3Pin1, LOW);
  digitalWrite(Motor3Pin2, LOW);
  digitalWrite(Motor4Pin1, LOW);
  digitalWrite(Motor4Pin2, LOW);
}
