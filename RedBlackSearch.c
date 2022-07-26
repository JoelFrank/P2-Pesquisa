#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int TChave;

typedef struct {
	TChave Chave;
	/* outros compomentes */
} TItem;

typedef struct SNo *TArvBin;

typedef struct SNo {
	TItem Item;
	TArvBin Esq, Dir;
	int cor; //1 - rubro ; 0 - negro
} TNo;

//Calcula a altura Negra de uma arvore qualquer
int AlturaNegra(TArvBin No)
{
    int esq, dir;
    if(No == NULL)
        return(0);
    else {
        esq = AlturaNegra(No->Esq); //Conta a altura negra da esquerda
        dir = AlturaNegra(No->Dir); //Conta a altura negra da direita
    }

    if(esq > dir)
        return(EhNegro(No)+esq); //Retorna somente o numero de nos negros
    else
        return(EhNegro(No)+dir);
}

int EhNegro(TArvBin No)
{
return (No == NULL) || (No->cor == 0);
}
int EhRubro(TArvBin No)
{
return (No != NULL) && (No->cor == 1);
}

//Verifica se uma arvore eh Rubro Negra
int ArvoreARN(TArvBin No)
{
    if(No == NULL || (ArvoreARN(No->Esq) && ArvoreARN(No->Dir))) //Se o noh e NULL e se Dir e Esq sao ARN, a arvore eh ARN
        return(1);

    //Se a Altura Negra da direita e da esquerda sao diferentes ou se existem duplos rubros, a arvore noho eh ARN
    if(AlturaNegra(No->Dir) != AlturaNegra(No->Esq) || (EhRubro(No) && (EhRubro(No->Esq) || EhRubro(No->Dir))))
        return(0);

}
//inverte as cores de um noh
void TrocaCores(TArvBin No)
{
    if(No != NULL) {
    if(EhNegro(No)) //Se o noh eh negro, ele passa a ser rubro
        (No)->cor = 1;
    else if(EhRubro(No)) //Se o noh eh rubro, ele passa a ser negro
        (No)->cor = 0;
    }
}

void RotacaoDireita(TArvBin *pA)
{
	TArvBin pB = (*pA)->Esq;
	(*pA)->Esq = pB->Dir;
    pB->Dir = (*pA);
    (*pA) = pB;
}

void RotacaoEsquerda(TArvBin *pA)
{
    TArvBin pB = (*pA)->Dir;
	(*pA)->Dir = pB->Esq;
    pB->Esq = (*pA);
    (*pA) = pB;
}


void BalancaNo(TArvBin *Avo, TArvBin *Pai, TArvBin *Filho)
{
    TArvBin Tio; //Declarando e definindo o tio
    //Verificando se eh necessehrio rebalancear a arvore
    if(EhRubro(*Pai) && EhRubro(*Filho) && (Avo) != NULL) {

        //Definindo quem eh o tio
        if((*Avo)->Esq == (*Pai))
            Tio = (*Avo)->Dir;
        else if((*Avo)->Dir == (*Pai))
            Tio = (*Avo)->Esq;

        //Caso 01 - Tio eh rubro - basta colorir todos os envolvidos
        if(EhRubro(Tio)){
            TrocaCores(*Pai);
            TrocaCores(Tio);
            TrocaCores(*Avo);
        }
        //Caso 02 - Tio eh  negro
         else if(EhNegro(Tio)) {

            if((*Avo)->Dir == (*Pai)){
                if((*Pai)->Esq == (*Filho)) //Subcaso 02 - Pai e filho de lados opostos, faeho uma rotaeheho para cair no subcaso 03
                    RotacaoDireita(Pai);
                TrocaCores(*Avo); //Subcaso 02 - Troca cores e faz uma rotaeheho no aveh
                TrocaCores(*Pai);
                RotacaoEsquerda(Avo);

            }
            //Os mesmos casos se repetem de maneira simehtrica
            else if((*Avo)->Esq == (*Pai)){
                if((*Pai)->Dir == (*Filho))
                    RotacaoEsquerda(Pai);
                TrocaCores(*Avo);
                TrocaCores(*Pai);
                RotacaoDireita(Avo);
            }
        }
    }
 }


