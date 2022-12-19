#include <iostream>
#include <random>
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAM 100
#define STEPS 6000
#define INTERVAL 600
#define real double
#define EXPERIMENTS 100

using namespace std;

int main()
{
    printf("Número de experimentos: %d\n", EXPERIMENTS);
    typedef std::chrono::high_resolution_clock myclock;
    myclock::time_point beginning = myclock::now();

    std::default_random_engine generator;
    // obtain a seed from the timer
    myclock::duration d = myclock::now() - beginning;
    unsigned seed2 = d.count();
    generator.seed (seed2);
    std::uniform_real_distribution<real> distribution_1(0.95*1.25*(pow(10, -3)),1.05*1.25*(pow(10, -3)));
    std::uniform_real_distribution<real> distribution_0(0.95*5*(pow(10, -4)),1.05*5*(pow(10, -4)));

    int i, j, n, x, y, lessX, lessY, plusX, plusY, pele, k, swap = 0, **tecido, save = STEPS/INTERVAL;
    char str[40];
    real pb = 1000, Ta = 37, cb = 4200, *p, *c, *Q, A = 0.5*pow(10, 6), r0 = 3.1*pow(10, -3);
    real ***u, ****u_new, hx = 0.001, ht = 0.5, *wb, **Calor_nano, *kappa, kip, kim, kjp, kjm;
    // ht <= 2.25
    tecido = (int**)malloc(TAM*sizeof(int*));
    Q = (real*)malloc(2*sizeof(real));
    Calor_nano = (real**)malloc(TAM*sizeof(real*));
    p = (real*)malloc(2*sizeof(real));
    u = (real***)malloc(2*sizeof(real**));
    u_new = (real****)malloc(EXPERIMENTS*sizeof(real***));
    c = (real*)malloc(2*sizeof(real));
    wb = (real*)malloc(2*sizeof(real));
    kappa = (real*)malloc(2*sizeof(real));
    for (i = 0; i < TAM; i++)
    {
        tecido[i] = (int*)malloc(TAM*sizeof(int));
        Calor_nano[i] = (real*)malloc(TAM*sizeof(real));
    }
    for (i = 0; i < 2; i++)
    {
        u[i] = (real**)malloc(TAM*sizeof(real*));
    }
    for (i = 0; i < EXPERIMENTS; i++)
    {
        u_new[i] = (real***)malloc(save*sizeof(real**));
    }
    for (i = 0; i < EXPERIMENTS; i++)
    {
        for (j = 0; j < save; j++)
        {
            u_new[i][j] = (real**)malloc(TAM*sizeof(real*));
        }
    }
    for (i = 0; i < EXPERIMENTS; i++)
    {
        for (j = 0; j < save; j++)
        {
            for (k = 0; k < TAM; k++)
                u_new[i][j][k] = (real*)malloc(TAM*sizeof(real));
        }
    }
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < TAM; j++)
        {
            u[i][j] = (real*)malloc(TAM*sizeof(real));
        }
    }
    //definindo as constantes
    p[0] = 1000;
    c[0] = 4200;
    Q[0] = 4200;
    kappa[0] = 0.5;
    p[1] = 1200;
    c[1] = 3600;
    Q[1] = 420;
    kappa[1] = 0.55;

    for (i = 0; i < TAM; i++)
    {
        for (j = 0; j < TAM; j++)
        {
            u[swap][i][j] = Ta;
            Calor_nano[i][j] = A*exp(-(pow((i*hx - 0.05), 2) + pow((j*hx - 0.05), 2))/pow(r0, 2));
            tecido[i][j] = ((i*hx >= 0.04 + hx/2 && i*hx <= 0.06 + hx/2) && (j*hx >= 0.04 + hx/2 && j*hx <= 0.06 + hx/2)) ? 1 : 0;
        }
    }
    for (n = 0; n < EXPERIMENTS; n++)
    {
        swap = 0;
        // Restarting the initial matrix
        {
            for (i = 0; i < TAM; i++)
            {
                for (j = 0; j < TAM; j++)
                {
                    u[swap][i][j] = Ta;
                    u[!swap][i][j] = Ta;
                }
            }
            wb[0] = distribution_0(generator);
            wb[1] = distribution_1(generator);

        }

        for (k = 0; k < STEPS; k++)
        {
          for (i = 0; i < TAM; i++)
          {
              for (j = 0; j < TAM; j++)
              {
                pele = tecido[i][j];
                x = i;
                y = j;

                lessX = (x == 0)         ? x : x - 1;
                plusX = (x == (TAM - 1)) ? x : x + 1;

                kim = (x == 0)         ?  kappa[pele] : 2*kappa[tecido[lessX][y]]*kappa[pele]/(kappa[tecido[lessX][y]] + kappa[pele]);
                kip = (x == (TAM - 1)) ?  kappa[pele] : 2*kappa[tecido[plusX][y]]*kappa[pele]/(kappa[tecido[plusX][y]] + kappa[pele]);

                lessY = (y == 0)         ?  y : y - 1;
                plusY = (y == (TAM - 1)) ?  y : y + 1;

                kjm = (y == 0)         ? kappa[pele] : 2*kappa[tecido[x][lessY]]*kappa[pele]/(kappa[tecido[x][lessY]] + kappa[pele]);
                kjp = (y == (TAM - 1)) ? kappa[pele] : 2*kappa[tecido[x][plusY]]*kappa[pele]/(kappa[pele] + kappa[tecido[x][plusY]]);

                u[!swap][x][y] = (ht/(p[pele]*c[pele]))*(
                      (kip*u[swap][plusX][j] + kjp*u[swap][x][plusY] - (kip+kim+kjp+kjm)*u[swap][i][j] + kim*u[swap][lessX][j] + kjm*u[swap][x][lessY])/(pow(hx, 2))
                      + wb[pele]*pb*cb*(Ta - u[swap][i][j]) + Q[pele] + Calor_nano[i][j]) + u[swap][i][j];
              }
          }

            if (k % INTERVAL == 0)
                for (i = 0; i < TAM; i++)
                    for (j = 0; j < TAM; j++)
                        u_new[n][k/INTERVAL][i][j] = u[swap][i][j];

          swap = !swap;
        }
    }
    real ***mean, aux, ***sdv;
    mean = (real***)malloc(save*sizeof(real**));
    sdv = (real***)malloc(save*sizeof(real**));
    for (i = 0; i < save; i++)
    {
        mean[i] = (real**)malloc(TAM*sizeof(real*));
        sdv[i] = (real**)malloc(TAM*sizeof(real*));
    }
    for ( i = 0; i < save; i++)
        for (j = 0; j < TAM; j++)
            {
                mean[i][j] = (real*)malloc(TAM*sizeof(real));
                sdv[i][j] = (real*)malloc(TAM*sizeof(real));
            }
    for (k = 0; k < save; k++)
    {
        for (i = 0; i < TAM; i++)
        {
            for (j = 0; j < TAM; j++)
            {
                aux = 0;
                for (n = 0; n < EXPERIMENTS; n++)
                    aux += u_new[n][k][i][j];

                aux = aux/EXPERIMENTS;
                mean[k][i][j] = aux;
            }

        }
    }
    for (k = 0; k < save; k++)
    {
        for (i = 0; i < TAM; i++)
        {
            for (j = 0; j < TAM; j++)
            {
                aux = 0;
                for (n = 0; n < EXPERIMENTS; n++)
                    aux += pow((u_new[n][k][i][j] - mean[k][i][j]), 2);

                aux = sqrt(aux/EXPERIMENTS);
                sdv[k][i][j] = aux;
            }
        }
    }
    for (k = 0; k < save; k++)
    {
        sprintf(str, "hipertermia_heterogeneo_np_%d.txt", k+1);
        FILE *saida = fopen(str, "w");
        for (i = 0; i < TAM; i++)
        {
            for (j = 0; j < TAM; j++)
            {
                fprintf(saida, "%lf ", mean[k][i][j]);
            }
            fprintf(saida, "\n");
        }
        fclose(saida);
    }
    for (k = 0; k < save; k++)
    {
        sprintf(str, "hipertermia_sdv_%d.txt", k+1);
        FILE *saida = fopen(str, "w");
        for (i = 0; i < TAM; i++)
        {
            for (j = 0; j < TAM; j++)
            {
                fprintf(saida, "%lf ", sdv[k][i][j]);
            }
            fprintf(saida, "\n");
        }
        fclose(saida);
    }
    for (i = 0; i < TAM; i++)
    {
        free(Calor_nano[i]);
        free(tecido[i]);
    }
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < TAM; j++)
            free(u[i][j]);
        free(u[i]);
    }
    for (i = 0; i < EXPERIMENTS; i++)
    {
        for (j = 0; j < save; j++)
        {
            for (k = 0; k < TAM; k++)
                free(u_new[i][j][k]);
            free(u_new[i][j]);
        }
        free(u_new[i]);
    }
    for (i = 0; i < save; i++)
    {
        for (j = 0; j < TAM; j++)
        {
            free(mean[i][j]);
            free(sdv[i][j]);
        }
        free(mean[i]);
        free(sdv[i]);
    }
    free(mean);
    free(sdv);
    free(tecido);
    free(Q);
    free(p);
    free(u);
    free(u_new);
    free(c);
    free(wb);
    free(Calor_nano);
    free(kappa);
    printf("Programa executado com sucesso.\n");
    return 0;
}

