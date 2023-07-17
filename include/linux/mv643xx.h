/*
 * mv64340.h - MV-64340 Internal registers definition file.
 *
 * Copyright 2002 Momentum Computer, Inc.
 * 	Author: Matthew Dharm <mdharm@momenco.com>
 * Copyright 2002 GALILEO TECHNOLOGY, LTD. 
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */
#ifndef __ASM_MV64340_H
#define __ASM_MV64340_H

#ifdef __MIPS__
#include <asm/addrspace.h>
#include <asm/marvell.h>
#endif
#include <asm/types.h>

/****************************************/
/* Processor Address Space              */
/****************************************/

/* DDR SDRAM BAR and size registers */

#define MV64340_CS_0_BASE_ADDR                                      0x008
#define MV64340_CS_0_SIZE                                           0x010
#define MV64340_CS_1_BASE_ADDR                                      0x208
#define MV64340_CS_1_SIZE                                           0x210
#define MV64340_CS_2_BASE_ADDR                                      0x018
#define MV64340_CS_2_SIZE                                           0x020
#define MV64340_CS_3_BASE_ADDR                                      0x218
#define MV64340_CS_3_SIZE                                           0x220

/* Devices BAR and size registers */

#define MV64340_DEV_CS0_BASE_ADDR                                   0x028
#define MV64340_DEV_CS0_SIZE                                        0x030
#define MV64340_DEV_CS1_BASE_ADDR                                   0x228
#define MV64340_DEV_CS1_SIZE                                        0x230
#define MV64340_DEV_CS2_BASE_ADDR                                   0x248
#define MV64340_DEV_CS2_SIZE                                        0x250
#define MV64340_DEV_CS3_BASE_ADDR                                   0x038
#define MV64340_DEV_CS3_SIZE                                        0x040
#define MV64340_BOOTCS_BASE_ADDR                                    0x238
#define MV64340_BOOTCS_SIZE                                         0x240

/* PCI 0 BAR and size registers */

#define MV64340_PCI_0_IO_BASE_ADDR                                  0x048
#define MV64340_PCI_0_IO_SIZE                                       0x050
#define MV64340_PCI_0_MEMORY0_BASE_ADDR                             0x058
#define MV64340_PCI_0_MEMORY0_SIZE                                  0x060
#define MV64340_PCI_0_MEMORY1_BASE_ADDR                             0x080
#define MV64340_PCI_0_MEMORY1_SIZE                                  0x088
#define MV64340_PCI_0_MEMORY2_BASE_ADDR                             0x258
#define MV64340_PCI_0_MEMORY2_SIZE                                  0x260
#define MV64340_PCI_0_MEMORY3_BASE_ADDR                             0x280
#define MV64340_PCI_0_MEMORY3_SIZE                                  0x288

/* PCI 1 BAR and size registers */
#define MV64340_PCI_1_IO_BASE_ADDR                                  0x090
#define MV64340_PCI_1_IO_SIZE                                       0x098
#define MV64340_PCI_1_MEMORY0_BASE_ADDR                             0x0a0
#define MV64340_PCI_1_MEMORY0_SIZE                                  0x0a8
#define MV64340_PCI_1_MEMORY1_BASE_ADDR                             0x0b0
#define MV64340_PCI_1_MEMORY1_SIZE                                  0x0b8
#define MV64340_PCI_1_MEMORY2_BASE_ADDR                             0x2a0
#define MV64340_PCI_1_MEMORY2_SIZE                                  0x2a8
#define MV64340_PCI_1_MEMORY3_BASE_ADDR                             0x2b0
#define MV64340_PCI_1_MEMORY3_SIZE                                  0x2b8

/* SRAM base address */
#define MV64340_INTEGRATED_SRAM_BASE_ADDR                           0x268

/* internal registers space base address */
#define MV64340_INTERNAL_SPACE_BASE_ADDR                            0x068

/* Enables the CS , DEV_CS , PCI 0 and PCI 1 
   windows above */
#define MV64340_BASE_ADDR_ENABLE                                    0x278

/****************************************/
/* PCI remap registers                  */
/****************************************/
      /* PCI 0 */
#define MV64340_PCI_0_IO_ADDR_REMAP                                 0x0f0
#define MV64340_PCI_0_MEMORY0_LOW_ADDR_REMAP                        0x0f8
#define MV64340_PCI_0_MEMORY0_HIGH_ADDR_REMAP                       0x320
#define MV64340_PCI_0_MEMORY1_LOW_ADDR_REMAP                        0x100
#define MV64340_PCI_0_MEMORY1_HIGH_ADDR_REMAP                       0x328
#define MV64340_PCI_0_MEMORY2_LOW_ADDR_REMAP                        0x2f8
#define MV64340_PCI_0_MEMORY2_HIGH_ADDR_REMAP                       0x330
#define MV64340_PCI_0_MEMORY3_LOW_ADDR_REMAP                        0x300
#define MV64340_PCI_0_MEMORY3_HIGH_ADDR_REMAP                       0x338
      /* PCI 1 */
