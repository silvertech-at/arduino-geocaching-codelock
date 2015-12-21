// Passwort
int PasswortArray[4] = {1,2,3,4};

// Zwischenablage der gedrückten Tasten
int ZifferEins = 0;
int ZifferZwei = 0;
int ZifferDrei = 0;
int ZifferVier = 0;

// Taster definieren
int TasterOK = A0;
int TasterEins = A1;
int TasterZwei = A2;
int TasterDrei = A3;
int TasterVier = A4;

// LED's definieren
int LEDblau = 10;
int LEDzu = 8;
int LEDgelb = 7;
int LEDoffen = 9;

// Display
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Sonstiges
int AutomatischZusperrenNach = 5;


//============================================================
void setup() {

// Festlegen der Ein und Ausgänge
pinMode(TasterOK,INPUT);
pinMode(TasterEins,INPUT);
pinMode(TasterZwei,INPUT);
pinMode(TasterDrei,INPUT);
pinMode(TasterVier,INPUT);
pinMode(LEDblau,OUTPUT);
pinMode(LEDoffen,OUTPUT);
pinMode(LEDzu,OUTPUT);
pinMode(LEDgelb,OUTPUT);

// Display
lcd.begin(16, 2);

// Zusperren
digitalWrite(LEDzu,HIGH);
}

//============================================================
void loop() {
  if (digitalRead(LEDzu) == HIGH && digitalRead(LEDoffen) == LOW){
    lcd.clear();
    lcd.print("Code eingeben");
    Zahleneingabe();
    }
  
  // LEDgelb leuchtet nach Zahleneingabe um öffnen zu bestätigen
  digitalWrite(LEDgelb,HIGH);
  
  do{
    if(digitalRead(TasterOK) == HIGH) //wurde öffnen gedrückt?
      {
        if((PasswortArray[0] == ZifferEins) && (PasswortArray[1] == ZifferZwei) && (PasswortArray[2] == ZifferDrei) && (PasswortArray[3] == ZifferVier))
          { // Code stimmt - gehe zu Funktion Aufsperren
          Aufsperren();
          break;
          }
        else
          { // Code ist falsch - gehe zu Funktion CodeFalsch
          CodeFalsch();
          break;
          }          
        }
    }while(1);
}

//============================================================
void Zahleneingabe() {
  for(int i = 1; i < 5; i++){
    do
    {
      delay(50);
    }while((digitalRead(TasterEins) == LOW) && (digitalRead(TasterZwei) == LOW) &&(digitalRead(TasterDrei) == LOW) && (digitalRead(TasterVier) == LOW));
    
      digitalWrite(LEDgelb,LOW);
      if(digitalRead(TasterEins) == HIGH){
        ZifferEins = i;
        LEDblauBlinken();
        delay(100);
        }
      else if(digitalRead(TasterZwei) == HIGH){
        ZifferZwei = i;
        LEDblauBlinken();
        delay(100);
        }
      else if(digitalRead(TasterDrei) == HIGH){
        ZifferDrei = i;
        LEDblauBlinken();
        delay(100);
        }
      else if(digitalRead(TasterVier) == HIGH){
        ZifferVier = i;
        LEDblauBlinken();
        delay(100);
        }
    }
    lcd.clear();
    lcd.print("Code eingegeben");
    lcd.setCursor(0, 1);
    lcd.print("OK bestaetigen");
}

//============================================================
void LEDblauBlinken() {
  digitalWrite(LEDblau,HIGH);
  delay(100);
  digitalWrite(LEDblau,LOW);
}

//============================================================
void Aufsperren() {
  lcd.clear();
  lcd.print("Code ist richtig");
  lcd.setCursor(0, 1);
  lcd.print("Oeffne Dose");
  digitalWrite(LEDzu,LOW);
  digitalWrite(LEDoffen,HIGH);
  digitalWrite(LEDgelb,LOW);
  
  AutomatischZusperren();
  
  digitalWrite(LEDoffen,LOW);
  digitalWrite(LEDzu,HIGH);
}

//============================================================
void CodeFalsch() {
  lcd.clear();
  lcd.print("Code falsch");
  lcd.setCursor(0, 1);
  lcd.print("Schade :-(");
  int Blink = 0;
     do
      {
        Blink = Blink + 1;
        digitalWrite(LEDgelb, HIGH);
        delay(500);
        digitalWrite(LEDgelb, LOW);
        delay(500);
      } while (Blink < AutomatischZusperrenNach);
}

//============================================================
void AutomatischZusperren() {
  int Blink = 0;
      do
      {
        Blink = Blink + 1;
        digitalWrite(LEDblau, HIGH);
        delay(500);
        digitalWrite(LEDblau, LOW);
        delay(500);
      }while (Blink < AutomatischZusperrenNach);
}
