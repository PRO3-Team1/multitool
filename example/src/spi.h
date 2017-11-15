/*
 * spi.h
 *
 *  Created on: Nov 24, 2015
 *      Author: mortenopprudjakobsen
 */

#ifndef SPI_H_
#define SPI_H_

void spi_init(void);
unsigned char spi_xfer(unsigned char tx);
void spi_start();
void spi_stop();

#endif /* SPI_H_ */
