#include <SoftwareSerial.h>

#define SensorSol 11
#define SensorOrta 12
#define SensorSag 13

#define MotorR1 6
#define MotorR2 7 
#define MotorRE 9

#define MotorL1 5
#define MotorL2 4
#define MotorLE 3

#define buzzer 10
char data;
char state;
int delaysuresi = 0;
int hiz = 50;
int gerihiz = 50;
int donushiz=90;
int sol,sag,orta;
int uzundelay = 0;
int nerede = 0;
int sayac = 0;
int beyazsayac = 0;
int trigPin = 8;
int echoPin = 2;
long sure;
long uzaklik;
int ilerigeri=0;
int az = 1;
int durum = 0;
String veri = "";
int buzzerPin = 10;
int notaSayisi = 8;
int C = 262;
int D = 294;
int E = 330;
int F = 349;
int G = 392;
int A = 440;
int B = 494;
int C_ = 523;
int notalar[] = {C, D, E, F, G, A, B, C_};
SoftwareSerial bt_iletisim(0, 1);
void setup() {
  
  pinMode(SensorSol, INPUT);
  pinMode(SensorOrta, INPUT);
  pinMode(SensorSag, INPUT);

  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);

  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  
  pinMode(MotorRE, OUTPUT);
  pinMode(MotorLE, OUTPUT);

  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT); /* trig pini çıkış olarak ayarlandı */
  pinMode(echoPin,INPUT); /* echo pini giriş olarak ayarlandı */
  bt_iletisim.begin(9600);
  Serial.begin(9600);
  analogWrite(MotorRE, hiz);
  analogWrite(MotorLE, hiz);
  //digitalWrite(MotorR1, HIGH); // Sağ aktif
  //digitalWrite(MotorL1, HIGH); // Sol aktif

}
int sagdeger(){
  
  return digitalRead(SensorSag);
}
int soldeger(){
  
  return digitalRead(SensorSol);
}
int ortadeger(){
  
  return digitalRead(SensorOrta);
}


