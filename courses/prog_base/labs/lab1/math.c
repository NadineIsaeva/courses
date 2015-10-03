#include <math.h>
double calc ( double x , double y , double z ) {
    double a;
  if ((z!=0) && (x>0) && (sin(y)!=0) && ((x-y)>=0) && (pow(x-y,1/z)!=0)) {
    a = pow(x,y+1)/pow(x-y,1/z) + 4*y+z/x+pow(x,abs(1/sin(y)));
    return a;
  }
  else {
        return NAN;
  }
}
