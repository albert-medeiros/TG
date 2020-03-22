/* Os usu�riarios s�o inseridos atraves de um arquivo externo de forma que o conteudo seja disposto em uma linha o nome do usuario e na ligua em seguida a idade, na proxima
   nome do Proximo usuario e assim por diante 
   
   Ja a sequencia de seguidores tbm s�o atribuidas atraves de um arquivo externo tambem com as informacoes separadas por linha, na qual, a primeira ligua o seguidor e na de baixo o seguido e assim por diante
*/

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
i. preenche a matriz de pesos com zeros, aloca uma posi��o de mem�ria (posi��o 0) para as listas de adjac�ncia e adjac�ncia em AVL e faz com o que seus conte�dos apontem para NULL; 
ii. n�o � necess�rio oferecer essa op��o ao usu�rio; 
iii. poder�o ser utilizados os �ndices da lista de 1 a n
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
i. libera, dinamicamente, uma linha e uma coluna da matriz de pesos para representar as rela��es do novo usu�rio, aloca uma posi��o de mem�ria em cada uma das listas e realiza a inser��o de tal usu�rio pelo nome (que ser� fornecido); 
ii. o programa dever� verificar se o usu�rio j� est� inserido e, caso positivo, retornar uma mensagem de erro.
*/
	
	char nome[20];
	
	FILE *entrada = fopen("arquivo.txt", "r"); //abertura do arquivo 
				
	if(entrada == NULL){
		printf("\t  -> Erro na abertura do arquivo");
		system("pause");
	}
	
	
	while(!feof(entrada)){
		fscanf(entrada, "%s\n",&nome); //l� os dados do arquivo
		for(int j=1;j<=qntCadastros;j++){
			if(strcmp(vetorUsuarios[j].nome,nome) == 0){
				printf("\n\t\t - - - Usuario ' %s ' ja foi inserido - - -\n\n",nome);
				system("pause");
			}
			
		}
		
		
		strcpy(vetorUsuarios[qntCadastros].nome,nome);
		fscanf(entrada, "%d\n",&vetorUsuarios[qntCadastros].idade); //l� os dados do arquivo
		printf("\tUsuario %s cadastrado\n",vetorUsuarios[qntCadastros].nome);
		qntCadastros++;
	}
	
}

