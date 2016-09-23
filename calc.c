#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define MAX 1000
struct pilha
{
    link topo;      /* t é o topo da pilha -- proximo espaco vazio do vetor */
    //int v[MAX]; /* v é o vetor que armazena os elementos da pilha */
};

/* Define um novo tipo de dado chamado Pilha que é um ponteiro para "struct pilha". */
typedef struct pilha * Pilha;

struct celula {
  int item;
  link next;
};
typedef struct celula * link;

Pilha novaPilha () {
  Pilha p;
  p = malloc(sizeof(struct pilha));
  if (p == NULL) {
    printf ("Erro ao alocar meória para a pilha\n");
    exit(-1);
  }
  p->topo = NULL;
  return p;
}

link novoNo (int item, link next) {
  link n = malloc(sizeof(struct celula));
  if(n == NULL) {
    printf ("Erro ao alocar novoNo\n");
    exit(-1);
  }
  n->item = item;
  n->next = next;
  return n;
}

/* Aloca espaço para armazenar uma nova Pilha 
Pilha novaPilha () {
    Pilha p = malloc(sizeof(*p));
    if (p == NULL)
        {
            printf("Algum erro aconteceu !\n");
            exit(-1);
        }
    p->t = 0; //devemos inicializar o topo com 0 
    return p;
}*/

/* Libera memória de uma dada pilha p */
//void destroiPilha (Pilha p)
//{
//   free(p);
//}
void destroiPilha (Pilha p) {
  while(!estaVazia(p)) {
    pop(p);
  }
  free(p);
}


void imprimePilha(Pilha p) {
  link t;
  for (t = p->topo; t != NULL; t = t->next){
    printf ("%c ", t->item);
  }
  printf("\n");b
  return ;
}

#if 0
void push (Pilha p, int item) {
  link t = novoNo(item, NULL);
  if(p->topo == NULL) {
    p->topo = t;
    return;
  }
  t->next = p->topo;
  p->topo = t;
}
#endif

/* Operação de inserir novo elemento na pilha */
//void push (Pilha p, int valor) {
//    p->v[(p->t)++] = valor;
//}
void push (Pilha p, int item) {
  p->topo = novoNo(item, p->topo);
}

/* Operação de remover um elemento da pilha */
//int pop (Pilha p) {
//    return p->v[--(p->t)];
//}
int pop (Pilha p) {
  int aux;
  link t;
  if(p->topo == NULL) {
    printf ("Erro de pilha vazia\n");
    exit(-1);
  }
  aux = p->topo->item;
  t = p->topo;
  p->topo = t->next;
  free (t);
  return aux;
}

/* Operação para pegar o elemento do topo da pilha */
//int topo (Pilha p) {
//    return p->v[p->t - 1];
//}
int pegaTopo(Pilha p) {
  if (p->topo == NULL) {
    printf("A pilha esta vazia\n");
    return 0;
  }
  return p->topo->item;
}

/* Transforma a notação infixa para a notação posfixa */
char * infixoParaPosfixo (char * entrada, char * saida, int t) {
  int i; 
  int j;
  int aux;
  j = 0;
  Pilha p = novaPilha();
  for ( i = 0; entrada[i] != '\0' && (i < 255); i++ ){
    if (entrada[i] >= '0' && entrada[i] <= '9') {
      saida[j++] = entrada[i];
    } else if (entrada[i] == '+' || entrada[i] == '-') {
        
      while(!estaVazia(p)) {
        aux = pegaTopo(p);
        if (aux == '(' ) break;
        pop(p);
        saida[j++] = aux;
      }
      push(p, entrada[i]);

    } else if ( entrada[i] == '*' || entrada[i] == '/') {
      while(!estaVazia(p)) {
        aux = pegaTopo(p);
        if (aux == '(' || aux == '+' || aux == '-') break;
            pop(p);
            saida[j++] = aux;
      }
      push(p, entrada[i]);
    } else if ( entrada[i] == ')' ) {
      while(1) {
	aux = pop(p);
	if (aux == '(') break;
	saida[j++] = aux;
      }
    } else if (entrada[i] == '(' ) {
      push(p, entrada[i]);
    }
  }
  while (!estaVazia(p))
    saida[j++] = pop(p);
  saida[j] = '\0';
  destroiPilha(p);
  return saida;
}

int bemEncaixado (char* s) {
    Pilha p = novaPilha();
    int i;
    int resultado = 1;
    for(i = 0; s[i] != '\0'; i++) {
        if(s[i] == '(') {
            if(p->t >= MAX) {
                resultado = 0;
                break;
            }
            push(p, 1);
        } else if (s[i] == ')') {
            if(p->t <= 0) {
                resultado = 0;
                break;
            }
            pop(p);
        }
    }
    if(p->topo > 0)
        resultado = 0;
    destroiPilha(p);
    return resultado;
}


int calcula (char * s) {
  int i;
  int resp = 0;
  int a, b;
  Pilha p = novaPilha();
  for (i = 0; s[i] != '\0'; i++) {
    if(s[i] >= '0'  && s[i] <= '9') {
      push(p, s[i] - '0');
      continue;
    }
    if (s[i] == '+') {
      a = pop(p);
      b = pop(p);
      push(p, a + b);
    } else if (s[i] == '*') {
      a = pop(p);
      b = pop(p);
      push(p, a * b);
    } else if (s[i] == '-') {
      a = pop(p);
      b = pop(p);
      push (p, b - a); // para testar
    } else if (s[i] == '/') {
      a = pop(p);
      b = pop(p);
      push (p, b/a); // para testar
    }
  }
  resp = pop(p);
  destroiPilha(p);
  return resp;
}



/* Exemplo de utilização */
int main () {
    char infixo[255] ;
    char posfixo[255];
    printf("Sou uma calculadora de inteiros implementado com pilha!\n");
    printf("Digite quit para sair !\n");
    printf ("> ");
    while(fgets(infixo, 255, stdin) != NULL) {
        if(strcmp(infixo, "quit\n") == 0)  {
            printf ("morri !\n");
            return 0;
        }
        if(bemEncaixado(infixo)) {
            infixoParaPosfixo(infixo, posfixo, 255);
            printf("%d\n", calcula(posfixo));
        } else
            printf ("Erro nos parenteses\n");
        printf ("> ");
    }
    return 0;
}
