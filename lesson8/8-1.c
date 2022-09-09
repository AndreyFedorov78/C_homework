//
// Created by Andrei Fedorov on 22.08.2022.
//
#include <stdio.h>
#include <stdint.h>



int main() {
    FILE *fIn, *fOut;
    fIn=fopen("input.bin", "rb");
    fOut=fopen("output.bin", "wb");
    uint8_t k;
    uint16_t value;
    fseek(fIn, -1, SEEK_END);
    uint16_t stop = ftell (fIn);
    fread(&k, 1, 1, fIn);
    fseek(fIn, k*2, SEEK_SET);
    while (stop-ftell(fIn)){
        fread(&value, 2, 1, fIn);
        fwrite(&value, 2, 1, fOut);
        //printf("0x%u ", value);
    }

    fseek(fIn, 0, SEEK_SET);
    while (k*2-ftell(fIn)){
        fread(&value, 2, 1, fIn);
        fwrite(&value, 2, 1, fOut);
        //printf("0x%u ", value);

    }

    //printf("\n");



    fclose(fIn);
    fclose(fOut);

    return 0;
};