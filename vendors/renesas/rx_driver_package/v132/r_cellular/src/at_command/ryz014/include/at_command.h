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
 * File Name    : at_command.h
 * Description  : Configures the AT command.
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
#include "r_cellular_if.h"

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/
#ifndef AT_COMMAND_H
#define AT_COMMAND_H

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/
extern const uint8_t * const gp_at_command[ATC_LIST_MAX];

/*************************************************************************************************
 * Function Name  @fn            atc_ate0
 * Description    @details       Execute the AT command (ATE0). / echo-off.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_ate0 (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cfun
 * Description    @details       Execute the AT command (CFUN). / ctrol of module operation.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     mode -
 *                                  Function to be set for the module.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cfun (st_cellular_ctrl_t * const p_ctrl, const e_cellular_module_status_t mode);

/*************************************************************************************************
 * Function Name  @fn            atc_cfun_check
 * Description    @details       Execute the AT command (CFUN?). Check control level of modules.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cfun_check (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cgatt
 * Description    @details       Execute the AT command (CGATT). / Attach/detach to AP.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     mode -
 *                                  Select Connect/Disconnect.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cgatt (st_cellular_ctrl_t * const p_ctrl, const e_atc_ap_status_t mode);

/****************************************************************************************************************
 * Function Name  @fn            atc_cgatt_check
 * Description    @details       Execute the AT command (CGATT?). / Check the status of the connection to the AP.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ***************************************************************************************************************/
