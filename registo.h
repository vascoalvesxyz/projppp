#include "tipos.h"

pRegisto registo_criar(); 
void registo_carregar(pRegisto raiz);
void registo_guardar(pRegisto raiz);
void registo_destroi(pRegisto raiz); 
int registo_vazia(pRegisto raiz); 
void registo_procura(pRegisto raiz, int chave, pRegisto *anterior, pRegisto *atual);
void registo_insere(pRegisto raiz, Registo registo); 
void registo_retira(pRegisto raiz, size_tt id);
void registo_procura_id(pRegisto raiz, size_tt id, pRegisto *anterior, pRegisto *atual);
void registo_listar_tensoes_max(pDoente raiz_doente, pRegisto raiz, int n); 
void registo_listar_doente(pRegisto raiz, size_tt id);
int registo_validar_data(Data d_registo, Data d_doente);
