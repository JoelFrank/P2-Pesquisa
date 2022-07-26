#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef int TChave;
typedef struct {
  TChave Chave;
  /* outros compomentes */
}TItem;

typedef struct SNo * TArvBin;
typedef struct SNo {
  TItem Item;
  TArvBin Esq, Dir;
}TNo;

#define NIL NULL
typedef TArvBin TApontador;
typedef struct {
  TArvBin Raiz;
  int n;
}TDicionario;


void main(){
 
  clock_t inicio,fim;
  int max = 10;
  TDicionario *TDicionario_Inicia();
  TDicionario *Dicionario;
  Dicionario = TDicionario_Inicia();
  TItem x;

  int *vetor;
  vetor = (TChave*) malloc(max*sizeof(int));
  vetor[max]; 
  
  //=================COMECO PARA ALEATORIO==============================
  
  //números aleatorios sem repeticão
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
  //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);

  //=================FIM PARA ALEATORIO==============================  
   
}

/* Inicia um dicionario vazio */
TDicionario * TDicionario_Inicia() {
  TDicionario * D;
  D = (TDicionario * ) malloc(sizeof(TDicionario));
  D -> n = 0;
  D -> Raiz = NULL;
  return D;
}

/*TArvBin Pesquisa(TArvBin No, TChave c) {
  if (No == NULL)
    return NULL; // retorna NULL caso a chave nao seja encontrada
  else if (c < No -> Item.Chave)
    return Pesquisa(No -> Esq, c);
  else if (c > No -> Item.Chave)
    return Pesquisa(No -> Dir, c);
  else
    return No;
}*/

/*TArvBin Pesquisa(TArvBin Raiz, TChave c) {
  TArvBin No;
  No = Raiz;
  while ((No != NULL) && (c != No -> Item.Chave)) {
    if (c < No -> Item.Chave)
      No = No -> Esq;
    else if (c > No -> Item.Chave)
      No = No -> Dir;
  }
  return No;
}*/
//ARBOL-ESHOJA?//
//Devuelve 1 si es Hoja, 0 si no lo es
int esHoja(TArvBin raiz){
    if (!raiz->Dir && !raiz->Esq)
       return 1;
    else
        return 0; 
}
TArvBin buscar(TArvBin raiz, TChave c){
    if (raiz == NULL){
        return NULL;
    }else{
        if (c == raiz->Item.Chave){
            return raiz;
        }else{
            if (c < raiz->Item.Chave){
                return buscar (raiz->Esq, c);
            }else{
                return buscar (raiz->Dir, c);
            }
        }
    }
}

/*int Insere(TArvBin * pNo, TItem x) {
  if ( * pNo == NULL) {
    * pNo = (TArvBin) malloc(sizeof(TNo));
    ( * pNo) -> Item = x;
    ( * pNo) -> Esq = NULL;
    ( * pNo) -> Dir = NULL;
    return 1;
  } else if (x.Chave < ( * pNo) -> Item.Chave)
    return Insere( & ( * pNo) -> Esq, x);
  else if (x.Chave > ( * pNo) -> Item.Chave)
    return Insere( & ( * pNo) -> Dir, x);
  else
    return 0; // retorna 0 caso o item ja estiver na arvore
}*/

int Insere(TArvBin * pRaiz, TItem x) {
  TArvBin * pNo;
  pNo = pRaiz;
  while (( * pNo != NULL) && (x.Chave != ( * pNo) -> Item.Chave)) {
    if (x.Chave < ( * pNo) -> Item.Chave)
      pNo = & ( * pNo) -> Esq;
    else if (x.Chave > ( * pNo) -> Item.Chave)
      pNo = & ( * pNo) -> Dir;
  }
  if ( * pNo == NULL) {
    * pNo = (TArvBin) malloc(sizeof(TNo));
    ( * pNo) -> Item = x;
    ( * pNo) -> Esq = NULL;
    ( * pNo) -> Dir = NULL;
    return 1;
  }
  return 0; // retorna 0 caso o item ja estiver na arvore
}

/*int Retira(TArvBin * p, TChave c) {
  TArvBin q;
  if ( * p == NULL)
    return 0; // retorna 0 caso o item nao esteja na arvore
  else if (c < ( * p) -> Item.Chave)
    return Retira( & ( * p) -> Esq, c);
  else if (c > ( * p) -> Item.Chave)
    return Retira( & ( * p) -> Dir, c);
  else {
    q = * p;
    if (q -> Esq == NULL)
      *
      p = q -> Dir;
    else if (q -> Dir == NULL)
      *
      p = q -> Esq;
    else // possui dois filhos
      Sucessor( & q, & q -> Dir); // equivalente a Predecessor(&q, &q->Esq);
    free(q);
    return 1;
  }
}*/

int Retira(TArvBin * pRaiz, TChave c) {
  TArvBin * p, q;
  p = pRaiz;
  
  while (( * p != NULL) && (c != ( * p) -> Item.Chave)) {
    if (c < ( * p) -> Item.Chave)
      p = & ( * p) -> Esq;
    else  if (c > ( * p) -> Item.Chave)
      p = & ( * p) -> Dir;
  }
  if ( * p != NULL) {
    q = * p;
    if (q -> Esq == NULL)
      * p = q -> Dir;
    else if (q -> Dir == NULL)
      * p = q -> Esq;
    else // possui dois filhos
      Sucessor(&q, &q -> Dir); // equivalente a Predecessor(&q, &q->Esq);
    free(q);
    return 1;
  }
  return 0; // retorna 0 caso o item nao esteja na arvore
}

void Predecessor(TArvBin * q, TArvBin * r) {
  if (( * r) -> Dir != NULL)
    Predecessor(q, & ( * r) -> Dir);
  else {
    ( * q) -> Item = ( * r) -> Item;
    * q = * r;
    * r = ( * r) -> Esq;
  }
}
void Sucessor(TArvBin *q, TArvBin *r) {
  if ((*r) -> Esq != NULL)
    Sucessor(q, & ( *r) -> Esq);
  else {
    ( *q) -> Item = ( *r) -> Item;
    *q = *r;
    *r = (*r) -> Dir;
  }
}

/* Retorna um apontador para o item com chave c no dicionario */
TApontador TDicionario_Pesquisa(TDicionario * D, TChave c) {
  return buscar(D -> Raiz, c);
}
/* Insere um item no dicionario */
int TDicionario_Insere(TDicionario * D, TItem x) {
  if (!Insere( & D -> Raiz, x))
    return 0; // retorna 0 caso o item ja estiver no dicionario
  D -> n++; // n eh o tamanho
  return 1;
}
/* Retira o item com chave c do dicionario */
int TDicionario_Retira(TDicionario * D, TChave c) {
  if (!Retira( & D -> Raiz, c))
    return 0; // retorna 0 caso o item nao esteja no dicionario
  D -> n--;
  return 1;
}