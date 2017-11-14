#!/bin/bash
taille_vecteur=1000
taille_vecteur_max=1000000
nbthreads=1
while [ $taille_vecteur -le $taille_vecteur_max ]
do
  ./creer_vecteur -s taille_vecteur > vecteur.txt
  #./tri_sequentiel --time --quiet --rusage < vecteur.txt
  #./tri_threads --time --rusage --quiet --parallelism 4 < vecteur.txt
  taille_vecteur=$(($taille_vecteur + 1000))
done

#./creer_vecteur -s taille_vecteur >vecteur.txt
