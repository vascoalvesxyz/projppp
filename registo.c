#include "registo.h"
#include <stdlib.h>
#include <stdio.h>

pRegisto registo_criar() {
  pRegisto aux;
  Registo registo = { 0, "", 0, 0, 0, 0};
  aux = (pRegisto) malloc (sizeof (noRegisto));

  if (aux != NULL) {
    aux->registo = registo;
    aux->prox = NULL;
  }
  return aux;
}

void registo_carregar(pRegisto r) {
  FILE *f;
  f = fopen("registos.txt", "r");
  if (f == NULL) {
    return;
  }
  Registo registo;
  while (fscanf(f, "%d %s %lf %lf %lf %lf", &registo.id, registo.data, &registo.peso, &registo.altura, &registo.tensao_maxima, &registo.tensao_minima) == 6) {
    registo_insere(r, registo);
  }
  fclose(f);
}

void registo_destroi (pRegisto r){
  pRegisto temp_ptr;
  while (!registo_vazia(r)) {
    temp_ptr = r;
    r = r->prox;
    free (temp_ptr);
  }
  free(r);
}

int registo_vazia (pRegisto r) {
  return r->prox == NULL;
}

void registo_procura(pRegisto lista, int chave, pRegisto* ant, pRegisto* actual){
  *ant = lista; *actual = lista->prox;
  while ((*actual) != NULL && (*actual)->registo.tensao_maxima > chave) {
    *ant = *actual;
    *actual = (*actual)->prox;
  }
  if ((*actual) != NULL && (*actual)->registo.tensao_maxima != chave)
    *actual = NULL;
}

void registo_insere(pRegisto r, Registo registo) {
  pRegisto no, ant, inutil;
  no = (pRegisto) malloc (sizeof (noRegisto));
  if (no != NULL) {
    no->registo = registo;
    registo_procura(r, registo.tensao_maxima, &ant, &inutil);
    no->prox = ant->prox;
    ant->prox = no;
  }
} 

void registo_listar_tensoes_max(pRegisto r, int n) {
  pRegisto temp_ptr = r;
  while (temp_ptr != NULL && temp_ptr->registo.tensao_maxima >= n) {
    printf("Doente: %d\nTensão máxima:%lf\n", temp_ptr->registo.id, temp_ptr->registo.tensao_maxima);
    temp_ptr = temp_ptr->prox;
  }
} 

void registo_listar_doente(pRegisto r, size_tt id) {
  pRegisto temp_ptr = r;
  while (temp_ptr != NULL) {
    Registo registo_doente = temp_ptr->registo;
    if (registo_doente.id == id) {
      printf("Data: %s\nPeso: %lf\nAltura: %lf\nTensão máxima: %lf\nTensão mínima: %lf\n", registo_doente.data, registo_doente.peso, registo_doente.altura, registo_doente.tensao_maxima, registo_doente.tensao_minima);
      return;
    }
    temp_ptr = temp_ptr->prox;
  }
  printf("Não foi encontrado nenhum doente com esse ID.");
}
