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
void bultin_etudiant(Etudiant *etudiant) // une fonction permetant d enregistrer les resultat academique d un etudiant
{
    if (etudiant == NULL) return;

    // On verifie si l'etudiant est bien inscrit
    if (etudiant->eta_inscription == 0)
    {
        printf("Impossible d'ajouter une note : cet etudiant n'est pas activement inscrit.\n");
        return;
    }
    Note *nouveau_note = (Note*)malloc(sizeof(Note)); // allocation dynamique 
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
        Note *note_restante = etudiant->modules;
        while (note_restante->note_suivante != NULL) 
        {
            note_restante = note_restante->note_suivante;
        }
        // On accroche la nouvelle note tout a la fin
        note_restante->note_suivante = nouveau_note;
    }
    
}
// on va cree une fonction pour parcourire et afficher les etudiants de la liste
void liste_de_la_classe(Filiere *filiere)
{
    if (filiere == NULL || filiere->premier_du_liste == NULL) // verifie si la filiere est vide ou non
    {
        printf("Aucun etudiant inscrit dans la filiere.\n");
        return;
    }

    printf("\n--------Liste des etudiants de la classe--------\n");
    Etudiant *actuel_liste = filiere->premier_du_liste;
    while (actuel_liste != NULL) // affiche les identifient des etudiants
    {
        printf("Nom: %s, Prenom: %s, Numero de dossier: %d\n",actuel_liste->nom, actuel_liste->prenom, actuel_liste->numero_dossier);
        actuel_liste = actuel_liste->etudiant_suivant;
    }
}
// fonction qui va afficher le bulletin d un etudiant
void bulletin(Filiere *filiere)
{
    if (filiere == NULL || filiere->premier_du_liste == NULL)
    {
        printf("Aucun etudiant inscrit dans la filiere.\n");
        return;
    }

    printf("\n--------Bulletin des etudiants de la classe--------\n");
    Etudiant *actuel_liste_info = filiere->premier_du_liste;
    if (actuel_liste_info->eta_inscription == 1)
    {
        while (actuel_liste_info != NULL)
        {
            printf("Nom: %s, Prenom: %s, Numero de dossier: %d\n",actuel_liste_info->nom, actuel_liste_info->prenom, actuel_liste_info->numero_dossier);
            Note *actuel_liste_bulletin = actuel_liste_info->modules;
            float moyenne;
            float point_totale = 0;
            int coef_totale = 0;
            while (actuel_liste_bulletin != NULL)
            {
                printf("Matiere: %s, Note: %f, Coeficiant: %d\n",actuel_liste_bulletin->matier, actuel_liste_bulletin->valeur, actuel_liste_bulletin->coef);
                point_totale += actuel_liste_bulletin->valeur*actuel_liste_bulletin->coef;
                coef_totale += actuel_liste_bulletin->coef;
                actuel_liste_bulletin = actuel_liste_bulletin->note_suivante;
            }
            actuel_liste_info = actuel_liste_info->etudiant_suivant;
            if (coef_totale != 0)
            {
                 moyenne = point_totale/coef_totale;
                printf("Moyenne Generale: %.2f\n",moyenne);
            }
            else
            printf("Aucune note enregistre\n");
        }

    }
}
// fonction pour rechercher un etudiant
void recherche_et_modification_etudiant(Filiere *filiere)
{
    if (filiere == NULL || filiere->premier_du_liste == NULL)
    {
        printf("Aucun etudiant dans la filiere.\n");
        return;
    }
    int id_rechercher;
    printf("Donner le numero de dossier de l etudiant rechercher:\n");
    scanf("%d", &id_rechercher);

    Etudiant *etudiant_actuel = filiere->premier_du_liste;
    while (etudiant_actuel != NULL && etudiant_actuel->numero_dossier != id_rechercher)
    {
        etudiant_actuel = etudiant_actuel->etudiant_suivant;
    }
    if (etudiant_actuel == NULL)
    {
        printf("%d ne correspond a aucun etudiant enregistre:\n", id_rechercher);
    }
    else
    {
        int choix;
        printf("\n--------Etudiant trouver--------\n");
        printf("Nom: %s, Prenom: %s, Numero de dossier: %d, Etat d inscription:%s", etudiant_actuel->nom, etudiant_actuel->prenom, etudiant_actuel->numero_dossier, (etudiant_actuel->eta_inscription == 1) ? "Inscrit" : "Non inscrit");
        printf("\n-------Que souhaitez-vous modifier--------\n");
        printf("1 Le Nom\n");
        printf("2 Le Prenom\n");
        printf("3 Le Numero de dossier\n");
        printf("4 L etat d'inscription (1: inscrit, 0: Suspendu)\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

    switch (choix) // cette partie va permetre a l utulisateur de modifier les parametre qu il souhaite
        {
         case 1:
            printf("Entrez le nouveau nom : ");
            scanf("%s", etudiant_actuel->nom);
            printf("Nom modifie avec succes !\n");
            break;
         case 2:
            printf("Entrez le nouveau prenom : ");
            scanf("%s", etudiant_actuel->prenom);
            printf("Prenom modifie avec succes !\n");
            break;
         case 3:
            printf("Entrez le nouveau numero de dossier : ");
            scanf("%d", &etudiant_actuel->numero_dossier);
            printf("Numero de dossier modifie avec succes !\n");
            break;
         case 4:
            printf("Entrez le nouveau statut (1 pour Inscrit, 0 pour Non inscrit) : ");
            scanf("%d", &etudiant_actuel->eta_inscription);
            printf("Statut d'inscription mis a jour !\n");
            break;
         default:
            printf("Choix invalide. Aucune modification effectuee.\n");
            break;
        }

    }
}
// fonction pour suprimer un etudiant de la liste
void suprimer_etudiant(Filiere *filiere)
{
    if (filiere == NULL || filiere->premier_du_liste == NULL)
    {
        printf("Il n y a aucune etudiant ");
        return;
    }
    int id_supprimer;
    printf("Donner le numero de dossier de l etudiant que vous souhaiter suprimer de la filiere:\n");
    scanf("%d", &id_supprimer);
    Etudiant *actuel_etudiant = filiere->premier_du_liste;
    Etudiant *precedent_etudiant = NULL;
    while (actuel_etudiant != NULL && id_supprimer != filiere->premier_du_liste->numero_dossier)
    {
        precedent_etudiant = actuel_etudiant; // l etudiant precedent devient l actuel etudiant
        actuel_etudiant = actuel_etudiant->etudiant_suivant; // l actuel etudiant pas a l etudiant suivant
    }
    if (actuel_etudiant == NULL)
    {
        printf("Etudiant introuvable avec l id :%d\n",id_supprimer);
    }
    if (precedent_etudiant == NULL)
    {
        // correspond au premier etudiant
        filiere->premier_du_liste = actuel_etudiant->etudiant_suivant;
        // cas ou la liste contien q un seul etudiant
        if (filiere->premier_du_liste == NULL)
        {
            filiere->dernier_du_liste = NULL;
        }
        
    }
    else
    {
        // l etudiant est au milieux ou a la fin
        precedent_etudiant->etudiant_suivant = actuel_etudiant->etudiant_suivant;
        // Si on a supprimé le dernier, l'avant-dernier (precedent) devient le nouveau dernier
        if (actuel_etudiant == filiere->dernier_du_liste) 
        {
            filiere->dernier_du_liste = precedent_etudiant;
        }
    }
    free(actuel_etudiant); // liber l espace allouher a l etudiant suprimer
    filiere->nb_etudiants--;
    printf("L etudiant avec l id :%d a ete supprimer avec succe\n", id_supprimer);
}

