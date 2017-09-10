/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * This file has been automatically generated using ChibiStudio board
 * generator plugin. Do not edit manually.
 */

#ifndef BOARD_H
#define BOARD_H

/*
 * Setup for OpenPilot Revolution board.
 */

/*
 * Board identifier.
 */
#define BOARD_OP_REVOLUTION
#define BOARD_NAME                  "OpenPilot Revolution"

/*
 * Board oscillators-related settings.
 * NOTE: LSE not fitted.
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                8000000U
#endif

/*
 * Board voltages.
 * Required for performance limits calculation.
 */
#define STM32_VDD                   330U

/*
 * MCU type as defined in the ST header.
 */
#define STM32F405xx

/*
 * IO pins assignments.
 */
#define GPIOA_SERVO_OUT_6           0U
#define GPIOA_SERVO_OUT_5           1U
#define GPIOA_SERVO_OUT_4           2U
#define GPIOA_SERVO_OUT_3           3U
#define GPIOA_MPU_CS                4U
#define GPIOA_MPU_SCK               5U
#define GPIOA_MPU_MISO              6U
#define GPIOA_MPU_MOSI              7U
#define GPIOA_SONAR                 8U
#define GPIOA_UART1_TX              9U
#define GPIOA_UART1_RX              10U
#define GPIOA_OTG_FS_DM             11U
#define GPIOA_OTG_FS_DP             12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_MODEM_CS              15U

#define GPIOB_SERVO_OUT_1           0U
#define GPIOB_SERVO_OUT_2           1U
#define GPIOB_BOOT0                 2U
#define GPIOB_FLASH_CS              3U
#define GPIOB_LED_WARN              4U
#define GPIOB_LED_STAT              5U
#define GPIOB_PIN6                  6U
#define GPIOB_MAG_DRDY              7U
#define GPIOB_MAG_BAR_SCL           8U
#define GPIOB_MAG_BAR_SDA           9U
#define GPIOB_FLEXI_SCL             10U
#define GPIOB_FLEXI_SDA             11U
#define GPIOB_INPUT_PIN_3           12U
#define GPIOB_INPUT_PIN_4           13U
#define GPIOB_SERVO_IN_1            14U
#define GPIOB_SERVO_IN_2            15U

#define GPIOC_SBUS_INV              0U
#define GPIOC_CURR_ANA              1U
#define GPIOC_VOLT_ANA              2U
#define GPIOC_MODEM_FREQ            3U
#define GPIOC_MPU_INT               4U
#define GPIOC_VBUS_SEN              5U
#define GPIOC_SERVO_IN_3            6U
#define GPIOC_SERVO_IN_4            7U
#define GPIOC_SERVO_IN_5            8U
#define GPIOC_SERVO_IN_6            9U
#define GPIOC_MODEM_FLASH_SCK       10U
#define GPIOC_MODEM_FLASH_MISO      11U
#define GPIOC_MODEM_FLASH_MOSI      12U
#define GPIOC_PIN13                 13U
#define GPIOC_PIN14                 14U
#define GPIOC_PIN15                 15U

#define GPIOD_OSC_IN                0U
#define GPIOD_OSC_OUT               1U
#define GPIOD_MODEM_IRQ             2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

#define GPIOE_PIN0                  0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

#define GPIOH_PIN0                  0U
#define GPIOH_PIN1                  1U
#define GPIOH_PIN2                  2U
#define GPIOH_PIN3                  3U
#define GPIOH_PIN4                  4U
#define GPIOH_PIN5                  5U
#define GPIOH_PIN6                  6U
#define GPIOH_PIN7                  7U
#define GPIOH_PIN8                  8U
#define GPIOH_PIN9                  9U
#define GPIOH_PIN10                 10U
#define GPIOH_PIN11                 11U
#define GPIOH_PIN12                 12U
#define GPIOH_PIN13                 13U
#define GPIOH_PIN14                 14U
#define GPIOH_PIN15                 15U

#define GPIOI_PIN0                  0U
#define GPIOI_PIN1                  1U
#define GPIOI_PIN2                  2U
#define GPIOI_PIN3                  3U
#define GPIOI_PIN4                  4U
#define GPIOI_PIN5                  5U
#define GPIOI_PIN6                  6U
#define GPIOI_PIN7                  7U
#define GPIOI_PIN8                  8U
#define GPIOI_PIN9                  9U
#define GPIOI_PIN10                 10U
#define GPIOI_PIN11                 11U
#define GPIOI_PIN12                 12U
#define GPIOI_PIN13                 13U
#define GPIOI_PIN14                 14U
#define GPIOI_PIN15                 15U

/*
 * IO lines assignments.
 */
#define LINE_SERVO_OUT_6            PAL_LINE(GPIOA, 0U)
#define LINE_SERVO_OUT_5            PAL_LINE(GPIOA, 1U)
#define LINE_SERVO_OUT_4            PAL_LINE(GPIOA, 2U)
#define LINE_SERVO_OUT_3            PAL_LINE(GPIOA, 3U)
#define LINE_MPU_CS                 PAL_LINE(GPIOA, 4U)
#define LINE_MPU_SCK                PAL_LINE(GPIOA, 5U)
#define LINE_MPU_MISO               PAL_LINE(GPIOA, 6U)
#define LINE_MPU_MOSI               PAL_LINE(GPIOA, 7U)
#define LINE_SONAR                  PAL_LINE(GPIOA, 8U)
#define LINE_UART1_TX               PAL_LINE(GPIOA, 9U)
#define LINE_UART1_RX               PAL_LINE(GPIOA, 10U)
#define LINE_OTG_FS_DM              PAL_LINE(GPIOA, 11U)
#define LINE_OTG_FS_DP              PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)
#define LINE_MODEM_CS               PAL_LINE(GPIOA, 15U)

