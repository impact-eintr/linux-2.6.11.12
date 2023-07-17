/*
 *	PCI Class, Vendor and Device IDs
 *
 *	Please keep sorted.
 */

/* Device classes and subclasses */

#define PCI_CLASS_NOT_DEFINED		0x0000
#define PCI_CLASS_NOT_DEFINED_VGA	0x0001

#define PCI_BASE_CLASS_STORAGE		0x01
#define PCI_CLASS_STORAGE_SCSI		0x0100
#define PCI_CLASS_STORAGE_IDE		0x0101
#define PCI_CLASS_STORAGE_FLOPPY	0x0102
#define PCI_CLASS_STORAGE_IPI		0x0103
#define PCI_CLASS_STORAGE_RAID		0x0104
#define PCI_CLASS_STORAGE_OTHER		0x0180

#define PCI_BASE_CLASS_NETWORK		0x02
#define PCI_CLASS_NETWORK_ETHERNET	0x0200
#define PCI_CLASS_NETWORK_TOKEN_RING	0x0201
#define PCI_CLASS_NETWORK_FDDI		0x0202
#define PCI_CLASS_NETWORK_ATM		0x0203
#define PCI_CLASS_NETWORK_OTHER		0x0280

#define PCI_BASE_CLASS_DISPLAY		0x03
#define PCI_CLASS_DISPLAY_VGA		0x0300
#define PCI_CLASS_DISPLAY_XGA		0x0301
#define PCI_CLASS_DISPLAY_3D		0x0302
#define PCI_CLASS_DISPLAY_OTHER		0x0380

#define PCI_BASE_CLASS_MULTIMEDIA	0x04
#define PCI_CLASS_MULTIMEDIA_VIDEO	0x0400
#define PCI_CLASS_MULTIMEDIA_AUDIO	0x0401
#define PCI_CLASS_MULTIMEDIA_PHONE	0x0402
#define PCI_CLASS_MULTIMEDIA_OTHER	0x0480

#define PCI_BASE_CLASS_MEMORY		0x05
#define PCI_CLASS_MEMORY_RAM		0x0500
#define PCI_CLASS_MEMORY_FLASH		0x0501
#define PCI_CLASS_MEMORY_OTHER		0x0580

#define PCI_BASE_CLASS_BRIDGE		0x06
#define PCI_CLASS_BRIDGE_HOST		0x0600
#define PCI_CLASS_BRIDGE_ISA		0x0601
#define PCI_CLASS_BRIDGE_EISA		0x0602
#define PCI_CLASS_BRIDGE_MC		0x0603
#define PCI_CLASS_BRIDGE_PCI		0x0604
#define PCI_CLASS_BRIDGE_PCMCIA		0x0605
#define PCI_CLASS_BRIDGE_NUBUS		0x0606
#define PCI_CLASS_BRIDGE_CARDBUS	0x0607
#define PCI_CLASS_BRIDGE_RACEWAY	0x0608
#define PCI_CLASS_BRIDGE_OTHER		0x0680

#define PCI_BASE_CLASS_COMMUNICATION	0x07
#define PCI_CLASS_COMMUNICATION_SERIAL	0x0700
#define PCI_CLASS_COMMUNICATION_PARALLEL 0x0701
#define PCI_CLASS_COMMUNICATION_MULTISERIAL 0x0702
#define PCI_CLASS_COMMUNICATION_MODEM	0x0703
#define PCI_CLASS_COMMUNICATION_OTHER	0x0780

#define PCI_BASE_CLASS_SYSTEM		0x08
#define PCI_CLASS_SYSTEM_PIC		0x0800
#define PCI_CLASS_SYSTEM_DMA		0x0801
#define PCI_CLASS_SYSTEM_TIMER		0x0802
#define PCI_CLASS_SYSTEM_RTC		0x0803
#define PCI_CLASS_SYSTEM_PCI_HOTPLUG	0x0804
#define PCI_CLASS_SYSTEM_OTHER		0x0880

#define PCI_BASE_CLASS_INPUT		0x09
#define PCI_CLASS_INPUT_KEYBOARD	0x0900
#define PCI_CLASS_INPUT_PEN		0x0901
#define PCI_CLASS_INPUT_MOUSE		0x0902
#define PCI_CLASS_INPUT_SCANNER		0x0903
#define PCI_CLASS_INPUT_GAMEPORT	0x0904
#define PCI_CLASS_INPUT_OTHER		0x0980

#define PCI_BASE_CLASS_DOCKING		0x0a
#define PCI_CLASS_DOCKING_GENERIC	0x0a00
#define PCI_CLASS_DOCKING_OTHER		0x0a80

#define PCI_BASE_CLASS_PROCESSOR	0x0b
#define PCI_CLASS_PROCESSOR_386		0x0b00
#define PCI_CLASS_PROCESSOR_486		0x0b01
#define PCI_CLASS_PROCESSOR_PENTIUM	0x0b02
#define PCI_CLASS_PROCESSOR_ALPHA	0x0b10
#define PCI_CLASS_PROCESSOR_POWERPC	0x0b20
#define PCI_CLASS_PROCESSOR_MIPS	0x0b30
#define PCI_CLASS_PROCESSOR_CO		0x0b40

#define PCI_BASE_CLASS_SERIAL		0x0c
#define PCI_CLASS_SERIAL_FIREWIRE	0x0c00
#define PCI_CLASS_SERIAL_ACCESS		0x0c01
#define PCI_CLASS_SERIAL_SSA		0x0c02
#define PCI_CLASS_SERIAL_USB		0x0c03
#define PCI_CLASS_SERIAL_FIBER		0x0c04
#define PCI_CLASS_SERIAL_SMBUS		0x0c05

#define PCI_BASE_CLASS_INTELLIGENT	0x0e
#define PCI_CLASS_INTELLIGENT_I2O	0x0e00

#define PCI_BASE_CLASS_SATELLITE	0x0f
#define PCI_CLASS_SATELLITE_TV		0x0f00
#define PCI_CLASS_SATELLITE_AUDIO	0x0f01
#define PCI_CLASS_SATELLITE_VOICE	0x0f03
#define PCI_CLASS_SATELLITE_DATA	0x0f04

#define PCI_BASE_CLASS_CRYPT		0x10
#define PCI_CLASS_CRYPT_NETWORK		0x1000
#define PCI_CLASS_CRYPT_ENTERTAINMENT	0x1001
#define PCI_CLASS_CRYPT_OTHER		0x1080

#define PCI_BASE_CLASS_SIGNAL_PROCESSING 0x11
#define PCI_CLASS_SP_DPIO		0x1100
#define PCI_CLASS_SP_OTHER		0x1180

#define PCI_CLASS_OTHERS		0xff

/* Vendors and devices.  Sort key: vendor first, device next. */

#define PCI_VENDOR_ID_DYNALINK		0x0675
#define PCI_DEVICE_ID_DYNALINK_IS64PH	0x1702

#define PCI_VENDOR_ID_BERKOM			0x0871
#define PCI_DEVICE_ID_BERKOM_A1T		0xffa1
#define PCI_DEVICE_ID_BERKOM_T_CONCEPT		0xffa2
#define PCI_DEVICE_ID_BERKOM_A4T		0xffa4
#define PCI_DEVICE_ID_BERKOM_SCITEL_QUADRO	0xffa8

