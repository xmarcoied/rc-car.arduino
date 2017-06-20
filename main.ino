  #include <Keypad.h>
  #include <NewPing.h>
  
  // Motor-base related
  const int Motor1Pin1 = 2;  const int Motor1Pin2 = 3;
  const int Motor2Pin1 = 4;  const int Motor2Pin2 = 5;
  const int Motor3Pin1 = 6;  const int Motor3Pin2 = 7;
  const int Motor4Pin1 = 8;  const int Motor4Pin2 = 9; 
  char state = 's';
  char * msg = "Marco";
  int config1 = 0 ; int config2 = 0 ;
  int config3 = 0 ; int config4 = 0 ;
  int config5 = 0 ; int config6 = 0 ;
  int config7 = 0 ; int config8 = 0 ;
  int config9 = 0 ; int config10 = 0 ;
  
  // Keypad related
  const byte ROWS = 4; 
  const byte COLS = 4; 
  char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
  };
  byte rowPins[ROWS] = {A5, A4, A3, A2}; //connect to the row pinouts of the keypad
  byte colPins[COLS] = {A9, A8, A7, A6}; //connect to the column pinouts of the keypad
  Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

  // Flame-sensor related
  // lowest and highest sensor readings:
  const int sensorMin = 0;     // sensor minimum
  const int sensorMax = 1024;  // sensor maximum
  
  // Sound related
  int soundDetectedPin = 10; // Use Pin 10 as our Input
  int soundDetectedVal = HIGH; // This is where we record our Sound Measurement
  boolean bAlarm = false;
  unsigned long lastSoundDetectTime; // Record the time that we measured a sound
  int soundAlarmTime = 500; // Number of milli seconds to keep the sound alarm high

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

    // Sound related
    pinMode (soundDetectedPin, INPUT) ; // input from the Sound Detection Module
  } 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
  void loop() {
    delay(50);
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
    if(state == '1'){
      config1 = toggle(config1);
      showoff("Password" , config1);
    }
    if(state == '2'){
      config2 = toggle(config2);
      showoff("Flame Sensor" , config2);
    }
    if(state == '3'){
      config3 = toggle(config3);
      showoff("Sound" , config3);
    }
    if(state == '4'){
      config4 = toggle(config4);
      showoff("" , config4);
    }
    if(state == '5'){
      config5 = toggle(config5);
      showoff("" , config5);
    }
    if(state == '6'){
      config6 = toggle(config6);
      showoff("" , config6);
    }

    if(state == '7'){
      config7 = toggle(config7);
      showoff("" , config7);
    }

    if(state == '8'){
      config8 = toggle(config8);
      showoff("" , config8);
    }
    // Conf1 == Keypad and password
    if(config1 == 1){
      conf1();
    }
    if(config2 == 1){
      conf2();
    }
  }
  
  int toggle(int var){
    if(var == 0) return 1 ;
    if(var == 1) return 0 ;
  }
  void showoff(char* c , int var){
    if(var == 0){
      Serial.print(c);
      Serial.println(" is off");
    }
    else {
      Serial.print(c);
      Serial.println(" is on");
    }
  }

  // config1 == Keypad and password
  void conf1(){
    char key = keypad.getKey();
    if(key)
      Serial.println(key);
  }

  void conf2(){
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
  }

  void conf3(){
    soundDetectedVal = digitalRead (soundDetectedPin) ; // read the sound alarm time
    // If we hear a sound
    if (soundDetectedVal == LOW){
        lastSoundDetectTime = millis(); // record the time of the sound alarm
        // The following is so you don't scroll on the output screen
        if (!bAlarm){
          Serial.println("LOUD, LOUD");
          bAlarm = true;
        }
    }
    else{
      if( (millis()-lastSoundDetectTime) > soundAlarmTime  &&  bAlarm){
        Serial.println("quiet");
        bAlarm = false;
      }
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
    digitalWrite(Motor3Pin1, LOW);
    digitalWrite(Motor3Pin2, HIGH);
    digitalWrite(Motor4Pin1, HIGH);
    digitalWrite(Motor4Pin2, LOW);
  }
  
  void GoRight() {
    digitalWrite(Motor1Pin1, LOW);
    digitalWrite(Motor1Pin2, HIGH);
    digitalWrite(Motor2Pin1, HIGH);
    digitalWrite(Motor2Pin2, LOW);
    digitalWrite(Motor3Pin1, HIGH);
    digitalWrite(Motor3Pin2, LOW);
    digitalWrite(Motor4Pin1, LOW);
    digitalWrite(Motor4Pin2, HIGH);
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