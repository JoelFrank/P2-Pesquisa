#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define NIL - 1
typedef int TChave;
typedef struct {
  TChave Chave;
  /* outros compomentes */
}
TItem;
typedef int TApontador;
typedef struct {
  TItem * Item;
  int n, max;
}
TDicionario;

void main(){

  clock_t inicio,fim;
  int max = 100;
  TDicionario *TDicionario_Inicia();
  TDicionario *Dicionario;
  Dicionario = TDicionario_Inicia();
  TItem x;

  int *vetor;
  vetor = (TChave*) malloc(max*sizeof(int));
  vetor[max];
  
  //=================COMECO PARA ALEATORIO==============================
  
  /*//números aleatorios sem repeticão
  for (int i = 0; i < max; i++) {     // fill array
    vetor[i] = i;
    //printf("Inseriu chave: %d\n",vetor[i]);
  }
  //printf("=============================\n");
  for (int i = 0; i < max; i++) {    // shuffle array
      int temp = vetor[i];
      int randomIndex = rand()%max;
      vetor[i]           = vetor[randomIndex];
      vetor[randomIndex] = temp;
      x.Chave = vetor[randomIndex];
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
  
  
  //comeca em cualquer nro aleatorio de -n a n
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
  //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);

  
  //==========================FIM QUASE=============================
  //*************************************************************************************************
  //*************************************************************************************************
  //*************************************************************************************************
  /*//inicio=clock();
   for (int i = 0; i < max; i++) {
    TDicionario_Pesquisa(Dicionario,i);
   }
  //fim=clock();
  //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);  
  //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/

  
   /*//inicio=clock();
   for (int i = 0; i < max; i++) {
    TDicionario_Retira(Dicionario,i);
   }
   //fim=clock();
   //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);  
   //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/
  

}


/* Inicia um dicionario vazio */
TDicionario * TDicionario_Inicia() {
  TDicionario * D;
  D = (TDicionario * ) malloc(sizeof(TDicionario));
  D -> n = 0;
  D -> max = 10;
  D -> Item = (TItem * ) malloc(D -> max * sizeof(TItem));
  return D;
}

TApontador TDicionario_Binaria(TDicionario * D,
  TApontador esq, TApontador dir, TChave c) {
  TApontador meio;
  meio = (esq + dir) / 2;
  if (esq > dir)
    return NIL; // retorna -1 caso a chave nao seja encontrada
  else if (c > D -> Item[meio].Chave)
    return TDicionario_Binaria(D, meio + 1, dir, c);
  else if (c < D -> Item[meio].Chave)
    return TDicionario_Binaria(D, esq, meio - 1, c);
  else
    return meio;
}

/* Retorna um apontador para o item com chave c no dicionario */
/*TApontador TDicionario_Pesquisa(TDicionario * D, TChave c) {
  return TDicionario_Binaria(D, 0, D -> n - 1, c);
}*/

/* Retorna um apontador para o item com chave c no dicionario */
TApontador TDicionario_Pesquisa(TDicionario * D, TChave c) {
  TApontador meio, esq, dir;
  esq = 0;
  dir = D -> n - 1;
  while (esq <= dir) {
    meio = (esq + dir) / 2;
    if (c > D -> Item[meio].Chave)
      esq = meio + 1;
    else ;if (c < D -> Item[meio].Chave)
      dir = meio - 1;
    else
      return meio;
  }
  return NIL; // retorna -1 caso a chave nao seja encontrada
}


/* Insere um item no dicionario */
int TDicionario_Insere(TDicionario * D, TItem x) {
  TApontador i;
  if (TDicionario_Pesquisa(D, x.Chave) != NIL)
    return 0; // retorna 0 caso o item ja estiver no dicionario
  if (D -> n == D -> max) {
    D -> max *= 2;
    D -> Item = (TItem * ) realloc(D -> Item, D -> max * sizeof(TItem));
  }
  i = D -> n - 1;
  while ((i >= 0) && (x.Chave < D -> Item[i].Chave)) {
    D -> Item[i + 1] = D -> Item[i];
    i--;
  }
  D -> Item[i + 1] = x;
  D -> n++;
  return 1;
}

/* Retira o item com chave c do dicionario */
int TDicionario_Retira(TDicionario * D, TChave c) {
  TApontador i;
  i = TDicionario_Pesquisa(D, c);
  if (i == NIL)
    return 0; // retorna 0 caso o item nao esteja no dicionario
  while (i < D -> n - 1) {
    D -> Item[i] = D -> Item[i + 1];
    i++;
  }
  D -> n--;
  if (4 * D -> n == D -> max) {
    D -> max /= 2;
    D -> Item = (TItem * ) realloc(D -> Item, D -> max * sizeof(TItem));
  }
  return 1;
}