#define LINE_SERVO_OUT_1            PAL_LINE(GPIOB, 0U)
#define LINE_SERVO_OUT_2            PAL_LINE(GPIOB, 1U)
#define LINE_BOOT0                  PAL_LINE(GPIOB, 2U)
#define LINE_FLASH_CS               PAL_LINE(GPIOB, 3U)
#define LINE_LED_WARN               PAL_LINE(GPIOB, 4U)
#define LINE_LED_STAT               PAL_LINE(GPIOB, 5U)
#define LINE_MAG_DRDY               PAL_LINE(GPIOB, 7U)
#define LINE_MAG_BAR_SCL            PAL_LINE(GPIOB, 8U)
#define LINE_MAG_BAR_SDA            PAL_LINE(GPIOB, 9U)
#define LINE_FLEXI_SCL              PAL_LINE(GPIOB, 10U)
#define LINE_FLEXI_SDA              PAL_LINE(GPIOB, 11U)
#define LINE_INPUT_PIN_3            PAL_LINE(GPIOB, 12U)
#define LINE_INPUT_PIN_4            PAL_LINE(GPIOB, 13U)
#define LINE_SERVO_IN_1             PAL_LINE(GPIOB, 14U)
#define LINE_SERVO_IN_2             PAL_LINE(GPIOB, 15U)

#define LINE_SBUS_INV               PAL_LINE(GPIOC, 0U)
#define LINE_CURR_ANA               PAL_LINE(GPIOC, 1U)
#define LINE_VOLT_ANA               PAL_LINE(GPIOC, 2U)
#define LINE_MODEM_FREQ             PAL_LINE(GPIOC, 3U)
#define LINE_MPU_INT                PAL_LINE(GPIOC, 4U)
#define LINE_VBUS_SEN               PAL_LINE(GPIOC, 5U)
#define LINE_SERVO_IN_3             PAL_LINE(GPIOC, 6U)
#define LINE_SERVO_IN_4             PAL_LINE(GPIOC, 7U)
#define LINE_SERVO_IN_5             PAL_LINE(GPIOC, 8U)
#define LINE_SERVO_IN_6             PAL_LINE(GPIOC, 9U)
#define LINE_MODEM_FLASH_SCK        PAL_LINE(GPIOC, 10U)
#define LINE_MODEM_FLASH_MISO       PAL_LINE(GPIOC, 11U)
#define LINE_MODEM_FLASH_MOSI       PAL_LINE(GPIOC, 12U)

#define LINE_OSC_IN                 PAL_LINE(GPIOD, 0U)
#define LINE_OSC_OUT                PAL_LINE(GPIOD, 1U)
#define LINE_MODEM_IRQ              PAL_LINE(GPIOD, 2U)






/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))

/*
 * GPIOA setup:
 *
 * PA0  - SERVO_OUT_6               (alternate 1).
 * PA1  - SERVO_OUT_5               (alternate 1).
 * PA2  - SERVO_OUT_4               (alternate 1).
 * PA3  - SERVO_OUT_3               (alternate 1).
 * PA4  - MPU_CS                    (output pushpull maximum).
 * PA5  - MPU_SCK                   (alternate 5).
 * PA6  - MPU_MISO                  (alternate 5).
 * PA7  - MPU_MOSI                  (alternate 5).
 * PA8  - SONAR                     (input pullup).
 * PA9  - UART1_TX                  (alternate 7).
 * PA10 - UART1_RX                  (alternate 7).
 * PA11 - OTG_FS_DM                 (alternate 10).
 * PA12 - OTG_FS_DP                 (alternate 10).
 * PA13 - SWDIO                     (alternate 0).
 * PA14 - SWCLK                     (alternate 0).
 * PA15 - MODEM_CS                  (alternate 6).
 */