#define PCI_VENDOR_ID_COMPAQ		0x0e11
#define PCI_DEVICE_ID_COMPAQ_TOKENRING	0x0508
#define PCI_DEVICE_ID_COMPAQ_1280	0x3033
#define PCI_DEVICE_ID_COMPAQ_TRIFLEX	0x4000
#define PCI_DEVICE_ID_COMPAQ_6010	0x6010
#define PCI_DEVICE_ID_COMPAQ_TACHYON	0xa0fc
#define PCI_DEVICE_ID_COMPAQ_SMART2P	0xae10
#define PCI_DEVICE_ID_COMPAQ_NETEL100	0xae32
#define PCI_DEVICE_ID_COMPAQ_NETEL10	0xae34
#define PCI_DEVICE_ID_COMPAQ_TRIFLEX_IDE 0xae33
#define PCI_DEVICE_ID_COMPAQ_NETFLEX3I	0xae35
#define PCI_DEVICE_ID_COMPAQ_NETEL100D	0xae40
#define PCI_DEVICE_ID_COMPAQ_NETEL100PI	0xae43
#define PCI_DEVICE_ID_COMPAQ_NETEL100I	0xb011
#define PCI_DEVICE_ID_COMPAQ_CISS	0xb060
#define PCI_DEVICE_ID_COMPAQ_CISSB	0xb178
#define PCI_DEVICE_ID_COMPAQ_CISSC	0x46
#define PCI_DEVICE_ID_COMPAQ_THUNDER	0xf130
#define PCI_DEVICE_ID_COMPAQ_NETFLEX3B	0xf150

#define PCI_VENDOR_ID_NCR		0x1000
#define PCI_VENDOR_ID_LSI_LOGIC		0x1000
#define PCI_DEVICE_ID_NCR_53C810	0x0001
#define PCI_DEVICE_ID_NCR_53C820	0x0002
#define PCI_DEVICE_ID_NCR_53C825	0x0003
#define PCI_DEVICE_ID_NCR_53C815	0x0004
#define PCI_DEVICE_ID_LSI_53C810AP	0x0005
#define PCI_DEVICE_ID_NCR_53C860	0x0006
#define PCI_DEVICE_ID_LSI_53C1510	0x000a
#define PCI_DEVICE_ID_NCR_53C896	0x000b
#define PCI_DEVICE_ID_NCR_53C895	0x000c
#define PCI_DEVICE_ID_NCR_53C885	0x000d
#define PCI_DEVICE_ID_NCR_53C875	0x000f
#define PCI_DEVICE_ID_NCR_53C1510	0x0010
#define PCI_DEVICE_ID_LSI_53C895A	0x0012
#define PCI_DEVICE_ID_LSI_53C875A	0x0013
#define PCI_DEVICE_ID_LSI_53C1010_33	0x0020
#define PCI_DEVICE_ID_LSI_53C1010_66	0x0021
#define PCI_DEVICE_ID_LSI_53C1030	0x0030
#define PCI_DEVICE_ID_LSI_1030_53C1035	0x0032
#define PCI_DEVICE_ID_LSI_53C1035	0x0040
#define PCI_DEVICE_ID_NCR_53C875J	0x008f
#define PCI_DEVICE_ID_LSI_FC909		0x0621
#define PCI_DEVICE_ID_LSI_FC929		0x0622
#define PCI_DEVICE_ID_LSI_FC929_LAN	0x0623
#define PCI_DEVICE_ID_LSI_FC919		0x0624
#define PCI_DEVICE_ID_LSI_FC919_LAN	0x0625
#define PCI_DEVICE_ID_LSI_FC929X	0x0626
#define PCI_DEVICE_ID_LSI_FC939X	0x0642
#define PCI_DEVICE_ID_LSI_FC949X	0x0640
#define PCI_DEVICE_ID_LSI_FC919X	0x0628
#define PCI_DEVICE_ID_NCR_YELLOWFIN	0x0701
#define PCI_DEVICE_ID_LSI_61C102	0x0901
#define PCI_DEVICE_ID_LSI_63C815	0x1000
#define PCI_DEVICE_ID_LSI_SAS1064	0x0050
#define PCI_DEVICE_ID_LSI_SAS1066	0x005E
#define PCI_DEVICE_ID_LSI_SAS1068	0x0054
#define PCI_DEVICE_ID_LSI_SAS1064A	0x005C
#define PCI_DEVICE_ID_LSI_SAS1064E	0x0056
#define PCI_DEVICE_ID_LSI_SAS1066E	0x005A
#define PCI_DEVICE_ID_LSI_SAS1068E	0x0058
#define PCI_DEVICE_ID_LSI_SAS1078	0x0060

