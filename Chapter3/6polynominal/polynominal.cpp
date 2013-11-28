/*********************************************************************
*
*   This file use to process polynominal function
*   Implement:@Process polynominal input
*             @Process polynominal add/sub function
*             @Process polynominal multiply function
*
*   @Author: Amos.Zhu
*
*   $$Caution: Support two equation only yet
*
*   %Input: from 1.txt file, equations should have inorder,and in
*           the same order
*
*********************************************************************/

#include "AmosType.hpp"
#include "CList.hpp"
#include "polynominal.hpp"
#include <stdio.h>
#include <string.h>

#define DB_PRINT(fmt,args...) printf("\033[33m[%s]:"fmt"\033[0m\n",__FUNCTION__,##args)

/****************************************
*               Macro
***************************************/
#define BUFSIZE 512
#define DEBUG 0

/***************************************
*            Internal function
***************************************/
static Err_t mutiplySingle(polynominal_t* a1,CList<polynominal_t>* input,CList<polynominal_t>* output);


/***************************************
*               Text
***************************************/
int main(void)
{
    char buf[BUFSIZE];
    char* equation;
    CList<polynominal_t> list1,list2,list3;
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


AM_U32 processDigit(char** fmt)
{
    AM_U32 num=0;
    while(ISDIGIT(**fmt))
    {
        num*=10;
        num+=**fmt-'0';
        (*fmt)++;
    }
    return num;
}

Err_t polynominalInput(char* buf,CList<polynominal_t>* equation)
{
    char* p;
    short flag;
    AM_S32 num;
    polynominal_t value;

    if((buf==NULL)||(equation==NULL))
        return INVALIDE_PARAMET;

    INITVALUE(value);
    CLEARFLAG(flag);

    p=buf;

    while(*p)
    {
        SETCOEF(flag);
        switch(*p)
        {
            case '+':
            {
                p++;
            }
            continue;
            break;
            case '-':
            {
                SETSIGN(flag);
                p++;
            }
            continue;
            break;
            case 'X':
            case 'x':
            {
                CLEARCOEF(flag);
                if(*++p=='^')
                {
                    SETEXP(flag);
                    p++;
                }
                else
                {
                    value.exponent=1;
                    equation->Insert(value);
                    INITVALUE(value);
                    CLEARFLAG(flag);
                }
            }
            continue;
            break;
            default:
                break;
        }

        if(!ISDIGIT(*p))
        {
            DB_PRINT("input error!");
            return OPERATOR_FAILED;
        }

        num=processDigit(&p);
        if(flag&SIGN)
        {
            num=-num;
            CLEARSIGN(flag);
        }


        /****************************************************************
        *
        *   Amos assume that whenever finish processing the exponent,
        *   It should move to next nominal,and clear all flag status!
        *
        ****************************************************************/
        if(flag&EXPONENT)
        {
            value.exponent=num;
            equation->Insert(value);
            INITVALUE(value);
            CLEARFLAG(flag);
        }
        else
        {
            value.coeficient=num;
        }


        /***********************************************
        *
        *   eg: x^-1+56+6x^2
        *   56 is a special coeficient withou exponent,
        *   process here
        *
        ***********************************************/
        if(flag&COEFONLY)
        {
            if(*p=='X'||*p=='x')
                continue;
            else
            {
                value.exponent=0;
                equation->Insert(value);
                INITVALUE(value);
                CLEARFLAG(flag);
            }
        }

    }
    equation->Reverse();  /*Keep inorder*/
    return RETURN_SUCCESS;
}

Err_t polynominalOutput(CList<polynominal_t>* input,char* output)
{
    char* p;
    polynominal_t value;
    AM_U32 len;
    AM_U32 flag;
    char buf[30];

    if((input==NULL)||(output==NULL))
        return INVALIDE_PARAMET;

    p=output;
    memcpy(p,"F(x)=",strlen("F(x)="));
    p+=strlen("F(x)=");
    input->ResetElemNext();
    input->GetElemNext(&value);

    /********************************
    *   If the output is zero
    ********************************/
    if(input->CountNo()==0)
    {
        *p++='0';
        *p='\0';
        return RETURN_SUCCESS;
    }

    /********************************
    *   Process the first element
    ********************************/
    if((value.coeficient==1)&&(value.exponent==0))
    {
        *p++='1';
        goto SecondProcess;
    }

    if(value.coeficient==1)
    {
        /***************************
        *   Do not do anything
        ***************************/
    }
    else
    {
        sprintf(buf,"%d",value.coeficient);
        memcpy(p,buf,strlen(buf));
        p+=strlen(buf);
    }

    if(value.exponent==0)
    {
        goto SecondProcess;
    }
    else if(value.exponent==1)
    {
        *p++='X';
        goto SecondProcess;
    }
    else
    {
        *p++='X';
        *p++='^';
        sprintf(buf,"%d",value.exponent);
        memcpy(p,buf,strlen(buf));
        p+=strlen(buf);
        goto SecondProcess;
    }
    /**********************************************
    *   Process other elements exclude the first
    **********************************************/
SecondProcess:
    while(input->GetElemNext(&value)==RETURN_SUCCESS)
    {
        memset(buf,0,30);

        /*****************************
        *   Process the coeficient
        *****************************/
        if((value.coeficient==1)&&(value.exponent==0))
        {
            *p++='+';
            *p++='1';
            continue;
        }
        else if(value.coeficient==1)
        {
            *p++='+';
        }
        else if(value.coeficient>1)
        {
            *p++='+';
            sprintf(buf,"%d",value.coeficient);
            memcpy(p,buf,strlen(buf));
            p+=strlen(buf);
        }
        else if(value.coeficient<0)
        {
            sprintf(buf,"%d",value.coeficient);
            memcpy(p,buf,strlen(buf));
            p+=strlen(buf);
        }

        /*****************************
        *   Process the exponent
        *****************************/
        if(value.exponent==0)
        {
            continue;
        }
        else if(value.exponent==1)
        {
            *p++='X';
            continue;
        }
        else
        {
            *p++='X';
            *p++='^';
            sprintf(buf,"%d",value.exponent);
            memcpy(p,buf,strlen(buf));
            p+=strlen(buf);
            continue;
        }
    }

    *p='\0';
    return RETURN_SUCCESS;
}

/***********************************************************************************************
*
*   Traverse both list,if input1 has M elments and the input2 has N elemnts;
*
*   Time cost O(M+N);
*
***********************************************************************************************/
Err_t polynominalAdd(CList<polynominal_t>* input1,CList<polynominal_t>* input2,CList<polynominal_t>* output)
{
    polynominal_t p1,p2,o3;
    if((input1==NULL)||(input2==NULL)||(output==NULL))
        return INVALIDE_PARAMET;

    input1->ResetElemNext();
    input2->ResetElemNext();

    if(input1->GetElemNext(&p1)!=RETURN_SUCCESS)
        goto ProcessList2;

    if(input2->GetElemNext(&p2)!=RETURN_SUCCESS)
        goto ProcessList1;

    for(;;)
    {
        if(p1.exponent<p2.exponent)
        {
            o3.coeficient=p1.coeficient;
            o3.exponent=p1.exponent;
            output->Insert(o3);
            if(input1->GetElemNext(&p1)!=RETURN_SUCCESS)
                goto ProcessList2;

        }
        else if(p1.exponent>p2.exponent)
        {
            o3.coeficient=p2.coeficient;
            o3.exponent=p2.exponent;
            output->Insert(o3);
            if(input2->GetElemNext(&p2)!=RETURN_SUCCESS)
                goto ProcessList1;
        }
        else if(p1.exponent==p2.exponent)
        {
            o3.coeficient=p1.coeficient+p2.coeficient;
            o3.exponent=p1.exponent;
            if(o3.coeficient!=0) /*if the coeficient is zero, do not add it to the list*/
                output->Insert(o3);
            if(input1->GetElemNext(&p1)!=RETURN_SUCCESS)
                goto ProcessList2;

            if(input2->GetElemNext(&p2)!=RETURN_SUCCESS)
                goto ProcessList1;
        }
        else
        {
            DB_PRINT("Error!");
            return OPERATOR_FAILED;
        }
    }

ProcessList1:
    o3.coeficient=p1.coeficient;
    o3.exponent=p1.exponent;
    if(o3.coeficient!=0)
        output->Insert(o3);
    while(input1->GetElemNext(&p1)==RETURN_SUCCESS)
    {
        o3.coeficient=p1.coeficient;
        o3.exponent=p1.exponent;
        output->Insert(o3);
    }
    output->Reverse();  // Keep inorder
    return RETURN_SUCCESS;
ProcessList2:
    o3.coeficient=p2.coeficient;
    o3.exponent=p2.exponent;
    if(o3.coeficient!=0)
        output->Insert(o3);

    while(input2->GetElemNext(&p2)==RETURN_SUCCESS)
    {
        o3.coeficient=p2.coeficient;
        o3.exponent=p2.exponent;
        output->Insert(o3);
    }
    output->Reverse(); // Keep inorder
    return RETURN_SUCCESS;

}

/************************************************************************************
*
*   m present the List which have M element and cost O(M) to traverse this list,
*   n present the List which have N element and cost O(N) to traverse this list,
*
*   @@Caution m<n
*   @@This function cost O(N*M^2)
*
************************************************************************************/

Err_t polynominalMutiply(CList<polynominal_t>* input1,CList<polynominal_t>* input2,CList<polynominal_t>* output)
{
    CList<polynominal_t> *m,*n,result1,result2,result3;
    polynominal_t value;
    if((input1==NULL)||(input2==NULL)||(output==NULL))
        return INVALIDE_PARAMET;

    if(input1->CountNo()<input2->CountNo())
    {
        m=input1;
        n=input2;
    }
    else
    {
        m=input2;
        n=input1;
    }

    n->ResetElemNext();
    while(n->GetElemNext(&value)==RETURN_SUCCESS)
    {
        mutiplySingle(&value,m,&result1);
#if(DEBUG)
        int i;
        polynominal_t value1;
        result1.ResetElemNext();
        printf("Result1:::\n");
        for(i=0; i<result1.CountNo(); i++)
        {
            result1.GetElemNext(&value1);
            printf("index %d: coef %d,exponent %d\n",i,value1.coeficient,value1.exponent);
        }
        result2.ResetElemNext();
        printf("Result2:::\n");
        for(i=0; i<result2.CountNo(); i++)
        {
            result2.GetElemNext(&value1);
            printf("index %d: coef %d,exponent %d\n",i,value1.coeficient,value1.exponent);
        }
#endif
        polynominalAdd(&result1,&result2,&result3);
#if(DEBUG)
        printf("After result1+result2------>\n");
        result3.ResetElemNext();
        for(i=0; i<result3.CountNo(); i++)
        {
            result3.GetElemNext(&value1);
            printf("index %d: coef %d,exponent %d\n",i,value1.coeficient,value1.exponent);
        }
#endif
        result2=result3;
        result3.Destroy();
        result1.Destroy();
    }
    *output=result2;
    return RETURN_SUCCESS;
}


/**************************************************************
*
*   This cost O(M),Traverse only once
*
**************************************************************/
static Err_t mutiplySingle(polynominal_t* a1,CList<polynominal_t>* input,CList<polynominal_t>* output)
{
    polynominal_t value;
    if((a1==NULL)||(input==NULL)||(output==NULL))
        return INVALIDE_PARAMET;

    input->ResetElemNext();
    while(input->GetElemNext(&value)==RETURN_SUCCESS)
    {
        value.coeficient*=a1->coeficient;
        value.exponent+=a1->exponent;
#if(DEBUG)
        DB_PRINT("value.coeficient=%d,value.exponent=%d",value.coeficient,value.exponent);
#endif
        output->Insert(value);
    }
    output->Reverse(); //Keep inorder

    return RETURN_SUCCESS;
}

