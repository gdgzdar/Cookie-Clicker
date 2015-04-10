#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte cookieBtn = 6;                  // pin tlačítka pro počítání cookies
byte currentStateCookieBtn;          // aktuální stav tlačítka pro počítání cookies
byte lastStateCookieBtn = 0;         // minulý stav tlačítka pro počítání cookies
byte multiplierBtn = 7;              // pin tlačítka pro násobič přičítané hodnoty
byte currentStateMultiplierBtn = 0;  // aktuální stav tlačítka pro násobič přičítané hodnoty
byte lastStateMultiplierBtn = 0;     // minulý stav tlačítka pro násobič přičítané hodnoty
unsigned long cookiesQuantity =  0;  // celkový počet cookies
long increment = 1;                  // přičítaná hodnota
int priceOfMultiplier = 30;          // cena násobiče cookies

void setup() {
  lcd.begin(16, 2);
  lcd.clear();     
  pinMode(cookieBtn, INPUT);
  pinMode(multiplierBtn, INPUT);    
}

void loop() {
  
  currentStateCookieBtn = digitalRead(cookieBtn);
  currentStateMultiplierBtn = digitalRead(multiplierBtn);
  
  if(currentStateCookieBtn == 1 && lastStateCookieBtn == 0){
    cookiesQuantity += increment;
    lastStateCookieBtn = 1;
  }
  else if (currentStateCookieBtn == 0 && lastStateCookieBtn == 1)     lastStateCookieBtn = 0;
  
  if(currentStateMultiplierBtn == 1 && lastStateMultiplierBtn == 0){  
    if(cookiesQuantity >= priceOfMultiplier){
      increment *= 2;
      cookiesQuantity -= priceOfMultiplier;         
      priceOfMultiplier *= 2;
    }
    lastStateMultiplierBtn = 1;
  }
  else if (currentStateMultiplierBtn == 0 && lastStateMultiplierBtn == 1) lastStateMultiplierBtn = 0;
  
  
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


