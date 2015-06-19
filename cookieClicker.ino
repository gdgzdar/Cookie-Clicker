#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte cookieBtn = 6;                  // pin tlačítka pro počítání cookies
byte currentStateCookieBtn;          // aktuální stav tlačítka pro počítání cookies
byte lastStateCookieBtn = 0;         // minulý stav tlačítka pro počítání cookies
byte multiplierBtn = 7;              // pin tlačítka pro násobič přičítané hodnoty
byte currentStateMultiplierBtn = 0;  // aktuální stav tlačítka pro násobič přičítané hodnoty
byte lastStateMultiplierBtn = 0;     // minulý stav tlačítka pro násobič přičítané hodnoty

byte shopFarmBtn = 15;
byte currentStateShopFarmBtn; 
byte lastStateShopFarmBtn = 0;

byte shopFactoryBtn = 16;
byte currentStateShopFactoryBtn; 
byte lastStateShopFactoryBtn = 0;

byte shopMineBtn = 17;
byte currentStateShopMineBtn; 
byte lastStateShopMineBtn = 0;

byte shopClonerBtn = 18;
byte currentStateShopClonerBtn; 
byte lastStateShopClonerBtn = 0;

unsigned long cookiesQuantity =  0;                              // celkový počet cookies
long increment = 1;                                              // přičítaná hodnota
int priceOfMultiplier[] = {10,20,30,40,50,250,600,9999999};      // cena násobiče cookies
byte counterMultiplierBuy = 0;                                   // kolikrát koupeno

long priceFarm = 100;
byte percentageRaiseFarm = 10;
int addFarm = 5;

long priceFactory = 500;
byte percentageRaiseFactory = 15;
int addFactory = 15;

long priceMine = 5000;
byte percentageRaiseMine = 35;
int addMine = 30;

long priceCloner = 10000;
byte percentageRaiseCloner = 50;
int addCloner = 100;

byte diodeMultiplierG = 42;
byte diodeMultiplierR = 43;

byte diodeFarmG = 44;
byte diodeFarmR = 45;

byte diodeFactoryG = 46;
byte diodeFactoryR = 47;

byte diodeMineG = 48;
byte diodeMineR = 49;

byte diodeClonerG = 50;
byte diodeClonerR = 51;

String infoMsg;
unsigned long msgDelay = 0;

long perSecondAdd = 0;
long lastSecond;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();     
  pinMode(cookieBtn, INPUT);
  pinMode(multiplierBtn, INPUT);    
  pinMode(shopFarmBtn, INPUT);    
  pinMode(shopFactoryBtn, INPUT);   
  pinMode(shopMineBtn, INPUT);   
  pinMode(shopClonerBtn, INPUT);   
  
  pinMode(diodeMultiplierG, OUTPUT);
  pinMode(diodeMultiplierR, OUTPUT);
  pinMode(diodeFarmG, OUTPUT);
  pinMode(diodeFarmR, OUTPUT);
  pinMode(diodeFactoryG, OUTPUT);
  pinMode(diodeFactoryR, OUTPUT);
  pinMode(diodeMineG, OUTPUT);
  pinMode(diodeMineR, OUTPUT);
  pinMode(diodeClonerG, OUTPUT);
  pinMode(diodeClonerR, OUTPUT);  
  
  digitalWrite(diodeMultiplierG, 1);
  digitalWrite(diodeMultiplierR, 0);
  digitalWrite(diodeFarmG, 1);
  digitalWrite(diodeFarmR, 0);
  digitalWrite(diodeFactoryG, 1);
  digitalWrite(diodeFactoryR, 0);
  digitalWrite(diodeMineG, 1);
  digitalWrite(diodeMineR, 0);
  lastSecond = millis();
  infoMsg = String("Cookies");
}

boolean enoughCookies(unsigned long price){
  if (price > cookiesQuantity)  
  {
//    infoMsg = String("Malo cookies");
    msgDelay = millis() + 2000;
    return false;
  }
  else
  {
    return true;
  }
}

void shopStatus() {
  if (enoughCookies(priceOfMultiplier[counterMultiplierBuy]))
  {
    digitalWrite(diodeMultiplierG, 1);
    digitalWrite(diodeMultiplierR, 0);
  }
  else
  {
    digitalWrite(diodeMultiplierG, 0);
    digitalWrite(diodeMultiplierR, 1);
  }
  
  
  if (enoughCookies(priceFarm))
  {
    digitalWrite(diodeFarmG, 1);
    digitalWrite(diodeFarmR, 0);
  }
  else
  {
    digitalWrite(diodeFarmG, 0);
    digitalWrite(diodeFarmR, 1);
  }
  
  
  if (enoughCookies(priceFactory))
  {
    digitalWrite(diodeFactoryG, 1);
    digitalWrite(diodeFactoryR, 0);
  }
  else
  {
    digitalWrite(diodeFactoryG, 0);
    digitalWrite(diodeFactoryR, 1);
  }  
  
  if (enoughCookies(priceMine))
  {
    digitalWrite(diodeMineG, 1);
    digitalWrite(diodeMineR, 0);
  }
  else
  {
    digitalWrite(diodeMineG, 0);
    digitalWrite(diodeMineR, 1);
  }
  
  if (enoughCookies(priceCloner))
  {
    digitalWrite(diodeClonerG, 1);
    digitalWrite(diodeClonerR, 0);
  }
  else
  {
    digitalWrite(diodeClonerG, 0);
    digitalWrite(diodeClonerR, 1);
  }  
  
}

