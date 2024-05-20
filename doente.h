#include "tipos.h"

pDoente doente_criar();
void doente_carregar(pDoente raiz);
void doente_guardar(pDoente raiz);
void doente_destroi(pDoente raiz);
int doente_vazia(pDoente raiz);
size_tt doente_obter_id(pDoente raiz);
void doente_insere(pDoente raiz, Doente doente);
void doente_retira(pDoente raiz, size_tt id);
void doente_procura(pDoente raiz, size_tt id, pDoente *anterior, pDoente *atual);
void doente_info(pDoente raiz, size_tt id);
void doente_listar_ordem_alfabetica(pDoente raiz); 
Doente doente_id_para_doente(pDoente raiz, size_tt id);
