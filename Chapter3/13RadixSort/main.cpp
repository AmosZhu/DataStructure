#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AmosType.hpp"
#include "RadixSort.hpp"

#define FILEPATH "random.txt"
#define OUTPUTPATH "output.txt"

int main(void)
{
    FILE* fIn;
    FILE* fOut;
    char buf[BUFSIZE];
    char* pBuf;
    AM_U32 digitSize;
    AM_U32 countNo;
    AM_U32 bucketSize;
    AM_U32 i;
    AM_U32* data;
    fIn=fopen(FILEPATH,"rb+");
    fOut=fopen(OUTPUTPATH,"wb+");

    memset(buf,0,BUFSIZE);
    fscanf(fIn,"%s",buf);
    pBuf=strchr(buf,'=');
    pBuf++;
    digitSize=atoi(pBuf);

    memset(buf,0,BUFSIZE);
    fscanf(fIn,"%s",buf);
    pBuf=strchr(buf,'=');
    pBuf++;
    countNo=atoi(pBuf);

    memset(buf,0,BUFSIZE);
    fscanf(fIn,"%s",buf);
    pBuf=strchr(buf,'=');
    pBuf++;
    bucketSize=atoi(pBuf);

    data=(AM_U32*)malloc(countNo*sizeof(AM_U32));

    for(i=0; i<countNo; i++)
    {
        fscanf(fIn,"%d",&data[i]);
    }


    RadixSort(bucketSize,digitSize,countNo,data);

    for(i=0; i<countNo; i++)
    {
        fprintf(fOut,"%d\n",data[i]);
    }
    printf("\n");

    fclose(fIn);
    fclose(fOut);

    return 1;
}