#define MV64340_PCI_1_IO_ADDR_REMAP                                 0x108
#define MV64340_PCI_1_MEMORY0_LOW_ADDR_REMAP                        0x110
#define MV64340_PCI_1_MEMORY0_HIGH_ADDR_REMAP                       0x340
#define MV64340_PCI_1_MEMORY1_LOW_ADDR_REMAP                        0x118
#define MV64340_PCI_1_MEMORY1_HIGH_ADDR_REMAP                       0x348
#define MV64340_PCI_1_MEMORY2_LOW_ADDR_REMAP                        0x310
#define MV64340_PCI_1_MEMORY2_HIGH_ADDR_REMAP                       0x350
#define MV64340_PCI_1_MEMORY3_LOW_ADDR_REMAP                        0x318
#define MV64340_PCI_1_MEMORY3_HIGH_ADDR_REMAP                       0x358
 
#define MV64340_CPU_PCI_0_HEADERS_RETARGET_CONTROL                  0x3b0
#define MV64340_CPU_PCI_0_HEADERS_RETARGET_BASE                     0x3b8
#define MV64340_CPU_PCI_1_HEADERS_RETARGET_CONTROL                  0x3c0
#define MV64340_CPU_PCI_1_HEADERS_RETARGET_BASE                     0x3c8
#define MV64340_CPU_GE_HEADERS_RETARGET_CONTROL                     0x3d0
#define MV64340_CPU_GE_HEADERS_RETARGET_BASE                        0x3d8
#define MV64340_CPU_IDMA_HEADERS_RETARGET_CONTROL                   0x3e0
#define MV64340_CPU_IDMA_HEADERS_RETARGET_BASE                      0x3e8

/****************************************/
/*         CPU Control Registers        */
/****************************************/

#define MV64340_CPU_CONFIG                                          0x000
#define MV64340_CPU_MODE                                            0x120
#define MV64340_CPU_MASTER_CONTROL                                  0x160
#define MV64340_CPU_CROSS_BAR_CONTROL_LOW                           0x150
#define MV64340_CPU_CROSS_BAR_CONTROL_HIGH                          0x158
#define MV64340_CPU_CROSS_BAR_TIMEOUT                               0x168

/****************************************/
/* SMP RegisterS                        */
/****************************************/

#define MV64340_SMP_WHO_AM_I                                        0x200
#define MV64340_SMP_CPU0_DOORBELL                                   0x214
#define MV64340_SMP_CPU0_DOORBELL_CLEAR                             0x21C
#define MV64340_SMP_CPU1_DOORBELL                                   0x224
#define MV64340_SMP_CPU1_DOORBELL_CLEAR                             0x22C
#define MV64340_SMP_CPU0_DOORBELL_MASK                              0x234
#define MV64340_SMP_CPU1_DOORBELL_MASK                              0x23C
#define MV64340_SMP_SEMAPHOR0                                       0x244
#define MV64340_SMP_SEMAPHOR1                                       0x24c
#define MV64340_SMP_SEMAPHOR2                                       0x254
#define MV64340_SMP_SEMAPHOR3                                       0x25c
#define MV64340_SMP_SEMAPHOR4                                       0x264
#define MV64340_SMP_SEMAPHOR5                                       0x26c
#define MV64340_SMP_SEMAPHOR6                                       0x274
#define MV64340_SMP_SEMAPHOR7                                       0x27c

/****************************************/
/*  CPU Sync Barrier Register           */
/****************************************/

#define MV64340_CPU_0_SYNC_BARRIER_TRIGGER                          0x0c0
#define MV64340_CPU_0_SYNC_BARRIER_VIRTUAL                          0x0c8
#define MV64340_CPU_1_SYNC_BARRIER_TRIGGER                          0x0d0
#define MV64340_CPU_1_SYNC_BARRIER_VIRTUAL                          0x0d8

/****************************************/
/* CPU Access Protect                   */
/****************************************/

