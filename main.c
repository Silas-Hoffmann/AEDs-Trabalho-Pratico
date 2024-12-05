#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ingrediente.h"
#include "pizza.h"
/*
struct ingredientes {
	int id;
	char nome[50];
	float preco;
}; //struct de ingredientes (usado para pizzas e ingredientes globais)

struct formatoPizzas {
	int id;
	char nome[50];
	float preco;
	char tamanho;
	int quantidadeIngredientes;
	struct ingredientes ingredientes[15];
}; //struct de pizzas com struct de ingredientes de cada pizza


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

void leituraStruct(struct formatoPizzas *pizza) {

	FILE* card = fopen ("cardapio","r");
	if (card == NULL) {
		printf ("erro na leitura de cardapio");
	}

	FILE* ing = fopen ("ingredientes","r");
	if (card == NULL) {
		printf ("erro na leitura de ingredientes");
	}

	int quantidade;
	fscanf(card,"%d",&quantidade);//le a quantidade de pizzas
	//printf ("%d\n",quantidade);//conferencia de dados

	for (int i=0; i<quantidade; i++) {
		fscanf(ing,"%d",&pizza[i].quantidadeIngredientes);//le a quantidade de ingredientes da pizza

		fscanf(card,"%d",&pizza[i].id);
		fgetc(card);

		fgets(pizza[i].nome,sizeof(pizza[i].nome),card);
		pizza[i].nome[strcspn(pizza[i].nome,"\n")]='\0';

		fscanf(card,"%c",&pizza[i].tamanho);
		fgetc(card);

		fscanf (card,"%f",&pizza[i].preco);
		fgetc(card);

		for (int j=0; j<pizza[i].quantidadeIngredientes; j++) {
			fscanf (ing,"%d",&pizza[i].ingredientes[j].id);
			fgetc(ing);

			fgets (pizza[i].ingredientes[j].nome,sizeof(pizza[i].ingredientes[j].nome),ing);
			pizza[i].ingredientes[j].nome[strcspn(pizza[i].ingredientes[j].nome,"\n")]='\0';

			fscanf (ing,"%f",&pizza[i].ingredientes[j].preco);
			fgetc(ing);
		}
	}
} //atualiza struct com base no arquivo

void leituraArquivo(struct formatoPizzas *pizza, int* quantidadePizzas) {
	FILE* novoCard = fopen ("NovoCardapio","w+");
	if (novoCard == NULL) {
		printf ("erro do novo cardapio");
	}
	FILE* novoIng = fopen ("NovoIngredientes","w+");
	if (novoIng == NULL) {
		printf ("erro do novo ingredientes");
	}

	fprintf(novoCard,"%d\n",*quantidadePizzas);
	for (int i=0; i<*quantidadePizzas; i++) {
		fprintf(novoCard,"%d\n",pizza[i].id);
		fprintf(novoCard,"%s\n",pizza[i].nome);
		fprintf(novoCard,"%c\n",pizza[i].tamanho);
		fprintf(novoCard,"%.2f\n",pizza[i].preco);
	}

	for (int i=0; i<*quantidadePizzas; i++) {
		fprintf(novoIng,"%d\n",pizza[i].quantidadeIngredientes);
		for (int j=0; j<pizza[i].quantidadeIngredientes; j++) {
			fprintf(novoIng,"%d\n",pizza[i].ingredientes[j].id);
			fprintf(novoIng,"%s\n",pizza[i].ingredientes[j].nome);
			fprintf(novoIng,"%.2f\n",pizza[i].ingredientes[j].preco);
		}
	}

	fclose(novoCard);
	fclose(novoIng);
	remove("cardapio");
	remove("ingredientes");
	rename("NovoCardapio","cardapio");
	rename("NovoIngredientes","ingredientes");

} //atualiza arquivo com base no struct

//-----------------------------------------------------------------

void editarIngrediente(struct formatoPizzas *pizza, int* quantidadePizzas,int pos, struct ingredientes *ingrediente, int* quantidadeIG){
    char ingdesejado[50];
    printf ("Qual ingrediente deseja editar?\n");
    for (int i=0;i<pizza[pos].quantidadeIngredientes;i++){
        printf ("------------------\n");
        printf("%s\n",pizza[pos].ingredientes[i].nome);
        printf("%.2f\n",pizza[pos].ingredientes[i].preco);
    }
    fgets(ingdesejado,sizeof(ingdesejado),stdin); //pega o ingrediente que vai ser editado
    ingdesejado[strcspn(ingdesejado,"\n")]='\0';
    
    int cnt=0;
    
    for (int i=0;i<pizza[pos].quantidadeIngredientes;i++){
        if (strcmp(pizza[pos].ingredientes[i].nome,ingdesejado)==0){ //se achar o ingrediente a ser editado
            printf ("Digite o novo nome: ");
            fgets(pizza[pos].ingredientes[i].nome,sizeof(pizza[pos].ingredientes[i].nome),stdin); //pega o novo nome para o ingrediente
            pizza[pos].ingredientes[i].nome[strcspn(pizza[pos].ingredientes[i].nome,"\n")]='\0';
            
            for (int k=0;k<*quantidadeIG;k++){
                if (strcmp(pizza[pos].ingredientes[i].nome,ingrediente[k].nome)==0){// se nome digitado == nome de um IG
                    pizza[pos].ingredientes[i].preco=ingrediente[k].preco; //preco do ingrediente == preco do IG
                    pizza[pos].ingredientes[i].id=ingrediente[k].id; //id do ingrediente == id do IG
                }else{ //se for um ingrediente novo
                    cnt=1;
                }
            }
            
            if (cnt=1){ //se for um ingrediente novo
                printf("Ingrediente novo\n");
                
                printf("Digite o preco do ingrediente: RS ");
                scanf ("%f",&pizza[pos].ingredientes[i].preco); //pega o preco do ingrediente
                getchar();
                
                pizza[pos].ingredientes[i].id=1+ingrediente[*(quantidadeIG)-1].id; //cria um novo ID
                
                printf ("Atualizando lista de IG\n");
                //cria um novo IG:
                ingrediente[*quantidadeIG].id=pizza[pos].ingredientes[i].id; //passa o id
                strcpy(ingrediente[*quantidadeIG].nome,pizza[pos].ingredientes[i].nome); //passa o nome
                ingrediente[*quantidadeIG].preco=pizza[pos].ingredientes[i].preco; //passa o preco
                
                *quantidadeIG+=1; //adiciona +1 ao contador de IG
                igStructParaArquivo(ingrediente, quantidadeIG); //atualiza o arquivo de IG com base no Struct
            }
            printf ("Nome alterado\n");
        }
    }
} //editar ingredientes da pizza

void removerIngrediente(struct formatoPizzas *pizza, int* quantidadePizzas,int pos, struct ingredientes *ingrediente, int* quantidadeIG){
    
    char ingdesejado[50];
    printf ("Qual ingrediente deseja remover?\n");
    for (int i=0;i<pizza[pos].quantidadeIngredientes;i++){
        printf ("------------------\n");
        printf("%s\n",pizza[pos].ingredientes[i].nome);
        printf("%.2f\n",pizza[pos].ingredientes[i].preco);
    }
    fgets(ingdesejado,sizeof(ingdesejado),stdin); //pega o ingrediente que vai ser removido
    ingdesejado[strcspn(ingdesejado,"\n")]='\0';

    int posIng=0;
    
    //eu preciso de conferir primeiramente se a pizza dessa posicao realmente tem o ingrediente.
    for (int i=0;i<pizza[pos].quantidadeIngredientes;i++){
        if (strcmp(pizza[pos].ingredientes[i].nome,ingdesejado)==0){//se achar o ingrediente
            posIng=pizza[pos].ingredientes[i].id;
        }
    }
    
    
	FILE* novoIng = fopen ("NovoIngredientes","w+");
	if (novoIng == NULL) {
		printf ("erro do novo ingredientes");
	}

	for (int i=0; i<*quantidadePizzas; i++) {
	    if (i!=pos){ //se nao for a pizza que deseja editar
    		fprintf(novoIng,"%d\n",pizza[i].quantidadeIngredientes);
    		for (int j=0; j<pizza[i].quantidadeIngredientes; j++) {
    			fprintf(novoIng,"%d\n",pizza[i].ingredientes[j].id);
    			fprintf(novoIng,"%s\n",pizza[i].ingredientes[j].nome);
    			fprintf(novoIng,"%.2f\n",pizza[i].ingredientes[j].preco);
    		}
	    }else if (i==pos){ //se for a pizza que deseja editar
	        fprintf(novoIng,"%d\n",pizza[i].quantidadeIngredientes-1);
    		for (int j=0; j<pizza[i].quantidadeIngredientes; j++) {
    		    if (pizza[i].ingredientes[j].id!=posIng){
        			fprintf(novoIng,"%d\n",pizza[i].ingredientes[j].id);
        			fprintf(novoIng,"%s\n",pizza[i].ingredientes[j].nome);
        			fprintf(novoIng,"%.2f\n",pizza[i].ingredientes[j].preco);
    	        }
    		}
	    }
	}

	fclose(novoIng);
	remove("ingredientes");
	rename("NovoIngredientes","ingredientes");
    
	leituraStruct(pizza);
	
	//processo de remocao da lista de IG (TUDO OK)
	char simnao;
    printf ("Gostaria tambem de remover da lista dos Ingredientes Globais? [s][n]\n");
    simnao=getchar();
    getchar();
    
    if (simnao=='s'){
        FILE* novoIG = fopen ("NovoIngGlob","w+");
    	if (novoIG == NULL) {
    		printf ("erro do novo cardapio");
    	}
        int aux=0;
        for (int i=0; i<*quantidadeIG; i++){
            if (strcmp(ingrediente[i].nome,ingdesejado)==0){
                aux=1;
            }
        }
        
    	fprintf(novoIG,"%d\n",*(quantidadeIG)-aux);
    	for (int i=0; i<*quantidadeIG; i++) {
    	    if (strcmp(ingrediente[i].nome,ingdesejado)!=0){
        		fprintf(novoIG,"%d\n",ingrediente[i].id);
        		fprintf(novoIG,"%s\n",ingrediente[i].nome);
        		fprintf(novoIG,"%.2f\n",ingrediente[i].preco);
    	    }
    	}
    
    	fclose(novoIG);
    	remove("ingredientesGlobais");
    	rename("NovoIngGlob","ingredientesGlobais");
    	
    	igArquivoParaStruct (ingrediente);
	
    }else if (simnao=='n'){
        //nada acontece :)
    }
    
} //remove ingrediente da pizza

void adicionarIngrediente(struct formatoPizzas *pizza, int* quantidadePizzas,int pos, struct ingredientes *ingrediente, int* quantidadeIG){
    
    char ingdesejado[50];
    printf ("Qual ingrediente deseja adicionar?\n");
    printf("Ingredientes da pizza:\n");
    for (int i=0;i<pizza[pos].quantidadeIngredientes;i++){
        printf ("------------------\n");
        printf("%s\n",pizza[pos].ingredientes[i].nome);
        printf("%.2f\n",pizza[pos].ingredientes[i].preco);
    }
    fgets(ingdesejado,sizeof(ingdesejado),stdin); //pega o ingrediente que vai ser adicionado
    ingdesejado[strcspn(ingdesejado,"\n")]='\0';
    
    int jaExiste=0;
    for (int i=0;i<pizza[pos].quantidadeIngredientes;i++){
        if (strcmp(pizza[pos].ingredientes[i].nome,ingdesejado)==0){ //verifica se já tem o ingrediente na pizza
            printf("Essa pizza já tem esse ingrediente");
            jaExiste=1;
        }
    }
    int naoExiste=1;
    if (jaExiste==0){ //se nao tem esse ingrediente
        strcpy(pizza[pos].ingredientes[pizza[pos].quantidadeIngredientes].nome,ingdesejado); //adiciona o nome do ingrediente (pizza.ingredientes)
        
        
        for (int i=0;i<*quantidadeIG;i++){
            if (strcmp(ingrediente[i].nome,ingdesejado)==0){ // se esse ingrediente está cadastrado nos IG
                naoExiste=0;
                pizza[pos].ingredientes[pizza[pos].quantidadeIngredientes].id=ingrediente[i].id;
                pizza[pos].ingredientes[pizza[pos].quantidadeIngredientes].preco=ingrediente[i].preco;
            }
        }
        if (naoExiste==1){ //se for um ingrediente completamente novo, sem cadastro
            printf("Ingrediente novo\n");
            printf ("Digite o preco do ingrediente: RS ");
            scanf ("%f",&pizza[pos].ingredientes[pizza[pos].quantidadeIngredientes].preco); //pega o preco (pizza.ingredientes)
            getchar();
            pizza[pos].ingredientes[pizza[pos].quantidadeIngredientes].id=1+(ingrediente[*quantidadeIG-1].id); //cria o id (pizza.ingredientes)
            
            strcpy(ingrediente[*quantidadeIG].nome,ingdesejado);
            ingrediente[*quantidadeIG].id = pizza[pos].ingredientes[pizza[pos].quantidadeIngredientes].id; //passa as 3 informacoes para os IG
            ingrediente[*quantidadeIG].preco = pizza[pos].ingredientes[pizza[pos].quantidadeIngredientes].preco;
            *quantidadeIG = *(quantidadeIG)+1;
        }
        
        pizza[pos].quantidadeIngredientes+=1;
        leituraArquivo(pizza,quantidadePizzas);
        igStructParaArquivo(ingrediente, quantidadeIG);
    }
} //adiciona novo ingrediente da pizza

//-----------------------------------------------------------------

void exibirCardapio(char tipo,struct formatoPizzas *pizza, int* quantidadePizzas) {
	if (tipo!='r') {
		printf ("------------------------------------------------------\n");
		printf ("-----------------------Cardapio-----------------------\n");
		printf ("------------------------------------------------------\n");
	}

	for (int i=0; i<*quantidadePizzas; i++) {

		//printf ("%d\n",pizza[i].id);
		printf ("%s\n",pizza[i].nome);
		printf ("Tamanho: %c\n",pizza[i].tamanho);
		printf ("RS %.2f\n",pizza[i].preco);
		printf ("Ingredientes:\n");
		for (int j=0; j<pizza[i].quantidadeIngredientes; j++) {
			printf ("\t     %s\n",pizza[i].ingredientes[j].nome);
		}
		printf ("------------------------------\n");
	}

	//-------------------------------------------
} //exibe o cardapio para o usuC!rio

void exportarCardapio(struct formatoPizzas *pizza, int* quantidadePizzas) {
    
    FILE* arq = fopen ("Cardapio da Pizzaria","w+");
	if (arq == NULL) {
		printf ("erro de exportacap");
	}
    fprintf (arq,"------------------------------------------------------------\n");
	fprintf (arq,"---------------------Pizzaria do Silas----------------------\n");
	fprintf (arq,"------------------------------------------------------------\n");
	for (int i=0; i<*quantidadePizzas; i++){
	    fprintf(arq,"%s\n",pizza[i].nome);
	    fprintf(arq,"Tamanho: %c\n",pizza[i].tamanho);
	    fprintf(arq,"Ingredientes: ");
	    for (int j=0; j<pizza[i].quantidadeIngredientes; j++) {
			fprintf(arq,"%s",pizza[i].ingredientes[j].nome);
			if (j!=pizza[i].quantidadeIngredientes-1){
			    fprintf (arq,", ");
			}
		}
		fprintf(arq,"\nPreco: RS %.2f\n",pizza[i].preco);
		fprintf(arq,"------------------------------------------------------------\n");
	}
} //exporta cardápio formatado

//-----------------------------------------------------------------

void removendo(int oqueRemover, struct formatoPizzas *pizza, int* quantidadePizzas) {

	FILE* novoCard = fopen ("NovoCardapio","w+"); //cria arquivo 1
	if (novoCard == NULL) {
		printf ("erro do novo cardapio");
	}
	FILE* novoIng = fopen ("NovoIngredientes","w+"); //cria arquivo 2
	if (novoIng == NULL) {
		printf ("erro do novo ingredientes");
	}

	fprintf(novoCard,"%d\n",*(quantidadePizzas)-1);
	for (int i=0; i<*quantidadePizzas; i++) {
		if (pizza[i].id!=oqueRemover) {
			fprintf(novoCard,"%d\n",pizza[i].id);
			fprintf(novoCard,"%s\n",pizza[i].nome);
			fprintf(novoCard,"%c\n",pizza[i].tamanho);
			fprintf(novoCard,"%.2f\n",pizza[i].preco);
		}
	}

	for (int i=0; i<*quantidadePizzas; i++) {
		if (pizza[i].id!=oqueRemover) {
			fprintf(novoIng,"%d\n",pizza[i].quantidadeIngredientes);
			for (int j=0; j<pizza[i].quantidadeIngredientes; j++) {
				fprintf(novoIng,"%d\n",pizza[i].ingredientes[j].id);
				fprintf(novoIng,"%s\n",pizza[i].ingredientes[j].nome);
				fprintf(novoIng,"%.2f\n",pizza[i].ingredientes[j].preco);
			}
		}
	}

	fclose(novoCard);
	fclose(novoIng);
	remove("cardapio");
	remove("ingredientes");
	rename("NovoCardapio","cardapio");
	rename("NovoIngredientes","ingredientes");
}// exclui a pizza desejada

void removerPizza(struct formatoPizzas *pizza, int* quantidadePizzas) {
	printf ("------------------------------------------------------\n");
	printf ("------------------------Remocao-----------------------\n");
	int oqueRemover=50135;
	while (oqueRemover!=0) {
		//exibirCardapio('r');
		printf("------------------------------------------------------\n");
		printf ("Qual o ID da pizza que deseja remover?\n");
		printf ("0-Voltar\n");
		scanf("%d",&oqueRemover);
		getchar();
		if (oqueRemover!=0) {
			for (int i=0; i<*quantidadePizzas; i++) {
				if (pizza[i].id==oqueRemover) {
					printf("Pizza Encontrada\n");
					removendo(oqueRemover, pizza, quantidadePizzas); //remove a pizza
					leituraStruct(pizza); //reescaneia o struct com a nova quantidade de pizzas
				}
			}
		}
	}
} // pega informaC'C5es da pizza que deseja exclur

//-----------------------------------------------------------------

void editarPizza(struct formatoPizzas *pizza, int* quantidadePizzas, struct ingredientes *ingrediente, int* quantidadeIG) {
	printf ("------------------------------------------------------\n");
	printf ("------------------------Edicao------------------------\n");
	int editp=1;
	while (editp!=0) {
		//exibirCardapio('r');
		printf("------------------------------------------------------\n");
		printf ("Qual o ID da pizza que deseja editar?\n");
		printf ("0-Voltar\n");
		scanf ("%d",&editp);
		getchar();
		if (editp!=0) { // se nao tiver cancelado
			int encontrado=0;
			for (int i=0; i<*quantidadePizzas; i++) { // procurando pizza
				if (pizza[i].id==editp) {
					printf ("%s\n",pizza[i].nome);
					printf ("Tamanho: %c\n",pizza[i].tamanho);
					printf ("RS %.2f\n",pizza[i].preco);
					printf ("Ingredientes:\n");
					for (int j=0; j<pizza[i].quantidadeIngredientes; j++) {
						printf ("\t     %s\n",pizza[i].ingredientes[j].nome);
					}
					printf ("------------------------------\n");
					encontrado=1;
				}
			}

			char operacao='n';
			while (encontrado==1 && ((operacao=='n'||operacao=='N')||(operacao=='t'||operacao=='t')||(operacao=='p'||operacao=='P'))) { //se encontrou a pizza
				printf ("Oque deseja editar?\n");
				printf ("N-Nome\n");
				printf ("T-Tamanho\n");
				printf ("P-Preco\n");
				printf ("E-Editar Ingredientes\n");
				printf ("A-Adicionar Ingredientes\n");
				printf ("R-Remover Ingredientes\n");
				printf ("C-Cancelar\n");
				operacao=getchar();
				getchar();
				if (operacao!='c' && operacao!='C') { //se nao tiver cancelado
					for (int i=0; i<*quantidadePizzas; i++) { //procura novamente a pizza
						if (pizza[i].id==editp) { //processo de mudar informacoes da pizza
							if (operacao=='n'||operacao=='N') { //mudar nome
								printf ("Digite o novo nome: ");
								fgets(pizza[i].nome,sizeof(pizza[i].nome),stdin);
								pizza[i].nome[strcspn(pizza[i].nome,"\n")]='\0';
								printf ("Nome alterado\n");
							} else if (operacao=='t'||operacao=='T') { //mudar tamanho
								printf ("Digite o novo tamanho: ");
								pizza[i].tamanho=getchar();
								getchar();
								printf ("Tamanho alterado\n");
							} else if (operacao=='p'||operacao=='P') { //mudar preco
								printf ("Digite o novo preco: RS");
								scanf ("%f",&pizza[i].preco);
								getchar();
								printf ("Preco alterado\n");
							}else if (operacao=='e'||operacao=='E'){ //editar ingrediente
							    editarIngrediente(pizza,quantidadePizzas,i,ingrediente, quantidadeIG);
							}else if (operacao=='a'||operacao=='A'){ //adicionar ingrediente
							    adicionarIngrediente(pizza,quantidadePizzas,i,ingrediente, quantidadeIG);
							}else if (operacao=='r'||operacao=='R'){ //remover ingrediente
							    removerIngrediente(pizza,quantidadePizzas,i,ingrediente, quantidadeIG);
							}else {
								printf ("Operacao nao encontrada\n");
							}
						}
					}
				}
			}
		}
	}
	// depois de terminar tudo -> atualizar arquivo com base no struct
	leituraArquivo(pizza,quantidadePizzas);
} //edita nome, tamanho e preco

//-----------------------------------------------------------------

void adicionarPizza(struct formatoPizzas *pizza, int* quantidadePizzas, struct ingredientes *ingrediente, int* quantidadeIG) {

	printf ("-------------------------------------------------------\n");
	printf ("--------------------Adicionar Pizza--------------------\n");
	printf ("-------------------------------------------------------\n");

	pizza[*quantidadePizzas].id = 1 + pizza[*(quantidadePizzas)-1].id;
	printf ("Digite o nome da nova pizza: ");
	fgets (pizza[*quantidadePizzas].nome, sizeof(pizza[*quantidadePizzas].nome),stdin); //pega o nome da nova pizza
	pizza[*quantidadePizzas].nome[strcspn(pizza[*quantidadePizzas].nome,"\n")]='\0';

	printf ("Digite o tamanho da nova pizza: ");
	pizza[*quantidadePizzas].tamanho=getchar(); //pega o tamanho da nova pizza
	getchar();

	printf ("Digite o preco da nova pizza: "); //pega o preco da nova pizza
	scanf ("%f",&pizza[*quantidadePizzas].preco);

	printf ("Quantos ingredientes tem a nova pizza? ");
	scanf ("%d",&pizza[*quantidadePizzas].quantidadeIngredientes); //pega a quantidade de ingredientes
	getchar();

	printf ("Digite os ingredientes:\n");
	for (int i=0; i<pizza[*quantidadePizzas].quantidadeIngredientes; i++) {
		printf ("Digite o ingrediente %d: ",i+1);
		fgets (pizza[*quantidadePizzas].ingredientes[i].nome, sizeof(pizza[*quantidadePizzas].ingredientes[i].nome), stdin); //pega o nome dos ingredientes
		pizza[*quantidadePizzas].ingredientes[i].nome[strcspn(pizza[*quantidadePizzas].ingredientes[i].nome,"\n")]='\0';

		printf ("Digite o preco do ingrediente: RS");
		scanf ("%f",&pizza[*quantidadePizzas].ingredientes[i].preco); //pega o preco dos ingredientes
		getchar();
		if (i>0){ //se nao for o primeiro ingrediente
		    for (int j=0;j<i;j++){ //processo de comparacao se o ingrediente digitado e igual a outro
		        if (strcmp(pizza[*quantidadePizzas].ingredientes[i].nome,pizza[*quantidadePizzas].ingredientes[j].nome)==0){
		            
                    printf ("Ingrediente repetido. Digite outro ingrediente:");
	                fgets (pizza[*quantidadePizzas].ingredientes[i].nome, sizeof(pizza[*quantidadePizzas].ingredientes[i].nome), stdin);
	                pizza[*quantidadePizzas].ingredientes[i].nome[strcspn(pizza[*quantidadePizzas].ingredientes[i].nome,"\n")]='\0';
		            
		            printf ("Digite o preco do ingrediente: RS");
            		scanf ("%f",&pizza[*quantidadePizzas].ingredientes[i].preco);
            		getchar();
		            j--;
		        }
		    }
		}
	}
	int existe=0;
	
    for (int j=0;j<pizza[*quantidadePizzas].quantidadeIngredientes;j++){ //muda ingrediente
        for (int i=0; i<*quantidadeIG; i++) { //muda IG
            if (strcmp(pizza[*quantidadePizzas].ingredientes[j].nome,ingrediente[i].nome)==0){ //se o ingrediente ja possui cadastro
                pizza[*quantidadePizzas].ingredientes[j].id=ingrediente[i].id;
                pizza[*quantidadePizzas].ingredientes[j].preco=ingrediente[i].preco;
                printf("!!! O ingrediente %s ja esta cadastrado. O seu preco foi ajustado para RS%.2f\n",ingrediente[i].nome,ingrediente[i].preco);
                printf ("!!! Caso queira alterar, mude os dados do ingrediente no menu 'Editar ingredientes'\n");
                printf ("------------------------------------------------------\n");
                existe=1;
            }
        }
        if (existe==0){
            pizza[*quantidadePizzas].ingredientes[j].id=ingrediente[*(quantidadeIG)-1].id;
            *quantidadeIG = *(quantidadeIG)+1;
        }
        existe=0;
	}

	//------------------------------------------------------------------
	//----------processo de atribuicao de id para ingredientes----------
	//------------------------------------------------------------------

	*(quantidadePizzas)=*(quantidadePizzas)+1;// atualiza a quantidade de pizzas
	// depois de terminar tudo -> atualizar arquivo com base no struct
	leituraArquivo(pizza,quantidadePizzas);
	igStructParaArquivo(ingrediente,quantidadeIG);
}

//-----------------------------------------------------------------

void editarCardapio(struct formatoPizzas *pizza, int* quantidadePizzas, struct ingredientes *ingrediente, int* quantidadeIG) {
	printf ("-------------------------------------------------------\n");
	printf ("--------------------Editar Cardapio--------------------\n");
	printf ("-------------------------------------------------------\n");

	//declaracao de variC!veis
	char edop='b';
	while (edop!='v'&&edop!='v') {
		printf ("Oque deseja editar?");
		printf ("\nE-Editar Pizzas");
		printf ("\nA-Adicionar Pizzas");
		printf ("\nR-Remover Pizzas");
		printf ("\nV-Voltar\n");

		edop=getchar();
		getchar();

		if (edop=='E'||edop=='e') {
			editarPizza(pizza,quantidadePizzas,ingrediente, quantidadeIG);
		} else if (edop=='A'||edop=='a') {
			adicionarPizza(pizza, quantidadePizzas, ingrediente, quantidadeIG);
		} else if (edop=='R'||edop=='r') {
			removerPizza(pizza, quantidadePizzas);
		}
	}

} // painel de editar cardapio

//-----------------------------------------------------------------

void processoVenda (struct formatoPizzas *pizza, int* quantidadePizzas){
    
    exibirCardapio('a',pizza, quantidadePizzas);
    
    int quantidade=1;
    float total=0;
    char sabor[50];
    int pizzaEncontrada=0;
    while (quantidade!=0){
        printf ("Digite '0' para iniciar Modo de Debug\n");
        printf ("Digite a quantidade de pizzas: ");
        scanf ("%d",&quantidade);
        getchar();
        if (quantidade!=0){
            printf ("Digite os sabores\n");
            for (int i=0;i<quantidade;i++){
                printf ("Pizza %d: ",i+1);
                fgets(sabor,sizeof(sabor),stdin); //pega os sabores de pizza
                sabor[strcspn(sabor,"\n")]='\0';
                
                for (int j=0;j<*quantidadePizzas;j++){
                    if (strcmp(sabor,pizza[j].nome)==0){
                        total+=pizza[j].preco;
                        pizzaEncontrada=1;
                    }
                }
                if (pizzaEncontrada==0){
                    printf ("Pizza nao encontrada\n");
                    printf ("Digite outro sabor\n");
                    i--;
                }
                pizzaEncontrada=0;
            }
            printf ("Total a pagar: RS%.2f\n",total);
		    printf ("------------------------------------------------------\n");
        }
        total=0;
    }
}

*/

