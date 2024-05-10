#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doente.h"

pDoente doente_criar() {
    pDoente aux;

    Doente doente = { "", 0, "", "", "", 0 };

    aux = (pDoente)malloc(sizeof(noDoente));
    if (aux != NULL) {
        aux->doente = doente;
        aux->prox = NULL;
    }
    return aux;
}

void doente_destroi(pDoente raiz) {
    pDoente temp_ptr;
    while (!doente_vazia(raiz)) {
        temp_ptr = raiz;
        raiz = raiz->prox;
        free (temp_ptr);
    }

    free(raiz);
}

int doente_vazia(pDoente raiz) {
    return raiz->prox == NULL;
}

void doente_procura(pDoente raiz, size_tt id, pDoente *anterior, pDoente *atual) {
    *anterior = raiz;
    *atual = raiz->prox;
    // esta merda nunca acaba
    while ((*anterior) != NULL && (*anterior)->doente.id < id) {
        //printf("anterior: %p\tatual: %p\n", anterior, atual); // para debug
        *anterior = *anterior;
        *atual = (*anterior)->prox;
        // esta merda acaba 😀
        if (*anterior == raiz) break;
    }
    if ((*anterior) != NULL && (*anterior)->doente.id != id) {
      *atual = NULL;
    }
}

void doente_insere(pDoente raiz, Doente doente, int isloading) {
    pDoente novo, ant, inutil;

    novo = (pDoente)malloc(sizeof(noDoente));

    if (novo != NULL) {
        // insere no fim porque esta por ordem
        if (isloading == FALSE)  {
            ant = raiz->prox;
            while (ant->prox !=NULL ) ant = ant->prox;
            doente.id = (ant != raiz) ? ant->doente.id + 1 : 1;
        }
        // so neste caso é que precisamos de procurar
        // porque ja sabemos o id
        else {
            doente_procura(raiz, doente.id, &ant, &inutil);
        }

        novo->doente = doente;
        novo->prox = ant->prox; 
        ant->prox = novo; 

    } else {
        printf("Não há mais memória.");
        free(novo);
    }
}


void doente_retira(pDoente raiz, size_tt id) {
    pDoente atual, anterior;
    doente_procura(raiz, id, &anterior, &atual);
    if (atual == NULL) {
      printf("Não existe nenhum doente com esse ID!\n");
      return;
    }
    anterior->prox = atual->prox; 
    free(atual); 
}

void doente_info(pDoente raiz, size_tt id) {
    pDoente atual, anterior;
    doente_procura(raiz, id, &anterior, &atual);
    if (atual == NULL) {
      printf("Não existe nenhum doente com esse ID!\n");
      return;
    }
    Doente doente = atual->doente;
    printf("Nome: %s\nID: %d\nEmail: %s\nNúmero de cartão de cidadão: %s\nData de nascimento: %s\nNúmero de telefone: %d\n", doente.nome, doente.id, doente.email, doente.cc, doente.data, doente.telefone);
}

void doente_listar_todos(pDoente raiz) {
    pDoente aux = raiz->prox;
    while (aux) {
        printf("Doente: %s ID: %d\n", aux->doente.nome, aux->doente.id);
        aux = aux->prox;
    }
}

void doente_carregar(pDoente raiz) {
    FILE *ficheiro = fopen("doentes.txt", "r");
    if (ficheiro == NULL) {
        printf("Não há ficheiro com doentes\n");
        return;
    }
    
    Doente doente;
    while (fscanf(ficheiro, "%d ", &doente.id)) { 
        if (fgets(doente.nome, 50, ficheiro) == NULL) break;
        doente.nome[strcspn(doente.nome, "\n")] = '\0';
        if (fgets(doente.data, 50, ficheiro) == NULL) break;
        doente.data[strcspn(doente.data, "\n")] = '\0';
        if (fgets(doente.cc, 14, ficheiro) == NULL) break;
        doente.cc[strcspn(doente.cc, "\n")] = '\0';
        fscanf(ficheiro, "%d ", &doente.telefone);
        if (fgets(doente.email, 50, ficheiro) == NULL) break;
        doente.email[strcspn(doente.email, "\n")] = '\0';

        doente_insere(raiz, doente, TRUE); // hmm

        printf("Doente carregado: %s\n", doente.nome);
    }

    if (fclose(ficheiro) != 0) printf("Erro ao fechar o ficheiro!\n");
    printf("Todos os doentes forma carregados!\n");
}


void doentes_update_ficheiro(pDoente raiz) {
    FILE *ficheiro;
    ficheiro = fopen("doentes.txt", "w");

    if (ficheiro == NULL) {
        printf("Erro ao abrir o ficheiro!\n");
        return;
    }

    pDoente temp_ptr = raiz->prox;
    while (temp_ptr !=NULL) {
        Doente doente = temp_ptr->doente;


        printf("Guardando doente: %s", doente.nome);
        if (fprintf(ficheiro, "%d\n%s\n%s\n%s\n%d\n%s\n", doente.id, doente.nome, doente.data, doente.cc, doente.telefone, doente.email)) {
            printf("\n"); } else { printf("\t [ERRO]\n");
        };

        temp_ptr = temp_ptr->prox;
    }

    // o close estava dentro do loop 😭😭
    if (fclose(ficheiro) != 0) printf("Erro ao fechar o ficheiro!\n");
}
