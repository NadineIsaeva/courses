#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    char *name;
    int diameter;
} Satellite;

typedef struct
{
    char *name;
    int diameter;
    Satellite **satellites;
} Planet;

typedef struct
{
    char *name;
    Planet **planets;
} StarSystem;

Satellite *createSatellite(char *name, int diameter)
{
    Satellite *newSatellite = malloc(sizeof(Satellite));
    char *newName = malloc(strlen(name) + 1);
    strcpy(newName, name);
    newSatellite->name = newName;
    newSatellite->diameter = diameter;
    return newSatellite;
}

Satellite *deleteSatellite(Satellite *satellite)
{
    free(satellite->name);
    free(satellite);
    return NULL;
}

void printSatellite(Satellite *satellite)
{
    printf("Satellite %s, diameter: %i\n", satellite->name, satellite->diameter);
}

int numberOfSatellites(Satellite **satellites)
{
    int numberOfSatellites = 0;
    Satellite **currentSatellite = satellites;
    while (*currentSatellite)
    {
        ++numberOfSatellites;
        ++currentSatellite;
    }

    return numberOfSatellites;
}

Planet *createPlanet(char *name, int diameter)
{
    Planet *newPlanet = malloc(sizeof(Planet));
    char *newName = malloc(strlen(name) + 1);
    strcpy(newName, name);
    Satellite **newSatellites = malloc(sizeof(Satellite *));
    *newSatellites = NULL;
    newPlanet->name = newName;
    newPlanet->diameter = diameter;
    newPlanet->satellites = newSatellites;
    return newPlanet;
}

void addSatelliteToPlanet(Planet *planet, Satellite *satellite)
{
    int isSatelliteExists = 0;
    Satellite **currentSatellite = planet->satellites;
    while (*currentSatellite)
    {
        if (*currentSatellite == satellite)
        {
            isSatelliteExists = 1;
            break;
        }

        ++currentSatellite;
    }

    if (!isSatelliteExists)
    {
        int satellitesNumber = numberOfSatellites(planet->satellites);
        planet->satellites = realloc(planet->satellites, sizeof(Satellite *) * (satellitesNumber + 2));
        memmove(planet->satellites + 1, planet->satellites, sizeof(Satellite *) * (satellitesNumber + 1));
        planet->satellites[0] = satellite;
    }
}

void removeSatelliteFromPlanet(Planet *planet, Satellite *satellite)
{
    int satellitePosition = -1;
    int i = 0;
    Satellite **currentSatellite = planet->satellites;
    while (*currentSatellite)
    {
        if (*currentSatellite == satellite)
        {
            satellitePosition = i;
            break;
        }

        ++currentSatellite;
        ++i;
    }

    if (satellitePosition != -1)
    {
        int satellitesNumber = numberOfSatellites(planet->satellites);
        deleteSatellite(planet->satellites[i]);
        memmove(planet->satellites + i, planet->satellites + i + 1, sizeof(Satellite *) * (satellitesNumber - i + 2));
        planet->satellites = realloc(planet->satellites, sizeof(Satellite *) * satellitesNumber);
    }
}

Planet *deletePlanet(Planet *planet)
{
    free(planet->name);
    Satellite **currentSatellite = planet->satellites;
    while (*currentSatellite)
    {
        deleteSatellite(*currentSatellite);
        ++currentSatellite;
    }
    free(planet->satellites);
    free(planet);
    return 0;
}

void printPlanet(Planet *planet)
{
    printf("Planet %s, diameter: %i\nSatellites:\n", planet->name, planet->diameter);
    Satellite **currentSatellite = planet->satellites;
    int i = 0;
    while (*currentSatellite)
    {
        printf("%i: ", i);
        printSatellite(*currentSatellite);
        ++currentSatellite;
        ++i;
    }
    printf("\n");
}

int numberOfPlanets(Planet **planets)
{
    int numberOfPlanets = 0;
    Planet **currentPlanet = planets;
    while (*currentPlanet)
    {
        ++numberOfPlanets;
        ++currentPlanet;
    }

    return numberOfPlanets;
}

StarSystem *createStarSystem(char *name)
{
    StarSystem *newStarSystem = malloc(sizeof(StarSystem));
    char *newName = malloc(strlen(name) + 1);
    strcpy(newName, name);
    Planet **newPlanets = malloc(sizeof(Planet *));
    *newPlanets = NULL;
    newStarSystem->name = newName;
    newStarSystem->planets = newPlanets;
    return newStarSystem;
}

void addPlanetToStarSystem(StarSystem *starSystem, Planet *planet)
{
    int isPlanetExists = 0;
    Planet **currentPlanet = starSystem->planets;
    while (*currentPlanet)
    {
        if (*currentPlanet == planet)
        {
            isPlanetExists = 1;
            break;
        }

        ++currentPlanet;
    }

    if (!isPlanetExists)
    {
        int planetsNumber = numberOfPlanets(starSystem->planets);
        starSystem->planets = realloc(starSystem->planets, sizeof(Planet *) * (planetsNumber + 2));
        memmove(starSystem->planets + 1, starSystem->planets, sizeof(Planet *) * (planetsNumber + 1));
        starSystem->planets[0] = planet;
    }
}