#define MV64340_CPU_PROTECT_WINDOW_0_BASE_ADDR                      0x180
#define MV64340_CPU_PROTECT_WINDOW_0_SIZE                           0x188
#define MV64340_CPU_PROTECT_WINDOW_1_BASE_ADDR                      0x190
#define MV64340_CPU_PROTECT_WINDOW_1_SIZE                           0x198
#define MV64340_CPU_PROTECT_WINDOW_2_BASE_ADDR                      0x1a0
#define MV64340_CPU_PROTECT_WINDOW_2_SIZE                           0x1a8
#define MV64340_CPU_PROTECT_WINDOW_3_BASE_ADDR                      0x1b0
#define MV64340_CPU_PROTECT_WINDOW_3_SIZE                           0x1b8


/****************************************/
/*          CPU Error Report            */
/****************************************/

#define MV64340_CPU_ERROR_ADDR_LOW                                  0x070
#define MV64340_CPU_ERROR_ADDR_HIGH                                 0x078
#define MV64340_CPU_ERROR_DATA_LOW                                  0x128
#define MV64340_CPU_ERROR_DATA_HIGH                                 0x130
#define MV64340_CPU_ERROR_PARITY                                    0x138
#define MV64340_CPU_ERROR_CAUSE                                     0x140
#define MV64340_CPU_ERROR_MASK                                      0x148

/****************************************/
/*      CPU Interface Debug Registers 	*/
/****************************************/

#define MV64340_PUNIT_SLAVE_DEBUG_LOW                               0x360
#define MV64340_PUNIT_SLAVE_DEBUG_HIGH                              0x368
#define MV64340_PUNIT_MASTER_DEBUG_LOW                              0x370
#define MV64340_PUNIT_MASTER_DEBUG_HIGH                             0x378
#define MV64340_PUNIT_MMASK                                         0x3e4

/****************************************/
/*  Integrated SRAM Registers           */
/****************************************/

#define MV64340_SRAM_CONFIG                                         0x380
#define MV64340_SRAM_TEST_MODE                                      0X3F4
#define MV64340_SRAM_ERROR_CAUSE                                    0x388
#define MV64340_SRAM_ERROR_ADDR                                     0x390
#define MV64340_SRAM_ERROR_ADDR_HIGH                                0X3F8
#define MV64340_SRAM_ERROR_DATA_LOW                                 0x398
#define MV64340_SRAM_ERROR_DATA_HIGH                                0x3a0
#define MV64340_SRAM_ERROR_DATA_PARITY                              0x3a8

/****************************************/
/* SDRAM Configuration                  */
/****************************************/

#define MV64340_SDRAM_CONFIG                                        0x1400
#define MV64340_D_UNIT_CONTROL_LOW                                  0x1404
#define MV64340_D_UNIT_CONTROL_HIGH                                 0x1424
#define MV64340_SDRAM_TIMING_CONTROL_LOW                            0x1408
#define MV64340_SDRAM_TIMING_CONTROL_HIGH                           0x140c
#define MV64340_SDRAM_ADDR_CONTROL                                  0x1410
#define MV64340_SDRAM_OPEN_PAGES_CONTROL                            0x1414
#define MV64340_SDRAM_OPERATION                                     0x1418
#define MV64340_SDRAM_MODE                                          0x141c
#define MV64340_EXTENDED_DRAM_MODE                                  0x1420
#define MV64340_SDRAM_CROSS_BAR_CONTROL_LOW                         0x1430
#define MV64340_SDRAM_CROSS_BAR_CONTROL_HIGH                        0x1434
#define MV64340_SDRAM_CROSS_BAR_TIMEOUT                             0x1438
#define MV64340_SDRAM_ADDR_CTRL_PADS_CALIBRATION                    0x14c0
#define MV64340_SDRAM_DATA_PADS_CALIBRATION                         0x14c4

/****************************************/
/* SDRAM Error Report                   */
/****************************************/

#define MV64340_SDRAM_ERROR_DATA_LOW                                0x1444
#define MV64340_SDRAM_ERROR_DATA_HIGH                               0x1440
#define MV64340_SDRAM_ERROR_ADDR                                    0x1450
#define MV64340_SDRAM_RECEIVED_ECC                                  0x1448
#define MV64340_SDRAM_CALCULATED_ECC                                0x144c
#define MV64340_SDRAM_ECC_CONTROL                                   0x1454
#define MV64340_SDRAM_ECC_ERROR_COUNTER                             0x1458

/******************************************/
/*  Controlled Delay Line (CDL) Registers */
/******************************************/

#define MV64340_DFCDL_CONFIG0                                       0x1480
#define MV64340_DFCDL_CONFIG1                                       0x1484
#define MV64340_DLL_WRITE                                           0x1488
#define MV64340_DLL_READ                                            0x148c
#define MV64340_SRAM_ADDR                                           0x1490
#define MV64340_SRAM_DATA0                                          0x1494
#define MV64340_SRAM_DATA1                                          0x1498
#define MV64340_SRAM_DATA2                                          0x149c
#define MV64340_DFCL_PROBE                                          0x14a0

