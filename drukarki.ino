
/*Wiktoria Ignor, Michał Ufniarz 2019*/


#define X_STEP_PIN         54   /*przypisanie nazwy do pinu*/
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62

#define X_MIN_PIN           3
#define X_MAX_PIN           2
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

int krok = 0;                     /*definiowanie zmiennych globalnych*/
int kierunek = 0;
String a;
int kroki1=0, kroki2=0, kroki3=0;
int kierunek1=0, kierunek2=0, kierunek3=0;
int czy_mam_odpowiedziec=0;

void setup() {
  Serial.begin(57600);
  
  pinMode(X_ENABLE_PIN, OUTPUT);         /*inincjalizacja programu czyli ustawienie kierunku i wartości pinów*/
  digitalWrite(X_ENABLE_PIN, LOW);
  pinMode(X_DIR_PIN, OUTPUT);
  digitalWrite(X_DIR_PIN, HIGH);
  pinMode(X_STEP_PIN, OUTPUT);
  digitalWrite(X_STEP_PIN, HIGH);

  pinMode(Y_ENABLE_PIN, OUTPUT);
  digitalWrite(Y_ENABLE_PIN, LOW);
  pinMode(Y_DIR_PIN, OUTPUT);
  digitalWrite(Y_DIR_PIN, HIGH);
  pinMode(Y_STEP_PIN, OUTPUT);
  digitalWrite(Y_STEP_PIN, HIGH);

  pinMode(Z_ENABLE_PIN, OUTPUT);
  digitalWrite(Z_ENABLE_PIN, LOW);
  pinMode(Z_DIR_PIN, OUTPUT);
  digitalWrite(Z_DIR_PIN, HIGH);
  pinMode(Z_STEP_PIN, OUTPUT);
  digitalWrite(Z_STEP_PIN, HIGH);

  pinMode(X_MAX_PIN, INPUT_PULLUP);     /*ustawienie wysokiej impedancji na krańcówkach*/
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  pinMode(Z_MAX_PIN, INPUT_PULLUP);

}

void loop() {

  if((kierunek1 == 1 || (kierunek1 == 0 && digitalRead(X_MAX_PIN)==0) )&& kroki1>0){     /*sterowanie głowicą w kierunku pionowym*/  
    digitalWrite(X_STEP_PIN, LOW);
    kroki1--;
  }
  if((kierunek2 == 1 || (kierunek2 == 0 && digitalRead(Y_MAX_PIN)==0)) && kroki2>0){
    digitalWrite(Y_STEP_PIN, LOW);
    kroki2--;
  }
  if((kierunek3 == 1 || (kierunek3 == 0 && digitalRead(Z_MAX_PIN)==0)) && kroki3>0){
    digitalWrite(Z_STEP_PIN, LOW);
    kroki3--;
  }

 
 
  delay(1);
  digitalWrite(X_STEP_PIN, HIGH);
  digitalWrite(Y_STEP_PIN, HIGH);
  digitalWrite(Z_STEP_PIN, HIGH);
  delay(1);
  krok++;

//  if (krok == 500) {
//
//    krok = 0;
//    kierunek = !kierunek;
//    digitalWrite(X_DIR_PIN, kierunek);
//    digitalWrite(Y_DIR_PIN, kierunek);
//    digitalWrite(Z_DIR_PIN, kierunek);
//
//
//  }

  while (Serial.available()>0) {

    a=Serial.readStringUntil('\n');
    sscanf(a.c_str(), "a %d b %d c %d", &kroki1, &kroki2, &kroki3);             /*komunikacja szeregowa*/
   // Serial.println(kroki1);
    czy_mam_odpowiedziec=1;
    
    if(kroki1<0){ 
       kroki1= -kroki1;
       kierunek1=1;
       digitalWrite(X_DIR_PIN, kierunek1);       
    } else {
      kierunek1=0;
      digitalWrite(X_DIR_PIN, kierunek1);
    }
    
    if(kroki2<0){ 
       kroki2= -kroki2;
       kierunek2=1;
       digitalWrite(Y_DIR_PIN, kierunek2);       
    } else {
      kierunek2=0;
      digitalWrite(Y_DIR_PIN, kierunek2);
    }
    
    if(kroki3<0){ 
       kroki3= -kroki3;
       kierunek3=1;
       digitalWrite(Z_DIR_PIN, kierunek3);       
    } else {
      kierunek3=0;
      digitalWrite(Z_DIR_PIN, kierunek3);
    }

    
  } //koniec komunikacji szeregowej

      if(kroki1==0 && kroki2==0 && kroki3==0 && czy_mam_odpowiedziec==1)
    {
      Serial.println("OK");
      czy_mam_odpowiedziec=0;
    }
  
  
}
