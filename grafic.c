#include <stdio.h>
#include <ctype.h>
#include "sah.h"

void int_Board(char board[SIZE][SIZE])
{
    char alb[SIZE]={'t','c','n','q','k','n','c','t'};
    char negru[SIZE]={'T','C','N','Q','K','N','C','T'};
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            if(i==0) {
                board[i][j] = negru[j];
            } else if(i==1) {
                board[i][j] = 'P';
            } else if(i==6) {
                board[i][j] = 'p';
            } else if(i==7) {
                board[i][j] = alb[j];
            } else {
                if((i+j)%2 == 0)
                    board[i][j] = 'o';
                else
                    board[i][j] = '#';
            }   
        }
    }
}

void print_Board(char board[SIZE][SIZE])
{
    printf("\n    a  b  c  d  e  f  g  h\n");
    for(int i=0; i<SIZE; i++)
    {
        printf(" %d ", 8-i); 
        
        for(int j=0; j<SIZE; j++)
        {
            if ((i + j) % 2 == 0) {
                printf("\033[47m"); 
            } else {
                printf("\033[100m");
            }

            char p = board[i][j];
            if (este_gol(p)) {
                printf("   "); 
            } else {
                if (este_alb(p)) {
                    printf("\033[34m"); // Albastru
                } else {
                    printf("\033[31m"); // Rosu
                }
                char tip = tolower(p);
                switch(tip) {
                    case 'p': printf(" ♟ "); break;
                    case 't': printf(" ♜ "); break;
                    case 'c': printf(" ♞ "); break;
                    case 'n': printf(" ♝ "); break;
                    case 'q': printf(" ♛ "); break;
                    case 'k': printf(" ♚ "); break;
                }
            }
            printf("\033[0m");
        }
        
        printf(" %d\n", 8-i);
    }
    printf("    a  b  c  d  e  f  g  h\n\n");
}