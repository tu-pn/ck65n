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
 * File Name    : r_cellular_sendsocket.c
 * Description  : Function to send data to a socket.
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
static int32_t cellular_send_data (st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no,
                                        const uint8_t * const p_data, const int32_t length, const uint32_t timeout_ms);
static uint32_t cellular_send_size_check (st_cellular_ctrl_t * const p_ctrl, const int32_t length,
                                            const int32_t complete_length);
static e_cellular_timeout_check_t cellular_tx_flag_check (st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no);
static e_cellular_timeout_check_t cellular_atc_response_chek (st_cellular_ctrl_t * const p_ctrl,
                                                                    const uint8_t socket_no);

/*************************************************************************************************
 * Function Name  @fn            R_CELLULAR_SendSocket
 ************************************************************************************************/
int32_t R_CELLULAR_SendSocket(st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no,
                    const uint8_t * const p_data, const int32_t length, const uint32_t timeout_ms)
{
    int32_t complete_length = 0;
    e_cellular_err_t ret = CELLULAR_SUCCESS;
    e_cellular_err_semaphore_t semaphore_ret = CELLULAR_SEMAPHORE_SUCCESS;

    if ((NULL == p_data) || (0 >= length) || (NULL == p_ctrl))
    {
        ret = CELLULAR_ERR_PARAMETER;
    }
    else
    {
        if (CELLULAR_SYSTEM_CLOSE == p_ctrl->system_state)
        {
            ret = CELLULAR_ERR_NOT_OPEN;
        }
        else if (CELLULAR_SYSTEM_OPEN == p_ctrl->system_state)
        {
            ret =  CELLULAR_ERR_NOT_CONNECT;
        }
        else
        {
            R_BSP_NOP();
        }
    }

    if (CELLULAR_SUCCESS == ret)
    {
        if ((CELLULAR_START_SOCKET_NUMBER > socket_no) || (p_ctrl->creatable_socket < socket_no))
        {
            ret = CELLULAR_ERR_PARAMETER;
        }
    }

    if (CELLULAR_SUCCESS == ret)
    {
        if ((CELLULAR_SOCKET_STATUS_CONNECTED !=
                        p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].socket_status))
        {
            ret = CELLULAR_ERR_SOCKET_NOT_READY;
        }
    }

    if (CELLULAR_SUCCESS == ret)
    {
        semaphore_ret = cellular_take_semaphore(p_ctrl->at_semaphore);
        if (CELLULAR_SEMAPHORE_SUCCESS != semaphore_ret)
        {
            ret = CELLULAR_ERR_OTHER_ATCOMMAND_RUNNING;
        }
    }

    if (CELLULAR_SUCCESS == ret)
    {
        complete_length = cellular_send_data(p_ctrl, socket_no, p_data, length, timeout_ms);
        cellular_give_semaphore(p_ctrl->at_semaphore);
        cellular_delay_task(1);
    }
    else
    {
        complete_length = ret;
    }

    if (CELLULAR_SUCCESS != ret)
    {
        complete_length = ret;
    }

    return complete_length;
}
/**********************************************************************************************************************
 * End of function R_CELLULAR_SendSocket
 *********************************************************************************************************************/

/*************************************************************************************************
 * Function Name  @fn            cellular_send_data
 * Description    @details       Send data to the module.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Socket number for sending data.
 *                @param[in]     p_data -
 *                                  Pointer to send data.
 *                @param[in]     length -
 *                                  Send data size.
 *                @param[in]     timeout_ms -
 *                                  timeout millisecond.
 * Return Value   @retval        More than 1 -
 *                                  Successfully sent data.
 *                @retval        CELLULAR_ERR_PARAMETER -
 *                                  Argument is abnormal.
 *                @retval        CELLULAR_ERR_SOCKET_NUM -
 *                                  No available socket.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 *                @retval        CELLULAR_ERR_OTHER_ATCOMMAND_RUNNING -
 *                                  Other AT commands are running.
 ************************************************************************************************/
