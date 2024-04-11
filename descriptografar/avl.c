#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

struct NO
{
    int valor;
    char letra;
    int type;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO No;

AVL *criaAVL()
{
    AVL *raiz = (AVL *)malloc(sizeof(AVL));
    if (raiz != NULL)
    {
        *raiz = NULL;
    }

    return raiz;
}

int deletaNOAVL(No *no)
{
    if (vaziaAVL(no))
    {
        return -1;
    }

    deletaNOAVL(no->esq);
    deletaNOAVL(no->dir);
    free(no);
    no = NULL;
    return 0;
}

int deletarAVL(AVL *raiz)
{
    if (vaziaAVL(raiz))
    {
        return -1;
    }

    deletaNOAVL(*raiz);
    free(raiz);

    return 0;
}

int alturaNoAVL(No *no)
{
    if (vaziaAVL(no))
    {
        return -1;
    }

    return no->altura;
}

int balanceamentoAVL(No *no)
{
    return labs(alturaNoAVL(no->esq) - alturaNoAVL(no->dir)); // Labs retorna o valor abosluto, como um módulo de X
}

int maior(int x, int y)
{
    if (x > y)
    {
        return x;
    }

    return y;
}

int vaziaAVL(AVL *raiz)
{
    if (raiz == NULL || *raiz == NULL)
    {
        return 1;
    }

    return 0;
}

int qtdNoAVL(AVL *raiz)
{
    if (vaziaAVL(raiz))
    {
        return -1;
    }

    int alt_esq = qtdNoAVL(&((*raiz)->esq));
    int alt_dir = qtdNoAVL(&((*raiz)->dir));
    return (alt_esq + alt_dir + 1);
}

int alturaAVL(AVL *raiz)
{
    if (vaziaAVL(raiz))
    {
        return -1;
    }

    int alt_esq = alturaAVL(&((*raiz)->esq));
    int alt_dir = alturaAVL(&((*raiz)->dir));

    if (alt_esq > alt_dir)
    {
        return (alt_esq + 1);
    }

    return (alt_dir + 1);
}

int preOrdemAVL(AVL *raiz)
{
    if (vaziaAVL(raiz))
    {
        return -1;
    }

    printf("%c", (*raiz)->letra);
    preOrdemAVL(&((*raiz)->esq));
    preOrdemAVL(&((*raiz)->dir));

    return 0;
}

int ordemSimetricaAVL(AVL *raiz)
{
    if (vaziaAVL(raiz))
    {
        return -1;
    }
    ordemSimetricaAVL(&((*raiz)->esq));
    printf("%c", (*raiz)->letra);
    ordemSimetricaAVL(&((*raiz)->dir));

    return 0;
}

int posOrdemAVL(AVL *raiz)
{
    if (vaziaAVL(raiz))
    {
        return -1;
    }

    posOrdemAVL(&((*raiz)->esq));
    posOrdemAVL(&((*raiz)->dir));
    printf("%c", (*raiz)->letra);

    return 0;
}

void rotacaoLL(AVL *A)
{
    No *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(alturaNoAVL((*A)->esq), alturaNoAVL((*A)->dir)) + 1;
    B->altura = maior(alturaNoAVL(B->esq), (*A)->altura) + 1;
    *A = B;
}

void rotacaoRR(AVL *A)
{
    No *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(alturaNoAVL((*A)->esq), alturaNoAVL((*A)->dir)) + 1;
    B->altura = maior(alturaNoAVL(B->dir), (*A)->altura) + 1;
    (*A) = B;
}

void rotacaoLR(AVL *A)
{
    rotacaoRR(&(*A)->esq);
    rotacaoLL(A);
}

void rotacaoRL(AVL *A)
{

    rotacaoLL(&(*A)->dir);
    rotacaoRR(A);
}

int insereAVL(AVL *raiz, int valor, char letra)
{
    int res;
    if (vaziaAVL(raiz))
    {
        No *novo;
        novo = (No *)malloc(sizeof(No));
        if (novo == NULL)
            return 0;

        novo->valor = valor;
        novo->letra = letra;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    No *atual = *raiz;
    if (valor < atual->valor)
    {
        if ((res = insereAVL(&(atual->esq), valor, letra)) == 1)
        {
            if (balanceamentoAVL(atual) >= 2)
            {
                if (valor < (*raiz)->esq->valor)
                {
                    rotacaoLL(raiz);
                }
                else
                {
                    rotacaoLR(raiz);
                }
            }
        }
    }
    else
    {
        if (valor > atual->valor)
        {
            if ((res = insereAVL(&(atual->dir), valor, letra)) == 1)
            {
                if (balanceamentoAVL(atual) >= 2)
                {
                    if ((*raiz)->dir->valor < valor)
                    {
                        rotacaoRR(raiz);
                    }
                    else
                    {
                        rotacaoRL(raiz);
                    }
                }
            }
        }
        else
        {
            printf("Valor duplicado!!\n");
            return 0;
        }
    }

    atual->altura = maior(alturaNoAVL(atual->esq), alturaNoAVL(atual->dir)) + 1;

    return res;
}

No *procuraMenor(No *atual)
{
    No *no1 = atual;
    No *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int removeAVL(AVL *raiz, int valor)
{
    if (vaziaAVL(raiz))
    {
        return -1;
    }

    int res;
    if (valor < (*raiz)->valor)
    {
        if ((res = removeAVL(&(*raiz)->esq, valor)) == 1)
        {
            if (balanceamentoAVL(*raiz) >= 2)
            {
                if (alturaNoAVL((*raiz)->dir->esq) <= alturaNoAVL((*raiz)->dir->dir))
                    rotacaoRR(raiz);
                else
                    rotacaoRL(raiz);
            }
        }
    }

    if ((*raiz)->valor < valor)
    {
        if ((res = removeAVL(&(*raiz)->dir, valor)) == 1)
        {
            if (balanceamentoAVL(*raiz) >= 2)
            {
                if (alturaNoAVL((*raiz)->esq->dir) <= alturaNoAVL((*raiz)->esq->esq))
                    rotacaoLL(raiz);
                else
                    rotacaoLR(raiz);
            }
        }
    }

    if ((*raiz)->valor == valor)
    {
        if (((*raiz)->esq == NULL || (*raiz)->dir == NULL))
        {
            No *oldNode = (*raiz);
            if ((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(oldNode);
        }
        else
        {
            No *temp = procuraMenor((*raiz)->dir);
            (*raiz)->valor = temp->valor;
            removeAVL(&(*raiz)->dir, (*raiz)->valor);
            if (balanceamentoAVL(*raiz) >= 2)
            {
                if (alturaNoAVL((*raiz)->esq->dir) <= alturaNoAVL((*raiz)->esq->esq))
                    rotacaoLL(raiz);
                else
                    rotacaoLR(raiz);
            }
        }
        if (*raiz != NULL)
            (*raiz)->altura = maior(alturaNoAVL((*raiz)->esq), alturaNoAVL((*raiz)->dir)) + 1;
        return 1;
    }

    (*raiz)->altura = maior(alturaNoAVL((*raiz)->esq), alturaNoAVL((*raiz)->dir)) + 1;

    return res;
}
