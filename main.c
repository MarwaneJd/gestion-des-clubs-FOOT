#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Joueur {
    char Nom[20];
    char Prenom[20];
    char date_naissance[20];
    char poste[20];
    int salaire;
    int valeur_marchande;
    int transfert;
    int annee;
} Joueur;

typedef struct Element {
    Joueur joueur;
    struct Element *suiv;
    struct Element *prec;
} Element;

typedef struct Liste {
    Element *Tete;
    Element *Fin;
    int Taille;
    char nom_club[20];
} Liste;

void afficher_joueur(Joueur j) {
    printf("Nom de joueur: %s\n", j.Nom);
    printf("Prenom de joueur: %s\n", j.Prenom);
    printf("Date de naissance de joueur: %s\n", j.date_naissance);
    printf("Poste de joueur: %s\n", j.poste);
    printf("Salaire de joueur: %d\n", j.salaire);
    printf("Valeur marchande de joueur: %d\n", j.valeur_marchande);
    printf("Transfert: %d\n", j.transfert);
}

void ajouter_debut(Liste *L) {
    if (L->Taille == 100) {
        printf("Liste des joueurs pleine\n");
        return;
    }

    Element *E = malloc(sizeof(Element));
    printf("Donner le nom de joueur: ");
    scanf("%s", E->joueur.Nom);
    printf("Donner le prenom de joueur: ");
    scanf("%s", E->joueur.Prenom);
    printf("Donner la date de naissance du joueur: ");
    scanf("%s", E->joueur.date_naissance);
    printf("Poste de joueur: ");
    scanf("%s", E->joueur.poste);
    printf("Saisir le salaire de joueur: ");
    scanf("%d", &E->joueur.salaire);
    printf("Saisir la valeur marchande du joueur: ");
    scanf("%d", &E->joueur.valeur_marchande);
    printf("Saisir la possibilite de transfert du joueur(0 ou 1): ");
    scanf("%d", &E->joueur.transfert);

    if (L->Tete == NULL) {
        L->Tete = L->Fin = E;
        E->suiv = E->prec = NULL;
    } else {
        E->suiv = L->Tete;
        E->prec = NULL;
        L->Tete->prec = E;
        L->Tete = E;
    }

    L->Taille++;
}

void afficher_LISTE(Liste L) {
    int i = 1;
    Element *tmp = L.Tete;
    if (tmp == NULL) {
        printf("Liste de joueurs vide\n");
    } else {
        while (tmp != NULL) {
            printf("\nJoueur %d\n", i);
            afficher_joueur(tmp->joueur);
            tmp = tmp->suiv;
            i++;
        }
    }
}

void supp_debut(Liste *L) {
    if (L->Taille == 1) {
        free(L->Tete);
        L->Tete = L->Fin = NULL;
    } else {
        L->Tete = L->Tete->suiv;
        free(L->Tete->prec);
        L->Tete->prec = NULL;
    }
    L->Taille--;
}

void supp_fin(Liste *L) {
    if (L->Taille == 1) {
        free(L->Tete);
        L->Tete = L->Fin = NULL;
    } else {
        L->Fin = L->Fin->prec;
        free(L->Fin->suiv);
        L->Fin->suiv = NULL;
    }
    L->Taille--;
}

void supp_milieu(Liste *L, int pos) {
    int cpt = 1;
    Element *tmp = L->Tete;
    if (pos > 1 && pos < L->Taille) {
        while (cpt != pos) {
            tmp = tmp->suiv;
            cpt++;
        }
        tmp->suiv->prec = tmp->prec;
        tmp->prec->suiv = tmp->suiv;
        free(tmp);
        L->Taille--;
    } else {
        printf("Position invalide\n");
    }
}

void supp_joueur(Liste *L) {
    char Nom[20];
    int cpt = 1;
    Element *tmp = L->Tete;
    if (tmp == NULL) {
        printf("Liste de joueurs vide\n");
    } else {
        printf("\nDonner le nom du joueur a supprimer: ");
        scanf("%s", Nom);
        while (tmp != NULL) {
            if (strcmp(Nom, tmp->joueur.Nom) == 0) {
                if (cpt == 1)
                    supp_debut(L);
                else if (cpt == L->Taille)
                    supp_fin(L);
                else
                    supp_milieu(L, cpt);
                break;
            }
            tmp = tmp->suiv;
            cpt++;
        }
    }
}