#define VAL_GPIOA_MODER             (PIN_MODE_ALTERNATE(GPIOA_SERVO_OUT_6) |\
                                     PIN_MODE_ALTERNATE(GPIOA_SERVO_OUT_5) |\
                                     PIN_MODE_ALTERNATE(GPIOA_SERVO_OUT_4) |\
                                     PIN_MODE_ALTERNATE(GPIOA_SERVO_OUT_3) |\
                                     PIN_MODE_OUTPUT(GPIOA_MPU_CS) |        \
                                     PIN_MODE_ALTERNATE(GPIOA_MPU_SCK) |    \
                                     PIN_MODE_ALTERNATE(GPIOA_MPU_MISO) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_MPU_MOSI) |   \
                                     PIN_MODE_INPUT(GPIOA_SONAR) |          \
                                     PIN_MODE_ALTERNATE(GPIOA_UART1_TX) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_UART1_RX) |   \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DM) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_OTG_FS_DP) |  \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_MODEM_CS))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_SERVO_OUT_6) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_SERVO_OUT_5) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_SERVO_OUT_4) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_SERVO_OUT_3) |\
                                     PIN_OTYPE_PUSHPULL(GPIOA_MPU_CS) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_MPU_SCK) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOA_MPU_MISO) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_MPU_MOSI) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SONAR) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART1_TX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_UART1_RX) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DM) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_OTG_FS_DP) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_MODEM_CS))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_HIGH(GPIOA_SERVO_OUT_6) |   \
                                     PIN_OSPEED_HIGH(GPIOA_SERVO_OUT_5) |   \
                                     PIN_OSPEED_HIGH(GPIOA_SERVO_OUT_4) |   \
                                     PIN_OSPEED_HIGH(GPIOA_SERVO_OUT_3) |   \
                                     PIN_OSPEED_HIGH(GPIOA_MPU_CS) |        \
                                     PIN_OSPEED_HIGH(GPIOA_MPU_SCK) |       \
                                     PIN_OSPEED_HIGH(GPIOA_MPU_MISO) |      \
                                     PIN_OSPEED_HIGH(GPIOA_MPU_MOSI) |      \
                                     PIN_OSPEED_HIGH(GPIOA_SONAR) |         \
                                     PIN_OSPEED_HIGH(GPIOA_UART1_TX) |      \
                                     PIN_OSPEED_HIGH(GPIOA_UART1_RX) |      \
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_DM) |     \
                                     PIN_OSPEED_HIGH(GPIOA_OTG_FS_DP) |     \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_HIGH(GPIOA_MODEM_CS))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_PULLUP(GPIOA_SERVO_OUT_6) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SERVO_OUT_5) |\
                                     PIN_PUPDR_PULLDOWN(GPIOA_SERVO_OUT_4) |\
                                     PIN_PUPDR_PULLDOWN(GPIOA_SERVO_OUT_3) |\
                                     PIN_PUPDR_FLOATING(GPIOA_MPU_CS) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_MPU_SCK) |    \
                                     PIN_PUPDR_FLOATING(GPIOA_MPU_MISO) |   \
                                     PIN_PUPDR_FLOATING(GPIOA_MPU_MOSI) |   \
                                     PIN_PUPDR_PULLUP(GPIOA_SONAR) |        \
                                     PIN_PUPDR_PULLUP(GPIOA_UART1_TX) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_UART1_RX) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_OTG_FS_DM) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_OTG_FS_DP) |    \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLUP(GPIOA_SWCLK) |        \
                                     PIN_PUPDR_PULLUP(GPIOA_MODEM_CS))
#define VAL_GPIOA_ODR               (PIN_ODR_HIGH(GPIOA_SERVO_OUT_6) |      \
                                     PIN_ODR_HIGH(GPIOA_SERVO_OUT_5) |      \
                                     PIN_ODR_HIGH(GPIOA_SERVO_OUT_4) |      \
                                     PIN_ODR_HIGH(GPIOA_SERVO_OUT_3) |      \
                                     PIN_ODR_HIGH(GPIOA_MPU_CS) |           \
                                     PIN_ODR_HIGH(GPIOA_MPU_SCK) |          \
                                     PIN_ODR_HIGH(GPIOA_MPU_MISO) |         \
                                     PIN_ODR_HIGH(GPIOA_MPU_MOSI) |         \
                                     PIN_ODR_HIGH(GPIOA_SONAR) |            \
                                     PIN_ODR_HIGH(GPIOA_UART1_TX) |         \
                                     PIN_ODR_HIGH(GPIOA_UART1_RX) |         \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DM) |        \
                                     PIN_ODR_HIGH(GPIOA_OTG_FS_DP) |        \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_HIGH(GPIOA_MODEM_CS))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_SERVO_OUT_6, 1U) |   \
                                     PIN_AFIO_AF(GPIOA_SERVO_OUT_5, 1U) |   \
                                     PIN_AFIO_AF(GPIOA_SERVO_OUT_4, 1U) |   \
                                     PIN_AFIO_AF(GPIOA_SERVO_OUT_3, 1U) |   \
                                     PIN_AFIO_AF(GPIOA_MPU_CS, 0U) |        \
                                     PIN_AFIO_AF(GPIOA_MPU_SCK, 5U) |       \
                                     PIN_AFIO_AF(GPIOA_MPU_MISO, 5U) |      \
                                     PIN_AFIO_AF(GPIOA_MPU_MOSI, 5U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_SONAR, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_UART1_TX, 7U) |      \
                                     PIN_AFIO_AF(GPIOA_UART1_RX, 7U) |      \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DM, 10U) |    \
                                     PIN_AFIO_AF(GPIOA_OTG_FS_DP, 10U) |    \
                                     PIN_AFIO_AF(GPIOA_SWDIO, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_SWCLK, 0U) |         \
                                     PIN_AFIO_AF(GPIOA_MODEM_CS, 6U))

/*
 * GPIOB setup:
 *
 * PB0  - SERVO_OUT_1               (alternate 2).
 * PB1  - SERVO_OUT_2               (alternate 2).
 * PB2  - BOOT0                     (input pullup).
 * PB3  - FLASH_CS                  (output pushpull maximum).
 * PB4  - LED_WARN                  (output pushpull maximum).
 * PB5  - LED_STAT                  (output pushpull maximum).
 * PB6  - PIN6                      (input pullup).
 * PB7  - MAG_DRDY                  (input pulldown).
 * PB8  - MAG_BAR_SCL               (alternate 4).
 * PB9  - MAG_BAR_SDA               (alternate 4).
 * PB10 - FLEXI_SCL                 (alternate 4).
 * PB11 - FLEXI_SDA                 (alternate 4).
 * PB12 - INPUT_PIN_3               (input pullup).
 * PB13 - INPUT_PIN_4               (input pullup).
 * PB14 - SERVO_IN_1                (alternate 9).
 * PB15 - SERVO_IN_2                (alternate 9).
 */
