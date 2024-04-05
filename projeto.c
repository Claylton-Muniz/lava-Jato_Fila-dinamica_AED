#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct No {
    int info;
    struct No* prox;
} No; // estrutura de um nó

typedef struct {
    No* f;
    No* r;
    int size;
} Fila; // estrutura da fila



No* criarNo(int valor) {
    No* no = (No*)malloc(sizeof(No)); // criando um nó

    no->info = valor;
    no->prox = NULL;

    return no; // criando um nó e suas infos
}

void imprimirFila(Fila* f) {
    No* temp = f->f;
    while (temp != NULL) {
        printf("%d - ", temp->info);
        temp = temp->prox;
    }
    printf("\n");
}

Fila* criarFilaDin() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));   // criando um nó para apontar

    fila->f = NULL;                             // para o inicio
    fila->r = NULL;                             // para o fim
    fila->size = 0;                             // indica o tamanho da fila

    return fila;
}

Fila* insersaoFila(Fila* f, int value, int k) {
    if (f->size < k) {
        No* no = criarNo(value);
        if (f->r != NULL) {
            f->r->prox = no;
        } else {
            f->f = no;
        }
        f->r = no;
        f->size++;
    } else {
        printf("Volte mais tarde já atinjimos nossa capacidade \n");
    }
    
    return f;
}

Fila* remocaoFila(Fila* f) {
    // e se não tiver mais um cara para remover?
    No* pt = f->f;
    f->f = f->f->prox;
    if (f->f == NULL) {
        f->r = NULL;
    }
    free(pt);
    f->size--;

    return f;
}

int lavaJato(char *v, int n, int k) {

    Fila* f = criarFilaDin();
    int lavados = 0;
    int temp_ini = 0;

    printf("\n");

    for (int i = 0; i < n; i++) {
        if (v[i] == '0') {
            if (f->f != NULL) {
                if (temp_ini == 3) {
                    f = remocaoFila(f);
                    temp_ini = 0;
                    lavados++;
                } else {
                    temp_ini++;
                }
            }
        } else {
            if (temp_ini == 3) {
                f = remocaoFila(f);
                temp_ini = 0;
                lavados++;
                f = insersaoFila(f, 1, k);
            } else {
                f = insersaoFila(f, 1, k);
                temp_ini++;
            }
        } 
    }

    return lavados;
}

int main(int argc, char const *argv[])
{
    // permitindo caracteres UTF-8 no windows
    SetConsoleOutputCP(CP_UTF8);

    char *v = NULL; // vetor binario
    int n;

    v = (char*)malloc(50 * sizeof(char));

    do
    {
        printf("Diga seu vetor binário: ");
        scanf("%s", v);
        n = strlen(v);
    } while (n < 1); // n >= 1

    // Redimensiona o espaço alocado para o vetor
    v = (char*)realloc(v, n * sizeof(char));

    int k;

    do
    {
        printf("Capacidade máxima de atendimentos: ");
        scanf("%d", &k);
    } while (k < 0);
    
    int lavados = lavaJato(v, n, k);

    printf("\nForam lavados %d carros durante esse dia", lavados);
    
    return 0;
}
