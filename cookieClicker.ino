#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Nastaveni pinů pro vstupy a výstupy a inicializace pomocných proměnných

//  Tlačítko a proměnné požívané pro tlačítka pro přičítání cookies 
byte cookieBtn = 6;                  // pin tlačítka pro počítání cookies
byte currentStateCookieBtn;          // proměnná, do které ukádáme aktuální stav tlačítka pro počítání cookies 
byte lastStateCookieBtn = 0;         // proměnná, kam si ukládáme minulý stav tlačítka pro počítání cookies

// Tlačítko násobič cookies
byte multiplierBtn = 7;              
byte currentStateMultiplierBtn = 0;  
byte lastStateMultiplierBtn = 0;     

// Položky obchodu
// Cookie Farm
byte shopFarmBtn = 15;
byte currentStateShopFarmBtn; 
byte lastStateShopFarmBtn = 0;

// Cookie factory
byte shopFactoryBtn = 16;
byte currentStateShopFactoryBtn; 
byte lastStateShopFactoryBtn = 0;

// Cookie Mine
byte shopMineBtn = 17;
byte currentStateShopMineBtn; 
byte lastStateShopMineBtn = 0;

// Cookie clooner
byte shopClonerBtn = 18;
byte currentStateShopClonerBtn; 
byte lastStateShopClonerBtn = 0;


// Nastavení proměnných
unsigned long cookiesQuantity =  0;                              // celkový počet cookies
long increment = 1;                                              // přičítaná hodnota
int priceOfMultiplier[] = {10,20,30,40,50,250,600,9999999};      // cena násobiče cookies
byte counterMultiplierBuy = 0;                                   // kolikrát koupeno

// Nastavení položek proměnných
long priceFarm = 100;             // počáteční cena na koupení položky
byte percentageRaiseFarm = 10;    // o kolik procent se zvýší cena položky po koupení
int addFarm = 5;                  // kolik cookies za sekundu se bude přičítat

long priceFactory = 500;
byte percentageRaiseFactory = 15;
int addFactory = 15;

long priceMine = 5000;
byte percentageRaiseMine = 35;
int addMine = 30;

long priceCloner = 10000;
byte percentageRaiseCloner = 50;
int addCloner = 100;

// Nastavení výstupů pro barevné LED, které zobrazují, zda položku obchodu lze nebo nelze koupit
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

// Nastavení pomocných zpráv
String infoMsg;
unsigned long msgDelay = 0;

// Nastavení pro automatické přičítání cookies každou sekundu
long perSecondAdd = 0;
long lastSecond;

void setup() {
  // inicializace displaye
  lcd.begin(16, 2);                           
  lcd.clear();     
  // inicializace pinů pro vstupy z tlačítek
  pinMode(cookieBtn, INPUT);
  pinMode(multiplierBtn, INPUT);    
  pinMode(shopFarmBtn, INPUT);    
  pinMode(shopFactoryBtn, INPUT);   
  pinMode(shopMineBtn, INPUT);   
  pinMode(shopClonerBtn, INPUT);   
  // inicializace pinů pro výstupy na LEDky
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

  // rozsvícení LEDek
  digitalWrite(diodeMultiplierG, 1);
  digitalWrite(diodeMultiplierR, 0);
  digitalWrite(diodeFarmG, 1);
  digitalWrite(diodeFarmR, 0);
  digitalWrite(diodeFactoryG, 1);
  digitalWrite(diodeFactoryR, 0);
  digitalWrite(diodeMineG, 1);
  digitalWrite(diodeMineR, 0);
  lastSecond = millis();            // uložíme si aktuální počet ms od začátku běhu Arduina
  infoMsg = String("Cookies");
}


// Funkce pro zjištění, zda mohu položku obchodu koupit
// Přijímá hodnotu ceny, za kterou se dá položka koupit a porovná ji s hodnoutou celkového množství cookies
boolean enoughCookies(unsigned long price){
  if (price > cookiesQuantity)  
  {
    return false;
  }
  else
  {
    return true;
  }
}


// Funkce shopStatus se stará o vizualizaci možností koupit položku
// Rozsvěcí zelené nebo červené LEDky podle hodnot, které mu vrátí funkce enoughCookies
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