#define PCI_VENDOR_ID_ATI		0x1002
/* Mach64 */
#define PCI_DEVICE_ID_ATI_68800		0x4158
#define PCI_DEVICE_ID_ATI_215CT222	0x4354
#define PCI_DEVICE_ID_ATI_210888CX	0x4358
#define PCI_DEVICE_ID_ATI_215ET222	0x4554
/* Mach64 / Rage */
#define PCI_DEVICE_ID_ATI_215GB		0x4742
#define PCI_DEVICE_ID_ATI_215GD		0x4744
#define PCI_DEVICE_ID_ATI_215GI		0x4749
#define PCI_DEVICE_ID_ATI_215GP		0x4750
#define PCI_DEVICE_ID_ATI_215GQ		0x4751
#define PCI_DEVICE_ID_ATI_215XL		0x4752
#define PCI_DEVICE_ID_ATI_215GT		0x4754
#define PCI_DEVICE_ID_ATI_215GTB	0x4755
#define PCI_DEVICE_ID_ATI_215_IV	0x4756
#define PCI_DEVICE_ID_ATI_215_IW	0x4757
#define PCI_DEVICE_ID_ATI_215_IZ	0x475A
#define PCI_DEVICE_ID_ATI_210888GX	0x4758
#define PCI_DEVICE_ID_ATI_215_LB	0x4c42
#define PCI_DEVICE_ID_ATI_215_LD	0x4c44
#define PCI_DEVICE_ID_ATI_215_LG	0x4c47
#define PCI_DEVICE_ID_ATI_215_LI	0x4c49
#define PCI_DEVICE_ID_ATI_215_LM	0x4c4D
#define PCI_DEVICE_ID_ATI_215_LN	0x4c4E
#define PCI_DEVICE_ID_ATI_215_LR	0x4c52
#define PCI_DEVICE_ID_ATI_215_LS	0x4c53
#define PCI_DEVICE_ID_ATI_264_LT	0x4c54
/* Mach64 VT */
#define PCI_DEVICE_ID_ATI_264VT		0x5654
#define PCI_DEVICE_ID_ATI_264VU		0x5655
#define PCI_DEVICE_ID_ATI_264VV		0x5656
/* Rage128 GL */
#define PCI_DEVICE_ID_ATI_RAGE128_RE	0x5245
#define PCI_DEVICE_ID_ATI_RAGE128_RF	0x5246
#define PCI_DEVICE_ID_ATI_RAGE128_RG	0x5247
/* Rage128 VR */
#define PCI_DEVICE_ID_ATI_RAGE128_RK	0x524b
#define PCI_DEVICE_ID_ATI_RAGE128_RL	0x524c
#define PCI_DEVICE_ID_ATI_RAGE128_SE	0x5345
#define PCI_DEVICE_ID_ATI_RAGE128_SF	0x5346
#define PCI_DEVICE_ID_ATI_RAGE128_SG	0x5347
#define PCI_DEVICE_ID_ATI_RAGE128_SH	0x5348
#define PCI_DEVICE_ID_ATI_RAGE128_SK	0x534b
#define PCI_DEVICE_ID_ATI_RAGE128_SL	0x534c
#define PCI_DEVICE_ID_ATI_RAGE128_SM	0x534d
#define PCI_DEVICE_ID_ATI_RAGE128_SN	0x534e
/* Rage128 Ultra */
#define PCI_DEVICE_ID_ATI_RAGE128_TF	0x5446
#define PCI_DEVICE_ID_ATI_RAGE128_TL	0x544c
#define PCI_DEVICE_ID_ATI_RAGE128_TR	0x5452
#define PCI_DEVICE_ID_ATI_RAGE128_TS	0x5453
#define PCI_DEVICE_ID_ATI_RAGE128_TT	0x5454
#define PCI_DEVICE_ID_ATI_RAGE128_TU	0x5455
/* Rage128 M3 */
#define PCI_DEVICE_ID_ATI_RAGE128_LE	0x4c45
#define PCI_DEVICE_ID_ATI_RAGE128_LF	0x4c46
/* Rage128 M4 */
#define PCI_DEVICE_ID_ATI_RAGE128_MF    0x4d46
#define PCI_DEVICE_ID_ATI_RAGE128_ML    0x4d4c
/* Rage128 Pro GL */
#define PCI_DEVICE_ID_ATI_RAGE128_PA	0x5041
#define PCI_DEVICE_ID_ATI_RAGE128_PB	0x5042
#define PCI_DEVICE_ID_ATI_RAGE128_PC	0x5043
#define PCI_DEVICE_ID_ATI_RAGE128_PD	0x5044
#define PCI_DEVICE_ID_ATI_RAGE128_PE	0x5045
#define PCI_DEVICE_ID_ATI_RAGE128_PF	0x5046
/* Rage128 Pro VR */
#define PCI_DEVICE_ID_ATI_RAGE128_PG	0x5047
#define PCI_DEVICE_ID_ATI_RAGE128_PH	0x5048
#define PCI_DEVICE_ID_ATI_RAGE128_PI	0x5049
#define PCI_DEVICE_ID_ATI_RAGE128_PJ	0x504A
#define PCI_DEVICE_ID_ATI_RAGE128_PK	0x504B
#define PCI_DEVICE_ID_ATI_RAGE128_PL	0x504C
#define PCI_DEVICE_ID_ATI_RAGE128_PM	0x504D
#define PCI_DEVICE_ID_ATI_RAGE128_PN	0x504E
#define PCI_DEVICE_ID_ATI_RAGE128_PO	0x504F
#define PCI_DEVICE_ID_ATI_RAGE128_PP	0x5050
#define PCI_DEVICE_ID_ATI_RAGE128_PQ	0x5051
#define PCI_DEVICE_ID_ATI_RAGE128_PR	0x5052
#define PCI_DEVICE_ID_ATI_RAGE128_TR	0x5452
#define PCI_DEVICE_ID_ATI_RAGE128_PS	0x5053
#define PCI_DEVICE_ID_ATI_RAGE128_PT	0x5054
#define PCI_DEVICE_ID_ATI_RAGE128_PU	0x5055
#define PCI_DEVICE_ID_ATI_RAGE128_PV	0x5056
#define PCI_DEVICE_ID_ATI_RAGE128_PW	0x5057
#define PCI_DEVICE_ID_ATI_RAGE128_PX	0x5058
/* Rage128 M4 */
#define PCI_DEVICE_ID_ATI_RADEON_LE	0x4d45
#define PCI_DEVICE_ID_ATI_RADEON_LF	0x4d46
/* Radeon R100 */
#define PCI_DEVICE_ID_ATI_RADEON_QD	0x5144
#define PCI_DEVICE_ID_ATI_RADEON_QE	0x5145
#define PCI_DEVICE_ID_ATI_RADEON_QF	0x5146
#define PCI_DEVICE_ID_ATI_RADEON_QG	0x5147
/* Radeon RV100 (VE) */
#define PCI_DEVICE_ID_ATI_RADEON_QY	0x5159
#define PCI_DEVICE_ID_ATI_RADEON_QZ	0x515a
/* Radeon R200 (8500) */
#define PCI_DEVICE_ID_ATI_RADEON_QL	0x514c
#define PCI_DEVICE_ID_ATI_RADEON_QN	0x514e
#define PCI_DEVICE_ID_ATI_RADEON_QO	0x514f
#define PCI_DEVICE_ID_ATI_RADEON_Ql	0x516c
#define PCI_DEVICE_ID_ATI_RADEON_BB	0x4242
/* Radeon R200 (9100) */
#define PCI_DEVICE_ID_ATI_RADEON_QM	0x514d
/* Radeon RV200 (7500) */
#define PCI_DEVICE_ID_ATI_RADEON_QW	0x5157
#define PCI_DEVICE_ID_ATI_RADEON_QX	0x5158
/* Radeon NV-100 */
#define PCI_DEVICE_ID_ATI_RADEON_N1	0x5159
#define PCI_DEVICE_ID_ATI_RADEON_N2	0x515a
/* Radeon RV250 (9000) */
#define PCI_DEVICE_ID_ATI_RADEON_Id	0x4964
#define PCI_DEVICE_ID_ATI_RADEON_Ie	0x4965
#define PCI_DEVICE_ID_ATI_RADEON_If	0x4966
#define PCI_DEVICE_ID_ATI_RADEON_Ig	0x4967
/* Radeon RV280 (9200) */
#define PCI_DEVICE_ID_ATI_RADEON_Y_	0x5960
#define PCI_DEVICE_ID_ATI_RADEON_Ya	0x5961
#define PCI_DEVICE_ID_ATI_RADEON_Yd	0x5964
/* Radeon R300 (9500) */
#define PCI_DEVICE_ID_ATI_RADEON_AD	0x4144
/* Radeon R300 (9700) */
#define PCI_DEVICE_ID_ATI_RADEON_ND	0x4e44
#define PCI_DEVICE_ID_ATI_RADEON_NE	0x4e45
#define PCI_DEVICE_ID_ATI_RADEON_NF	0x4e46
#define PCI_DEVICE_ID_ATI_RADEON_NG	0x4e47
#define PCI_DEVICE_ID_ATI_RADEON_AE	0x4145
#define PCI_DEVICE_ID_ATI_RADEON_AF	0x4146
/* Radeon R350 (9800) */
#define PCI_DEVICE_ID_ATI_RADEON_NH	0x4e48
#define PCI_DEVICE_ID_ATI_RADEON_NI	0x4e49
/* Radeon RV350 (9600) */
#define PCI_DEVICE_ID_ATI_RADEON_AP	0x4150
#define PCI_DEVICE_ID_ATI_RADEON_AR	0x4152
/* Radeon M6 */
#define PCI_DEVICE_ID_ATI_RADEON_LY	0x4c59
#define PCI_DEVICE_ID_ATI_RADEON_LZ	0x4c5a
/* Radeon M7 */
#define PCI_DEVICE_ID_ATI_RADEON_LW	0x4c57
#define PCI_DEVICE_ID_ATI_RADEON_LX	0x4c58
/* Radeon M9 */
#define PCI_DEVICE_ID_ATI_RADEON_Ld	0x4c64
#define PCI_DEVICE_ID_ATI_RADEON_Le	0x4c65
#define PCI_DEVICE_ID_ATI_RADEON_Lf	0x4c66
#define PCI_DEVICE_ID_ATI_RADEON_Lg	0x4c67
/* Radeon */
#define PCI_DEVICE_ID_ATI_RADEON_RA	0x5144
#define PCI_DEVICE_ID_ATI_RADEON_RB	0x5145
#define PCI_DEVICE_ID_ATI_RADEON_RC	0x5146
#define PCI_DEVICE_ID_ATI_RADEON_RD	0x5147
/* RadeonIGP */
#define PCI_DEVICE_ID_ATI_RS100		0xcab0
#define PCI_DEVICE_ID_ATI_RS200		0xcab2
#define PCI_DEVICE_ID_ATI_RS200_B	0xcbb2
#define PCI_DEVICE_ID_ATI_RS250		0xcab3
#define PCI_DEVICE_ID_ATI_RS300_100	0x5830
#define PCI_DEVICE_ID_ATI_RS300_133	0x5831
#define PCI_DEVICE_ID_ATI_RS300_166	0x5832
#define PCI_DEVICE_ID_ATI_RS300_200	0x5833
/* ATI IXP Chipset */
#define PCI_DEVICE_ID_ATI_IXP200_IDE	0x4349
#define PCI_DEVICE_ID_ATI_IXP300_IDE	0x4369
#define PCI_DEVICE_ID_ATI_IXP400_IDE	0x4376