/******************************************/
/*   Debug Registers                      */
/******************************************/

#define MV64340_DUNIT_DEBUG_LOW                                     0x1460
#define MV64340_DUNIT_DEBUG_HIGH                                    0x1464
#define MV64340_DUNIT_MMASK                                         0X1b40

/****************************************/
/* Device Parameters			*/
/****************************************/

#define MV64340_DEVICE_BANK0_PARAMETERS				    0x45c
#define MV64340_DEVICE_BANK1_PARAMETERS				    0x460
#define MV64340_DEVICE_BANK2_PARAMETERS				    0x464
#define MV64340_DEVICE_BANK3_PARAMETERS				    0x468
#define MV64340_DEVICE_BOOT_BANK_PARAMETERS			    0x46c
#define MV64340_DEVICE_INTERFACE_CONTROL                            0x4c0
#define MV64340_DEVICE_INTERFACE_CROSS_BAR_CONTROL_LOW              0x4c8
#define MV64340_DEVICE_INTERFACE_CROSS_BAR_CONTROL_HIGH             0x4cc
#define MV64340_DEVICE_INTERFACE_CROSS_BAR_TIMEOUT                  0x4c4

/****************************************/
/* Device interrupt registers		*/
/****************************************/

#define MV64340_DEVICE_INTERRUPT_CAUSE				    0x4d0
#define MV64340_DEVICE_INTERRUPT_MASK				    0x4d4
#define MV64340_DEVICE_ERROR_ADDR				    0x4d8
#define MV64340_DEVICE_ERROR_DATA   				    0x4dc
#define MV64340_DEVICE_ERROR_PARITY     			    0x4e0

/****************************************/
/* Device debug registers   		*/
/****************************************/

#define MV64340_DEVICE_DEBUG_LOW     				    0x4e4
#define MV64340_DEVICE_DEBUG_HIGH     				    0x4e8
#define MV64340_RUNIT_MMASK                                         0x4f0

/****************************************/
/* PCI Slave Address Decoding registers */
/****************************************/