// Funkce shopEngine se stará o logiku nakupování věcí z shopu
// vstupní hodnoty jsou cena položky, procenta navýšení ceny a hodnota, kolik cookies za sekundu položka shopu přidává
long shopEngine(long price, byte raise, int add){
  long newPrice;
	if (enoughCookies(price))                       // pokud máme dost cookies (cena je menší než celkový počet cookies)
	{
	  perSecondAdd += add;                          // nastavíme novou hodnotu přírustku cookies za sekundu
    newPrice = price + (price*raise/100);         // zvýšíme cenu položky shopu o počet procent "raise"
    cookiesQuantity -= price;                     // zaplacenou cenu odečteme od celkového počt cookies
	  return newPrice;                              // a vrátíme novou cenu položky
  }
	else
	{
	  return price;                                 // pokud k nákupu nedojde, vrátíme původní cenu
	}
}

// Hlavni program
void loop() {
  // Na začátku smyčky si načtene stavy tlačítek
  currentStateCookieBtn = digitalRead(cookieBtn);
  currentStateMultiplierBtn = digitalRead(multiplierBtn);
  currentStateShopFarmBtn = digitalRead(shopFarmBtn);
  currentStateShopFactoryBtn = digitalRead(shopFactoryBtn);
  currentStateShopMineBtn = digitalRead(shopMineBtn);
  currentStateShopClonerBtn = digitalRead(shopClonerBtn);
  // Nastvíme aktuální stav obchodu
  shopStatus();

  // Zjistíme, zda je tlačítko stisknuté a minule nebylo - tím zabráníme, aby program počítal neustále stiknuté tlačítko jako stisky.
  // Uživatel opravdu musí tlačítko pustit a znovu stisknout. Požíváme tuto logiku testování u všech tlačítek
  if(currentStateCookieBtn == 1 && lastStateCookieBtn == 0)
  {
    // přičteme cookies k celkovému počtu a změníme minulý stav tlačítka na stisknuté
    cookiesQuantity += increment;
    lastStateCookieBtn = 1;
  }
  else if (currentStateCookieBtn == 0 && lastStateCookieBtn == 1) lastStateCookieBtn = 0; // jinak nastavíme, že tlačítko stisknuté není
  
  // Tlačítko násobiče přičítání cookies
  if(currentStateMultiplierBtn == 1 && lastStateMultiplierBtn == 0)
  {  
    if(cookiesQuantity >= priceOfMultiplier[counterMultiplierBuy])  // pokud máme dost cookies
    {
      increment *= 2;                                               // zdvojnásobíme přičítanou hodnotu
      cookiesQuantity -= priceOfMultiplier[counterMultiplierBuy];   // a odečteme cenu od celkového počtu
      counterMultiplierBuy++;                                       // a zvýšíme hodnotu počtu zakopení - pdole ní v poly cen určujeme aktuální cenu
                                                                    // Toto platí pro násobič, u položek shopu se o změnu ceny stará funkce shopEngine
    }
    lastStateMultiplierBtn = 1;
  }
  else if (currentStateMultiplierBtn == 0 && lastStateMultiplierBtn == 1) lastStateMultiplierBtn = 0;
  
  // Tlačítko 1------------------------------------------------------------------------------------
  
  if(currentStateShopFarmBtn == 1 && lastStateShopFarmBtn == 0)
  {   
      priceFarm = shopEngine(priceFarm, percentageRaiseFarm, addFarm);  //  platí pro všechny položky shopu, shopEngine nám zvýší počet přičítaných cookies a vrátí novou cenu nebo zachová původní
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


// Přičítání hodnot každou vteřinu
// pokud je rozdíl aktuálního počtu milisekund od začátku běhu programu větší o 1000 než hodnota v lastSeconds
// znamená to, že uběhla minimálně 1s.
// K celkové hodnotě se pak přičte aktuální sekundový přírustek a nastaví se nová hodnota pro lastSecond
if((millis() - lastSecond) > 1000) 
{
  lastSecond = millis();
  cookiesQuantity += perSecondAdd;
}

  delay(30);                    // nastavení zpoždění kvůli omezení blikání displaye
  lcd.clear();     
  lcd.setCursor(0, 0);          // Nastavení kurzoru na začátek prvního řádku
  lcd.print(infoMsg);           // a vypsání zprávy ("Cookies:")
  lcd.setCursor(0, 1);          // Nastavení kurzoru na začátek druhého řádku displaye
  lcd.print(cookiesQuantity);   // a vypsání celkového počtu cookies

}
