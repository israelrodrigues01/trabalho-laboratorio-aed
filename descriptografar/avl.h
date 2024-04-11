#ifndef AVL_H_INCLUDED
#define AVL_H_INCLUDED

typedef struct NO *AVL;

AVL *criaAVL();
int deletarAVL(AVL *);
int insereAVL(AVL *, int valor, char letra);
int removeAVL(AVL *, int valor);
int vaziaAVL(AVL *);
int alturaAVL(AVL *);
int preOrdemAVL(AVL *);
int ordemSimetricaAVL(AVL *);
int posOrdemAVL(AVL *);

#endif // AVL_H_INCLUDED
