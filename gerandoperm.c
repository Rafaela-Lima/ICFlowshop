#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int main(int argc, char const *argv[])
{
    int L, C;
    int flag;
    scanf("%d%d", &L, &C);

    int populacao[L][C];

    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < C; j++)
        {
            populacao[i][j] = -1;
        }
    }

    srand(time(NULL));
    for (int i = 0; i < L; i++)
    {
        while (1)
        {
            int randon = rand() % C;
            for (int j = 0; j < C; j++)
            {
                if (randon == populacao[i][j])
                {
                    flag = 0;
                    break;
                }
                else
                {
                    flasg = 1;
                }
            }
        }
        populacao[i][j] = randon;
    }
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < C; j++)
        {
            printf("%d\t", populacao[i][j]);
        }
        printf("\n");
    }

    return 0;
}
