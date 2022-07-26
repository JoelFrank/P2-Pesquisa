#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define Error(Str) FatalError(Str)
#define FatalError(Str) fprintf(stderr, "%s\n", Str), exit(1)


typedef int TItem;

//Parte Para .h
#ifndef _AATree_H_
#define _AATree_H_

struct SNo;
typedef struct SNo * Position;
typedef struct SNo * AATree;

extern Position NullNode;
#endif

Position NullNode = NULL; /* Precisa de mais inicialização */

struct SNo {
  TItem Element;
  AATree Left;
  AATree Right;
  int Level;
};

AATree Inicializa(void) {
  if (NullNode == NULL) {
    NullNode = malloc(sizeof(struct SNo));
    if (NullNode == NULL) {
      FatalError("Fora da memória!!");
    }
    NullNode -> Left = NullNode -> Right = NullNode;
    NullNode -> Level = 0;
  }
  return NullNode;
}

AATree Libera(AATree T) {
  if (T != NullNode) {
    Libera(T -> Left);
    Libera(T -> Right);
    free(T);
  }
  return NullNode;
}

Position Pesquisa(AATree T, TItem X) {
  if (T == NullNode) {
    return NullNode;
  }
  if (X < T -> Element) {
    return Pesquisa(T -> Left, X);
  } else if (X > T -> Element) {
    return Pesquisa(T -> Right, X);
  } else {
    return T;
  }
}

Position PesquisaMin(AATree T) {
  if (T == NullNode) {
    return NullNode;
  } else if (T -> Left == NullNode) {
    return T;
  } else {
    return PesquisaMin(T -> Left);
  }
}

Position PesquisaMax(AATree T) {
  if (T != NullNode) {
    while (T -> Right != NullNode) {
      T = T -> Right;
    }
  }
  return T;
}

/*
  * Esta funcao so pode ser chamada se K2 tiver um filho esquerdo.
  * Executa uma rotacao entre um noh (K2) e seu filho esquerdo.
  * Atualiza as alturas e retorne uma nova raiz.
  */
static Position Rotacao_Esquerda(Position K2) {
  Position K1;

  K1 = K2 -> Left;
  K2 -> Left = K1 -> Right;
  K1 -> Right = K2;

  return K1; /* New root */
}

/*
  * Esta funcao so pode ser chamada se K1 tiver um filho certo.
  * Execute uma rotacao entre um noh (K1) e seu filho direito.
  * Atualize as alturas e retorne uma nova raiz.
  */
static Position Rotacao_Dereita(Position K1) {
  Position K2;

  K2 = K1 -> Right;
  K1 -> Right = K2 -> Left;
  K2 -> Left = K1;

  return K2; /* New root */
}

/* Se o filho esquerdo de T estiver no mesmo nivel de T, executa uma rotação. */
AATree Skew(AATree T) {
  if (T -> Left -> Level == T -> Level) {
    T = Rotacao_Esquerda(T);
  }
  return T;
}

/* Se o neto mais a direita de T estiver no mesmo nivel, gira o filho a direita para cima. */
AATree Split(AATree T) {
  if (T -> Right -> Right -> Level == T -> Level) {
    T = Rotacao_Dereita(T);
    T -> Level++;
  }
  return T;
}

AATree Insere(AATree T, TItem Item) {
  if (T == NullNode) {
    /* Create and return a one-node tree */
    T = malloc(sizeof(struct SNo));
    if (T == NULL) {
      FatalError("Fora da memória!!");
    } else {
      T -> Element = Item;
      T -> Left = T -> Right = NullNode;
      T -> Level = 1;
    }
    
  } else if (Item < T -> Element) {
    T -> Left = Insere(T -> Left, Item);
  } else if (Item > T -> Element) {
    T -> Right = Insere(T -> Right, Item);
  }
/* Caso contrario e uma duplicata; fazer nada */

  T = Skew(T);
  T = Split(T);

  return T;
}

