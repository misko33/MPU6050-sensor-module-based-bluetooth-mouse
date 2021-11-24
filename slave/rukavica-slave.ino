int val, x = 0, y = 0, k = 3, a;
#include "Keyboard.h"
#include <Mouse.h>

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {

  if (Serial1.available() > 0)
  {
    val = Serial1.parseInt();

    Keyboard.begin();
    
    if (val == 273)
      Keyboard.releaseAll();
    
    if (val == 269)
      Mouse.press(MOUSE_LEFT);
    if (val == 270)
      Mouse.release(MOUSE_LEFT);
      
    if (val == 271)
      Mouse.press(MOUSE_RIGHT);
    if (val == 272)
      Mouse.release(MOUSE_RIGHT);

    if (val > 300 && val < 305) k = val - 300;

    if (val > 20 && val < 91 || val < -20 && val > -91)
      x = val / k;
    else x = 0;
    
    if (val > 2000 || val < -2000)
      y = val / 100 * -1 / k;
    else y = 0;
    
    Mouse.move(x , y);
     
      if (val == 274){
        Keyboard.press(KEY_UP_ARROW);
      }
      
      if (val == 276){
        Keyboard.press(KEY_DOWN_ARROW);
      }
      
      if (val == 278){
        Keyboard.press(KEY_LEFT_ARROW);
      }
      
      if (val == 280){
        Keyboard.press(KEY_RIGHT_ARROW);
      }
      
      if (val == 283){
        Keyboard.press('w');
      }
      
      if (val == 285){
        Keyboard.press('s');
      }
      
      if (val == 287){
        Keyboard.press('a');
      }
      
      if (val == 289){
        Keyboard.press('d');
      }
        
      if (val == 291)
        Keyboard.press(KEY_RETURN);
      if (val == 292)
        Keyboard.release(KEY_RETURN);

      if (val == 293)
        Keyboard.press(KEY_ESC);
      if (val == 294)
        Keyboard.release(KEY_ESC);
      
      if (val == 295){
        a = 15 / k;
        Mouse.move(0 , 0 , a);
      }
      if (val == 296){
        a = 15 / k * -1;
        Mouse.move(0 , 0 , a);
      }
  }
}