#define PCI_VENDOR_ID_VLSI		0x1004
#define PCI_DEVICE_ID_VLSI_82C592	0x0005
#define PCI_DEVICE_ID_VLSI_82C593	0x0006
#define PCI_DEVICE_ID_VLSI_82C594	0x0007
#define PCI_DEVICE_ID_VLSI_82C597	0x0009
#define PCI_DEVICE_ID_VLSI_82C541	0x000c
#define PCI_DEVICE_ID_VLSI_82C543	0x000d
#define PCI_DEVICE_ID_VLSI_82C532	0x0101
#define PCI_DEVICE_ID_VLSI_82C534	0x0102
#define PCI_DEVICE_ID_VLSI_82C535	0x0104
#define PCI_DEVICE_ID_VLSI_82C147	0x0105
#define PCI_DEVICE_ID_VLSI_VAS96011	0x0702

#define PCI_VENDOR_ID_ADL		0x1005
#define PCI_DEVICE_ID_ADL_2301		0x2301

#define PCI_VENDOR_ID_NS		0x100b
#define PCI_DEVICE_ID_NS_87415		0x0002
#define PCI_DEVICE_ID_NS_87560_LIO	0x000e
#define PCI_DEVICE_ID_NS_87560_USB	0x0012
#define PCI_DEVICE_ID_NS_83815		0x0020
#define PCI_DEVICE_ID_NS_83820		0x0022
#define PCI_DEVICE_ID_NS_SCx200_BRIDGE	0x0500
#define PCI_DEVICE_ID_NS_SCx200_SMI	0x0501
#define PCI_DEVICE_ID_NS_SCx200_IDE	0x0502
#define PCI_DEVICE_ID_NS_SCx200_AUDIO	0x0503
#define PCI_DEVICE_ID_NS_SCx200_VIDEO	0x0504
#define PCI_DEVICE_ID_NS_SCx200_XBUS	0x0505
#define PCI_DEVICE_ID_NS_SC1100_BRIDGE	0x0510
#define PCI_DEVICE_ID_NS_87410		0xd001

#define PCI_VENDOR_ID_TSENG		0x100c
#define PCI_DEVICE_ID_TSENG_W32P_2	0x3202
#define PCI_DEVICE_ID_TSENG_W32P_b	0x3205
#define PCI_DEVICE_ID_TSENG_W32P_c	0x3206
#define PCI_DEVICE_ID_TSENG_W32P_d	0x3207
#define PCI_DEVICE_ID_TSENG_ET6000	0x3208

#define PCI_VENDOR_ID_WEITEK		0x100e
#define PCI_DEVICE_ID_WEITEK_P9000	0x9001
#define PCI_DEVICE_ID_WEITEK_P9100	0x9100

#define PCI_VENDOR_ID_DEC		0x1011
#define PCI_DEVICE_ID_DEC_BRD		0x0001
#define PCI_DEVICE_ID_DEC_TULIP		0x0002
#define PCI_DEVICE_ID_DEC_TGA		0x0004
#define PCI_DEVICE_ID_DEC_TULIP_FAST	0x0009
#define PCI_DEVICE_ID_DEC_TGA2		0x000D
#define PCI_DEVICE_ID_DEC_FDDI		0x000F
#define PCI_DEVICE_ID_DEC_TULIP_PLUS	0x0014
#define PCI_DEVICE_ID_DEC_21142		0x0019
#define PCI_DEVICE_ID_DEC_21052		0x0021
#define PCI_DEVICE_ID_DEC_21150		0x0022
#define PCI_DEVICE_ID_DEC_21152		0x0024
#define PCI_DEVICE_ID_DEC_21153		0x0025
#define PCI_DEVICE_ID_DEC_21154		0x0026
#define PCI_DEVICE_ID_DEC_21285		0x1065
#define PCI_DEVICE_ID_COMPAQ_42XX	0x0046

#define PCI_VENDOR_ID_CIRRUS		0x1013
#define PCI_DEVICE_ID_CIRRUS_7548	0x0038
#define PCI_DEVICE_ID_CIRRUS_5430	0x00a0
#define PCI_DEVICE_ID_CIRRUS_5434_4	0x00a4
#define PCI_DEVICE_ID_CIRRUS_5434_8	0x00a8
#define PCI_DEVICE_ID_CIRRUS_5436	0x00ac
#define PCI_DEVICE_ID_CIRRUS_5446	0x00b8
#define PCI_DEVICE_ID_CIRRUS_5480	0x00bc
#define PCI_DEVICE_ID_CIRRUS_5462	0x00d0
#define PCI_DEVICE_ID_CIRRUS_5464	0x00d4
#define PCI_DEVICE_ID_CIRRUS_5465	0x00d6
#define PCI_DEVICE_ID_CIRRUS_6729	0x1100
#define PCI_DEVICE_ID_CIRRUS_6832	0x1110
#define PCI_DEVICE_ID_CIRRUS_7542	0x1200
#define PCI_DEVICE_ID_CIRRUS_7543	0x1202
#define PCI_DEVICE_ID_CIRRUS_7541	0x1204

