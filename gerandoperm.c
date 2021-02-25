#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#define NR_JOBS 20 //numero de trabalhos
#define NR_MACH 5  //numero de maquinas
#define TAM_POP 5

typedef struct individuo
{
    int job[NR_JOBS];
    int makespan;
} ind;

int leArquivo(int tempo[NR_MACH][NR_JOBS])
{
    FILE *arquivo = fopen("Nome.txt", "r"); // cria ou abre o arquivo
    if (arquivo == NULL)

    { // testa se o arquivo foi aberto com sucesso
        printf("\n\nImpossivel abrir o arquivo!\n\n");
        return 0;
    }
    int job, maq, s, u, b;

    //  while(arquivo != EOF) {
    while (getc(arquivo) != ':')
    {
        /* Adicionar caracter à string. */
    }
    fscanf(arquivo, "%d %d %d %d %d\n", &job, &maq, &s, &u, &b);

    while (getc(arquivo) != ':')
    {
        /* Adicionar caracter à string. */
    }
    printf("\n");

    for (maq = 0; maq < NR_MACH; maq++)
    {
        for (job = 0; job < NR_JOBS; job++)
        {
            int temp;
            fscanf(arquivo, "%d", &temp);
            tempo[maq][job] = temp;
        }
    }
    //   }
    fclose(arquivo);
    return 0;
}

void geraPop(ind pop[TAM_POP])
{
    int i, j, x, aux;
    for (i = 0; i < TAM_POP; i++)
    {
        for (j = 0; j < NR_JOBS; j++)
        {
            pop[i].job[j] = j + 1;
        }
    }

    for (i = 0; i < TAM_POP; i++)
    {
        for (j = 0; j < NR_JOBS; j++)
        {
            x = rand() % NR_JOBS;
            aux = pop[i].job[j];
            pop[i].job[j] = pop[i].job[x];
            pop[i].job[x] = aux;
        }
    }
}

int max(int v1, int v2)
{
    if (v1 > v2)
    {
        return v1;
    }
    else
    {
        return v2;
    }
}

void makespan(ind *solucao, int tempo[NR_MACH][NR_JOBS])
{
    int job;
    int fim_jobmaq[NR_MACH][NR_JOBS];
    int makespan = 0;
    //int perm[4] = {0, 1, 2, 3};

    for (int i = 0; i < NR_MACH; i++)
    {
        for (int j = 0; j < NR_JOBS; j++)
        {
            fim_jobmaq[i][j] = 0;
        }
    }

    for (int m = 0; m < NR_MACH; m++)
    {
        for (int j = 0; j < NR_JOBS; j++)
        {
            int job_maqant = m > 0 ? fim_jobmaq[m - 1][j] : 0;
            int maq_jobant = j > 0 ? fim_jobmaq[m][j - 1] : 0;
            fim_jobmaq[m][j] = max(job_maqant, maq_jobant) + tempo[m][solucao->job[j] - 1];
        }
    }

    for (int m = 0; m < NR_MACH; ++m)
    {
        for (int j = 0; j < NR_JOBS; ++j)
        {
            if (fim_jobmaq[m][j] > makespan)
            {
                makespan = fim_jobmaq[m][j];
            }
        }
    }
    solucao->makespan = makespan;
}

int torneio(ind pop[], int tam_POP, int size) //melhor solucao
{
    int cont = 0;
    int options[size];

    do
    {
        int i = rand() % tam_POP; //seleciona uma solucao aleatoria

        //verifica se já foi escolhida
        int isInList = 0;
        for (int j = 0; j < cont; j++)
        {
            if (options[j] == i)
            {
                isInList = 1;
                break;
            }
        }
        //adiciona na lista se nao foi escolhida
        if (isInList == 0)
        {
            printf("%d %d\n", i, pop[i].makespan);
            options[cont] = i;
            cont++;
        }
    } while (cont < size);

    int best = options[0]; //encontra indice a melhor solucao
    for (int i = 0; i < size; i++)
    {
        if (pop[options[i]].makespan <= pop[best].makespan)
        {
            best = options[i];
        }
    }

    printf("Melhor solucao: %d\n", pop[best].makespan);

    return best;
}

void mutacao(ind *solucao) //modificando os pais
{
    int i1, i2;
    // sorteia duas posições aleatorias e diferentes
    i1 = rand() % NR_JOBS;
    do
    {
        i2 = rand() % NR_JOBS;
    } while (i1 == i2);

    printf("Mutacao %d e %d\n", i1, i2);
    // troca os valores entre as posições
    int aux = solucao->job[i1];
    solucao->job[i1] = solucao->job[i2];
    solucao->job[i2] = aux;
}

int verifica_elemento(int *filho, int elemento) //verifica se existe elemento no vetor filho
{
    for (int i = 0; i < NR_JOBS; i++)
    {
        if (filho[i] == elemento)
        {
            return 1;
        }
    }
    return 0;
}

