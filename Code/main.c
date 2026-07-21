#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h" 
#include<time.h>

int main()
{

    Etudiant *inscrire_etudiants(Filiere *filiere);
    void note_etudiants(Etudiant *etudiant);
    void liste_de_la_classe(Filiere *filiere);
    void bulletin(Filiere *filiere);
    void recherche_et_modification_etudiant(Filiere *filiere);
    void suprimer_etudiant(Filiere *filiere);
    void maximum(Filiere *filiere);
    void minimum(Filiere *filiere);
    void du_majorant_minorant(Filiere *filiere);
    void orde_alphabet(Filiere *filiere);
     


    int votre_choix1 = 1;
    int votre_choix2 = 1;
    int votre_choix3;
    Etudiant *nouveau_etudiant = NULL;
    Filiere ma_filiere;

    ma_filiere.premier_du_liste = NULL;
    ma_filiere.dernier_du_liste = NULL;
    ma_filiere.nb_etudiants = 0;


    printf("\n=================================================================================================================\n");
    printf("\n                                     PLATEFORME DE GESTION DE SCOLARITE                                         \n ");
    printf("\n=================================================================================================================\n");


    printf("\n================================================== BIENVENUE! ===================================================\n");
    printf("Veuillez donner le nom de votre filiere:\n");
    scanf("%s", ma_filiere.nom_filiere);

    do
    {
        do
       {
            printf("\n================== Veullier faire votre choix en fonction de ce que vous souhaitez faire ========================\n");
            printf("[1] -----------------inscrire un ou plusieure etudiants et ajouter ou non leurs notes---------------------------- :\n");
            printf("[2] ------------------------------afficher la liste de la classe------------------------------------------------- :\n");
            printf("[3] ---------------------------------afficher leurs bulletins---------------------------------------------------- :\n");
            printf("[4] ----------rechercher et ou modifier les informations personnel ou accademique d'unetudiant------------------- :\n");
            printf("[5] -----------------------------suprimer un etudiant de la liste------------------------------------------------ :\n");
            printf("[6] ------------------------------------nouveaux bulletin-------------------------------------------------------- :\n");
            printf("[7] -----------------------------trouver le majorant de la filiere----------------------------------------------- :\n");
            printf("[8] ---------------------afficher l etudiant ayant la plus faible moyenne---------------------------------------- :\n");
            printf("[9] --------------------afficher la liste de la classe par ordre de merite--------------------------------------- :\n");
            printf("[10] -----------------afficher la listre de la filiere par ordre alphabetique------------------------------------ :\n");
            printf("[11] --Calculer le temps d executions pour les trie par selection et a bulle pour un nombre d etudiants donner--- :\n");
            printf("[12] -------------------------------pour arreter le programme---------------------------------------------------- :\n");
            scanf("%d", &votre_choix3);
        }while (votre_choix3 < 1 || votre_choix3 > 12);
        if (votre_choix3 == 12) 
        {
            printf("------------------------------------------- A BIENTOT! ---------------------------------------------------------- :\n");
            break;
        } 
        switch (votre_choix3)
        {
            case 1:
            votre_choix1 = 1;
            while (votre_choix1 != 0)
            {
                nouveau_etudiant = inscrire_etudiants(&ma_filiere);
                printf("Vouler vous ajouter ces note si oui tape (1) si non (0)\n");
                scanf("%d", &votre_choix2);
                if (votre_choix2 == 1)
                {
                    note_etudiants(nouveau_etudiant);
                }
                printf("Voulez vous inscrire un nouveaux etudiant si oui tape (1) si non (0)\n");
                scanf("%d", &votre_choix1);
            }
            break;
            case 2:
            liste_de_la_classe(&ma_filiere);
            break;
            case 3:
            bulletin(&ma_filiere);
            break;
            case 4:
            recherche_et_modification_etudiant(&ma_filiere);
            break;
            case 5:
            suprimer_etudiant(&ma_filiere);
            break;
            case 6:
            printf("---------------------------------- Bulletin apres modification! ------------------------------------------------ :\n");
            bulletin(&ma_filiere);
            break;
            case 7:
            maximum(&ma_filiere);
            break;
            case 8:
            minimum(&ma_filiere);
            break;
            case 9:
            du_majorant_minorant(&ma_filiere);
            printf("------------------- Classe triee par ordre de merite du meillieure au moins bon -------------------------------- :\n");
            liste_de_la_classe(&ma_filiere);
            break;
            case 10:
            orde_alphabet(&ma_filiere);
            printf("---------------------------------- Classe triee par ordre alphabetique ------------------------------------------- :\n");
            liste_de_la_classe(&ma_filiere);
            break;
            case 11:
            { 

                Filiere ma_filiere_temps;
                ma_filiere_temps.premier_du_liste = NULL;
                ma_filiere_temps.dernier_du_liste = NULL;
                ma_filiere_temps.nb_etudiants = 0;
                int n ;
                int i ;
                float temps_totale;
                clock_t temps_debut;
                clock_t temps_fin;

                float temps_totale2;
                clock_t temps_debut2;
                clock_t temps_fin2;

                do
                {
                    printf("Donner le nombre d etudiants :\n");
                    scanf("%d", &n);
                }while (n < 20);
    
                for ( i = 0; i < n; i++)
               {
                    Etudiant *nouveau_etudiant = (Etudiant*)malloc(sizeof(Etudiant));
                    strcpy(nouveau_etudiant->nom, "Diop");
                    strcpy(nouveau_etudiant->prenom, "Mohamed");
                    nouveau_etudiant->numero_dossier = i;

                    if (n / 20 != 0)
                    {
                        nouveau_etudiant->moyenne_general = (float)(n - i) / (n / 20.0);
                    } 
                    else
                    {
                        nouveau_etudiant->moyenne_general = 10.0;
                    }
        
                    nouveau_etudiant->etudiant_suivant = NULL;
                    if (ma_filiere_temps.premier_du_liste == NULL)
                    {
                        ma_filiere_temps.dernier_du_liste = nouveau_etudiant;
                        ma_filiere_temps.dernier_du_liste = nouveau_etudiant;
                    }
                    else
                    {
                        ma_filiere_temps.dernier_du_liste->etudiant_suivant = nouveau_etudiant;
                       ma_filiere_temps.dernier_du_liste = nouveau_etudiant;
                    }
                    ma_filiere_temps.nb_etudiants++;
        
                }

                temps_debut = clock();
                du_majorant_minorant(&ma_filiere_temps);
                temps_fin = clock();
                temps_totale = (float)(temps_fin - temps_debut)/CLOCKS_PER_SEC;
                Etudiant *courant = ma_filiere_temps.premier_du_liste;
                while (courant != NULL) 
                {
                    Etudiant *suivant = courant->etudiant_suivant;
                    free(courant);
                    courant = suivant;
                }

                // pour n = 100 ,nouveau_etudiant->moyenne_general = (n - i) / 5.0;le temps d execution est : 0.000000 seconde
                // pour n = 500 ,nouveau_etudiant->moyenne_general = (n - i) / 25.0;le temps d execution est : 0.000000 seconde 
                // pour n = 1000 ,nouveau_etudiant->moyenne_general = (n - i) / 50.0;le temps d execution est : 0.001000 seconde 
                // pour n = 1500 ,nouveau_etudiant->moyenne_general = (n - i) / 75.0;le temps d execution est : 0.004000 seconde 
                // pour n = 10000 ,nouveau_etudiant->moyenne_general = (n - i) / 500.0;le temps d execution est : 0.075000 seconde 
                // pour n = 15000 ,nouveau_etudiant->moyenne_general = (n - i) / 750.0;le temps d execution est : 0.344000 seconde  
                // pour n = 50000 ,nouveau_etudiant->moyenne_general = (n - i) / 2500.0;le temps d execution est : 2.977000 seconde 
                // pour n = 80000 ,nouveau_etudiant->moyenne_general = (n - i) / 4000.0;le temps d execution est : 8.488000 seconde
                // pour n = 100000 ,nouveau_etudiant->moyenne_general = (n - i) / 5000.0;le temps d execution est : 16.330000 seconde


                 
                ma_filiere_temps.premier_du_liste = NULL;
                ma_filiere_temps.dernier_du_liste = NULL;
                ma_filiere_temps.nb_etudiants = 0;
                for ( i = 0; i < n; i++)
                {
                    Etudiant *nouveau_etudiant = (Etudiant*)malloc(sizeof(Etudiant));
                    sprintf(nouveau_etudiant->nom, "Diop%d", n - i);
                    sprintf(nouveau_etudiant->prenom, "Mohamed%d", i);
                    nouveau_etudiant->numero_dossier = i;
                    nouveau_etudiant->moyenne_general = 12;
        
                    nouveau_etudiant->etudiant_suivant = NULL;
                    if (ma_filiere_temps.premier_du_liste == NULL)
                    {
                        ma_filiere_temps.premier_du_liste = nouveau_etudiant;
                        ma_filiere_temps.dernier_du_liste = nouveau_etudiant;
                    }
                    else
                    {
                        ma_filiere_temps.dernier_du_liste->etudiant_suivant = nouveau_etudiant;
                        ma_filiere_temps.dernier_du_liste = nouveau_etudiant;
                    }
                    ma_filiere_temps.nb_etudiants++;
        
                }
                temps_debut2 = clock();
                orde_alphabet(&ma_filiere_temps);
                temps_fin2 = clock();
                temps_totale2 = (float)(temps_fin2 - temps_debut2)/CLOCKS_PER_SEC;
      
                printf("pour : %d etudiants :\n", n);
                printf("le temps d execution du trie par selection est : %f seconde \n", temps_totale);
                printf("le temps d execution du trie a bulle est : %f seconde \n", temps_totale2);

                courant = ma_filiere_temps.premier_du_liste;
                while (courant != NULL) 
                {
                    Etudiant *suivant = courant->etudiant_suivant;
                    free(courant);
                    courant = suivant;
                }
    
                // pour n = 100 ,le temps d execution est : 0.000000 seconde 
                // pour n = 500 ,le temps d execution est : 0.003000 seconde 
                // pour n = 1000 ,le temps d execution est : 0.011000 seconde  
                // pour n = 1500 ,le temps d execution est : 0.017000 seconde 
                // pour n = 10000 ,le temps d execution est : 1.073000 seconde 
                // pour n = 15000 ,le temps d execution est : 1.577000 seconde 
                // pour n = 50000 ,le temps d execution est : 24.124001 seconde 
                // pour n = 80000 ,le temps d execution est : 71.599998 seconde 
                // pour n = 100000 ,le temps d execution est : 117.851997 seconde   
            }
            break;
            default:
            printf("Choix invalide! Aucune modification effectuee.\n");
            break;
    
            
        } 
    } while (votre_choix3 != 12);
    
    return 0;
} 


