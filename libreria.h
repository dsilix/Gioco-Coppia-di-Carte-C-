// Sviluppato da Silvio Saturno

#ifndef MAIN_C_LIBRERIA_H
#define MAIN_C_LIBRERIA_H
#endif //MAIN_C_LIBRERIA_H
#include <stdlib.h>
#include <time.h> // La usiamo per rand
#include <string.h>
#define NMAZZO 40
#define MAXNAME 25
#define COPERTO 0
#define SCOPERTO 1


//Creo un tipo "Seme" che mi servirà per la struct "carta" in quanto ho bisogno di associare un int(0...3) al seme
typedef enum{bastoni,coppe,denari,spade}Seme;
//LA STRUCT CARTA E' COMPOSTA DAL VALORE (1..10), DAL SEME E DALLO STATO (COPERTO/SCOPERTO)
typedef struct carta{
    int val;
    Seme seme;
    int stato;
}carta;

//SCEGLIE IL GIOCATORE INIZIALE
void playeriniziale(char *player1, char *player2) {
    printf("\n\tGIOCO DELLE COPPIE DI CARTE\n\n");
    //PRENDIAMO IN INPUT I NOMI DEI DUE GIOCATORI
    printf("Inserire il nome del primo giocatore (Max 14 caratteri): ");
    scanf("%s", player1);
    printf("Il nome del primo giocatore e' %s",player1);
    printf("\nInserire il nome del secondo giocatore (Max 14 caratteri): ");
    fflush(stdin);
    scanf("%s", player2);
    printf("Il nome del secondo giocatore e' %s",player2);

}

//CREA IL MAZZO, INIZIALMENTE E' ORDINATO
void creamazzo(carta *mazzo){
    int i, j, k = 0;
    int valori[10]={1,2,3,4,5,6,7,8,9,10};
    Seme semi[4] ={bastoni,coppe,denari,spade};
    while (k < NMAZZO) {
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 10; j++) {
                (mazzo+k)->seme = *(semi + i);
                (mazzo+k)->val = *(valori + j);
                (mazzo+k)->stato = COPERTO;
                k++;
            }
        }
    }
}

//MISCHIA IL MAZZO, COME SEED A srand() IMPOSTO time IN MODO DA OTTENERE DEI VALORI SEMPRE DIVERSI IN BASE ALL'ORA CORRENTE
void mischia(carta* mazzo){
    int numero_casuale = 0, numero_casuale2 = 0;
    int i,numscambi;
    carta temp = {0,0};
    srand(time(NULL));
    printf("\n\tQuante volte si desidera mischiare? ");
    scanf("%d",&numscambi);
    for(i=0;i<numscambi;i++){
        //GENERA GLI INDICI DELLE CARTE DA SCAMBIARE, CON QUESTO DO WHILE CREIAMO NUOVI INDICI NEL CASO FOSSERO IDENTICI
        do {
            numero_casuale = rand() % NMAZZO;
            numero_casuale2 = rand() % NMAZZO;
        } while(numero_casuale == numero_casuale2);
        temp = *(mazzo +numero_casuale);
        *(mazzo +numero_casuale) = *(mazzo +numero_casuale2);
        *(mazzo +numero_casuale2) = temp;

    }
}

//SCEGLIE CASUALMENTE UNO DEI DUE GIOCATORI
void scegligiocatore(char *player1, char *player2, int *segnaturno){
    int counter = 0;
    *segnaturno = rand() % 2;
    //QUESTO CICLO WHILE SERVE A DARE UN EFFETTO DI ATTESA NELLA SCELTA DEL GIOCATORE
    while (counter < 3) {
        printf("\nScelgo il giocatore che inizia");
        for (int i = 0; i < 4; i++) {
            _sleep(500);
            printf(".");
            counter++;
        }
        //IN BASE AL VALORE DEL SEGNATURNO VIENE SELEZIONATO IL GIOCATORE
        if (*segnaturno == 0){
            printf("\nInizia %s!", player1);
            _sleep(1000);}
        else{
            printf("\nInizia %s!", player2);
            _sleep(1000);}
    }
}

//STAMPA A SCHERMO IL MAZZO. SE LA CARTA E' COPERTA VERRA' STAMPATO '*', ALTRIMENTI STAMPA IL VALORE
void stampamazzo(carta *mazzo){
    int i;
    printf("\n\tMAZZO MISCHIATO");
    for (i = 0; i < 40; i++) {
        if (i % 10 == 0) {
            printf("\n\t");
        }
        if((mazzo+i)->stato==SCOPERTO)
            printf("%2d ", (mazzo + i)->val);
        else
            printf("*  ");
    }
}

