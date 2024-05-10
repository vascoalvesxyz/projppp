/* ID do doente 
 * Nome 
 * Email 
 * Cartão de cidadão 
 * Data de nascimento 
 * Telefone 
*/

#define TRUE    1
#define FALSE   0

typedef unsigned int size_tt ; 

typedef struct Doente {
    char nome[50];
    size_tt id;
    char email[50];
    char cc[14];
    char data[50];       
    size_tt telefone;
} Doente;

typedef struct noDoente {
    struct Doente doente;
    struct noDoente* prox;
} noDoente ;

typedef struct noDoente* pDoente;

pDoente doente_criar();
void doente_carregar(pDoente d);
void doente_destroi(pDoente d);
int doente_vazia(pDoente d);
void doente_insere(pDoente d, Doente doente, int isloading);
void doente_retira(pDoente d, size_tt id);
void doente_procura(pDoente raiz, size_tt id, pDoente *ant, pDoente *act);
void doente_info(pDoente d, size_tt id);
void doente_listar_todos(pDoente d); 
void doentes_update_ficheiro(pDoente raiz);
