#include "Flash.h"


Flash::Flash(int negS, int DO, int negW, int DIO, int C, int negHOLD){
  p_negS = negS;
  p_DO = DO;
  p_negW = negW;
  p_DIO = DIO;
  p_C = C;
  p_negHOLD = negHOLD;
  SPI.begin();
  Serial.begin(9600);
  pinMode(negS, OUTPUT);
  pinMode(DO, OUTPUT);
  pinMode(negW, OUTPUT);  
  pinMode(DIO, INPUT);
  pinMode(C, OUTPUT);
  pinMode(negHOLD, OUTPUT);
  digitalWrite(negW, LOW);  
  digitalWrite(negHOLD, HIGH);
}


int Flash::get_manufacture_id(){
  int flash_id=-1;
  digitalWrite(p_negS, LOW);
  int ret = SPI.transfer(RDID);
  flash_id = SPI.transfer(0x00);
  digitalWrite(p_negS, HIGH);      
  return flash_id;
}

int Flash::get_flash_capacity(){
  int capacity=-1;
  digitalWrite(p_negS, LOW);
  int ret = SPI.transfer(RDID);
  SPI.transfer(0x00);
  SPI.transfer(0x00);
  capacity = SPI.transfer(0x00);
  digitalWrite(p_negS, HIGH);
  return capacity;
}

int Flash::read_data(long address){
  int value = -1;
  digitalWrite(p_negS, LOW); 
  int ret = SPI.transfer(READ); 
  SPI.transfer(address & 0x0f);  
  SPI.transfer((address & 0xf0)>>8);  
  SPI.transfer((address & 0xf00)>>16);
  value = SPI.transfer(0x00);
  digitalWrite(p_negS, HIGH);  
  return value;
}

void Flash::write_byte(long address, int value){
  digitalWrite(p_negS, LOW); 
  int ret = SPI.transfer(WREN);
  digitalWrite(p_negS, HIGH);
  digitalWrite(p_negS, LOW); 
  ret = SPI.transfer(PP); 
  SPI.transfer(address & 0x0f);  
  SPI.transfer((address & 0xf0)>>8);  
  SPI.transfer((address & 0xf00)>>16);
  SPI.transfer(value);
  digitalWrite(p_negS, HIGH);  
}

void Flash::chip_erase(void){
  digitalWrite(p_negS, LOW);
  int ret = SPI.transfer(WREN);   
  digitalWrite(p_negS, HIGH);
  digitalWrite(p_negS, LOW);
  ret = SPI.transfer(CE);
  digitalWrite(p_negS, HIGH);
  digitalWrite(p_negS, LOW);
  ret = SPI.transfer(RDSR);
  digitalWrite(p_negS, HIGH);
  digitalWrite(p_negS, LOW);  
  int data = SPI.transfer(0x00);
  while ((data & 0x02) != 0x0){
    data = SPI.transfer(0x00);
  }  
  digitalWrite(p_negS, HIGH);
}

