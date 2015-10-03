#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main () {
    int hour = 2;
    int minute = 17;
    int code = 44;
    int time = (hour*60) + minute;
    float price;
    if ((code>=10) && (code<=999)) {
        switch (code) {
    case 44:
        price = time*0.77;
        break;
    case 62:
        price = time*0.8;
        break;
    case 32:
        price = time*0.95;
        break;
    case 692:
    case 697:
        price = time*1.5;
        break;
    default:
        price = time*1;
        break;

}
if ((code<10) && (code>999)) {
            printf("Error");
        }
        else {printf("%f", price);
        }
    }
}



