/**********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : r_cellular_private.h
 * Description  : Configures the driver.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : xx.xx.xxxx 1.00     First Release
 *         : 02.09.2021 1.01     Fixed reset timing
 *         : 21.10.2021 1.02     Support for Azure RTOS
 *                               Support for GCC for Renesas GNURX Toolchain
 *         : 15.11.2021 1.03     Improved receiving behavior, removed socket buffers
 *         : 24.01.2022 1.04     R_CELLULAR_SetPSM and R_CELLULAR_SetEDRX have been added as new APIs
 *********************************************************************************************************************/

#ifndef CELLULAR_PRIVATE_H
#define CELLULAR_PRIVATE_H

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
#include "platform.h"
#endif

#include "r_cellular_config.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/
#define CELLULAR_SOCKET_IP_PROTOCOL_TCP     (6)
#define CELLULAR_SOCKET_IP_PROTOCOL_UDP     (17)
#define CELLULAR_SOCKET_IP_VERSION_4        (4)

#define CELLULAR_ATC_BUFF_SIZE              (300)
#define CELLULAR_ATC_RESPONSE_BUFF_SIZE     (2048)

#define CELLULAR_MAIN_TASK_BIT              (0x01 << 1)
#define CELLULAR_RECV_TASK_BIT              (0x01 << 2)

#define CELLULAR_TIME_WAIT_TASK_START       (10000)
#define CELLULAR_TIME_OUT_MAX_DELAY         (0xffffffff)

#define CELLULAR_MAX_AP_NAME_LENGTH         (64)
#define CELLULAR_MAX_AP_ID_LENGTH           (32)
#define CELLULAR_MAX_AP_PASS_LENGTH         (64)
#define CELLULAR_MAX_SIM_PASS_LENGTH        (8)

/* Convert a macro value to a string */
#define CELLULAR_STRING_MACRO(str)          #str
/* Call CELLULAR_STRING_MACRO */
#define CELLULAR_STRING_CONVERT(arg)        (CELLULAR_STRING_MACRO(arg))

#if (defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__) && defined(__LIT)) \
    || (defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL))
/* Converts IP address to 32 bits in little endian. */
#define CELLULAR_IP_ADDER_CONVERT(IPv4_0, IPv4_1, IPv4_2, IPv4_3)\
                                ( ( ( ( uint32_t ) ( IPv4_3 ) ) << 24UL ) |    \
                                ( ( ( uint32_t ) ( IPv4_2 ) ) << 16UL ) |    \
                                ( ( ( uint32_t ) ( IPv4_1 ) ) << 8UL ) |    \
                                ( ( uint32_t ) ( IPv4_0 ) ) )
#else
/* Convert IP address to 32 bits in big endian. */
#define CELLULAR_IP_ADDER_CONVERT(IPv4_0, IPv4_1, IPv4_2, IPv4_3)\
                                ( ( ( ( uint32_t ) ( IPv4_0 ) ) << 24UL ) |    \
                                ( ( ( uint32_t ) ( IPv4_1 ) ) << 16UL ) |    \
                                ( ( ( uint32_t ) ( IPv4_2 ) ) << 8UL ) |    \
                                ( ( uint32_t ) ( IPv4_3 ) ) )
#endif

#if defined(__CCRX__) || defined(__ICCRX__) || defined(__RX__)
/* Driver Type */
#define CELLULAR_IMPLEMENT_TYPE ('A')

/* PDR port macros. */
#define CELLULAR_SET_DDR(x, y)                 (CELLULAR_SET_DDR_PREPROC(x, y))
/* Set the port direction. */
#define CELLULAR_SET_DDR_PREPROC(x, y)         ((PORT ## x .PDR.BIT.B ## y))

/* PODR port macros. */
#define CELLULAR_SET_DR(x, y)                  (CELLULAR_SET_DR_PREPROC(x, y))
/* Set the port I/O. */
#define CELLULAR_SET_DR_PREPROC(x, y)          ((PORT ## x .PODR.BIT.B ## y))

#define CELLULAR_PIN_DIRECTION_MODE_OUTPUT     (1)

#define BUILD_TIME_ERROR_MESSAGE_MCU_NOT_SUPPORT    "your MCU/compiler does not support this driver."
#define BUILD_TIME_ERROR_MESSAGE_BOARD_NOT_SUPPORT  "your board does not support this driver, \
                                                    please define board name macro like BSP_BOARD_RX65N_CLOUD_KIT."
#elif defined(__CCRL__) || defined(__ICCRL78__) || defined(__RL)
/* Driver Type */
#define CELLULAR_IMPLEMENT_TYPE ('B')

/* PM port macros. */
#define CELLULAR_SET_DDR(x, y)                 (CELLULAR_SET_DDR_PREPROC(x, y))
/* Set the port direction. */
#define CELLULAR_SET_DDR_PREPROC(x, y)         ((PM ## x ## _bit.no ## y))

/* P port macros. */
#define CELLULAR_SET_DR(x, y)                  (CELLULAR_SET_DR_PREPROC(x, y))
/* Set the port I/O. */
#define CELLULAR_SET_DR_PREPROC(x, y)          ((P ## x ## _bit.no ## y))

#define CELLULAR_PIN_DIRECTION_MODE_OUTPUT     (0)
#endif

#endif /* CELLULAR_PRIVATE_H */
