/* 
   
   Regras:
	1-> Usuarios s�o inseridos atraves do arquivo.txt sendo que s�o dispostos nome em na primeira linha e idade logo na de baixo
	2-> A inser��o de quem segue quem tbm e feita atraves do arquivo seguir.txt no qual � disposto na primeira linha quem segue e na loga na de baixo quem � seguido
   
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

//#include "avl.h"

#define tam 51

#define ALOCA (TNo*)malloc(sizeof(TNo))

//variavel global para contagem de linha da matriz de pesos
int qntCadastros=1;


//----------------------------------------------------------------------- STRUCT / INICIALIZA ------------------------------------------------------------------------------------
typedef struct usuario{ // Dados dos usuarios
	char nome[20];
	int idade;
}TipoUsuario;

typedef struct no{ //struct para armazenar os valores salvos na �rvore
	struct no *esq,*dir; // aponta para o proximo no
	TipoUsuario user; //chave real
} TNo;

//----------------------------------------------------------------------- STRUCT / INICIALIZA ------------------------------------------------------------------------------------

int altura(TNo *ptr){  
	if (ptr == NULL){ //Caso n�o haja algum n� na �rvore
		return -1; //return -1 - altura 
	}
	
	else{
		int he = altura(ptr->esq); //percorrer a esquerda
		int hd = altura(ptr->dir); //percorrer a direita
		if(he<hd){ 		//verifica qual das ramifica��es � maior
			return hd+1;	//conta os n�veis das ramifica��es da direita
		}
		else{
			return he+1;	//conta os n�veis das ramifica��es da esquerda
		}
	}
}

void rotacaoDir(TNo **ptr){
	
	TNo *q,*temp; //ponteiro
	q = (*ptr)->esq; //q vai receber a sub �rvore a esquerda
	temp = q->dir; //sub �rvore a direita de q 
	q->dir = (*ptr); //aponta pra raiz da sub �rvore passada
	(*ptr)->esq = temp; //a raiz vai apontar pra temp
	(*ptr) = q; //defino que q vai ser a nov raiz
	
}

void rotacaoEsq(TNo **ptr){
	TNo *q,*temp; //ponteiro
	
	q = (*ptr)->dir; //q vai receber a sub �rvore a direita
	temp = q->esq; //sub �rvore a ESQUERDA de q 
	q->esq = (*ptr); //aponta pra raiz da sub �rvore passada
	(*ptr)->dir = temp; //a raiz vai apontar pra temp
	(*ptr) = q; //defino que q vai ser a nov raiz
}

//-----------------------------------------------------------------------------------------------------------------> Arvore
//
//aluno1 
//aluno2
//aluno4
//aluno1
//aluno10
//aluno20
//aluno3
//aluno15
//aluno2
//aluno1
//aluno2
//aluno3
//aluno2
//aluno4
//aluno2
//aluno5
//aluno2
//aluno6

void in_ordem(TNo **ptr,int existe){
	printf("\n\n\n\t\t\t 1");
	if((ptr[existe]) != NULL){
		printf("\n\n\n\t\t\t 2");
		in_ordem(&(ptr[existe])->esq, existe);
		
		printf("\nNome: %s\t",(ptr[existe])->user.nome);	
		printf("\nIdade: %d\t",(ptr[existe])->user.idade);	
		
		printf("\n\n\n\t\t\t 3");
		in_ordem(&(ptr[existe])->dir, existe);
		printf("\n\n\n\t\t\t 4");
	}
}

void insereAVL(TNo **ptr, TipoUsuario user,int linha){
	int FB,fb;

	if (ptr[linha] == NULL){ // entra na hora de criar um novo n�
		(ptr[linha]) = ALOCA; //aloco dinamicamente um espa�o pra "ptr"
		(ptr[linha])->esq = NULL;
		(ptr[linha])->dir = NULL;
		strcpy((ptr[linha])->user.nome, user.nome); // o n� recebe o valor do nome
		(ptr[linha])->user = user; // o n� recebe os outros valores
	}
	
	else{
			if(user.idade<(ptr[linha])->user.idade){ //verifica��o para saber em qual lado � inserido o valor
				insereAVL(&(ptr[linha])->esq,user,linha); //passa o valor da esquerda se for menor
			}
			else if(user.idade>(ptr[linha])->user.idade){ //verifica��o para saber em qual lado � inserido o valor
				insereAVL(&(ptr[linha])->dir, user, linha); //passa o valor da direita se for maior
			}
	}
	
	//FB - Pai;  
	//fb - filho;
	//Ap�s inserir o valor � verifica do Fator de balanceamento
	
	FB=(altura((ptr[linha])->dir))-(altura((ptr[linha])->esq)); //calcula a altura ao desempilhar
	printf("\n\n\n\t\t\t%d\n\n\n\n",FB);
	
	if(FB == +2){ //caso o FB do n� seja 2 ent�o tem que fazer altera��o 
			
		fb = altura((ptr[linha])->dir->dir)-altura((ptr[linha])->dir->esq); //calcula a altura do filho da direita
		
		if(fb==1){ // se for igual a um ent�o rota��o simples 
			rotacaoEsq(ptr);
		}
			
		else if(fb == -1){ // se for igual a menos um ent�o rota��o dulpa
			rotacaoDir(&(ptr[linha])->dir);
			rotacaoEsq(ptr);
		}
	}
		
	else if(FB == -2){
	
		fb = (altura((ptr[linha])->esq->dir))-(altura((ptr[linha])->esq->esq)); //calcula a altura do filho da direita
		if(fb== -1){ // se for igual a um ent�o rota��o simples 
			rotacaoDir(ptr);
		}
	
		else if(fb== +1){ // se for igual a menos um ent�o rota��o dulpa
			rotacaoEsq(&(ptr[linha])->esq);
			rotacaoDir(ptr);
		}	
	}
}
	
//-----------------------------------------------------------------------------------------------------------------> Arvore
	

void inicializaGrafos(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam], TNo **ptr){ 
/*
i. preenche a matriz de pesos com zeros, aloca uma posi��o de mem�ria (posi��o 0) para as listas de adjac�ncia e adjac�ncia em AVL e faz com o que seus conte�dos apontem para NULL; 
ii. n�o � necess�rio oferecer essa op��o ao usu�rio; 
iii. poder�o ser utilizados os �ndices da lista de 1 a n
*/

