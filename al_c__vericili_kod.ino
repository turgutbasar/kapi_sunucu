#include <RCSwitch.h>
#include <EEPROM.h> /* EEPROM fonksiyonları için kütüphane dahil edilmelidir. */
RCSwitch mySwitch = RCSwitch();
long kayitAdresi ;
long kayitAdresi1 ;
long kayitAdresi2 ;
long kayitAdresi3 ; 
long okunacakAdres;
long okunacakAdres1;
long okunacakAdres2;
long okunacakAdres3;
long code;
long code1;
long decoded;
long kaydedilecekVeri;
long kaydedilecekVeri1;
long kaydedilecekVeri2;
long kaydedilecekVeri3;
long payload[4];
long bytes[4];

void setup() {
  pinMode(23, INPUT); //kayıt modu
  EEPROM.begin(64);
  Serial.begin(9600);
  mySwitch.enableTransmit(10);
 mySwitch.setPulseLength(504);
  mySwitch.setRepeatTransmit(30);
  mySwitch.enableReceive(2);  // Receiver input on interrupt 0 (D2)
 
}

void loop() 
{
 if(digitalRead(23)==0){
mySwitch.getReceivedValue();
mySwitch.getReceivedBitlength();
Serial.println("kayıt modu ");
if (mySwitch.available()) {
code =  mySwitch.getReceivedValue();
//Serial.println( mySwitch.getReceivedValue());
Serial.println( code );
//Serial.println( mySwitch.getReceivedBitlength());
byte payload[4];
payload[0] = (byte) ((code & 0xFF000000) >> 24 );
payload[1] = (byte) ((code & 0x00FF0000) >> 16 );
payload[2] = (byte) ((code & 0x0000FF00) >> 8  );
payload[3] = (byte) ((code & 0X000000FF)       );

kayitAdresi = 1; /* Verinin yazılacağı EEPROM adresi */ 
kayitAdresi1 = 2;
kayitAdresi2 = 3;
kayitAdresi3 = 4;

Serial.println( payload[3] );
Serial.println( payload[2] );
Serial.println( payload[1] );
Serial.println( payload[0] );

 kaydedilecekVeri = payload[0]; /* EEPROMA kaydedilecek veri */
 EEPROM.write(kayitAdresi, kaydedilecekVeri);
  EEPROM.commit();
 kaydedilecekVeri1 = payload[1]; /* EEPROMA kaydedilecek veri */
 EEPROM.write(kayitAdresi1, kaydedilecekVeri1);
  EEPROM.commit();
 kaydedilecekVeri2 = payload[2]; /* EEPROMA kaydedilecek veri */
 EEPROM.write(kayitAdresi2, kaydedilecekVeri2);
  EEPROM.commit();
 kaydedilecekVeri3 = payload[3]; /* EEPROMA kaydedilecek veri */
 EEPROM.write(kayitAdresi3, kaydedilecekVeri3);
  EEPROM.commit();
 delay(1000);
}
delay(100);
}
else {
 okunacakAdres = 1; // 10 adresini okuyacağız
 bytes[0] = EEPROM.read(okunacakAdres );
 okunacakAdres1 = 2; // 10 adresini okuyacağız
 bytes[1] = EEPROM.read(okunacakAdres1 );
 okunacakAdres2 = 3; // 10 adresini okuyacağız
 bytes[2] = EEPROM.read(okunacakAdres2 );
 okunacakAdres3 = 4; // 10 adresini okuyacağız
 bytes[3] = EEPROM.read(okunacakAdres3 );
 code1 = ((long)(bytes[0]) << 24)
              + ((long)(bytes[1]) << 16)
              + ((long)(bytes[2]) << 8)
              + ((long)(bytes[3]));


 //mySwitch.send(code1, 24);
 Serial.println( code1 );
 
 Serial.println("kayıt modu degil ");
  Serial.println( bytes[3] );
Serial.println( bytes[2] );
Serial.println( bytes[1] );
Serial.println( bytes[0] );
delay(1000);
}
}
