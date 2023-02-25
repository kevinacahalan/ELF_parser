#include <elf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include "stuff.h"

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

static void print_EI_CLASS(unsigned char class){
	switch(class){
	case ELFCLASSNONE:
		printf("EI_CLASS: ELFCLASSNONE\n");
		break;
	case ELFCLASS32:
		printf("EI_CLASS: ELFCLASS32, (32 bit)\n");
		break;
	case ELFCLASS64:
		printf("EI_CLASS: ELFCLASS64, (64 bit)\n");
		break;
	default:
		printf("Something is odd with EI_CLASS, value is: %d\n", class);
		exit(1);
	}
}

static void print_EI_DATA(unsigned char data){
	switch(data){
	case ELFDATANONE:
		printf("EI_DATA: ELFDATANONE\n");
		break;
	case ELFDATA2LSB:
		printf("EI_DATA: ELFDATA2LSB, (little endian)\n");
		break;
	case ELFDATA2MSB:
		printf("EI_DATA: ELFDATA2MSB, (big endian)\n");
		break;
	default:
		printf("Something is odd with EI_DATA, value is: %d\n", data);
		exit(1);
	}
}

static void print_EI_VERSION(unsigned char version){
	switch(version){
	case EV_NONE:
        printf("EI_VERSION: EV_NONE");
        break;
	case EV_CURRENT:
        printf("EI_VERSION: EV_CURRENT, ELF specification version: %d\n", EV_CURRENT);
        break;
	default:
        printf("Something is odd with EI_VERSION, value is: %d\n", version);
		exit(1);
	}
}

static void print_EI_OSABI(unsigned char osabi){
    switch(osabi){
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
        printf("Something is odd with EI_OSABI, value is: %d\n", osabi);
		exit(1);
    }
}

static void print_e_ident(unsigned char *ident_data) {    
    unsigned char mag0 = ident_data[EI_MAG0]; // first byte
    unsigned char mag1 = ident_data[EI_MAG1]; // second byte
    unsigned char mag2 = ident_data[EI_MAG2]; // third byte
    unsigned char mag3 = ident_data[EI_MAG3]; // fouth byte
    unsigned char class = ident_data[EI_CLASS]; // 1 for 32bit, 2 for 64bit, 0 for NONE
    unsigned char data = ident_data[5]; // endian, 1 for little, 2 for big
    unsigned char version = ident_data[6];
    unsigned char osabi = ident_data[7];
    unsigned char abiversion = ident_data[8];

    int is_eif =
        mag0 == ELFMAG0 && mag1 == 'E' && mag2 == 'L' && mag3 == 'F';
	if (!is_eif){
		printf("Not an ELF!\n");
		exit(1);
	}
    printf("\nInfo from first 16 bytes of file, the e_ident data:\n");

    print_EI_CLASS(class);
    print_EI_DATA(data);
    print_EI_VERSION(version);
    print_EI_OSABI(osabi);

    printf("EI_ABIVERSION: %d\n", abiversion);
}

#define PRINT_HEADER_DATA(sz)\
    static void print_header_data##sz(Elf##sz##_Ehdr e){\
        /* Should have line here to printf e_ident data */\
        \
        printf("\n...Program Header data:\n");\
\
        /* print e_ident */\
        print_e_ident(e.e_ident);\
\
        printf("\nOther data:\n");\
\
        /* print e_type */\
        switch(e.e_type){\
        case ET_NONE:\
        default:\
            printf("e_type: Unknown type.\n");\
            break;\
        case ET_REL:\
            printf("e_type: Relocatable file.\n");\
            break;\
        case ET_EXEC:\
            printf("e_type: Executable file.\n");\
            break;\
        case ET_DYN:\
            printf("e_type: Shared object.\n");\
            break;\
        case ET_CORE:\
            printf("e_type: Core file.\n");\
            break;\
        }\
