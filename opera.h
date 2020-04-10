/* 
   
   Regras:
	1-> Usuarios são inseridos atraves do arquivo.txt sendo que são dispostos nome em na primeira linha e idade logo na de baixo
	2-> A inserção de quem segue quem tbm e feita atraves do arquivo seguir.txt no qual é disposto na primeira linha quem segue e na loga na de baixo quem é seguido
    3-> Em todas as verificacoes comeca-se no 1 pois o vetor tem 51 posicoes
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

typedef struct no{ //struct para armazenar os valores salvos na árvore
	struct no *esq,*dir; // aponta para o proximo no
	TipoUsuario user; //chave real
} TNo;

//----------------------------------------------------------------------- STRUCT / INICIALIZA ------------------------------------------------------------------------------------

int altura(TNo *ptr){  
	if (ptr == NULL){ //Caso não haja algum nó na árvore
		return -1; //return -1 - altura 
	}
	
	else{
		int he = altura(ptr->esq); //percorrer a esquerda
		int hd = altura(ptr->dir); //percorrer a direita
		if(he<hd){ 		//verifica qual das ramificações é maior
			return hd+1;	//conta os níveis das ramificações da direita
		}
		else{
			return he+1;	//conta os níveis das ramificações da esquerda
		}
	}
}

void rotacaoDir(TNo **ptr){
	
	TNo *q,*temp; //ponteiro
	q = (*ptr)->esq; //q vai receber a sub árvore a esquerda
	temp = q->dir; //sub árvore a direita de q 
	q->dir = (*ptr); //aponta pra raiz da sub árvore passada
	(*ptr)->esq = temp; //a raiz vai apontar pra temp
	(*ptr) = q; //defino que q vai ser a nov raiz
	
}

void rotacaoEsq(TNo **ptr){
	TNo *q,*temp; //ponteiro
	
	q = (*ptr)->dir; //q vai receber a sub árvore a direita
	temp = q->esq; //sub árvore a ESQUERDA de q 
	q->esq = (*ptr); //aponta pra raiz da sub árvore passada
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
int entrou1 =0,entrou2=0;
void insereAVL(TNo *ptr[tam], TipoUsuario user,int linha){
	
	//printf("Entrou no InsereAVL e vai inserir na linha %d o usuario %s\t",linha,user.nome);
	int FB,fb;
		
	if (ptr[linha] == NULL && entrou1==0){ // entra na hora de criar um novo nó
		(ptr[linha]) = ALOCA; //aloco dinamicamente um espaço pra "ptr"
		(ptr[linha])->esq = NULL;
		(ptr[linha])->dir = NULL;
		strcpy((ptr[linha])->user.nome, user.nome); // o nó recebe o valor do nome
		(ptr[linha])->user = user; // o nó recebe os outros valores
		entrou1 =1;
	}
	
	else if (*ptr == NULL && entrou1 == 1){ // entra na hora de criar um novo nó
	printf("Entrou aqui irmão ->\t");
		(*ptr) = ALOCA; //aloco dinamicamente um espaço pra "ptr"
		(*ptr)->esq = NULL;
		(*ptr)->dir = NULL;
		(*ptr)->user = user; // o nó recebe os outros valores
	}
	
	else{
				
			if(user.idade<(ptr[linha])->user.idade){ //verificação para saber em qual lado é inserido o valor			
				insereAVL(&(*ptr[linha]).esq,user,linha); //passa o valor da esquerda se for menor
			}
			else if(user.idade>(ptr[linha])->user.idade){ //verificação para saber em qual lado é inserido o valor			
				insereAVL(&(*ptr[linha]).dir, user, linha); //passa o valor da direita se for maior
			}
	}
	
	//FB - Pai;  
	//fb - filho;
	//Após inserir o valor é verifica do Fator de balanceamento
	
	
	FB=(altura((ptr[linha])->dir))-(altura((ptr[linha])->esq)); //calcula a altura ao desempilhar
	printf("\n\n\n\t\t\t%d\n\n\n\n",FB);
	
	if(FB == +2){ //caso o FB do nó seja 2 então tem que fazer alteração 
		printf("\n\t\t\tEntrou1: %d - entrou2: %d",entrou1,entrou2);
			
		fb = altura((ptr[linha])->dir->dir)-altura((ptr[linha])->dir->esq); //calcula a altura do filho da direita
		
		if(fb==1){ // se for igual a um então rotação simples 
			rotacaoEsq(&ptr[linha]);
		}
			
		else if(fb == -1){ // se for igual a menos um então rotação dulpa
			rotacaoDir(&(ptr[linha])->dir);
			rotacaoEsq(&ptr[linha]);
		}
	}
		
	else if(FB == -2){
		printf("\n\t\t\tEntrou1: %d - entrou2: %d",entrou1,entrou2);
	
		fb = (altura((ptr[linha])->esq->dir))-(altura((ptr[linha])->esq->esq)); //calcula a altura do filho da direita
		if(fb== -1){ // se for igual a um então rotação simples 
			rotacaoDir(&ptr[linha]);
		}
	
		else if(fb== +1){ // se for igual a menos um então rotação dulpa
			rotacaoEsq(&(ptr[linha])->esq);
			rotacaoDir(&ptr[linha]);
		}	
	}
}
	
//-----------------------------------------------------------------------------------------------------------------> Arvore



void inicializaGrafos(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam], TNo **ptr){ 
/*
i. preenche a matriz de pesos com zeros, aloca uma posição de memória (posição 0) para as listas de adjacência e adjacência em AVL e faz com o que seus conteúdos apontem para NULL; 
ii. não é necessário oferecer essa opção ao usuário; 
iii. poderão ser utilizados os índices da lista de 1 a n
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
			
			//verifica se o usuário já foi inserido e caso já tenha sido inserido encerra-se a insercao
			for(int j=1;j<=qntCadastros;j++){
				if(strcmp(vetorUsuarios[j].nome,nome) == 0){
					printf("\n\t\t - - - Usuario ' %s ' ja foi inserido - - -\n\n",nome);
					system("pause");
					break;
				}
				
			}
//-----------------------------------------------------------------------------------------------------------------> Vetor de Usuarios para ser usaddo como base na hora de inserir, escluir e etc
		
			strcpy(vetorUsuarios[qntCadastros].nome,nome);
			fscanf(entrada, "%d\n",&vetorUsuarios[qntCadastros].idade); //lê os dados do arquivo
			printf("\tUsuario %s cadastrado\n",vetorUsuarios[qntCadastros].nome);			
			qntCadastros++;
//-----------------------------------------------------------------------------------------------------------------> Vetor de Usuarios para ser usaddo como base na hora de inserir, escluir e etc
	}
	
}

void inserirRelacao(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam], TNo *ptr[tam]){
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
			
//-----------------------------------------------------------------------------------------------------------------> Verificacao se existe o usuario			
		//percorre o vetor até achar o nome digitado pelo usuário e salva a posição que ele está pois 
		//é a mesma que está na matriz, tanto em linha quanto em coluna		
		for(int i=1;i<qntCadastros;i++){ 
			
			if(strcmp(vetorUsuarios[i].nome,nomeSeguidor) == 0){
				linha = i;				
				cont++;
				if(cont == 2){  //caso tenha entrado duas vezes, uma vez em cada "if", ja para a verificacao não necessitando percorrer o resto do vetor pois ja foi encontrada a posicao do seguidor e do seguido 
					break;
				}
			}
			
			if(strcmp(vetorUsuarios[i].nome,nomeSeguido) == 0){
				coluna = i;
				
				cont++;
				if(cont == 2){  //caso tenha entrado duas vezes, uma vez em cada "if", ja para a verificacao não necessitando percorrer o resto do vetor pois ja foi encontrada a posicao do seguidor e do seguido
					break;
				}
			}
		}
		
		if(cont != 2){ // se nao entrou duas vezes não tem algum usuario
			printf("\n\t - somente um usuário encontrado - ");
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

void listarSeguidores(int existe, usuario vetorUsuarios[tam],int matrizUsuarios[tam][tam],int modo,TNo *ptr[tam]){
/*
i.após o usuário do programa escolher um usuário cadastrado x, esta opção deverá listar todos os usuários os quais x segue e por quais usuários x é seguido,
  inclusive com os tempos relacionados à cada relação existente; 
ii.no caso da representação por lista com adjacências em AVL, fornecer ao usuário a opção de se utilizar algum dos algoritmos de percurso em árvores in-ordem,
   pré-ordem ou pós-ordem.
*/

	int segue=0,eSeguido=0;
	switch(modo){
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios				
		case 1:
			printf("\n\n\n -------------------- Matriz de Pesos ----------------------- ");
			printf("\n\tO usuario Segue:\n"); 
			for(int i=1;i<qntCadastros;i++){ //percorre toda a linha da matriz mostrando todos os usuarios que sao seguidos por esse usuário
				if(matrizUsuarios[existe][i] == 1){
					printf("\t\t\t %s\n", vetorUsuarios[i].nome);
					segue=1; //se ele nao seguir não entra no if logo abaixo 
				}
			}
			if(segue == 0){
				printf("\t\t\t O usuario nao segue ninguem!\n");
			}
			
			printf("\n\tO usuario eh seguido:\n");
			for(int i=1;i<qntCadastros;i++){ //percorre toda a coluna da matriz mostrando todos os usuarios que estão seguindo esse usuário
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
//i. lista todos os usuários que são seguidos por usuários mais velhos, inclusive com os quantitativos associados a cada um deles.
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
i. ocorre similarmente à inserção de relações, porém a relação deverá estar previamente inserida. 
ii. caso a relação não esteja inserida deve-se oferecer essa opção ao usuário do programa.
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
i. remove um usuário previamente cadastrado na rede social, inclusive, com todas as suas relações; 
ii. caso o usuário não esteja cadastrado, exibir uma mensagem de erro.
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
i. remove uma relação previamente cadastrada na rede social; 
ii. caso algum elemento da relação a ser removida (vértice ou aresta) não esteja inserido, exibir uma mensagem de erro.
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

void printaTodosUsuarios(usuario vetorUsuarios[tam]){

	int vzs=10; //Pra quando houver mais de x usuarios cadastrados, esse número ser usado como base para quebraa de linha no for a abaixo
	printf("\n\n\t\t\t\t\t- Todos usuarios -\n\t");
		for(int i=1;i<qntCadastros;i++){ //printa os usuários cadastrados
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

int verificaSeExiste(usuario vetorUsuarios[tam],char nomeListaCadastrados[20]){ /*funcao responsavel por verificar se o usuario digitado na main esta cadastrado na rede
retornando a posicao que ele se encotra no vetor responsavel por armazenar os cadastros (vetorUsuarios) */
	
	int posicao = 0;
	for(int i=1;i<qntCadastros;i++){
		if(strcmp(nomeListaCadastrados, vetorUsuarios[i].nome)==0){ //verifica onde que e igual e se existe e salva a posicao no vetor que ele esta
			posicao=i;
		}
	}
	
	if(posicao == 0){ //caso não encontrar
		printf("O nome digitado nao esta cadastrado na rede. Digite novamente!\n");
		system("pause");
		return 0;
	}
	else{ //caso encontrar
		return posicao; 
	}
	
}

