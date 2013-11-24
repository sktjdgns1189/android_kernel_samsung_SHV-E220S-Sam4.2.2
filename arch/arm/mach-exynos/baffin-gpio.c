/*
 *  linux/arch/arm/mach-exynos/baffin-gpio.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * EXYNOS - GPIO setting in set board
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/gpio.h>
#include <linux/serial_core.h>
#include <plat/devs.h>
#include <plat/gpio-cfg.h>
#include <plat/regs-serial.h>
#include <mach/gpio-midas.h>
#include <plat/cpu.h>
#include <mach/pmu.h>

struct gpio_init_data {
	uint num;
	uint cfg;
	uint val;
	uint pud;
	uint drv;
};

extern int s3c_gpio_slp_cfgpin(unsigned int pin, unsigned int config);
extern int s3c_gpio_slp_setpull_updown(unsigned int pin, unsigned int config);

/*
 * baffin GPIO Init Table
 */
static struct gpio_init_data baffin_init_gpios[] = {
	{EXYNOS4_GPA1(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPA1(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPD0(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1},
	{EXYNOS4_GPD0(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1},

	{EXYNOS4_GPD1(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* NFC_SDA_1.8V */
	{EXYNOS4_GPD1(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* NFC_SCL_1.8V */

	{EXYNOS4_GPD1(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* GSENSE_SDA_1.8V */
	{EXYNOS4_GPD1(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* GSENSE_SCL_1.8V */

#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4_GPX0(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
			S3C_GPIO_PULL_UP, S5P_GPIO_DRVSTR_LV1}, /* Home KEY */
#else
	{EXYNOS4_GPX0(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ONE,
			S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* Home KEY */
#endif
	{EXYNOS4_GPX0(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* PS_ALS_INT */
	{EXYNOS4_GPX0(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1},
	{EXYNOS4_GPX0(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1},
	{EXYNOS4_GPX0(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1},
	{EXYNOS4_GPX0(6), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1},

	{EXYNOS4_GPX0(7), S3C_GPIO_SFN(0xF), S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* AP_PMIC_IRQ */

	{EXYNOS4_GPX1(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1},
	{EXYNOS4_GPX1(7), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* NFC_IRQ */

	{EXYNOS4_GPX2(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1},
	{EXYNOS4_GPX2(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1},	/* NC */
	{EXYNOS4_GPX2(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* V_BUS_INT */
	{EXYNOS4_GPX2(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* FUEL_ALERT */
	{EXYNOS4_GPX2(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* WLAN_HOST_WAKEUP */
	{EXYNOS4_GPX2(6), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* BT_HOST_WAKEUP */
	{EXYNOS4_GPX2(7), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* nPower */

	{EXYNOS4_GPX3(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPX3(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* BT_WAKE */
	{EXYNOS4_GPX3(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1},
#ifdef CONFIG_MACH_BAFFIN
	{EXYNOS4_GPX3(7), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* EAR_GND_DET */
#endif
	{EXYNOS4212_GPJ0(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV4}, /* WLAN_EN */
	{EXYNOS4_GPK3(0), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_CLK */
	{EXYNOS4_GPK3(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_CMD */
	{EXYNOS4_GPK3(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPK3(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_D(0) */
	{EXYNOS4_GPK3(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_D(1) */
	{EXYNOS4_GPK3(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_D(2) */
	{EXYNOS4_GPK3(6), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* WLAN_SDIO_D(3) */

	{EXYNOS4212_GPM3(0), S3C_GPIO_OUTPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV1}, /* PMIC_DVS1 */
	{EXYNOS4_GPY0(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(4), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY0(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY1(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY1(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY1(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY1(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
	{EXYNOS4_GPY2(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */

	{EXYNOS4212_GPJ1(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV3}, /* CAM_MCLK */
	{EXYNOS4212_GPM2(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV3}, /* VTCAM_MCLK */

	{EXYNOS4_GPK2(0), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV4}, /* SD_CLK */
	{EXYNOS4_GPK2(1), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV4}, /* SD_CMD */
	{EXYNOS4_GPK2(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV4}, /* SD_nCD(NC) */
	{EXYNOS4_GPK2(3), S3C_GPIO_SFN(2), S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV4}, /* SD_DAT0 */
	{EXYNOS4_GPK2(4), S3C_GPIO_SFN(2), S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV4}, /* SD_DAT1 */
	{EXYNOS4_GPK2(5), S3C_GPIO_SFN(2), S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV4}, /* SD_DAT2 */
	{EXYNOS4_GPK2(6), S3C_GPIO_SFN(2), S3C_GPIO_SETPIN_NONE,
		S3C_GPIO_PULL_NONE, S5P_GPIO_DRVSTR_LV4}, /* SD_DAT3 */
#if defined(CONFIG_MACH_SUPERIOR_KOR_SKT)
	{EXYNOS4_GPF0(5), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
#endif
#if defined(CONFIG_MACH_SUPERIOR_KOR_SKT)
	{EXYNOS4_GPY2(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
#else
	{EXYNOS4_GPY2(2), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* VIB_ON */
#endif
	{EXYNOS4_GPY2(3), S3C_GPIO_INPUT, S3C_GPIO_SETPIN_ZERO,
		S3C_GPIO_PULL_DOWN, S5P_GPIO_DRVSTR_LV1}, /* NC */
};

/*
 * BAFFIN GPIO Sleep Table
 */
static unsigned int baffin_sleep_gpio_table[][3] = {
	{EXYNOS4_GPA0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* BT_UART_RXD */
	{EXYNOS4_GPA0(1),  S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, /* BT_UART_TXD */
	{EXYNOS4_GPA0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* BT_UART_CTS */
	{EXYNOS4_GPA0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_UP}, /* BT_UART_RTS */
	{EXYNOS4_GPA0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_UP}, /* GPS_UART_RXD */
	{EXYNOS4_GPA0(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_UP}, /* GPS_UART_TXD */
	{EXYNOS4_GPA0(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* GPS_UART_CTS */
	{EXYNOS4_GPA0(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* GPS_UART_RTS */

	{EXYNOS4_GPA1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* AP_RXD */
	{EXYNOS4_GPA1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* AP_TXD */
	{EXYNOS4_GPA1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* TSP_SDA_1.8V */
	{EXYNOS4_GPA1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* TSP_SCL_1.8V */
#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4_GPA1(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* AP_VIA_TXD_1.8V */
	{EXYNOS4_GPA1(5),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* AP_VIA_RXD_1.8V */
#else
	{EXYNOS4_GPA1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPA1(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif

	{EXYNOS4_GPB(0),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* CODEC_SDA_1.8V */
	{EXYNOS4_GPB(1),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* CODEC_SCL_1.8V */
	{EXYNOS4_GPB(2),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* MHL_DSCL_1.8V,NFC_SCL_1.8V */
	{EXYNOS4_GPB(3),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* MHL_DSDA_1.8V,NFC_SDA_1.8V */
	{EXYNOS4_GPB(4),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* CAM_SPI_SCLK */
	{EXYNOS4_GPB(5),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_UP}, /* CAM_SPI_SSN */
	{EXYNOS4_GPB(6),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* CAM_SPI_MISO */
	{EXYNOS4_GPB(7),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* CAM_SPI_MOSI */

	{EXYNOS4_GPC0(0),  S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, /* TDMB_PWR_EN */
	{EXYNOS4_GPC0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* LCD_2.2V_EN */
#if defined(CONFIG_MACH_BAFFIN_KOR_SKT) || defined(CONFIG_MACH_BAFFIN_KOR_KT) \
	|| defined(CONFIG_MACH_SUPERIOR_KOR_SKT)
	{EXYNOS4_GPC0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#else
	{EXYNOS4_GPC0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* AP_CP_WAKEUP_1.8V */
#endif
	{EXYNOS4_GPC0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPC0(4),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN}, /* TDMB_INT */

#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4_GPC1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* CP_RST_INDICATE_1.8V */
#else
	{EXYNOS4_GPC1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4_GPC1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* TDMB_SPI_CLK */
	{EXYNOS4_GPC1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* TDMB_SPI_CS */
	{EXYNOS4_GPC1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* TDMB_SPI_DI */
	{EXYNOS4_GPC1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* TDMB_SPI_DO */

	{EXYNOS4_GPD0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* VIBTONE_PWM */
	{EXYNOS4_GPD0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPD0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* AP_PMIC_SDA_1.8V */
	{EXYNOS4_GPD0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* AP_PMIC_SCL_1.8V */

	{EXYNOS4_GPD1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* 8M_CAM_SDA_1.8V */
	{EXYNOS4_GPD1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* 8M_CAM_SCL_1.8V */
	{EXYNOS4_GPD1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* GSENSE_SDA_1.8V */
	{EXYNOS4_GPD1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* GSENSE_SCL_1.8V */

	{EXYNOS4_GPF0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* RGB_SDA_1.8V_AP */
	{EXYNOS4_GPF0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* RGB_SCL_1.8V_AP */
	{EXYNOS4_GPF0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* GYRO_INT */
	{EXYNOS4_GPF0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF0(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* LCD_BL_EN */
	{EXYNOS4_GPF0(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC	*/
	{EXYNOS4_GPF0(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* OTG_EN */

	{EXYNOS4_GPF1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* OLED_ID */
	{EXYNOS4_GPF1(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_DOWN}, /* ACTIVE_STATE_HSIC */
	{EXYNOS4_GPF1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* VT_CAM_ID */
	{EXYNOS4_GPF1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* ISP_RESET */
	{EXYNOS4_GPF1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* FUEL_SCL_1.8V */
	{EXYNOS4_GPF1(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* FUEL_SDA_1.8V */
	{EXYNOS4_GPF1(6),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* PDA_ACTIVE */
	{EXYNOS4_GPF1(7),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* MICBIAS_EN */

	{EXYNOS4_GPF2(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* SUB_MICBIAS_EN */
	{EXYNOS4_GPF2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* MLCD_RST */
	{EXYNOS4_GPF2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* AP_CMC_INT */
#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4_GPF2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* AUTO_DFS */
	{EXYNOS4_GPF2(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* CP_RST_1.8V */
#else
	{EXYNOS4_GPF2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPF2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4_GPF2(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#if defined(CONFIG_MACH_SUPERIOR_KOR_SKT)
	{EXYNOS4_GPF2(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#else
	{EXYNOS4_GPF2(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* KEY_LED_CTRL */
#endif
	{EXYNOS4_GPF2(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPF3(0),  S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, /* LCD_DET */
	{EXYNOS4_GPF3(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* BUCK2_SEL */
	{EXYNOS4_GPF3(2),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* BUCK3_SEL */
	{EXYNOS4_GPF3(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* BUCK4_SEL */
	{EXYNOS4_GPF3(4),  S3C_GPIO_SLP_INPUT,  S3C_GPIO_PULL_DOWN}, /* MHL_RST */
	{EXYNOS4_GPF3(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* MHL_INT */

	{EXYNOS4_GPK0(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* NAND_CLK */
	{EXYNOS4_GPK0(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* NAND_CMD */
	{EXYNOS4_GPK0(2),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* eMMC_EN */
	{EXYNOS4_GPK0(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* NAND_D(0) */
	{EXYNOS4_GPK0(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* NAND_D(1) */
	{EXYNOS4_GPK0(5),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* NAND_D(2) */
	{EXYNOS4_GPK0(6),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* NAND_D(3) */

	{EXYNOS4_GPK1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPK1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPK1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPK1(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* NAND_D(4) */
	{EXYNOS4_GPK1(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* NAND_D(5) */
	{EXYNOS4_GPK1(5),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* NAND_D(6) */
	{EXYNOS4_GPK1(6),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* NAND_D(7) */

	{EXYNOS4_GPK2(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* T_FLASH_CLK */
	{EXYNOS4_GPK2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* T_FLASH_CMD */
	{EXYNOS4_GPK2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPK2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* T_FLASH_D(0) */
	{EXYNOS4_GPK2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* T_FLASH_D(1) */
	{EXYNOS4_GPK2(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* T_FLASH_D(2) */
	{EXYNOS4_GPK2(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* T_FLASH_D(3) */

	{EXYNOS4_GPK3(0),  S3C_GPIO_SLP_OUT0,  S3C_GPIO_PULL_NONE}, /* WLAN_SDIO_CLK */
	{EXYNOS4_GPK3(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* WLAN_SDIO_CMD */
	{EXYNOS4_GPK3(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPK3(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* WLAN_SDIO_D(0) */
	{EXYNOS4_GPK3(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* WLAN_SDIO_D(1) */
	{EXYNOS4_GPK3(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* WLAN_SDIO_D(2) */
	{EXYNOS4_GPK3(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* WLAN_SDIO_D(3) */

	{EXYNOS4_GPL0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4_GPL0(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* GPIO_FM34_PWDN */
#elif defined(CONFIG_MACH_SUPERIOR_KOR_SKT)
	{EXYNOS4_GPL0(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* LINEOUT_EN */
#else
	{EXYNOS4_GPL0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4_GPL0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
/*	{EXYNOS4_GPL0(5),  S3C_GPIO_SLP_OUT0,  S3C_GPIO_PULL_NONE}, */
	{EXYNOS4_GPL0(6),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE}, /* BT_EN */
/*	{EXYNOS4_GPL0(7),  S3C_GPIO_SLP_OUT0,  S3C_GPIO_PULL_NONE}, */

	{EXYNOS4_GPL1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
/*	{EXYNOS4_GPL1(2),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE}, */

	{EXYNOS4_GPL2(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* GYRO_DE */
	{EXYNOS4_GPL2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* GPS_nRST */
	{EXYNOS4_GPL2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* GPS_EN */
	{EXYNOS4_GPL2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPL2(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},  /* CMC221_CPU_RST */
	{EXYNOS4_GPL2(5),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE},  /* CMC_PMIC_PWRON */
	{EXYNOS4_GPL2(6),  S3C_GPIO_SLP_PREV,  S3C_GPIO_PULL_NONE}, /* NFC_EN */
	{EXYNOS4_GPL2(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NFC_FIRMWARE */

#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4_GPY0(0),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, /* DPRAM_CSN */
	{EXYNOS4_GPY0(1),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, /* VIA_DPRAM_CSN */
	{EXYNOS4_GPY0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY0(4),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, /* DPRAM_REN */
	{EXYNOS4_GPY0(5),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, /* DPRAM_WEN */
#else
	{EXYNOS4_GPY0(0),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, /* DPRAM_CSN */
	{EXYNOS4_GPY0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY0(4),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, /* DPRAM_REN */
	{EXYNOS4_GPY0(5),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, /* DPRAM_WEN */
#endif

#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4_GPY1(0),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, /* DPRAM_LBN */
	{EXYNOS4_GPY1(1),  S3C_GPIO_SLP_OUT1, S3C_GPIO_PULL_NONE}, /* DPRAM_UBN */
#else
	{EXYNOS4_GPY1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif

#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4_GPY1(2),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* VP_BP_N */
	{EXYNOS4_GPY1(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* VP_RST_N */
#else
	{EXYNOS4_GPY1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif

	{EXYNOS4_GPY2(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* TF_EN */
	{EXYNOS4_GPY2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#if defined(CONFIG_MACH_SUPERIOR_KOR_SKT)
	{EXYNOS4_GPY2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#else
	{EXYNOS4_GPY2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* VIB_ON */
#endif
	{EXYNOS4_GPY2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* MSENSE_SDA_1.8V */
	{EXYNOS4_GPY2(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* MSENSE_SCL_1.8V */

	{EXYNOS4_GPY3(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(0) */
	{EXYNOS4_GPY3(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(1) */
	{EXYNOS4_GPY3(2),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(2) */
	{EXYNOS4_GPY3(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(3) */
	{EXYNOS4_GPY3(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(4) */
	{EXYNOS4_GPY3(5),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(5) */
	{EXYNOS4_GPY3(6),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(6) */
	{EXYNOS4_GPY3(7),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(7) */

	{EXYNOS4_GPY4(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(8) */
	{EXYNOS4_GPY4(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(9) */
	{EXYNOS4_GPY4(2),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(10) */
	{EXYNOS4_GPY4(3),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(11) */
	{EXYNOS4_GPY4(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(12) */
	{EXYNOS4_GPY4(5),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* DPRAM_A(13) */
	{EXYNOS4_GPY4(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPY4(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4_GPY5(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(0) */
	{EXYNOS4_GPY5(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(1) */
	{EXYNOS4_GPY5(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(2) */
	{EXYNOS4_GPY5(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(3) */
	{EXYNOS4_GPY5(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(4) */
	{EXYNOS4_GPY5(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(5) */
	{EXYNOS4_GPY5(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(6) */
	{EXYNOS4_GPY5(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(7) */

	{EXYNOS4_GPY6(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(8) */
	{EXYNOS4_GPY6(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(9) */
	{EXYNOS4_GPY6(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(10) */
	{EXYNOS4_GPY6(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(11) */
	{EXYNOS4_GPY6(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(12) */
	{EXYNOS4_GPY6(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(13) */
	{EXYNOS4_GPY6(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(14) */
	{EXYNOS4_GPY6(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* DPRAM_D(15) */

	{EXYNOS4_GPZ(0),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* MM_I2S_CLK */
	{EXYNOS4_GPZ(1),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPZ(2),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* MM_I2S_SYNC */
	{EXYNOS4_GPZ(3),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* MM_I2S_DI */
	{EXYNOS4_GPZ(4),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* MM_I2S_DO */
	{EXYNOS4_GPZ(5),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4_GPZ(6),   S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	/* Exynos4212 specific gpio */
	{EXYNOS4212_GPJ0(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* WLAN_EN */
	{EXYNOS4212_GPJ0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPJ0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPJ0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* CMC_USB_DETECT(Cur NC) */
	{EXYNOS4212_GPJ0(4),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* CODEC_LDO_EN */
	{EXYNOS4212_GPJ0(5),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* PS_ALS_EN */
#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4212_GPJ0(6),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* LTE_VIA_UART_SEL */
#else
	{EXYNOS4212_GPJ0(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4212_GPJ0(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* MSENSE_INT */

#if defined(CONFIG_MACH_SUPERIOR_KOR_SKT)
	{EXYNOS4212_GPJ1(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* CAM_SW_EN */
#else
	{EXYNOS4212_GPJ1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
#if defined(CONFIG_MACH_SUPERIOR_KOR_SKT)
	{EXYNOS4212_GPJ1(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* TORCH_EN */
	{EXYNOS4212_GPJ1(2),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* TORCH_SET */
#else
	{EXYNOS4212_GPJ1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPJ1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4212_GPJ1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* CAM_MCLK */
	{EXYNOS4212_GPJ1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* MHL_WAKE_UP */

	{EXYNOS4212_GPM0(0),  S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, /* LED_VDD_EN */
	{EXYNOS4212_GPM0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* ISP_STANDBY */
	{EXYNOS4212_GPM0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* CAM_IO_EN */
	{EXYNOS4212_GPM0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* CAM_ISP_CORE_EN */
	{EXYNOS4212_GPM0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* CAM_AF_EN */
#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4212_GPM0(5),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* CP_BOOT_SEL_1.8V */
	{EXYNOS4212_GPM0(6),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* CP_ON */
#else
	{EXYNOS4212_GPM0(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM0(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4212_GPM0(7),  S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, /* CAM_SENSOR_CORE_EN */

#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4212_GPM1(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* VIA_PS_HOLD_OFF */
	{EXYNOS4212_GPM1(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* VIA_USB_OFF */
#else
	{EXYNOS4212_GPM1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4212_GPM1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* HW_REV0 */
	{EXYNOS4212_GPM1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* HW_REV1 */
	{EXYNOS4212_GPM1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* HW_REV2 */
	{EXYNOS4212_GPM1(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* HW_REV3 */
	{EXYNOS4212_GPM1(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* CAM_VT_nRST */

	{EXYNOS4212_GPM2(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* IF_PMIC_SDA_1.8V */
	{EXYNOS4212_GPM2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* IF_PMIC_SCL_1.8V */
	{EXYNOS4212_GPM2(2),  S3C_GPIO_SLP_OUT0, S3C_GPIO_PULL_NONE}, /* CAM_MCLK_VGA */
	{EXYNOS4212_GPM2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* TSP_nINT */
	{EXYNOS4212_GPM2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* SUSPEND_REQUEST_HSIC */

	{EXYNOS4212_GPM3(0),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* PMIC_DVS1 */
	{EXYNOS4212_GPM3(1),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* PMIC_DVS2 */
	{EXYNOS4212_GPM3(2),  S3C_GPIO_SLP_PREV, S3C_GPIO_PULL_NONE}, /* PMIC_DVS3 */
	{EXYNOS4212_GPM3(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM3(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM3(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC(SKT,KT),ISP_TXD(LGT) */
	{EXYNOS4212_GPM3(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* CMC_SPI_CLK_REQ */
	{EXYNOS4212_GPM3(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC(SKT,KT),ISP_RXD(LGT) */

#if defined(CONFIG_MACH_BAFFIN_KOR_LGT)
	{EXYNOS4212_GPM4(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* VP_SCL */
	{EXYNOS4212_GPM4(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_NONE}, /* VP_SDA */
#else
	{EXYNOS4212_GPM4(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
#endif
	{EXYNOS4212_GPM4(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* VT_CAM_SCL */
	{EXYNOS4212_GPM4(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* VT_CAM_SDA */
	{EXYNOS4212_GPM4(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPM4(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPV0(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV0(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPV1(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV1(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPV2(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV2(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPV3(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(2),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(3),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(4),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(5),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(6),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV3(7),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */

	{EXYNOS4212_GPV4(0),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
	{EXYNOS4212_GPV4(1),  S3C_GPIO_SLP_INPUT, S3C_GPIO_PULL_DOWN}, /* NC */
}; /* baffin_sleep_gpio_table */

struct baffin_sleep_table {
	unsigned int (*ptr)[3];
	int size;
};

#define GPIO_TABLE(_ptr) \
	{.ptr = _ptr, \
	.size = ARRAY_SIZE(_ptr)} \

 #define GPIO_TABLE_NULL \
	{.ptr = NULL, \
	.size = 0} \

static struct baffin_sleep_table baffin_sleep_table[] = {
	GPIO_TABLE(baffin_sleep_gpio_table),/* Rev0.0 (0x00) */
	GPIO_TABLE_NULL,
};

static void config_sleep_gpio_table(int array_size,
				    unsigned int (*gpio_table)[3])
{
	u32 i, gpio;

	for (i = 0; i < array_size; i++) {
		gpio = gpio_table[i][0];
		s3c_gpio_slp_cfgpin(gpio, gpio_table[i][1]);
		s3c_gpio_slp_setpull_updown(gpio, gpio_table[i][2]);
	}
}

/* To save power consumption, gpio pin set before enterling sleep */
void midas_config_sleep_gpio_table(void)
{
	int i;
	int index = min(ARRAY_SIZE(baffin_sleep_table), system_rev + 1);

	for (i = 0; i < index; i++) {
		if (baffin_sleep_table[i].ptr == NULL)
			continue;

		config_sleep_gpio_table(baffin_sleep_table[i].size,
				baffin_sleep_table[i].ptr);
	}
}

/* Intialize gpio set in midas board */
void midas_config_gpio_table(void)
{
	u32 i, gpio;

	printk(KERN_DEBUG "%s\n", __func__);

	for (i = 0; i < ARRAY_SIZE(baffin_init_gpios); i++) {
		gpio = baffin_init_gpios[i].num;
		if (gpio <= EXYNOS4212_GPV4(1)) {
			s3c_gpio_cfgpin(gpio, baffin_init_gpios[i].cfg);
			s3c_gpio_setpull(gpio, baffin_init_gpios[i].pud);

			if (baffin_init_gpios[i].val != S3C_GPIO_SETPIN_NONE)
				gpio_set_value(gpio, baffin_init_gpios[i].val);

			s5p_gpio_set_drvstr(gpio, baffin_init_gpios[i].drv);
		}
	}
}
