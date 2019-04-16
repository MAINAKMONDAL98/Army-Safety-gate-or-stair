#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int a;
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.noBacklight();//To Power ON the back light
  pinMode(A0,INPUT);
  pinMode(8,OUTPUT);

}
void loop() 
{a = analogRead(A0);
Serial.println(a);
if(a>=500){
  delay(1000);
  String content= "1";

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {Serial.println(content);
  delay(500);
    if ((content == "1")&&(a>=500)) //change here the UID of the card/cards that you want to give access
  { lcd.backlight();
    Serial.println("Denied access");
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print("     ENEMIES"); //You can write 16 Characters per line .
    delay(2000);//Delay used to give a dynamic effect
    lcd.setCursor(0,1);  //Defining positon to write from second row,first column .
    lcd.print("      ALART");
    delay(8000); 

lcd.clear();//Clean the screen
    Serial.println();
    delay(300);
    lcd.noBacklight();
    digitalWrite(8,1);
    delay(100);
    digitalWrite(8,0);
  }
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  //String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if ((content.substring(1) == "9B F5 73 0E" ||"9B 58 91 0D")&&(a>=500)) //change here the UID of the card/cards that you want to give access
  { lcd.backlight();
    Serial.println("Authorized access");
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print("  INDIAN ARMY "); //You can write 16 Characters per line .
    delay(2000);//Delay used to give a dynamic effect
    lcd.setCursor(0,1);  //Defining positon to write from second row,first column .
    lcd.print("   JAI HIND");
    delay(8000); 

lcd.clear();//Clean the screen
    Serial.println();
    delay(300);
    lcd.noBacklight();
  }
}
 
 else   {
    Serial.println(" Access denied");
    delay(200);
  }

} 
