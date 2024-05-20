// Comum
#ifndef TIPOS_H
#define TIPOS_H
#include <stdio.h>
typedef unsigned int size_tt; 
typedef struct Data {
  int dia, mes, ano;
} Data;
#endif

// Registos
#ifndef REGISTOS_H
#define REGISTOS_H
typedef struct Registo {
  size_tt id;
  Data data; 
  double tensao_minima, tensao_maxima, peso, altura;
} Registo;
typedef struct noRegisto{
  struct Registo registo;
  struct noRegisto* prox;
} noRegisto;
typedef noRegisto* pRegisto;
#endif

// Doentes
#ifndef DOENTES_H
#define TAM_EMAIL 255
#define TAM_NOME 255
#define TAM_CC 16
#define DOENTES_H
typedef struct Doente {
  char nome[TAM_EMAIL];
  size_tt id;
  char email[TAM_EMAIL];
  char cc[TAM_CC];
  Data data;       
  size_tt telefone;
} Doente;
typedef struct noDoente {
  struct Doente doente;
  struct noDoente* prox;
  struct noDoente* prox_alfabetica;
} noDoente;
typedef struct noDoente* pDoente;
#endif

void limpar_buffer(FILE *stream);
void ler_data(Data *data);
int validar_email(char *input);
int validar_nome(char *input);
int validar_cc(char *input);
int validar_telefone(int input);
