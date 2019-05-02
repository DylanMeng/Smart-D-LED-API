/***************************************************************
* FILE NAME: ota.h
*
* MIT License
*
* Copyright (c) 2019 Dylan Meng
*
***************************************************************/

#define UPDATE_FILE "UPDATE.BIN"
#define KNOW_CHECKSUM_FILE "KNOW_CHECKSUM.BIN"

class otaClass {

protected: 

	SerialFlashFile know_checksum_file;
	SerialFlashFile update_file;

	uint8 tmpBuffer[4];
	//uint8 spiFlashBuffer[512];
	CRC32 crc;

public:
		
	void initFlash() {
		if (!SerialFlash.begin(SERIAL_FLASH_CS)) {
			DEBUG_PRINT("Critical: Unable to access SPI Flash chip"); // OTA update will not work
		}
	}

	void addChecksumToFlash(uint8_t crc32_a, uint8_t crc32_b, 
		uint8_t crc32_c, uint8_t crc32_d) {

		if (SerialFlash.create(KNOW_CHECKSUM_FILE, 4))
		{
			know_checksum_file = SerialFlash.open(KNOW_CHECKSUM_FILE);

			tmpBuffer[0] = crc32_a;
			tmpBuffer[1] = crc32_b;
			tmpBuffer[2] = crc32_c;
			tmpBuffer[3] = crc32_d;

			know_checksum_file.write(tmpBuffer, 4);

			for (int i = 0; i < 4; i++)
			{
				tmpBuffer[i] = 0;
			}

			know_checksum_file.close();


		}
		if (SerialFlash.exists(KNOW_CHECKSUM_FILE))
		{
			know_checksum_file = SerialFlash.open(KNOW_CHECKSUM_FILE);

			know_checksum_file.read(tmpBuffer, 4);

			//replyBuffer[2] = tmpBuffer[0];
			//replyBuffer[3] = tmpBuffer[1];
			//replyBuffer[4] = tmpBuffer[2];
			//replyBuffer[5] = tmpBuffer[3];

			know_checksum_file.close();

		}


	}
	uint8 verifyFile() {
	crc.reset(); // Reset the CRC engine		

	if (SerialFlash.exists(UPDATE_FILE)) // Check if an update file is on the external flash
	{
		update_file = SerialFlash.open(UPDATE_FILE);

		if (update_file) // File opened successfully?
		{
			unsigned long updateSize = update_file.size(); // Get update file size

			unsigned long byteCount = 0;

			uint8 serialFlashBuffer[512];
			size_t n;

			while (byteCount < updateSize)
			{

				n = update_file.read(serialFlashBuffer, sizeof(serialFlashBuffer));

				for (size_t i = 0; i < n; i++)
				{
					crc.update(serialFlashBuffer[i]);
				}


				byteCount = byteCount + n;
				//DEBUG_PRINT_LN(byteCount);


			}

			uint32_t checksum = crc.finalize(); // Calculate the final CRC32 checksum.
			DEBUG_PRINT_LN("CHECKSUM");
			DEBUG_PRINT_HEX(checksum);

			update_file.close();

			if (SerialFlash.exists(KNOW_CHECKSUM_FILE))
			{

				know_checksum_file = SerialFlash.open(KNOW_CHECKSUM_FILE);

				if (know_checksum_file) // File opened successfully?
				{
					know_checksum_file.read(tmpBuffer, 4);

					DEBUG_PRINT_LN("KNOW CHECKSUM");
					DEBUG_PRINT_HEX(tmpBuffer[3]);
					DEBUG_PRINT_HEX(tmpBuffer[2]);
					DEBUG_PRINT_HEX(tmpBuffer[1]);
					DEBUG_PRINT_HEX(tmpBuffer[0]);
					DEBUG_PRINT_LN("KNOW CHECKSUM");

					know_checksum_file.close();

					uint8 calculated_checksum[4];


					calculated_checksum[0] = checksum;
					calculated_checksum[1] = checksum >> 8;
					calculated_checksum[2] = checksum >> 16;
					calculated_checksum[3] = checksum >> 24;

					DEBUG_PRINT_LN("CAL CHECKSUM");
					DEBUG_PRINT_LN("");
					DEBUG_PRINT_HEX(calculated_checksum[3]);
					DEBUG_PRINT_LN("");
					DEBUG_PRINT_HEX(calculated_checksum[2]);
					DEBUG_PRINT_LN("");
					DEBUG_PRINT_HEX(calculated_checksum[1]);
					DEBUG_PRINT_LN("");
					DEBUG_PRINT_HEX(calculated_checksum[0]);
					DEBUG_PRINT_LN("");
					DEBUG_PRINT_LN("CAL CHECKSUM");

					if (memcmp(calculated_checksum, tmpBuffer, sizeof(calculated_checksum)) == 0)
					{
						DEBUG_PRINT("Update file match checksum - transfer was succesfull");
						return 1;
					}
					else
					{
						DEBUG_PRINT("Update file is corrupted checksum does not match!");
						return 0;
					}
				}
				else
				{
					DEBUG_PRINT("Fail to open know checksum");
					return 0;
				}

			}
			else
			{
				DEBUG_PRINT("know checksum file does not exist");
				return 0;
			}
		}
		else
		{
			DEBUG_PRINT("Fail to open update file");
			return 0;
		}
	}
	else
	{
		DEBUG_PRINT("Update file does not exist");
		return 0;
	}
}
};

otaClass ota;