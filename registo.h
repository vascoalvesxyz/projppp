/* ID do doente 
 * Data do registo 
 * Tensão máxima 
 * Tensão mínima 
 * Peso
 * Altura 
*/

typedef unsigned int size_tt ; 

typedef struct Registo {
    size_tt id;
    char* data; 
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
void registo_carregar(pRegisto r);
void registo_destroi(pRegisto r); 
int registo_vazia(pRegisto r); 
void registo_insere(pRegisto r, Registo registo); 
void registo_listar_tensoes_max(pRegisto r, int n); 
void registo_listar_doente(pRegisto r, size_tt id);