#define MV64340_PCI_0_CS_0_BANK_SIZE                                0xc08
#define MV64340_PCI_1_CS_0_BANK_SIZE                                0xc88
#define MV64340_PCI_0_CS_1_BANK_SIZE                                0xd08
#define MV64340_PCI_1_CS_1_BANK_SIZE                                0xd88
#define MV64340_PCI_0_CS_2_BANK_SIZE                                0xc0c
#define MV64340_PCI_1_CS_2_BANK_SIZE                                0xc8c
#define MV64340_PCI_0_CS_3_BANK_SIZE                                0xd0c
#define MV64340_PCI_1_CS_3_BANK_SIZE                                0xd8c
#define MV64340_PCI_0_DEVCS_0_BANK_SIZE                             0xc10
#define MV64340_PCI_1_DEVCS_0_BANK_SIZE                             0xc90
#define MV64340_PCI_0_DEVCS_1_BANK_SIZE                             0xd10
#define MV64340_PCI_1_DEVCS_1_BANK_SIZE                             0xd90
#define MV64340_PCI_0_DEVCS_2_BANK_SIZE                             0xd18
#define MV64340_PCI_1_DEVCS_2_BANK_SIZE                             0xd98
#define MV64340_PCI_0_DEVCS_3_BANK_SIZE                             0xc14
#define MV64340_PCI_1_DEVCS_3_BANK_SIZE                             0xc94
#define MV64340_PCI_0_DEVCS_BOOT_BANK_SIZE                          0xd14
#define MV64340_PCI_1_DEVCS_BOOT_BANK_SIZE                          0xd94
#define MV64340_PCI_0_P2P_MEM0_BAR_SIZE                             0xd1c
#define MV64340_PCI_1_P2P_MEM0_BAR_SIZE                             0xd9c
#define MV64340_PCI_0_P2P_MEM1_BAR_SIZE                             0xd20
#define MV64340_PCI_1_P2P_MEM1_BAR_SIZE                             0xda0
#define MV64340_PCI_0_P2P_I_O_BAR_SIZE                              0xd24
#define MV64340_PCI_1_P2P_I_O_BAR_SIZE                              0xda4
#define MV64340_PCI_0_CPU_BAR_SIZE                                  0xd28
#define MV64340_PCI_1_CPU_BAR_SIZE                                  0xda8
#define MV64340_PCI_0_INTERNAL_SRAM_BAR_SIZE                        0xe00
#define MV64340_PCI_1_INTERNAL_SRAM_BAR_SIZE                        0xe80
#define MV64340_PCI_0_EXPANSION_ROM_BAR_SIZE                        0xd2c
#define MV64340_PCI_1_EXPANSION_ROM_BAR_SIZE                        0xd9c
#define MV64340_PCI_0_BASE_ADDR_REG_ENABLE                          0xc3c
#define MV64340_PCI_1_BASE_ADDR_REG_ENABLE                          0xcbc
#define MV64340_PCI_0_CS_0_BASE_ADDR_REMAP			    0xc48
#define MV64340_PCI_1_CS_0_BASE_ADDR_REMAP			    0xcc8
#define MV64340_PCI_0_CS_1_BASE_ADDR_REMAP			    0xd48
#define MV64340_PCI_1_CS_1_BASE_ADDR_REMAP			    0xdc8
#define MV64340_PCI_0_CS_2_BASE_ADDR_REMAP			    0xc4c
#define MV64340_PCI_1_CS_2_BASE_ADDR_REMAP			    0xccc
#define MV64340_PCI_0_CS_3_BASE_ADDR_REMAP			    0xd4c
#define MV64340_PCI_1_CS_3_BASE_ADDR_REMAP			    0xdcc
#define MV64340_PCI_0_CS_0_BASE_HIGH_ADDR_REMAP			    0xF04
#define MV64340_PCI_1_CS_0_BASE_HIGH_ADDR_REMAP			    0xF84
#define MV64340_PCI_0_CS_1_BASE_HIGH_ADDR_REMAP			    0xF08
#define MV64340_PCI_1_CS_1_BASE_HIGH_ADDR_REMAP			    0xF88
#define MV64340_PCI_0_CS_2_BASE_HIGH_ADDR_REMAP			    0xF0C
#define MV64340_PCI_1_CS_2_BASE_HIGH_ADDR_REMAP			    0xF8C
#define MV64340_PCI_0_CS_3_BASE_HIGH_ADDR_REMAP			    0xF10
#define MV64340_PCI_1_CS_3_BASE_HIGH_ADDR_REMAP			    0xF90
#define MV64340_PCI_0_DEVCS_0_BASE_ADDR_REMAP			    0xc50
#define MV64340_PCI_1_DEVCS_0_BASE_ADDR_REMAP			    0xcd0
#define MV64340_PCI_0_DEVCS_1_BASE_ADDR_REMAP			    0xd50
#define MV64340_PCI_1_DEVCS_1_BASE_ADDR_REMAP			    0xdd0
#define MV64340_PCI_0_DEVCS_2_BASE_ADDR_REMAP			    0xd58
#define MV64340_PCI_1_DEVCS_2_BASE_ADDR_REMAP			    0xdd8
#define MV64340_PCI_0_DEVCS_3_BASE_ADDR_REMAP           	    0xc54
#define MV64340_PCI_1_DEVCS_3_BASE_ADDR_REMAP           	    0xcd4
#define MV64340_PCI_0_DEVCS_BOOTCS_BASE_ADDR_REMAP      	    0xd54
#define MV64340_PCI_1_DEVCS_BOOTCS_BASE_ADDR_REMAP      	    0xdd4
#define MV64340_PCI_0_P2P_MEM0_BASE_ADDR_REMAP_LOW                  0xd5c
#define MV64340_PCI_1_P2P_MEM0_BASE_ADDR_REMAP_LOW                  0xddc
#define MV64340_PCI_0_P2P_MEM0_BASE_ADDR_REMAP_HIGH                 0xd60
#define MV64340_PCI_1_P2P_MEM0_BASE_ADDR_REMAP_HIGH                 0xde0
#define MV64340_PCI_0_P2P_MEM1_BASE_ADDR_REMAP_LOW                  0xd64
#define MV64340_PCI_1_P2P_MEM1_BASE_ADDR_REMAP_LOW                  0xde4
#define MV64340_PCI_0_P2P_MEM1_BASE_ADDR_REMAP_HIGH                 0xd68
#define MV64340_PCI_1_P2P_MEM1_BASE_ADDR_REMAP_HIGH                 0xde8
#define MV64340_PCI_0_P2P_I_O_BASE_ADDR_REMAP                       0xd6c
#define MV64340_PCI_1_P2P_I_O_BASE_ADDR_REMAP                       0xdec 
#define MV64340_PCI_0_CPU_BASE_ADDR_REMAP_LOW                       0xd70
#define MV64340_PCI_1_CPU_BASE_ADDR_REMAP_LOW                       0xdf0
#define MV64340_PCI_0_CPU_BASE_ADDR_REMAP_HIGH                      0xd74
#define MV64340_PCI_1_CPU_BASE_ADDR_REMAP_HIGH                      0xdf4
#define MV64340_PCI_0_INTEGRATED_SRAM_BASE_ADDR_REMAP               0xf00
#define MV64340_PCI_1_INTEGRATED_SRAM_BASE_ADDR_REMAP               0xf80
#define MV64340_PCI_0_EXPANSION_ROM_BASE_ADDR_REMAP                 0xf38
#define MV64340_PCI_1_EXPANSION_ROM_BASE_ADDR_REMAP                 0xfb8
#define MV64340_PCI_0_ADDR_DECODE_CONTROL                           0xd3c
#define MV64340_PCI_1_ADDR_DECODE_CONTROL                           0xdbc
#define MV64340_PCI_0_HEADERS_RETARGET_CONTROL                      0xF40
#define MV64340_PCI_1_HEADERS_RETARGET_CONTROL                      0xFc0
#define MV64340_PCI_0_HEADERS_RETARGET_BASE                         0xF44
#define MV64340_PCI_1_HEADERS_RETARGET_BASE                         0xFc4
#define MV64340_PCI_0_HEADERS_RETARGET_HIGH                         0xF48
#define MV64340_PCI_1_HEADERS_RETARGET_HIGH                         0xFc8

