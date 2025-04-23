#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int id;
    char nome[MAX];
    char descricao[MAX];
    int concluida; // 0 = não concluida, 1 = concluida
} Tarefa;

 void cadastrarTarefa()
{   
    char linha[400];
    FILE *pont_arq;
    int r;
    Tarefa t;
    
    /*printf("Insira o id da tarefa: ");
    scanf("%d", &t.id);
    while(getchar() != '\n');*/

    int i;

    FILE *leitura_arq = fopen("tarefas.txt", "r");
    t.id = 1;

    if (leitura_arq != NULL)
    {
        Tarefa temp;
        char linha_lida[400];

        while (fgets(linha_lida, sizeof(linha_lida), leitura_arq)){
            sscanf(linha_lida, "%d;[^;];[^;];%d", &temp.id, temp.nome, temp.descricao, &temp.concluida);
            if (temp.id >= t.id){
                t.id = temp.id + 1;
            }
        }
        fclose(leitura_arq);
    }

    pont_arq = fopen("tarefas.txt", "a");

    if(pont_arq == NULL){
        printf("Erro ao tentar abrir o arquivo!\n");
        exit(1);
    }
    
    printf("Insira o nome da tarefa: ");
    fgets(t.nome, MAX, stdin);
    t.nome[strcspn(t.nome, "\n")] = 0;

    printf("Insira a descricao da tarefa: ");
    fgets(t.descricao, MAX, stdin);
    t.descricao[strcspn(t.descricao, "\n")] = 0;

    t.concluida = 0;
    sprintf(linha,"%d;%s;%s;%d\n", t.id, t.nome, t.descricao, t.concluida);
    r = fputs(linha, pont_arq);

    if(r == EOF){
        printf("\nErro ao tentar gravar os dados\n");
    } else {
        printf("\ndados gravados com sucesso\n");
    }
    fclose(pont_arq);
}

void listarTarefas()
{
    char linha[400];
    FILE *pont_arq;
    Tarefa tarefa_lida;
    
    pont_arq = fopen("tarefas.txt", "r");

    if(pont_arq == NULL){
        printf("Erro ao tentar abrir o arquivo!\n");
        return;
    }

    printf("\nTarefas cadastradas:\n");
    while ((fgets(linha, MAX, pont_arq) != NULL)){
        sscanf(linha, "%d;%[^;];%[^;];%d", &tarefa_lida.id, tarefa_lida.nome, &tarefa_lida.descricao, &tarefa_lida.concluida);

        printf("\nID: %d\n", tarefa_lida.id);
        printf("Nome: %s\n", tarefa_lida.nome);
        printf("Descrição: %s\n", tarefa_lida.descricao);
        printf("Concluida: %s\n", tarefa_lida.concluida ? "SIM" : "NAO");
    }
    
    
    fclose(pont_arq);

}


int main()
{
    int opcao;

    do{
        printf("\n***MENU***\n");
        printf("1- CADASTRAR TAREFA\n");
        printf("2- LISTAR TAREFAS\n");
        printf("3- SAIR\n");
        printf("ESCOLHA UMA OPCAO:\n");
        scanf("%d", &opcao);
        while(getchar() != '\n');

        switch (opcao){
            case 1:
                cadastrarTarefa();
                break;

            case 2:
                listarTarefas();
                break;

            case 3:
                printf("SAINDO... ");
                break;

            default:
                printf("opcao invalida\n");
        }
    } while(opcao != 3);

        return 0;
}
