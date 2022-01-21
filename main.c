// Sviluppato da Silvio Saturno

//Questo programma è un gioco di carte napoletane in cui lo scopo è quello di "scoprire" due carte uguali.
//Le carte vengono definite uguali quando il loro valore lo è (esempio: 10 BASTONI = 10 COPPE).
//Verrà chiesto a 2 giocatori di inserire il loro nome in input, inizierà... COMPLETARE
#include <stdio.h>
#include "libreria.h"

//PROTOTIPI
void mischia(carta*);                         //MISCHIA IL MAZZO DI CARTE
void creamazzo(carta*);                       //CREA IL MAZZO DI CARTE
void playeriniziale(char*,char*);             //PRENDE IN INPUT I NOMI DEI GIOCATORI
void gameplay(carta*, char*,char*);           //FASE DI GIOCO, TERMINA NEL MOMENTO IN CUI TUTTE LE CARTE SONO SCOPERTE
void scegligiocatore(char *, char * , int *); //SCEGLIE CASUALMENTE UNO DEI DUE GIOCATORI
void stampamazzo(carta*);                     //STAMPA A SCHERMO IL MAZZO DI CARTE

int main() {
    //DICHIARAZIONE VARIABILI

    carta mazzo[40];
    char player1[MAXNAME];                   //I DUE GIOCATORI SONO player1 e player2
    char player2[MAXNAME];
    creamazzo(mazzo);                        //CREO IL MAZZO
    playeriniziale(player1, player2);        //PRENDO IN INPUT I NOMI DEI GIOCATORI E NE SCELGO UNO CASUALMENTE
    mischia(mazzo);                          //MISCHIO IL MAZZO
    gameplay(mazzo, player1, player2);       //INIZIO IL GAMEPLAY
}

