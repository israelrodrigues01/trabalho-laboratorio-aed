#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

int main()
{
    Heap *heap = criaHeap(10);
    Paciente cicero;
    cicero.nome, "Cicero";
    cicero.urgencia = 1;
    cicero.hora = 11;
    cicero.minuto = 11;
    cicero.segundo = 11;

    Paciente b;
    b.nome, "b";
    b.urgencia = 1;
    b.hora = 11;
    b.minuto = 11;
    b.segundo = 11;

    Paciente c;
    c.nome, "c";
    c.urgencia = 2;
    c.hora = 11;
    c.minuto = 11;
    c.segundo = 11;

    Paciente d;
    d.nome, "d";
    d.urgencia = 2;
    d.hora = 11;
    d.minuto = 11;
    d.segundo = 10;

    insereHeap(heap, cicero);
    insereHeap(heap, b);
    insereHeap(heap, c);
    insereHeap(heap, d);
    removeHeap(heap);
    removeHeap(heap);
    removeHeap(heap);

    return 0;
}
