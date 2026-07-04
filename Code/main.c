#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h" // On lie tes structures d'étudiants et de notes !

int main()
{
    int votre_choix1 = 1;
    int votre_choix2 = 1;
    Etudiant *nouveau_etudiant = NULL;
    Filiere ma_filiere;
    ma_filiere.premier_du_liste = NULL;
    ma_filiere.dernier_du_liste = NULL;
    ma_filiere.nb_etudiants = 0;
    
    printf("======== BIENVENUE! =======\n");
    printf("Veuillez donner le nom de votre filiere:\n");
    scanf("%s", ma_filiere.nom_filiere);
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
    liste_de_la_classe(&ma_filiere);
    bulletin(&ma_filiere);
    recherche_et_modification_etudiant(&ma_filiere);
    suprimer_etudiant(&ma_filiere);
    printf("======== Bulletin apres modification! ========");
    bulletin(&ma_filiere);
    maximum(&ma_filiere);
    minimum(&ma_filiere);
    du_majorant_minorant(&ma_filiere);
    printf("-------- Classe triee par ordre de merite du meillieure au moins bon -------\n");
    liste_de_la_classe(&ma_filiere);
    orde_alphabet(&ma_filiere);
    printf("-------- Classe triee par ordre alphabetique --------\n");
    liste_de_la_classe(&ma_filiere);

    return 0;
}
