#include "registo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

pRegisto registo_criar() {
  pRegisto aux;
  Registo registo = { 0, {0, 0, 0} , 0, 0, 0, 0};
  aux = (pRegisto) malloc (sizeof (noRegisto));

  if (aux != NULL) {
    aux->registo = registo;
    aux->prox = NULL;
  }
  return aux;
}

void registo_carregar(pRegisto raiz) {
  FILE *ficheiro = fopen("registos.txt", "r");
  if (ficheiro == NULL) {
    return;
  }
  char clr;
  Registo registo;
  while (fscanf(ficheiro, "%d", &registo.id) == 1) {
    fscanf(ficheiro, "%c", &clr);
    printf("ID: %d\n", registo.id);
    char data_text[14];
    if (fgets(data_text, 14, ficheiro) == NULL) break;
    Data dt = {atoi(strtok(data_text, "/")), atoi(strtok(NULL, "/")), atoi(strtok(NULL, "/"))};
    registo.data = dt;
    printf("Data: %d/%d/%d\n", registo.data.dia, registo.data.mes, registo.data.ano);
    fscanf(ficheiro, "%lf%lf%lf%lf", &registo.tensao_maxima, &registo.tensao_minima, &registo.peso, &registo.altura);
    registo_insere(raiz, registo);
    printf("Registo carregado: %d\n", registo.id);      
  } ; 
  if (fclose(ficheiro) != 0) {
    printf("Erro ao fechar o ficheiro!\n");
  }
}

void registo_guardar(pRegisto raiz) {
  FILE *ficheiro = fopen("registos.txt", "w");
  if (ficheiro == NULL) {
    return;
  }
  pRegisto aux = raiz->prox;
  while (aux != NULL) {
    Registo registo = aux->registo;
    fprintf(ficheiro, "%d\n%d/%d/%d\n%lf\n%lf\n%lf\n%lf\n", registo.id, registo.data.dia, registo.data.mes, registo.data.ano, registo.tensao_maxima, registo.tensao_minima, registo.peso, registo.altura);
    printf("Registo escrito: %d\n", registo.id);  
    aux = aux->prox;
  }
  if (fclose(ficheiro) != 0) {
    printf("Erro ao fechar o ficheiro!\n");
  }
}

void registo_destroi (pRegisto raiz){
  pRegisto temp_ptr;
  while (!registo_vazia(raiz)) {
    temp_ptr = raiz;
    raiz = raiz->prox;
    free (temp_ptr);
  }
  free(raiz);
}

int registo_vazia (pRegisto raiz) {
  return raiz->prox == NULL;
}

void registo_procura(pRegisto raiz, int chave, pRegisto* anterior, pRegisto* atual){
  *anterior = raiz; 
  *atual = raiz->prox;
  while ((*atual) != NULL && (*atual)->registo.tensao_maxima > chave) {
    *anterior = *atual;
    *atual = (*atual)->prox;
  }
  if ((*atual) != NULL && (*atual)->registo.tensao_maxima != chave) {
    *atual = NULL;
  }
}

void registo_insere(pRegisto raiz, Registo registo) {
  pRegisto no, anterior, inutil;
  no = (pRegisto) malloc (sizeof (noRegisto));
  if (no != NULL) {
    registo_procura(raiz, registo.tensao_maxima, &anterior, &inutil);
    no->registo = registo;
    no->prox = anterior->prox;
    anterior->prox = no;
  }
} 

void registo_listar_tensoes_max(pDoente raiz_doente, pRegisto raiz, int n) {
  int *done = calloc(10000, sizeof(int));
  pRegisto temp_ptr = raiz->prox;
  while (temp_ptr != NULL && temp_ptr->registo.tensao_maxima >= n) {
    if (!done[temp_ptr->registo.id]) {
      done[temp_ptr->registo.id] = 1;
      char nome[TAM_NOME];
      pDoente aux = raiz_doente->prox;
      while (aux) {
        if (aux->doente.id == temp_ptr->registo.id) {
          strcpy(nome, aux->doente.nome);
          break;
        }
        aux = aux->prox;
      }
      printf("Doente: %s\nTensão máxima: %lf\n", nome, temp_ptr->registo.tensao_maxima);
    }
    temp_ptr = temp_ptr->prox;
  }
  free(done);
} 

void registo_listar_doente(pRegisto raiz, size_tt id) {
  pRegisto temp_ptr = raiz;
  while (temp_ptr != NULL) {
    Registo registo_doente = temp_ptr->registo;
    if (registo_doente.id == id) {
      printf("Data: %d/%d/%d\nPeso: %lf\nAltura: %lf\nTensão máxima: %lf\nTensão mínima: %lf\n", registo_doente.data.dia, registo_doente.data.mes, registo_doente.data.ano, registo_doente.peso, registo_doente.altura, registo_doente.tensao_maxima, registo_doente.tensao_minima);
      return;
    }
    temp_ptr = temp_ptr->prox;
  }
  printf("Esse doente não tem nenhum registo.\n");
}