//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios	
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
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios		
	
//-----------------------------------------------------------------------------------------------------------------> Arvore		
	for(int i=0;i<tam;i++){
		ptr[i] = NULL;	
	}
//-----------------------------------------------------------------------------------------------------------------> Arvore	
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
			
			//verifica se o usu�rio j� foi inserido e caso j� tenha sido inserido encerra-se a insercao
			for(int j=1;j<=qntCadastros;j++){
				if(strcmp(vetorUsuarios[j].nome,nome) == 0){
					printf("\n\t\t - - - Usuario ' %s ' ja foi inserido - - -\n\n",nome);
					system("pause");
					break;
				}
				
			}
//-----------------------------------------------------------------------------------------------------------------> Vetor de Usuarios para ser usaddo como base na hora de inserir, escluir e etc
		
			strcpy(vetorUsuarios[qntCadastros].nome,nome);
			fscanf(entrada, "%d\n",&vetorUsuarios[qntCadastros].idade); //l� os dados do arquivo
			printf("\tUsuario %s cadastrado\n",vetorUsuarios[qntCadastros].nome);			
			qntCadastros++;
//-----------------------------------------------------------------------------------------------------------------> Vetor de Usuarios para ser usaddo como base na hora de inserir, escluir e etc
	}
	
}