#define PCI_VENDOR_ID_IBM		0x1014
#define PCI_DEVICE_ID_IBM_FIRE_CORAL	0x000a
#define PCI_DEVICE_ID_IBM_TR		0x0018
#define PCI_DEVICE_ID_IBM_82G2675	0x001d
#define PCI_DEVICE_ID_IBM_MCA		0x0020
#define PCI_DEVICE_ID_IBM_82351		0x0022
#define PCI_DEVICE_ID_IBM_PYTHON	0x002d
#define PCI_DEVICE_ID_IBM_SERVERAID	0x002e
#define PCI_DEVICE_ID_IBM_TR_WAKE	0x003e
#define PCI_DEVICE_ID_IBM_MPIC		0x0046
#define PCI_DEVICE_ID_IBM_3780IDSP	0x007d
#define PCI_DEVICE_ID_IBM_CHUKAR	0x0096
#define PCI_DEVICE_ID_IBM_CPC710_PCI64	0x00fc
#define PCI_DEVICE_ID_IBM_CPC710_PCI32	0x0105
#define	PCI_DEVICE_ID_IBM_405GP		0x0156
#define PCI_DEVICE_ID_IBM_SNIPE		0x0180
#define PCI_DEVICE_ID_IBM_SERVERAIDI960	0x01bd
#define PCI_DEVICE_ID_IBM_CITRINE		0x028C
#define PCI_DEVICE_ID_IBM_GEMSTONE		0xB166
#define PCI_DEVICE_ID_IBM_MPIC_2	0xffff
#define PCI_DEVICE_ID_IBM_ICOM_DEV_ID_1	0x0031
#define PCI_DEVICE_ID_IBM_ICOM_DEV_ID_2	0x0219
#define PCI_DEVICE_ID_IBM_ICOM_V2_TWO_PORTS_RVX		0x021A
#define PCI_DEVICE_ID_IBM_ICOM_V2_ONE_PORT_RVX_ONE_PORT_MDM	0x0251
#define PCI_DEVICE_ID_IBM_ICOM_FOUR_PORT_MODEL	0x252

#define PCI_VENDOR_ID_COMPEX2		0x101a // pci.ids says "AT&T GIS (NCR)"
#define PCI_DEVICE_ID_COMPEX2_100VG	0x0005

#define PCI_VENDOR_ID_WD		0x101c
#define PCI_DEVICE_ID_WD_7197		0x3296
#define PCI_DEVICE_ID_WD_90C		0xc24a

#define PCI_VENDOR_ID_AMI		0x101e
#define PCI_DEVICE_ID_AMI_MEGARAID3	0x1960
#define PCI_DEVICE_ID_AMI_MEGARAID	0x9010
#define PCI_DEVICE_ID_AMI_MEGARAID2	0x9060

#define PCI_VENDOR_ID_AMD		0x1022
#define PCI_DEVICE_ID_AMD_LANCE		0x2000
#define PCI_DEVICE_ID_AMD_LANCE_HOME	0x2001
#define PCI_DEVICE_ID_AMD_SCSI		0x2020
#define PCI_DEVICE_ID_AMD_SERENADE	0x36c0
#define PCI_DEVICE_ID_AMD_FE_GATE_7006	0x7006
#define PCI_DEVICE_ID_AMD_FE_GATE_7007	0x7007
#define PCI_DEVICE_ID_AMD_FE_GATE_700C	0x700C
#define PCI_DEVICE_ID_AMD_FE_GATE_700D	0x700D
#define PCI_DEVICE_ID_AMD_FE_GATE_700E	0x700E
#define PCI_DEVICE_ID_AMD_FE_GATE_700F	0x700F
#define PCI_DEVICE_ID_AMD_COBRA_7400	0x7400
#define PCI_DEVICE_ID_AMD_COBRA_7401	0x7401
#define PCI_DEVICE_ID_AMD_COBRA_7403	0x7403
#define PCI_DEVICE_ID_AMD_COBRA_7404	0x7404
#define PCI_DEVICE_ID_AMD_VIPER_7408	0x7408
#define PCI_DEVICE_ID_AMD_VIPER_7409	0x7409
#define PCI_DEVICE_ID_AMD_VIPER_740B	0x740B
#define PCI_DEVICE_ID_AMD_VIPER_740C	0x740C
#define PCI_DEVICE_ID_AMD_VIPER_7410	0x7410
#define PCI_DEVICE_ID_AMD_VIPER_7411	0x7411
#define PCI_DEVICE_ID_AMD_VIPER_7413	0x7413
#define PCI_DEVICE_ID_AMD_VIPER_7414	0x7414
#define PCI_DEVICE_ID_AMD_OPUS_7440	0x7440
#	define PCI_DEVICE_ID_AMD_VIPER_7440	PCI_DEVICE_ID_AMD_OPUS_7440
#define PCI_DEVICE_ID_AMD_OPUS_7441	0x7441
#	define PCI_DEVICE_ID_AMD_VIPER_7441	PCI_DEVICE_ID_AMD_OPUS_7441
#define PCI_DEVICE_ID_AMD_OPUS_7443	0x7443
#	define PCI_DEVICE_ID_AMD_VIPER_7443	PCI_DEVICE_ID_AMD_OPUS_7443
#define PCI_DEVICE_ID_AMD_OPUS_7445	0x7445
#define PCI_DEVICE_ID_AMD_OPUS_7448	0x7448
# define	PCI_DEVICE_ID_AMD_VIPER_7448	PCI_DEVICE_ID_AMD_OPUS_7448
#define PCI_DEVICE_ID_AMD_OPUS_7449	0x7449
#	define PCI_DEVICE_ID_AMD_VIPER_7449	PCI_DEVICE_ID_AMD_OPUS_7449
#define PCI_DEVICE_ID_AMD_8111_LAN	0x7462
#define PCI_DEVICE_ID_AMD_8111_IDE	0x7469
#define PCI_DEVICE_ID_AMD_8111_SMBUS2	0x746a
#define PCI_DEVICE_ID_AMD_8111_SMBUS	0x746b
#define PCI_DEVICE_ID_AMD_8111_AUDIO	0x746d
#define PCI_DEVICE_ID_AMD_8151_0	0x7454
#define PCI_DEVICE_ID_AMD_8131_APIC     0x7450

#define PCI_VENDOR_ID_TRIDENT		0x1023
#define PCI_DEVICE_ID_TRIDENT_4DWAVE_DX	0x2000
#define PCI_DEVICE_ID_TRIDENT_4DWAVE_NX	0x2001
#define PCI_DEVICE_ID_TRIDENT_9320	0x9320
#define PCI_DEVICE_ID_TRIDENT_9388	0x9388
#define PCI_DEVICE_ID_TRIDENT_9397	0x9397
#define PCI_DEVICE_ID_TRIDENT_939A	0x939A
#define PCI_DEVICE_ID_TRIDENT_9520	0x9520
#define PCI_DEVICE_ID_TRIDENT_9525	0x9525
#define PCI_DEVICE_ID_TRIDENT_9420	0x9420
#define PCI_DEVICE_ID_TRIDENT_9440	0x9440
#define PCI_DEVICE_ID_TRIDENT_9660	0x9660
#define PCI_DEVICE_ID_TRIDENT_9750	0x9750
#define PCI_DEVICE_ID_TRIDENT_9850	0x9850
#define PCI_DEVICE_ID_TRIDENT_9880	0x9880
#define PCI_DEVICE_ID_TRIDENT_8400	0x8400
#define PCI_DEVICE_ID_TRIDENT_8420	0x8420
#define PCI_DEVICE_ID_TRIDENT_8500	0x8500

#define PCI_VENDOR_ID_AI		0x1025
#define PCI_DEVICE_ID_AI_M1435		0x1435

#define PCI_VENDOR_ID_DELL		0x1028
#define PCI_DEVICE_ID_DELL_RACIII	0x0008
#define PCI_DEVICE_ID_DELL_RAC4		0x0012

