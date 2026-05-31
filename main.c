#include <stdio.h>
#include <stdlib.h>
#include "sah.h"


int main()
{
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif
    char board[SIZE][SIZE];
    int r1,r2,turn=0,punctaj_alb=0,punctaj_negru=0;
    char c1,c2;
    int_Board(board);

    while(1)
    {
        int randul_albului;
        if(turn%2==0)
            randul_albului=1;
        else    
            randul_albului=0;
        int in_sah=este_in_sah(board,randul_albului);
        int are_mutari=are_mutari_legale(board,randul_albului);
        if(are_mutari==0)
        {
            print_Board(board);
            if (in_sah) {
                printf("\n=======================================================\n");
                printf("  SAH MAT! Jucatorul %s a castigat!\n", randul_albului ? "NEGRU" : "ALB");
                printf("=======================================================\n");
            } else {
                printf("\n=======================================================\n");
                printf("  REMIZA! (Pat). Jucatorul nu are mutari legale.\n");
                printf("=======================================================\n");
            }
            break;
        }
        if (in_sah) {
            printf("\n  [!] ATENTIE: REGELE TAU ESTE IN SAH! [!]\n");
        }
        printf("\n-----------------------------------\n");
        printf("SCOR->Alb: %d | Negru: %d\n", punctaj_alb, punctaj_negru);
        if (turn%2==0)
            printf("  ----> ESTE RANDUL ALBULUI <----\n");
        else
            printf("  ----> ESTE RANDUL NEGRULUI <----\n");
        printf("-----------------------------------\n");
        print_Board(board);
        printf("alege o piesa si dupa mut-o (ex: d2 d3):\n");
        if(scanf(" %c%d %c%d",&c1,&r1,&c2,&r2)!=4 || c1<'a' || c1>'h' || r1<1 || r1>8 || c2<'a' || c2>'h' || r2<1 || r2>8)
        {
            printf("---->COORDONATE INVALIDE. INCEARCA DIN NOU<----\n");
            int c;
            while((c=getchar())!='\n' && c!=EOF) {}
            continue;
        }
        if(miscare_piesa(board,c1,r1,c2,r2,turn,&punctaj_alb,&punctaj_negru)==0)
            printf("----> MISCARE ILEGALA <----\n");
        else
            turn++;
    }
    return 0;
}