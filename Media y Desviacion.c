#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int main(){
    int max,valor;    
    printf("Ingrese el tamano de n:");
    scanf("%d", &max);
    int *v;
    v = (int*) malloc(max*sizeof(int));
    v[max];
    int par = 0;
    for (int j = 1; j <= max; j++)
    {
        //printf("Ingrese valor del arreglo:");
        //scanf("%d", &valor);
        v[j] = par;
        par = par +2;

    }
    
   
    float media, desvio;
    calcular(v, max, &media, &desvio);
    printf("M:%f\nD:%f\n",media,desvio);
    //system("pause");
    return 0;
}

void calcular (int *vetor, int n, float  *m, float *dp){
    int i;
    *m=0.0;//para a media
    for (i = 1; i <= n; i++)
    {
        *m = *m + vetor[i];
    }
    *m = *m/n;
    *dp = 0.0;//para desvio padrao
    for (i = 1; i <= n; i++)
    {
        *dp = *dp + pow(vetor[i] - *m,2);
    }
    *dp = sqrt(*dp/(n-1));    
    
}