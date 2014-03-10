#include "CRangePrintTree.hpp"

AM_U32 data[]= {11,22,54,32,89,57,40,12,101,220,445,532,980,1,4,0};

static void printNode(AM_U32 node)
{
    printf("[%d]",node);
}

static cmp_t cmpFunc(AM_U32* arg1,AM_U32* arg2)
{
    if((arg1==NULL)||(arg2==NULL))
        return INVALID;

    if(*arg1==*arg2)
        return EQUAL;
    else if(*arg1>*arg2)
        return LARGER;
    else if(*arg1<*arg2)
        return SMALLER;
}


int main(int argc,char* argv[])
{
    AM_U32 length=sizeof(data)/sizeof(AM_U32);
    AM_U32 idx;
    CRangePrintTree<AM_U32> printTree;
    printTree.SetCmpFunc(cmpFunc);
    printTree.SetPrintFunc(printNode);
    for(idx=0; idx<length; idx++)
    {
        printTree.Insert(&data[idx]);
    }

    printTree.InorderTraversal();
    printTree.RangePrint(10,600);

}
