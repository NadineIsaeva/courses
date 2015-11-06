#include <stdio.h>
#include <math.h>


int n = 15;
int m = 4;


double calc(int n, int m)
{
    double x = 0;
    int i;
    int j;
    int n1 = 0;
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= m; j++)
        {
            x += cos(i*M_PI/2) + (n1+1)*sin(j*M_PI/4);
        }
    }

    return x;
}

int main () {
    printf("%f ", calc(n, m));
}
