#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define SIZE 8

int este_gol(char p) {
    return p=='o' || p=='#';
}

int este_alb(char p) {
    return p>='a' && p<='z' && p!='o';
}


int este_negru(char p) {
    return p>='A' && p<='Z';
}
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

int valoare_piesa(char p)
{
    char tip=tolower(p);
    if(tip=='p')
        return 1;
    if(tip=='c' || tip=='n')
        return 3;
    if(tip=='t')
        return 5;
    if(tip=='q')
        return 9;
    return 0;
}

int drum_liber(char board[SIZE][SIZE],int X1,int Y1,int X2,int Y2)
{
    int stepX,stepY;
    if(X2>X1)
        stepX=1;
    else
    {
        if(X2<X1)
            stepX=-1;
        else
            stepX=0;
    }
    if(Y2>Y1)
        stepY=1;
    else 
    {
        if(Y2<Y1)
            stepY=-1;
        else
            stepY=0;
    }
    int cX=X1+stepX;
    int cY=Y1+stepY;
    while(cX!=X2 || cY!=Y2)
    {
        if(!este_gol(board[cY][cX]))
            return 0;
        cX+=stepX;
        cY+=stepY;
    }
    return 1;
}

int mutare_valida(char board[SIZE][SIZE],int X1,int Y1,int X2,int Y2)
{
    char piesa=board[Y1][X1];
    char destinatie=board[Y2][X2];
    int dx=abs(X2-X1);
    int dy=abs(Y2-Y1);
    int mutare_legala=0;
    char tip_piesa=tolower(piesa);
    switch(tip_piesa)
    {
        case 'p':
            if (piesa=='p') { // Alb
                if(dx == 0 && este_gol(destinatie)) {
                    if(Y1-Y2==1) mutare_legala = 1;
                    if(Y1==6 && Y1-Y2 == 2 && este_gol(board[Y1-1][X1])) mutare_legala=1;
                } else if(dx==1 && Y1-Y2==1 && este_negru(destinatie)) mutare_legala=1;
            } else { // Negru
                if(dx==0 && este_gol(destinatie)) {
                    if(Y2-Y1==1) mutare_legala=1;
                    if(Y1==1 && Y2-Y1==2 && este_gol(board[Y1+1][X1])) mutare_legala=1;
                } else if(dx==1 && Y2-Y1==1 && este_alb(destinatie)) mutare_legala=1;
            }
            break;  
        case 't':
            if((dx==0 || dy==0) && drum_liber(board,X1,Y1,X2,Y2))
                mutare_legala=1;
            break;
        case 'n':
            if(dx==dy && drum_liber(board,X1,Y1,X2,Y2))
                mutare_legala=1;
            break;
        case 'q':
            if((dx==0 || dy==0 || dx==dy) && drum_liber(board,X1,Y1,X2,Y2)) 
                mutare_legala=1;
            break;
        case 'c':
            if((dx==1 && dy==2) || (dx==2 && dy==1))
                mutare_legala=1;
            break;
        case 'k':
            if((dx<=1 && dy<=1) && drum_liber(board,X1,Y1,X2,Y2))
                mutare_legala=1;
            break;
    }

    if(mutare_legala==0)
        return 0;
    else
        return 1;

}

int este_in_sah(char board[SIZE][SIZE] ,int alb)
{
    int regeX,regeY;
    char rege;
    if(alb==1)
        rege='k';
    else
        rege='K';
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            if(board[i][j]==rege)
            {
                regeY=i;
                regeX=j;
                break;
            }
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
        {
            char piesa=board[i][j];
            if(!este_gol(piesa))
                if((alb && este_negru(piesa)) || (!alb && este_alb(piesa)))
                    if(mutare_valida(board,j,i,regeX,regeY))
                        return 1;
        }
    return 0;
}

int promotion(char piesa, int Y2)
{
    if(este_alb(piesa) && piesa=='p')
        if(Y2==0)
            return 1;
    if(este_negru(piesa) && piesa=='P')
        if(Y2==SIZE-1)
            return 1;
    return 0;
}

int are_mutari_legale(char board[SIZE][SIZE], int alb)
{
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
        {
            char piesa=board[i][j];
            if((alb && este_alb(piesa)) || (!alb && este_negru(piesa)))
            {
                for(int y=0;y<SIZE;y++)
                    for(int x=0;x<SIZE;x++)
                    {
                        char destinatie=board[y][x];
                        if((este_alb(piesa) && este_alb(destinatie)) || (este_negru(piesa) && este_negru(destinatie)))
                            continue;
                        if(mutare_valida(board,j,i,x,y))
                        {
                            char piesa_stearsa=destinatie;
                            char patrat_plecare;
                            if((i+j)%2==0)
                                patrat_plecare='o';
                            else
                                patrat_plecare='#';
                            board[y][x]=piesa;
                            board[i][j]=patrat_plecare;

                            int still_sah=este_in_sah(board,alb);

                            board[i][j] = piesa;
                            board[y][x] = piesa_stearsa;
                            if(!still_sah)
                                return 1;
                        }
                    }
            }
        }
    return 0;
}

int miscare_piesa(char board[SIZE][SIZE],char cord_intX, int cord_intY,char cord_outX, int cord_outY, int turn, int *punctaj_alb, int *punctaj_negru)
{
    int X1=cord_intX-'a', X2=cord_outX-'a';
    int Y1=8-cord_intY,Y2=8-cord_outY;
    char piesa=board[Y1][X1];
    char destinatie=board[Y2][X2];
    if(este_gol(piesa) || (X1==X2 && Y1==Y2))
        return 0;
    if(turn%2==0 && este_negru(piesa))
    {
        return 0;
    }
    if(turn%2==1 && este_alb(piesa))
    {
        return 0;
    }
    if ((este_alb(piesa) && este_alb(destinatie)) || (este_negru(piesa) && este_negru(destinatie))) 
        return 0;

    if (mutare_valida(board,X1,Y1,X2,Y2)==0)
        return 0;
    
    char piesa_stearsa=destinatie;
    char patrat_plecare;
    if((X1+Y1)%2==0)
        patrat_plecare='o';
    else
        patrat_plecare='#';

    if(promotion(piesa,Y2))
    {
        if(este_alb(piesa))
            board[Y2][X2]='q';
        else
            board[Y2][X2]='Q';
    }
    else
        board[Y2][X2]=piesa;
    board[Y1][X1]=patrat_plecare;
    int suntem_alb;
    if(turn%2==0)
        suntem_alb=1;
    else
        suntem_alb=0;
    
    if(este_in_sah(board,suntem_alb))
    {
        board[Y1][X1]=piesa;
        board[Y2][X2]=piesa_stearsa;
        printf("\n----> MUTARE ILEGALA: REGELE TAU RAMANE IN SAH! <----\n");
        return 0;
    }

    if(!este_gol(destinatie))
    {
        if(este_alb(destinatie))
            *punctaj_negru+=valoare_piesa(destinatie);
        else
            *punctaj_alb+=valoare_piesa(destinatie);
    }
    return 1;
}

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