void inserirRelacao(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam], TNo *ptr[tam]){
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
			
//-----------------------------------------------------------------------------------------------------------------> Verificacao se existe o usuario			
		//percorre o vetor at� achar o nome digitado pelo usu�rio e salva a posi��o que ele est� pois 
		//� a mesma que est� na matriz, tanto em linha quanto em coluna		
		for(int i=1;i<qntCadastros;i++){ 
			
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
			break;
		}
//-----------------------------------------------------------------------------------------------------------------> Verificacao se existe o usuario		

//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios	
//		printf("linha %d - Coluna %d\n",linha,coluna);
		matrizUsuarios[linha][coluna] = 1;		
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios		

//-----------------------------------------------------------------------------------------------------------------> Arvore
		insereAVL(ptr,vetorUsuarios[coluna],linha);
//-----------------------------------------------------------------------------------------------------------------> Arvore

	
		cont=0;		
	}
}

void listarSeguidores(int existe, char nomeListaseguidores[20], usuario vetorUsuarios[tam],int matrizUsuarios[tam][tam],int modo,TNo *ptr[tam]){
/*
i.ap�s o usu�rio do programa escolher um usu�rio cadastrado x, esta op��o dever� listar todos os usu�rios os quais x segue e por quais usu�rios x � seguido,
  inclusive com os tempos relacionados � cada rela��o existente; 
ii.no caso da representa��o por lista com adjac�ncias em AVL, fornecer ao usu�rio a op��o de se utilizar algum dos algoritmos de percurso em �rvores in-ordem,
   pr�-ordem ou p�s-ordem.
*/

	int segue=0,eSeguido=0;
	switch(modo){
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios				
		case 1:
			printf("\n\n\n -------------------- Matriz de Pesos ----------------------- ");
			printf("\n\tO usuario Segue:\n"); 
			for(int i=1;i<qntCadastros;i++){ //percorre toda a linha da matriz mostrando todos os usuarios que sao seguidos por esse usu�rio
				if(matrizUsuarios[existe][i] == 1){
					printf("\t\t\t %s\n", vetorUsuarios[i].nome);
					segue=1; //se ele nao seguir n�o entra no if logo abaixo 
				}
			}
			if(segue == 0){
				printf("\t\t\t O usuario nao segue ninguem!\n");
			}
			
			printf("\n\tO usuario eh seguido:\n");
			for(int i=1;i<qntCadastros;i++){ //percorre toda a coluna da matriz mostrando todos os usuarios que est�o seguindo esse usu�rio
				if(matrizUsuarios[i][existe] == 1){
					printf("\t\t\t %s\n", vetorUsuarios[i].nome);
					eSeguido=1; //se alguem seguir nao entra no if logo abaixo 
				}
			}
			
			if(eSeguido == 0){
				printf("\t\t\t O usuario nao eh seguido por ninguem!\n");
			}
			
			
			printf(" -------------------- Matriz de Pesos ----------------------- \n\n");
		break;
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios				
		
		case 2:
			printf("\n\n\n -------------------- lista de adjacencias ----------------------- ");
			printf("\n\n\n -------------------- lista de adjacencias ----------------------- \n\n");
		
		break;
		
		case 3:
			printf("\n\n\n -------------------- lista de adjacencias AVL ----------------------- ");
			
			
			in_ordem(ptr,existe);
			
			
			printf("\n\n\n -------------------- lista de adjacencias AVL -----------------------\n\n");
		
		break;	
	}
}

void listarSeguidoresVelhos(int existe,usuario vetorUsuarios[tam],int matrizUsuarios[tam][tam]){
//i. lista todos os usu�rios que s�o seguidos por usu�rios mais velhos, inclusive com os quantitativos associados a cada um deles.
	int segue=0,eSeguido=0;
	
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios			
	printf("\n\n\n -------------------- Matriz de Pesos ----------------------- \n\n");
	
	printf("\n\t%s com %d anos segue:\n", vetorUsuarios[existe].nome, vetorUsuarios[existe].idade);
	for(int i=1;i<qntCadastros;i++){		
		if(matrizUsuarios[existe][i] == 1){ //verifica se existe e salva a posicao no vetor que ele esta
			//for(int j=1;j<qntCadastros;j++){
				if((vetorUsuarios[existe].idade < vetorUsuarios[i].idade)&&(i!=existe)){
					printf("\t\t %s - %d anos\n", vetorUsuarios[i].nome, vetorUsuarios[i].idade);
					segue=1;
				}
			//}
			
		}
	}
	
	if(segue == 0){
			printf("-> ninguem :( <-");
	}
	
	printf("\n\n -------------------- Matriz de Pesos ----------------------- \n\n");
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios		

}