#define VAL_GPIOB_MODER             (PIN_MODE_ALTERNATE(GPIOB_SERVO_OUT_1) |\
                                     PIN_MODE_ALTERNATE(GPIOB_SERVO_OUT_2) |\
                                     PIN_MODE_INPUT(GPIOB_BOOT0) |          \
                                     PIN_MODE_OUTPUT(GPIOB_FLASH_CS) |      \
                                     PIN_MODE_OUTPUT(GPIOB_LED_WARN) |      \
                                     PIN_MODE_OUTPUT(GPIOB_LED_STAT) |      \
                                     PIN_MODE_INPUT(GPIOB_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOB_MAG_DRDY) |       \
                                     PIN_MODE_ALTERNATE(GPIOB_MAG_BAR_SCL) |\
                                     PIN_MODE_ALTERNATE(GPIOB_MAG_BAR_SDA) |\
                                     PIN_MODE_ALTERNATE(GPIOB_FLEXI_SCL) |  \
                                     PIN_MODE_ALTERNATE(GPIOB_FLEXI_SDA) |  \
                                     PIN_MODE_INPUT(GPIOB_INPUT_PIN_3) |    \
                                     PIN_MODE_INPUT(GPIOB_INPUT_PIN_4) |    \
                                     PIN_MODE_ALTERNATE(GPIOB_SERVO_IN_1) | \
                                     PIN_MODE_ALTERNATE(GPIOB_SERVO_IN_2))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_SERVO_OUT_1) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_SERVO_OUT_2) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_BOOT0) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOB_FLASH_CS) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LED_WARN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_LED_STAT) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_MAG_DRDY) |   \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_MAG_BAR_SCL) |\
                                     PIN_OTYPE_OPENDRAIN(GPIOB_MAG_BAR_SDA) |\
                                     PIN_OTYPE_OPENDRAIN(GPIOB_FLEXI_SCL) | \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_FLEXI_SDA) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_INPUT_PIN_3) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_INPUT_PIN_4) |\
                                     PIN_OTYPE_PUSHPULL(GPIOB_SERVO_IN_1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_SERVO_IN_2))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_HIGH(GPIOB_SERVO_OUT_1) |   \
                                     PIN_OSPEED_HIGH(GPIOB_SERVO_OUT_2) |   \
                                     PIN_OSPEED_HIGH(GPIOB_BOOT0) |         \
                                     PIN_OSPEED_HIGH(GPIOB_FLASH_CS) |      \
                                     PIN_OSPEED_HIGH(GPIOB_LED_WARN) |      \
                                     PIN_OSPEED_HIGH(GPIOB_LED_STAT) |      \
                                     PIN_OSPEED_HIGH(GPIOB_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOB_MAG_DRDY) |      \
                                     PIN_OSPEED_HIGH(GPIOB_MAG_BAR_SCL) |   \
                                     PIN_OSPEED_HIGH(GPIOB_MAG_BAR_SDA) |   \
                                     PIN_OSPEED_HIGH(GPIOB_FLEXI_SCL) |     \
                                     PIN_OSPEED_HIGH(GPIOB_FLEXI_SDA) |     \
                                     PIN_OSPEED_HIGH(GPIOB_INPUT_PIN_3) |   \
                                     PIN_OSPEED_HIGH(GPIOB_INPUT_PIN_4) |   \
                                     PIN_OSPEED_HIGH(GPIOB_SERVO_IN_1) |    \
                                     PIN_OSPEED_HIGH(GPIOB_SERVO_IN_2))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOB_SERVO_OUT_1) |\
                                     PIN_PUPDR_PULLDOWN(GPIOB_SERVO_OUT_2) |\
                                     PIN_PUPDR_PULLUP(GPIOB_BOOT0) |        \
                                     PIN_PUPDR_PULLUP(GPIOB_FLASH_CS) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_LED_WARN) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_LED_STAT) |     \
                                     PIN_PUPDR_PULLUP(GPIOB_PIN6) |         \
                                     PIN_PUPDR_PULLDOWN(GPIOB_MAG_DRDY) |   \
                                     PIN_PUPDR_PULLUP(GPIOB_MAG_BAR_SCL) |  \
                                     PIN_PUPDR_PULLUP(GPIOB_MAG_BAR_SDA) |  \
                                     PIN_PUPDR_PULLUP(GPIOB_FLEXI_SCL) |    \
                                     PIN_PUPDR_PULLUP(GPIOB_FLEXI_SDA) |    \
                                     PIN_PUPDR_PULLUP(GPIOB_INPUT_PIN_3) |  \
                                     PIN_PUPDR_PULLUP(GPIOB_INPUT_PIN_4) |  \
                                     PIN_PUPDR_PULLDOWN(GPIOB_SERVO_IN_1) | \
                                     PIN_PUPDR_PULLDOWN(GPIOB_SERVO_IN_2))
