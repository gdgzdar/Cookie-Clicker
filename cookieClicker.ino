#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte cookieBtn = 6;                  // pin tlačítka pro počítání cookies
byte lastStateCookieBtn = 0;         // minulý stav tlačítka pro počítání cookies
byte multiplierBtn = 7;              // pin tlačítka pro násobič přičítané hodnoty
byte lastStateMultiplierBtn = 0;     // minulý stav tlačítka pro násobič přičítané hodnoty
unsigned long cookiesQuantity =  0;  // celkový počet cookies
long increment = 1;                  // přičítaná hodnota

void setup() {
  lcd.begin(16, 2);
  lcd.clear();     
  pinMode(cookieBtn, INPUT);
  pinMode(multiplierBtn, INPUT);    
  }

void loop() {
  if(digitalRead(cookieBtn) == 1 && lastStateCookieBtn == 0){
    cookiesQuantity += increment;
    lastStateCookieBtn = 1;
  }
  else if (digitalRead(cookieBtn) == 0 && lastStateCookieBtn == 1)     lastStateCookieBtn = 0;
  
  if(digitalRead(multiplierBtn) == 1 && lastStateMultiplierBtn == 0){  
    if(cookiesQuantity > 29){
      increment *= 2;
      cookiesQuantity -= 30;         
    }
    lastStateMultiplierBtn = 1;
  }
  else if (digitalRead(multiplierBtn) == 0 && lastStateMultiplierBtn == 1) lastStateMultiplierBtn = 0;
  
  
  delay(50);
  lcd.clear();     
  lcd.setCursor(0, 0);
  lcd.print("Cookies");
  lcd.setCursor(11, 0);
  lcd.print(increment);
  lcd.setCursor(10, 0);
  lcd.print("x");  
  lcd.setCursor(0, 1);
  lcd.print(cookiesQuantity);
}


