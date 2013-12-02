/*******************************************************************
*
*   This file processes the arithmetic operation,
*   Amos use the Reverse Polish notation to process the expression
*
*******************************************************************/


#include "AmosType.hpp"
#include "RPNCalculate.hpp"
#include "CStack.hpp"

/*************************************
*               Macro
*************************************/


/************************************
*       Internal function
************************************/
static AM_S32 calculate(AM_S32 v1,AM_S32 v2,char op);
static BOOL priorityCmp(char op1,char op2);
static BOOL IsOperator(char op);
static AM_U32 processDigit(char** fmt);


/***********************************
*               Text
***********************************/


Err_t RPNCalculate(char* expression,AM_S32* result)
{
    char* p;
    char opIn;
    char opOut;
    AM_S32 value;
    AM_S32 v1,v2;
    CStack<char> opStack;  /*Store the operation*/
    CStack<AM_S32> numStack; /*Store the numbers*/

    if((expression==NULL)||(result==NULL))
        return INVALIDE_PARAMET;

    p=expression;

    while(*p)
    {
        if(ISDIGIT(*p))/*Process digit*/
        {
            value=processDigit(&p);
            numStack.Push(&value);
            continue;
        }

        if(ISPARTHES_L(*p)) /*Not a digit ,maybe a left parentheses*/
        {
            opStack.Push(p);
            p++;
            continue;
        }

        if(ISPARTHES_R(*p)) /*Maybe a right parentheses*/
        {
            while((opStack.Pop(&opOut)==RETURN_SUCCESS)&&(!ISPARTHES_L(opOut))&&(!opStack.IsEmpty()))
            {
                numStack.Pop(&v2);
                numStack.Pop(&v1);
                value=calculate(v1,v2,opOut);
                if(value==INFINITY)
                    return OPERATOR_FAILED;
                numStack.Push(&value);
            }
            p++;
            continue;
        }

        while((!opStack.IsEmpty())&&(!numStack.IsEmpty())\
              &&(opStack.Top(&opOut)==RETURN_SUCCESS)&&(!ISPARTHES_L(opOut))\
              &&(priorityCmp(opOut,*p)==TRUE)) /*A normal operator,pop out the operator which */
        {
            opStack.Pop(&opOut);
            numStack.Pop(&v2);
            numStack.Pop(&v1);
            value=calculate(v1,v2,opOut);
            if(value==INFINITY)
                return INVALIDE_PARAMET;
            numStack.Push(&value);

        }
        opStack.Push(p);
        p++;
        continue;
    }

    /*
    *   Some operator may still in the stack
    */

    while(!opStack.IsEmpty())
    {
        opStack.Pop(&opOut);
        numStack.Pop(&v2);
        numStack.Pop(&v1);
        value=calculate(v1,v2,opOut);
        if(value==INFINITY)
            return OPERATOR_FAILED;
        numStack.Push(&value);
    }

    /*
    *   When operators have been all processed,the last number must be the result
    */
    numStack.Pop(result);

    /*
    *   If there still some elements in the numStack, the expression is invalid
    */
    if(!numStack.IsEmpty())
        return OPERATOR_FAILED;

    return RETURN_SUCCESS;
}

static AM_S32 calculate(AM_S32 v1,AM_S32 v2,char op)
{
    AM_S32 ret=INFINITY;
    switch(op)
    {
        case '+':
        {
            ret=v1+v2;
        }
        break;
        case '-':
        {
            ret=v1-v2;
        }
        break;
        case '*':
        {
            ret=v1*v2;
        }
        break;
        case '/':
        {
            ret=v1/v2;
        }
        break;
        default:
            printf("Invalide input!\n");
    }
    return ret;
}

/************************************************************************
*
*   If op1's priority is bigger than op2/Or equal,it will return TRUE
*   Otherwise it will return FALSE;
*
************************************************************************/

static BOOL priorityCmp(char op1,char op2)
{
    AM_U32 flag1=0,flag2=0;
    switch(op1)
    {
        case '+':
        case '-':
            flag1|=OP_PLUSMIN;
            break;
        case '*':
        case '/':
            flag1|=OP_MULTDIV;
            break;
        default:
            printf("%c is invalid operator!\n",op1);
            break;
    }

    switch(op2)
    {
        case '+':
        case '-':
            flag2|=OP_PLUSMIN;
            break;
        case '*':
        case '/':
            flag2|=OP_MULTDIV;
            break;
        default:
            printf("%c is invalid operator!\n",op2);
            break;
    }


    if(flag1>=flag2)
        return TRUE;
    else
        return FALSE;
}

static BOOL IsOperator(char op)
{
    switch(op)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            return TRUE;
        default:
            return FALSE;
    }
}

static AM_U32 processDigit(char** fmt)
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