int crossover(ind *pai1, ind *pai2, int *filho) //one order crossover
{
    int i1, i2;

    for (int i = 0; i < NR_JOBS; i++)
    {
        filho[i] = -1;
    }

    // sorteia duas posições do pai1
    i1 = rand() % NR_JOBS;
    do
    {
        i2 = rand() % NR_JOBS;
    } while (i2 < i1);

    for (int j = i1; j <= i2; j++)
    {
        filho[j] = pai1->job[j];
    }

    //pai2
    int count = 0;
    for (int i = i2 + 1;; i++)
    {
        if (i == NR_JOBS)
        {
            i = 0;
        }
        if (i == i1)
        {
            break;
        }
        while (1)
        {
            if (verifica_elemento(filho, pai2->job[count]) == 0)
            {
                filho[i] = pai2->job[count];
                count++;
                break;
            }
            count++;
        }
    }
    printf("Intervalo pai 1: %d ate %d\nPai 1: ", i1, i2);
    for (int i = 0; i < NR_JOBS; i++)
    {
        printf("%d ", pai1->job[i]);
    }
    printf("\nPai 2: ");
    for (int i = 0; i < NR_JOBS; i++)
    {
        printf("%d ", pai2->job[i]);
    }
    printf("\nFilho: ");
    for (int i = 0; i < NR_JOBS; i++)
    {
        printf("%d ", filho[i]);
    }
}

int main(int argc, char const *argv[])
{
    ind pop[TAM_POP];
    ind melhorPop;
    melhorPop.makespan = -1;
    int i, j, k;
    int tempo[NR_MACH][NR_JOBS];
    leArquivo(tempo);
    srand(time(NULL));
    geraPop(pop);

    //laço principal AG
    for (int p = 0; p < 10; p++)
    {
        //calcula o makespan de toda a populacao, solucao por solucao
        for (i = 0; i < TAM_POP; i++)
        {
            makespan(&pop[i], tempo);
        }

        //imprime matriz tempos
        //printf("\nMatriz de tempos \n");
        for (i = 0; i < NR_MACH; i++) //iniciar permutacoes com zero;
        {
            for (j = 0; j < NR_JOBS; j++)
            {
                printf("%d ", tempo[i][j]);
            }
            printf("\n");
        }

        //imprime as permutacoes que compoem a populacao
        printf("\n Permutacoes \n");
        for (i = 0; i < TAM_POP; i++) //iniciar permutacoes com zero;
        {
            for (j = 0; j < NR_JOBS; j++)
            {
                printf("%d ", pop[i].job[j]);
            }
            printf("\n");
        }

        //exibe o makespan de cada solução
        for (i = 0; i < TAM_POP; i++)
        {
            printf("Makespan pop[%d] = %d \n", i, pop[i].makespan);
        }

        int pai1 = torneio(pop, TAM_POP, 2);
        int pai2 = torneio(pop, TAM_POP, 2);
        int tempFilho[NR_JOBS];
        crossover(&pop[pai1], &pop[pai2], tempFilho);

        ind filho;
        for (int i = 0; i < NR_JOBS; i++)
        {
            filho.job[i] = tempFilho[i];
        }
        printf("\n");
        mutacao(&filho);
        makespan(&filho, tempo);

        printf("Makespan do filho: %d \n", filho.makespan);
        printf("Makespan do pai1: %d \n", pop[pai1].makespan);
        printf("Makespan do pai2: %d \n", pop[pai2].makespan);
        printf("\n");

        if (pop[pai1].makespan > filho.makespan)
        {
            if (pop[pai2].makespan > filho.makespan)
            {
                if (pop[pai1].makespan > pop[pai2].makespan)
                {
                    pop[pai1] = filho;
                }
                else
                {
                    pop[pai2] = filho;
                }
            }
        }
        else if (pop[pai2].makespan > filho.makespan)
        {
            pop[pai2] = filho;
        }

        if (pop[pai1].makespan < pop[pai2].makespan)
        {
            if (melhorPop.makespan == -1)
            {
                melhorPop = pop[pai1];
            }
            else if (melhorPop.makespan > pop[pai1].makespan)
            {
                melhorPop = pop[pai1];
            }
        }
        else
        {
            if (melhorPop.makespan == -1)
            {
                melhorPop = pop[pai2];
            }
            else if (melhorPop.makespan > pop[pai2].makespan)
            {
                melhorPop = pop[pai2];
            }
        }
        printf("----------------------------- IT = %d -----------------------------\n ", p);
    }

    printf("\n melhor populacao entre: %d\n", melhorPop.makespan);
    for (int i = 0; i < NR_JOBS; i++)
    {
        printf("%d ", melhorPop.job[i]);
    }
}
