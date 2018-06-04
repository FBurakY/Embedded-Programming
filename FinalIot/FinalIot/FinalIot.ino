/* Servo kutuphanesi projeye dahil edildi */
#include <Servo.h>  
#define ag_ismi "WifiAraniyor"
#define ag_sifresi "20162024BT"

// defines pins numbers
const int buzzer = 53; //buzzer pin 53 a bağlı
const int stepPinX = 2; //step motor için step ve dir pin bağlantıları
const int dirPinX = 5;
const int stepPinY = 3; 
const int dirPinY = 6;
const int stepPinZ = 4; 
const int dirPinZ = 7; 
int kirmizi=24;//led pinleri 24,26 ve 28. pinlere bağlı.
int yesil=26;
int mavi=28;
int yon;//yön değişkenmiz

//Fonksiyon Prototipleri
void Ses();
void yesilYak();
void maviYak();
void kirmiziYak();
void motorDurdur();
void ledSondur();
void setup()
{
 
  Serial.begin(115200); //Seriport'u açıyoruz. Güncellediğimiz 
                        //ESP modülünün baudRate değeri 115200 olduğu için bizde Seriport'u 115200 şeklinde seçiyoruz
  Serial.println("AT"); //ESP modülümüz ile bağlantı kurulup kurulmadığını kontrol ediyoruz.
  pinMode(kirmizi, OUTPUT);
  pinMode(yesil, OUTPUT);
  pinMode(mavi, OUTPUT); 
  digitalWrite(kirmizi, LOW);
  digitalWrite(yesil, LOW); 
  digitalWrite(mavi, LOW);
  pinMode(buzzer, OUTPUT); // Pin 30 çıkış olarak ayarlandı
  pinMode(stepPinX,OUTPUT); 
  pinMode(dirPinX,OUTPUT);
  pinMode(stepPinY,OUTPUT); 
  pinMode(dirPinY,OUTPUT);
  pinMode(stepPinZ,OUTPUT); 
  pinMode(dirPinZ,OUTPUT);
  digitalWrite(stepPinX, LOW);
  digitalWrite(dirPinX, LOW);
  digitalWrite(stepPinY, LOW);
  digitalWrite(dirPinY, LOW);
  digitalWrite(stepPinZ, LOW);
  digitalWrite(dirPinZ, LOW);
  delay(3000); //ESP ile iletişim için 3 saniye bekliyoruz.
 
  if(Serial.find("OK")){         //esp modülü ile bağlantıyı kurabilmişsek modül "AT" komutuna "OK" komutu ile geri dönüş yapıyor.
     Serial.println("AT+CWMODE=1"); //esp modülümüzün WiFi modunu STA şekline getiriyoruz. Bu mod ile modülümüz başka ağlara bağlanabilecek.
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
    Serial.println(baglantiKomutu);
     delay(5000);
 }
 
   Serial.print("AT+CIPMUX=1\r\n");
   delay(200);
   Serial.print("AT+CIPSERVER=1,80\r\n");   
   delay(1000);
}
void loop(){

  if(Serial.available()>0){
    Serial.print("AT+CIFSR\r\n");
    if(Serial.find("+IPD,")){

      //String metin = "<head> Yigido Robot Sunar </head>";
      
      //metin += "<br><a href=\" ?pin=xleft\"><button type='button'>X-Sol</button></a>"; //X-Ekseni Sola Tetik Butonu
      //metin += "<br><a href=\" ?pin=xrigt\"><button type='button'>X-Sag</button></a>"; //X-Ekseni Sağa Tetik Butonu

      //metin += "<br><a href=\" ?pin=yup\"><button type='button'>Y-Yukarı</button></a>"; //Y-Ekseni Yukarı Tetik Butonu
      //metin += "<br><a href=\" ?pin=ydown\"><button type='button'>Y-Asagi</button></a>";//Y-Ekseni Aşağı Tetik Butonu   

      // metin += "<br><a href=\" ?pin=znext\"><button type='button'>Z-İleri</button></a>"; //Z-Ekseni Ileri Tetik Butonu
      //metin += "<br><a href=\" ?pin=zback\"><button type='button'>Z-Geri</button></a>";  //Z-Ekseni Geri Tetik Butonu

      //metin += "<br><a href=\" ?pin=stp\"><button type='button'>STOP</button></a>";  //Eksenleri Durdur Butonu
         
      
      String cipsend = "AT+CIPSEND=";
      cipsend +="0";
      cipsend +=",";
      cipsend +=9500;
      cipsend += "\r\n";
      Serial.print(cipsend);
      delay(1);      
      motor_kontrol();
      Serial.println("AT+CIPCLOSE=0");
      
    }
  }
}


