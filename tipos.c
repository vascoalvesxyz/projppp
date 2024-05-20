#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "tipos.h"

void limpar_buffer(FILE *stream) {
  char clr;
  do {
    clr = fgetc(stream);
  } while (clr != '\n' && clr != EOF);
}

void ler_data(Data *data) {
  printf("Insira o dia: ");
  while (scanf("%d", &data->dia) != 1 || data->dia>31 || data->dia <= 0) {
    limpar_buffer(stdin);
    printf("Dia inválido. Tente novamente: ");
  }
  printf("Insira o mês: ");
  while (scanf("%d", &data->mes) != 1 || data->mes>12 || data->mes <= 0) {
    limpar_buffer(stdin);
    printf("Mês inválido. Tente novamente: ");
  }
  printf("Insira o ano: ");
  while (scanf("%d", &data->ano) != 1 || data->ano > 2100 || data->ano < 1900 ) {
    limpar_buffer(stdin);
    printf("Ano inválido. Tente novamente: ");
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
  if (strlen(input) != 14) {
    return 0;
  }
  for (int i=0;i<8;i++) {
    if (!isdigit(*input)) {
      return 0;
    }
    input++;
  }
  if (*input != '-') return 0;
  input++;
  if (!isdigit(*input)) return 0;
  input++;
  if (*input != '-') return 0;
  return 1;
}

int validar_telefone(int input) {
  if (input < 200000000 || input > 999999999) {
    return 0;
  }
  return 1;
}