#define PCI_VENDOR_ID_MATROX		0x102B
#define PCI_DEVICE_ID_MATROX_MGA_2	0x0518
#define PCI_DEVICE_ID_MATROX_MIL	0x0519
#define PCI_DEVICE_ID_MATROX_MYS	0x051A
#define PCI_DEVICE_ID_MATROX_MIL_2	0x051b
#define PCI_DEVICE_ID_MATROX_MIL_2_AGP	0x051f
#define PCI_DEVICE_ID_MATROX_MGA_IMP	0x0d10
#define PCI_DEVICE_ID_MATROX_G100_MM	0x1000
#define PCI_DEVICE_ID_MATROX_G100_AGP	0x1001
#define PCI_DEVICE_ID_MATROX_G200_PCI	0x0520
#define PCI_DEVICE_ID_MATROX_G200_AGP	0x0521
#define	PCI_DEVICE_ID_MATROX_G400	0x0525
#define PCI_DEVICE_ID_MATROX_G550	0x2527
#define PCI_DEVICE_ID_MATROX_VIA	0x4536

#define PCI_VENDOR_ID_CT		0x102c
#define PCI_DEVICE_ID_CT_69000		0x00c0
#define PCI_DEVICE_ID_CT_65545		0x00d8
#define PCI_DEVICE_ID_CT_65548		0x00dc
#define PCI_DEVICE_ID_CT_65550		0x00e0
#define PCI_DEVICE_ID_CT_65554		0x00e4
#define PCI_DEVICE_ID_CT_65555		0x00e5

#define PCI_VENDOR_ID_MIRO		0x1031
#define PCI_DEVICE_ID_MIRO_36050	0x5601
#define PCI_DEVICE_ID_MIRO_DC10PLUS	0x7efe
#define PCI_DEVICE_ID_MIRO_DC30PLUS	0xd801

#define PCI_VENDOR_ID_NEC		0x1033
#define PCI_DEVICE_ID_NEC_CBUS_1	0x0001 /* PCI-Cbus Bridge */
#define PCI_DEVICE_ID_NEC_LOCAL		0x0002 /* Local Bridge */
#define PCI_DEVICE_ID_NEC_ATM		0x0003 /* ATM LAN Controller */
#define PCI_DEVICE_ID_NEC_R4000		0x0004 /* R4000 Bridge */
#define PCI_DEVICE_ID_NEC_486		0x0005 /* 486 Like Peripheral Bus Bridge */
#define PCI_DEVICE_ID_NEC_ACCEL_1	0x0006 /* Graphic Accelerator */
#define PCI_DEVICE_ID_NEC_UXBUS		0x0007 /* UX-Bus Bridge */
#define PCI_DEVICE_ID_NEC_ACCEL_2	0x0008 /* Graphic Accelerator */
#define PCI_DEVICE_ID_NEC_GRAPH		0x0009 /* PCI-CoreGraph Bridge */
#define PCI_DEVICE_ID_NEC_VL		0x0016 /* PCI-VL Bridge */
#define PCI_DEVICE_ID_NEC_STARALPHA2	0x002c /* STAR ALPHA2 */
#define PCI_DEVICE_ID_NEC_CBUS_2	0x002d /* PCI-Cbus Bridge */
#define PCI_DEVICE_ID_NEC_USB		0x0035 /* PCI-USB Host */
#define PCI_DEVICE_ID_NEC_CBUS_3	0x003b
#define PCI_DEVICE_ID_NEC_NAPCCARD	0x003e
#define PCI_DEVICE_ID_NEC_PCX2		0x0046 /* PowerVR */
#define PCI_DEVICE_ID_NEC_NILE4		0x005a
#define PCI_DEVICE_ID_NEC_VRC5476       0x009b
#define PCI_DEVICE_ID_NEC_VRC4173	0x00a5
#define PCI_DEVICE_ID_NEC_VRC5477_AC97  0x00a6
#define PCI_DEVICE_ID_NEC_PC9821CS01    0x800c /* PC-9821-CS01 */
#define PCI_DEVICE_ID_NEC_PC9821NRB06   0x800d /* PC-9821NR-B06 */

#define PCI_VENDOR_ID_FD		0x1036
#define PCI_DEVICE_ID_FD_36C70		0x0000

#define PCI_VENDOR_ID_SI		0x1039
#define PCI_DEVICE_ID_SI_5591_AGP	0x0001
#define PCI_DEVICE_ID_SI_6202		0x0002
#define PCI_DEVICE_ID_SI_503		0x0008
#define PCI_DEVICE_ID_SI_ACPI		0x0009
#define PCI_DEVICE_ID_SI_SMBUS		0x0016
#define PCI_DEVICE_ID_SI_LPC		0x0018
#define PCI_DEVICE_ID_SI_5597_VGA	0x0200
#define PCI_DEVICE_ID_SI_6205		0x0205
#define PCI_DEVICE_ID_SI_501		0x0406
#define PCI_DEVICE_ID_SI_496		0x0496
#define PCI_DEVICE_ID_SI_300		0x0300
#define PCI_DEVICE_ID_SI_315H		0x0310
#define PCI_DEVICE_ID_SI_315		0x0315
#define PCI_DEVICE_ID_SI_315PRO		0x0325
#define PCI_DEVICE_ID_SI_530		0x0530
#define PCI_DEVICE_ID_SI_540		0x0540
#define PCI_DEVICE_ID_SI_550		0x0550
#define PCI_DEVICE_ID_SI_540_VGA	0x5300
#define PCI_DEVICE_ID_SI_550_VGA	0x5315
#define PCI_DEVICE_ID_SI_601		0x0601
#define PCI_DEVICE_ID_SI_620		0x0620
#define PCI_DEVICE_ID_SI_630		0x0630
#define PCI_DEVICE_ID_SI_633		0x0633
#define PCI_DEVICE_ID_SI_635		0x0635
#define PCI_DEVICE_ID_SI_640		0x0640
#define PCI_DEVICE_ID_SI_645		0x0645
#define PCI_DEVICE_ID_SI_646		0x0646
#define PCI_DEVICE_ID_SI_648		0x0648
#define PCI_DEVICE_ID_SI_650		0x0650
#define PCI_DEVICE_ID_SI_651		0x0651
#define PCI_DEVICE_ID_SI_652		0x0652
#define PCI_DEVICE_ID_SI_655		0x0655
#define PCI_DEVICE_ID_SI_661		0x0661
#define PCI_DEVICE_ID_SI_730		0x0730
#define PCI_DEVICE_ID_SI_733		0x0733
#define PCI_DEVICE_ID_SI_630_VGA	0x6300
#define PCI_DEVICE_ID_SI_730_VGA	0x7300
#define PCI_DEVICE_ID_SI_735		0x0735
#define PCI_DEVICE_ID_SI_740		0x0740
#define PCI_DEVICE_ID_SI_741		0x0741
#define PCI_DEVICE_ID_SI_745		0x0745
#define PCI_DEVICE_ID_SI_746		0x0746
#define PCI_DEVICE_ID_SI_748		0x0748
#define PCI_DEVICE_ID_SI_750		0x0750
#define PCI_DEVICE_ID_SI_751		0x0751
#define PCI_DEVICE_ID_SI_752		0x0752
#define PCI_DEVICE_ID_SI_755		0x0755
#define PCI_DEVICE_ID_SI_760		0x0760
#define PCI_DEVICE_ID_SI_900		0x0900
#define PCI_DEVICE_ID_SI_961		0x0961
#define PCI_DEVICE_ID_SI_962		0x0962
#define PCI_DEVICE_ID_SI_963		0x0963
#define PCI_DEVICE_ID_SI_5107		0x5107
#define PCI_DEVICE_ID_SI_5300		0x5300
#define PCI_DEVICE_ID_SI_5511		0x5511
#define PCI_DEVICE_ID_SI_5513		0x5513
#define PCI_DEVICE_ID_SI_5518		0x5518
#define PCI_DEVICE_ID_SI_5571		0x5571
#define PCI_DEVICE_ID_SI_5581		0x5581
#define PCI_DEVICE_ID_SI_5582		0x5582
#define PCI_DEVICE_ID_SI_5591		0x5591
#define PCI_DEVICE_ID_SI_5596		0x5596
#define PCI_DEVICE_ID_SI_5597		0x5597
#define PCI_DEVICE_ID_SI_5598		0x5598
#define PCI_DEVICE_ID_SI_5600		0x5600
#define PCI_DEVICE_ID_SI_6300		0x6300
#define PCI_DEVICE_ID_SI_6306		0x6306
#define PCI_DEVICE_ID_SI_6326		0x6326
#define PCI_DEVICE_ID_SI_7001		0x7001
#define PCI_DEVICE_ID_SI_7012		0x7012
#define PCI_DEVICE_ID_SI_7016		0x7016