void inserirRelacao(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam]){
/*
i. insere uma rela��o de �� seguidor de/seguido por� entre um par de usu�rios;
ii. nessa opera��o de inser��o, os usu�rios dever�o estar previamente inseridos na rede; 
iii. dever�o ser listados os nomes dos usu�rios da rede social para que o usu�rio do programa se guie na escolha; 
iv. a inser��o da rela��o � conclu�da ap�s a inclus�o simult�nea das informa��es nas tr�s estruturas representativas; 
v. caso a rela��o j� esteja inserida, deve-se oferecer a op��o de atualizar a o per�odo de tempo associado entre os dois usu�rios selecionados;
vi. no caso da representa��o na lista com adjac�ncias em AVL, ao se inserir uma nova rela��o, � necess�rio verificar se as AVLs que representam 
	os usu�rios foram desbalanceadas e, caso positivo, realizar as opera��es de rotacionamento de v�rtices (n�s). ? Revise os algoritmos de rotacionamento
	de �rvores AVL e utilize os algoritmos j� implementados em outras atividades.
*/


	char nomeSeguido[20], nomeSeguidor[20];
	int coluna=0, linha=0,cont=0;
	FILE *seguir = fopen("seguir.txt", "r"); //abertura do arquivo	
	if(seguir == NULL){
		printf("\t  -> Erro na abertura do arquivo");
		system("pause");
	}
	
	while(!feof(seguir)){
		fscanf(seguir, "%s\n",&nomeSeguidor); //l� os dados do arquivo
		fscanf(seguir, "%s\n",&nomeSeguido); //l� os dados do arquivo
		
		printf("\n\n--> %s segue %s\n", nomeSeguidor, nomeSeguido);
		
		
		for(int i=1;i<qntCadastros;i++){ //percorre o vetor at� achar o nome digitado pelo usu�rio e salva a posi��o que ele est� pois � a mesma que est� na matriz, tanto em linha quanto em coluna
			if(strcmp(vetorUsuarios[i].nome,nomeSeguidor) == 0){
				linha = i;				
				cont++;
				if(cont == 2){  //caso tenha entrado duas vezes, uma vez em cada "if", ja para a verificacao n�o necessitando percorrer o resto do vetor pois ja foi encontrada a posicao do seguidor e do seguido 
					break;
				}
			}
			
			if(strcmp(vetorUsuarios[i].nome,nomeSeguido) == 0){
				coluna = i;
				
				cont++;
				if(cont == 2){  //caso tenha entrado duas vezes, uma vez em cada "if", ja para a verificacao n�o necessitando percorrer o resto do vetor pois ja foi encontrada a posicao do seguidor e do seguido
					break;
				}
			}
		}
		if(cont != 2){ // se nao entrou duas vezes n�o tem algum usuario
			printf("\n\t - somente um usu�rio encontrado - ");
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
		
	
		cont=0;	
	}
}

void listarSeguidores(int existe, char nomeListaseguidores[20], usuario vetorUsuarios[tam],int matrizUsuarios[tam][tam],int modo){
/*
i.ap�s o usu�rio do programa escolher um usu�rio cadastrado x, esta op��o dever� listar todos os usu�rios os quais x segue e por quais usu�rios x � seguido,
  inclusive com os tempos relacionados � cada rela��o existente; 
ii.no caso da representa��o por lista com adjac�ncias em AVL, fornecer ao usu�rio a op��o de se utilizar algum dos algoritmos de percurso em �rvores in-ordem,
   pr�-ordem ou p�s-ordem.
*/

	int segue=0,eSeguido=0;
	switch(modo){
		case 1:
			printf("\n\n\n -------------------- Matriz de Pesos ----------------------- ");
			printf("\n\tO usuario Segue:\n"); 
			for(int i=1;i<qntCadastros;i++){ //percorre toda a linha da matriz mostrando todos os usuarios que sao seguidos por esse usu�rio
				if(matrizUsuarios[existe][i] == 1){
					printf("\t\t\t %s\n", vetorUsuarios[i].nome);
					segue=1;
				}
			}
			
			printf("\n\tO usuario eh seguido:\n");
			for(int i=1;i<qntCadastros;i++){ //percorre toda a coluna da matriz mostrando todos os usuarios que est�o seguindo esse usu�rio
				if(matrizUsuarios[i][existe] == 1){
					printf("\t\t\t %s\n", vetorUsuarios[i].nome);
					eSeguido=1;
				}
			}
			printf(" -------------------- Matriz de Pesos ----------------------- ");
		break;
		
		case 2:
			printf("\n\n\n -------------------- lista de adjac�ncias ----------------------- ");
			printf("\n\n\n -------------------- lista de adjac�ncias ----------------------- ");
		
		break;
		
		case 3:
			printf("\n\n\n -------------------- lista de adjac�ncias AVL ----------------------- ");
			printf("\n\n\n -------------------- lista de adjac�ncias AVL ----------------------- ");
		
		break;	
	}
}

void listarSeguidoresVelhos(){
//i. lista todos os usu�rios que s�o seguidos por usu�rios mais velhos, inclusive com os quantitativos associados a cada um deles.


}

void atualizarRelacao(){
/*
i. ocorre similarmente � inser��o de rela��es, por�m a rela��o dever� estar previamente inserida. 
ii. caso a rela��o n�o esteja inserida deve-se oferecer essa op��o ao usu�rio do programa.
*/

}

void removerUsuario(){
/* 
i. remove um usu�rio previamente cadastrado na rede social, inclusive, com todas as suas rela��es; 
ii. caso o usu�rio n�o esteja cadastrado, exibir uma mensagem de erro.
*/
}

void removerRelacao(){
/*
i. remove uma rela��o previamente cadastrada na rede social; 
ii. caso algum elemento da rela��o a ser removida (v�rtice ou aresta) n�o esteja inserido, exibir uma mensagem de erro.
*/	


}


main(){
	
	printf("\n\n\t  - - - - Programa iniciado - - - -\n\n");
	int matrizUsuarios[tam][tam],opcListausuarios,vzs=10,existe=0,modo=0;
	char nomeListaseguidores[20];
	usuario vetorUsuarios[tam];
	inicializaGrafos(vetorUsuarios, matrizUsuarios);	
	inserirUsuario(vetorUsuarios);
	
	printf("\n\n\t  - - - - %d usuarios cadastrados - - - -\n\n", qntCadastros);
	
	inserirRelacao(vetorUsuarios, matrizUsuarios);

//--------------------------------- Listando os seguidores do usu�rio a ser escolhido -----------------------------------------------------------
	printf("\n\nVoce deseja listar os usuarios? 1-sim 2-nao\n");
	scanf("%d",&opcListausuarios); printf("\n\n\t");

	vzs=10; //Pra quando houver mais de x usuarios cadastrados, esse n�mero ser usado como base para quebraa de linha no for a abaixo
	if(opcListausuarios == 1){
		for(int i=1;i<qntCadastros;i++){ //printa os usu�rios cadastrados
			printf("%s ",vetorUsuarios[i].nome);
			if(i==vzs){ //saber a hora de dar quebra de linha na mostra de usuarios
				printf("\n\t");
				vzs= vzs+10;
			}
			else{ //nao printar o "-" na depois do ultimo valor antes da quebra de linha
				printf("- ");
			}
		}
		
		A: //se o nome nao for um valido vem pra ca
		printf("\n\nDigite o nome a ser listado: ");
		scanf("%s", &nomeListaseguidores);
		for(int i=1;i<qntCadastros;i++){
			if(strcmp(nomeListaseguidores, vetorUsuarios[i].nome)==0){ //verifica se existe e salva a posicao no vetor que ele esta
				existe=i;
			}
		}
		
		if(existe == 0){
			printf("O nome digitado nao esta cadastrado. Digite novamente!\n");
			system("pause");
			goto A;
		}
		
		while(modo == 0){
			printf("\nDigite o modo a ser listado:\n\t\t 1- Matriz de Pesos\n\t\t 2- lista de adjacencias\n\t\t 3- lista de adjacencias em Arvores AVL\n");
			scanf("%d",&modo);
			if(modo>3 || modo<0){
				modo=0;
				printf("\n\t\tO numero digitado eh invalido. Digite novamente!\n");
				system("pause");
			}	
		}
		
		listarSeguidores(existe, nomeListaseguidores,vetorUsuarios,matrizUsuarios,modo);	   
	}
//--------------------------------------------------------------------------------------------


	printf("\n\n\t\t-\tFIM\t-");
}
