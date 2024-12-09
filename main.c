#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <unistd.h>
#define MAX_BUSES 50
#define MAX_RESERVATIONS 100

typedef struct {
    int idBus;
    char destination[50];
    int capacite;
    int placesReservees;
} Bus;

typedef struct {
    int idReservation;
    int idBus;
    char nomPassager[50];
    int numeroPlace;
} Reservation;

void creerBus(Bus b[], int *p);
void afficherBus(Bus b[], int bc);
void creerReservation(Reservation r[], int *rc, Bus b[], int *bc);
void afficherReservations(Reservation r[], int rc);
void modifierReservation(Reservation r[], int rc);
void sauvegarderBus(Bus b[], int bc);
void sauvegarderReservations(Reservation r[], int rc);
void chargerBus(Bus b[], int *bc);
void chargerReservations(Reservation r[], int *rc);
void clearScreen();
void headMessage();
void menu();

int main() {
    headMessage();
    return 0;
}
void menu() {
    Bus b[MAX_BUSES];
    Reservation r[MAX_RESERVATIONS];
    int bc = 0;
    int rc = 0;
    int choix;

    chargerBus(b, &bc);
    chargerReservations(r, &rc);

    do {
        clearScreen();
        printf("*************************************************\n");
        printf("*************  Application E-Bus  *************\n");
        printf("*************************************************\n");
        printf("1. Creer un nouveau bus\n");
        printf("2. Afficher les details du bus\n");
        printf("3. Creer une nouvelle reservation\n");
        printf("4. Afficher les details des reservations\n");
        printf("5. Modifier les details d'une reservation\n");
        printf("6. Quitter\n");
        printf("*************************************************\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                creerBus(b, &bc);
                sauvegarderBus(b, bc);
                break;
            case 2:
                afficherBus(b, bc);
                break;
            case 3:
                creerReservation(r, &rc, b, &bc);
                sauvegarderReservations(r, rc);
                sauvegarderBus(b, bc);
                break;
            case 4:
                afficherReservations(r, rc);
                break;
            case 5:
                modifierReservation(r, rc);
                sauvegarderReservations(r, rc);
                break;
            case 6:
                printf("\nAu revoir !\n");
                break;
            default:
                printf("Erreur : Choix invalide. Veuillez reessayer.\n");
                break;
        }
        if (choix != 6) {
            printf("\nAppuyez sur une touche pour revenir au menu principal...");
            getchar();
            getchar();
        }

    } while (choix != 6);
}
void headMessage()
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############                  Bienvenue dans E-BUS             ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    printf("                                  realise par Nader Ben Salah / Ahmed Laayouni                                 ");
    printf("\n\t\t\t----------------------------------------------------------------------------\n");
    #ifdef _WIN32
     Sleep(2500);
    #else
      usleep(2500000);
    #endif
    system("cls");
    fflush(stdin);
    menu();
}
void creerBus(Bus b[], int *p) {
    if (*p < MAX_BUSES) {
        clearScreen();
        printf("*************************************************\n");
        printf("******  Creation d'un nouveau bus  *************\n");
        printf("*************************************************\n");

        printf("Entrez l'ID du bus : ");
        scanf("%d", &b[*p].idBus);

        printf("Entrez la destination du bus : ");
        scanf("%s", b[*p].destination);

        printf("Entrez la capacite du bus : ");
        scanf("%d", &b[*p].capacite);

        b[*p].placesReservees = 0;
        (*p)++;

        printf("\nBus cree avec succes !\n");
    } else {
        printf("\nErreur : Nombre maximal de bus atteint.\n");
    }
}

void afficherBus(Bus b[], int bc) {
    clearScreen();
    printf("*************************************************\n");
    printf("**************  Details des Bus  ****************\n");
    printf("*************************************************\n");

    if (bc == 0) {
        printf("Aucun bus disponible.\n");
        return;
    }

    printf("%-10s %-20s %-10s %-15s\n", "ID Bus", "Destination", "Capacite", "Places reservees");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < bc; i++) {
        printf("%-10d %-20s %-10d %-15d\n", b[i].idBus, b[i].destination, b[i].capacite, b[i].placesReservees);
    }
}


