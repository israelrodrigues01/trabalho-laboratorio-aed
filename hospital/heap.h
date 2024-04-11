#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

struct paciente
{
    char nome[100];
    int urgencia;
    int hora;
    int minuto;
    int segundo;
};

typedef struct heap Heap;
typedef struct paciente Paciente;

Heap *criaHeap(int maximo);
int insereHeap(Heap *, Paciente dados);
int removeHeap(Heap *);
int deletaHeap(Heap *);

#endif // HEAP_H_INCLUDED