#define VAL_GPIOB_ODR               (PIN_ODR_HIGH(GPIOB_SERVO_OUT_1) |      \
                                     PIN_ODR_HIGH(GPIOB_SERVO_OUT_2) |      \
                                     PIN_ODR_HIGH(GPIOB_BOOT0) |            \
                                     PIN_ODR_HIGH(GPIOB_FLASH_CS) |         \
                                     PIN_ODR_LOW(GPIOB_LED_WARN) |          \
                                     PIN_ODR_LOW(GPIOB_LED_STAT) |          \
                                     PIN_ODR_HIGH(GPIOB_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOB_MAG_DRDY) |         \
                                     PIN_ODR_HIGH(GPIOB_MAG_BAR_SCL) |      \
                                     PIN_ODR_HIGH(GPIOB_MAG_BAR_SDA) |      \
                                     PIN_ODR_HIGH(GPIOB_FLEXI_SCL) |        \
                                     PIN_ODR_HIGH(GPIOB_FLEXI_SDA) |        \
                                     PIN_ODR_HIGH(GPIOB_INPUT_PIN_3) |      \
                                     PIN_ODR_HIGH(GPIOB_INPUT_PIN_4) |      \
                                     PIN_ODR_HIGH(GPIOB_SERVO_IN_1) |       \
                                     PIN_ODR_HIGH(GPIOB_SERVO_IN_2))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_SERVO_OUT_1, 2U) |   \
                                     PIN_AFIO_AF(GPIOB_SERVO_OUT_2, 2U) |   \
                                     PIN_AFIO_AF(GPIOB_BOOT0, 0U) |         \
                                     PIN_AFIO_AF(GPIOB_FLASH_CS, 0U) |      \
                                     PIN_AFIO_AF(GPIOB_LED_WARN, 0U) |      \
                                     PIN_AFIO_AF(GPIOB_LED_STAT, 0U) |      \
                                     PIN_AFIO_AF(GPIOB_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOB_MAG_DRDY, 0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_MAG_BAR_SCL, 4U) |   \
                                     PIN_AFIO_AF(GPIOB_MAG_BAR_SDA, 4U) |   \
                                     PIN_AFIO_AF(GPIOB_FLEXI_SCL, 4U) |     \
                                     PIN_AFIO_AF(GPIOB_FLEXI_SDA, 4U) |     \
                                     PIN_AFIO_AF(GPIOB_INPUT_PIN_3, 0U) |   \
                                     PIN_AFIO_AF(GPIOB_INPUT_PIN_4, 0U) |   \
                                     PIN_AFIO_AF(GPIOB_SERVO_IN_1, 9U) |    \
                                     PIN_AFIO_AF(GPIOB_SERVO_IN_2, 9U))

/*
 * GPIOC setup:
 *
 * PC0  - SBUS_INV                  (output pushpull maximum).
 * PC1  - CURR_ANA                  (analog).
 * PC2  - VOLT_ANA                  (analog).
 * PC3  - MODEM_FREQ                (input pulldown).
 * PC4  - MPU_INT                   (input pulldown).
 * PC5  - VBUS_SEN                  (input pullup).
 * PC6  - SERVO_IN_3                (alternate 3).
 * PC7  - SERVO_IN_4                (alternate 3).
 * PC8  - SERVO_IN_5                (alternate 3).
 * PC9  - SERVO_IN_6                (alternate 3).
 * PC10 - MODEM_FLASH_SCK           (alternate 6).
 * PC11 - MODEM_FLASH_MISO          (alternate 6).
 * PC12 - MODEM_FLASH_MOSI          (alternate 6).
 * PC13 - PIN13                     (input pullup).
 * PC14 - PIN14                     (input pullup).
 * PC15 - PIN15                     (input pullup).
 */