/***********************************/
/*   PCI Control Register Map      */
/***********************************/

#define MV64340_PCI_0_DLL_STATUS_AND_COMMAND                        0x1d20
#define MV64340_PCI_1_DLL_STATUS_AND_COMMAND                        0x1da0
#define MV64340_PCI_0_MPP_PADS_DRIVE_CONTROL                        0x1d1C
#define MV64340_PCI_1_MPP_PADS_DRIVE_CONTROL                        0x1d9C
#define MV64340_PCI_0_COMMAND			         	    0xc00
#define MV64340_PCI_1_COMMAND					    0xc80
#define MV64340_PCI_0_MODE                                          0xd00
#define MV64340_PCI_1_MODE                                          0xd80
#define MV64340_PCI_0_RETRY	        	 		    0xc04
#define MV64340_PCI_1_RETRY				            0xc84
#define MV64340_PCI_0_READ_BUFFER_DISCARD_TIMER                     0xd04
#define MV64340_PCI_1_READ_BUFFER_DISCARD_TIMER                     0xd84
#define MV64340_PCI_0_MSI_TRIGGER_TIMER                             0xc38
#define MV64340_PCI_1_MSI_TRIGGER_TIMER                             0xcb8
#define MV64340_PCI_0_ARBITER_CONTROL                               0x1d00
#define MV64340_PCI_1_ARBITER_CONTROL                               0x1d80
#define MV64340_PCI_0_CROSS_BAR_CONTROL_LOW                         0x1d08
#define MV64340_PCI_1_CROSS_BAR_CONTROL_LOW                         0x1d88
#define MV64340_PCI_0_CROSS_BAR_CONTROL_HIGH                        0x1d0c
#define MV64340_PCI_1_CROSS_BAR_CONTROL_HIGH                        0x1d8c
#define MV64340_PCI_0_CROSS_BAR_TIMEOUT                             0x1d04
#define MV64340_PCI_1_CROSS_BAR_TIMEOUT                             0x1d84
#define MV64340_PCI_0_SYNC_BARRIER_TRIGGER_REG                      0x1D18
#define MV64340_PCI_1_SYNC_BARRIER_TRIGGER_REG                      0x1D98
#define MV64340_PCI_0_SYNC_BARRIER_VIRTUAL_REG                      0x1d10
#define MV64340_PCI_1_SYNC_BARRIER_VIRTUAL_REG                      0x1d90
#define MV64340_PCI_0_P2P_CONFIG                                    0x1d14
#define MV64340_PCI_1_P2P_CONFIG                                    0x1d94

#define MV64340_PCI_0_ACCESS_CONTROL_BASE_0_LOW                     0x1e00
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_0_HIGH                    0x1e04
#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_0                         0x1e08
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_1_LOW                     0x1e10
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_1_HIGH                    0x1e14
#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_1                         0x1e18
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_2_LOW                     0x1e20
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_2_HIGH                    0x1e24
#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_2                         0x1e28
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_3_LOW                     0x1e30
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_3_HIGH                    0x1e34
#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_3                         0x1e38
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_4_LOW                     0x1e40
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_4_HIGH                    0x1e44
#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_4                         0x1e48
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_5_LOW                     0x1e50
#define MV64340_PCI_0_ACCESS_CONTROL_BASE_5_HIGH                    0x1e54
#define MV64340_PCI_0_ACCESS_CONTROL_SIZE_5                         0x1e58

