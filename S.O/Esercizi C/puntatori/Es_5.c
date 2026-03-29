#include <stdio.h>    // Libreria per input/output (printf)
#include <stdlib.h>   // Libreria per malloc() e free()

/*
Definisci una struttura Node con campo value e puntatore next.
Implementa le funzioni:
 - insert_head: inserisce un nodo in testa alla lista
 - print_list: stampa tutti gli elementi della lista
 - free_list: dealloca la memoria usata dalla lista
*/

// ✅ Definizione della struttura Node
typedef struct Node {
    int value;            // valore contenuto nel nodo
    struct Node* next;    // puntatore al nodo successivo nella lista
} Node;

/*
❓ PERCHÉ usare 'struct Node* next' e poi 'typedef struct Node { ... } Node;'?

In C, quando definisci una struttura, il suo nome "interno" (usato dentro se stessa)
deve essere preceduto da 'struct', perché il tipo 'Node' non è ancora completamente definito.

Il typedef alla fine:
    } Node;
serve solo per creare un ALIAS del tipo completo 'struct Node' → ora posso scrivere 'Node' invece di 'struct Node'.

Quindi:
    struct Node* next;   // uso dentro la definizione (il tipo non è ancora completo)
    Node* p;             // uso fuori, dopo la definizione (grazie al typedef)
*/

// 🔹 Funzione per inserire un nodo in testa alla lista
Node* insert_head(Node* head, int value) {
    // Alloco dinamicamente memoria per un nuovo nodo
    Node* new_node = malloc(sizeof(Node));
    new_node->value = value;  // assegno il valore
    new_node->next = head;    // il nuovo nodo punta all’attuale testa

    // Aggiorno la testa: ora la testa della lista è il nuovo nodo
    return new_node;
    return head; // questa linea non verrà mai eseguita
}

// 🔹 Funzione per stampare tutti gli elementi della lista
void print_list(Node* head) {
    Node* current = head;        // puntatore temporaneo per scorrere la lista
    while (current != NULL) {    // ciclo fino a quando non arrivo alla fine (NULL)
        printf("%d -> ", current->value);
        current = current->next; // passo al nodo successivo
    }
    printf("NULL\n");            // stampa finale che indica la fine della lista
}

// 🔹 Funzione per deallocare tutti i nodi della lista
void free_list(Node* head) {
    Node* current = head;  // puntatore per attraversare la lista
    Node* next;            // puntatore temporaneo al nodo successivo

    // Scorro la lista liberando ogni nodo
    while (current != NULL) {
        next = current->next; // salvo l’indirizzo del nodo successivo
        free(current);        // libero la memoria del nodo corrente
        current = next;       // passo al prossimo nodo
    }
}

// funzione di deallocazione ricorsiva (alternativa a free_list)
void free_list_recursive(Node* head) {
    if (head == NULL) return; // caso base: lista vuota
    free_list_recursive(head->next); // libera il resto della lista
    free(head); // libera il nodo corrente
}

int main() {
    Node* head = NULL;  // lista vuota all’inizio (nessun nodo)

    // Inserisco tre nodi in testa (l'ultimo inserito diventa la nuova testa)
    head=insert_head(head, 10);  // lista: 10 -> NULL
    head=insert_head(head, 20);  // lista: 20 -> 10 -> NULL
    head=insert_head(head, 30);  // lista: 30 -> 20 -> 10 -> NULL

    // Stampa la lista collegata
    printf("Lista collegata: ");
    print_list(head);

    // Libero la memoria occupata dalla lista
    free_list_recursive(head);
    head = NULL;  // buona pratica: azzero il puntatore dopo il free

    // Stampo la lista dopo la deallocazione (sarà vuota)
    print_list(head); // stampa: NULL

    return 0; // fine programma
}
