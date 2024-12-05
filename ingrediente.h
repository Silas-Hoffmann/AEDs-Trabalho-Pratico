#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ingredientes {
	int id;
	char nome[50];
	float preco;
}ingredientes; //struct de ingredientes (usado para pizzas e ingredientes globais)
//-----------------------------------------------------------------

void igArquivoParaStruct (struct ingredientes *ingrediente); //passa as informacoes do arquivo de ingredientes globais para o struct de ingredientes

void igStructParaArquivo (struct ingredientes *ingrediente, int* quantidadeIG); //passa informacoes do struct de ingredientes para o arquivo de ingredientes globais

//-----------------------------------------------------------------