#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"
#include "doente.h"
#include "registo.h"

int main() {
  pDoente doentes = doente_criar();
  doente_carregar(doentes);
  pRegisto registos = registo_criar();
  registo_carregar(registos);
  char input, clr;
  while (input != 'Q') {
    printf("Escolha uma opção:\n  A) Introduzir dados de um novo doente\n  B) Eliminar um doente existente\n  C) Listar todos os doentes por ordem alfabética\n  D) Listar os doentes com tensões máximas acima de um determinado valor (por ordem decrescente das mesmas)\n  E) Apresentar toda a informação de um determinado doente\n  F) Registar as tensões, o peso e a altura de um determinado doente num determinado dia\n  Q) Sair do programa\n");
    scanf("%c", &input);
    switch (input) {
      case 'A': {
        Doente doente;
        doente.id = 0;
        printf("Insira o nome do doente: ");
        scanf("%c", &clr);
        fgets(doente.nome, TAM_NOME, stdin);
        while (!validar_nome(doente.nome)) {
          printf("Nome inválido! Tente novamente: ");
          fgets(doente.nome, TAM_NOME, stdin);
        } 
        doente.nome[strlen(doente.nome)-1] = '\0';
        printf("Insira o email do doente: ");
        fgets(doente.email, TAM_EMAIL, stdin);
        while (!validar_email(doente.email)) {
          printf("Email inválido! Tente novamente: ");
          fgets(doente.email, TAM_EMAIL, stdin);
        } 
        doente.email[strlen(doente.email)-1] = '\0';
        printf("Insira o cartão de cidadão do doente: ");
        fgets(doente.cc, TAM_CC, stdin);
        while (!validar_cc(doente.cc)) {
          printf("Cartão de cidadão inválido! Tente novmente: ");
          fgets(doente.cc, TAM_CC, stdin);
        } 
        doente.cc[strlen(doente.cc)-1] = '\0';
        printf("Insira a data de nascimento do doente.\n");
        ler_data(&doente.data);
        printf("Insira o número de telefone do doente: ");
        scanf("%d",&doente.telefone);
        while (!validar_telefone(doente.telefone)) {
          printf("Número de telefone inválido! Tente novmente: ");
          scanf("%d",&doente.telefone);
        } 
        doente_insere(doentes, doente);
        doente_guardar(doentes);
        break;
      }
      case 'B': {
        int id;
        printf("Insira o ID do doente que pretende eliminar: ");
        scanf("%d", &id);
        doente_retira(doentes, id);
        doente_guardar(doentes);
        break;
      }
      case 'C': {
        printf("Lista de doentes por ordem alfabética:\n");
        doente_listar_ordem_alfabetica(doentes);
        break;
      }
      case 'D': {
        int tensao;
        printf("Insira o valor de tensão mínimo pelo qual quer listar os doentes: ");
        scanf("%d", &tensao);
        registo_listar_tensoes_max(registos, tensao);
        break;
      }
      case 'E': {
        int id;
        printf("Insira o ID do doente que pretende ver as informações: ");
        scanf("%d", &id);
        printf("Informações do doente:\n");
        doente_info(doentes, id);
        printf("Registos do doente:\n");
        registo_listar_doente(registos, id);
        break;
      }

      case 'F': {
        Registo registo;
        printf("Insira o ID do doente deste registo: ");
        scanf("%d", &registo.id);
        printf("Insira a data do registo.\n");
        ler_data(&registo.data);
        printf("Insira a tensão mínima do doente: ");
        scanf("%lf",&registo.tensao_minima);
        printf("Insira a tensão máxima do doente: ");
        scanf("%lf",&registo.tensao_maxima);
        printf("Insira o peso do doente: ");
        scanf("%lf",&registo.peso);
        printf("Insira a altura do doente: ");
        scanf("%lf",&registo.altura);
        printf("O registo foi adicionado!\n");
        registo_insere(registos, registo);
        registo_guardar(registos);
        break;
      }
    }
    scanf("%c", &clr);
  }
  registo_destroi(registos);
  doente_destroi(doentes);
  return 0;
}
