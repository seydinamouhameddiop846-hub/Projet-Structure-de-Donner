#include<stdio.h>
#include<stdbool.h>
// on cree une premier structure de type note
typedef struct Note
{
    char matier[20]; // ici on donne la matiere
    float valeur; // sa valeur
    int coef;
    struct Note *note_suivante; // permet de passer au note suivant du meme etudiant
}Note;
// on cree une deuxieme structure de type etudiant
typedef struct Etudiant
{
    char nom[30];
    char prenom[40];
    int numero_dossier; // identifiant unique par etudiant 
    bool eta_inscription; // 1 si l etudiant s'est inscrit et 0 sinon (initialise lors de la creation)
    Note *modules; // est un pointeur de type Note 
    struct Etudiant *etudiant_suivant; // permet de passer a l etudiant suivant
}Etudiant;
typedef struct
{
    char nom_filiere[60];
    int nb_etudiants;
    Etudiant *premier_du_liste; // point sur le premier de la liste des etudiant
    Etudiant *dernier_du_liste; // point sur le dernier etudiant de la liste 
}Filiere;



