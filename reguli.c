#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "sah.h"

int este_gol(char p) {
    return p=='o' || p=='#';
}

int este_alb(char p) {
    return p>='a' && p<='z' && p!='o';
}

int este_negru(char p) {
    return p>='A' && p<='Z';
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