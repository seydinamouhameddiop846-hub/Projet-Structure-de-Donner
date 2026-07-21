
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdbool.h>    
#include "structure.h" 

// on va cree une fonction qui permetra de cree un etudiant et de l ajouter dans une filiere
Etudiant *inscrire_etudiants(Filiere *filiere)
{
    // allocation dynamique d un nouveau etudiant
    Etudiant *nouveau_etudiant = (Etudiant*) malloc(sizeof(Etudiant));
    if (nouveau_etudiant == NULL)
    {
        printf("Ereure : impossible d allouer la memoire");
        return NULL;
    }
    // ajout des information d un etudiant par l utulisateur
    printf("\n-------------------------------------Formulaire d inscription---------------------------------------------------- :\n");
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
        filiere->dernier_du_liste->etudiant_suivant = nouveau_etudiant; // le pointeur dernier_du_liste  pointe sure le nouveau etudiant
        filiere->dernier_du_liste = nouveau_etudiant; // Il devient le nouveau dernier de la filiere
    }

    filiere->nb_etudiants++; 
    printf("L'etudiant %s %s a ete inscrit avec succes !\n", nouveau_etudiant->prenom, nouveau_etudiant->nom);
    return nouveau_etudiant;
}
void note_etudiants(Etudiant *etudiant) // une fonction permetant d enregistrer les resultat academique d un etudiant
{
    if (etudiant == NULL) return;

    // On verifie si l'etudiant est bien inscrit
    if (etudiant->eta_inscription == 0)
    {
        printf("Impossible d'ajouter une note : cet etudiant n'est pas activement inscrit.\n");
        return;
    }
    int nouveaux_matiere = 2;
    while (nouveaux_matiere == 2)
    {
        Note *nouveau_note = (Note*)malloc(sizeof(Note)); // allocation dynamique 
        if (nouveau_note == NULL)
        {
        printf("Ereure : impossible d allouer la memoire");
        return;
        }
    
    
        // ajout du resultat d un etudiant
        printf("\n---------------------------------Resultats Academique--------------------------------------------------------S :\n");
        printf("Donner la matiere : \n");
        scanf("%s", nouveau_note->matier);
        do
        {
            printf("Donner la note obtenue : \n");
            scanf("%f", &nouveau_note->valeur);
            if (nouveau_note->valeur < 0 || nouveau_note->valeur > 20) 
            {
                printf("Erreur ! La note doit etre comprise entre 0 et 20.\n");
            }
        }   while (nouveau_note->valeur < 0 || nouveau_note->valeur > 20);
        do
        {
            printf("Donner le coeficient du matiere : \n");
            scanf("%d", &nouveau_note->coef);
            if (nouveau_note->coef <= 0 || nouveau_note->coef > 10) 
            {
                printf("Erreur ! Le coefficient doit etre compris entre 1 et 10.\n");
            }
        } while (nouveau_note->coef <= 0 || nouveau_note->coef > 10);
    
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
            // On ajoute la nouvelle note tout a la fin
            note_restante->note_suivante = nouveau_note;
        }
        printf("Matiere ajouter avec succe:\n");
        printf("Si vous vouler ajouter une nouvelle matiere tape 2 si non 0:\n");
        scanf("%d", &nouveaux_matiere);
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

    printf("\n---------------------------------Liste des etudiants de la classe------------------------------------------------ :\n");
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

    printf("\n--------------------------------Bulletin des etudiants de la classe---------------------------------------------- :\n");
    
    float somme_des_moyennes_classe = 0;
    int etudiants_avec_notes = 0; // prend en compte que les etudiants ayant une moyenne 

    Etudiant *actuel_liste_info = filiere->premier_du_liste;
    
    while (actuel_liste_info != NULL)
    {
        // On verifie le statut d inscription de chaque etudiant 
        if (actuel_liste_info->eta_inscription == 1)
        {
            printf("Nom: %s, Prenom: %s, Numero de dossier: %d\n", actuel_liste_info->nom, actuel_liste_info->prenom, actuel_liste_info->numero_dossier);
            Note *actuel_liste_bulletin = actuel_liste_info->modules;
            float point_totale = 0;
            int coef_totale = 0;
            
            while (actuel_liste_bulletin != NULL)
            {
                printf("Matiere: %s, Note: %f, Coeficiant: %d\n", actuel_liste_bulletin->matier, actuel_liste_bulletin->valeur, actuel_liste_bulletin->coef);
                point_totale += actuel_liste_bulletin->valeur * actuel_liste_bulletin->coef;
                coef_totale += actuel_liste_bulletin->coef;
                actuel_liste_bulletin = actuel_liste_bulletin->note_suivante;
            }
            
            if (coef_totale != 0)
            {
                actuel_liste_info->moyenne_general = point_totale / coef_totale;
                printf("Moyenne Generale: %.2f\n\n", actuel_liste_info->moyenne_general);
                somme_des_moyennes_classe += actuel_liste_info->moyenne_general;
                etudiants_avec_notes++;
            }
            else
            {
                actuel_liste_info->moyenne_general = 0;
                printf("Aucune note enregistre\n");
            }
        }
        // On passe a l etudiant suivant 
        actuel_liste_info = actuel_liste_info->etudiant_suivant;
    }

    // Affichage de la moyenne gennerale 
    if (etudiants_avec_notes != 0)
    {
        float moyenne_general_classe = somme_des_moyennes_classe / etudiants_avec_notes;
        printf("MOYENNE GENERALE DE LA FILIERE : %.2f / 20\n", moyenne_general_classe);
    }
    else
    {
        printf("Les etudiants non pas de note.\n");
    }
}
// fonction pour rechercher un etudiant
void recherche_et_modification_etudiant(Filiere *filiere)
{
    int votre_choix = 3;
    int choix;
    char matier[50];
    float note;
    int coef;
    while (votre_choix == 3)
    {
        printf("Voulez vous rechercher ou modifier les info d un autre etudiant si oui taper 3 si non 0:\n");
        scanf("%d", &votre_choix);
        if (votre_choix == 0)
        {
            break;
        }
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
            printf("\n-----------------------------------------Etudiant trouver--------------------------------------------------\n");
            printf("Nom: %s, Prenom: %s, Numero de dossier: %d, Etat d inscription:%s", etudiant_actuel->nom, etudiant_actuel->prenom, etudiant_actuel->numero_dossier, (etudiant_actuel->eta_inscription == 1) ? "Inscrit" : "Non inscrit");
            printf("\n------------------------------------Que souhaitez-vous modifier--------------------------------------------\n");
            printf("[1] Le Nom\n");
            printf("[2] Le Prenom\n");
            printf("[3] Le Numero de dossier\n");
            printf("[4] L etat d'inscription (1: inscrit, 0: Suspendu)\n");
            printf("[5] Matiere Note et Coef\n");
            printf("Votre choix : ");
            scanf("%d", &choix);
        }
        switch (choix) // cette partie va permetre a l utulisateur de modifier les parametre qu il souhaite
        {
            case 1:
                printf("Entrez le nouveau nom :\n ");
                scanf(" %s", etudiant_actuel->nom);
                printf("Nom modifie avec succes !\n");
                break;
            case 2:
                printf("Entrez le nouveau prenom :\n ");
                scanf(" %s", etudiant_actuel->prenom);
                printf("Prenom modifie avec succes !\n");
                break;
            case 3:
                printf("Entrez le nouveau numero de dossier :\n ");
                scanf(" %d", &etudiant_actuel->numero_dossier);
                printf("Numero de dossier modifie avec succes !\n");
                break;
            case 4:
                printf("Entrez le nouveau statut (1 pour Inscrit, 0 pour Non inscrit) :\n ");
                scanf(" %d", &etudiant_actuel->eta_inscription);
                printf("Statut d'inscription mis a jour !\n");
                break;
            case 5:
            if (etudiant_actuel->modules == NULL)
            {
                etudiant_actuel->modules = malloc(sizeof*(etudiant_actuel->modules));
                if (etudiant_actuel->modules == NULL)
                {
                    printf("Eureur de l allocation dynamique ");
                }
            }
            Note *etudiant_actuel_modules = NULL;
            Note *actuel = etudiant_actuel->modules;
            while (actuel->note_suivante != NULL)
            {
                actuel = actuel->note_suivante;
            }
            etudiant_actuel_modules = actuel;
            
            printf("Entrez la nouvelle matiere :\n");
            scanf("%s", matier);
            if (strcmp(etudiant_actuel_modules->matier, matier) == 0 )
            {
                printf("Entrez la nouvelle note :\n");
                scanf("%f", &etudiant_actuel_modules->valeur);
                printf("Entrez le nouveau coef:\n");
                scanf("%d", &etudiant_actuel_modules->coef);
                printf("La matiere ainsi que sa note et son coef on ete modifier avec succe !\n");
               
            }
            else
            {
                etudiant_actuel_modules->note_suivante = malloc(sizeof(Note));
                if (etudiant_actuel_modules->note_suivante == NULL) 
                {
                    printf("Erreur d allocation memoire \n");
                    break;
                }
                strcpy(etudiant_actuel_modules->note_suivante->matier,matier);
                printf("Donner la note de la nouvelle matier :\n");
                scanf("%f", &note);
                etudiant_actuel_modules->note_suivante->valeur = note;
                printf("Donner le coef de la nouvelle matier :\n");
                scanf("%d", &coef);
                etudiant_actuel_modules->note_suivante->coef = coef;
                etudiant_actuel_modules->note_suivante->note_suivante = NULL;
            }
            break;
        } 
    }    
}           
// fonction pour suprimer un etudiant de la liste
void suprimer_etudiant(Filiere *filiere)
{
    int votre_choix = 4;
    int id_supprimer;
    while (votre_choix == 4)
    {
        printf("Si vous vouler supprimer une autre etudiant tape 4 sinon 0:\n");
        scanf(" %d", &votre_choix);
        if (votre_choix == 0)
        {
            break;
        }
        
        if (filiere == NULL || filiere->premier_du_liste == NULL)
        {
            printf("Il n y a aucune etudiant ");
            return;
        }
        printf("Donner le numero de dossier de l etudiant que vous souhaiter suprimer de la filiere:\n");
        scanf(" %d", &id_supprimer);
        Etudiant *actuel_etudiant = filiere->premier_du_liste;
        Etudiant *precedent_etudiant = NULL;
        while (actuel_etudiant != NULL && id_supprimer != actuel_etudiant->numero_dossier)
        {
            precedent_etudiant = actuel_etudiant; // l etudiant precedent devient l actuel etudiant
            actuel_etudiant = actuel_etudiant->etudiant_suivant; // l actuel etudiant pas a l etudiant suivant
        }
        if (actuel_etudiant == NULL)
        {
            printf("Etudiant introuvable avec l id :%d\n",id_supprimer);
        }
        else
        {
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
                if (actuel_etudiant == filiere->dernier_du_liste) 
                {
                    filiere->dernier_du_liste = precedent_etudiant;
                }
            }
            free(actuel_etudiant); // liber l espace allouher a l etudiant suprimer
            filiere->nb_etudiants--;
            printf("L etudiant avec l id :%d a ete supprimer avec succe\n", id_supprimer);
        }
    }    
}
// fonction pour trouver le majorant de la filiere
void maximum(Filiere *filiere)
{
    if (filiere == NULL || filiere->premier_du_liste == NULL)
    {
        printf("Il n y a aucune etudiant ");
        return;
    }
    float majorant = 0.0;
    Etudiant *etudiant_major = filiere->premier_du_liste;
    Etudiant *le_major = NULL; // Pointeur pour memoriser le majorant
    while (etudiant_major != NULL)
    {
        if (etudiant_major->eta_inscription == 1 && etudiant_major->moyenne_general >= 0.0)
        {
            if (etudiant_major->moyenne_general > majorant)
            {
                majorant = etudiant_major->moyenne_general; // mise a jour du nouveaux majorant
                le_major = etudiant_major; // memorise l enplacement du majorant actuelle
            }
        }
        etudiant_major = etudiant_major->etudiant_suivant;
    }
    if (le_major != NULL)
    {
        printf("Le majorant de la filiere :%s, est %s, %s, numero de dossier : %d, et a une moyenne generale de :%.2f\n",filiere->nom_filiere, le_major->prenom, le_major->nom, le_major->numero_dossier, le_major->moyenne_general);
    }
}
// fonction pour trouver le minorant 
void minimum(Filiere *filiere)
{
    if (filiere == NULL || filiere->premier_du_liste == NULL)
    {
        printf("Il n y a aucune etudiant ");
        return;
    }
    float minorant = 20;
    Etudiant *etudiant_minor = filiere->premier_du_liste;
    Etudiant *le_minor = NULL; // Pointeur pour memoriser le minorant
    while (etudiant_minor != NULL)
    {
        if (etudiant_minor->eta_inscription == 1 && etudiant_minor->moyenne_general >= 0.0)
        {
            if (etudiant_minor->moyenne_general < minorant)
            {
                minorant = etudiant_minor->moyenne_general; // mise a jour du nouveaux minorant
                le_minor = etudiant_minor; // memorise l enplacement du minorant actuelle
            }
        }
        etudiant_minor = etudiant_minor->etudiant_suivant;
    }
    if (le_minor != NULL)
    {
        printf("L etudiant ayant la plus faible note de la filiere :%s, est %s, %s, numero de dossier : %d, et a une moyenne generale de :%.2f\n",filiere->nom_filiere, le_minor->prenom, le_minor->nom, le_minor->numero_dossier, le_minor->moyenne_general);
    }
}
// tri par ordre de merite (tri par selection)
void du_majorant_minorant(Filiere *filiere)
{
    if (filiere == NULL || filiere->premier_du_liste == NULL)
    {
        printf("Il n y a aucune etudiant ");
        return;
    }
    Etudiant *i = filiere->premier_du_liste;
    Etudiant *j;
    Etudiant *major_minor = NULL; // Pointeur pour memoriser le i
    // il nous faut des variable et une pointeur pour les echange fineaux
    char tmp_nom[50];
    char tmp_prenom[50];
    int tmp_id;
    int tmp_etat_inscription;
    float tmp_moyenne_general;
    Note *tmp_modules;
    while (i != NULL)
    {
        if (i->eta_inscription == 1)
        {
            major_minor = i; // on suppose que le plus grant est le i
            j = i->etudiant_suivant;
            while (j != NULL)
            {
                if (j->moyenne_general > major_minor->moyenne_general)
                {
                    major_minor = j; // j devient temporairement le plus grand
                }
                j = j->etudiant_suivant; // j passe a l etudiant suivant
            }
            if (major_minor != i)
            {
                strcpy(tmp_nom, i->nom);
                strcpy(tmp_prenom, i->prenom);
                tmp_id = i->numero_dossier;
                tmp_etat_inscription = i->eta_inscription;
                tmp_moyenne_general = i->moyenne_general;
                tmp_modules = i->modules;

                strcpy(i->nom, major_minor->nom);
                strcpy(i->prenom, major_minor->prenom);
                i->numero_dossier = major_minor->numero_dossier;
                i->eta_inscription = major_minor->eta_inscription;
                i->moyenne_general = major_minor->moyenne_general;
                i->modules = major_minor->modules;

                strcpy(major_minor->nom, tmp_nom);
                strcpy(major_minor->prenom, tmp_prenom);
                major_minor->numero_dossier = tmp_id;
                major_minor->eta_inscription = tmp_etat_inscription;
                major_minor->moyenne_general = tmp_moyenne_general;
                major_minor->modules = tmp_modules;
            } 
            i = i->etudiant_suivant;
        }   
    }
        
        
}    
// tri par ordre alphabetique (tri a bulle)
void orde_alphabet(Filiere *filiere)
{
    if (filiere == NULL || filiere->premier_du_liste == NULL)
    {
        printf("Il n y a aucune etudiant \n");
        return;
    }

    Etudiant *i = filiere->premier_du_liste;
    Etudiant *j;

    char tmp_nom[50];
    char tmp_prenom[50];
    int tmp_id;
    int tmp_etat_inscription;
    float tmp_moyenne_general;
    Note *tmp_modules;

    while (i != NULL)
    {
        if (i->eta_inscription == 1)
        {
            j = i->etudiant_suivant;
        
            while (j != NULL)
            {
                if (strcmp(i->nom, j->nom) > 0)
                {
                    strcpy(tmp_nom, i->nom);
                    strcpy(tmp_prenom, i->prenom);
                    tmp_id = i->numero_dossier;
                    tmp_etat_inscription = i->eta_inscription;
                    tmp_moyenne_general = i->moyenne_general;
                    tmp_modules = i->modules;

                    strcpy(i->nom, j->nom);
                    strcpy(i->prenom, j->prenom);
                    i->numero_dossier = j->numero_dossier;
                    i->eta_inscription = j->eta_inscription;
                    i->moyenne_general = j->moyenne_general;
                    i->modules = j->modules;

                    strcpy(j->nom, tmp_nom);
                    strcpy(j->prenom, tmp_prenom);
                    j->numero_dossier = tmp_id;
                    j->eta_inscription = tmp_etat_inscription;
                    j->moyenne_general = tmp_moyenne_general;
                    j->modules = tmp_modules;
                }
                j = j->etudiant_suivant; // j avance
            }
        
            i = i->etudiant_suivant; // i avance
        }
    }
        
        
}

