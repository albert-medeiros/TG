#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//#include "avl.h"

#define tam 51

//variavel global para contagem de linha da matriz de pesos
int qntCadastros=1;

typedef struct usuario{ // Dados dos alunos
	char nome[20];
	int idade;
	
}TipoAluno;

void inicializaGrafos(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam]){ 
/*
i. preenche a matriz de pesos com zeros, aloca uma posição de memória (posição 0) para as listas de adjacência e adjacência em AVL e faz com o que seus conteúdos apontem para NULL; 
ii. não é necessário oferecer essa opção ao usuário; 
iii. poderão ser utilizados os índices da lista de 1 a n
*/

	printf("\n\n\t -> Inicializando o Grafo: \n");
	for(int i=0; i<=tam;i++){
		for(int j=0; j<tam;j++){
			//printf("%d\n");
			matrizUsuarios[i][j] = 0;
		}
	}
	
	for(int i=0; i<tam;i++){
			//printf("%d\n");
			vetorUsuarios[i].idade = 0;
			strcpy(vetorUsuarios[i].nome, "");
	}
}

void inserirUsuario(usuario vetorUsuarios[tam]){

/*
i. libera, dinamicamente, uma linha e uma coluna da matriz de pesos para representar as relações do novo usuário, aloca uma posição de memória em cada uma das listas e realiza a inserção de tal usuário pelo nome (que será fornecido); 
ii. o programa deverá verificar se o usuário já está inserido e, caso positivo, retornar uma mensagem de erro.
*/
	
	char nome[20];
	
	FILE *entrada = fopen("arquivo.txt", "r"); //abertura do arquivo 
				
	if(entrada == NULL){
		printf("\t  -> Erro na abertura do arquivo");
		system("pause");
	}
	
	
	while(!feof(entrada)){
		fscanf(entrada, "%s\n",&nome); //lê os dados do arquivo
		for(int j=1;j<=qntCadastros;j++){
			if(strcmp(vetorUsuarios[j].nome,nome) == 0){
				printf("\n\t\t - - - Usuario ' %s ' ja foi inserido - - -\n\n",nome);
				system("pause");
			}
			
		}
		
		
		strcpy(vetorUsuarios[qntCadastros].nome,nome);
		fscanf(entrada, "%d\n",&vetorUsuarios[qntCadastros].idade); //lê os dados do arquivo
		printf("\tUsuario %s cadastrado\n",vetorUsuarios[qntCadastros].nome);
		qntCadastros++;
	}
	
}

void inserirRelacao(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam]){
/*
i. insere uma relação de “é seguidor de/seguido por” entre um par de usuários;
ii. nessa operação de inserção, os usuários deverão estar previamente inseridos na rede; 
iii. deverão ser listados os nomes dos usuários da rede social para que o usuário do programa se guie na escolha; 
iv. a inserção da relação é concluída após a inclusão simultânea das informações nas três estruturas representativas; 
v. caso a relação já esteja inserida, deve-se oferecer a opção de atualizar a o período de tempo associado entre os dois usuários selecionados;
vi. no caso da representação na lista com adjacências em AVL, ao se inserir uma nova relação, é necessário verificar se as AVLs que representam 
	os usuários foram desbalanceadas e, caso positivo, realizar as operações de rotacionamento de vértices (nós). ? Revise os algoritmos de rotacionamento
	de árvores AVL e utilize os algoritmos já implementados em outras atividades.
*/


	char nomeSeguido[20], nomeSeguidor[20];
	int coluna=0, linha=0,cont=0;
	FILE *seguir = fopen("seguir.txt", "r"); //abertura do arquivo	
	if(seguir == NULL){
		printf("\t  -> Erro na abertura do arquivo");
		system("pause");
	}
	
	while(!feof(seguir)){
		fscanf(seguir, "%s\n",&nomeSeguidor); //lê os dados do arquivo
		fscanf(seguir, "%s\n",&nomeSeguido); //lê os dados do arquivo
		
		printf("\n\n--> %s segue %s\n", nomeSeguidor, nomeSeguido);
		
		
		for(int i=1;i<qntCadastros;i++){
			if(strcmp(vetorUsuarios[i].nome,nomeSeguidor) == 0){
				linha = i;				
				cont++;
				if(cont == 2){
					break;
				}
			}
			
			if(strcmp(vetorUsuarios[i].nome,nomeSeguido) == 0){
				coluna = i;
				
				cont++;
				if(cont == 2){
					break;
				}
			}
		}
		if(cont != 2){
			printf("\n\t - somente um usuário encontrado - ");
		}
	
		
		printf("linha %d - Coluna %d\n",linha,coluna);
		matrizUsuarios[linha][coluna] = 1;
		
		
		// Printar a matriz de pesos
//		for(int i=1;i<qntCadastros;i++){
//			for(int j=1;j<qntCadastros;j++){
//				printf("[ %d ]", matrizUsuarios[i][j]);
//			}
//			printf("\n");
//		}
//		
		
		
		
	}
	
	
	

}

void listarSeguidores(){
/*
i.após o usuário do programa escolher um usuário cadastrado x, esta opção deverá listar todos os usuários os quais x segue e por quais usuários x é seguido, inclusive com os tempos relacionados à cada relação existente; 
ii. no caso da representação por lista com adjacências em AVL, fornecer ao usuário a opção de se utilizar algum dos algoritmos de percurso em árvores in-ordem, pré-ordem ou pós-ordem.
*/


}

void listarSeguidoresVelhos(){
//i. lista todos os usuários que são seguidos por usuários mais velhos, inclusive com os quantitativos associados a cada um deles.


}

void atualizarRelacao(){
//i. ocorre similarmente à inserção de relações, porém a relação deverá estar previamente inserida. ii. caso a relação não esteja inserida deve-se oferecer essa opção ao usuário do programa.

}

void removerUsuario(){
/* 
i. remove um usuário previamente cadastrado na rede social, inclusive, com todas as suas relações; 
ii. caso o usuário não esteja cadastrado, exibir uma mensagem de erro.
*/
}

void removerRelacao(){
/*
i. remove uma relação previamente cadastrada na rede social; 
ii. caso algum elemento da relação a ser removida (vértice ou aresta) não esteja inserido, exibir uma mensagem de erro.
*/	


}


main(){
	
	printf("\n\n\t  - - - - Programa iniciado - - - -\n\n");
	int matrizUsuarios[tam][tam];
	usuario vetorUsuarios[tam];
	inicializaGrafos(vetorUsuarios, matrizUsuarios);
	
	inserirUsuario(vetorUsuarios);
	
	printf("\n\n\t  - - - - %d usuarios cadastrados - - - -\n\n", qntCadastros);
	
	
	inserirRelacao(vetorUsuarios, matrizUsuarios);
	printf("\n\n");
	printf("           -      FIM             -");
	
	
}
