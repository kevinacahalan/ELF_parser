#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

struct ptrsz {
    char *data;
    size_t size;
};

struct ei {
    unsigned char mag0;
    unsigned char mag1;
    unsigned char mag2;
    unsigned char mag3;
    unsigned char class;
    unsigned char data;
    unsigned char version;
    unsigned char osabi;
    unsigned char abiversion;
    unsigned char pad;
    unsigned char nident;
};

static int ffstat(FILE* fp, struct stat* s) {
    // Convert from file pointer to file descripter
    int fd = fileno(fp);
    return fstat(fd, s);
}

static int get_size_of_file(FILE* ifp) {
    struct stat s;
    ffstat(ifp, &s);
    int n_bytes = s.st_size;

    return n_bytes;
}

static struct ptrsz copy_file_to_heap(FILE* fp) {
    int n_bytes = get_size_of_file(fp);
    char* file_data = malloc(n_bytes);
    fread(file_data, n_bytes, 1, fp);

    return (struct ptrsz){.data = file_data, .size = n_bytes};
}

static struct ei get_e_ident_data(struct ptrsz file_data) {
    // This code can be written in a MUCH BETTER WAY
    struct ei rt;
    rt.mag0 = file_data.data[0];
    rt.mag1 = file_data.data[1];
    rt.mag2 = file_data.data[2];
    rt.mag3 = file_data.data[3];
    rt.class = file_data.data[4];
    rt.data = file_data.data[5];
    rt.version = file_data.data[6];
    rt.osabi = file_data.data[7];
    rt.abiversion = file_data.data[8];
    rt.pad = file_data.data[9];
    rt.nident = file_data.data[10];

    return rt;
}

void print_e_ident(struct ei ei) {
    int is_eif =
        ei.mag0 == 0x7f && ei.mag1 == 'E' && ei.mag2 == 'L' && ei.mag3 == 'F';
	if (!is_eif){
		printf("Not an ELF!\n");
		exit(1);
	}

	// print EI_CLASS
	switch(ei.class){
	case ELFCLASSNONE:
		printf("EI_CLASS: ELFCLASSNONE\n");
		break;
	case ELFCLASS32:
		printf("EI_CLASS: ELFCLASS32\n");
		break;
	case ELFCLASS64:
		printf("EI_CLASS: ELFCLASS64\n");
		break;
	default:
		printf("Something is odd with EI_CLASS, value is: %d\n", ei.class);
		exit(1);
	}

	// print EI_DATA
	switch(ei.data){
	case ELFDATANONE:
		printf("EI_DATA: ELFDATANONE\n");
		break;
	case ELFDATA2LSB:
		printf("EI_DATA: ELFDATA2LSB\n");
		break;
	case ELFDATA2MSB:
		printf("EI_DATA: ELFDATA2MSB\n");
		break;
	default:
		printf("Something is odd with EI_DATA, value is: %d\n", ei.data);
		exit(1);
	}

	// print EI_VERSION
	switch(ei.data){
	case EV_NONE:
        printf("EI_VERSION: EV_NONE");
        break;
	case EV_CURRENT:
        printf("EI_VERSION: EV_CURRENT, ELF specification version: %d\n", EV_CURRENT);
        break;
	default:
        printf("Something is odd with EI_VERSION, value is: %d\n", ei.version);
		exit(1);
	}

    // print EI_OSABI
    switch(ei.osabi){
    case ELFOSABI_NONE | ELFOSABI_SYSV:
        printf("EI_OSABI: ELFOSABI_NONE / ELFOSABI_SYSV\n");
        break;
    case ELFOSABI_HPUX:
        printf("EI_OSABI: ELFOSABI_HPUX\n");
        break;
    case ELFOSABI_NETBSD:
        printf("EI_OSABI: ELFOSABI_NETBSD\n");
        break;
    case ELFOSABI_LINUX:
        printf("EI_OSABI: ELFOSABI_LINUX\n");
        break;
    case ELFOSABI_SOLARIS:
        printf("EI_OSABI: ELFOSABI_SOLARIS\n");
        break;
    case ELFOSABI_IRIX:
        printf("EI_OSABI: ELFOSABI_IRIX\n");
        break;
    case ELFOSABI_FREEBSD:
        printf("EI_OSABI: ELFOSABI_FREEBSD\n");
        break;
    case ELFOSABI_TRU64:
        printf("EI_OSABI: ELFOSABI_TRU64\n");
        break;
    case ELFOSABI_ARM:
        printf("EI_OSABI: ELFOSABI_ARM\n");
        break;
    case ELFOSABI_STANDALONE:
        printf("EI_OSABI: ELFOSABI_STANDALONE\n");
        break;
    default:
        printf("Something is odd with EI_OSABI, value is: %d\n", ei.osabi);
		exit(1);
    }

    printf("EI_ABIVERSION: %d\n", ei.abiversion);
    printf("EI_PAD: %d\n", ei.pad);
    printf("EI_NIDENT: %d\n",  ei.nident);
}

