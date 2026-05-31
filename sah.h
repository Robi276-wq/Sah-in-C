#ifndef SAH_H
#define SAH_H

#define SIZE 8


void int_Board(char board[SIZE][SIZE]);
void print_Board(char board[SIZE][SIZE]);
int este_gol(char p);
int este_alb(char p);
int este_negru(char p);
int valoare_piesa(char p);
int drum_liber(char board[SIZE][SIZE], int X1, int Y1, int X2, int Y2);
int mutare_valida(char board[SIZE][SIZE], int X1, int Y1, int X2, int Y2);
int este_in_sah(char board[SIZE][SIZE], int alb);
int promotion(char piesa, int Y2);
int are_mutari_legale(char board[SIZE][SIZE], int alb);
int miscare_piesa(char board[SIZE][SIZE], char cord_intX, int cord_intY, char cord_outX, int cord_outY, int turn, int *punctaj_alb, int *punctaj_negru);

#endif