void creerReservation(Reservation r[], int *rc, Bus b[], int *bc) {
    if (*rc < MAX_RESERVATIONS) {
        if (*bc == 0) {
            printf("\nErreur : Aucun bus disponible. Veuillez creer un bus d'abord.\n");
            return;
        }

        clearScreen();
        printf("*************************************************\n");
        printf("************  Creation d'une reservation  ******\n");
        printf("*************************************************\n");

        printf("Entrez le nom du passager : ");
        scanf("%s", r[*rc].nomPassager);

        printf("Entrez l'ID du bus pour la reservation : ");
        scanf("%d", &r[*rc].idBus);

        int busExiste = 0;
        int busIndex = -1;
        for (int i = 0; i < *bc; i++) {
            if (b[i].idBus == r[*rc].idBus) {
                busExiste = 1;
                busIndex = i;
                break;
            }
        }

        if (!busExiste) {
            printf("\nErreur : L'ID de bus %d n'existe pas.\n", r[*rc].idBus);
            return;
        }

        if (b[busIndex].placesReservees >= b[busIndex].capacite) {
            printf("\nErreur : Bus complet. Aucune place disponible.\n");
            return;
        }

        printf("Entrez le numero de place : ");
        scanf("%d", &r[*rc].numeroPlace);

        if (r[*rc].numeroPlace < 1 || r[*rc].numeroPlace > b[busIndex].capacite) {
            printf("\nErreur : Numero de place invalide.\n");
            return;
        }

        r[*rc].idReservation = *rc + 1;
        (*rc)++;
        b[busIndex].placesReservees++;
        printf("\nReservation creee avec succes !\n");

    } else {
        printf("\nErreur : Nombre maximal de reservations atteint.\n");
    }
}

void afficherReservations(Reservation r[], int rc) {
    clearScreen();
    printf("*************************************************\n");
    printf("**************  Details des Reservations  *******\n");
    printf("*************************************************\n");

    if (rc == 0) {
        printf("Aucune reservation disponible.\n");
        return;
    }

    printf("ID Reservation\tID Bus\tNom Passager\t\tNumero de Place\n");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < rc; i++) {
        printf("%d\t\t%d\t%-15s\t\t%d\n", r[i].idReservation, r[i].idBus,
               r[i].nomPassager, r[i].numeroPlace);
    }
}

void modifierReservation(Reservation r[], int rc) {
    if (rc == 0) {
        printf("\nErreur : Aucune reservation disponible.\n");
        return;
    }

    clearScreen();
    printf("*************************************************\n");
    printf("**********  Modification d'une reservation  *****\n");
    printf("*************************************************\n");

    int idRes;
    printf("Entrez l'ID de la reservation a modifier : ");
    scanf("%d", &idRes);

    int k = -1;
    for (int i = 0; i < rc; i++) {
        if (r[i].idReservation == idRes) {
            k = i;
            break;
        }
    }

    if (k == -1) {
        printf("\nErreur : Reservation non trouvee.\n");
    } else {
        printf("Entrez le nouveau numero de place : ");
        scanf("%d", &r[k].numeroPlace);
        printf("\nReservation modifiee avec succes !\n");
    }
}

void sauvegarderBus(Bus b[], int bc) {
    FILE *file = fopen("buses.txt", "w");
    for (int i = 0; i < bc; i++) {
        fprintf(file, "%d %s %d %d\n", b[i].idBus, b[i].destination, b[i].capacite, b[i].placesReservees);
    }
    fclose(file);
}

void sauvegarderReservations(Reservation r[], int rc) {
    FILE *file = fopen("reservations.txt", "w");
    for (int i = 0; i < rc; i++) {
        fprintf(file, "%d %d %s %d\n", r[i].idReservation, r[i].idBus, r[i].nomPassager, r[i].numeroPlace);
    }
    fclose(file);
}

void chargerBus(Bus b[], int *bc) {
    FILE *file = fopen("buses.txt", "r");
    if (file == NULL) return;

    while (fscanf(file, "%d %s %d %d", &b[*bc].idBus, b[*bc].destination, &b[*bc].capacite, &b[*bc].placesReservees) == 4) {
        (*bc)++;
    }
    fclose(file);
}

void chargerReservations(Reservation r[], int *rc) {
    FILE *file = fopen("reservations.txt", "r");
    if (file == NULL) return;

    while (fscanf(file, "%d %d %s %d", &r[*rc].idReservation, &r[*rc].idBus, r[*rc].nomPassager, &r[*rc].numeroPlace) == 4) {
        (*rc)++;
    }
    fclose(file);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