#define VAL_GPIOC_MODER             (PIN_MODE_OUTPUT(GPIOC_SBUS_INV) |      \
                                     PIN_MODE_ANALOG(GPIOC_CURR_ANA) |      \
                                     PIN_MODE_ANALOG(GPIOC_VOLT_ANA) |      \
                                     PIN_MODE_INPUT(GPIOC_MODEM_FREQ) |     \
                                     PIN_MODE_INPUT(GPIOC_MPU_INT) |        \
                                     PIN_MODE_INPUT(GPIOC_VBUS_SEN) |       \
                                     PIN_MODE_ALTERNATE(GPIOC_SERVO_IN_3) | \
                                     PIN_MODE_ALTERNATE(GPIOC_SERVO_IN_4) | \
                                     PIN_MODE_ALTERNATE(GPIOC_SERVO_IN_5) | \
                                     PIN_MODE_ALTERNATE(GPIOC_SERVO_IN_6) | \
                                     PIN_MODE_ALTERNATE(GPIOC_MODEM_FLASH_SCK) |\
                                     PIN_MODE_ALTERNATE(GPIOC_MODEM_FLASH_MISO) |\
                                     PIN_MODE_ALTERNATE(GPIOC_MODEM_FLASH_MOSI) |\
                                     PIN_MODE_INPUT(GPIOC_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOC_PIN15))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_SBUS_INV) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_CURR_ANA) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_VOLT_ANA) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_MODEM_FREQ) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_MPU_INT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_VBUS_SEN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SERVO_IN_3) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SERVO_IN_4) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SERVO_IN_5) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_SERVO_IN_6) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_MODEM_FLASH_SCK) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_MODEM_FLASH_MISO) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_MODEM_FLASH_MOSI) |\
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN15))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_HIGH(GPIOC_SBUS_INV) |      \
                                     PIN_OSPEED_HIGH(GPIOC_CURR_ANA) |      \
                                     PIN_OSPEED_HIGH(GPIOC_VOLT_ANA) |      \
                                     PIN_OSPEED_HIGH(GPIOC_MODEM_FREQ) |    \
                                     PIN_OSPEED_HIGH(GPIOC_MPU_INT) |       \
                                     PIN_OSPEED_HIGH(GPIOC_VBUS_SEN) |      \
                                     PIN_OSPEED_HIGH(GPIOC_SERVO_IN_3) |    \
                                     PIN_OSPEED_HIGH(GPIOC_SERVO_IN_4) |    \
                                     PIN_OSPEED_HIGH(GPIOC_SERVO_IN_5) |    \
                                     PIN_OSPEED_HIGH(GPIOC_SERVO_IN_6) |    \
                                     PIN_OSPEED_HIGH(GPIOC_MODEM_FLASH_SCK) |\
                                     PIN_OSPEED_HIGH(GPIOC_MODEM_FLASH_MISO) |\
                                     PIN_OSPEED_HIGH(GPIOC_MODEM_FLASH_MOSI) |\
                                     PIN_OSPEED_HIGH(GPIOC_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOC_PIN15))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_PULLUP(GPIOC_SBUS_INV) |     \
                                     PIN_PUPDR_PULLUP(GPIOC_CURR_ANA) |     \
                                     PIN_PUPDR_PULLUP(GPIOC_VOLT_ANA) |     \
                                     PIN_PUPDR_PULLDOWN(GPIOC_MODEM_FREQ) | \
                                     PIN_PUPDR_PULLDOWN(GPIOC_MPU_INT) |    \
                                     PIN_PUPDR_PULLUP(GPIOC_VBUS_SEN) |     \
                                     PIN_PUPDR_PULLDOWN(GPIOC_SERVO_IN_3) | \
                                     PIN_PUPDR_PULLDOWN(GPIOC_SERVO_IN_4) | \
                                     PIN_PUPDR_PULLDOWN(GPIOC_SERVO_IN_5) | \
                                     PIN_PUPDR_PULLDOWN(GPIOC_SERVO_IN_6) | \
                                     PIN_PUPDR_PULLUP(GPIOC_MODEM_FLASH_SCK) |\
                                     PIN_PUPDR_PULLUP(GPIOC_MODEM_FLASH_MISO) |\
                                     PIN_PUPDR_PULLUP(GPIOC_MODEM_FLASH_MOSI) |\
                                     PIN_PUPDR_PULLUP(GPIOC_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOC_PIN15))
#define VAL_GPIOC_ODR               (PIN_ODR_LOW(GPIOC_SBUS_INV) |          \
                                     PIN_ODR_HIGH(GPIOC_CURR_ANA) |         \
                                     PIN_ODR_HIGH(GPIOC_VOLT_ANA) |         \
                                     PIN_ODR_HIGH(GPIOC_MODEM_FREQ) |       \
                                     PIN_ODR_HIGH(GPIOC_MPU_INT) |          \
                                     PIN_ODR_HIGH(GPIOC_VBUS_SEN) |         \
                                     PIN_ODR_HIGH(GPIOC_SERVO_IN_3) |       \
                                     PIN_ODR_HIGH(GPIOC_SERVO_IN_4) |       \
                                     PIN_ODR_HIGH(GPIOC_SERVO_IN_5) |       \
                                     PIN_ODR_HIGH(GPIOC_SERVO_IN_6) |       \
                                     PIN_ODR_HIGH(GPIOC_MODEM_FLASH_SCK) |  \
                                     PIN_ODR_HIGH(GPIOC_MODEM_FLASH_MISO) | \
                                     PIN_ODR_HIGH(GPIOC_MODEM_FLASH_MOSI) | \
                                     PIN_ODR_HIGH(GPIOC_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOC_PIN15))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_SBUS_INV, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_CURR_ANA, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_VOLT_ANA, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_MODEM_FREQ, 0U) |    \
                                     PIN_AFIO_AF(GPIOC_MPU_INT, 0U) |       \
                                     PIN_AFIO_AF(GPIOC_VBUS_SEN, 0U) |      \
                                     PIN_AFIO_AF(GPIOC_SERVO_IN_3, 3U) |    \
                                     PIN_AFIO_AF(GPIOC_SERVO_IN_4, 3U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_SERVO_IN_5, 3U) |    \
                                     PIN_AFIO_AF(GPIOC_SERVO_IN_6, 3U) |    \
                                     PIN_AFIO_AF(GPIOC_MODEM_FLASH_SCK, 6U) |\
                                     PIN_AFIO_AF(GPIOC_MODEM_FLASH_MISO, 6U) |\
                                     PIN_AFIO_AF(GPIOC_MODEM_FLASH_MOSI, 6U) |\
                                     PIN_AFIO_AF(GPIOC_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOC_PIN15, 0U))

/*
 * GPIOD setup:
 *
 * PD0  - OSC_IN                    (input pullup).
 * PD1  - OSC_OUT                   (input pullup).
 * PD2  - MODEM_IRQ                 (input pullup).
 * PD3  - PIN3                      (input pullup).
 * PD4  - PIN4                      (input pullup).
 * PD5  - PIN5                      (input pullup).
 * PD6  - PIN6                      (input pullup).
 * PD7  - PIN7                      (input pullup).
 * PD8  - PIN8                      (input pullup).
 * PD9  - PIN9                      (input pullup).
 * PD10 - PIN10                     (input pullup).
 * PD11 - PIN11                     (input pullup).
 * PD12 - PIN12                     (input pullup).
 * PD13 - PIN13                     (input pullup).
 * PD14 - PIN14                     (input pullup).
 * PD15 - PIN15                     (input pullup).
 */
