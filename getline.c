#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Enter file name: \n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL){
        perror("Error opening file");
        return 1;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    char *last_line = NULL, *second_last_line = NULL;

    while ((read = getline(&line, &len, file)) != -1) {
        if (second_last_line){
            free(second_last_line);
        }
        second_last_line = last_line;
        last_line = strdup(line);
    }

    if (second_last_line){
        printf("%s", second_last_line);
    }
    if (last_line){
        printf("%s", last_line);
    }

    free(line);
    free(last_line);
    free(second_last_line);

    fclose(file);
    return 0;
}