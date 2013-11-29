/********************************************************
*
*   This file is the implement of the radix sort
*
*   N is the size of the data, and M is the digit size
*   Time Cost: O(N*M)
*
********************************************************/


#include "AmosType.hpp"
#include <string.h>

/********************************************
*               Macro
********************************************/
#define DEBUG 0
#define DB_PRINT(fmt,args...) printf("\033[33m[%s]:"fmt"\033[0m",__FUNCTION__,##args)

/*******************************************
*               Text
*******************************************/


/**********************************************************
*
*   Actual time cost in my radix sort: O(M*(2N+M))
*
***********************************************************/
Err_t RadixSort(AM_U32 bucketSize,AM_U32 digitSize,AM_U32 countNo,AM_U32* data)
{
    AM_U32 bucket[bucketSize];
    AM_U32 temp[countNo];
    AM_U32 base=1;
    AM_S32 i=0;
    AM_U32 index;

    if(data==NULL)
        return INVALIDE_PARAMET;

    while(digitSize>0)
    {
        memset(bucket,0,bucketSize*sizeof(AM_U32));
        for(i=0; i<countNo; i++)
        {
            index=(data[i]/base)%bucketSize;
            bucket[index]++;
        }

        for(i=1; i<bucketSize; i++)
        {
            bucket[i]+=bucket[i-1];
        }
#if(DEBUG)
        for(i=0; i<bucketSize; i++)
        {
            printf("bucket[%d]:%d,",i,bucket[i]);
        }
        printf("\n");
#endif


        for(i=countNo-1; i>=0; i--)
        {
            index=(data[i]/base)%bucketSize;
            temp[--bucket[index]]=data[i];
        }

        memcpy(data,temp,countNo*sizeof(AM_U32));

#if(DEBUG)
        for(i=0; i<countNo; i++)
        {
            printf("%d, ",data[i]);
        }
        printf("\n");
#endif

        base*=bucketSize;
        digitSize--;
    }
#if(DEBUG)
    for(i=0; i<countNo; i++)
    {
        printf("%d, ",data[i]);
    }
    printf("\n");
#endif
    return RETURN_SUCCESS;
}

