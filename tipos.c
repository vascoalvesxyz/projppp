#include <stdio.h>
#include "tipos.h"

void ler_data(Data *data) {
  printf("Insira o dia: ");
  scanf("%d", &data->dia);
  while (data->dia>31 || data->dia <= 0) {
    printf("Dia inválido. Tente novamente: ");
    scanf("%d", &data->dia);
  }
  printf("Insira o mês: ");
  scanf("%d", &data->mes);
  while (data->mes>12 || data->mes <= 0) {
    printf("Mês inválido. Tente novamente: ");
    scanf("%d", &data->mes);
  }
  printf("Insira o ano: ");
  scanf("%d", &data->ano);
  while (data->ano < 1900 ) {
    printf("Ano inválido. Tente novamente: ");
    scanf("%d", &data->ano);
  }
}

int validar_email(char *input) {
  return 1;
}

int validar_nome(char *input) {
  return 1;
}

int validar_cc(char *input) {
  return 1;
}

int validar_telefone(int input) {
  return 1;
}
