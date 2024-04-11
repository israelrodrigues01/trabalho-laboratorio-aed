#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main()
{
    AVL *avl[100] = {0};
    int ids[100] = {0};
    int tipos[100] = {0};
    int count = 0;
    int exist = 0;

    FILE *arquivo;
    char linha[100];

    arquivo = fopen("entrada.txt", "r");

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        int ID, TIPO;
        sscanf(linha, "%d, %d", &ID, &TIPO);

        for (int i = 0; i <= count + 1; i++)
        {
            if (ID == ids[i])
            {
                exist = 1;
                break;
            }
        }

        if (!exist)
        {
            ids[count] = ID;
            tipos[count] = TIPO;
            avl[count] = criaAVL();
            count++;
        }
    }

    arquivo = fopen("entrada.txt", "r");

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        int ID;
        char LETRA;
        int VALOR;
        sscanf(linha, "%d,%c,%d", &ID, &LETRA, &VALOR);

        for (int i = 0; i < count + 1; i++)
        {
            if(VALOR != 0){
                if (ids[i] == ID)
                {
                    insereAVL(avl[i], VALOR, LETRA);
                }
            }
        }
    }

    for (int i = 0; i < count + 1; i++)
    {
        if (tipos[i] == 1)
        {
            preOrdemAVL(avl[i]);
            printf("\n");
        }
        else if (tipos[i] == 2)
        {
            ordemSimetricaAVL(avl[i]);
            printf("\n");
        }
        else
        {
            posOrdemAVL(avl[i]);
            printf("\n");
        }

        deletarAVL(avl[i]);
    }

    fclose(arquivo);
    return 0;
}
