/***************************************************************
* FILE NAME: spi_flash.h
*
* MIT License
*
* Copyright (c) 2019 Dylan Meng
*	
* Modification / wrapper of https://github.com/Marzogh/SPIMemory (GPL-3.0)
***************************************************************/

class spiFlashClass {

public:
	
	uint8_t alive = 0; 
	uint8_t jedec_id[3] = { 0x00, 0x00, 0x00 };
	uint32_t chipsize = 0;	
	uint32_t blocksize = 0;

	void init(uint8_t serial_flash_cs) {
		if (!SerialFlash.begin(serial_flash_cs)) {
			alive = 0;
			DEBUG_PRINT("SPI FLASH - CRITICAL ERROR - Unable to access SPI Flash chip"); 		
		}
		else {
			alive = 1;
			DEBUG_PRINT("SPI FLASH - INIT SUCESS");
		}
	}
	
	void get_info() {
		if (alive == 1) {
			DEBUG_PRINT("SPI FLASH - DEVICE INFO");

			uint8_t buf[256];

			SerialFlash.readID(buf);
			chipsize = SerialFlash.capacity(buf);
			blocksize = SerialFlash.blockSize();
			jedec_id[0] = buf[0];
			jedec_id[1] = buf[1];
			jedec_id[2] = buf[2];

			// Print chip identification
			DEBUG_PRINT_LN();
			DEBUG_PRINT_LN("Read Chip Identification:");
			DEBUG_PRINT("  JEDEC ID:     ");
			DEBUG_PRINT_HEX(jedec_id[0]);
			DEBUG_PRINT(" ");
			DEBUG_PRINT_HEX(jedec_id[1]);
			DEBUG_PRINT(" ");
			DEBUG_PRINT_HEX(jedec_id[2]);
			DEBUG_PRINT_LN();
			DEBUG_PRINT("  Memory Size:  ");
			DEBUG_PRINT(chipsize);
			DEBUG_PRINT_LN(" bytes");
			DEBUG_PRINT("  Block Size:   ");
			DEBUG_PRINT(blocksize);
			DEBUG_PRINT_LN(" bytes");
		}
		else
		{
			DEBUG_PRINT("SPI FLASH - CRITICAL ERROR - Not initialize / unreachable");
		}
	}

	void hardware_test() {
		if (alive == 1) {
			DEBUG_PRINT("SPI FLASH - HARDWARE TEST - TODO");
		}
		else
		{
			DEBUG_PRINT("SPI FLASH - CRITICAL ERROR - Not initialize / unreachable");
		}
	}

};

spiFlashClass spiFlash;