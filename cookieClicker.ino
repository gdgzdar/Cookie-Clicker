#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte cookieBtn = 6;                  // pin tlačítka pro počítání cookies
byte currentStateCookieBtn;          // aktuální stav tlačítka pro počítání cookies
byte lastStateCookieBtn = 0;         // minulý stav tlačítka pro počítání cookies
byte multiplierBtn = 7;              // pin tlačítka pro násobič přičítané hodnoty
byte currentStateMultiplierBtn = 0;  // aktuální stav tlačítka pro násobič přičítané hodnoty
byte lastStateMultiplierBtn = 0;     // minulý stav tlačítka pro násobič přičítané hodnoty

byte shopBtn1 = 15;
byte currentStateShopBtn1; 
byte lastStateShopBtn1 = 0;

byte shopBtn2 = 16;
byte currentStateShopBtn2; 
byte lastStateShopBtn2 = 0;

byte shopBtn3 = 17;
byte currentStateShopBtn3; 
byte lastStateShopBtn3 = 0;

byte shopBtn4 = 18;
byte currentStateShopBtn4; 
byte lastStateShopBtn4 = 0;

unsigned long cookiesQuantity =  0;  // celkový počet cookies
long increment = 1;                  // přičítaná hodnota
int priceOfMultiplier[] = {10,20,30,40,50,250,600,9999999};          // cena násobiče cookies
byte counterMultiplierBuy = 0;       // kolikrát koupeno
String infoMsg;                      // zprava
unsigned long msgDelay = 0;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();     
  pinMode(cookieBtn, INPUT);
  pinMode(multiplierBtn, INPUT);    
  pinMode(shopBtn1, INPUT);    
  pinMode(shopBtn2, INPUT);   
  pinMode(shopBtn3, INPUT);   
  pinMode(shopBtn4, INPUT);   
  infoMsg = String("Cookies");
}

void enoughCookies(unsigned long price){
   if (price > cookiesQuantity)  {
    infoMsg = String("Malo cookies");
    msgDelay = millis() + 2000;
    }
}


void loop() {
  
  currentStateCookieBtn = digitalRead(cookieBtn);
  currentStateMultiplierBtn = digitalRead(multiplierBtn);
  currentStateShopBtn1 = digitalRead(shopBtn1);
  currentStateShopBtn2 = digitalRead(shopBtn2);
  currentStateShopBtn3 = digitalRead(shopBtn3);
  currentStateShopBtn4 = digitalRead(shopBtn4);
  
  
  if(currentStateCookieBtn == 1 && lastStateCookieBtn == 0){
    cookiesQuantity += increment;
    lastStateCookieBtn = 1;
  }
  else if (currentStateCookieBtn == 0 && lastStateCookieBtn == 1)     lastStateCookieBtn = 0;
  
  if(currentStateMultiplierBtn == 1 && lastStateMultiplierBtn == 0){  
    enoughCookies(priceOfMultiplier[counterMultiplierBuy]);
    if(cookiesQuantity >= priceOfMultiplier[counterMultiplierBuy]){
      increment *= 2;
      cookiesQuantity -= priceOfMultiplier[counterMultiplierBuy];         
      counterMultiplierBuy++;
    }
    lastStateMultiplierBtn = 1;
  }
  else if (currentStateMultiplierBtn == 0 && lastStateMultiplierBtn == 1) lastStateMultiplierBtn = 0;
  
  // Tlačítko 1------------------------------------------------------------------------------------
  
  if(currentStateShopBtn1 == 1 && lastStateShopBtn1 == 0){  
    enoughCookies(priceOfMultiplier[counterMultiplierBuy]);
    if(cookiesQuantity >= priceOfMultiplier[counterMultiplierBuy]){
      increment *= 2;
      cookiesQuantity -= priceOfMultiplier[counterMultiplierBuy];         
      counterMultiplierBuy++;
    }
    lastStateShopBtn1 = 1;
  }
  else if (currentStateShopBtn1 == 0 && lastStateShopBtn1 == 1) lastStateShopBtn1 = 0;
  
  // Tlačítko 2------------------------------------------------------------------------------------
  
  if(currentStateShopBtn2 == 1 && lastStateShopBtn2 == 0){  
    enoughCookies(priceOfMultiplier[counterMultiplierBuy]);
    if(cookiesQuantity >= priceOfMultiplier[counterMultiplierBuy]){
      increment *= 2;
      cookiesQuantity -= priceOfMultiplier[counterMultiplierBuy];         
      counterMultiplierBuy++;
    }
    lastStateShopBtn2 = 1;
  }
  else if (currentStateShopBtn2 == 0 && lastStateShopBtn2 == 1) lastStateShopBtn2 = 0;

  // Tlačítko 3------------------------------------------------------------------------------------
  
  if(currentStateShopBtn3 == 1 && lastStateShopBtn3 == 0){  
    enoughCookies(priceOfMultiplier[counterMultiplierBuy]);
    if(cookiesQuantity >= priceOfMultiplier[counterMultiplierBuy]){
      increment *= 2;
      cookiesQuantity -= priceOfMultiplier[counterMultiplierBuy];         
      counterMultiplierBuy++;
    }
    lastStateShopBtn3 = 1;
  }
  else if (currentStateShopBtn3 == 0 && lastStateShopBtn3 == 1) lastStateShopBtn3 = 0;
  
    // Tlačítko 4------------------------------------------------------------------------------------
  
  if(currentStateShopBtn4 == 1 && lastStateShopBtn4 == 0){  
    enoughCookies(priceOfMultiplier[counterMultiplierBuy]);
    if(cookiesQuantity >= priceOfMultiplier[counterMultiplierBuy]){
      increment *= 2;
      cookiesQuantity -= priceOfMultiplier[counterMultiplierBuy];         
      counterMultiplierBuy++;
    }
    lastStateShopBtn4 = 1;
  }
  else if (currentStateShopBtn4 == 0 && lastStateShopBtn4 == 1) lastStateShopBtn4 = 0;
  
  delay(50);
  lcd.clear();     
  lcd.setCursor(0, 0);
  if (msgDelay < millis() ) {    infoMsg = String("Cookies");    }
  lcd.print(infoMsg);
  lcd.setCursor(0, 1);
  lcd.print(cookiesQuantity);
}


