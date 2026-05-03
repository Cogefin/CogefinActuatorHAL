

#ifndef __ARDUINO_SHIELD_CONVERTER_H__
#define __ARDUINO_SHIELD_CONVERTER_H__
#include "detectArduinoHardware.h"



#if FORM_FACTOR_TYPE == FORM_FACTOR_MKR /* MKR */
#define DIGITAL_0_RX 13
#define DIGITAL_1_TX 14
#define DIGITAL_2     2
#define DIGITAL_3     3
#define DIGITAL_4     4
#define DIGITAL_5     5
#define DIGITAL_6     6
#define DIGITAL_7     7
#define DIGITAL_8     0
#define DIGITAL_9     1
#define DIGITAL_10   21 /* A6 */
#define DIGITAL_11    8
#define DIGITAL_12   10
#define DIGITAL_13    9
#define ANALOG_0     A0
#define ANALOG_1     A1
#define ANALOG_2     A2
#define ANALOG_3     A3
#define ANALOG_4     A4
#define ANALOG_5     A5
#ifndef SPI_SCK
#define SPI_SCK       9
#endif
#ifndef SPI_CIPO
#define SPI_CIPO     10
#endif
#ifndef SPI_COPI
#define SPI_COPI      8
#endif
#ifndef SPI_MISO
#define SPI_MISO     10
#endif
#ifndef SPI_MOSI
#define SPI_MOSI      8
#endif
#ifndef I2C_SDA
#define I2C_SDA      11
#endif
#ifndef I2C_SCL
#define I2C_SCL      12
#endif
#elif FORM_FACTOR_TYPE == FORM_FACTOR_NANO /* NANO */
#define DIGITAL_0_RX  0
#define DIGITAL_1_TX  1
#define DIGITAL_2     2
#define DIGITAL_3     3
#define DIGITAL_4     4
#define DIGITAL_5     5
#define DIGITAL_6     6
#define DIGITAL_7     7
#define DIGITAL_8     8
#define DIGITAL_9     9
#define DIGITAL_10   10
#define DIGITAL_11   11
#define DIGITAL_12   12
#define DIGITAL_13   13
#define ANALOG_0     A0
#define ANALOG_1     A1
#define ANALOG_2     A2
#define ANALOG_3     A3
#define ANALOG_4     A4
#define ANALOG_5     A5
#ifndef SPI_SCK
#define SPI_SCK      13
#endif
#ifndef SPI_CIPO
#define SPI_CIPO     12
#endif
#ifndef SPI_COPI
#define SPI_COPI     11
#endif
#ifndef SPI_MISO
#define SPI_MISO     12
#endif
#ifndef SPI_MOSI
#define SPI_MOSI     11
#endif
#ifndef I2C_SDA
#define I2C_SDA      A4
#endif
#ifndef I2C_SCL
#define I2C_SCL      A5
#endif
#else /* Classic etc.*/
#define DIGITAL_0_RX  0
#define DIGITAL_1_TX  1
#define DIGITAL_2     2
#define DIGITAL_3     3
#define DIGITAL_4     4
#define DIGITAL_5     5
#define DIGITAL_6     6
#define DIGITAL_7     7
#define DIGITAL_8     8
#define DIGITAL_9     9
#define DIGITAL_10   10
#define DIGITAL_11   11
#define DIGITAL_12   12
#define DIGITAL_13   13
#define ANALOG_0     A0
#define ANALOG_1     A1
#define ANALOG_2     A2
#define ANALOG_3     A3
#define ANALOG_4     A4
#define ANALOG_5     A5
#ifndef SPI_SCK
#define SPI_SCK      13
#endif
#ifndef SPI_CIPO
#define SPI_CIPO     12
#endif
#ifndef SPI_COPI
#define SPI_COPI     11
#endif
#ifndef SPI_MISO
#define SPI_MISO     12
#endif
#ifndef SPI_MOSI
#define SPI_MOSI     11
#endif
#ifndef I2C_SDA
#define I2C_SDA      18
#endif
#ifndef I2C_SCL
#define I2C_SCL      19
#endif
#endif

#endif /* __ARDUINO_SHIELD_CONVERTER_H__ */
