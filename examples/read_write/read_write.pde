#include "Flash.h"

Flash my_flash = Flash(10, 2, 3, 5, 6, 7);

void setup() {
  Serial.begin(9600);
}

void loop() {
  my_flash.write_byte(35, 0xc);
  delay(1000);
  Serial.println(my_flash.read_data(35), HEX);
  while(1);
}