TArvBin Inicializa()
{
	return NULL;
}
//Funoheho que insere um noh
int InsereRec(TArvBin *Pai, TArvBin *Avo, TItem x) {

    if (*Pai == NULL) { //Caso a pesquisa seja sem sucesso inserimos utilizando a alocaeheho
        TNo* No = (TNo*) malloc (sizeof(TNo));
        No->cor = 1;
        No->Item = x;
        No->Esq = NULL;
        No->Dir = NULL;
        *Pai = No;
        return(1);
    }
    //Caso contrehrio percorremos a arvore
     else {
        if (x.Chave > (*Pai)->Item.Chave) {
                InsereRec(&(*Pai)->Dir, Pai, x);
                BalancaNo(Avo, Pai, &(*Pai)->Dir); //Toda vez que um noh eh inserido, verificamos se eh preciso balancear
        }
        else if (x.Chave < (*Pai)->Item.Chave) {
                InsereRec(&(*Pai)->Esq, Pai, x);
                BalancaNo(Avo, Pai, &(*Pai)->Esq);
        }
        else if (x.Chave == (*Pai)->Item.Chave)
            return(0);
    }

}

void Insere(TArvBin *pRaiz, TItem x)
{
	InsereRec(pRaiz, NULL, x);
	if((*pRaiz)!=NULL)
        (*pRaiz)->cor = 0;
}

void Carrega(TArvBin *pNo)
{
	int i, n;
	TItem x;

	scanf("%d", &n);
	for (i = 0; i < n ; i++) {
		scanf("%d", &x.Chave);
		Insere(pNo, x);
	}
}

void Libera(TArvBin *pNo)
{
	TArvBin No;

	No = *pNo;
	if (No != NULL) {
		Libera(&No->Esq);
		Libera(&No->Dir);
		free(No);
		(*pNo) = NULL;
	}
}

void Imprime(TArvBin No)
{
	if (No != NULL) {
		if (EhNegro(No))
			printf("(N%d", No->Item.Chave);
		else
			printf("(R%d", No->Item.Chave);
		Imprime(No->Esq);
		Imprime(No->Dir);
		printf(")");
	}
	else
		printf("()");
}
TArvBin Pesquisa(TArvBin No, TChave x)
{
	if (No == NULL)
		return NULL; // retorna NULL caso a chave nao seja encontrada
	else if (x < No->Item.Chave)
		return Pesquisa(No->Esq, x);
	else if (x > No->Item.Chave)
		return Pesquisa(No->Dir, x);
	else
		return No;
}


//====================================================
//=====================PARA REMOVER===================
//====================================================

/*
void Libera(TArvBin *pNo)
{
	TArvBin No;

	No = *pNo;
	if (No != NULL) {
		Libera(&No->Esq);
		Libera(&No->Dir);
		free(No);
		(*pNo) = NULL;
	}
}*/
void Remove(TArvBin * pRaiz, TChave x) {
  RetiraRecursivo(pRaiz, x);
  if ( *pRaiz != NULL)
    ( *pRaiz) -> cor = 0; // a raiz e negra
}

int RetiraRecursivo(TArvBin * p, TChave x) {
  TArvBin q;
  int bh;
  if ( * p == NULL)
    return 0; // retorna 0 caso o item nao esteja na arvore
  else if (x < ( * p) -> Item.Chave) {
    if (RetiraRecursivo( & ( * p) -> Esq, x))
      return BalancaDireita(p); // subarvore esquerda encolheu
    return 0;
  } else if (x > ( * p) -> Item.Chave) {
    if (RetiraRecursivo( & ( * p) -> Dir, x))
      return BalancaEsquerda(p); // subarvore direita encolheu
    return 0;
  } else {
    q = * p;
    if (q -> Esq == NULL) {
      * p = q -> Dir;
      bh = EhNegro( * p) && EhNegro(q);
      if (!bh && EhNegro(q))
        ( * p) -> cor = 0;
    } else if (q -> Dir == NULL) {
      * p = q -> Esq;
      bh = EhNegro( * p) && EhNegro(q);
      if (!bh && EhNegro(q))
        ( * p) -> cor = 0;
    } else { // possui dois filhos
      if (Sucessor(&q, &q -> Dir))
        bh = BalancaEsquerda(p); // subarvore direita encolheu
      else bh = 0;
    }
    free(q);
    return bh;
  }
}

