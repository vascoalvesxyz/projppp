/* ID do doente 
 * Nome 
 * Email 
 * Cartão de cidadão 
 * Data de nascimento 
 * Telefone 
 */
#include "tipos.h"

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
void doente_id_para_nome(pDoente raiz, size_tt id, char *nome);
