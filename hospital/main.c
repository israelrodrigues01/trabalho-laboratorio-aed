#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void menu()
{
    printf("Digite o numero da opcao desejada:\n");
    printf("1 - Inserir paciente\n");
    printf("2 - Atender Paciente\n");
    printf("3 - Encerrar programa\n");
}

void prencherPaciente(Paciente *paciente)
{
    char nome[100];
    int urgencia, hora, minuto, segundo;

    printf("\nDigite o nome do paciente: ");
    fflush(stdin);
    scanf("%s", paciente->nome);

    do
    {
        printf("\nUrgencia de acordo com o Protocolo de Mancheste: ");
        printf("\n1 - Vermelho\n");
        printf("2 - Laranja\n");
        printf("3 - Amarelo\n");
        printf("4 - Verde\n");
        printf("5 - Azul\n");
        scanf("%d", &urgencia);

        if (urgencia < 0 || urgencia > 6)
        {
            printf("Opcao invalida, tente novamente. \n\n");
        }
    } while (urgencia < 0 || urgencia > 6);

    do
    {
        printf("Hora de chegada: ");
        scanf("%d", &hora);

        if (hora < 1 || hora > 24)
        {
            printf("Opcao invalida, tente novamente. \n\n");
        }
    } while (hora < 0 || hora > 24);

    do
    {
        printf("Minuto de chegada: ");
        scanf("%d", &minuto);

        if (minuto < 0 || minuto > 59)
        {
            printf("Opcao invalida, tente novamente. \n\n");
        }
    } while (minuto < 0 || minuto > 59);

    do
    {
        printf("Segundo de chegada: ");
        scanf("%d", &segundo);

        if (segundo < 0 || segundo > 59)
        {
            printf("Opcao invalida, tente novamente. \n\n");
        }
    } while (segundo < 0 || segundo > 59);

    paciente->urgencia = urgencia;
    paciente->hora = hora;
    paciente->minuto = minuto;
    paciente->segundo = segundo;
}

int main()
{
    int start = 1, opcao;
    Heap *heap = criaHeap(10);

    Paciente paciente;

    while (start)
    {
        menu();
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            prencherPaciente(&paciente);
            insereHeap(heap, paciente);
        }
        else if (opcao == 2)
        {
            removeHeap(heap);
        }
        else if (opcao == 3)
        {
            start = 0;
            deletaHeap(heap);
        }
        else
        {
            printf("Opcao invalida, tente novamente. \n\n");
        }
    }

    return 0;
}
