/**
 * MAX6675.h
 *
 *  Created on: 17/02/2019
 *      Author: Toshiba
 */

#ifndef MAX6675_H_
#define MAX6675_H_

#include "stm32f3xx.h"

#if defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F3)
#include "stm32f3xx_hal.h"
#elif defined(STM32F4)
#include "stm32f3xx_hal.h"
#else
#error "MAX6675 library was tested only on STM32F1 and STM32F4 MCU families. Please modify ssd1306.h if you know what you are doing. Also please send a pull request if it turns out the library works on other MCU's as well!"
#endif


#include "stdbool.h"
#include "stdlib.h"
#include "spi.h"

#define MAX6675_SPI hspi3
#define BUFFER_SIZE 2
#define MAX_TEMP 1024
#define MAX6675_RESOLUTION 4095

typedef struct MAX6675_Typedef MAX6675_Typedef;

struct MAX6675_Typedef{

	uint16_t Value;
	float Temp_C;
	bool State;

	uint16_t (*MAX6675_getValue)(MAX6675_Typedef* const sensor);
	float (*MAX6675_getTemp)(MAX6675_Typedef* const sensor);
	bool (*MAX6675_getState)(MAX6675_Typedef* const sensor);
};

uint16_t MAX6675_getValue(MAX6675_Typedef* const sensor);
float MAX6675_getTemp(MAX6675_Typedef* const sensor);
bool MAX6675_getState(MAX6675_Typedef* const sensor);

void MAX6675_Init(MAX6675_Typedef* const sensor, uint16_t (*getValue_f)(MAX6675_Typedef* const sensor),
				  float (*getTemp_f)(MAX6675_Typedef* const sensor),bool (*getState_f)(MAX6675_Typedef* const sensor));
MAX6675_Typedef* MAX6675_Create(void);
void MAX6675_Cleanup(MAX6675_Typedef* const sensor);
void MAX6675_Destroy(MAX6675_Typedef* const sensor);

#endif /* MAX6675_H_ */
