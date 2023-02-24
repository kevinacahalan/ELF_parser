#ifndef STUFF_H
#define STUFF_H

#include <elf.h>
char *e_machine_look_up[] = {
    [EM_NONE]         = "No machine",
    [EM_M32]          = "AT&T WE 32100",
    [EM_SPARC]        = "SUN SPARC",
    [EM_386]          = "Intel 80386",
    [EM_68K]          = "Motorola m68k family",
    [EM_88K]          = "Motorola m88k family",
    [EM_IAMCU]        = "Intel MCU",
    [EM_860]          = "Intel 80860",
    [EM_MIPS]         = "MIPS R3000 big-endian",
    [EM_S370]         = "IBM System/370",
    [EM_MIPS_RS3_LE]  = "MIPS R3000 little-endian",
    [EM_PARISC]       = "HPPA",
    [EM_VPP500]       = "Fujitsu VPP500",
    [EM_SPARC32PLUS]  = "Sun's \"v8plus\"",
    [EM_960]          = "Intel 80960",
    [EM_PPC]          = "PowerPC",
    [EM_PPC64]        = "PowerPC 64-bit",
    [EM_S390]         = "IBM S390",
    [EM_SPU]          = "IBM SPU/SPC",
    [EM_V800]         = "NEC V800 series",
    [EM_FR20]         = "Fujitsu FR20",
    [EM_RH32]         = "TRW RH-32",
    [EM_RCE]          = "Motorola RCE",
    [EM_ARM]          = "ARM",
    [EM_FAKE_ALPHA]   = "Digital Alpha",
    [EM_SH]           = "Hitachi SH",
    [EM_SPARCV9]      = "SPARC v9 64-bit",
    [EM_TRICORE]      = "Siemens Tricore",
    [EM_ARC]          = "Argonaut RISC Core",
    [EM_H8_300]       = "Hitachi H8/300",
    [EM_H8_300H]      = "Hitachi H8/300H",
    [EM_H8S]          = "Hitachi H8S",
    [EM_H8_500]       = "Hitachi H8/500",
    [EM_IA_64]        = "Intel Merced",
    [EM_MIPS_X]       = "Stanford MIPS-X",
    [EM_COLDFIRE]     = "Motorola Coldfire",
    [EM_68HC12]       = "Motorola M68HC12",
    [EM_MMA]          = "Fujitsu MMA Multimedia Accelerator",
    [EM_PCP]          = "Siemens PCP",
    [EM_NCPU]         = "Sony nCPU embeeded RISC",
    [EM_NDR1]         = "Denso NDR1 microprocessor",
    [EM_STARCORE]     = "Motorola Start*Core processor",
    [EM_ME16]         = "Toyota ME16 processor",
    [EM_ST100]        = "STMicroelectronic ST100 processor",
    [EM_TINYJ]        = "Advanced Logic Corp. Tinyj emb.fam",
    [EM_X86_64]       = "AMD x86-64 architecture",
    [EM_PDSP]         = "Sony DSP Processor",
    [EM_PDP10]        = "Digital PDP-10",
    [EM_PDP11]        = "Digital PDP-11",
    [EM_FX66]         = "Siemens FX66 microcontroller",
    [EM_ST9PLUS]      = "STMicroelectronics ST9+ 8/16 mc",
    [EM_ST7]          = "STmicroelectronics ST7 8 bit mc",
    [EM_68HC16]       = "Motorola MC68HC16 microcontroller",
    [EM_68HC11]       = "Motorola MC68HC11 microcontroller",
    [EM_68HC08]       = "Motorola MC68HC08 microcontroller",
    [EM_68HC05]       = "Motorola MC68HC05 microcontroller",
    [EM_SVX]          = "Silicon Graphics SVx",
    [EM_ST19]         = "STMicroelectronics ST19 8 bit mc",
    [EM_VAX]          = "Digital VAX",
    [EM_CRIS]         = "Axis Communications 32-bit emb.proc",
    [EM_JAVELIN]      = "Infineon Technologies 32-bit emb.proc",
    [EM_FIREPATH]     = "Element 14 64-bit DSP Processor",
    [EM_ZSP]          = "LSI Logic 16-bit DSP Processor",
    [EM_MMIX]         = "Donald Knuth's educational 64-bit proc",
    [EM_HUANY]        = "Harvard University machine-independent object files",
    [EM_PRISM]        = "SiTera Prism",
    [EM_AVR]          = "Atmel AVR 8-bit microcontroller",
    [EM_FR30]         = "Fujitsu FR30",
    [EM_D10V]         = "Mitsubishi D10V",
    [EM_D30V]         = "Mitsubishi D30V",
    [EM_V850]         = "NEC v850",
    [EM_M32R]         = "Mitsubishi M32R",
    [EM_MN10300]      = "Matsushita MN10300",
    [EM_MN10200]      = "Matsushita MN10200",
    [EM_PJ]           = "picoJava",
    [EM_OPENRISC]     = "OpenRISC 32-bit embedded processor",
    [EM_ARC_COMPACT]  = "ARC International ARCompact",
    [EM_XTENSA]       = "Tensilica Xtensa Architecture",
    [EM_VIDEOCORE]    = "Alphamosaic VideoCore",
    [EM_TMM_GPP]      = "Thompson Multimedia General Purpose Proc",
    [EM_NS32K]        = "National Semi. 32000",
    [EM_TPC]          = "Tenor Network TPC",
    [EM_SNP1K]        = "Trebia SNP 1000",
    [EM_ST200]        = "STMicroelectronics ST200",
    [EM_IP2K]         = "Ubicom IP2xxx",
    [EM_MAX]          = "MAX processor",
    [EM_CR]           = "National Semi. CompactRISC",
    [EM_F2MC16]       = "Fujitsu F2MC16",
    [EM_MSP430]       = "Texas Instruments msp430",
    [EM_BLACKFIN]     = "Analog Devices Blackfin DSP",
    [EM_SE_C33]       = "Seiko Epson S1C33 family",
    [EM_SEP]          = "Sharp embedded microprocessor",
    [EM_ARCA]         = "Arca RISC",
    [EM_UNICORE]      = "PKU-Unity & MPRC Peking Uni. mc series",
    [EM_EXCESS]       = "eXcess configurable cpu",
    [EM_DXP]          = "Icera Semi. Deep Execution Processor",
    [EM_ALTERA_NIOS2] = "Altera Nios II",
    [EM_CRX]          = "National Semi. CompactRISC CRX",
    [EM_XGATE]        = "Motorola XGATE",
    [EM_C166]         = "Infineon C16x/XC16x",
    [EM_M16C]         = "Renesas M16C",
    [EM_DSPIC30F]     = "Microchip Technology dsPIC30F",
    [EM_CE]           = "Freescale Communication Engine RISC",
    [EM_M32C]         = "Renesas M32C",
    [EM_TSK3000]      = "Altium TSK3000",
    [EM_RS08]         = "Freescale RS08",
    [EM_SHARC]        = "Analog Devices SHARC family",
    [EM_ECOG2]        = "Cyan Technology eCOG2",
    [EM_SCORE7]       = "Sunplus S+core7 RISC",
    [EM_DSP24]        = "New Japan Radio (NJR) 24-bit DSP",
    [EM_VIDEOCORE3]   = "Broadcom VideoCore III",
    [EM_LATTICEMICO32] = "RISC for Lattice FPGA",
    [EM_SE_C17]       = "Seiko Epson C17",
    [EM_TI_C6000]     = "Texas Instruments TMS320C6000 DSP",
    [EM_TI_C2000]     = "Texas Instruments TMS320C2000 DSP",
    [EM_TI_C5500]     = "Texas Instruments TMS320C55x DSP",
    [EM_TI_ARP32]     = "Texas Instruments App. Specific RISC",
    [EM_TI_PRU]       = "Texas Instruments Prog. Realtime Unit",
    [EM_MMDSP_PLUS]   = "STMicroelectronics 64bit VLIW DSP",
    [EM_CYPRESS_M8C]  = "Cypress M8C",
    [EM_R32C]         = "Renesas R32C",
    [EM_TRIMEDIA]     = "NXP Semi. TriMedia",
    [EM_QDSP6]        = "QUALCOMM DSP6",
    [EM_8051]         = "Intel 8051 and variants",
    [EM_STXP7X]       = "STMicroelectronics STxP7x",
    [EM_NDS32]        = "Andes Tech. compact code emb. RISC",
    [EM_ECOG1X]       = "Cyan Technology eCOG1X",
    [EM_MAXQ30]       = "Dallas Semi. MAXQ30 mc",
    [EM_XIMO16]       = "New Japan Radio (NJR) 16-bit DSP",
    [EM_MANIK]        = "M2000 Reconfigurable RISC",
    [EM_CRAYNV2]      = "Cray NV2 vector architecture",
    [EM_RX]           = "Renesas RX",
    [EM_METAG]        = "Imagination Tech. META",
    [EM_MCST_ELBRUS]  = "MCST Elbrus",
    [EM_ECOG16]       = "Cyan Technology eCOG16",
    [EM_CR16]         = "National Semi. CompactRISC CR16",
    [EM_ETPU]         = "Freescale Extended Time Processing Unit",
    [EM_SLE9X]        = "Infineon Tech. SLE9X",
    [EM_L10M]         = "Intel L10M",
    [EM_K10M]         = "Intel K10M",
    [EM_AARCH64]      = "ARM AARCH64",
    [EM_AVR32]        = "Amtel 32-bit microprocessor",
    [EM_STM8]         = "STMicroelectronics STM8",
    [EM_TILE64]       = "Tilera TILE64",
    [EM_TILEPRO]      = "Tilera TILEPro",
    [EM_MICROBLAZE]   = "Xilinx MicroBlaze",
    [EM_CUDA]         = "NVIDIA CUDA",
    [EM_TILEGX]       = "Tilera TILE-Gx",
    [EM_CLOUDSHIELD]  = "CloudShield",
    [EM_COREA_1ST]    = "KIPO-KAIST Core-A 1st gen.",
    [EM_COREA_2ND]    = "KIPO-KAIST Core-A 2nd gen.",
    [EM_ARCV2]        = "Synopsys ARCv2 ISA. ",
    [EM_OPEN8]        = "Open8 RISC",
    [EM_RL78]         = "Renesas RL78",
    [EM_VIDEOCORE5]   = "Broadcom VideoCore V",
    [EM_78KOR]        = "Renesas 78KOR",
    [EM_56800EX]      = "Freescale 56800EX DSC",
    [EM_BA1]          = "Beyond BA1",
    [EM_BA2]          = "Beyond BA2",
    [EM_XCORE]        = "XMOS xCORE",
    [EM_MCHP_PIC]     = "Microchip 8-bit PIC(r)",
    [EM_KM32]         = "KM211 KM32",
    [EM_KMX32]        = "KM211 KMX32",
    [EM_EMX16]        = "KM211 KMX16",
    [EM_EMX8]         = "KM211 KMX8",
    [EM_KVARC]        = "KM211 KVARC",
    [EM_CDP]          = "Paneve CDP",
    [EM_COGE]         = "Cognitive Smart Memory Processor",
    [EM_COOL]         = "Bluechip CoolEngine",
    [EM_NORC]         = "Nanoradio Optimized RISC",
    [EM_CSR_KALIMBA]  = "CSR Kalimba",
    [EM_Z80]          = "Zilog Z80",
    [EM_VISIUM]       = "Controls and Data Services VISIUMcore",
    [EM_FT32]         = "FTDI Chip FT32",
    [EM_MOXIE]        = "Moxie processor",
    [EM_AMDGPU]       = "AMD GPU",
    [EM_RISCV]        = "RISC-V",
    [EM_BPF]          = "Linux BPF -- in-kernel virtual machine",
    [EM_CSKY]         = "C-SKY",
};

#endif