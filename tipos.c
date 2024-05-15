#include <ctype.h>
#include <stdio.h>
#include <string.h>
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
  input[strlen(input)-1] = '\0';
  char *arroba = strchr(input, '@');
  if (!arroba) return 0;
  char *ponto = strrchr(arroba, '.');
  if (!ponto) return 0;
  if (arroba == input || ponto == arroba + 1 || ponto[1] == '\0') return 0;
  return 1;
}

int validar_nome(char *input) {
  input[strlen(input)-1] = '\0';
  while (*input) {
    if (!isalpha(*input) && *input != ' ') {
      return 0;
    }
    input++;
  }
  return 1;
}

int validar_cc(char *input) {
  input[strlen(input)-1] = '\0';
  printf("len %ld\n", strlen(input));
  if (strlen(input) != 14) {
    printf("lenlth\n");
    return 0;
  }
  for (int i=0;i<8;i++) {
    if (!isdigit(*input)) {
      printf("digit\n");
      return 0;
    }
    input++;
  }
  printf("hifen 1\n");
  if (*input != '-') return 0;
  input++;
  printf("number\n");
  if (!isdigit(*input)) return 0;
  input++;
  printf("hifen 2\n");
  if (*input != '-') return 0;
  return 1;
}

int validar_telefone(int input) {
  if (input < 200000000 || input > 999999999) {
    return 0;
  }
  return 1;
}