#define PCI_VENDOR_ID_HP		0x103c
#define PCI_DEVICE_ID_HP_VISUALIZE_EG	0x1005
#define PCI_DEVICE_ID_HP_VISUALIZE_FX6	0x1006
#define PCI_DEVICE_ID_HP_VISUALIZE_FX4	0x1008
#define PCI_DEVICE_ID_HP_VISUALIZE_FX2	0x100a
#define PCI_DEVICE_ID_HP_TACHYON	0x1028
#define PCI_DEVICE_ID_HP_TACHLITE	0x1029
#define PCI_DEVICE_ID_HP_J2585A		0x1030
#define PCI_DEVICE_ID_HP_J2585B		0x1031
#define PCI_DEVICE_ID_HP_J2973A		0x1040
#define PCI_DEVICE_ID_HP_J2970A		0x1042
#define PCI_DEVICE_ID_HP_DIVA		0x1048
#define PCI_DEVICE_ID_HP_DIVA_TOSCA1	0x1049
#define PCI_DEVICE_ID_HP_DIVA_TOSCA2	0x104A
#define PCI_DEVICE_ID_HP_DIVA_MAESTRO	0x104B
#define PCI_DEVICE_ID_HP_PCI_LBA	0x1054
#define PCI_DEVICE_ID_HP_REO_SBA	0x10f0
#define PCI_DEVICE_ID_HP_REO_IOC	0x10f1
#define PCI_DEVICE_ID_HP_VISUALIZE_FXE	0x108b
#define PCI_DEVICE_ID_HP_DIVA_HALFDOME	0x1223
#define PCI_DEVICE_ID_HP_DIVA_KEYSTONE	0x1226
#define PCI_DEVICE_ID_HP_DIVA_POWERBAR	0x1227
#define PCI_DEVICE_ID_HP_ZX1_SBA	0x1229
#define PCI_DEVICE_ID_HP_ZX1_IOC	0x122a
#define PCI_DEVICE_ID_HP_PCIX_LBA	0x122e
#define PCI_DEVICE_ID_HP_SX1000_IOC	0x127c
#define PCI_DEVICE_ID_HP_DIVA_EVEREST	0x1282
#define PCI_DEVICE_ID_HP_DIVA_AUX	0x1290
#define PCI_DEVICE_ID_HP_CISSA		0x3220

#define PCI_VENDOR_ID_PCTECH		0x1042
#define PCI_DEVICE_ID_PCTECH_RZ1000	0x1000
#define PCI_DEVICE_ID_PCTECH_RZ1001	0x1001
#define PCI_DEVICE_ID_PCTECH_SAMURAI_0	0x3000
#define PCI_DEVICE_ID_PCTECH_SAMURAI_1	0x3010
#define PCI_DEVICE_ID_PCTECH_SAMURAI_IDE 0x3020

#define PCI_VENDOR_ID_ASUSTEK		0x1043
#define PCI_DEVICE_ID_ASUSTEK_0675	0x0675

#define PCI_VENDOR_ID_DPT		0x1044
#define PCI_DEVICE_ID_DPT		0xa400

#define PCI_VENDOR_ID_OPTI		0x1045
#define PCI_DEVICE_ID_OPTI_92C178	0xc178
#define PCI_DEVICE_ID_OPTI_82C557	0xc557
#define PCI_DEVICE_ID_OPTI_82C558	0xc558
#define PCI_DEVICE_ID_OPTI_82C621	0xc621
#define PCI_DEVICE_ID_OPTI_82C700	0xc700
#define PCI_DEVICE_ID_OPTI_82C701	0xc701
#define PCI_DEVICE_ID_OPTI_82C814	0xc814
#define PCI_DEVICE_ID_OPTI_82C822	0xc822
#define PCI_DEVICE_ID_OPTI_82C861	0xc861
#define PCI_DEVICE_ID_OPTI_82C825	0xd568

#define PCI_VENDOR_ID_ELSA		0x1048
#define PCI_DEVICE_ID_ELSA_MICROLINK	0x1000
#define PCI_DEVICE_ID_ELSA_QS3000	0x3000

#define PCI_VENDOR_ID_SGS		0x104a
#define PCI_DEVICE_ID_SGS_2000		0x0008
#define PCI_DEVICE_ID_SGS_1764		0x0009

#define PCI_VENDOR_ID_BUSLOGIC		      0x104B
#define PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER_NC 0x0140
#define PCI_DEVICE_ID_BUSLOGIC_MULTIMASTER    0x1040
#define PCI_DEVICE_ID_BUSLOGIC_FLASHPOINT     0x8130

#define PCI_VENDOR_ID_TI		0x104c
#define PCI_DEVICE_ID_TI_TVP4010	0x3d04
#define PCI_DEVICE_ID_TI_TVP4020	0x3d07
#define PCI_DEVICE_ID_TI_4450		0x8011
#define PCI_DEVICE_ID_TI_1130		0xac12
#define PCI_DEVICE_ID_TI_1031		0xac13
#define PCI_DEVICE_ID_TI_1131		0xac15
#define PCI_DEVICE_ID_TI_1250		0xac16
#define PCI_DEVICE_ID_TI_1220		0xac17
#define PCI_DEVICE_ID_TI_1221		0xac19
#define PCI_DEVICE_ID_TI_1210		0xac1a
#define PCI_DEVICE_ID_TI_1450		0xac1b
#define PCI_DEVICE_ID_TI_1225		0xac1c
#define PCI_DEVICE_ID_TI_1251A		0xac1d
#define PCI_DEVICE_ID_TI_1211		0xac1e
#define PCI_DEVICE_ID_TI_1251B		0xac1f
#define PCI_DEVICE_ID_TI_4410		0xac41
#define PCI_DEVICE_ID_TI_4451		0xac42
#define PCI_DEVICE_ID_TI_4520		0xac46
#define PCI_DEVICE_ID_TI_1410		0xac50
#define PCI_DEVICE_ID_TI_1420		0xac51
#define PCI_DEVICE_ID_TI_1451A		0xac52
#define PCI_DEVICE_ID_TI_1620		0xac54
#define PCI_DEVICE_ID_TI_1520		0xac55
#define PCI_DEVICE_ID_TI_1510		0xac56

