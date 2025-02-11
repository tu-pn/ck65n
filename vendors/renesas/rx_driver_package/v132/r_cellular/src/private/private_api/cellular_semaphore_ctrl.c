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
 * File Name    : cellular_semaphore_ctrl.c
 * Description  : Function to manage semaphore functions.
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
#include "cellular_private_api.h"
#include "cellular_freertos.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/

/****************************************************************************
 * Function Name  @fn            cellular_semaphore_init
 ***************************************************************************/
e_cellular_err_t cellular_semaphore_init(st_cellular_ctrl_t * const p_ctrl)
{
    e_cellular_err_t ret = CELLULAR_SUCCESS;
    uint8_t semaphore_name[20] = {0};
    uint8_t count = 0;

    p_ctrl->at_semaphore = cellular_create_semaphore("atc_semaphore");
    if (NULL == p_ctrl->at_semaphore)
    {
        ret = CELLULAR_ERR_SEMAPHORE_INIT;
    }
    else
    {
        for (count = 0; count < p_ctrl->creatable_socket; count++ )
        {
            sprintf((char *)semaphore_name,     //(uint8_t * ) -> (char *)
                    "socket-%d_semaphore", count + CELLULAR_START_SOCKET_NUMBER);
            p_ctrl->p_socket_ctrl[count].rx_semaphore =
                    cellular_create_semaphore((const char *)semaphore_name);    //(uint8_t * ) -> (const char *)
            if (NULL == p_ctrl->p_socket_ctrl[count].rx_semaphore)
            {
                ret = CELLULAR_ERR_SEMAPHORE_INIT;
            }
        }

    }

    return ret;
}
/**********************************************************************************************************************
 * End of function cellular_semaphore_init
 *********************************************************************************************************************/
