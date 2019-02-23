/*
 * MAX6675.c
 *
 *  Created on: 17/02/2019
 *      Author: Toshiba
 */

#include "MAX6675.h"

uint16_t MAX6675_getValue(MAX6675_Typedef* const sensor)
{
	uint8_t buffer[BUFFER_SIZE];

	HAL_SPI_Receive(&MAX6675_SPI,buffer,1,HAL_MAX_DELAY);

	sensor->Value = buffer[1] << 8 | buffer[0];

	sensor->Value = sensor->Value >> 3;

	return sensor->Value;
}

float MAX6675_getTemp(MAX6675_Typedef* const sensor)
{
	sensor->Temp_C = (sensor->MAX6675_getValue(sensor) * MAX_TEMP)/MAX6675_RESOLUTION;

	return sensor->Temp_C;
}

bool MAX6675_getState(MAX6675_Typedef* const sensor)
{
	return sensor->State;
}

void MAX6675_Init(MAX6675_Typedef* const sensor, uint16_t (*getValue_f)(MAX6675_Typedef* const sensor),
				  float (*getTemp_f)(MAX6675_Typedef* const sensor),bool (*getState_f)(MAX6675_Typedef* const sensor))
{
	/*Se inicializan las variables del objeto sensor*/
	sensor->State = false;
	sensor->Temp_C = 0;
	sensor->Value = 0;

	/*Se inializan los apuntadores de los metodos*/
	sensor->MAX6675_getState = getState_f;
	sensor->MAX6675_getTemp = getTemp_f;
	sensor->MAX6675_getValue = getValue_f;
}

MAX6675_Typedef* MAX6675_Create(void)
{
	MAX6675_Typedef* sensor = (MAX6675_Typedef*)malloc(sizeof(MAX6675_Typedef));
	if (sensor != NULL)
	{
		MAX6675_Init(sensor,MAX6675_getValue,MAX6675_getTemp,MAX6675_getState);
	}

	return sensor;
}

void MAX6675_Cleanup(MAX6675_Typedef* const sensor)
{

}

void MAX6675_Destroy(MAX6675_Typedef* const sensor)
{
	if (sensor != NULL)
	{
		MAX6675_Cleanup(sensor);
	}
	free(sensor);
}