#define VAL_GPIOD_MODER             (PIN_MODE_INPUT(GPIOD_OSC_IN) |         \
                                     PIN_MODE_INPUT(GPIOD_OSC_OUT) |        \
                                     PIN_MODE_INPUT(GPIOD_MODEM_IRQ) |      \
                                     PIN_MODE_INPUT(GPIOD_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOD_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOD_OSC_IN) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOD_OSC_OUT) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOD_MODEM_IRQ) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_OSPEED_HIGH(GPIOD_OSC_IN) |        \
                                     PIN_OSPEED_HIGH(GPIOD_OSC_OUT) |       \
                                     PIN_OSPEED_HIGH(GPIOD_MODEM_IRQ) |     \
                                     PIN_OSPEED_HIGH(GPIOD_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOD_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_PUPDR_PULLUP(GPIOD_OSC_IN) |       \
                                     PIN_PUPDR_PULLUP(GPIOD_OSC_OUT) |      \
                                     PIN_PUPDR_PULLUP(GPIOD_MODEM_IRQ) |    \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_ODR_HIGH(GPIOD_OSC_IN) |           \
                                     PIN_ODR_HIGH(GPIOD_OSC_OUT) |          \
                                     PIN_ODR_HIGH(GPIOD_MODEM_IRQ) |        \
                                     PIN_ODR_HIGH(GPIOD_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOD_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_AFIO_AF(GPIOD_OSC_IN, 0U) |        \
                                     PIN_AFIO_AF(GPIOD_OSC_OUT, 0U) |       \
                                     PIN_AFIO_AF(GPIOD_MODEM_IRQ, 0U) |     \
                                     PIN_AFIO_AF(GPIOD_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN7, 0U))
#define VAL_GPIOD_AFRH              (PIN_AFIO_AF(GPIOD_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOD_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOD_PIN15, 0U))

/*
 * GPIOE setup:
 *
 * PE0  - PIN0                      (input pullup).
 * PE1  - PIN1                      (input pullup).
 * PE2  - PIN2                      (input pullup).
 * PE3  - PIN3                      (output pushpull maximum).
 * PE4  - PIN4                      (input pullup).
 * PE5  - PIN5                      (input pullup).
 * PE6  - PIN6                      (input pullup).
 * PE7  - PIN7                      (input pullup).
 * PE8  - PIN8                      (input pullup).
 * PE9  - PIN9                      (input pullup).
 * PE10 - PIN10                     (input pullup).
 * PE11 - PIN11                     (input pullup).
 * PE12 - PIN12                     (input pullup).
 * PE13 - PIN13                     (input pullup).
 * PE14 - PIN14                     (input pullup).
 * PE15 - PIN15                     (input pullup).
 */
#define VAL_GPIOE_MODER             (PIN_MODE_INPUT(GPIOE_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN2) |           \
                                     PIN_MODE_OUTPUT(GPIOE_PIN3) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOE_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOE_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_OSPEED_HIGH(GPIOE_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOE_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_PUPDR_PULLUP(GPIOE_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_ODR_HIGH(GPIOE_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOE_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_AFIO_AF(GPIOE_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN7, 0U))
#define VAL_GPIOE_AFRH              (PIN_AFIO_AF(GPIOE_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOE_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOE_PIN15, 0U))

/*
 * GPIOF setup:
 *
 * PF0  - PIN0                      (input pullup).
 * PF1  - PIN1                      (input pullup).
 * PF2  - PIN2                      (input pullup).
 * PF3  - PIN3                      (input pullup).
 * PF4  - PIN4                      (input pullup).
 * PF5  - PIN5                      (input pullup).
 * PF6  - PIN6                      (input pullup).
 * PF7  - PIN7                      (input pullup).
 * PF8  - PIN8                      (input pullup).
 * PF9  - PIN9                      (input pullup).
 * PF10 - PIN10                     (input pullup).
 * PF11 - PIN11                     (input pullup).
 * PF12 - PIN12                     (input pullup).
 * PF13 - PIN13                     (input pullup).
 * PF14 - PIN14                     (input pullup).
 * PF15 - PIN15                     (input pullup).
 */
#define VAL_GPIOF_MODER             (PIN_MODE_INPUT(GPIOF_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOF_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOF_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_OSPEED_HIGH(GPIOF_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOF_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_PUPDR_PULLUP(GPIOF_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_ODR_HIGH(GPIOF_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOF_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_AFIO_AF(GPIOF_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN7, 0U))
#define VAL_GPIOF_AFRH              (PIN_AFIO_AF(GPIOF_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOF_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOF_PIN15, 0U))

/*
 * GPIOG setup:
 *
 * PG0  - PIN0                      (input pullup).
 * PG1  - PIN1                      (input pullup).
 * PG2  - PIN2                      (input pullup).
 * PG3  - PIN3                      (input pullup).
 * PG4  - PIN4                      (input pullup).
 * PG5  - PIN5                      (input pullup).
 * PG6  - PIN6                      (input pullup).
 * PG7  - PIN7                      (input pullup).
 * PG8  - PIN8                      (input pullup).
 * PG9  - PIN9                      (input pullup).
 * PG10 - PIN10                     (input pullup).
 * PG11 - PIN11                     (input pullup).
 * PG12 - PIN12                     (input pullup).
 * PG13 - PIN13                     (input pullup).
 * PG14 - PIN14                     (input pullup).
 * PG15 - PIN15                     (input pullup).
 */
#define VAL_GPIOG_MODER             (PIN_MODE_INPUT(GPIOG_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOG_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOG_PIN15))
#define VAL_GPIOG_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOG_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOG_PIN15))
#define VAL_GPIOG_OSPEEDR           (PIN_OSPEED_HIGH(GPIOG_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOG_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_PUPDR             (PIN_PUPDR_PULLUP(GPIOG_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOG_PIN15))
#define VAL_GPIOG_ODR               (PIN_ODR_HIGH(GPIOG_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOG_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOG_PIN15))
#define VAL_GPIOG_AFRL              (PIN_AFIO_AF(GPIOG_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN7, 0U))
#define VAL_GPIOG_AFRH              (PIN_AFIO_AF(GPIOG_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOG_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOG_PIN15, 0U))

/*
 * GPIOH setup:
 *
 * PH0  - PIN0                      (input pullup).
 * PH1  - PIN1                      (input pullup).
 * PH2  - PIN2                      (input pullup).
 * PH3  - PIN3                      (input pullup).
 * PH4  - PIN4                      (input pullup).
 * PH5  - PIN5                      (input pullup).
 * PH6  - PIN6                      (input pullup).
 * PH7  - PIN7                      (input pullup).
 * PH8  - PIN8                      (input pullup).
 * PH9  - PIN9                      (input pullup).
 * PH10 - PIN10                     (input pullup).
 * PH11 - PIN11                     (input pullup).
 * PH12 - PIN12                     (input pullup).
 * PH13 - PIN13                     (input pullup).
 * PH14 - PIN14                     (input pullup).
 * PH15 - PIN15                     (input pullup).
 */
#define VAL_GPIOH_MODER             (PIN_MODE_INPUT(GPIOH_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOH_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOH_PIN15))
#define VAL_GPIOH_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOH_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOH_PIN15))
#define VAL_GPIOH_OSPEEDR           (PIN_OSPEED_HIGH(GPIOH_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOH_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_PUPDR             (PIN_PUPDR_PULLUP(GPIOH_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOH_PIN15))
#define VAL_GPIOH_ODR               (PIN_ODR_HIGH(GPIOH_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOH_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOH_PIN15))
#define VAL_GPIOH_AFRL              (PIN_AFIO_AF(GPIOH_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN7, 0U))
#define VAL_GPIOH_AFRH              (PIN_AFIO_AF(GPIOH_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOH_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOH_PIN15, 0U))

/*
 * GPIOI setup:
 *
 * PI0  - PIN0                      (input pullup).
 * PI1  - PIN1                      (input pullup).
 * PI2  - PIN2                      (input pullup).
 * PI3  - PIN3                      (input pullup).
 * PI4  - PIN4                      (input pullup).
 * PI5  - PIN5                      (input pullup).
 * PI6  - PIN6                      (input pullup).
 * PI7  - PIN7                      (input pullup).
 * PI8  - PIN8                      (input pullup).
 * PI9  - PIN9                      (input pullup).
 * PI10 - PIN10                     (input pullup).
 * PI11 - PIN11                     (input pullup).
 * PI12 - PIN12                     (input pullup).
 * PI13 - PIN13                     (input pullup).
 * PI14 - PIN14                     (input pullup).
 * PI15 - PIN15                     (input pullup).
 */
#define VAL_GPIOI_MODER             (PIN_MODE_INPUT(GPIOI_PIN0) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN1) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN2) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN3) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN4) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN5) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN6) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN7) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN8) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN9) |           \
                                     PIN_MODE_INPUT(GPIOI_PIN10) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN11) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN12) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN13) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN14) |          \
                                     PIN_MODE_INPUT(GPIOI_PIN15))
