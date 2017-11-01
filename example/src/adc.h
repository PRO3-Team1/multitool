/*
 * adc.h
 *
 *  Created on: Nov 5, 2015
 *      Author: mortenopprudjakobsen
 */

#ifndef ADC_H_
#define ADC_H_


void adc_init(void);
unsigned int adc_read(int chan_sel);
unsigned int cal_val(unsigned int val);

#endif /* ADC_H_ */
