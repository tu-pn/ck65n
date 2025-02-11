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
 * File Name    : cellular_byte_pool_control.c
 * Description  : Manages the memory byte pool.
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : xx.xx.xxxx 1.00     First Release
 *         : 02.09.2021 1.01     Fixed reset timing
 *         : 21.10.2021 1.02     Support for Azure RTOS
 *                               Support for GCC for Renesas GNURX Toolchain
 *         : 15.11.2021 1.03     Improved receiving behavior, removed socket buffers
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "cellular_freertos.h"

#if BSP_CFG_RTOS_USED == (5)
/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
TX_BLOCK_POOL g_cellular_scoket_pool;
TX_BLOCK_POOL g_cellular_event_pool;
TX_BLOCK_POOL g_cellular_thread_pool;
TX_BLOCK_POOL g_cellular_semaphore_pool;

static uint8_t cellular_socket_pool[TOTAL_SOCKET_BLOCK_SIZE];
static uint8_t cellular_event_pool[TOTAL_EVENT_BLOCK_SIZE];
static uint8_t cellular_thread_pool[TOTAL_THREAD_BLOCK_SIZE];
static uint8_t cellular_semaphore_pool[TOTAL_SEMAPHORE_BLOCK_SIZE];

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

/*****************************************************************************************
 * Function Name  @fn            cellular_block_pool_create
 ****************************************************************************************/
e_cellular_err_t cellular_block_pool_create(void)
{
    e_cellular_err_t ret = CELLULAR_SUCCESS;
    UINT rtos_ret;

    rtos_ret = tx_block_pool_create(&g_cellular_scoket_pool, "socket pool",
            sizeof(st_cellular_socket_ctrl_t), cellular_socket_pool, TOTAL_SOCKET_BLOCK_SIZE);

    if (TX_SUCCESS == rtos_ret)
    {
        rtos_ret = tx_block_pool_create(&g_cellular_event_pool, "event pool",
                sizeof(TX_EVENT_FLAGS_GROUP), cellular_event_pool, TOTAL_EVENT_BLOCK_SIZE);
    }

    if (TX_SUCCESS == rtos_ret)
    {
        rtos_ret = tx_block_pool_create(&g_cellular_thread_pool, "thread pool",
                sizeof(TX_THREAD), cellular_thread_pool, TOTAL_THREAD_BLOCK_SIZE);
    }

    if (TX_SUCCESS == rtos_ret)
    {
        rtos_ret = tx_block_pool_create(&g_cellular_semaphore_pool, "semaphore pool",
                sizeof(TX_SEMAPHORE), cellular_semaphore_pool, TOTAL_SEMAPHORE_BLOCK_SIZE);
    }

    if (TX_SUCCESS != rtos_ret)
    {
        ret = CELLULAR_ERR_MEMORY_ALLOCATION;
    }


    return ret;
}
/**********************************************************************************************************************
 * End of function cellular_block_pool_create
 *********************************************************************************************************************/

/*****************************************************************************************
 * Function Name  @fn            cellular_block_pool_delete
 ****************************************************************************************/
e_cellular_err_t cellular_block_pool_delete(void)
{
    e_cellular_err_t ret = CELLULAR_SUCCESS;
    UINT rtos_ret;

    rtos_ret = tx_block_pool_delete(&g_cellular_scoket_pool);

    if (TX_SUCCESS == rtos_ret)
    {
        rtos_ret = tx_block_pool_delete(&g_cellular_event_pool);
    }

    if (TX_SUCCESS == rtos_ret)
    {
        rtos_ret = tx_block_pool_delete(&g_cellular_thread_pool);
    }

    if (TX_SUCCESS == rtos_ret)
    {
        rtos_ret = tx_block_pool_delete(&g_cellular_semaphore_pool);
    }

    if (TX_SUCCESS != rtos_ret)
    {
        ret = CELLULAR_ERR_MEMORY_ALLOCATION;
    }

    return ret;
}
/**********************************************************************************************************************
 * End of function cellular_block_pool_delete
 *********************************************************************************************************************/
#endif /* BSP_CFG_RTOS_USED == 5 */
