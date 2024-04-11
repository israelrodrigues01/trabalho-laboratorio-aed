#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

struct heap
{
    int maximo;
    int posicao;
    Paciente *prioridade;
};

Heap *criaHeap(int maximo)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap));

    if (heap != NULL)
    {
        heap->maximo = maximo;
        heap->posicao = 0;
        heap->prioridade = (Paciente *)malloc(maximo * sizeof(Paciente));
    }

    return heap;
}

int vazio(Heap *heap)
{
    if (heap == NULL)
    {
        return 1;
    }
    return 0;
}

void troca(Heap *heap, int pos, int pai)
{
    Paciente paciente = heap->prioridade[pos];
    heap->prioridade[pos] = heap->prioridade[pai];
    heap->prioridade[pai] = paciente;
}

void subir(Heap *heap, int pos)
{
    int pai;
    while (pos > 0)
    {
        pai = (pos - 1) / 2;
        if (heap->prioridade[pai].urgencia > heap->prioridade[pos].urgencia)
        {
            troca(heap, pos, pai);
        }
        else if (heap->prioridade[pai].urgencia == heap->prioridade[pos].urgencia)
        {
            if (heap->prioridade[pai].hora > heap->prioridade[pos].hora)
            {
                troca(heap, pos, pai);
            }
            else if (heap->prioridade[pai].hora == heap->prioridade[pos].hora)
            {
                if (heap->prioridade[pai].minuto > heap->prioridade[pos].minuto)
                {
                    troca(heap, pos, pai);
                }
                else if (heap->prioridade[pai].minuto == heap->prioridade[pos].minuto)
                {
                    if (heap->prioridade[pai].segundo > heap->prioridade[pos].segundo)
                    {
                        troca(heap, pos, pai);
                    }
                }
            }
        }
        else
        {
            break;
        }

        pos = pai;
    }
}

void descer(Heap *heap, int pos, int tam)
{
    int pai = pos;
    int filho_esq, filho_dir, filho;

    while (2 * pai + 1 < tam)
    {
        filho_esq = 2 * pai + 1;
        filho_dir = 2 * pai + 2;

        if (filho_dir > tam)
        {
            filho_dir = filho_esq;
        }

        // Verica qual filho tem mais prioridade
        if (heap->prioridade[filho_esq].urgencia < heap->prioridade[filho_dir].urgencia)
        {
            filho = filho_esq;
        }
        else if (heap->prioridade[filho_esq].urgencia == heap->prioridade[filho_dir].urgencia)
        {
            if (heap->prioridade[filho_esq].hora < heap->prioridade[filho_dir].hora)
            {
                filho = filho_esq;
            }
            else if (heap->prioridade[filho_esq].hora == heap->prioridade[filho_dir].hora)
            {
                if (heap->prioridade[filho_esq].minuto < heap->prioridade[filho_dir].minuto)
                {
                    filho = filho_esq;
                }
                else if (heap->prioridade[filho_esq].minuto == heap->prioridade[filho_dir].minuto)
                {
                    if (heap->prioridade[filho_esq].segundo < heap->prioridade[filho_dir].segundo)
                    {
                        filho = filho_esq;
                    }
                }
            }
        }
        else
        {
            filho = filho_dir;
        }

        // Troca do filho e pai, caso o filho tenha mais prioridade que o pai
        if (heap->prioridade[pai].urgencia > heap->prioridade[filho].urgencia)
        {
            troca(heap, filho, pai);
        }
        else if (heap->prioridade[pai].urgencia == heap->prioridade[filho].urgencia)
        {
            if (heap->prioridade[pai].hora > heap->prioridade[filho].hora)
            {
                troca(heap, filho, pai);
            }
            else if (heap->prioridade[pai].hora == heap->prioridade[filho].hora)
            {
                if (heap->prioridade[pai].minuto > heap->prioridade[filho].minuto)
                {
                    troca(heap, filho, pai);
                }
                else if (heap->prioridade[pai].minuto == heap->prioridade[filho].minuto)
                {
                    if (heap->prioridade[pai].segundo > heap->prioridade[filho].segundo)
                    {
                        troca(heap, filho, pai);
                    }
                }
            }
        }
        else
        {
            break;
        }

        pai = filho;
    }
}

int insereHeap(Heap *heap, Paciente dados)
{
    if (vazio(heap))
    {
        return -1;
    }

    if (heap->posicao < heap->maximo)
    {
        heap->prioridade[heap->posicao] = dados;
        subir(heap, heap->posicao);
        heap->posicao++;
        return 1;
    }

    return 0;
};

int removeHeap(Heap *heap)
{
    if (vazio(heap))
    {
        return -1;
    }

    if (heap->posicao > 0)
    {
        printf("\nUrgencia: %d", heap->prioridade[0].urgencia);
        printf("\nHora: %d", heap->prioridade[0].hora);
        printf("\nminuto: %d", heap->prioridade[0].minuto);
        printf("\nsegundo: %d", heap->prioridade[0].segundo);
        heap->prioridade[0] = heap->prioridade[heap->posicao - 1];
        heap->posicao--;
        descer(heap, 0, heap->posicao);
        return 1;
    }
    return 0;
};

int deletaHeap(Heap *);
