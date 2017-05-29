#ifndef flash_lib_h
#define flash_lib_h

//#include "Arduino.h"
#include <SPI.h>

#define negHOLD A0
#define negW A1
#define negS A4
// ---- commands ----
#define WREN 0x06 // write enable
#define WRDI 0x04 // write disable
#define RDSR 0x05 // read status register (> data bytes)
#define WRSR 0x01 // write status register (1 data byte)
#define READ 0x03 // read data bytes (> data bytes)
#define FAST_READ 0x0b // read data bytes at higher speed (> data bytes)
#define FAST_READ_DUAL_OUTPUT 0x3b // read data bytes at higher speed by dual output (> data bytes)
#define FAST_READ_DUAL_INPUT_OUTPUT 0xbb // read data bytes at higher speed by dual input and dual output (> data bytes)
#define PP 0x02 // page program (256 data bytes)
#define SE 0x20 // sector erase
#define BE 0xd8 // block erase
#define CE 0xc7 // chip erase
#define DP 0xb9 // deep power down
#define RDID 0x9f // read device identification (> data bytes)
#define REMS 0x90 // read electronic manufacturer & device identification (> data bytes)
#define RES 0xab // release from deep power-down (and read electronic signature) (> data bytes)

class Flash {
  public:
    Flash(int negS, int DO, int negW, int DIO, int C, int negHOLD);
    int get_manufacture_id();
    int get_flash_capacity();
    int read_data(long address);
    void write_byte(long address, int value);
    void chip_erase(void);
  private:
    int p_negS;
    int p_DO;
    int p_negW;
    int p_DIO;
    int p_C;
    int p_negHOLD;
};

#endif

