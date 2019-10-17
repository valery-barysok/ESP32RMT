/**
This file is part of ESP32RMT esp-idf component from
pax-devices (https://github.com/CalinRadoni/pax-devices)
Copyright (C) 2019+ by Calin Radoni

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef ESP32RMT_H
#define ESP32RMT_H

#include "ESP32RMTChannel.h"

// TODO: This class is useless right now !
// Everything that is LED related (timings and send buffer filling should go in DLEDController)

class ESP32RMT
{
public:
	ESP32RMT(void);
	~ESP32RMT(void);

	bool Create(DStrip* inStrip);
	void Destroy(void);

	/**
	 * @brief Configures the RMT peripheral
	 *
	 * Configures the GPIO `gpio_number`
	 * Configure the RMT peripheral using the RMT driver.
	 * Sets `gpio_number` and `channel` members.
	 *
	 * @param[in]     gpio_number The number of GPIO connected to the LED strip.
	 * @param[in]     channel     The RMT channel to control the LED strip.
	 */
	bool Configure(gpio_num_t inGPIONumber, rmt_channel_t inChannel);

	/**
	 * @brief Send data to RMT driver
     *
     * This function works with 1, 2, 3 or 4 bytes per pixel but it currently implements only the:
     * - GRB
     * - GRBW
     * DColorType modes an will return false if called for other modes.
	 */
	bool Send(void);

private:
	DStrip*  strip;

	gpio_num_t    gpio_number;  /*!< The number of GPIO connected to the LED strip */
	rmt_channel_t channel;      /*!< The RMT channel to control the LED strip */
	rmt_item32_t  rmtLO, rmtHI; /*!< Values required to send 0 and 1 */
    rmt_item32_t  rmtLR, rmtHR; /*!< Values required to send 0 and 1 including reset */
	rmt_item32_t  *uglyBuffer;  /*!< The buffer to be passed to the RMT driver for sending */
	uint32_t      uglyLen;      /*!< Length of uglyBuffer */

	void SetGPIO(void);

	void Byte_to_rmtitem(uint8_t data, uint16_t inIdx);
};

#endif