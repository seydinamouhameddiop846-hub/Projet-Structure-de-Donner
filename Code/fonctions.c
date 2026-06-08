#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>    
#include "structure.h" // Permet d'utiliser Note et Etudiant ici !

// on va cree une fonction qui permetra de cree un etudiant et de l ajouter dans une filiere
void inscrire_etudiants(Filiere *filiere)
{
    // allocation dynamique d un nouveau etudiant
    Etudiant *nouveau_etudiant = (Etudiant*) malloc(sizeof(Etudiant));
    if (nouveau_etudiant == NULL)
    {
        printf("Ereure : impossible d allouer la memoire");
        return;
    }
    // ajout des information d un etudiant par l utulisateur
    printf("\n--------Formulaire d inscription--------\n");
    printf("Donner le nom de l etudiant : \n");
    scanf("%s", nouveau_etudiant->nom);
    printf("Donner le prenom de l etudiant : \n");
    scanf("%s", nouveau_etudiant->prenom);
    printf("Donner son numero de dosier : \n");
    scanf("%d", &nouveau_etudiant->numero_dossier);

    nouveau_etudiant->eta_inscription = 1;    // on va enregistrer l etat d inscription a 1 par defaut
    nouveau_etudiant->modules = NULL ; // pas encore de note
    nouveau_etudiant->etudiant_suivant = NULL; // se sera le dernier etudiant

    if (filiere->premier_du_liste == NULL) 
    {
        // La liste est vide, il est le tout premier et le tout dernier
        filiere->premier_du_liste = nouveau_etudiant;
        filiere->dernier_du_liste = nouveau_etudiant;
    } else 
    {
        filiere->dernier_du_liste->etudiant_suivant = nouveau_etudiant; // si la liste est non vide le pointeur dernier_du_liste va pointe sure le nouveau etudiant
        filiere->dernier_du_liste = nouveau_etudiant; // Il devient le nouveau dernier de la filiere
    }

    filiere->nb_etudiants++; // On incremente le compteur de la classe
    printf("L'etudiant %s %s a ete inscrit avec succes !\n", nouveau_etudiant->prenom, nouveau_etudiant->nom);
}
void bultin_etudiant(Etudiant *etudiant)
{
    Note *nouveau_note = (Note*)malloc(sizeof(Note));
    if (nouveau_note == NULL)
    {
        printf("Ereure : impossible d allouer la memoire");
        return;
    }
    // ajout du resultat d un etudiant
    printf("\n--------Resultats Academique--------\n");
    printf("Donner la matiere : \n");
    scanf("%s", nouveau_note->matier);
    printf("Donner la note obtenue : \n");
    scanf("%f", &nouveau_note->valeur);
    printf("Donner le coeficient du matiere : \n");
    scanf("%d", &nouveau_note->coef);

    nouveau_note->note_suivante = NULL; // c est la premiere et dernier note 


    if (etudiant->modules == NULL)
    {
        // Cas ou l etudiant n a encore aucune note
        etudiant->modules = nouveau_note;
    } 
    else 
    {
        // Cas ou l'etudiant a deja des notes, on parcourt pour aller a la fin
        Note *courant = etudiant->modules;
        while (courant->note_suivante != NULL) 
        {
            courant = courant->note_suivante;
        }
        // On accroche la nouvelle note tout a la fin
        courant->note_suivante = nouveau_note;
    }
    
    

    

}