\
        /* print e_machine */\
        /* MIGHT BE A HUGE THING ON THE STACK */\
\
        int amount = sizeof e_machine_look_up / sizeof e_machine_look_up[0];\
        printf("e_machine: %s\n", e.e_machine >= amount ? "Unknown": e_machine_look_up[e.e_machine]);\
\
        /* print e_version */\
        switch(e.e_version){\
        case EV_NONE:\
            printf("e_version: Invalid version\n");\
            break;\
        case EV_CURRENT:\
            printf("e_version: Current version\n");\
            break;\
        default:\
            printf("e_version: %d\n", e.e_version);\
            break;\
        }\
\
        printf("e_entry: %016" PRIx##sz "\n", e.e_entry);\
        printf("e_phoff: %016" PRIx##sz "\n", e.e_phoff);\
        printf("e_shoff: %016" PRIx##sz "\n", e.e_shoff);\
        printf("e_flags: %08x\n", e.e_flags);\
        printf("e_ehsize: %d\n", e.e_ehsize);\
        printf("e_phentsize: %d\n", e.e_phentsize);\
        printf("e_phnum: %d\n", e.e_phnum);\
        printf("e_shentsize: %d\n", e.e_shentsize);\
        printf("e_shnum: %d\n", e.e_shnum);\
        printf("e_shstrndx: %d\n", e.e_shstrndx);\
    }

PRINT_HEADER_DATA(32)
PRINT_HEADER_DATA(64)

#define GEN_PROGRAM_HEADER_TABLE_FMT(l) "%8x %8x %8" #l "x %12" #l "x %12" #l "x %8" #l "x %12" #l "x %8" #l "x %c"

#define PROGRAM_HEADER_TABLE_FMT_32 GEN_PROGRAM_HEADER_TABLE_FMT()
#define PROGRAM_HEADER_TABLE_FMT_64 GEN_PROGRAM_HEADER_TABLE_FMT(l)
#define PRINT_PROGRAM_HEADER_TABLE(sz)\
    static void print_program_header_table##sz(struct ptrsz file_data, Elf##sz##_Ehdr e){\
        Elf##sz##_Phdr p;\
        if(sizeof p != e.e_phentsize){\
            printf("BAD STUFF at %s:%d, sizeof p != e.e_phentsize\n",__FILE__, __LINE__);\
            exit(38);\
        }\
\
        /* Should check for wrap around, does not */\
        if(e.e_phnum * e.e_phentsize + e.e_phoff > file_data.size){\
            printf("BAD STUFF at %s:%d, e.e_phnum * e.e_phentsize + e.e_phoff > file_data.size\n", __FILE__, __LINE__);\
            exit(39);\
        }\
\
        printf("\n...Program Header Table:\n");\
        printf(\
            "%8s %8s %8s %12s %12s %8s %12s %8s\n",\
            "type", "flags", "offset", "vaddr", "paddr", \
            "filesz", "memsz", "align"\
            );\
        for (size_t i = 0; i < e.e_phnum; i++){\
            memcpy(&p, file_data.data + e.e_phoff + i * e.e_phentsize, e.e_phentsize);\
            printf(\
                PROGRAM_HEADER_TABLE_FMT_##sz,\
                p.p_type, p.p_flags, p.p_offset, p.p_vaddr, p.p_paddr,\
                p.p_filesz, p.p_memsz, p.p_align, '\n'\
            );\
        }\
    }

#define GEN_SECTION_HEADER_TABLE_FMT(l) "%8x %8x %8" #l "x %12" #l "x %12" #l"x %8" #l"x %8x %8x %8" #l "x %8" #l "x %s %c"
#define SECTION_HEADER_TABLE_FMT_32 GEN_SECTION_HEADER_TABLE_FMT()
#define SECTION_HEADER_TABLE_FMT_64 GEN_SECTION_HEADER_TABLE_FMT(l)
#define PRINT_SECTION_HEADER_TABLE(sz)\
    static void print_section_header_table##sz (struct ptrsz file_data, Elf##sz##_Ehdr e) \
    {\
        Elf##sz##_Shdr s;\
        if(sizeof s != e.e_shentsize){\
            printf("BAD STUFF at %s:%d\n", __FILE__, __LINE__);\
            exit(38);\
        }\
\
        /* Should check for wrap around, does not */\
        if(e.e_shnum * e.e_shentsize + e.e_shoff > file_data.size){\
            printf("BAD STUFF at %s:%d\n", __FILE__, __LINE__);\
            exit(39);\
        }\
\
        /* Find section names */ \
        Elf##sz##_Shdr names_header;\
        memcpy(&names_header, file_data.data + e.e_shoff + e.e_shstrndx * e.e_shentsize, e.e_shentsize);\
        char *names = names_header.sh_offset + file_data.data;\
\
        printf("\n...Section Header Table:\n");\
        printf(\
            "%8s %8s %8s %12s %12s %8s %8s %8s %8s %8s %s\n",\
            "name", "type", "flags", "addr", "offset", "size", \
            "link", "info", "addralign", "entsize", "Header Names"\
            );\
        for (size_t i = 0; i < e.e_shnum; i++){\
            memcpy(&s, file_data.data + e.e_shoff + i * e.e_shentsize, e.e_shentsize);\
            printf(\
                SECTION_HEADER_TABLE_FMT_##sz,\
                s.sh_name, s.sh_type, s.sh_flags, s.sh_addr, s.sh_offset, \
                s.sh_size, s.sh_link, s.sh_info, s.sh_addralign, s.sh_entsize,\
                s.sh_name + names, '\n'\
            );\
        }\
    }

PRINT_PROGRAM_HEADER_TABLE(32)
PRINT_SECTION_HEADER_TABLE(32)
PRINT_PROGRAM_HEADER_TABLE(64)
PRINT_SECTION_HEADER_TABLE(64)

int main(int argc, char const* argv[]) {
    (void)argc;
    FILE* ifp = fopen(argv[1], "rb");
    struct ptrsz file_data = copy_file_to_heap(ifp);

    // These variable will come to use later when the code is improved
    unsigned char class = file_data.data[EI_CLASS]; // 1 for 32bit, 2 for 64bit, 0 for NONE
    unsigned char data = file_data.data[EI_DATA]; // endian, 1 for little, 2 for big
    (void)data;

    if (data != ELFDATA2LSB) {
        printf("Only little endian ELF files are supported");
        exit(123);
    }


    switch (class){
    case ELFCLASS32: {
        printf("32 bit elf!");
        // Grab header data
        Elf32_Ehdr e; // For now assumeing I am dealing with an elf 64
        if (file_data.size < sizeof e){
            printf("File does not have enough space for elf header!\n");
            exit(89);
        }
        
        memcpy(&e, file_data.data, sizeof e);
        print_header_data32(e);
        print_program_header_table32(file_data, e);
        print_section_header_table32(file_data, e);
        exit(123);
        }
        break;
    case ELFCLASS64:
        printf("64 bit elf!");
        // Grab header data
        Elf64_Ehdr e; // For now assumeing I am dealing with an elf 64
        if (file_data.size < sizeof e){
            printf("File does not have enough space for elf header!\n");
            exit(89);
        }
        
        memcpy(&e, file_data.data, sizeof e);
        print_header_data64(e);
        print_program_header_table64(file_data, e);
        print_section_header_table64(file_data, e);

        break;
    case ELFCLASSNONE:
        printf("This ELF does not have a class, that's kinda funky ngl\n");
        exit(123);
    case ELFCLASSNUM:
        printf("This ELF has the class ELFCLASSNUM...currently not supported\n");
        exit(123);
    default:
        break;
    }



    // print_plt(file_data, e);
    // print_got(file_data, e);


    return 0;
}
