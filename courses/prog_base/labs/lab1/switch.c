#include <math.h>
int SizeOfDataType (int data_type) {
switch(data_type) {
        case 0:
            return sizeof(char);
        case 1:
            return sizeof(signed char);
        case 2:
            return sizeof(short);
        case 3:
            return sizeof(unsigned int);
        case 4:
            return sizeof(long);
        case 5:
            return sizeof(unsigned long long);
        case 6:
            return sizeof(float);
        case 7:
            return sizeof(double);
        default:
            return 0;
}
}
int exec(int op, int a, int b) {
   int result;
   /* Insert your code here */
int n0=4;
int n1=0;

if (op<0) {
 int c = a;
     a = b;
     b = c;
     op *= -1;
    }
switch(op) {
case 0:
    return  -a;
case 1:
    return  a + b;
case 2:
    return  a - b;
case 3:
    return a*b;
case 4:
    return (b==0) ? 0: a/b;
case 5:
    return  abs(a);
case 6:
    return  pow(a,b);
case 7:
case 13:
case 77:
    return (b==0) ? 0: a%b;
case 8:
    return (a>b) ? a : b;
case 9:
    return (a<b) ? a : b;
case 10:
    return abs(a)*SizeOfDataType(abs(b)%8);
case 11:
    return floor (M_PI*((a+b)%6)/b);
default:
    return (op>=100) ? -1 : ((a+1!=0) && (b+1!=0) ? (op % abs ( a + 1 )) + ( op % abs ( b
+ 1 )) : 0 );
}
   return result;
}
