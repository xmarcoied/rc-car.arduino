int pso1=22 ; int pso2=24  ;int psos =2  ;//pso=pin shemal odam  .. psos pin shemal odam speed (pwm to control speed).. (let 1 be forwards  direction and 2 backwards direction )
int psw1=26  ; int psw2 =28  ;int psws =3 ;  //pin shemal wara 
int pyo1 =30 ; int pyo2 =32 ; int pyos  =4   ; //pin yemen odam 
int pyw1=34  ;int pyw2=36   ; int pyws =5 ; // pin yemen wara 
int irs = HIGH ; int irsc=0;



void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode (pso1,OUTPUT);pinMode (pso2,OUTPUT);
  pinMode (psw1,OUTPUT);pinMode(psw2,OUTPUT);
  pinMode (pyo1 ,OUTPUT);pinMode(pyo2,OUTPUT);
  pinMode(pyw1,OUTPUT);pinMode(pyw2,OUTPUT);
  pinMode (52,INPUT); 
  pinMode(13,OUTPUT);

}
 //1,0,1,0 backwards >> 0,1,0,1 forwards 
void speedcontrol ( int pwm1,int pwm2,int pwm3 ,int pwm4)//shemal odam,shemal wara,yemen odam ,yemen wara speed 
{  analogWrite ( psos,pwm1);analogWrite (psws ,pwm2);
analogWrite (pyos,pwm3) ;analogWrite (pyws,pwm4);}
void leftwheels (int dir01,int dir02,int dirw1 ,int dirw2 ) //front backwards,front forwards,back backwards , back forwards
{ digitalWrite (pso1,dir01); digitalWrite (pso2,dir02);
digitalWrite (psw1,dirw1) ; digitalWrite (psw2,dirw2);}
void rightwheels ( int dir01,int dir02 ,int dirw1 ,int dirw2) { 
  digitalWrite(pyo1,dir01); digitalWrite(pyo2,dir02);
  digitalWrite (pyw1,dirw1); digitalWrite(pyw2,dirw2);}

void fastforward ()
{ speedcontrol(255,255,255,255);leftwheels(0,1,0,1);
rightwheels (0,1,0,1);}
void forward ()
{ speedcontrol (128,128,128,128); leftwheels(0,1,0,1); rightwheels(0,1,0,1);}
void fastbackwards ()
{ speedcontrol(255,255,255,255) ; leftwheels(1,0,1,0); rightwheels(1,0,1,0);}
void backwards ()
{ speedcontrol(128,128,128,128);leftwheels(1,0,1,0); rightwheels(1,0,1,0);}
void rightwards ()
{ speedcontrol (255,255,255,255);
leftwheels(0,1,0,1); rightwheels(1,0,1,0);}
void leftwards()
{ speedcontrol(255,255,255,255); leftwheels(1,0,1,0); rightwheels(0,1,0,1);}

void STOP () 
{ speedcontrol(0,0,0,0);}
void slowrightwards() 
{  speedcontrol (200,200,200,200);
leftwheels(0,1,0,1); rightwheels(1,0,1,0);

}




void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0)
 { char  blut = Serial.read() ;
  if (blut != 'S') { 
    if (blut=='F') fastforward() ;
    else if (blut =='f') forward();
    else if (blut=='B') fastbackwards();
    else if (blut=='b') backwards();
    else if (blut=='R') rightwards();
    else if (blut=='L') leftwards();
    else STOP() ;}
 }
 
 irs = digitalRead (52);
 if (irs== LOW)  irsc++;
  else irsc=0;
 Serial.println(irsc);
 
//if (irsc==5) { slowrightwards();delay(1000);fastforward(); irsc=0;}
 
 
 
 
 
 
 
 }
      
    
    
    
    
    
    
    
    
    
