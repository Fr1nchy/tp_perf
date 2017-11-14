#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "algo_principal.h"
#include "appels_sequentiels.h"

void algo_principal(int parallelism, int *tableau, int taille, char *arg)
{
    void *args_algo;
    arguments_t args;
    (void) parallelism;
    struct timeval temps_execution_avant, temps_execution_apres;

    gettimeofday (&temps_execution_avant, NULL);
    args_algo = initialisation(0, tableau, taille, arg);
    args.num = 0;
    args.inf = 0;
    args.sup = taille-1;
    args.tableau = tableau;
    args.taille = taille;
    args.args_algo = args_algo;

    traitement(&args);

    traitement_resultats(0, &args);
    gettimeofday (&temps_execution_apres, NULL);
    printf("temps execution en us: %ld us\n",((temps_execution_apres.tv_sec - temps_execution_avant.tv_sec) * 1000000 + temps_execution_apres.tv_usec) - temps_execution_avant.tv_usec);
}
