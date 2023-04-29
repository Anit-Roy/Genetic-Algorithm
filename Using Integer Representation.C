#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
int **population, **children, *popfitnessarray, *childfitnessarray;
int popsize, childcount, irsize;
int individualsize, maxfitvaluefound, maxfitindividualposition;
float mutprobability, randzeroone;
int crossoverindex;
int OPTIMALSOLFITNESS, MAXITER, BASE_SIZE;
int lb, ub;
int iterations = 0;
int solutionfound();
void initpopulation();
void evalfitness(int **, int, int *);
int fitness(int *);
void recombineparents();
void mutatechildren();
void makenextgenpopulation();
void getinputparams();
void printsolution(const char *);
void printdata(int **, int, int *);

int main()
{
    getinputparams();
    initpopulation();
    evalfitness(population, popsize, popfitnessarray);
    printdata(population, popsize, popfitnessarray);
    while (iterations < MAXITER)
    {
        iterations++;
        if (solutionfound())
        {
            printsolution("Optimal Solution found with ");
            return 0;
        }
        recombineparents();
        mutatechildren();
        evalfitness(children, childcount, childfitnessarray);
        printdata(children, childcount, childfitnessarray);
        makenextgenpopulation();
    }
    if (solutionfound())
        printsolution("Optimal Solution found with ");
    else
        printsolution("Sub-optimal Solution found with ");
    return 0;
}

void getinputparams()
{
    printf("Enter individual size(representation size):");
    scanf("%d", &irsize);
    printf("Enter poplationsize:");
    scanf("%d", &popsize);
    printf("Enter mutation probability:");
    scanf("%f", &mutprobability);
    printf("Enter maximum fitness level of optimal solution:");
    scanf("%d", &OPTIMALSOLFITNESS);
    printf("Enter maximum number of iterations:");
    scanf("%d", &MAXITER);
    printf("Enter the base size:");
    scanf("%d", &BASE_SIZE);
    printf("Enter the lower bound:");
    scanf("%d", &lb);
    printf("Enter the upper bound:");
    scanf("%d", &ub);

    childcount = popsize;
    population = (int **)malloc(popsize * sizeof(int *));
    children = (int **)malloc(childcount * sizeof(int *));
    for (int i = 0; i < childcount; i++)
    {
        children[i] = malloc(irsize * sizeof(int));
    }
    popfitnessarray = (int *)malloc(popsize * sizeof(int));
    childfitnessarray = (int *)malloc(childcount * sizeof(int));
}

void printdata(int **candidates, int count, int *fitnessarray)
{
    int i, j;
    printf("============Printing %s data==========", candidates == population ? "Population" : "Children");
    for (i = 0; i < count; i++)
    {
        printf("\nIndividual[%d]=", i + 1);
        for (j = 0; j < irsize; j++)
            printf("%d ", candidates[i][j]);
        printf("   Fitness=%d\n", fitnessarray[i]);
    }
    printf("\n");
}

void printsolution(const char *text)
{
    int i;
    printf("%s fitness=%d and solution individual=", text, maxfitvaluefound);
    for (i = 0; i < irsize; i++)
        printf("%d ", population[maxfitindividualposition][i]);
    printf("\n <popltnsize, irsize, parentcount, childcount, mutnprobab, maxitertns, itertnsdone,individualno>=");
    printf(" <%d, %d, %d, %d, %0.3f, %d, %d, %d>\n", popsize, irsize, popsize, childcount, mutprobability, MAXITER, iterations, maxfitindividualposition + 1);
}

int solutionfound()
{
    int i, solutionfound = 0;
    maxfitvaluefound = INT_MIN;
    for (i = 0; i < popsize; i++)
    {
        if (popfitnessarray[i] > maxfitvaluefound)
        {
            maxfitvaluefound = popfitnessarray[i];
            maxfitindividualposition = i;
        }
        if (popfitnessarray[i] == OPTIMALSOLFITNESS)
        {
            solutionfound = 1;
            maxfitvaluefound = popfitnessarray[i];
            maxfitindividualposition = i;
        }
    }
    return solutionfound;
}

void initpopulation()
{
    srand(time(0));
    int i, j;
    for (i = 0; i < popsize; i++)
    {
        population[i] = (int *)malloc(irsize * sizeof(int));
        for (j = 0; j < irsize; j++)
            population[i][j] = rand() % BASE_SIZE;
    }
}
void evalfitness(int **candidates, int count, int *fitnessarray)
{
    int i;
    for (i = 0; i < count; i++)
        fitnessarray[i] = fitness(candidates[i]);
}

int fitness(int *individual)
{
    int i, fitval = 0;
    for (i = 0; i < irsize; i++)
        if (individual[i] == BASE_SIZE - 1)
            fitval++;
    return fitval;
}

void recombineparents()
{
    int i, j, k;
    for (i = 0, k = 0; i < popsize; i += 2, k += 2)
    {
        crossoverindex = rand() % irsize;
        for (j = 0; j < irsize; j++)
        {
            if (j < crossoverindex)
            {
                children[k][j] = population[i][j];
                children[k + 1][j] = population[i + 1][j];
            }
            else
            {
                children[k][j] = population[i + 1][j];
                children[k + 1][j] = population[i][j];
            }
        }
    }
}

void makenextgenpopulation()
{
    int i, j;
    memcpy(population[0], children[0], irsize * sizeof(int));
    for (i = 1; i < popsize; i++)
    {
        memcpy(population[i], children[i], irsize * sizeof(int));
    }

    memcpy(popfitnessarray, childfitnessarray, popsize * sizeof(int));
}

void mutatechildren()
{
    int i, j, newgen;
    for (i = 0; i < childcount; i++)
    {
        srand(time(0));
        for (j = 0; j < irsize; j++)
        {
            randzeroone = ((float)rand()) / RAND_MAX;
            if (randzeroone <= mutprobability)
            {
                // children[i][j] = 1 - children[i][j];
                newgen = (rand() % (ub - lb + 1)) + (ub - lb + 1);
                if (newgen > BASE_SIZE - 1)
                {
                    newgen = BASE_SIZE - 1;
                }
                if (newgen < 0)
                {
                    newgen = 0;
                }

                children[i][j] = newgen;
            }
        }
    }
}
