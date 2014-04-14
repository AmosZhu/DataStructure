#include "AmosType.hpp"
#include "CList.hpp"
#include "polynominal.hpp"
#include <stdio.h>
#include <string.h>


static void copyFunc(polynominal_t* dst,polynominal_t* src)
{
    memcpy(dst,src,sizeof(polynominal_t));
}

int main(void)
{
    char buf[BUFSIZE];
    char* equation;
    CList<polynominal_t> list1,list2,list3;
    list1.SetCopyFunc(copyFunc);

    list2=list1;
    list3=list1;
    polynominal_t value;
    FILE* fp;
    int i;
    /*********************
    *   Open file
    *********************/
    fp=fopen("1.txt","rb+");
    /************************
    *   require equation
    ************************/
    fscanf(fp,"%s",buf);
    printf("%s\n",buf);
    equation=strchr(buf,'=');
    equation++;
    polynominalInput(equation,&list1);
    list1.ResetElemNext();
    printf("no %d\n",list1.CountNo());
    for(i=0; i<list1.CountNo(); i++)
    {
        list1.GetElemNext(&value);
        printf("index %d: coef %d,exponent %d\n",i,value.coeficient,value.exponent);
    }

    /************************
    *   require equation
    ************************/
    memset(buf,0,BUFSIZE);
    fscanf(fp,"%s",buf);
    printf("%s\n",buf);
    equation=strchr(buf,'=');
    equation++;
    polynominalInput(equation,&list2);
    list2.ResetElemNext();
    printf("no %d\n",list2.CountNo());
    for(i=0; i<list2.CountNo(); i++)
    {
        list2.GetElemNext(&value);
        printf("index %d: coef %d,exponent %d\n",i,value.coeficient,value.exponent);
    }

    /******************************
    *   Polynominal add
    ******************************/
    memset(buf,0,BUFSIZE);
    polynominalAdd(&list1,&list2,&list3);
    printf("---------->Function add: list1+list2<-----------------\n");
    list3.ResetElemNext();
    for(i=0; i<list3.CountNo(); i++)
    {
        list3.GetElemNext(&value);
        printf("index %d: coef %d,exponent %d\n",i,value.coeficient,value.exponent);
    }

    polynominalOutput(&list3,buf);
    printf("%s\n",buf);

    /******************************
    *   Polynominal mutiply
    ******************************/

    printf("---------->Function mutiply: list1*list2<-----------------\n");

    memset(buf,0,BUFSIZE);
    list3.Destroy();

    polynominalMutiply(&list1,&list2,&list3);
    printf("no %d\n",list3.CountNo());
    list3.ResetElemNext();
    for(i=0; i<list3.CountNo(); i++)
    {
        list3.GetElemNext(&value);
        printf("index %d: coef %d,exponent %d\n",i,value.coeficient,value.exponent);
    }

    polynominalOutput(&list3,buf);
    printf("%s\n",buf);

    return 1;
}