e_cellular_err_t atc_cgatt_check (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cgauth
 * Description    @details       Execute the AT command (CGAUTH). / Set AP user name and password.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cgauth (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cgdcont
 * Description    @details       Execute the AT command (CGDCONT). / Set AP name.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cgdcont (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cpin
 * Description    @details       Execute the AT command (CPIN). / PIN/PUK code entry.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cpin (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cpin_check
 * Description    @details       Execute the AT command (CPIN?). / Check PIN/PUK lock status.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cpin_check (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_sqndnslkup
 * Description    @details       Execute the AT command (SQNDNSLKUP). / Execute DNS query.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     p_dmain_name -
 *                                  Pointer to the domain name.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_sqndnslkup (st_cellular_ctrl_t * const p_ctrl, const uint8_t * const p_domain_name);

/*************************************************************************************************
 * Function Name  @fn            atc_sqnscfg
 * Description    @details       Execute the AT command (SQNSCFG). / Configured the socket.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Socket number for configuring.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_sqnscfg (st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no);

/*************************************************************************************************
 * Function Name  @fn            atc_sqnscfgext
 * Description    @details       Execute the AT command (SQNSCFGEXT). / Configured the socket.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Socket number.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_sqnscfgext (st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no);

/*******************************************************************************************************
 * Function Name  @fn            atc_sqnsd
 * Description    @details       Execute the AT command (SQNSD). / Perform socket connect by IP address.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Number to connect socket.
 *                @param[in]     ip_address -
 *                                  Destination IP address.
 *                @param[in]     port -
 *                                  Destination port number.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ******************************************************************************************************/
e_cellular_err_t atc_sqnsd (st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no,
                                const uint32_t ip_address, const uint16_t port);

/****************************************************************************************************
 * Function Name  @fn            atc_sqnsd_host
 * Description    @details       Execute the AT command (SQNSD) / Perform socket connect by hostname.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Number to connect socket.
 *                @param[in]     p_hostname -
 *                                  Destination Host Name.
 *                @param[in]     port -
 *                                  Destination port number.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ***************************************************************************************************/
e_cellular_err_t atc_sqnsd_host (st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no,
                                    const uint8_t * p_hostname, const uint16_t port);

/*************************************************************************************************
 * Function Name  @fn            atc_sqnsh
 * Description    @details       Execute the AT command (SQNSH). / Close Socket Connect.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Socket number to disconnect.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_sqnsh (st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no);

/************************************************************************************************************
 * Function Name  @fn            atc_sqnsrecv
 * Description    @details       Execute the AT command (SQNSRECV). / Receive data from the specified socket.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Socket number to receive data.
 *                @param[in]     length -
 *                                  Number of bytes to receive.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ***********************************************************************************************************/
e_cellular_err_t atc_sqnsrecv (st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no, const int32_t length);

/*************************************************************************************************
 * Function Name  @fn            atc_sqnssendext
 * Description    @details       Execute the AT command (SQNSSENDEXT). / Send data to the specified socket.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Socket number to send data.
 *                @param[in]     length -
 *                                  Number of bytes to send.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_sqnssendext (st_cellular_ctrl_t * const p_ctrl, const uint8_t socket_no, const int32_t length);

/*****************************************************************************************************************
 * Function Name  @fn            atc_sqnsshdn
 * Description    @details       Execute the AT command (SQNSSHDN). / Device detach from the network and shutdown.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ****************************************************************************************************************/
e_cellular_err_t atc_sqnsshdn (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cclk
 * Description    @details       Execute the AT command (CCLK). / Set the time.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     p_time -
 *                                  Pointer to the structure that stores the date and time.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cclk (st_cellular_ctrl_t * const p_ctrl, const st_cellular_datetime_t * const p_time);

/*************************************************************************************************
 * Function Name  @fn            atc_cclk_check
 * Description    @details       Execute the AT command (CCLK?). / Get the time.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cclk_check (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_reset
 * Description    @details       Execute the AT command (AT^RESET). / Reset the device.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_reset (st_cellular_ctrl_t * const p_ctrl);

/********************************************************************************************************
 * Function Name  @fn            atc_cereg_off
 * Description    @details       Execute the AT command (AT+CEREG=0). / Disable notification of
 *                                                                      network registration information.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 *******************************************************************************************************/
e_cellular_err_t atc_cereg_off (st_cellular_ctrl_t * const p_ctrl);

/**********************************************************************************************************
 * Function Name  @fn            atc_sqnautoconnect
 * Description    @details       Execute the AT command (AT+SQNAUTOCONNECT=0). / Disable Auto-Connect mode.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 *********************************************************************************************************/
e_cellular_err_t atc_sqnautoconnect (st_cellular_ctrl_t * const p_ctrl);

/**********************************************************************************************************
 * Function Name  @fn            atc_sqnsimst
 * Description    @details       Execute the AT command (AT+SQNSIMST=0). / Disable SIM status notification.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 *********************************************************************************************************/
e_cellular_err_t atc_sqnsimst (st_cellular_ctrl_t * const p_ctrl);

/***************************************************************************************************************
 * Function Name  @fn            atc_cops
 * Description    @details       Execute the AT command (AT+COPS). / Specify the method of connecting to the AP.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     mode -
 *                                  Mode to set. 0=auto / 1=manual / 2=disconnect / 3=No mapping / 4=No support
 *                @param[in]     mcc -
 *                                  Country Code.
 *                @param[in]     mnc -
 *                                  Network number.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 **************************************************************************************************************/
e_cellular_err_t atc_cops (st_cellular_ctrl_t * const p_ctrl, const uint8_t mode,
                                            const uint16_t mcc, const uint8_t mnc);

/****************************************************************************************************
 * Function Name  @fn            atc_cops_check
 * Description    @details       Execute the AT command (AT+COPS?). / Check how to connect to the AP.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ***************************************************************************************************/
e_cellular_err_t atc_cops_check (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cgact
 * Description    @details       Execute the AT command (AT+CGACT). / Enable/Disable PDP context.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     mode -
 *                                  Setting the context ID. 0=deactivated / 1=activated
 *                @param[in]     context_id -
 *                                  Context ID number.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cgact (st_cellular_ctrl_t * const p_ctrl, const uint8_t mode, const uint8_t context_id);

/********************************************************************************************************
 * Function Name  @fn            atc_cgact_check
 * Description    @details       Execute the AT command (AT+CGACT). / Check the status of the PDP context
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 *******************************************************************************************************/
e_cellular_err_t atc_cgact_check (st_cellular_ctrl_t * const p_ctrl);

/**********************************************************************************************************************
 * Function Name  @fn            atc_cgpaddr
 * Description    @details       Execute the AT command (AT+CGPADDR). / Get the IP address assigned to the PDP context.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     context_id -
 *                                  Context ID number to check the configured IP address.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 *********************************************************************************************************************/
e_cellular_err_t atc_cgpaddr (st_cellular_ctrl_t * const p_ctrl, const uint8_t context_id);

/************************************************************************************************************
 * Function Name  @fn            atc_cpsms
 * Description    @details       Execute the AT command (AT+CPSMS). / Configure PSM.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     mode -
 *                                  Mode to set.
 *                @param[in]     tau -
 *                                  Set the TAU cycle.
 *                @param[in]     tau_multiplier -
 *                                  Multiplier for TAU cycle.
 *                @param[in]     active -
 *                                  Set the active time cycle.
 *                @param[in]     active_multiplier -
 *                                  Multiplier for active time cycle.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ***********************************************************************************************************/
e_cellular_err_t atc_cpsms (st_cellular_ctrl_t * const p_ctrl, const e_cellular_psm_mode_t mode,
                            const e_cellular_psm_cycle_t tau, const e_cellular_cycle_multiplier_t tau_multiplier,
                            const e_cellular_psm_cycle_t active, const e_cellular_cycle_multiplier_t active_multiplier);

/*************************************************************************************************
 * Function Name  @fn            atc_cpsms_check
 * Description    @details       Execute the AT command (AT+CPSMS?). / Check PSM Configure.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cpsms_check (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_sqnedrx
 * Description    @details       Execute the AT command (AT+SQNEDRX). / Configure eDRX.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     mode -
 *                                  Mode to set.
 *                @param[in]     edrx_value -
 *                                  Set the edrx cycle.
 *                @param[in]     ptw -
 *                                  Set the PTW cycle.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_sqnedrx (st_cellular_ctrl_t * const p_ctrl, const e_cellular_edrx_mode_t mode,
                                const e_cellular_edrx_cycle_t edrx_value, const e_cellular_edrx_cycle_t ptw);

/*************************************************************************************************
 * Function Name  @fn            atc_sqnedrx_check
 * Description    @details       Execute the AT command (AT+SQNEDRX?). / Check eDRX Configure.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_sqnedrx_check (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_csq
 * Description    @details       Execute the AT command (AT+CSQ). / Get RSSI and BER.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_csq (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cgmr
 * Description    @details       Execute the AT command (AT+CGMR). / Get software version.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cgmr (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cgsn
 * Description    @details       Execute the AT command (AT+CGSN). / Get serial number.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cgsn (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cgmm
 * Description    @details       Execute the AT command (AT+CGMM). / Get module name.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cgmm (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cgmi
 * Description    @details       Execute the AT command (AT+CGMI). / Get manufacturer name.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cgmi (st_cellular_ctrl_t * const p_ctrl);

/*************************************************************************************************
 * Function Name  @fn            atc_cimi
 * Description    @details       Execute the AT command (AT+CIMI). / Get IMSI.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_cimi (st_cellular_ctrl_t * const p_ctrl);

/*******************************************************************************************************************
 * Function Name  @fn            atc_crsm
 * Description    @details       Execute the AT command (AT+CRSM). / Read/write data from SIM card.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     command -
 *                                  Commands passed to the SIM. 176=READ BINARY / 178=READ RECORD / 192=GET RESPONSE
 *                                                              214=UPDATE BINARY / 220=UPDATE RECORD / 242=STATUS
 *                                                              203=RETRIEVE DATA / 219=SET DATA
 *                @param[in]     fileid -
 *                                  Identifier of an elementary data file on SIM.
 *                @param[in]     para_1 -
 *                                  Parameters passed to the SIM.
 *                @param[in]     para_2 -
 *                                  Parameters passed to the SIM.
 *                @param[in]     para_3 -
 *                                  Parameters passed to the SIM.
 *                @param[in]     data -
 *                                  Information that shall be written to the SIM.
 *                @param[in]     pathid -
 *                                  Contains the path of an elementary file on the SIM/UICC.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ******************************************************************************************************************/
e_cellular_err_t atc_crsm (st_cellular_ctrl_t * const p_ctrl, const uint8_t command, const uint16_t fileid,
                            const uint8_t para_1, const uint8_t para_2, const uint8_t para_3,
                            const uint8_t * data, const uint8_t * pathid);

/******************************************************************************************************************
 * Function Name  @fn            atc_sqnipscfg
 * Description    @details       Execute the AT command (AT+SQNIPSCFG). / Set the UARTs power saving configuration.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     mode -
 *                                  Enable(1)/Disable(0) the power saving mode.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 *****************************************************************************************************************/
e_cellular_err_t atc_sqnipscfg (st_cellular_ctrl_t * const p_ctrl, e_cellular_psm_mode_t mode);

/***************************************************************************************************
 * Function Name  @fn            atc_sqnricfg
 * Description    @details       Execute the AT command (AT+SQNRICFG). / Set the RING line behavior.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     mode -
 *                                  Enable(1)/Disable(0) the ring line.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 **************************************************************************************************/
e_cellular_err_t atc_sqnricfg (st_cellular_ctrl_t * const p_ctrl, e_cellular_psm_mode_t mode);

/*********************************************************************************************************************
 * Function Name  @fn            atc_cmer
 * Description    @details       Execute the AT command (AT+CMER). / Indicator status change notification setting.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     mode -
 *                                  Enable(1)/Disable(0) indicator event notification.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ********************************************************************************************************************/
e_cellular_err_t atc_cmer (st_cellular_ctrl_t * const p_ctrl, e_cellular_psm_mode_t mode);

#if (CELLULAR_IMPLEMENT_TYPE == 'B')
/****************************************************************************************************************
 * Function Name  @fn            atc_sqnsnvw
 * Description    @details       Execute the AT command (SQNSNVW). / Writing certificates and other data
 *                                                                   to non-volatile memory
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     data_type -
 *                                  Information to write.
 *                @param[in]     index -
 *                                  Destination index.
 *                @param[in]     p_data -
 *                                  Pointer to the data to write.
 *                @param[in]     size -
 *                                  Size of the data to be written.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ***************************************************************************************************************/
e_cellular_err_t atc_sqnsnvw (st_cellular_ctrl_t * const p_ctrl, const e_cellular_nvm_type_t data_type,
                                    const uint8_t index, const uint32_t size);

/********************************************************************************************************
 * Function Name  @fn            atc_sqnsnvw_erase
 * Description    @details       Execute the AT command (SQNSNVW). / Deleting certificates and other data
 *                                                                   from non-volatile memory
 *                @param[in]     data_type -
 *                                  Information to write.
 *                @param[in]     index -
 *                                  Destination index.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 *******************************************************************************************************/
e_cellular_err_t atc_sqnsnvw_erase (st_cellular_ctrl_t * const p_ctrl, const e_cellular_nvm_type_t data_type,
                                    const uint8_t index);

/*****************************************************************************************************
 * Function Name  @fn            atc_sqnspcfg
 * Description    @details       Execute the AT command (SQNSPCFG). / Configure the necessary settings
 *                                                                    for SSL/TLS connection.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     security_profile_id -
 *                                  Security Profile identifier
 *                @param[in]     cert_valid_level -
 *                                  Server certificate validation
 *                @param[in]     ca_certificate_id -
 *                                  Certificate ID of a trusted certification authority
 *                                    by written to non-volatile memory.
 *                @param[in]     client_certificate_id -
 *                                  Client certificate ID by written to non-volatile memory.
 *                @param[in]     client_privatekey_id -
 *                                  Privatekey ID by written to non-volatile memory.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ****************************************************************************************************/
e_cellular_err_t atc_sqnspcfg (st_cellular_ctrl_t * const p_ctrl,
                                    const uint8_t security_profile_id,
                                    const e_cellular_cert_validate_level_t cert_valid_level,
                                    const uint8_t ca_certificate_id,
                                    const uint8_t client_certificate_id,
                                    const uint8_t client_privatekey_id);

/*************************************************************************************************
 * Function Name  @fn            atc_sqnsscfg
 * Description    @details       Execute the AT command (SQNSSCFG). / Enable/Disable SSL/TLS connection.
 * Arguments      @param[in/out] p_ctrl -
 *                                  Pointer to managed structure.
 *                @param[in]     socket_no -
 *                                  Socket number to configurate.
 *                @param[in]     active -
 *                                  Pointer to store IP address.
 *                @param[in]     security_profile_id -
 *                                  Link to Security Profile identifier.
 * Return Value   @retval        CELLULAR_SUCCESS -
 *                                  Successfully executed AT command.
 *                @retval        CELLULAR_ERR_MODULE_COM -
 *                                  Communication with module failed.
 ************************************************************************************************/
e_cellular_err_t atc_sqnsscfg (st_cellular_ctrl_t * const p_ctrl,
                                    const uint8_t socket_no,
                                    const e_cellular_ssl_active_t active,
                                    const uint8_t security_profile_id);
#endif /* (CELLULAR_IMPLEMENT_TYPE == 'B') */

/*****************************************************************************
 * Function Name  @fn            atc_generate
 * Description    @details       Generate the AT command.
 * Arguments      @param[in/out] p_command_buff -
 *                                  Pointer to store the command.
 *                @param[in]     pp_command -
 *                                  Pointer to AT command.
 *                @param[in]     pp_command_arg -
 *                                  Pointer to the argument of the AT command.
 ****************************************************************************/
void atc_generate (uint8_t * const p_command_buff, const uint8_t * p_command , const uint8_t ** pp_command_arg);


#endif /* AT_COMMAND_H */
