/* ID do doente 
 * Data do registo 
 * Tensão máxima 
 * Tensão mínima 
 * Peso
 * Altura 
*/
#include "tipos.h"

typedef struct Registo {
    size_tt id;
    Data data; 
    double tensao_minima;
    double tensao_maxima;
    double peso;
    double altura;
} Registo;

typedef struct noRegisto{
    struct Registo registo;
    struct noRegisto* prox;
} noRegisto;

typedef noRegisto* pRegisto;

pRegisto registo_criar(); 
void registo_carregar(pRegisto raiz);
void registo_guardar(pRegisto raiz);
void registo_destroi(pRegisto raiz); 
int registo_vazia(pRegisto raiz); 
void registo_insere(pRegisto raiz, Registo registo); 
void registo_listar_tensoes_max(pRegisto raiz, int n); 
void registo_listar_doente(pRegisto raiz, size_tt id);


