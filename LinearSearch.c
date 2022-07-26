#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define NIL - 1


typedef int TChave;
typedef struct {
  TChave Chave;
  /* outros compomentes */
}TItem;
typedef int TApontador;
typedef struct {
  TItem * Item;
  int n, max;
}TDicionario;

void main(){
  clock_t inicio,fim;
  TDicionario *TDicionario_Inicia();
  TDicionario *Dicionario;
  Dicionario = TDicionario_Inicia();
  TItem x;
  int max =100;
  int *vetor;
  vetor = (TChave*) malloc(max*sizeof(int));
  vetor[max];
  
  
        //=================COMECO PARA ALEATORIO==============================
      //números aleatorios sem repeticão

      for (int i = 0; i < max; i++) {     // fill array
        vetor[i] = i;
        //printf("Inseriu chave: %d\n",vetor[i]);
      }
      
      for (int i =0 ; i < max; i++) {    // shuffle array
          int temp = vetor[i];
          int randomIndex = rand()%max;
          vetor[i]           = vetor[randomIndex];
          vetor[randomIndex] = temp;
          x.Chave = vetor[randomIndex];
      }
      for (int i = 0; i < max; i++) {    // print array
          x.Chave = vetor[i];
          //inicio=clock();
          TDicionario_Insere(Dicionario, x);
          //fim=clock();
          //printf("%dInseriu chave: %d\n",i,x.Chave);
          //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);     
          //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);
      }
      //=================FIM PARA ALEATORIO==============================
        
  
  //=================COMECO ORDENADOS ASCEN==========================
  
  /*//inicio=clock();
  for (int i = 0; i < max; i++) {     // fill array
      vetor[i] = i;
      x.Chave = vetor[i];
      TDicionario_Insere(Dicionario, x);
      //printf("Inseriu chave: %d\n",x.Chave);
    }
  //fim = clock();
  //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC); 
  //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/

  //=================FIM ORDENADOS ASCEN=============================

  //=================COMECO ORDENADOS DESC==========================
  
  /*//inicio=clock();
  int j = 0;
  for (int i = max-1; i >=0; i--) {     // fill array
      vetor[j] = i;
      x.Chave = vetor[j];
      j++;
      TDicionario_Insere(Dicionario, x);
      //printf("Inseriu chave: %d\n",x.Chave);
    }
  //fim = clock();
  //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC); 
  //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/
  
  //=================FIM ORDENADOS DESC=============================
 
  //==========================COMECO QUASE==========================
  /*//comeca em cualquer nro aleatorio de -n a n
  int flag; //bandeira
  int v = 0;
  int aux;
  vetor[0]= v;
  for (int i = 0; i < max; i++) {
      flag = rand() % 2; //dois valores poder 0 ou 1      
      v++;
      if(flag==1){// se flag eh 1 o arranjo soma mais 1 (secuencialmente)
          vetor[i] = v;
      }else{// se flag eh 0 intercambio o anterior por o seguinte   
          vetor[i] = v;   
          aux = vetor[i];
          vetor[i] = vetor[i-1];
          vetor[i-1] = aux;
      }
    }

  //inicio=clock();
    for (int i = 0; i < max; i++) {    // print array
      x.Chave = vetor[i];     
      TDicionario_Insere(Dicionario, x);
      //printf("Inseriu chave: %d\n",x.Chave);
      
  }
  //fim=clock();
  //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);     
  //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/
  //==========================FIM QUASE=============================
  /*for (int max = 0; max < maxima; max++)
  {
    
        
  }*/
  //inicio=clock();
   for (int i = 0; i < max; i++) {
    TDicionario_Pesquisa(Dicionario,i);
   }
  //fim=clock();
  //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);  
  //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);
  

  
   /*//inicio=clock();
   for (int i = 0; i < max; i++) {
    TDicionario_Retira(Dicionario,i);
   }
   //fim=clock();
   //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);  
   //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/
      
   /*for (int  r = 1; r <= maxima; r++)
   {
      printf("El acumulador es: %d\n", acumulador[r]);
   }*/
}


/* Inicia um dicionario vazio */
TDicionario * TDicionario_Inicia() {
  TDicionario * D;
  D = (TDicionario * ) malloc(sizeof(TDicionario));
  D -> n = 0;
  D -> max = 10;// os n elementos
  D -> Item = (TItem * ) malloc(D -> max * sizeof(TItem));//memoria para o arranjo
  return D;
}

TApontador TDicionario_Pesquisa(TDicionario * D, TChave c) {
  TApontador i;
  for (i = 0; i < D -> n; i++)
    if (D -> Item[i].Chave == c)
      return i;   
  return NIL; // retorna -1 caso a chave não seja encontrada  
}

/* Insere um item no dicionario */
int TDicionario_Insere(TDicionario * D, TItem x) {
  if (TDicionario_Pesquisa(D, x.Chave) != NIL)
    return 0; // retorna 0 caso o item ja estiver no dicionario
  if (D -> n == D -> max) {
    D -> max *= 2;
    D -> Item = (TItem * ) realloc(D -> Item, D -> max * sizeof(TItem));
  }
  D -> Item[D -> n++] = x; // n eh o tamanho
  return 1;

}

/* Retira o item com chave c do dicionario */
int TDicionario_Retira(TDicionario * D, TChave c) {
  TApontador i;
  i = TDicionario_Pesquisa(D, c);
  if (i == NIL)
    return 0; // retorna 0 caso o item nao esteja no dicionario
  D -> Item[i] = D -> Item[--D -> n]; // n eh o tamanho
  if (4 * D -> n == D -> max) {
    D -> max /= 2;
    D -> Item = (TItem * ) realloc(D -> Item, D -> max * sizeof(TItem));
  }
  return 1;
}