void loop() {
veri = "";
 if (bt_iletisim.available())
  {
    data = bt_iletisim.read();
    Serial.println(data);
    veri = veri + data;
} 

  
    if(data == 'B'){
      Serial.println("BASLIYORRRR");
        durum = 1;
          for (int i = 0; i < 5; i++)
  {
            tone(buzzerPin, notalar[i]);
            delay(450);
            noTone(buzzerPin);
            delay(150);
  }
  noTone(buzzerPin);
      }else if(data == 'D'){
        Serial.println("DURDUK");
        durum = 0;
        }
       else if(data == 'Y'){
          Serial.println("Uzaktan Kontrol Modu");
          durum = 2;
          }
    
 
  

  //Serial.print("Uzaklik: ");  
  //Serial.print(uzaklik); /* hesaplanan uzaklık bilgisayara aktarılıyor */
  //Serial.println(" CM olarak olculmustur.");  
  //delay(100);
    if(durum == 0){
        dur();
        ilerigeri = 0;
      }else if(durum == 1){ 
    digitalWrite(trigPin, LOW); /* sensör pasif hale getirildi */
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH); /* Sensore ses dalgasının üretmesi için emir verildi */
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    sure = pulseIn(echoPin, HIGH); /* ses dalgasının geri dönmesi için geçen sure ölçülüyor */
    uzaklik= sure /29.1/2; /* ölçülen sure uzaklığa çevriliyor */    
    if(uzaklik > 1){
        if(uzaklik < 30){
          
              dur();
          delay(100);
          }else{
              sol = digitalRead(SensorSol);
              sag = digitalRead(SensorSag);
              orta = digitalRead(SensorOrta);
              //Serial.print("SOL: ");
              //Serial.print(sol);
              //Serial.print("  ORTA: ");
              //Serial.print(orta);
              //Serial.print("  SAG: ");
              //Serial.println(sag);
              
          
              if(sol == 1 && orta == 1 && sag == 1){ //Hepsi siyah görürse
                if(nerede!=1){
                  nerede = 1;
                  analogWrite(MotorLE, 0); 
                  analogWrite(MotorRE, 0); 
                  delay(uzundelay);
                }
              duz();
            }   
            
            if(sol == 1 && orta == 1 && sag == 0){  // sol ve orta çizgiyi görürse
              if(nerede!=2){
                  nerede = 2;
                  analogWrite(MotorLE, 0); 
                  analogWrite(MotorRE, 0); 
                  delay(uzundelay);
                }
              soladon();
              
            }
            else if(sol == 0 && orta == 1 && sag == 1){  // Sağ sensör çizgiyi gördüğünde robot sağa dönsün.
              if(nerede!=3){
                  nerede = 3;
                  analogWrite(MotorLE, 0); 
                  analogWrite(MotorRE, 0); 
                  delay(uzundelay);
                } 
             sagadon();
          
            }
            else if(sol == 1 && orta == 0 && sag == 0){  // Sol sensör çizgiyi gördüğünde robot sağa dönsün.
            if(nerede!=4){
                  nerede = 4;
                  analogWrite(MotorLE, 0); 
                  analogWrite(MotorRE, 0); 
                  delay(uzundelay);
                }
              soladon();
            }
            else if(sol == 0 && orta == 1 && sag == 0){  // Orta sensör çizgiyi gördüğünde robot sağa dönsün.
              if(nerede!=5){
                  nerede = 5;
                  analogWrite(MotorLE, 0); 
                  analogWrite(MotorRE, 0); 
                  delay(uzundelay);
                }
              duz();
              
            }
            else if(sol == 0 && orta == 0 && sag == 1){  // Sağ sensör çizgiyi gördüğünde robot sağa dönsün.
              
              if(nerede!=6){
                  nerede = 6;
                  analogWrite(MotorLE, 0); 
                  analogWrite(MotorRE, 0); 
                  delay(uzundelay);
                }
              sagadon();
            }else if(sol == 1 && orta == 0 && sag == 1){  /// Sağ sensör çizgiyi gördüğünde robot sağa dönsün.
              
              if(nerede!=7){
                  nerede = 7;
                  analogWrite(MotorLE, 0); 
                  analogWrite(MotorRE, 0); 
                  delay(uzundelay);
                }
              soladon();
            }else{
              if(nerede == 5){
                ilerigeri=ilerigeri+1;
                }
              if(nerede!=8){
                  sayac = sayac + 1;
                  nerede = 8;
                  analogWrite(MotorLE, 0); 
                  analogWrite(MotorRE, 0); 
                  delay(uzundelay);
                }
                sayac = sayac + 1;
                
               if(ilerigeri>6){
                duz();
                } else{
              geri();
                }
                  
                  }
              }
            
            }
      }else if(durum == 2){
          if(data == '1'){
            duz();
            delay(20);
            }else if(data == '2'){
              geri();
              delay(20);
              }else if(data == '3'){
                  sagadon();
                  delay(20);
                }else if(data == '4'){
                  soladon();
                  delay(20);
                  }else if(data == '5'){
                      dur();
                    }
                  else{
                    dur();
                    }
        }
}


 
void soladon(){

    analogWrite(MotorLE, 0); 
    digitalWrite(MotorL2, LOW);
    digitalWrite(MotorR2, LOW);
    digitalWrite(MotorL1, LOW);
    digitalWrite(MotorR1, HIGH);
    analogWrite(MotorRE, donushiz); 
    if(ilerigeri > 5){
        ilerigeri = 0;
      }
}

void sagadon(){

    analogWrite(MotorRE, 0); 
    digitalWrite(MotorL2, LOW);
    digitalWrite(MotorR2, LOW);
    digitalWrite(MotorR1, LOW);
    digitalWrite(MotorL1, HIGH);
    analogWrite(MotorLE, donushiz); 
    if(ilerigeri > 5){
        ilerigeri = 0;
      }
}

void duz(){

    digitalWrite(MotorL2, LOW);
    digitalWrite(MotorR2, LOW);
    digitalWrite(MotorR1, HIGH);
    digitalWrite(MotorL1, HIGH);
    analogWrite(MotorLE, hiz); 
    analogWrite(MotorRE, hiz); 
    
}

void dur(){
  digitalWrite(MotorR1, LOW);
    digitalWrite(MotorL1, LOW);
    analogWrite(MotorLE, 0); 
    analogWrite(MotorRE, 0); 
  }

void geri(){

  
      digitalWrite(MotorR1, LOW);
    digitalWrite(MotorL1, LOW);
    
  digitalWrite(MotorR2, HIGH);
    digitalWrite(MotorL2, HIGH);
    analogWrite(MotorLE, gerihiz); 
    analogWrite(MotorRE, gerihiz); 
  }

  
