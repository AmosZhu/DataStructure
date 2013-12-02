#ifndef _RPN_CALCULATE_HPP_
#define _RPN_CALCULATE_HPP_

#define OP_PLUSMIN 0x00000001
#define OP_MULTDIV 0x00000002


#define ISDIGIT(x) (('0'<=x)&&('9'>=x))
#define ISPARTHES_L(x) (x=='(')
#define ISPARTHES_R(x) (x==')')


/*
*   This function is an external function to calculate the arithmetical expression
*/
Err_t RPNCalculate(char* expression,AM_S32* result);


#endif
