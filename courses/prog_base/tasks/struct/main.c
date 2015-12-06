#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Planet
    {
        char pName[20];
        int numOfSat;
        char * pColor;
    };

void print(int size, struct Planet * Planets)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf ("%d) %s\n", i+1, Planets[i].pName);
        printf ("The number of satellites: %d\n", Planets[i].numOfSat);
        printf ("The color of the planet: %s\n\n", Planets[i].pColor);
    }

}

int count(int size, struct Planet Planets[])
{
    int i;
    int number = 0;
    for (i = 0; i < size; i++)
    {
        if (Planets[i].numOfSat == 0)
        {
           number++;
        }
    }
    return number;
}

void change(struct Planet * pVar, const char * newValue)
{
    strcpy(pVar -> pName, newValue);
}

int main(void)
{
    int i;
    int size = 10;
    int number;
    int index = 0;
    struct Planet Planets[] = {{"Earth", 1, "nice blue"},
                            {"Venus", 0, "light yellow"},
                            {"Saturn", 62, "beige"},
                            {"Jupiter", 67, "strange orange"},
                            {"Uranus", 27, "light blue"},
                            {"Neptune", 14, "beautiful blue"},
                            {"Mercury", 0, "gray"},
                            {"Mars", 2, "red"},
                            {"Pluto", 5, "dark beige"},
                            {"Ceres", 0, "dark gray"}};

    print (size, Planets);
    count (size, Planets);
    printf("Number of planets without satellites: %d\n\n", count(size, Planets));

    printf("Enter the index of planet you want to rename: ");
    scanf("%d\n", &index);
    struct Planet * pVar = &Planets[index];
    change(pVar, "azaza kek");
    printf("Planets after renaming. Let's look for your renamed string!\n\n");
    print (size, Planets);

  /*Earth.pName = "Earth";
    Earth.numOfSat = 1;
    Earth.pColor = "nice_blue";

    struct Planet Venus;
    Venus.pName = "Venus";
    Venus.numOfSat = 0;
    Venus.pColor = "light_yellow";

    struct Planet Saturn;
    Saturn.pName = "Saturn";
    Saturn.numOfSat = 62;
    Saturn.pColor = "beige";

    struct Planet Jupiter;
    Jupiter.pName = "Jupiter";
    Jupiter.numOfSat = 67;
    Jupiter.pColor = "strange_orange";

    struct Planet Uranus;
    Uranus.pName = "Uranus";
    Uranus.numOfSat = 27;
    Uranus.pColor = "light_blue";

    struct Planet Neptune;
    Neptune.pName = "Neptune";
    Neptune.numOfSat = 14;
    Neptune.pColor = "beautiful_blue";

    struct Planet Mercury;
    Mercury.pName = "Mercury";
    Mercury.numOfSat = 0;
    Mercury.pColor = "gray";

    struct Planet Mars;
    Mars.pName = "Mars";
    Mars.numOfSat = 2;
    Mars.pColor = "red";

    struct Planet Pluto;
    Pluto.pName = "Pluto";
    Pluto.numOfSat = 5;
    Pluto.pColor = "dark_beige";

    struct Planet Ceres;
    Ceres.pName = "Ceres";
    Ceres.numOfSat = 0;
    Ceres.pColor = "dull_gray";*/
    return 0;
}