void atualizarRelacao(int existe, int existe1, usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam]){
/*
i. ocorre similarmente � inser��o de rela��es, por�m a rela��o dever� estar previamente inserida. 
ii. caso a rela��o n�o esteja inserida deve-se oferecer essa op��o ao usu�rio do programa.
*/
	int confirmacao=0,confirmacao1=0;

	printf("\nVoce relamente deseja atualizar a relacao entre %s e %s? 1-sim 2-nao\n",vetorUsuarios[existe].nome,vetorUsuarios[existe1].nome);
	scanf("%s",&confirmacao);
	if(confirmacao == 1){
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios				
		if(matrizUsuarios[existe][existe1] == 0){
			printf("\n\tO usuario %s nao seguia o usuario %s deseja que comece a seguir? 1-sim 2-nao ",vetorUsuarios[existe].nome,vetorUsuarios[existe1].nome);
			scanf("%s",&confirmacao1);
			if(confirmacao1 == 1){
				matrizUsuarios[existe][existe1] = 1;
			}
		}
		else{
			matrizUsuarios[existe][existe1] = 0;
		}
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios		
		
	}
}

void removerUsuario(int existe, usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam]){
/* 
i. remove um usu�rio previamente cadastrado na rede social, inclusive, com todas as suas rela��es; 
ii. caso o usu�rio n�o esteja cadastrado, exibir uma mensagem de erro.
*/
	
	int confirmacao=0,vzs;
	char aux[20];
	
	printf("\n\t VOCE REALMENTE DESEJA REMOVER O USUARIO %s DA REDE? 1-sim 2-nao\n", vetorUsuarios[existe].nome);
	scanf("%d", &confirmacao);
	
	if(confirmacao == 1){
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios				
		strcpy(aux,vetorUsuarios[existe].nome);

//---------------------------- Removendo do vetor ------------------	
		for(int i=existe;i<qntCadastros;i++){
			vetorUsuarios[i] = vetorUsuarios[i+1];
		}
		
//---------------------------- Removendo do vetor ------------------

//---------------------------- Removendo da matriz ------------------		
		for(int i=1;i<qntCadastros;i++){
			matrizUsuarios[existe][i] = matrizUsuarios[existe][i+1];
			matrizUsuarios[i][existe] = matrizUsuarios[i+1][existe];
		}
//---------------------------- Removendo da matriz ------------------		
		qntCadastros--;
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios				
		
		printf("\n\tO usuario %s foi removido e a rede tem  %d usuarios\n",aux,qntCadastros-1);
	}

}

void removerRelacao(int existe,int existe1, usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam]){
/*
i. remove uma rela��o previamente cadastrada na rede social; 
ii. caso algum elemento da rela��o a ser removida (v�rtice ou aresta) n�o esteja inserido, exibir uma mensagem de erro.
*/	
	
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios			
	if(matrizUsuarios[existe][existe1] == 0){
		printf("\n\n\tO usuario %s ja nao seguia o usuario %s", vetorUsuarios[existe].nome, vetorUsuarios[existe1].nome);
	}
	else if(matrizUsuarios[existe][existe1] == 1){
		matrizUsuarios[existe][existe1] = 0;
	}
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios		

}

