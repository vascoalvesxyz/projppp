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
  Registo registo;
  do {
    fscanf(ficheiro, "%d", &registo.id);
    printf("ID: %d\n", registo.id);
    int clr;
    fscanf(ficheiro, "%d", &clr);
    char data_text[12];
    if (fgets(data_text, 12, ficheiro) == NULL) break;
    Data dt = {atoi(strtok(data_text, "/")), atoi(strtok(NULL, "/")), atoi(strtok(NULL, "/"))};
    registo.data = dt;
    scanf("%lf%lf%lf%lf", &registo.tensao_maxima, &registo.tensao_minima, &registo.peso, &registo.altura);
    registo_insere(raiz, registo);
    printf("Registo carregado: %d\n", registo.id);      
  } while (registo.id != 0); 
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

void registo_listar_tensoes_max(pRegisto raiz, int n) {
  pRegisto temp_ptr = raiz;
  while (temp_ptr != NULL && temp_ptr->registo.tensao_maxima >= n) {
    printf("registo: %d\nTensão máxima:%lf\n", temp_ptr->registo.id, temp_ptr->registo.tensao_maxima);
    temp_ptr = temp_ptr->prox;
  }
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