#define MV64340_PCI_1_ACCESS_CONTROL_BASE_0_LOW                     0x1e80
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_0_HIGH                    0x1e84
#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_0                         0x1e88
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_1_LOW                     0x1e90
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_1_HIGH                    0x1e94
#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_1                         0x1e98
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_2_LOW                     0x1ea0
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_2_HIGH                    0x1ea4
#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_2                         0x1ea8
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_3_LOW                     0x1eb0
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_3_HIGH                    0x1eb4
#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_3                         0x1eb8
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_4_LOW                     0x1ec0
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_4_HIGH                    0x1ec4
#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_4                         0x1ec8
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_5_LOW                     0x1ed0
#define MV64340_PCI_1_ACCESS_CONTROL_BASE_5_HIGH                    0x1ed4
#define MV64340_PCI_1_ACCESS_CONTROL_SIZE_5                         0x1ed8

/****************************************/
/*   PCI Configuration Access Registers */
/****************************************/

#define MV64340_PCI_0_CONFIG_ADDR 				    0xcf8
#define MV64340_PCI_0_CONFIG_DATA_VIRTUAL_REG                       0xcfc
#define MV64340_PCI_1_CONFIG_ADDR 				    0xc78
#define MV64340_PCI_1_CONFIG_DATA_VIRTUAL_REG                       0xc7c
#define MV64340_PCI_0_INTERRUPT_ACKNOWLEDGE_VIRTUAL_REG	            0xc34
#define MV64340_PCI_1_INTERRUPT_ACKNOWLEDGE_VIRTUAL_REG	            0xcb4

/****************************************/
/*   PCI Error Report Registers         */
/****************************************/

#define MV64340_PCI_0_SERR_MASK					    0xc28
#define MV64340_PCI_1_SERR_MASK					    0xca8
#define MV64340_PCI_0_ERROR_ADDR_LOW                                0x1d40
#define MV64340_PCI_1_ERROR_ADDR_LOW                                0x1dc0
#define MV64340_PCI_0_ERROR_ADDR_HIGH                               0x1d44
#define MV64340_PCI_1_ERROR_ADDR_HIGH                               0x1dc4
#define MV64340_PCI_0_ERROR_ATTRIBUTE                               0x1d48
#define MV64340_PCI_1_ERROR_ATTRIBUTE                               0x1dc8
#define MV64340_PCI_0_ERROR_COMMAND                                 0x1d50
#define MV64340_PCI_1_ERROR_COMMAND                                 0x1dd0
#define MV64340_PCI_0_ERROR_CAUSE                                   0x1d58
#define MV64340_PCI_1_ERROR_CAUSE                                   0x1dd8
#define MV64340_PCI_0_ERROR_MASK                                    0x1d5c
#define MV64340_PCI_1_ERROR_MASK                                    0x1ddc

/****************************************/
/*   PCI Debug Registers                */
/****************************************/

#define MV64340_PCI_0_MMASK                                         0X1D24
#define MV64340_PCI_1_MMASK                                         0X1DA4

/*********************************************/
/* PCI Configuration, Function 0, Registers  */
/*********************************************/

#define MV64340_PCI_DEVICE_AND_VENDOR_ID 			    0x000
#define MV64340_PCI_STATUS_AND_COMMAND				    0x004
#define MV64340_PCI_CLASS_CODE_AND_REVISION_ID			    0x008
#define MV64340_PCI_BIST_HEADER_TYPE_LATENCY_TIMER_CACHE_LINE 	    0x00C

#define MV64340_PCI_SCS_0_BASE_ADDR_LOW   	      		    0x010
#define MV64340_PCI_SCS_0_BASE_ADDR_HIGH   		            0x014
#define MV64340_PCI_SCS_1_BASE_ADDR_LOW  	     	            0x018
#define MV64340_PCI_SCS_1_BASE_ADDR_HIGH 		            0x01C
#define MV64340_PCI_INTERNAL_REG_MEM_MAPPED_BASE_ADDR_LOW      	    0x020
#define MV64340_PCI_INTERNAL_REG_MEM_MAPPED_BASE_ADDR_HIGH     	    0x024
#define MV64340_PCI_SUBSYSTEM_ID_AND_SUBSYSTEM_VENDOR_ID	    0x02c
#define MV64340_PCI_EXPANSION_ROM_BASE_ADDR_REG	                    0x030
#define MV64340_PCI_CAPABILTY_LIST_POINTER                          0x034
#define MV64340_PCI_INTERRUPT_PIN_AND_LINE 			    0x03C
       /* capability list */
