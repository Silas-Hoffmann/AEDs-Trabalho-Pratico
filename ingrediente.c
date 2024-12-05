#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ingrediente.h"
#include "pizza.h"

//-----------------------------------------------------------------

void igArquivoParaStruct (struct ingredientes *ingrediente) {
	FILE* ig = fopen ("ingredientesGlobais","r");
	if (ig == NULL) {
		printf ("erro na leitura de ingredientes globais");
	}

	int quantidadeIG;
	fscanf(ig,"%d",&quantidadeIG);//le a quantidade de ingredientes globais

	for (int i=0; i<quantidadeIG; i++) {
		fscanf(ig,"%d",&ingrediente[i].id);
		fgetc(ig);
        
		fgets(ingrediente[i].nome,sizeof(ingrediente[i].nome),ig);
		ingrediente[i].nome[strcspn(ingrediente[i].nome,"\n")]='\0';
        
		fscanf (ig,"%f",&ingrediente[i].preco);
		fgetc(ig);
	}
} //passa as informacoes do arquivo de ingredientes globais para o struct de ingredientes

void igStructParaArquivo (struct ingredientes *ingrediente, int* quantidadeIG) {
    
    FILE* novoIG = fopen ("NovoIngGlob","w+");
	if (novoIG == NULL) {
		printf ("erro do novo cardapio");
	}

	fprintf(novoIG,"%d\n",*quantidadeIG);
	for (int i=0; i<*quantidadeIG; i++) {
		fprintf(novoIG,"%d\n",ingrediente[i].id);
		fprintf(novoIG,"%s\n",ingrediente[i].nome);
		fprintf(novoIG,"%.2f\n",ingrediente[i].preco);
	}

	fclose(novoIG);
	remove("ingredientesGlobais");
	rename("NovoIngGlob","ingredientesGlobais");

} //passa informacoes do struct de ingredientes para o arquivo de ingredientes globais

//-----------------------------------------------------------------