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

void doente_carregar(pDoente raiz) {
    FILE *ficheiro = fopen("doentes.txt", "r");
    if (ficheiro == NULL) {
        printf("Não há ficheiro com doentes\n");
        return;
    }
    
    Doente doente;

    int i = 1;
    while (fscanf(ficheiro, "%d ", &doente.id)) { 
        printf("Lendo linha %d...\n", i);
        if (fgets(doente.nome, 50, ficheiro) == NULL) break;
        doente.nome[strcspn(doente.nome, "\n")] = '\0';
        i++;
        printf("Lendo linha %d...\n", i);
        if (fgets(doente.data, 50, ficheiro) == NULL) break;
        doente.data[strcspn(doente.data, "\n")] = '\0';
        i++;
        printf("Lendo linha %d...\n", i);
        if (fgets(doente.cc, 14, ficheiro) == NULL) break;
        doente.cc[strcspn(doente.cc, "\n")] = '\0';
        i++;
        printf("Lendo linha %d...\n", i);
        fscanf(ficheiro, "%d ", &doente.telefone);
        if (fgets(doente.email, 50, ficheiro) == NULL) break;
        doente.email[strcspn(doente.email, "\n")] = '\0';
        i++;
        printf("Lendo linha %d...\n", i);

        doente_insere(raiz, doente);

        printf("\nDoente carregado: %s\n", doente.nome);
    }

    if (fclose(ficheiro) != 0) printf("Erro ao fechar o ficheiro!\n");
    printf("Doentes carregados...\n");
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
        printf("anterior: %p\tatual: %p\n", anterior, atual); // para debug
        *anterior = *anterior;
        *atual = (*anterior)->prox;
    }
    if ((*anterior) != NULL && (*anterior)->doente.id != id) {
      *atual = NULL;
    }
}

void doente_insere(pDoente raiz, Doente doente) {
    pDoente novo, ant, inutil;

    novo = (pDoente)malloc(sizeof(noDoente));
    
    if (novo != NULL) {
        doente_procura(raiz, doente.id, &ant, &inutil);

        doente.id = ant->doente.id+1;

        novo->doente = doente;
        novo->prox = ant->prox; 
        ant->prox = novo; 

        printf("O doente foi adicionado!\n");
    } else {
        printf("Não há mais memória.");
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
    // TODO: Remover do ficheiro o doente
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
