#ifndef _POLYNOMINAL_HPP_
#define _POLYNOMINAL_HPP_


typedef struct POLYNOMINAL_TYPE
{
    AM_S32 coeficient;
    AM_S32 exponent;
} polynominal_t;

#define COEFONLY 0x0001  //Not use yet
#define EXPONENT 0x0002
#define SIGN 0x0004

#define SETCOEF(flag) (flag|=COEFONLY)
#define SETEXP(flag) (flag|=EXPONENT)
#define SETSIGN(flag) (flag|=SIGN)

#define CLEARCOEF(flag) (flag&=~COEFONLY)
#define CLEAREXP(flag) (flag&=~EXPONENT)
#define CLEARSIGN(flag) (flag&=~SIGN)
#define CLEARFLAG(flag) (flag=0)

#define ISDIGIT(x) (('0'<=x)&&('9'>=x))

#define INITVALUE(value) value.coeficient=1;\
                            value.exponent=0;

Err_t polynominalInput(char* buf,CList<polynominal_t>* equation);
Err_t polynominalOutput(CList<polynominal_t>* input,char* output);
Err_t polynominalAdd(CList<polynominal_t>* input1,CList<polynominal_t>* input2,CList<polynominal_t>* output);
Err_t polynominalMutiply(CList<polynominal_t>* input1,CList<polynominal_t>* input2,CList<polynominal_t>* output);

#endif
