<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<smc>
<general version="2.0.0.0">
<configuration active="true" id="${configurationTypeReleaseID}">
<property id="com.renesas.smc.service.project.buildArtefactType" values="com.renesas.smc.service.project.buildArtefactType.exe"/>
<toolchain id="${toolChainID}">
<option id="com.renesas.smc.toolchain.option.buildArtefactType" key="com.renesas.smc.toolchain.option.buildArtefactType.exe"/>
<option id="com.renesas.smc.toolchain.option.rtos" key="com.renesas.smc.toolchain.option.rtos.freertos">
<item id="com.renesas.smc.toolchain.option.rtos.freertos" value="AmazonFreeRTOS_RX_${packageVersion}"/>
</option>
</toolchain>
</configuration>
<platform id="${targetDevice}"/>
<option id="board" value="Custom User Board"/>
</general>
<tool id="Summary" version="1.0.0.0">
<option id="com.renesas.smc.code.type" value="Normal Folder"/>
</tool>
<tool id="SWComponent" version="1.0.0.0">
<configuration inuse="true" name="r_bsp">
<component display="r_bsp" id="r_bsp5.52" version="5.52">
<gridItem id="BSP_CFG_CODE_FLASH_BANK_MODE" selectedIndex="0"/>
</component>
<source id="com.renesas.smc.tools.swcomponent.fit.source"/>
</configuration>
<configuration inuse="true" name="r_s12ad_rx">
<component display="r_s12ad_rx" id="r_s12ad_rx4.50" version="4.50"></component>
<source description="Components supporting Firmware Integration Technology" display="Firmware Integration Technology" id="com.renesas.smc.tools.swcomponent.fit.source"/>
</configuration>
<configuration inuse="true" name="r_flash_rx">
<component display="r_flash_rx" id="r_flash_rx4.50" version="4.50">
<gridItem id="FLASH_CFG_PARAM_CHECKING_ENABLE" selectedIndex="1"/>
<gridItem id="FLASH_CFG_CODE_FLASH_ENABLE" selectedIndex="1"/>
<gridItem id="FLASH_CFG_DATA_FLASH_BGO" selectedIndex="1"/>
<gridItem id="FLASH_CFG_CODE_FLASH_BGO" selectedIndex="1"/>
<gridItem id="FLASH_CFG_CODE_FLASH_RUN_FROM_ROM" selectedIndex="1"/>
</component>
<source description="Components supporting Firmware Integration Technology" display="Firmware Integration Technology" id="com.renesas.smc.tools.swcomponent.fit.source"/>
</configuration>
<configuration inuse="true" name="r_sci_rx">
<component display="r_sci_rx" id="r_sci_rx3.40" version="3.40"></component>
<source description="Components supporting Firmware Integration Technology" display="Firmware Integration Technology" id="com.renesas.smc.tools.swcomponent.fit.source"/>
</configuration>
<configuration inuse="true" name="r_byteq">
<component display="r_byteq" id="r_byteq1.80" version="1.80"></component>
<source description="Components supporting Firmware Integration Technology" display="Firmware Integration Technology" id="com.renesas.smc.tools.swcomponent.fit.source"/>
</configuration>
<configuration inuse="true" name="r_ether_rx">
<component display="r_ether_rx" id="r_ether_rx1.20" version="1.20"></component>
<source description="Components supporting Firmware Integration Technology" display="Firmware Integration Technology" id="com.renesas.smc.tools.swcomponent.fit.source"/>
</configuration>
<configuration inuse="true" name="FreeRTOS_Application">
<component display="FreeRTOS_Application" id="com.renesas.smc.tools.swcomponent.rtosconfigurator.freertos.amazon.application">
<gridItem id="CONNECTION" selectedIndex="1"/>
</component>
<source id="com.renesas.smc.tools.swcomponent.rtosconfigurator.source"/>
</configuration>
<configuration inuse="true" name="FreeRTOS_Object">
<component display="FreeRTOS_Object" id="com.renesas.smc.tools.swcomponent.rtosconfigurator.freertos.object"/>
<source id="com.renesas.smc.tools.swcomponent.rtosconfigurator.source"/>
</configuration>
<configuration inuse="true" name="FreeRTOS_Kernel">
<component display="FreeRTOS_Kernel" id="com.renesas.smc.tools.swcomponent.rtosconfigurator.freertos.amazon.kernel"/>
<source id="com.renesas.smc.tools.swcomponent.rtosconfigurator.source"/>
</configuration>
<configuration inuse="true" name="AWS_device_shadow">
<component display="AWS_device_shadow" id="com.renesas.smc.tools.swcomponent.rtosconfigurator.freertos.amazon.device_shadow"/>
<source id="com.renesas.smc.tools.swcomponent.rtosconfigurator.source"/>
</configuration>
<configuration inuse="true" name="AWS_tcp_ip">
<component display="AWS_tcp_ip" id="com.renesas.smc.tools.swcomponent.rtosconfigurator.freertos.amazon.tcp_ip"/>
<source id="com.renesas.smc.tools.swcomponent.rtosconfigurator.source"/>
</configuration>
<configuration inuse="true" name="AWS_mqtt">
<component display="AWS_mqtt" id="com.renesas.smc.tools.swcomponent.rtosconfigurator.freertos.amazon.mqtt"/>
<source id="com.renesas.smc.tools.swcomponent.rtosconfigurator.source"/>
</configuration>
<configuration inuse="true" name="AWS_secure_socket">
<component display="AWS_secure_socket" id="com.renesas.smc.tools.swcomponent.rtosconfigurator.freertos.amazon.secure_socket"/>
<source id="com.renesas.smc.tools.swcomponent.rtosconfigurator.source"/>
</configuration>
<configuration inuse="true" name="AWS_ggd">
<component display="AWS_ggd" id="com.renesas.smc.tools.swcomponent.rtosconfigurator.freertos.amazon.ggd"/>
<source id="com.renesas.smc.tools.swcomponent.rtosconfigurator.source"/>
</configuration>
</tool>
</smc>
