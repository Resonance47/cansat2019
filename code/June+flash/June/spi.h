#ifndef SPI_H_
#define SPI_H_

////////////////////////////////////////////////// Settings

// SPI
// #define SPI_DDR DDRB
// #define SPI_PORT PORTB
// #define SPI_PIN PINB
// #define MOSI 3
// #define MISO 4
// #define SCK 5

#define DUMMY_BYTE 0xFF

////////////////////////////////////////////////// Functions

// void spi_init()
// {
// 	SPI_DDR |= (1 << MOSI) | (1 << SCK);
// 	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
// }

void spi_write_byte(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & (1 << SPIF)));
}

uint8_t spi_read_byte()
{
	SPDR = DUMMY_BYTE;
	while(!(SPSR & (1 << SPIF)));
	return SPDR;
}

#endif /* SPI_H_ */