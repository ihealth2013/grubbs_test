#include "stdio.h"
#include "grubbstest.h"


void main() {

    int sourceValues[] = {324,424,1,343,354,455,456,5000};

      

    int  arrayLen = sizeof(sourceValues) / sizeof(sourceValues[0]);


    printf("source value:\r\n");
    for (int i = 0; i < arrayLen; i++) {
        printf("%d ", sourceValues[i]);
    }
    printf("\r\n");


    int discardCount = Discard_All_Outlier_Grubbs(sourceValues, arrayLen);

    printf("discard value: remove(%d) \r\n", discardCount);
    for (int i = 0; i < arrayLen ; i++) {
        printf("%d ", sourceValues[i]);
    }
    printf("\r\n");
     
}