//----------------------------------------------------------------------------------------------------------------->  ~ MAIN ~
main(){
	
	//declara��o de variaveis e cria��o da struct
	int matrizUsuarios[tam][tam],opcListausuarios,vzs=10,existe=0,modo=0;
	int existe1=0,opcMenu=-1;
	char nomeListaseguidores[20];
	usuario vetorUsuarios[tam], user;
	TNo *ptr[tam];
	
	inicializaGrafos(vetorUsuarios, matrizUsuarios, ptr);
	opcMenu=-1;
	while(opcMenu != 0){
		system("cls");
		printf("\n\n\t  - - - - Programa iniciado - - - -\n\n");
		printf("\t\t  - - - - Menu - - - -\n");
		printf("\t  - - - - - - - - - - - - - - - - - - - - - -\n");
		printf("\t\t 1 -> Inserir Usuarios\n");
		printf("\t\t 2 -> Inserir Relacao\n");
		printf("\t\t 3 -> Listar Seguidores\n");
		printf("\t\t 4 -> Listar seguidores mais velhos\n");
		printf("\t\t 5 -> Atulizar Relacao\n");
		printf("\t\t 6 -> Remover Usuario\n");
		printf("\t\t 7 -> Remover Relacao\n");
		printf("\t\t 0 -> Finalizar o Programa\n");
		printf("\t - - - - - - - - - - - - - - - - - - - - - -\n");
		printf("\t\tOpcao: "); scanf("%d", &opcMenu); printf("\n\n");
		
		
		switch(opcMenu){
			case 1:
				
				inserirUsuario(vetorUsuarios);
				printf("\n\n\t  - - - - %d usuarios cadastrados - - - -\n\n", qntCadastros-1);
				system("pause");
				
			break;
			
			case 2:
				
				inserirRelacao(vetorUsuarios, matrizUsuarios,ptr);
				system("pause");
				
			break;
			
			case 3:
				//--------------------------------- Listando os seguidores do usu�rio a ser escolhido -----------------------------------------------------------
				existe=0;
				printf("\n\nVoce deseja listar todos os usuarios ? 1-sim 2-nao\n");
				scanf("%d",&opcListausuarios); printf("\n\n\t");
			
				vzs=10; //Pra quando houver mais de x usuarios cadastrados, esse n�mero ser usado como base para quebraa de linha no for a abaixo
				if(opcListausuarios == 1){
					printf("\n\n\t\t\t\t\t- Todos usuarios -\n\t");
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
				}
					
				while(existe == 0){
					printf("\n\nDigite o nome a ser listado: ");
					scanf("%s", &nomeListaseguidores);
					for(int i=1;i<qntCadastros;i++){
						if(strcmp(nomeListaseguidores, vetorUsuarios[i].nome)==0){ //verifica se existe e salva a posicao no vetor que ele esta
							existe=i;
						}
					}
					
					if(existe == 0){
						printf("O nome digitado nao esta cadastrado na rede. Digite novamente!\n");
						system("pause");
					}	
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
					
				listarSeguidores(existe, nomeListaseguidores,vetorUsuarios,matrizUsuarios,modo,ptr);
				modo=0;	   
				
			
				system("pause");
			//---------------------------------- Listando os seguidores do usu�rio a ser escolhido -----------------------------------------------------------

			break;
			
			case 4:
				//---------------------------------- Listando quem o usuario mais velho segue -----------------------------------------------------------
					
					printf("\n\n\t\t\t\t\t- Todos usuarios -\n\t");
					vzs=10;
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
					
					existe = 0;
					while(existe==0){
						printf("\n\nDigite o nome do usuario a ser verificado: ");
						scanf("%s", &nomeListaseguidores);
						for(int i=1;i<qntCadastros;i++){
							if(strcmp(nomeListaseguidores, vetorUsuarios[i].nome)==0){ //verifica se existe e salva a posicao no vetor que ele esta
								existe=i;
							}
						}
						
						if(existe == 0){
							printf("O nome digitado nao esta cadastrado na rede. Digite novamente!\n");
							system("pause");
						}
					}
					
					listarSeguidoresVelhos(existe,vetorUsuarios,matrizUsuarios);	
					existe=-1;
					system("pause");
				
			//---------------------------------- Listando quem o usuario mais velho segue -----------------------------------------------------------

			break;
			
			case 5:
				
				//---------------------------------- Atualizando relacoes -----------------------------------------------------------					
					existe = 0; existe1=0;
					while(existe==0||existe1==0){
						printf("\n\nDigite o nome do usuario que vai comecar de seguir: ");
						scanf("%s", &nomeListaseguidores);
						for(int i=1;i<qntCadastros;i++){
							if(strcmp(nomeListaseguidores, vetorUsuarios[i].nome)==0){ //verifica se existe e salva a posicao no vetor que ele esta
								existe=i;
							}
						}
						
						if(existe == 0){
							printf("O primeiro nome digitado nao esta cadastrado na rede. Digite novamente!\n");
							system("pause");
						}
					
						printf("\n\nDigite o nome do usuario que vai parar ou comecar ser seguido: ");
						scanf("%s", &nomeListaseguidores);
						for(int i=1;i<qntCadastros;i++){
							if(strcmp(nomeListaseguidores, vetorUsuarios[i].nome)==0){ //verifica se existe e salva a posicao no vetor que ele esta
								existe1=i;
							}
						}
						
						if(existe1 == 0){
							printf("O segundo nome digitado nao esta cadastrado na rede. Digite novamente!\n");
							system("pause");
						}	
					}
					
					atualizarRelacao(existe, existe1,vetorUsuarios,matrizUsuarios);
					existe=-1;existe1=-1;

			
			//---------------------------------- Atualizando relacoes -----------------------------------------------------------				
			break;
			
			case 6:
				
				//---------------------------------- removendo um usu�rio -----------------------------------------------------------
				
					printf("\n\n\t\t\t\t\t- Todos usuarios -\n\t");
				
					vzs=10;
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
				
					existe = 0;
					
					
					while(existe==0){
						printf("\n\nDigite o nome a ser removido: ");
						scanf("%s", &nomeListaseguidores);
						for(int i=1;i<qntCadastros;i++){
							if(strcmp(nomeListaseguidores, vetorUsuarios[i].nome)==0){ //verifica se existe e salva a posicao no vetor que ele esta
								existe=i;
							}
						}
						
						if(existe == 0){
							printf("O nome digitado nao esta cadastrado na rede. Digite novamente!\n");
							system("pause");
						}	
					}
				
					removerUsuario(existe,vetorUsuarios,matrizUsuarios);

			//---------------------------------- removendo um usu�rio -----------------------------------------------------------		

				
			break;
			
			case 7:
				
				//---------------------------------- removendo uma relacao -----------------------------------------------------------
								
						printf("\n\n\t\t\t\t\t- Todos usuarios -\n\t");
						vzs=10;
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
						
						
						existe = 0; existe1=0;
						while(existe==0||existe1==0){
							printf("\n\nDigite o nome do usuario que vai parar de seguir: ");
							scanf("%s", &nomeListaseguidores);
							for(int i=1;i<qntCadastros;i++){
								if(strcmp(nomeListaseguidores, vetorUsuarios[i].nome)==0){ //verifica se existe e salva a posicao no vetor que ele esta
									existe=i;
								}
							}
							
							if(existe == 0){
								printf("O nome digitado nao esta cadastrado na rede. Digite novamente!\n");
								system("pause");
							}
						
							printf("\n\nDigite o nome do usuario que vai parar de ser seguido: ");
							scanf("%s", &nomeListaseguidores);
							for(int i=1;i<qntCadastros;i++){
								if(strcmp(nomeListaseguidores, vetorUsuarios[i].nome)==0){ //verifica se existe e salva a posicao no vetor que ele esta
									existe1=i;
								}
							}
							
							if(existe1 == 0){
								printf("O nome digitado nao esta cadastrado na rede. Digite novamente!\n");
								system("pause");
							}	
						}
						removerRelacao(existe,existe1,vetorUsuarios,matrizUsuarios);					
				//---------------------------------- removendo uma relacao -----------------------------------------------------------
			break;
			
			case 0:
				system("cls");
				printf("\n\n\n\n \t\tO programa chegou ao seu fim - igual a minha vontade de viver :(\n\n\n\n\t\t\t");			
				system("pause");
			break;
		}
		
	}
}
