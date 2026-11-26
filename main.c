#include <stdio.h>
#include <stdlib.h>

const char first_char = ' ';
const char last_char = '~';


int error_checking(FILE* FILE_READ, FILE* FILE_WRITE);
int innit_csv(FILE* FILE_WRITE);
int char_frequency(FILE* FILE_READ, FILE* FILE_WRITE);


int main(int argc, char** argv){
    int file_index = argc - 1;

    FILE* FILE_READ = fopen(argv[file_index], "r");
    FILE* FILE_WRITE = fopen(argv[1], "w+");

    if (error_checking(FILE_READ, FILE_WRITE)){
        return 0;
    }

    innit_csv(FILE_WRITE);

    while(file_index > 1 && argv[file_index] != NULL){
        if(error_checking(FILE_READ, FILE_WRITE)){
            return 0;
        }

        char_frequency(FILE_READ,FILE_WRITE);
        fclose(FILE_READ);
        file_index--;
        if (file_index > 1){
            FILE_READ = fopen(argv[file_index], "r");
        }
    }

    fclose(FILE_WRITE);
    return 0;
}

int char_frequency(FILE* FILE_READ, FILE* FILE_WRITE){
    int file_char_innit = fgetc(FILE_READ);
    int file_char_sec = fgetc(FILE_READ);
    int bytes_to_move;
    int row_byte;
    int col_byte;
    int char_numeric;
    int N = (last_char - first_char) + 1;
    while(file_char_sec != EOF){

        row_byte = (file_char_innit - first_char);
        col_byte = (file_char_sec - first_char);
        bytes_to_move = row_byte * (N * 9) + col_byte * 9 + 7;
        fseek(FILE_WRITE, bytes_to_move ,SEEK_SET);
        char_numeric = fgetc(FILE_WRITE);


        while(char_numeric == '9'){
            fseek(FILE_WRITE, -1L, SEEK_CUR);
            fputc('0',FILE_WRITE);
            fseek(FILE_WRITE, -2L, SEEK_CUR);
            char_numeric = fgetc(FILE_WRITE);
        }
            fseek(FILE_WRITE, -1L, SEEK_CUR);
            fputc(char_numeric + 1,FILE_WRITE);
            file_char_innit = file_char_sec;
            file_char_sec = fgetc(FILE_READ);
    }

    return 1;
}

int error_checking(FILE* FILE_READ, FILE* FILE_WRITE){
    if(FILE_READ == NULL || FILE_WRITE == NULL){
        perror("FILE_READ OR FILE_WRITE EQUALS NULL");
        return 1;
    }
    return 0;
}

int innit_csv(FILE* FILE_WRITE){
    int i = 0;
    int j = 0;

    for(i = 0; i <= (int)(last_char - first_char); i++){
        for(j = 0; j <= (last_char - first_char); j++){
            fputs("00000000", FILE_WRITE);
            if(j == (int)(last_char - first_char)){
                fputc('\n',FILE_WRITE);
            } else {
                fputc(',',FILE_WRITE);
            }
        }
    }
    return 1;
}
