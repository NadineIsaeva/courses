/*#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double long2double (long long);
int main () {
    long long number;
    printf ("Enter the number ");
    scanf ("%lli", &number);
    printf ("%.325llf",long2double(number));
}*/
double long2double (long long number){
double E = 0, F=0, V;
short S,i,j;
S=(number>>63)&1;
for (i=52;i<63;i++){
    E+=(((number>>i)&1)*pow(2,i-52));
}
for (j=51;j>=0;--j){
    F+= (((number>>j)&1)*pow(2,j-52));
}
if ((E == 2047) && (F!=0)) {
    return NAN;
}
if ((E == 2047) && (F==0) && (S==0)) {
    return INFINITY;
}
if ((E == 2047) && (F==0) && (S==1)) {
    return -INFINITY;
}
if ((E>0) && (E<2047)) {
        V = pow(-1,S)*pow(2,E-1023)*(F+1);
    return V;
}
if ((E==0) && (F!=0)){
        V = pow(-1,S) * pow(2,-1022)*F;
    return V;
}
if ((E==0) && (F==0) && (S==1)) {
    return -0;
}
if ((E==0) && (F==0) && (S==0)) {
    return 0;
}


}

