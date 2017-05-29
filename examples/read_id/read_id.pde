#include "Flash.h"

Flash my_flash = Flash(10, 2, 3, 5, 6, 7);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int data = my_flash.get_manufacture_id();
  Serial.println(data, HEX);  
  Serial.println(my_flash.get_flash_capacity(), HEX);  
}
