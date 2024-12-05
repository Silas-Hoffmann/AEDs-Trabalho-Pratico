#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct formatoPizzas {
	int id;
	char nome[50];
	float preco;
	char tamanho;
	int quantidadeIngredientes;
	struct ingredientes ingredientes[15];
}pizza; //struct de pizzas com struct de ingredientes de cada pizza

void leituraStruct(struct formatoPizzas *pizza); //atualiza struct com base no arquivo

void leituraArquivo(struct formatoPizzas *pizza, int* quantidadePizzas); //atualiza arquivo com base no struct

//-----------------------------------------------------------------

void editarIngrediente(struct formatoPizzas *pizza, int* quantidadePizzas,int pos, struct ingredientes *ingrediente, int* quantidadeIG); //editar ingredientes da pizza

void removerIngrediente(struct formatoPizzas *pizza, int* quantidadePizzas,int pos, struct ingredientes *ingrediente, int* quantidadeIG); //remove ingrediente da pizza

void adicionarIngrediente(struct formatoPizzas *pizza, int* quantidadePizzas,int pos, struct ingredientes *ingrediente, int* quantidadeIG); //adiciona novo ingrediente da pizza

//-----------------------------------------------------------------

void exibirCardapio(char tipo,struct formatoPizzas *pizza, int* quantidadePizzas); //exporta cardápio formatado

void exportarCardapio(struct formatoPizzas *pizza, int* quantidadePizzas); //exporta cardápio formatado

//-----------------------------------------------------------------

void removendo(int oqueRemover, struct formatoPizzas *pizza, int* quantidadePizzas); // exclui a pizza desejada

void removerPizza(struct formatoPizzas *pizza, int* quantidadePizzas); // pega informaC'C5es da pizza que deseja exclur

//-----------------------------------------------------------------

void editarPizza(struct formatoPizzas *pizza, int* quantidadePizzas, struct ingredientes *ingrediente, int* quantidadeIG); //edita nome, tamanho e preco

//-----------------------------------------------------------------

void adicionarPizza(struct formatoPizzas *pizza, int* quantidadePizzas, struct ingredientes *ingrediente, int* quantidadeIG);

//-----------------------------------------------------------------

void editarCardapio(struct formatoPizzas *pizza, int* quantidadePizzas, struct ingredientes *ingrediente, int* quantidadeIG); // painel de editar cardapio

//-----------------------------------------------------------------

void processoVenda (struct formatoPizzas *pizza, int* quantidadePizzas);