//PROCEDURA PORTANTE DEL PROGRAMMA,
void gameplay(carta *mazzo,char *player1, char *player2) {
    //Sceglie il giocatore che inizia
    int segnaturno = 0;
    scegligiocatore(player1,player2,&segnaturno);         // ASSEGNA ALLA VARIABILE segnaturno 0 o 1 CASUALMENTE
    int contatorecarte = 0;                               // QUESTO CONTATORE CI SERVE PER TERMINARE IL CICLO IN CASO SI SCOPRANO 40 CARTE
    int punteggio1=0,punteggio2=0;
    while(contatorecarte<NMAZZO){
        while(segnaturno == 0) {                          //TURNO GIOCATORE 1
            if(contatorecarte==NMAZZO)
                break;
            stampamazzo(mazzo);
            printf("\nTurno di %s\n", player1);
            int carta1 = 0, carta2 = 0;
            do {
                do{
                    do {
                        carta1=0;
                        printf("Scegli una carta\n");
                        scanf("%d", &carta1);
                        carta1= carta1-1; //DECREMENTIAMO DI UNO LA SCELTA IN MODO CHE IL GIOCATORE SELEZIONA DA 1 A 40 (INVECE CHE DA 0 A 39)
                        while(carta1<0 || carta1>40){
                            printf("SCEGLI UNA CARTA TRA 1 E 40!\n");
                            scanf("%d", &carta1);
                            carta1= carta1-1;
                            break;
                            }

                        if ((mazzo + carta1)->stato == SCOPERTO)
                            printf("Carta gia scelta\n");
                    } while ((mazzo + carta1)->stato == SCOPERTO);

                } while(carta1<0 || carta1>40);
                do {
                    do {
                        carta2=0;
                        printf("Scegli una carta\n");
                        scanf("%d", &carta2);
                        carta2 -=1;
                        while(carta2<0 || carta2>40){
                            printf("SCEGLI UNA CARTA TRA 1 E 40!");
                            scanf("%d", &carta2);
                            carta2 -=1;
                            break;
                        }
                        if ((mazzo + carta2)->stato == SCOPERTO)
                            printf("Carta gia scelta\n");

                    } while ((mazzo + carta2)->stato == SCOPERTO);

                } while(carta2<0 || carta2>40);

                if (carta1 == carta2)
                    printf("NON PUOI SELEZIONARE DUE CARTE UGUALI\n");
            } while (carta1 == carta2);
            if ((mazzo + carta1)->val == (mazzo + carta2)->val) {
                (mazzo+carta1)->stato = SCOPERTO;
                (mazzo+carta2)->stato = SCOPERTO;
                punteggio1++;
                contatorecarte += 2;
                printf("PUNTO!\n Punteggio di %s: %d\n", player1, punteggio1);
            } else {
                segnaturno = 1;
                printf("SBAGLIATO!");
            }
        }

        while(segnaturno == 1){                            //TURNO GIOCATORE 2
            if(contatorecarte==NMAZZO)
                break;
            stampamazzo(mazzo);
            printf("\nTurno di %s\n", player2);
            int carta1=0, carta2=0;
            do {
                do {
                    do {
                        carta1=0;
                        printf("\nScegli una carta\n");
                        scanf("%d", &carta1);
                        carta1= carta1-1; //DECREMENTIAMO DI UNO LA SCELTA IN MODO CHE IL GIOCATORE SELEZIONA DA 1 A 40 (INVECE CHE DA 0 A 39)
                        while(carta1<0 || carta1>40){
                            printf("SCEGLI UNA CARTA TRA 1 E 40!\n");
                            scanf("%d", &carta1);
                            carta1= carta1-1;
                            break;
                        }
                        if ((mazzo + carta1)->stato == SCOPERTO)
                            printf("Carta gia scelta");
                    } while ((mazzo + carta1)->stato == SCOPERTO);

                } while(carta1<0 || carta1>40);

                do{
                    do {
                        carta2=0;
                        printf("\nScegli una carta\n");
                        scanf("%d", &carta2);
                        carta2 -=1;
                        while(carta2<0 || carta2>40){
                            printf("SCEGLI UNA CARTA TRA 1 E 40!");
                            scanf("%d", &carta2);
                            carta2 -=1;
                            break;
                        }
                        if ((mazzo + carta2)->stato == SCOPERTO)
                            printf("Carta gia scelta\n");

                    } while ((mazzo + carta2)->stato == SCOPERTO);

                } while (carta2<0 || carta2>40);
                if(carta1==carta2)
                    printf("NON PUOI SELEZIONARE DUE CARTE UGUALI\n");
            }while(carta1==carta2);

            if ((mazzo + carta1)->val == (mazzo + carta2)->val) {
                (mazzo+carta1)->stato = SCOPERTO;
                (mazzo+carta2)->stato = SCOPERTO;
                punteggio2++;
                contatorecarte += 2;
                printf("PUNTO!\nPunteggio di %s: %d\n", player2, punteggio2);
            } else {
                segnaturno = 0;
                printf("SBAGLIATO!");
            }
        }
    }
    if(punteggio1>punteggio2){
        printf("\nHA VINTO %s | totalizza %d punti\n\n", player1,punteggio1);
        printf("\nHA PERSO %s | totalizza %d punti\n", player2, punteggio2);
    }
    else if(punteggio1==punteggio2)
        printf("\nPATTA!");
    else {
        printf("\nHA VINTO %s, con un punteggio di: %d\n", player2, punteggio2);
        printf("\n%s totalizza %d punti\n", player1, punteggio1);
    }
    printf("\n\n\tgithub.com/dsilix\n");

}

