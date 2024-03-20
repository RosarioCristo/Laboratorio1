#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_ID_LENGTH 50

// Estrutura para representar uma tarefa
typedef struct Task {
    char id[MAX_ID_LENGTH];
    int priority;
    struct Task *next;
} Task;

// Array de ponteiros para listas de tarefas, uma lista para cada prioridade
Task *task_lists[6] = {NULL};

// Função para criar uma nova tarefa
void new_task(int priority, char *id) {
    if (priority < 0 || priority > 5) {
        printf("Prioridade inválida.\n");
        return;
    }

    Task *new_task = (Task *)malloc(sizeof(Task));
    if (new_task == NULL) {
        printf("Erro ao alocar memória para nova tarefa.\n");
        return;
    }

    strcpy(new_task->id, id);
    new_task->priority = priority;
    new_task->next = NULL;

    // Inserindo a nova tarefa na lista correspondente à sua prioridade
    if (task_lists[priority] == NULL) {
        task_lists[priority] = new_task;
    } else {
        Task *current = task_lists[priority];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_task;
    }
}

// Função para listar tarefas com prioridade igual ou superior à especificada
void list_tasks(int priority) {
    if (priority < 0 || priority > 5) {
        printf("Prioridade inválida.\n");
        return;
    }

    printf("Tarefas com prioridade %d ou superior:\n", priority);
    for (int i = priority; i <= 5; i++) {
        Task *current = task_lists[i];
        while (current != NULL) {
            printf("Prioridade: %d, ID: %s\n", current->priority, current->id);
            current = current->next;
        }
    }
}

// Função para completar uma tarefa
void complete_task(char *id) {
    for (int i = 0; i <= 5; i++) {
        Task *current = task_lists[i];
        Task *prev = NULL;
        while (current != NULL) {
            if (strcmp(current->id, id) == 0) {
                // Tarefa encontrada, remover da lista
                if (prev == NULL) {
                    task_lists[i] = current->next;
                } else {
                    prev->next = current->next;
                }
                free(current);
                return;
            }
            prev = current;
            current = current->next;
        }
    }
    printf("TAREFA INEXISTENTE\n");
}

// Função para liberar memória alocada para todas as tarefas
void cleanup() {
    for (int i = 0; i <= 5; i++) {
        Task *current = task_lists[i];
        while (current != NULL) {
            Task *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    char command[10], id[MAX_ID_LENGTH];
    int priority;

    while (1) {
        printf("\nComando (new, list, complete): ");
        scanf("%s", command);

        if (strcmp(command, "new") == 0) {
            scanf("%d %s", &priority, id);
            new_task(priority, id);
        } else if (strcmp(command, "list") == 0) {
            scanf("%d", &priority);
            list_tasks(priority);
        } else if (strcmp(command, "complete") == 0) {
            scanf("%s", id);
            complete_task(id);
        } else {
            printf("Comando inválido.\n");
        }
    }

    cleanup();
    return 0;
}
