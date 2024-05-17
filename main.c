#include <stdio.h>

#include "tipos.h"
#include "doente.h"
#include "registo.h"

int main() {
  pDoente doentes = doente_criar();
  doente_carregar(doentes);
  pRegisto registos = registo_criar();
  registo_carregar(registos);
  char input;
  while (input != 'Q') {
    printf("Escolha uma opção:\n  A) Introduzir dados de um novo doente\n  B) Eliminar um doente existente\n  C) Listar todos os doentes por ordem alfabética\n  D) Listar os doentes com tensões máximas acima de um determinado valor (por ordem decrescente das mesmas)\n  E) Apresentar toda a informação de um determinado doente\n  F) Registar as tensões, o peso e a altura de um determinado doente num determinado dia\n  Q) Sair do programa\n");
    scanf("%c", &input);
    switch (input) {
      case 'A': {
        Doente doente;
        doente.id = 0;
        printf("Insira o nome do doente: ");
        limpar_buffer();
        fgets(doente.nome, TAM_NOME, stdin);
        while (!validar_nome(doente.nome)) {
          printf("Nome inválido! Tente novamente: ");
          fgets(doente.nome, TAM_NOME, stdin);
        } 
        printf("Insira o email do doente: ");
        fgets(doente.email, TAM_EMAIL, stdin);
        while (!validar_email(doente.email)) {
          printf("Email inválido! Tente novamente: ");
          fgets(doente.email, TAM_EMAIL, stdin);
        } 
        printf("Insira o cartão de cidadão do doente: ");
        fgets(doente.cc, TAM_CC, stdin);
        while (!validar_cc(doente.cc)) {
          printf("Cartão de cidadão inválido! Tente novamente: ");
          fgets(doente.cc, TAM_CC, stdin);
        } 
        printf("Insira a data de nascimento do doente.\n");
        ler_data(&doente.data);
        printf("Insira o número de telefone do doente: ");
        while (scanf("%d",&doente.telefone) != 1 || !validar_telefone(doente.telefone)) {
          limpar_buffer();
          printf("Número de telefone inválido! Tente novamente: ");
        } 
        doente_insere(doentes, doente);
        doente_guardar(doentes);
        break;
      }
      case 'B': {
        int id;
        printf("Insira o ID do doente que pretende eliminar: ");
        while (scanf("%d", &id) != 1 || doente_id_para_doente(doentes, id).id == 0) {
          limpar_buffer();
          printf("Doente não encontrado! Tente novamente: ");
        }
        printf("Doente %s eliminado!\n", doente_id_para_doente(doentes, id).nome);
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
        double tensao;
        printf("Insira o valor de tensão mínimo pelo qual quer listar os doentes: ");
        while (scanf("%lf", &tensao) != 1 || tensao <= 0 || tensao >= 200) {
          limpar_buffer();
          printf("Valor inválido! Tente novamente: ");
        }
        registo_listar_tensoes_max(doentes, registos, tensao);
        break;
      }
      case 'E': {
        int id;
        printf("Insira o ID do doente que pretende ver as informações: ");
        while (scanf("%d", &id) != 1 || doente_id_para_doente(doentes, id).id == 0) {
          limpar_buffer();
          printf("Doente não encontrado! Tente novamente: ");
        }
        printf("Informações do doente:\n");
        doente_info(doentes, id);
        printf("Registos do doente:\n");
        registo_listar_doente(registos, id);
        break;
      }

      case 'F': {
        Registo registo;
        printf("Insira o ID do doente deste registo: ");
        while (scanf("%d", &registo.id) != 1 || doente_id_para_doente(doentes, registo.id).id == 0) {
          limpar_buffer();
          printf("Doente não encontrado! Tente novamente: ");
        }
        printf("Insira a data do registo.\n");
        ler_data(&registo.data);
        printf("Insira a tensão mínima do doente: ");
        while (scanf("%lf", &registo.tensao_minima) != 1 || registo.tensao_minima <= 0 || registo.tensao_minima >= 200) {
          limpar_buffer();
          printf("Valor inválido! Tente novamente: ");
        }
        printf("Insira a tensão máxima do doente: ");
        while (scanf("%lf", &registo.tensao_maxima) != 1 || registo.tensao_maxima < registo.tensao_minima || registo.tensao_maxima >= 200) {
          limpar_buffer();
          printf("Valor inválido! Tente novamente: ");
        }
        printf("Insira o peso do doente: ");
        while (scanf("%lf", &registo.peso) != 1 || registo.peso <= 0 || registo.peso >= 500) {
          limpar_buffer();
          printf("Valor inválido! Tente novamente: ");
        }
        printf("Insira a altura do doente: ");
        while (scanf("%lf", &registo.altura) != 1 || registo.altura <= 0 || registo.altura >= 3) {
          limpar_buffer();
          printf("Valor inválido! Tente novamente: ");
        }
        printf("O registo foi adicionado!\n");
        registo_insere(registos, registo);
        registo_guardar(registos);
        break;
      }
    }
    limpar_buffer();
  }
  registo_destroi(registos);
  doente_destroi(doentes);
  return 0;
}