#define MV64340_PCI_POWER_MANAGEMENT_CAPABILITY                     0x040
#define MV64340_PCI_POWER_MANAGEMENT_STATUS_AND_CONTROL             0x044
#define MV64340_PCI_VPD_ADDR                                        0x048
#define MV64340_PCI_VPD_DATA                                        0x04c
#define MV64340_PCI_MSI_MESSAGE_CONTROL                             0x050
#define MV64340_PCI_MSI_MESSAGE_ADDR                                0x054
#define MV64340_PCI_MSI_MESSAGE_UPPER_ADDR                          0x058
#define MV64340_PCI_MSI_MESSAGE_DATA                                0x05c
#define MV64340_PCI_X_COMMAND                                       0x060
#define MV64340_PCI_X_STATUS                                        0x064
#define MV64340_PCI_COMPACT_PCI_HOT_SWAP                            0x068

/***********************************************/
/*   PCI Configuration, Function 1, Registers  */
/***********************************************/

#define MV64340_PCI_SCS_2_BASE_ADDR_LOW   			    0x110
#define MV64340_PCI_SCS_2_BASE_ADDR_HIGH			    0x114
#define MV64340_PCI_SCS_3_BASE_ADDR_LOW 			    0x118
#define MV64340_PCI_SCS_3_BASE_ADDR_HIGH			    0x11c
#define MV64340_PCI_INTERNAL_SRAM_BASE_ADDR_LOW          	    0x120
#define MV64340_PCI_INTERNAL_SRAM_BASE_ADDR_HIGH         	    0x124

/***********************************************/
/*  PCI Configuration, Function 2, Registers   */
/***********************************************/

#define MV64340_PCI_DEVCS_0_BASE_ADDR_LOW	    		    0x210
#define MV64340_PCI_DEVCS_0_BASE_ADDR_HIGH 			    0x214
#define MV64340_PCI_DEVCS_1_BASE_ADDR_LOW 			    0x218
#define MV64340_PCI_DEVCS_1_BASE_ADDR_HIGH      		    0x21c
#define MV64340_PCI_DEVCS_2_BASE_ADDR_LOW 			    0x220
#define MV64340_PCI_DEVCS_2_BASE_ADDR_HIGH      		    0x224

/***********************************************/
/*  PCI Configuration, Function 3, Registers   */
/***********************************************/

#define MV64340_PCI_DEVCS_3_BASE_ADDR_LOW	    		    0x310
#define MV64340_PCI_DEVCS_3_BASE_ADDR_HIGH 			    0x314
#define MV64340_PCI_BOOT_CS_BASE_ADDR_LOW			    0x318
#define MV64340_PCI_BOOT_CS_BASE_ADDR_HIGH      		    0x31c
#define MV64340_PCI_CPU_BASE_ADDR_LOW 				    0x220
#define MV64340_PCI_CPU_BASE_ADDR_HIGH      			    0x224

/***********************************************/
/*  PCI Configuration, Function 4, Registers   */
/***********************************************/

#define MV64340_PCI_P2P_MEM0_BASE_ADDR_LOW  			    0x410
#define MV64340_PCI_P2P_MEM0_BASE_ADDR_HIGH 			    0x414
#define MV64340_PCI_P2P_MEM1_BASE_ADDR_LOW   			    0x418
#define MV64340_PCI_P2P_MEM1_BASE_ADDR_HIGH 			    0x41c
#define MV64340_PCI_P2P_I_O_BASE_ADDR                 	            0x420
#define MV64340_PCI_INTERNAL_REGS_I_O_MAPPED_BASE_ADDR              0x424

/****************************************/
/* Messaging Unit Registers (I20)   	*/
/****************************************/

#define MV64340_I2O_INBOUND_MESSAGE_REG0_PCI_0_SIDE		    0x010
#define MV64340_I2O_INBOUND_MESSAGE_REG1_PCI_0_SIDE  		    0x014
#define MV64340_I2O_OUTBOUND_MESSAGE_REG0_PCI_0_SIDE 		    0x018
#define MV64340_I2O_OUTBOUND_MESSAGE_REG1_PCI_0_SIDE  		    0x01C
#define MV64340_I2O_INBOUND_DOORBELL_REG_PCI_0_SIDE  		    0x020
#define MV64340_I2O_INBOUND_INTERRUPT_CAUSE_REG_PCI_0_SIDE          0x024
#define MV64340_I2O_INBOUND_INTERRUPT_MASK_REG_PCI_0_SIDE	    0x028
#define MV64340_I2O_OUTBOUND_DOORBELL_REG_PCI_0_SIDE 		    0x02C
#define MV64340_I2O_OUTBOUND_INTERRUPT_CAUSE_REG_PCI_0_SIDE         0