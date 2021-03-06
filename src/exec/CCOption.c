#include <CCOption.h>

static void print_usage(CCOption* this){
    fprintf(stderr, "Usage: wvmcc [options] file...\n");
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -o <file>      Place the output into <file>.\n");
    fprintf(stderr, "  --version      Display compiler version information\n");
    fprintf(stderr, "  --help, -h     Display usage information\n");
    free(this);
    exit(-1);
}

static void print_version(CCOption* this){
    printf("wvmcc %s\n", WVMCC_VERSION);
    free(this);
    exit(0);
}

CCOption* new_CCOption(int argc, const char* argv[]){
    CCOption* newOption = (CCOption*) calloc(1, sizeof(CCOption));
    newOption->input_files = NULL;
    newOption->output_file = NULL;
    newOption->input_count = 0;
    // Parse option
    for(int i = 0; i < argc; ++i){
        if(!strcmp(argv[i], "-o")){
            if(i < argc - 1){
                newOption->output_file = argv[i+1];
                i += 1;
            }else{
                print_usage(newOption);
            }
        }else if(!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")){
            print_usage(newOption);
        }else if(!strcmp(argv[i], "--version")){
            print_version(newOption);
        }else{
            newOption->input_count += 1;
            newOption->input_files = (const char**) realloc(newOption->input_files, sizeof(const char*) * (newOption->input_count));
            newOption->input_files[newOption->input_count - 1] = argv[i];
        }
    }
    return newOption;
}

void free_CCOption(CCOption** option){
    free(*option);
    *option = NULL;
}