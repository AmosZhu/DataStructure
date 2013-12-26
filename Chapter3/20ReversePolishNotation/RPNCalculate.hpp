#ifndef _RPN_CALCULATE_HPP_
#define _RPN_CALCULATE_HPP_

#define OP_PLUSMIN 0x00000001
#define OP_MULTDIV 0x00000002


#define ISDIGIT(x) (('0'<=x)&&('9'>=x))
#define ISPARTHES_L(x) (x=='(')
#define ISPARTHES_R(x) (x==')')
#define ISPOW(x) (x=='^')

#define TYPE_NUMBER 0x01
#define TYPE_OP 0x02
#define TYPE_NULL 0x03

struct rpn_t
{
    AM_S32 value;
    AM_U8 type;
};


/*
*   This function is an external function to calculate the arithmetical expression
*/
Err_t RPNCalculate(char* expression,AM_S32* result);
Err_t RPNTranslate(char* expression,rpn_t* result);


#endif
