% Relatório
% Vasco Alves, Miguel Angelo 

# Introdução

O objectivo deste trabalho é construir uma aplicação capaz de armazenar, alterar e gerir a informação dos doentes de um médico. Esta informação inclui: nome, data de nascimento, cartão de cidadão, telefone e email. Para além desta funcionalidade deve ser capaz de armazenar os seus dados clínicos. Estes são: tensão arterial mínima, tensão arterial máxima, peso e altura. 

Para este efeito criamos duas listas ligadas armazenas em ficheiros `header`.  
```c
#include "doente.h"
#include "registo.h"
```
O `struct Doente` foi criado para
```c
typedef struct Doente {
    char nome[50];
    size_tt id;
    char email[50];
    char cc[15];
    char data[50];       
    size_tt telefone;
} Doente;

typedef struct noDoente {
    struct Doente doente;
    struct noDoente* prox;
} noDoente ;

```

