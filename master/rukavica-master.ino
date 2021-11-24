int pr2 = 0, pr3 = 0, pr4 = 0, pr5 = 0, pr6 = 0, pr7 = 0, pr8 = 0, pr9 = 0, k = 3, a, x, y, b = 1, j = 0;
#define button1 3
#define button2 4
#define button3 5
#include <MPU6050.h>
#include <Wire.h>
#include <I2Cdev.h>

boolean buttonState1 = LOW;
boolean buttonState2 = LOW;
boolean buttonState3 = LOW;

MPU6050 mpu;
int16_t ax, ay, az, gx, gy, gz;

void setup() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);

  Wire.begin();
  mpu.initialize(); //pokreni senzor mpu6050
  if (!mpu.testConnection()) { while (1); }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  if (debounceButton1(buttonState1) == HIGH && buttonState1 == LOW) // na pritisak 1. gumba
{
    Serial.println(269);
    buttonState1 = HIGH;
} else if (debounceButton1(buttonState1) == LOW && buttonState1 == HIGH){
    Serial.println(270);
    buttonState1 = LOW;
}
  
  if (debounceButton2(buttonState2) == HIGH && buttonState2 == LOW) // na pritisak 2. gumba
{
    for (int i = 0; i<51; i++){
        if (digitalRead(button2) == HIGH) {
          delay(40);
          if (digitalRead(button1) == HIGH) {
            j++;
          }
        } else {
            j = 0;
            break;
        }
        if (i == 50 && j < 40) {
          pr8++;
        }
        if (i == 50 && j > 40){
          pr9 = pr9 * -1 + 1;
          j = 0;
        }
      }
      
    if (pr8 == 0)
      Serial.println(271);
    else if (pr8 == 1)
      Serial.println(291);
    else if (pr8 == 2)
      Serial.println(293);
    else if (pr8 == 3){
      b *= -1;
      pr8 = 0;
    }
    
    buttonState2 = HIGH;
} else if (debounceButton2(buttonState2) == LOW && buttonState2 == HIGH){
    if (pr8 == 0)
      Serial.println(272);
    else if (pr8 == 1)
      Serial.println(292);
    else if (pr8 == 2)
      Serial.println(294);
    buttonState2 = LOW;
  }
  
  if (debounceButton3(buttonState3) == HIGH && buttonState3 == LOW) // na pritisak 3. gumba
{
    
    for (int i = 0; i<51; i++){
        if (digitalRead(button3) == HIGH) 
          delay(40);
        else break;
        if (i == 50) pr7 = 1;
    }
    if (pr7 == 0){
      if (pr2 == 0) 
        pr2 = 1;
      else if (pr2 == 1)
        pr2 = 2;
      else if (pr2 == 2)
        pr2 = 3;
      else if (pr2 == 3)
        pr2 = 0;
    }
    if (pr7 == 1) {
      k++;
      if (k == 5) k = 1;
      a = k + 300;
      Serial.println(a);
      pr7 = 0;
    }
    
    buttonState3 = HIGH;
    
} else if (debounceButton3(buttonState3) == LOW && buttonState3 == HIGH){
    buttonState3 = LOW;
  }

  if (pr2 == 0){ // postavljeno za mis

    if (pr9 == 0){ //normalno
      x = map(ax, -16000, 16000, 90, -90);
      y = map(ay, -16000, 16000, 90, -90);
      if (x > 10 || x < -10) Serial.println(x);
      y = y * 100 * b;
      if (y > 1000 || y < -1000) Serial.println(y);
    }
    
    if (pr9 == 1){ //scroll
      if (ax < 1000 && ay < -8000)
      Serial.println(295);
      if (ax < 1000 && ay > 8000)
      Serial.println(296);
    }

    if (pr4 !=0){
      pr4 = 0;
      Serial.println(273);
    }
  }

  if (pr2 == 1){ // postavljeno za strelice

    if (pr4 !=1){
      pr4 = 1;
      Serial.println(273);
    }

    if (pr9 == 0){
      if (ax < 1000 && ay < -8000){
        Serial.println(274);
        if (pr3 != 1) pr3 = 1;
      }
        
      if (ax < 1000 && ay > 8000){
        Serial.println(276);
        if (pr3 != 1) pr3 = 1;
      }
        
      if (ax > 8000 && ay < 1000){
        Serial.println(278);
        if (pr3 != 1) pr3 = 1;
      }
        
      if (ax < -8000 && ay < 1000){
        Serial.println(280);
        if (pr3 != 1) pr3 = 1;
      }
  
      if (ax > -8000 && ax < 8000 && ay > -8000 && ay < 8000){
        if (pr3 == 1){
          Serial.println(273);
          pr3 = 0;
        }
      }
    }

    if (pr9 == 1){ //scroll
      if (ax < 1000 && ay < -8000)
      Serial.println(295);
      if (ax < 1000 && ay > 8000)
      Serial.println(296);
    }
  }

  if (pr2 == 2){ // postavljeno za w a s d

    if (pr4 !=2){
      pr4 = 2;
      Serial.println(273);
    }

    if (pr9 == 0){
      if (ax < 1000 && ay < -8000){  
        Serial.println(283);
        if (pr3 != 1) pr3 = 1;
      }
        
      if (ax < 1000 && ay > 8000){
        Serial.println(285);
        if (pr3 != 1) pr3 = 1;
      }
        
      if (ax > 8000 && ay < 1000){
        Serial.println(287);
        if (pr3 != 1) pr3 = 1;
      }
        
      if (ax < -8000 && ay < 1000){
        Serial.println(289);
        if (pr3 != 1) pr3 = 1;
      }
    
      if (ax > -8000 && ax < 8000 && ay > -8000 && ay < 8000){
        if (pr3 == 1){
          Serial.println(273);
          pr3 = 0;
        }
      }
    }
    
    if (pr9 == 1){ //scroll
      if (ax < 1000 && ay < -8000)
      Serial.println(295);
      if (ax < 1000 && ay > 8000)
      Serial.println(296);
    }
  }

  delay(50);
}

boolean debounceButton1(boolean state)
{  // funkcija za debounce gumba 1, uklanja smetnje
  boolean stateNow = digitalRead(button1);;
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(button1);;
  }
  return stateNow;
  
}

boolean debounceButton2(boolean state)
{  // funkcija za debounce gumba 2, uklanja smetnje
  boolean stateNow = digitalRead(button2);;
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(button2);;
  }
  return stateNow;
  
}

boolean debounceButton3(boolean state)
{  // funkcija za debounce gumba 3, uklanja smetnje
  boolean stateNow = digitalRead(button3);;
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(button3);;
  }
  return stateNow;
  
}