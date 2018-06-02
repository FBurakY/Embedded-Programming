#define ag_ismi "Bla_Bla"
#define ag_sifresi "bambambamx"

//Fonksiyon Prototipleri
void yesilYak();
void maviYak();
void kirmiziYak();
void ledSondur();
void motorDurdur();
void Okunan();

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

void setup()
{ 

    //Donanım input-output çıkışları ayarlandı ...
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
  
    Serial.begin(115200); //Seriport'u açıyoruz. Güncellediğimiz 
                          //ESP modülünün baudRate değeri 115200 olduğu için bizde Seriport'u 115200 şeklinde seçiyoruz
    Serial.println("AT"); //ESP modülümüz ile bağlantı kurulup kurulmadığını kontrol ediyoruz.
    pinMode(13,OUTPUT);
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
    if(Serial.find("+IPD,")){
      String metin = "<head> Yigido Robot Sunar </head>";
      
      metin += "<br><a href=\" ?pin=xleft\"><button type='button'>X-Sol</button></a>"; //X-Ekseni Sola Tetik Butonu
      metin += "<br><a href=\" ?pin=xrigt\"><button type='button'>X-Sag</button></a>"; //X-Ekseni Sağa Tetik Butonu

      metin += "<br><a href=\" ?pin=yup\"><button type='button'>Y-Yukarı</button></a>"; //Y-Ekseni Yukarı Tetik Butonu
      metin += "<br><a href=\" ?pin=ydown\"><button type='button'>Y-Asagi</button></a>";//Y-Ekseni Aşağı Tetik Butonu   

      metin += "<br><a href=\" ?pin=znext\"><button type='button'>Z-İleri</button></a>"; //Z-Ekseni Ileri Tetik Butonu
      metin += "<br><a href=\" ?pin=zback\"><button type='button'>Z-Geri</button></a>";  //Z-Ekseni Geri Tetik Butonu

      metin += "<br><a href=\" ?pin=stp\"><button type='button'>STOP</button></a>";  //Eksenleri Durdur Butonu
         
      String cipsend = "AT+CIPSEND=";
      cipsend +="0";
      cipsend +=",";
      cipsend += metin.length();
      cipsend += "\r\n";
      Serial.print(cipsend);
      delay(500);
      Serial.println(metin);
      Okunan();
      Serial.println("AT+CIPCLOSE=0");
      
    }
  }
}

void Okunan(){
 String gelen ="";
 char serialdenokunan;
 
   while(Serial.available()>0){    
        serialdenokunan = Serial.read();
        gelen +=serialdenokunan;
        // 0,5KHz ses sinyali gönderiliyor
        tone(buzzer, 1000); 
        // 0,3 sn bekleme
        delay(300); 
        // ses sinyalini durdur
        noTone(buzzer);
        // 0,3 sn bekleme 
        delay(300);
        // 0,5KHz ses sinyali gönderiliyor
        tone(buzzer, 1000);    
   }
   Serial.println(gelen);
 
 //X-Ekseni Sağa
 if((gelen.indexOf(":GET /?pin=xrigt")>1)){   //X-Sağ butonuna basıldığında server adresinde /?pin=xrigt var ise
        digitalWrite(dirPinX,LOW);            //X-Ekseni Hareket Eder
        digitalWrite(stepPinX,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPinX,LOW);
        delayMicroseconds(500);
        yesilYak();                                          
 }
 //X-Ekseni Sola
  if((gelen.indexOf(":GET /?pin=xleft")>1)){  //X-Sol butonuna basıldığında server adresinde /?pin=xl var ise
        digitalWrite(dirPinX,HIGH);           //X-Ekseni Hareket Eder
        digitalWrite(stepPinX,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(stepPinX,LOW); 
        delayMicroseconds(500); 
        yesilYak();                       
 }
 //Y-Ekseni Yukari
 if((gelen.indexOf(":GET /?pin=yup")>1)){     // Y-Yukarı butonuna basıldığında server adresinde /?pin=yup var ise
        digitalWrite(dirPinY,LOW);            //Y-Ekseni Hareket Eder
        digitalWrite(stepPinY,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPinY,LOW);
        delayMicroseconds(500);
        maviYak();  
 }
 //Y-Ekseni Asagi
 if((gelen.indexOf(":GET /?pin=ydown")>1)){  //Y-Asagi butonuna basıldığında server adresinde /?pin=ydown var ise
        digitalWrite(dirPinY,HIGH);          //Y-Ekseni Hareket Eder
        digitalWrite(stepPinY,HIGH); 
        delayMicroseconds(500); 
        digitalWrite(stepPinY,LOW); 
        delayMicroseconds(500); 
        maviYak();
 }
 //Z-Ekseni İleri
 if((gelen.indexOf(":GET /?pin=znext")>1)){ // Z-Ileri butonuna basıldığında server adresinde /?pin=znext var ise
        digitalWrite(dirPinZ,HIGH); 
        digitalWrite(stepPinZ,HIGH);  
        delayMicroseconds(4000); 
        digitalWrite(stepPinZ,LOW); 
        delayMicroseconds(4000); 
        kirmiziYak();                   
 }
 //Z-Ekseni Geri
 if((gelen.indexOf(":GET /?pin=zback")>1)){ // Z-Geri butonuna basıldığında server adresinde /?pin=zback var ise
        digitalWrite(dirPinZ,LOW); 
        digitalWrite(stepPinZ,HIGH);
        delayMicroseconds(4000);
        digitalWrite(stepPinZ,LOW);
        delayMicroseconds(4000);
        kirmiziYak();
 }
 //Motor - Dur
 if((gelen.indexOf(":GET /?pin=stp")>1)){ // Stop butonuna basıldığında server adresinde /?pin=stp var ise
       motorDurdur();
       ledSondur();
       noTone(buzzer);
 }
 
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
