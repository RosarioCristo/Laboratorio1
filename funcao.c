#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int pid;
    int end_time;
    struct Process *next;
} Process;

// Função para atualizar o tempo de fim de um processo com um determinado pid
void update_terminated_process(Process *head, int pid, int end_time) {
    Process *current = head;
    
    // Percorre a lista em busca do processo com o pid dado
    while (current != NULL) {
        if (current->pid == pid) {
            // Atualiza o tempo de fim do processo
            current->end_time = end_time;
            return;
        }
        current = current->next;
    }
    
    // Se o processo não for encontrado
    printf("Processo com PID %d não encontrado.\n", pid);
}

// Função auxiliar para imprimir os elementos da lista
void print_list(Process *head) {
    Process *current = head;
    while (current != NULL) {
        printf("PID: %d, Tempo de Fim: %d\n", current->pid, current->end_time);
        current = current->next;
    }
}

// Função principal para testar a função update_terminated_process
int main() {
    // Criando alguns processos para teste
    Process *head = malloc(sizeof(Process));
    head->pid = 101;
    head->end_time = 0;
    head->next = malloc(sizeof(Process));
    head->next->pid = 202;
    head->next->end_time = 0;
    head->next->next = malloc(sizeof(Process));
    head->next->next->pid = 303;
    head->next->next->end_time = 0;
    head->next->next->next = NULL;
    
    printf("Lista de processos antes da atualização:\n");
    print_list(head);
    
    // Atualizando o tempo de fim do processo com PID 202
    update_terminated_process(head, 202, 10);
    
    printf("\nLista de processos depois da atualização:\n");
    print_list(head);
    
    // Liberando a memória alocada para os processos
    while (head != NULL) {
        Process *temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}
