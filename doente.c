#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "doente.h"

pDoente doente_criar() {
  pDoente aux;
  Doente doente = { "", 0, "", "", {0, 0, 0,} , 0 };
  aux = (pDoente)malloc(sizeof(noDoente));
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
  do {
    fscanf(ficheiro, "%d", &doente.id);
    printf("ID: %d\n", doente.id);
    int clr;
    fscanf(ficheiro, "%d", &clr);
    if (fgets(doente.nome, 50, ficheiro) == NULL) break;
    doente.nome[strcspn(doente.nome, "\n")] = '\0';
    printf("Nome: %s\n", doente.nome);
    char data_text[12];
    if (fgets(data_text, 12, ficheiro) == NULL) break;
    Data dt = {atoi(strtok(data_text, "/")), atoi(strtok(NULL, "/")), atoi(strtok(NULL, "/"))};
    doente.data = dt;
    printf("Data: %d/%d/%d\n", doente.data.dia, doente.data.mes, doente.data.ano);
    if (fgets(doente.cc, 15, ficheiro) == NULL) break;
    doente.cc[strcspn(doente.cc, "\n")] = '\0';
    printf("CC: %s\n", doente.cc);
    if (fscanf(ficheiro, "%d ", &doente.telefone)==0) break;
    printf("Telefone: %d\n", doente.telefone);
    if (fgets(doente.email, 50, ficheiro) == NULL) break;
    doente.email[strcspn(doente.email, "\n")] = '\0';
    printf("Email: %s\n", doente.email);
    doente_insere(raiz, doente);
    printf("Doente carregado: %s %d\n", doente.nome, doente.id);      
  } while (doente.id != 0); 
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
    printf("Doente escrito: %s\n", doente.nome);      
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
  pDoente aux = raiz->prox;
  while (aux->prox != NULL) {
    if ((aux->doente.id)+1 < aux->prox->doente.id) {
      return (aux->doente.id)+1;
    }
    aux = aux->prox;
  }
  return (aux->doente.id)+1;
}

void doente_insere(pDoente raiz, Doente doente) {
  pDoente no, anterior, inutil, anterior_alfabetica, inutil_alfabetica;
  no = (pDoente)malloc(sizeof(noDoente));
  if (no != NULL) {
    if (doente.id == 0) {
      printf("A obter novo id\n");
      doente.id = doente_obter_id(raiz);
      printf("Novo id obtido: %d\n", doente.id);
    }
    doente_procura(raiz, doente.id, &anterior, &inutil);
    no->doente = doente;
    no->prox = anterior->prox;
    anterior->prox = no;
    doente_procura_alfabetica(raiz, doente.nome, &anterior_alfabetica, &inutil_alfabetica);
    no->prox_alfabetica = anterior_alfabetica->prox_alfabetica;
    anterior_alfabetica->prox_alfabetica = no;
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
