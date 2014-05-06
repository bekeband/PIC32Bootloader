#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ETH_Btl_ETH_StarterKit.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ETH_Btl_ETH_StarterKit.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1094924598/Framework.o ${OBJECTDIR}/_ext/590309052/ARP.o ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o ${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o ${OBJECTDIR}/_ext/590309052/Helpers.o ${OBJECTDIR}/_ext/590309052/ICMP.o ${OBJECTDIR}/_ext/590309052/IP.o ${OBJECTDIR}/_ext/590309052/StackTsk.o ${OBJECTDIR}/_ext/590309052/Tick.o ${OBJECTDIR}/_ext/590309052/UDP.o ${OBJECTDIR}/_ext/1787047461/BootLoader.o ${OBJECTDIR}/_ext/1021585835/EthernetTasks.o ${OBJECTDIR}/_ext/1787047461/NVMem.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1094924598/Framework.o.d ${OBJECTDIR}/_ext/590309052/ARP.o.d ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o.d ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o.d ${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o.d ${OBJECTDIR}/_ext/590309052/Helpers.o.d ${OBJECTDIR}/_ext/590309052/ICMP.o.d ${OBJECTDIR}/_ext/590309052/IP.o.d ${OBJECTDIR}/_ext/590309052/StackTsk.o.d ${OBJECTDIR}/_ext/590309052/Tick.o.d ${OBJECTDIR}/_ext/590309052/UDP.o.d ${OBJECTDIR}/_ext/1787047461/BootLoader.o.d ${OBJECTDIR}/_ext/1021585835/EthernetTasks.o.d ${OBJECTDIR}/_ext/1787047461/NVMem.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1094924598/Framework.o ${OBJECTDIR}/_ext/590309052/ARP.o ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o ${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o ${OBJECTDIR}/_ext/590309052/Helpers.o ${OBJECTDIR}/_ext/590309052/ICMP.o ${OBJECTDIR}/_ext/590309052/IP.o ${OBJECTDIR}/_ext/590309052/StackTsk.o ${OBJECTDIR}/_ext/590309052/Tick.o ${OBJECTDIR}/_ext/590309052/UDP.o ${OBJECTDIR}/_ext/1787047461/BootLoader.o ${OBJECTDIR}/_ext/1021585835/EthernetTasks.o ${OBJECTDIR}/_ext/1787047461/NVMem.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ETH_Btl_ETH_StarterKit.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX795F512L
MP_LINKER_FILE_OPTION=,--script="..\..\linker_scripts\others\btl_32MX795F512L_generic.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1094924598/Framework.o: ../../Source/FrameWork/Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1094924598 
	@${RM} ${OBJECTDIR}/_ext/1094924598/Framework.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1094924598/Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/1094924598/Framework.o.d" -o ${OBJECTDIR}/_ext/1094924598/Framework.o ../../Source/FrameWork/Framework.c   
	
${OBJECTDIR}/_ext/590309052/ARP.o: ../../Source/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/ARP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/ARP.o.d" -o ${OBJECTDIR}/_ext/590309052/ARP.o "../../Source/TCPIP Stack/ARP.c"   
	