#define PCI_VENDOR_ID_SONY		0x104d
#define PCI_DEVICE_ID_SONY_CXD3222	0x8039

#define PCI_VENDOR_ID_OAK		0x104e
#define PCI_DEVICE_ID_OAK_OTI107	0x0107

/* Winbond have two vendor IDs! See 0x10ad as well */
#define PCI_VENDOR_ID_WINBOND2		0x1050
#define PCI_DEVICE_ID_WINBOND2_89C940	0x0940
#define PCI_DEVICE_ID_WINBOND2_89C940F	0x5a5a
#define PCI_DEVICE_ID_WINBOND2_6692	0x6692

#define PCI_VENDOR_ID_ANIGMA		0x1051
#define PCI_DEVICE_ID_ANIGMA_MC145575	0x0100
  
#define PCI_VENDOR_ID_EFAR		0x1055
#define PCI_DEVICE_ID_EFAR_SLC90E66_1	0x9130
#define PCI_DEVICE_ID_EFAR_SLC90E66_0	0x9460
#define PCI_DEVICE_ID_EFAR_SLC90E66_2	0x9462
#define PCI_DEVICE_ID_EFAR_SLC90E66_3	0x9463

#define PCI_VENDOR_ID_MOTOROLA		0x1057
#define PCI_VENDOR_ID_MOTOROLA_OOPS	0x1507
#define PCI_DEVICE_ID_MOTOROLA_MPC105	0x0001
#define PCI_DEVICE_ID_MOTOROLA_MPC106	0x0002
#define PCI_DEVICE_ID_MOTOROLA_MPC107	0x0004
#define PCI_DEVICE_ID_MOTOROLA_RAVEN	0x4801
#define PCI_DEVICE_ID_MOTOROLA_FALCON	0x4802
#define PCI_DEVICE_ID_MOTOROLA_HAWK	0x4803
#define PCI_DEVICE_ID_MOTOROLA_CPX8216	0x4806
#define PCI_DEVICE_ID_MOTOROLA_HARRIER	0x480b

#define PCI_VENDOR_ID_PROMISE		0x105a
#define PCI_DEVICE_ID_PROMISE_20265	0x0d30
#define PCI_DEVICE_ID_PROMISE_20267	0x4d30
#define PCI_DEVICE_ID_PROMISE_20246	0x4d33
#define PCI_DEVICE_ID_PROMISE_20262	0x4d38
#define PCI_DEVICE_ID_PROMISE_20263	0x0D38
#define PCI_DEVICE_ID_PROMISE_20268	0x4d68
#define PCI_DEVICE_ID_PROMISE_20268R	0x6268
#define PCI_DEVICE_ID_PROMISE_20269	0x4d69
#define PCI_DEVICE_ID_PROMISE_20270	0x6268
#define PCI_DEVICE_ID_PROMISE_20271	0x6269
#define PCI_DEVICE_ID_PROMISE_20275	0x1275
#define PCI_DEVICE_ID_PROMISE_20276	0x5275
#define PCI_DEVICE_ID_PROMISE_20277	0x7275
#define PCI_DEVICE_ID_PROMISE_5300	0x5300

#define PCI_VENDOR_ID_N9		0x105d
#define PCI_DEVICE_ID_N9_I128		0x2309
#define PCI_DEVICE_ID_N9_I128_2		0x2339
#define PCI_DEVICE_ID_N9_I128_T2R	0x493d

#define PCI_VENDOR_ID_UMC		0x1060
#define PCI_DEVICE_ID_UMC_UM8673F	0x0101
#define PCI_DEVICE_ID_UMC_UM8891A	0x0891
#define PCI_DEVICE_ID_UMC_UM8886BF	0x673a
#define PCI_DEVICE_ID_UMC_UM8886A	0x886a
#define PCI_DEVICE_ID_UMC_UM8881F	0x8881
#define PCI_DEVICE_ID_UMC_UM8886F	0x8886
#define PCI_DEVICE_ID_UMC_UM9017F	0x9017
#define PCI_DEVICE_ID_UMC_UM8886N	0xe886
#define PCI_DEVICE_ID_UMC_UM8891N	0xe891

#define PCI_VENDOR_ID_X			0x1061
#define PCI_DEVICE_ID_X_AGX016		0x0001

#define PCI_VENDOR_ID_MYLEX		0x1069
#define PCI_DEVICE_ID_MYLEX_DAC960_P	0x0001
#define PCI_DEVICE_ID_MYLEX_DAC960_PD	0x0002
#define PCI_DEVICE_ID_MYLEX_DAC960_PG	0x0010
#define PCI_DEVICE_ID_MYLEX_DAC960_LA	0x0020
#define PCI_DEVICE_ID_MYLEX_DAC960_LP	0x0050
#define PCI_DEVICE_ID_MYLEX_DAC960_BA	0xBA56

#define PCI_VENDOR_ID_PICOP		0x1066
#define PCI_DEVICE_ID_PICOP_PT86C52X	0x0001
#define PCI_DEVICE_ID_PICOP_PT80C524	0x8002

#define PCI_VENDOR_ID_APPLE		0x106b
#define PCI_DEVICE_ID_APPLE_BANDIT	0x0001
#define PCI_DEVICE_ID_APPLE_GC		0x0002
#define PCI_DEVICE_ID_APPLE_HYDRA	0x000e
#define PCI_DEVICE_ID_APPLE_UNI_N_FW	0x0018
#define PCI_DEVICE_ID_APPLE_KL_USB	0x0019
#define PCI_DEVICE_ID_APPLE_UNI_N_AGP	0x0020
#define PCI_DEVICE_ID_APPLE_UNI_N_GMAC	0x0021
#define PCI_DEVICE_ID_APPLE_KEYLARGO	0x0022
#define PCI_DEVICE_ID_APPLE_UNI_N_GMACP	0x0024
#define PCI_DEVICE_ID_APPLE_KEYLARGO_P	0x0025
#define PCI_DEVICE_ID_APPLE_KL_USB_P	0x0026
#define PCI_DEVICE_ID_APPLE_UNI_N_AGP_P	0x0027
#define PCI_DEVICE_ID_APPLE_UNI_N_AGP15	0x002d
#define PCI_DEVICE_ID_APPLE_UNI_N_FW2	0x0030
#define PCI_DEVICE_ID_APPLE_UNI_N_GMAC2	0x0032
#define PCI_DEVIEC_ID_APPLE_UNI_N_ATA	0x0033
#define PCI_DEVICE_ID_APPLE_UNI_N_AGP2	0x0034
#define PCI_DEVICE_ID_APPLE_IPID_ATA100	0x003b
#define PCI_DEVICE_ID_APPLE_KEYLARGO_I	0x003e
#define PCI_DEVICE_ID_APPLE_K2_ATA100	0x0043
#define PCI_DEVICE_ID_APPLE_K2_GMAC	0x004c
#define PCI_DEVICE_ID_APPLE_TIGON3	0x1645

#define PCI_VENDOR_ID_YAMAHA		0x1073
#define PCI_DEVICE_ID_YAMAHA_724	0x0004
#define PCI_DEVICE_ID_