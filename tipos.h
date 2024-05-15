#ifndef TIPOS_H
#define TIPOS_H
typedef unsigned int size_tt; 

typedef struct Data {
  int dia, mes, ano;
} Data;
#endif

void ler_data(Data *data);
int validar_email(char *input);
int validar_nome(char *input);
int validar_cc(char *input);
int validar_telefone(int input);