${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o: ../../Source/TCPIP\ Stack/ETHPIC32ExtPhy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o.d" -o ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o "../../Source/TCPIP Stack/ETHPIC32ExtPhy.c"   
	
${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o: ../../Source/TCPIP\ Stack/ETHPIC32ExtPhyDP83848.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o.d" -o ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o "../../Source/TCPIP Stack/ETHPIC32ExtPhyDP83848.c"   
	
${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o: ../../Source/TCPIP\ Stack/ETHPIC32IntMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o.d" -o ${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o "../../Source/TCPIP Stack/ETHPIC32IntMac.c"   
	
${OBJECTDIR}/_ext/590309052/Helpers.o: ../../Source/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/Helpers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/Helpers.o.d" -o ${OBJECTDIR}/_ext/590309052/Helpers.o "../../Source/TCPIP Stack/Helpers.c"   
	
${OBJECTDIR}/_ext/590309052/ICMP.o: ../../Source/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/ICMP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/ICMP.o.d" -o ${OBJECTDIR}/_ext/590309052/ICMP.o "../../Source/TCPIP Stack/ICMP.c"   
	
${OBJECTDIR}/_ext/590309052/IP.o: ../../Source/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/IP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/IP.o.d" -o ${OBJECTDIR}/_ext/590309052/IP.o "../../Source/TCPIP Stack/IP.c"   
	
${OBJECTDIR}/_ext/590309052/StackTsk.o: ../../Source/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/StackTsk.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/StackTsk.o.d" -o ${OBJECTDIR}/_ext/590309052/StackTsk.o "../../Source/TCPIP Stack/StackTsk.c"   
	
${OBJECTDIR}/_ext/590309052/Tick.o: ../../Source/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/Tick.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/Tick.o.d" -o ${OBJECTDIR}/_ext/590309052/Tick.o "../../Source/TCPIP Stack/Tick.c"   
	
${OBJECTDIR}/_ext/590309052/UDP.o: ../../Source/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/UDP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/UDP.o.d" -o ${OBJECTDIR}/_ext/590309052/UDP.o "../../Source/TCPIP Stack/UDP.c"   
	
${OBJECTDIR}/_ext/1787047461/BootLoader.o: ../../Source/BootLoader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1787047461 
	@${RM} ${OBJECTDIR}/_ext/1787047461/BootLoader.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/BootLoader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/1787047461/BootLoader.o.d" -o ${OBJECTDIR}/_ext/1787047461/BootLoader.o ../../Source/BootLoader.c   
	
${OBJECTDIR}/_ext/1021585835/EthernetTasks.o: ../../Source/Ethernet/EthernetTasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1021585835 
	@${RM} ${OBJECTDIR}/_ext/1021585835/EthernetTasks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1021585835/EthernetTasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/1021585835/EthernetTasks.o.d" -o ${OBJECTDIR}/_ext/1021585835/EthernetTasks.o ../../Source/Ethernet/EthernetTasks.c   
	
${OBJECTDIR}/_ext/1787047461/NVMem.o: ../../Source/NVMem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1787047461 
	@${RM} ${OBJECTDIR}/_ext/1787047461/NVMem.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/NVMem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PIC32MXSK=1 -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/1787047461/NVMem.o.d" -o ${OBJECTDIR}/_ext/1787047461/NVMem.o ../../Source/NVMem.c   
	
else
${OBJECTDIR}/_ext/1094924598/Framework.o: ../../Source/FrameWork/Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1094924598 
	@${RM} ${OBJECTDIR}/_ext/1094924598/Framework.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1094924598/Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/1094924598/Framework.o.d" -o ${OBJECTDIR}/_ext/1094924598/Framework.o ../../Source/FrameWork/Framework.c   
	
${OBJECTDIR}/_ext/590309052/ARP.o: ../../Source/TCPIP\ Stack/ARP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/ARP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/ARP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/ARP.o.d" -o ${OBJECTDIR}/_ext/590309052/ARP.o "../../Source/TCPIP Stack/ARP.c"   
	
${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o: ../../Source/TCPIP\ Stack/ETHPIC32ExtPhy.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o.d" -o ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhy.o "../../Source/TCPIP Stack/ETHPIC32ExtPhy.c"   
	
${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o: ../../Source/TCPIP\ Stack/ETHPIC32ExtPhyDP83848.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o.d" -o ${OBJECTDIR}/_ext/590309052/ETHPIC32ExtPhyDP83848.o "../../Source/TCPIP Stack/ETHPIC32ExtPhyDP83848.c"   
	
${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o: ../../Source/TCPIP\ Stack/ETHPIC32IntMac.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o.d" -o ${OBJECTDIR}/_ext/590309052/ETHPIC32IntMac.o "../../Source/TCPIP Stack/ETHPIC32IntMac.c"   
	
${OBJECTDIR}/_ext/590309052/Helpers.o: ../../Source/TCPIP\ Stack/Helpers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/Helpers.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/Helpers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/Helpers.o.d" -o ${OBJECTDIR}/_ext/590309052/Helpers.o "../../Source/TCPIP Stack/Helpers.c"   
	
${OBJECTDIR}/_ext/590309052/ICMP.o: ../../Source/TCPIP\ Stack/ICMP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/ICMP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/ICMP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/ICMP.o.d" -o ${OBJECTDIR}/_ext/590309052/ICMP.o "../../Source/TCPIP Stack/ICMP.c"   
	
${OBJECTDIR}/_ext/590309052/IP.o: ../../Source/TCPIP\ Stack/IP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/IP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/IP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/IP.o.d" -o ${OBJECTDIR}/_ext/590309052/IP.o "../../Source/TCPIP Stack/IP.c"   
	
${OBJECTDIR}/_ext/590309052/StackTsk.o: ../../Source/TCPIP\ Stack/StackTsk.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/StackTsk.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/StackTsk.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/StackTsk.o.d" -o ${OBJECTDIR}/_ext/590309052/StackTsk.o "../../Source/TCPIP Stack/StackTsk.c"   
	
${OBJECTDIR}/_ext/590309052/Tick.o: ../../Source/TCPIP\ Stack/Tick.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/Tick.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/Tick.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/Tick.o.d" -o ${OBJECTDIR}/_ext/590309052/Tick.o "../../Source/TCPIP Stack/Tick.c"   
	
${OBJECTDIR}/_ext/590309052/UDP.o: ../../Source/TCPIP\ Stack/UDP.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/590309052 
	@${RM} ${OBJECTDIR}/_ext/590309052/UDP.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/590309052/UDP.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/590309052/UDP.o.d" -o ${OBJECTDIR}/_ext/590309052/UDP.o "../../Source/TCPIP Stack/UDP.c"   
	
${OBJECTDIR}/_ext/1787047461/BootLoader.o: ../../Source/BootLoader.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1787047461 
	@${RM} ${OBJECTDIR}/_ext/1787047461/BootLoader.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/BootLoader.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/1787047461/BootLoader.o.d" -o ${OBJECTDIR}/_ext/1787047461/BootLoader.o ../../Source/BootLoader.c   
	
${OBJECTDIR}/_ext/1021585835/EthernetTasks.o: ../../Source/Ethernet/EthernetTasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1021585835 
	@${RM} ${OBJECTDIR}/_ext/1021585835/EthernetTasks.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1021585835/EthernetTasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/1021585835/EthernetTasks.o.d" -o ${OBJECTDIR}/_ext/1021585835/EthernetTasks.o ../../Source/Ethernet/EthernetTasks.c   
	
${OBJECTDIR}/_ext/1787047461/NVMem.o: ../../Source/NVMem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/_ext/1787047461 
	@${RM} ${OBJECTDIR}/_ext/1787047461/NVMem.o.d 
	@${FIXDEPS} "${OBJECTDIR}/_ext/1787047461/NVMem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -DTRANSPORT_LAYER_ETH -DDEMO_BOARD_ETH_STARTER_KIT -DETH_INTERNAL_MAC -I"../../Include/Ethernet" -I"../../Include/HardwareProfile" -I"../../Include" -I"../../Include/Usb/Stack" -I"../../Include/FrameWork" -I"../.." -I"../../Include/Usb" -I"../../Include/TCPIP Stack" -I"../../Include/Framework" -Os -MMD -MF "${OBJECTDIR}/_ext/1787047461/NVMem.o.d" -o ${OBJECTDIR}/_ext/1787047461/NVMem.o ../../Source/NVMem.c   
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ETH_Btl_ETH_StarterKit.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    ../../linker_scripts/others/btl_32MX795F512L_generic.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PIC32MXSK=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ETH_Btl_ETH_StarterKit.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PIC32MXSK=1,--defsym=_min_heap_size=30000,--gc-sections,-L"../../MPLAB_Workspace",-Map="$(BINDIR_)$(TARGETBASE).map"
else
dist/${CND_CONF}/${IMAGE_TYPE}/ETH_Btl_ETH_StarterKit.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   ../../linker_scripts/others/btl_32MX795F512L_generic.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/ETH_Btl_ETH_StarterKit.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}         -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=30000,--gc-sections,-L"../../MPLAB_Workspace",-Map="$(BINDIR_)$(TARGETBASE).map"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/ETH_Btl_ETH_StarterKit.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
