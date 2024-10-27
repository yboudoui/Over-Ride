#include <stdio.h>

int main(void){

    unsigned int number;
    unsigned int index, index2, index3;

    index = 4160435336;
    index2 = 4160435700;
    index3 = 4160435684;
    number = 4294956632;
    printf ("%u\n", number >> 8);
    printf ("%u\n", index % 3);
    printf ("%u\n", index2 % 3);
    printf ("%u\n", index3 % 3);

}