void print_header_data(Elf64_Ehdr e){
    // Should have line here to printf e_ident data

    // print e_type
    switch(e.e_type){
    case ET_NONE:
    default:
        printf("e_type: Unknown type.\n");
        break;
    case ET_REL:
        printf("e_type: Relocatable file.\n");
        break;
    case ET_EXEC:
        printf("e_type: Executable file.\n");
        break;
    case ET_DYN:
        printf("e_type: Shared object.\n");
        break;
    case ET_CORE:
        printf("e_type: Core file.\n");
        break;
    }

    // print e_machine
    // MIGHT BE A HUGE THING ON THE STACK
    char *look_up_array[] = {
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

    int amount = sizeof look_up_array / sizeof look_up_array[0];
    printf("e_machine: %s\n", e.e_machine >= amount ? "Unknown": look_up_array[e.e_machine]);

    // print e_version
    switch(e.e_version){
    case EV_NONE:
        printf("e_version: Invalid version\n");
        break;
    case EV_CURRENT:
        printf("e_version: Current version\n");
        break;
    default:
        printf("e_version: %d\n", e.e_version);
        break;
    }

    printf("e_entry: %016lx\n", e.e_entry);
    printf("e_phoff: %016lx\n", e.e_phoff);
    printf("e_shoff: %016lx\n", e.e_shoff);
    printf("e_flags: %08x\n", e.e_flags);
    printf("e_ehsize: %d\n", e.e_ehsize);
    printf("e_phentsize: %d\n", e.e_phentsize);
    printf("e_phnum: %d\n", e.e_phnum);
    printf("e_shentsize: %d\n", e.e_shentsize);
    printf("e_shnum: %d\n", e.e_shnum);
    printf("e_shstrndx: %d\n", e.e_shstrndx);
}

void print_program_header_table(struct ptrsz file_data, Elf64_Ehdr e){
    Elf64_Phdr p;
    if(sizeof p != e.e_phentsize){
        printf("BAD STUFF\n");
        exit(38);
    }

    // Should check for wrap around, does not
    if(e.e_phnum * e.e_phentsize + e.e_phoff > file_data.size){
        printf("BAD STUFF\n");
        exit(39);
    }

    printf("\nProgram Header Table:\n");
    printf(
        "%8s %8s %8s %12s %12s %8s %12s %8s\n",
        "type", "flags", "offset", "vaddr", "paddr", 
        "filesz", "memsz", "align"
        );
    for (size_t i = 0; i < e.e_phnum; i++){
        memcpy(&p, file_data.data + e.e_phoff + i * e.e_phentsize, e.e_phentsize);
        printf(
            "%8x %8x %8lx %12lx %12lx %8lx %12lx %8lx\n",
            p.p_type, p.p_flags, p.p_offset, p.p_vaddr, p.p_paddr,
            p.p_filesz, p.p_memsz, p.p_align
        );
    }
}

void print_section_header_table(struct ptrsz file_data, Elf64_Ehdr e){
    Elf64_Shdr s;
    if(sizeof s != e.e_shentsize){
        printf("BAD STUFF\n");
        exit(38);
    }

    // Should check for wrap around, does not
    if(e.e_shnum * e.e_shentsize + e.e_shoff > file_data.size){
        printf("BAD STUFF\n");
        exit(39);
    }

    // Find section names
    Elf64_Shdr names_header;
    memcpy(&names_header, file_data.data + e.e_shoff + e.e_shstrndx * e.e_shentsize, e.e_shentsize);
    char *names = names_header.sh_offset + file_data.data;

    printf("\nSection Header Table:\n");
    printf(
        "%8s %8s %8s %12s %12s %8s %8s %8s %8s %8s %s\n",
        "name", "type", "flags", "addr", "offset", "size", 
        "link", "info", "addralign", "entsize", "Header Names"
        );
    for (size_t i = 0; i < e.e_shnum; i++){
        memcpy(&s, file_data.data + e.e_shoff + i * e.e_shentsize, e.e_shentsize);
        printf(
            "%8x %8x %8lx %12lx %12lx %8lx %8x %8x %8lx %8lx %s\n",
            s.sh_name, s.sh_type, s.sh_flags, s.sh_addr, s.sh_offset, 
            s.sh_size, s.sh_link, s.sh_info, s.sh_addralign, s.sh_entsize,
            s.sh_name + names
        );
    }
}


int main(int argc, char const* argv[]) {
    (void)argc;
    FILE* ifp = fopen(argv[1], "rb");
    struct ptrsz file_data = copy_file_to_heap(ifp);

    struct ei El_info = get_e_ident_data(file_data);
    print_e_ident(El_info);

    // Grab header data
    Elf64_Ehdr e;
    memcpy(&e, file_data.data, sizeof e);
    print_header_data(e);
    print_program_header_table(file_data, e);
    print_section_header_table(file_data, e);


    return 0;
}
