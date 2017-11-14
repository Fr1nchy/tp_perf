#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "algo_principal.h"
#include "appels_sequentiels.h"

void *comportement_thread(void *arg) {
    traitement((arguments_t *) arg);
    pthread_exit(NULL);
}

void algo_principal(int parallelism, int *tableau, int taille, char *arg)
{
    arguments_t *arguments;
    pthread_t *tids;
    int inf, sup;
    int erreur, i;
    void *status, *args_algo;
    int temps_creation, temps_total;
    struct timeval temps_total_avant, temps_total_apres,temps_creation_avant,temps_creation_apres;

    gettimeofday (&temps_total_avant, NULL);
    args_algo = initialisation(parallelism, tableau, taille, arg);

    tids = malloc(parallelism*sizeof(pthread_t));
    arguments = malloc(parallelism*sizeof(arguments_t));
    if ((tids == NULL) || (arguments == NULL)) {
        fprintf(stderr, "Impossible d'allouer les structures de gestion des "
                        "threads\n");
        exit(1);
    }

    inf = 0;
    sup = (taille-1) / parallelism;

    gettimeofday (&temps_creation_avant, NULL);
    for (i=0; i<parallelism; i++) {
        arguments[i].num = i;
        arguments[i].inf = inf;
        arguments[i].sup = sup;
        arguments[i].tableau = tableau;
        arguments[i].taille = taille;
        arguments[i].args_algo = args_algo;

        erreur = pthread_create(&tids[i], NULL, comportement_thread,
                                &arguments[i]);
        if (erreur != 0) {
            fprintf(stderr, "Erreur de creation du thread %d\n", i);
            exit(1);
        }
        inf = sup+1;
        sup = ((i+2)*(taille-1)) / parallelism;
    }
    gettimeofday (&temps_creation_apres, NULL);

    for (i=0; i<parallelism; i++)
         pthread_join(tids[i], &status);
    traitement_resultats(parallelism, arguments);

    free(arguments);
    free(tids);
    gettimeofday (&temps_total_apres, NULL);
    temps_creation = ((temps_creation_apres.tv_sec - temps_creation_avant.tv_sec) * 1000000 + temps_creation_apres.tv_usec) - temps_creation_avant.tv_usec;
    temps_total = ((temps_total_apres.tv_sec - temps_total_avant.tv_sec) * 1000000 + temps_total_apres.tv_usec) - temps_total_avant.tv_usec;
    //printf("%ld\n", temps_creation); //temps de création threads en us
    printf("%ld\n",temps_total-temps_creation); // temps execution en us

}