#define VAL_GPIOI_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOI_PIN0) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN14) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOI_PIN15))
#define VAL_GPIOI_OSPEEDR           (PIN_OSPEED_HIGH(GPIOI_PIN0) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN1) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN2) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN3) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN4) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN5) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN6) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN7) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN8) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN9) |          \
                                     PIN_OSPEED_HIGH(GPIOI_PIN10) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN11) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN12) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN13) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN14) |         \
                                     PIN_OSPEED_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_PUPDR             (PIN_PUPDR_PULLUP(GPIOI_PIN0) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN1) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN2) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN3) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN4) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN5) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN6) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN7) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN8) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN9) |         \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN10) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN11) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN12) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN13) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN14) |        \
                                     PIN_PUPDR_PULLUP(GPIOI_PIN15))
#define VAL_GPIOI_ODR               (PIN_ODR_HIGH(GPIOI_PIN0) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN1) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN2) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN3) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN4) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN5) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN6) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN7) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN8) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN9) |             \
                                     PIN_ODR_HIGH(GPIOI_PIN10) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN11) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN12) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN13) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN14) |            \
                                     PIN_ODR_HIGH(GPIOI_PIN15))
#define VAL_GPIOI_AFRL              (PIN_AFIO_AF(GPIOI_PIN0, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN1, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN2, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN3, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN4, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN5, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN6, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN7, 0U))
#define VAL_GPIOI_AFRH              (PIN_AFIO_AF(GPIOI_PIN8, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN9, 0U) |          \
                                     PIN_AFIO_AF(GPIOI_PIN10, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN11, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN12, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN13, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN14, 0U) |         \
                                     PIN_AFIO_AF(GPIOI_PIN15, 0U))


#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
