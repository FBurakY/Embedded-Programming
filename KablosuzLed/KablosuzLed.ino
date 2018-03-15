int data;
//Yeşil
int ledY=7;
 

void setup() { 

pinMode(ledY,OUTPUT);

Serial.begin(9600);  

}

void loop() {

  if(Serial.available()){

    int data=Serial.read();
    delay(100);
      if(data =='1'){digitalWrite(ledY,1);}     
           
      if(data =='0'){digitalWrite(ledY,0);}
      delay(100);
  }  
}