int BalancaEsquerda(TArvBin * pC) {
  TArvBin pD = ( * pC) -> Esq;
  if (EhRubro(pD)) { // caso 4b
    RotacaoDireita(pC);
    pC = & ( * pC) -> Dir;
    pD = ( * pC) -> Esq;
  }
  if (pD != NULL) {
    if (EhNegro(pD -> Esq) && EhNegro(pD -> Dir)) { // caso 1
      InverteCor(pD);
      if (EhRubro( * pC)) {
        InverteCor( * pC);
        return 0;
      }
    } else {
      int cor = ( * pC) -> cor;
      ( * pC) -> cor = 0;
      if (EhNegro(pD -> Esq)) // caso 2b
        RotacaoEsquerda( & ( * pC) -> Esq);
      else
        InverteCor(pD -> Esq);
      RotacaoDireita(pC); // caso 3b
      ( * pC) -> cor = cor;
      return 0;
    }
  }
  return 1;
}

int BalancaDireita(TArvBin * pC) {
  TArvBin pD = ( * pC) -> Dir;
  if (EhRubro(pD)) { // caso 4a
    RotacaoEsquerda(pC);
    pC = & ( * pC) -> Esq;
    pD = ( * pC) -> Dir;
  }
  if (pD != NULL) {
    if (EhNegro(pD -> Esq) && EhNegro(pD -> Dir)) { // caso 1
      InverteCor(pD);
      if (EhRubro( * pC)) {
        InverteCor( * pC);
        return 0;
      }
    } else {
      int cor = ( * pC) -> cor;
      ( * pC) -> cor = 0;
      if (EhNegro(pD -> Dir)) // caso 2a
        RotacaoDireita( & ( * pC) -> Dir);
      else
        InverteCor(pD -> Dir);
      RotacaoEsquerda(pC); // caso 3a
      ( * pC) -> cor = cor;
      return 0;
    }
  }
  return 1;
}

int Sucessor(TArvBin * q, TArvBin * r) {
  int bh;
  if (( * r) -> Esq != NULL) {
    if (Sucessor(q, & ( * r) -> Esq))
      return BalancaDireita(r); // subarvore esquerda encolheu
    return 0;
  } else {
    ( * q) -> Item = ( * r) -> Item;
    * q = * r;
    * r = ( * r) -> Dir;
    bh = EhNegro( * q) && EhNegro( * r);
    if (!bh && EhNegro( * q))
      ( * r) -> cor = 0;
    return bh;
  }
}

void InverteCor(TArvBin No) {
  if (No != NULL) No -> cor = !No -> cor;
}


int main()
{
  

	TArvBin Raiz;
	TItem x;
    clock_t inicio,fim;
    int max = 10;
    int *vetor;
    vetor = (TChave*) malloc(max*sizeof(int));
	  Raiz = Inicializa();


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
      x.Chave = vetor[randomIndex];
  }

  //inicio=clock();
  for (int i = 0; i < max; i++) {    // print array
      x.Chave = vetor[i];      
      Insere(&Raiz, x); 
      //printf("Inseriu chave: %d\n",x.Chave);      
  }
   //fim=clock();
   //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);     
   //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion); 

  //printf("=========ASCENDENTE=========\n");
//inicio=clock();
  for (int i = 0; i < max; i++) {     // fill array
      vetor[i] = i;
      x.Chave = vetor[i];
      Insere(&Raiz, x);
      //printf("Inseriu chave: %d\n",x.Chave);
    }
  //fim = clock();
  //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC); 
  //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);

    /*//printf("=========DESCENDENTE=========\n");
  //inicio=clock();
    int j = 0;
    for (int i = max-1; i >=0; i--) {     // fill array
        vetor[j] = i;
        x.Chave = vetor[j];
        j++;
        Insere(&Raiz, x);
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
      x.Chave = vetor[i];     
      Insere(&Raiz, x);
      //printf("Inseriu chave: %d\n",x.Chave);      
    }
    //fim=clock();
    //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);     
    //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/
    
    /*//==========PESQUISA===========
    //printf("Empieza la pesquisa\n"); 
    //inicio=clock();
    for (int i = 0; i < max+1; i++) {
        Pesquisa(Raiz, i);    
    }
    //fim=clock();
    //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);  
    //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);*/

    //==========REMOCAO===========
    //printf("Empieza la remocao\n");
    //inicio=clock();
    for (int i = 0; i < max; i++) {
        x.Chave = i;
        //printf("llave a eliminar: %d\n",x.Chave);
        Remove(&Raiz, x.Chave);
    }
    //fim=clock();  
    //double time_insertion = (double)(((double)fim-(double)inicio)/CLOCKS_PER_SEC);  
    //printf(">>>Tempo de ejecucao = %3.3f segundos\n",time_insertion);


}