int main () {
	struct ingredientes ingrediente[100];
	struct formatoPizzas pizza[100];
	int quantidadePizzas, quantidadeIG;

	char operacao='a';

	while (operacao!='F' && operacao!='f') {

		leituraStruct(pizza);
		igArquivoParaStruct (ingrediente);

		FILE* arq = fopen ("cardapio","r");
		if (arq == NULL) {
			printf ("erro na leitura de arquivo");
		}
		fscanf(arq,"%d",&quantidadePizzas);
		fclose (arq);
		
		FILE* ig = fopen ("ingredientesGlobais","r");
		if (ig == NULL) {
			printf ("erro na leitura de ingredientes globais");
		}
		fscanf(ig,"%d",&quantidadeIG);
		fclose (ig);

		printf ("------------------------------------------------------\n");
		printf ("------------------Pizzaria do Silas-------------------\n");
		printf ("------------------------------------------------------\n");
		printf ("Quantidade de pizzas: %d\n",quantidadePizzas);
		printf ("Quantidade de IG: %d\n",quantidadeIG);
		printf ("------------------------------------------------------");

		printf ("\nQual operacao deseja realizar?");
		printf("\nP-Processo de Venda");
		printf("\nV-Visualizar Cardapio");
		printf ("\nE-Editar Cardapio");
		printf ("\nX-Exportar Cardapio");
		printf ("\nF-Finalizar Processo\n");
		operacao=getchar();
		getchar();

		if (operacao=='V'||operacao=='v') {
			leituraStruct(pizza);
			exibirCardapio('a',pizza, &quantidadePizzas);
		} else if (operacao=='E'||operacao=='e') {
			leituraStruct(pizza);
			editarCardapio(pizza, &quantidadePizzas, ingrediente, &quantidadeIG);
		} else if (operacao=='X'||operacao=='x') {
			leituraStruct(pizza);
			exportarCardapio(pizza, &quantidadePizzas);
		}else if (operacao=='p'||operacao=='P'){
		    processoVenda(pizza, &quantidadePizzas);
		}
	}
}

//processo de adicionar ingrediente está bugado
//processo de venda
