#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
//calculo do makespan no calculo;
//uma permutação pode ser igual a outra;

int main(int argc, char const *argv[])
{
    int pop[10][4], i, j, k;
    bool foi = false;
    srand(time(NULL));

    for (i = 0; i < 10; i++) //linhas;
    {
        do // verificar se linhas são diferentes;
        {
            foi = false;
            for (j = 0; j < 4; j++) //colunas;
            {
                do //colunas diferentes;
                {
                    foi = false;
                    pop[i][j] = rand() % 4 + 1;
                    for (k = 0; k < j; k++)
                    {
                        if (pop[i][j] == pop[i][k])
                        {
                            foi = true;
                            break;
                        }
                    }
                } while (foi);
            }
            for (k = 0; k < i; k++)
            {
                if ((pop[i][0] == pop[k][0]) && (pop[i][1] == pop[k][1]) && (pop[i][2] == pop[k][2]) && (pop[i][3] == pop[k][3])) //deixar generico para N jobs;
                {
                    foi = true;
                    break;
                }
            }
        } while (foi);
    }
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("%d", pop[i][j]);
        }
        printf("\n");
    }
}