AATree Remove(AATree T, TItem Item) {
  static Position DeletePtr, LastPtr;
  if (T != NullNode) {
    /* Etapa 1: Pesquise na arvore, define LastPtr e DeletePtr. */
    LastPtr = T;
    if (Item < T -> Element) {
      T -> Left = Remove(T -> Left, Item);
    } else {
      DeletePtr = T;
      T -> Right = Remove(T -> Right, Item);
    }

    /* Passo 2: Se na parte inferior da arvore e o item estiver presente, removemos. */
    if (T == LastPtr) {
      if (DeletePtr != NullNode && Item == DeletePtr -> Element) {
        DeletePtr -> Element = T -> Element;
        DeletePtr = NullNode;
        T = T -> Right;
        free(LastPtr);
      }
    }

    /* Passo 3: Caso contrario, nao estamos no fundo; Reequilibrar. */
    else if (T -> Left -> Level < T -> Level - 1 || T -> Right -> Level < T -> Level - 1) {
      if (T -> Right -> Level > --T -> Level) {
        T -> Right -> Level = T -> Level;
      }
      T = Skew(T);
      T -> Right = Skew(T -> Right);
      T -> Right -> Right = Skew(T -> Right -> Right);
      T = Split(T);
      T -> Right = Split(T -> Right);
    }
  }

  return T;
}

TItem Recuperar(Position P) {
  return P -> Element;
}

#define NumItems 10

int main(){

    //printf("Inicializando AA Tree...\n");
    AATree T;
    Position P;
    int i;
    int max=100;
    clock_t inicio,fim;
    int *vetor;
    vetor = (int*) malloc(max*sizeof(int)); //memoria dinamica para gerar valores grandes

    T = Inicializa();
    T = Libera(NullNode);

     //números aleatorios sem repeticão
      for (int i = 0; i < max; i++) {     // fill array
        vetor[i] = i;
        //printf("Inseriu chave: %d\n",vetor[i]);
      }
      //printf("=========ALEATORIO=========\n");
      for (int i = 0; i < max; i++) {    // shuffle array
          int temp = vetor[i];
          int randomIndex = rand()%max;
          vetor[i]           = vetor[randomIndex];
          vetor[randomIndex] = temp;
      }

      //inicio=clock();
      for (int i = 0; i < max; i++) {    // print array    
          Insere(T, vetor[i]); 
          //printf("Inseriu chave: %d\n",x.Chave);      
      }
      //fim=clock();
      //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);     
      //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);

    /*//printf("=========ASCENDENTE=========\n");
    //inicio=clock();
      for (int i = 0; i < max; i++) {     // fill array
          vetor[i] = i;
          Insere(T, vetor[i]);
          //printf("Inseriu chave: %d\n",x.Chave);
        }
      //fim = clock();
      //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC); 
      //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/

    /*//printf("=========DESCENDENTE=========\n");
    //inicio=clock();
      int j = 0;
      for (int i = max-1; i >=0; i--) {     // fill array
          vetor[j] = i;
          Insere(T, vetor[j]);
          j++;
          
          //printf("Inseriu chave: %d\n",x.Chave);
        }
      //fim = clock();
      //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC); 
      //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/

    /*//printf("=========QUASE=========\n");
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
        Insere(T, vetor[i]);
        //printf("Inseriu chave: %d\n",vetor[i]);        
    }
    //fim=clock();
    //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);     
    //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/

    //============================PESQUISA=========================
    /*//printf("Empieza la pesquisa\n");
    inicio=clock();
    for (int i = 0; i < max; i++) {
        Pesquisa(T, vetor[i]);
    }
    //fim=clock();
    //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);  
    //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/
    

    //============================REMOCAO=========================
    //printf("Empieza la remocao\n");
    //inicio=clock();
    for (int i = 0; i < max; i++) {
        //printf("llave a eliminar: %d\n",i);
        Remove(T, i);
    }
    //fim=clock();
    
    //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);  
    //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);

  }

