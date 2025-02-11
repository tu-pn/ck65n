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
 * File Name    : cellular_closesocket.c
 * Description  : Function to close the socket.
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

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "cellular_private_api.h"
#include "cellular_freertos.h"
#include "at_command.h"

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

/************************************************************************
 * Function Name  @fn            cellular_closesocket
 ***********************************************************************/
e_cellular_err_t cellular_closesocket(st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no)
{
    e_cellular_err_t ret = CELLULAR_SUCCESS;

    if (CELLULAR_SOCKET_STATUS_CONNECTED ==
            p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].socket_status)
    {
        ret = cellular_shutdownsocket(p_ctrl, socket_no);
    }

    if (CELLULAR_SUCCESS == ret)
    {
        p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].ipversion = 0;
        p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].protocol = 0;
        p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].receive_count = 0;
        p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].receive_num = 0;
        p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].receive_unprocessed_size = 0;
        p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].socket_status
            = CELLULAR_SOCKET_STATUS_CLOSED;
        p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].port = 0;
        p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].ipaddr = 0;
        p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].receive_flg = CELLULAR_RECEIVE_FLAG_OFF;
    }

    return ret;
}
/**********************************************************************************************************************
 * End of function cellular_closesocket
 *********************************************************************************************************************/