void motor_kontrol(){
 String gelen ="";
 char serialdenokunan;
 
 while(Serial.available()>0){
   serialdenokunan = Serial.read();
   gelen += serialdenokunan;     
 } 

 Serial.println("\tWhile Ciktim\n");
 Serial.println("\tGET : \t"+gelen);
 //X-Ekseni Sol
 if((gelen.indexOf(":GET /?1sol")>1)){
  for(int i=0 ; i<=10 ;i++){ 
    digitalWrite(dirPinX,HIGH); 
    digitalWrite(stepPinX,HIGH); 
    delayMicroseconds(2000); 
    digitalWrite(stepPinX,LOW); 
    delayMicroseconds(2000); 
    Ses();
    yesilYak();
  }
      motorDurdur();
      ledSondur();
      noTone(buzzer); 
 }
    
 //X-Ekseni Dur
 if(gelen.indexOf(":GET /?1dur")>1){  
      motorDurdur();
      ledSondur();
      noTone(buzzer);  
 }
 //X-Ekseni Sag
  if(gelen.indexOf(":GET /?1sag")>1){
   for(int i=0 ; i<=10 ;i++){ 
    digitalWrite(dirPinX,LOW); 
    digitalWrite(stepPinX,HIGH);
    delayMicroseconds(100);
    digitalWrite(stepPinX,LOW);
    delayMicroseconds(100);
    Ses();
    yesilYak();
   }
      motorDurdur();
      ledSondur();
      noTone(buzzer); 
  }  
 
 //Y-Ekseni Yukarı
 if(gelen.indexOf(":GET /?2sol")>1){ 
  for(int i=0 ; i<=10 ;i++){ 
    digitalWrite(dirPinY,LOW);
    digitalWrite(stepPinY,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPinY,LOW);
    delayMicroseconds(500);
    Ses();
    maviYak();
  }
      motorDurdur();
      ledSondur();
      noTone(buzzer); 
 }
 //Y-Ekseni Dur
 if(gelen.indexOf(":GET /?2dur")>1){  
      motorDurdur();
      ledSondur();
      noTone(buzzer);  
 }
 //Y-Ekseni Asagi
  if(gelen.indexOf(":GET /?2sag")>1){
   for(int i=0 ; i<=5 ;i++){ 
    digitalWrite(dirPinY,HIGH); 
    digitalWrite(stepPinY,HIGH); 
    delayMicroseconds(500); 
    digitalWrite(stepPinY,LOW); 
    delayMicroseconds(500); 
    Ses();
    maviYak();    
   }
      motorDurdur();
      ledSondur();
      noTone(buzzer); 
  }
 //Z-Ekseni Ileri
  if((gelen.indexOf(":GET /?3sol")>1)){
    for(int i =0; i<=5 ; i++){
      
    digitalWrite(dirPinZ,HIGH); 
    digitalWrite(stepPinZ,HIGH);  
    delayMicroseconds(4000); 
    digitalWrite(stepPinZ,LOW); 
    delayMicroseconds(4000); 
    kirmiziYak(); 
 }  
      motorDurdur();
      ledSondur();
      noTone(buzzer);
}     

 //Z-Ekseni Dur
 if((gelen.indexOf(":GET /?3dur")>1)){  
      motorDurdur();
      ledSondur();
      noTone(buzzer);
 }
  //Z-Ekseni Geri
  if((gelen.indexOf(":GET /?3sag")>1)){
   for(int i=0 ; i<=5 ; i++){  
          digitalWrite(dirPinZ,LOW); 
          digitalWrite(stepPinZ,HIGH);
          delayMicroseconds(4000);
          digitalWrite(stepPinZ,LOW);
          delayMicroseconds(4000);
          kirmiziYak(); 
          }
            motorDurdur();
            ledSondur();
            noTone(buzzer); 
        }   
}         

    void Ses(){
      tone(buzzer, 1000); // 0,5KHz ses sinyali gönderiliyor
      delay(300); // 0,3 sn bekleme
      noTone(buzzer); // ses sinyalini durdur
      delay(300); // 0,3 sn bekleme
      tone(buzzer, 1000); // 0,5KHz ses sinyali gönderiliyor 
      yesilYak(); 
    }
  
     void yesilYak(){
    digitalWrite(yesil, HIGH); 
    digitalWrite(kirmizi, LOW); 
    digitalWrite(mavi, LOW); 
      }
    void maviYak(){
    digitalWrite(yesil, LOW); 
    digitalWrite(kirmizi, LOW); 
    digitalWrite(mavi, HIGH); 
      }
    void kirmiziYak(){
    digitalWrite(yesil, LOW); 
    digitalWrite(kirmizi, HIGH); 
    digitalWrite(mavi, LOW); 
      }
    void ledSondur(){
    digitalWrite(yesil, LOW); 
    digitalWrite(kirmizi, LOW); 
    digitalWrite(mavi, LOW); 
      }
    void motorDurdur(){
    digitalWrite(stepPinX, LOW);
    digitalWrite(dirPinX, LOW);
    digitalWrite(stepPinY, LOW);
    digitalWrite(dirPinY, LOW);
    digitalWrite(stepPinZ, LOW);
    digitalWrite(dirPinZ, LOW);
    }