void removePlanetFromStarSystem(StarSystem *starSystem, Planet *planet)
{
    int planetPosition = -1;
    int i = 0;
    Planet **currentPlanet = starSystem->planets;
    while (*currentPlanet)
    {
        if (*currentPlanet == planet)
        {
            planetPosition = i;
            break;
        }

        ++currentPlanet;
        ++i;
    }

    if (planetPosition != -1)
    {
        int planetsNumber = numberOfPlanets(starSystem->planets);
        deletePlanet(starSystem->planets[i]);
        memmove(starSystem->planets + i, starSystem->planets + i + 1, sizeof(Planet *) * (planetsNumber - i + 2));
        starSystem->planets = realloc(starSystem->planets, sizeof(Planet *) * planetsNumber);
    }
}

Planet *deleteStarSystem(StarSystem *starSystem)
{
    free(starSystem->name);
    Planet **currentPlanet = starSystem->planets;
    while (*currentPlanet)
    {
        deletePlanet(*currentPlanet);
        ++currentPlanet;
    }
    free(starSystem->planets);
    free(starSystem);
    return 0;
}

void printStarSystem(StarSystem *starSystem)
{
    printf("Star system %s\nPlanets:\n", starSystem->name);
    Planet **currentPlanet = starSystem->planets;
    int i = 0;
    while (*currentPlanet)
    {
        printf("%i: Planet %s, diameter: %i\n   Satellites:\n", i, (**currentPlanet).name, (**currentPlanet).diameter);
        Satellite **currentSatellite = (**currentPlanet).satellites;
        while (*currentSatellite)
        {
            printf("    ");
            printSatellite(*currentSatellite);
            ++currentSatellite;
        }

        ++currentPlanet;
        ++i;
    }

    printf("\n");
}

int main()
{
    Satellite *satellite1 = createSatellite("Cerera", 5);
    Satellite *satellite2 = createSatellite("Aurora", 12);
    Satellite *satellite3 = createSatellite("Centauri", 1);
    Planet *planet1 = createPlanet("Uranus", 45);
    addSatelliteToPlanet(planet1, satellite1);
    addSatelliteToPlanet(planet1, satellite2);
    addSatelliteToPlanet(planet1, satellite3);

    Satellite *satellite4 = createSatellite("Moon", 2);
    Planet *planet2 = createPlanet("Earth", 20);
    addSatelliteToPlanet(planet2, satellite4);

    StarSystem *starSystem = createStarSystem("Sun");
    addPlanetToStarSystem(starSystem, planet1);
    addPlanetToStarSystem(starSystem, planet2);

    int menuSelectedPlanet = -1;

    char inputStr[80];
    while (1)
    {
        system("cls");

        if (menuSelectedPlanet == -1)
        {
            printStarSystem(starSystem);
            printf("Enter planet number, or enter 'e' to exit program, or 'add' to add, or 'delete' to delete \n");
        }
        else
        {
            printPlanet(starSystem->planets[menuSelectedPlanet]);
            printf("Enter 'e' to exit, 'add' to add satellite or 'delete' to delete satellite\n");
        }

        scanf("%s", inputStr);

        if (menuSelectedPlanet == -1)
        {
            if (strcmp(inputStr, "e") == 0)
                break;
            else if (strcmp(inputStr, "add") == 0)
            {
                char buffer[80];
                int diameter;

                scanf("%s %i", buffer, &diameter);

                addPlanetToStarSystem(starSystem, createPlanet(buffer, diameter));
            }
            else if (strcmp(inputStr, "delete") == 0)
            {
                int num;
                scanf("%i", &num);
                removePlanetFromStarSystem(starSystem, starSystem->planets[num]);
            }
            else
            {
                int selectedPlanet = atoi(inputStr);
                if ((selectedPlanet >= 0) && (selectedPlanet < numberOfPlanets(starSystem)))
                    menuSelectedPlanet = selectedPlanet;
            }
        }
        else
        {
            if (strcmp(inputStr, "e") == 0)
                menuSelectedPlanet = -1;
            else if (strcmp(inputStr, "add") == 0)
            {
                char buffer[80];
                int diameter;

                scanf("%s %i", buffer, &diameter);

                addSatelliteToPlanet(starSystem->planets[menuSelectedPlanet], createPlanet(buffer, diameter));
            }
            else if (strcmp(inputStr, "delete") == 0)
            {
                int num;
                scanf("%i", &num);
                removeSatelliteFromPlanet(starSystem->planets[menuSelectedPlanet], starSystem->planets[menuSelectedPlanet]->satellites[num]);
            }
        }
    }

    return 0;
}
