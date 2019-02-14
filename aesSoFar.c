#include <stdio.h>
#include <stdlib.h>

int sbox[256] ={
	  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

void rotWord(int* src, int len){
    int temper = src[0];
    for(int i = 0;i < len-1 ;i++) {
        src[i] = src[i+1];
    }
    src[len-1] = temper;
}

void xorArrays(int* src, int* second){
    for (int i = 0; i < 4; i++){
        src[i] = src[i] ^ second[i];
    }
}

void shiftRows(int* src, int len, int shifts){
    for(int i = 0; i < shifts; i++){
        int temper = src[0];
        for(int i = 0;i < len-1 ;i++) {
            src[i] = src[i+1];
        }
        src[len-1] = temper;
    }
}

void subBytes(int* src, int type){
    for (int i = 0; i < type; i++){
        src[i] = sbox[src[i]];
    }
}

void copyArray(int* src, int* dst, int len) {
    for (int i = 0; i < len; i++) {
        dst[i] = src[i];
    }
}

void printArrayHex(int array[], int arraySize){
	for (int i = 0; i < arraySize; i++){
		printf("%02x ", array[i]);
	}
    printf("\n");
}

void printArray(int array[], int arraySize){
	for (int i = 0; i < arraySize; i++){
		printf("%i ", array[i]);
	}
	printf("\n");
}

void getRoundKey(int* src, int round){
    if (round != 0){

        int rconArray[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

        int c0[4] = {0};
        int c1[4] = {0};
        int c2[4] = {0};
        int c3[4] = {0};

        for (int i = 0; i < 4; i++){
            c0[i] = src[i];
            c1[i] = src[i+4];
            c2[i] = src[i+8];
            c3[i] = src[i+12];
        }

        int temp[4] = {0};
        int roundKey[16] = {0};

        for (int j = 0; j < round; j++){

        int addRound[4] = {rconArray[j], 0x00, 0x00, 0x00};

            for (int k = 0; k < 4; k++){
                if (k == 0){
                    copyArray(c3, temp,4);
                    rotWord(temp,4);
                    subBytes(temp,4);
                    xorArrays(temp,addRound);
                    xorArrays(temp,c0);
                    copyArray(temp,c0,4);
                } else if (k == 1){
                    xorArrays(temp,c1);
                    copyArray(temp,c1,4);
                } else if (k == 2){
                    xorArrays(temp,c2);
                    copyArray(temp,c2,4);
                } else if (k == 3){
                    xorArrays(temp,c3);
                    copyArray(temp,c3,4);
                }
            }
            memcpy(roundKey, c0, 4 * sizeof(int));
            memcpy(&roundKey[4], c1, 4 * sizeof(int));
            memcpy(&roundKey[8], c2, 4 * sizeof(int));
            memcpy(&roundKey[12], c3, 4 * sizeof(int));
        }
        copyArray(roundKey,src,16);
    }
}

void AddRoundKey(int* state, int* roundKey){
    int k0[4] = {0};
    int k1[4] = {0};
    int k2[4] = {0};
    int k3[4] = {0};
    int t0[4] = {0};
    int t1[4] = {0};
    int t2[4] = {0};
    int t3[4] = {0};

    for (int i = 0; i < 4; i++){
        k0[i] = roundKey[i];
        k1[i] = roundKey[i+4];
        k2[i] = roundKey[i+8];
        k3[i] = roundKey[i+12];
        t0[i] = state[i];
        t1[i] = state[i+4];
        t2[i] = state[i+8];
        t3[i] = state[i+12];
    }

    xorArrays(k0,t0);
    xorArrays(k1,t1);
    xorArrays(k2,t2);
    xorArrays(k3,t3);
    int final[16] = {0};

    memcpy(final, k0, 4 * sizeof(int));
    memcpy(&final[4], k1, 4 * sizeof(int));
    memcpy(&final[8], k2, 4 * sizeof(int));
    memcpy(&final[12], k3, 4 * sizeof(int));

    copyArray(final,state,16);
}

int main(void) {
	int plaintext[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};

	int key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};

    // Round 0
    getRoundKey(key,0);
    AddRoundKey(plaintext,key);

    // Round 1-9
    subBytes(plaintext,16);
    printArrayHex(plaintext,16);

    // Round 10



}