long shopEngine(long price, byte raise, int add){
  long newPrice;
	if (enoughCookies(price))  
	{
	  perSecondAdd += add;
          newPrice = price + (price*raise/100);
//          infoMsg = String(newPrice);
          msgDelay = millis() + 2000;
          cookiesQuantity -= price;
	  return newPrice;
        }
	else
	{
	  return price;
	}
}


void loop() {
  
  currentStateCookieBtn = digitalRead(cookieBtn);
  currentStateMultiplierBtn = digitalRead(multiplierBtn);
  currentStateShopFarmBtn = digitalRead(shopFarmBtn);
  currentStateShopFactoryBtn = digitalRead(shopFactoryBtn);
  currentStateShopMineBtn = digitalRead(shopMineBtn);
  currentStateShopClonerBtn = digitalRead(shopClonerBtn);
  
  shopStatus();
    
  if(currentStateCookieBtn == 1 && lastStateCookieBtn == 0)
  {
    cookiesQuantity += increment;
    lastStateCookieBtn = 1;
  }
  else if (currentStateCookieBtn == 0 && lastStateCookieBtn == 1) lastStateCookieBtn = 0;
  
  if(currentStateMultiplierBtn == 1 && lastStateMultiplierBtn == 0)
  {  
    enoughCookies(priceOfMultiplier[counterMultiplierBuy]);
    if(cookiesQuantity >= priceOfMultiplier[counterMultiplierBuy])
    {
      increment *= 2;
      cookiesQuantity -= priceOfMultiplier[counterMultiplierBuy];         
      counterMultiplierBuy++;
    }
    lastStateMultiplierBtn = 1;
  }
  else if (currentStateMultiplierBtn == 0 && lastStateMultiplierBtn == 1) lastStateMultiplierBtn = 0;
  
  // Tlačítko 1------------------------------------------------------------------------------------
  
  if(currentStateShopFarmBtn == 1 && lastStateShopFarmBtn == 0)
  {   
      priceFarm = shopEngine(priceFarm, percentageRaiseFarm, addFarm); 
      lastStateShopFarmBtn = 1;
  }
  else if (currentStateShopFarmBtn == 0 && lastStateShopFarmBtn == 1) lastStateShopFarmBtn = 0;
  
  // Tlačítko 2------------------------------------------------------------------------------------
  
  if(currentStateShopFactoryBtn == 1 && lastStateShopFactoryBtn == 0)
  {  
    priceFactory = shopEngine(priceFactory, percentageRaiseFactory, addFactory); 
    lastStateShopFactoryBtn = 1;
  }
  else if (currentStateShopFactoryBtn == 0 && lastStateShopFactoryBtn == 1) lastStateShopFactoryBtn = 0;

  // Tlačítko 3------------------------------------------------------------------------------------
  
  if(currentStateShopMineBtn == 1 && lastStateShopMineBtn == 0)
  {  
    priceMine = shopEngine(priceMine, percentageRaiseMine, addMine); 
    lastStateShopMineBtn = 1;
  }
  else if (currentStateShopMineBtn == 0 && lastStateShopMineBtn == 1) lastStateShopMineBtn = 0;
  
    // Tlačítko 4------------------------------------------------------------------------------------
  
  if(currentStateShopClonerBtn == 1 && lastStateShopClonerBtn == 0)
  {  
    priceCloner = shopEngine(priceCloner, percentageRaiseCloner, addCloner); 
    lastStateShopClonerBtn = 1;
  }
  else if (currentStateShopClonerBtn == 0 && lastStateShopClonerBtn == 1) lastStateShopClonerBtn = 0;


  

if((millis() - lastSecond) > 1000) 
{
  lastSecond = millis();
  cookiesQuantity += perSecondAdd;
}
  
  delay(30);
  lcd.clear();     
  lcd.setCursor(0, 0);
  if (msgDelay < millis())
  {
    infoMsg = String("Cookies");    
  }
  lcd.print(infoMsg);
  lcd.setCursor(0, 1);
  lcd.print(cookiesQuantity);

}