static int32_t cellular_send_data(st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no,
                                    const uint8_t * const p_data, const int32_t length, const uint32_t timeout_ms)
{
    int32_t complete_length = 0;
    uint32_t send_size = 0;
    sci_err_t sci_ret = SCI_SUCCESS;
    e_cellular_err_t ret = CELLULAR_SUCCESS;
    e_cellular_timeout_check_t timeout = CELLULAR_NOT_TIMEOUT;

    st_cellular_socket_time_ctrl_t * const p_cellular_timeout_ctrl =
            &p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].cellular_tx_timeout_ctrl;

    cellular_timeout_init(p_cellular_timeout_ctrl, timeout_ms);

    while (complete_length < length)
    {
        if (CELLULAR_SOCKET_STATUS_CONNECTED !=
                p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].socket_status)
        {
            ret = CELLULAR_ERR_SOCKET_NOT_READY;
            break;
        }

        send_size = cellular_send_size_check(p_ctrl, length, complete_length);

        ret = atc_sqnssendext(p_ctrl, socket_no, send_size);
        if (CELLULAR_SUCCESS != ret)
        {
            break;
        }

        p_ctrl->sci_ctrl.tx_end_flg = CELLULAR_TX_END_FLAG_OFF;

        sci_ret = R_SCI_Send(p_ctrl->sci_ctrl.sci_hdl, (const uint8_t *)p_data + complete_length, send_size);
        if (SCI_SUCCESS != sci_ret)
        {
            ret = CELLULAR_ERR_MODULE_COM;
            break;
        }

        cellular_set_atc_number(p_ctrl, ATC_SQNSSENDEXT_END);

        timeout = cellular_tx_flag_check(p_ctrl, socket_no);
        if (CELLULAR_TIMEOUT != timeout)
        {
            timeout = cellular_atc_response_chek(p_ctrl, socket_no);
        }

        if (CELLULAR_TIMEOUT == timeout)
        {
            break;
        }

        complete_length += send_size;
    }

    if (CELLULAR_SUCCESS != ret)
    {
        complete_length = ret;
    }

    return complete_length;
}
/**********************************************************************************************************************
 * End of function cellular_send_data
 *********************************************************************************************************************/

/*************************************************************************************************
 * Function Name  @fn            cellular_send_size_check
 * Description    @details       Check the size of the data to be sent.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     length -
 *                                  Send data size.
 *                @param[in]     complete_length -
 *                                  Size of the completed transmission to the module.
 * Return Value   @retval        More than 1 -
 *                                  Successfully size check.
 ************************************************************************************************/
static uint32_t cellular_send_size_check(st_cellular_ctrl_t * const p_ctrl, const int32_t length,
                                            const int32_t complete_length)
{
    uint32_t send_size = 0;

    if ((length - complete_length) > p_ctrl->sci_ctrl.tx_buff_size)
    {
        send_size = p_ctrl->sci_ctrl.tx_buff_size;
    }
    else
    {
        send_size = (length - complete_length);
    }

    if (send_size > p_ctrl->sci_ctrl.tx_process_size)
    {
        send_size = p_ctrl->sci_ctrl.tx_process_size;
    }

    return send_size;
}
/**********************************************************************************************************************
 * End of function cellular_send_size_check
 *********************************************************************************************************************/

/*************************************************************************************************
 * Function Name  @fn            cellular_tx_flag_check
 * Description    @details       Wait for transmission completion flag.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Socket number for sending data.
 * Return Value   @retval        CELLULAR_NOT_TIMEOUT -
 *                                  Successfully flag check.
 *                @retval        CELLULAR_TIMEOUT -
 *                                  Time out.
 ************************************************************************************************/
static e_cellular_timeout_check_t cellular_tx_flag_check(st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no)
{
    e_cellular_timeout_check_t timeout = CELLULAR_NOT_TIMEOUT;

    st_cellular_socket_time_ctrl_t * const p_cellular_timeout_ctrl =
            &p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].cellular_tx_timeout_ctrl;

    while (1)
    {
        if (CELLULAR_TX_END_FLAG_ON == p_ctrl->sci_ctrl.tx_end_flg)
        {
            break;
        }

        timeout = cellular_check_timeout(p_cellular_timeout_ctrl);
        if (CELLULAR_TIMEOUT == timeout)
        {
            break;
        }
        cellular_delay_task(1);
    }

    return timeout;
}
/**********************************************************************************************************************
 * End of function cellular_tx_flag_check
 *********************************************************************************************************************/

/*************************************************************************************************
 * Function Name  @fn            cellular_atc_response_chek
 * Description    @details       Wait for the AT command response.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Socket number for sending data.
 * Return Value   @retval        CELLULAR_NOT_TIMEOUT -
 *                                  Successfully flag check.
 *                @retval        CELLULAR_TIMEOUT -
 *                                  Time out.
 ************************************************************************************************/
static e_cellular_timeout_check_t cellular_atc_response_chek(st_cellular_ctrl_t * const p_ctrl,
                                                                    const uint8_t socket_no)
{
    e_cellular_atc_return_t     at_ret  = ATC_RETURN_NONE;
    e_cellular_timeout_check_t  timeout = CELLULAR_NOT_TIMEOUT;

    st_cellular_socket_time_ctrl_t * const p_cellular_timeout_ctrl =
            &p_ctrl->p_socket_ctrl[socket_no - CELLULAR_START_SOCKET_NUMBER].cellular_tx_timeout_ctrl;

    while (1)
    {
        at_ret = cellular_get_atc_response(p_ctrl);
        if (ATC_RETURN_OK == at_ret)
        {
            break;
        }

        timeout = cellular_check_timeout(p_cellular_timeout_ctrl);
        if (CELLULAR_TIMEOUT == timeout)
        {
            break;
        }

        cellular_delay_task(1);
    }
    return timeout;
}
/**********************************************************************************************************************
 * End of function cellular_atc_response_chek
 *********************************************************************************************************************/
