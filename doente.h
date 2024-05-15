/* ID do doente 
 * Nome 
 * Email 
 * Cartão de cidadão 
 * Data de nascimento 
 * Telefone 
 */
#include "tipos.h"

#define TAM_EMAIL 255
#define TAM_NOME 255
#define TAM_CC 16

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

pDoente doente_criar();
void doente_carregar(pDoente raiz);
void doente_guardar(pDoente raiz);
void doente_destroi(pDoente raiz);
int doente_vazia(pDoente raiz);
size_tt doente_obter_id(pDoente raiz);
void doente_insere(pDoente raiz, Doente doente);
void doente_retira(pDoente raiz, size_tt id);
void doente_procura(pDoente raiz, size_tt id, pDoente *ant, pDoente *act);
void doente_info(pDoente raiz, size_tt id);
void doente_listar_ordem_alfabetica(pDoente raiz); 