char *chercher_joueur(Liste L) {
    char Nom[20];
    Element *tmp = L.Tete;
    if (tmp == NULL) {
        printf("Liste de joueurs vide\n");
    } else {
        printf("\nDonner le nom du joueur a chercher: ");
        scanf("%s", Nom);
        while (tmp != NULL) {
            if (strcmp(Nom, tmp->joueur.Nom) == 0) {
                return tmp->joueur.salaire;
            }
            tmp = tmp->suiv;
        }
    }
    return NULL;
}

Joueur salaire_plus(Liste *L) {
    Element *ptr = L->Tete;
    while (ptr != NULL) {
        if (ptr->joueur.annee > 2) {
            ptr->joueur.salaire += ptr->joueur.salaire * 0.1;
            return ptr->joueur;
        }
        ptr = ptr->suiv;
    }
    // Add a default return statement here if necessary
}
//fonction du moyenne de salaire des joueurs
float calculer_moyenne_salaire(Liste L) {
    if (L.Tete == NULL) {
        printf("Liste de joueurs vide\n");
        return 0;
    }

    Element* tmp = L.Tete;
    int somme_salaires = 0;
    int nombre_joueurs = 0;

    while (tmp != NULL) {
        somme_salaires += tmp->joueur.salaire;
        nombre_joueurs++;
        tmp = tmp->suiv;
    }

    if (nombre_joueurs > 0) {
        float moyenne = (float)somme_salaires / nombre_joueurs;
        return moyenne;
    } else {
        printf("La liste de joueurs est vide.\n");
        return 0;
    }
}


    void afficher_joueurs_transfert(Liste L) {
    Element* tmp = L.Tete;
    int c = 0;

    printf("Joueurs en transfert:\n");
    while (tmp != NULL) {
        if (tmp->joueur.transfert) {
            printf("Joueur %d:\n", ++c);
            afficher_joueur(tmp->joueur);
            printf("\n");
        }
        tmp = tmp->suiv;
    }

    if (c == 0) {
        printf("Aucun joueur en transfert.\n");
    }
}
void traiter_transfert_joueurs(Liste* L) {
    char nom_joueur[20];
    int montant_transfert;

    printf("Nom du joueur : ");
    scanf("%s", nom_joueur);

    printf("Montant du transfert : ");
    scanf("%d", &montant_transfert);

    Element* tmp = L->Tete;
    while (tmp != NULL) {
        if (strcmp(nom_joueur, tmp->joueur.Nom) == 0) {
            tmp->joueur.transfert = 1; // Le joueur est en transfert
            tmp->joueur.valeur_marchande = montant_transfert;
            printf("Le transfert du joueur %s a ete traite avec succes.\n", nom_joueur);
            return;
        }
        tmp = tmp->suiv;
    }
}


int main() {
    Liste L;
    L.Tete = L.Fin = NULL;
    L.Taille = 0;

    int choix;
    do {
            system("cls");
        printf("// GESTION DE CLUB//\n\n");
        printf("1. Acheter un joueur\n");
        printf("2. Vendre un joueur\n");
        printf("3. Chercher un joueur\n");
        printf("4. Afficher liste des joueurs\n");
        printf("5. Moyenne des salaires\n");
        printf("6. disponibilite de transfert\n");
        printf("7. Quitter\n\n");
        printf("Donner votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouter_debut(&L);
                break;
            case 2:
                supp_joueur(&L);
                // Code pour vender un joueur
                break;
            case 3:
                chercher_joueur(L);
                // Code pour rechercher un joueur
                break;
            case 4:
                afficher_LISTE(L);
                break;
            case 5:
                calculer_moyenne_salaire(L);
                break;
            case 6:
                afficher_joueurs_transfert(L);
                break;
            case 7:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }

        printf("\n");
        system("pause");
    } while (choix != 7);

    return 0;
}
