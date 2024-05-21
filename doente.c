#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "doente.h"

pDoente doente_criar() {
  Doente doente = { "", 0, "", "", {0, 0, 0,} , 1 };
  pDoente aux = (pDoente)malloc(sizeof(noDoente));
  if (aux != NULL) {
    aux->doente = doente;
    aux->prox = NULL;
    aux->prox_alfabetica = NULL;
  }
  return aux;
}

void doente_carregar(pDoente raiz) {
  FILE *ficheiro = fopen("doentes.txt", "r");
  if (ficheiro == NULL) {
    return;
  }
  Doente doente;
  while (fscanf(ficheiro, "%d", &doente.id) == 1) {
    limpar_buffer(ficheiro);
    fgets(doente.nome, TAM_NOME, ficheiro);
    doente.nome[strcspn(doente.nome, "\n")] = '\0';
    char data_text[14];
    fgets(data_text, 14, ficheiro);
    Data dt = {atoi(strtok(data_text, "/")), atoi(strtok(NULL, "/")), atoi(strtok(NULL, "/"))};
    doente.data = dt;
    fgets(doente.cc, TAM_CC, ficheiro);
    doente.cc[strcspn(doente.cc, "\n")] = '\0';
    fscanf(ficheiro, "%d", &doente.telefone);
    limpar_buffer(ficheiro);
    fgets(doente.email, TAM_EMAIL, ficheiro);
    doente.email[strcspn(doente.email, "\n")] = '\0';
    doente_insere(raiz, doente);
  }
  if (fclose(ficheiro) != 0) {
    printf("Erro ao fechar o ficheiro!\n");
  }
}

void doente_guardar(pDoente raiz) {
  FILE *ficheiro = fopen("doentes.txt", "w");
  if (ficheiro == NULL) {
    return;
  }
  pDoente aux = raiz->prox;
  while (aux != NULL) {
    Doente doente = aux->doente;
    fprintf(ficheiro, "%d\n%s\n%d/%d/%d\n%s\n%d\n%s\n", doente.id, doente.nome, doente.data.dia, doente.data.mes, doente.data.ano, doente.cc, doente.telefone, doente.email);
    aux = aux->prox;
  }
  if (fclose(ficheiro) != 0) {
    printf("Erro ao fechar o ficheiro!\n");
  }
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
  while ((*atual) != NULL && (*atual)->doente.id < id) {
    *anterior = *atual;
    *atual = (*atual)->prox;
  }
  if ((*atual) != NULL && (*atual)->doente.id != id) {
    *atual = NULL;
  }
}

void doente_procura_alfabetica(pDoente raiz, char *nome, pDoente *anterior, pDoente *atual) {
  *anterior = raiz;
  *atual = raiz->prox_alfabetica;
  while ((*atual) != NULL && strcasecmp((*atual)->doente.nome, nome) < 0) {
    *anterior = *atual;
    *atual = (*atual)->prox_alfabetica;
  }
  if ((*atual) != NULL && strcasecmp((*atual)->doente.nome, nome) != 0) {
    *atual = NULL;
  }
}

size_tt doente_obter_id(pDoente raiz) {
  return (raiz->doente.telefone)+1;
}

void doente_insere(pDoente raiz, Doente doente) {
  pDoente no, anterior, inutil, anterior_alfabetica, inutil_alfabetica;
  no = (pDoente)malloc(sizeof(noDoente));
  if (no != NULL) {
    if (doente.id == 0) {
      doente.id = doente_obter_id(raiz);
    }
    doente_procura(raiz, doente.id, &anterior, &inutil);
    no->doente = doente;
    no->prox = anterior->prox;
    anterior->prox = no;
    doente_procura_alfabetica(raiz, doente.nome, &anterior_alfabetica, &inutil_alfabetica);
    no->prox_alfabetica = anterior_alfabetica->prox_alfabetica;
    anterior_alfabetica->prox_alfabetica = no;
  }
  if (doente.id > raiz->doente.telefone) {
    raiz->doente.telefone = doente.id;
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
  printf("Nome: %s\nID: %d\nEmail: %s\nNúmero de cartão de cidadão: %s\nData de nascimento: %d/%d/%d\nNúmero de telefone: %d\n", doente.nome, doente.id, doente.email, doente.cc, doente.data.dia, doente.data.mes, doente.data.ano, doente.telefone);
}

void doente_listar_ordem_alfabetica(pDoente raiz) {
  pDoente aux = raiz->prox_alfabetica;
  while (aux) {
    printf("Doente: %s ID: %d\n", aux->doente.nome, aux->doente.id);
    aux = aux->prox_alfabetica;
  }
}

Doente doente_id_para_doente(pDoente raiz, size_tt id) {
  Doente doente = { "", 0, "", "", {0, 0, 0}, 0 };
  pDoente aux = raiz->prox;
  while (aux) {
    if (aux->doente.id == id) {
      doente = aux->doente;
    }
    aux = aux->prox;
  }
  return doente;
}
