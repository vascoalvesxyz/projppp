#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doente.h"
#include "registo.h"

int main() {
    pDoente doentes = doente_criar();
    printf("Carregando doentes...\n");
    doente_carregar(doentes);
    printf("Carregando registo...\n");
    pRegisto registos = registo_criar();
    registo_carregar(registos);
    char input, clr;
    while (input != 'Q') {
        printf("Escolha uma opção:\n  A) Introduzir dados de um novo doente\n  B) Eliminar um doente existente\n  C) Listar todos os doentes por ordem alfabética\n  D) Listar os doentes com tensões máximas acima de um determinado valor (por ordem decrescente das mesmas)\n  E) Apresentar toda a informação de um determinado doente\n  F) Registar as tensões, o peso e a altura de um determinado doente num determinado dia\n  Q) Sair do programa\n");
        scanf("%c", &input);
        switch (input) {
            case 'A': {
                          Doente doente;
                          printf("Insira o nome do doente: ");
                          scanf("%c", &clr);
                          fgets(doente.nome, 50, stdin);
                          doente.nome[strlen(doente.nome)-1] = '\0';
                          printf("Insira o email do doente: ");
                          fgets(doente.email, 50, stdin);
                          doente.email[strlen(doente.email)-1] = '\0';
                          printf("Insira o cartão de cidadão do doente: ");
                          fgets(doente.cc, 14, stdin);
                          doente.cc[strlen(doente.cc)-1] = '\0';
                          printf("Insira a data de nascimento do doente: ");
                          fgets(doente.data, 50, stdin);
                          doente.data[strlen(doente.data)-1] = '\0';
                          printf("Insira o número de telefone do doente: ");
                          scanf("%d",&doente.telefone);
                          doente_insere(doentes, doente);
                          break;
                      }
            case 'B': {
                          int id;
                          printf("Insira o ID do doente que pretende eliminar: ");
                          scanf("%d", &id);
                          doente_retira(doentes, id);
                          break;
                      }
            case 'C': {
                          printf("Lista de doentes por ordem alfabética:\n");
                          doente_listar_todos(doentes);
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
                          printf("Insira a data do registo: ");
                          char* data = malloc(50*sizeof(char)); 
                          fgets(data, 50, stdin);
                          registo.data = data;
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
                          break;
                      }
        }
        scanf("%c", &clr);
    }
    registo_destroi(registos);
    free(registos);
    doente_destroi(doentes);
    free(doentes);
    return 0;
}
