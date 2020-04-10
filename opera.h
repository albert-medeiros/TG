/* 
   
   Regras:
	1-> Usuarios s�o inseridos atraves do arquivo.txt sendo que s�o dispostos nome em na primeira linha e idade logo na de baixo
	2-> A inser��o de quem segue quem tbm e feita atraves do arquivo seguir.txt no qual � disposto na primeira linha quem segue e na loga na de baixo quem � seguido
    3-> Em todas as verificacoes comeca-se no 1 pois o vetor tem 51 posicoes
    4-> A variavel linha representa a posicao de quem vai comecar a seguir 
    5-> A variavel coluna representa a posicao de quem vai comecar a ser seguido
    
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


//-----------------------------------------------------------------------------------------------------------------> Comeco Funcoes usadas exclusivamenetes na Arvore AVL
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


//


void in_ordem(TNo *ptr){
	if((ptr) != NULL){
		in_ordem((ptr)->esq);		
		printf("\t\t\t %s\n",(ptr)->user.nome);	
		in_ordem((ptr)->dir);
	}
	else{
		printf("\t\t\t O usuario nao segue ninguem!\n");
	}
}

void insereAVL(TNo **ptr, TipoUsuario user){
	
	//printf("Entrou no InsereAVL e vai inserir na linha %d o usuario %s\t",linha,user.nome);
	int FB,fb;
		
	if (*ptr == NULL ){ // entra na hora de criar um novo n�
		(*ptr) = ALOCA; //aloco dinamicamente um espa�o pra "ptr"
		(*ptr)->esq = NULL;
		(*ptr)->dir = NULL;
		strcpy((*ptr)->user.nome, user.nome); // o n� recebe o valor do nome
		(*ptr)->user.idade = user.idade; // o n� recebe os outros valores
	}
	
	else{
		if(user.idade<(*ptr)->user.idade){ //verifica��o para saber em qual lado � inserido o valor
			insereAVL(&(*ptr)->esq,user); //passa o valor da esquerda se for menor
		}
		else if(user.idade>(*ptr)->user.idade){ //verifica��o para saber em qual lado � inserido o valor
			insereAVL(&(*ptr)->dir,user); //passa o valor da direita se for maior
		}
	}
	
	//FB - Pai;  
	//fb - filho;
	//Ap�s inserir o valor � verifica do Fator de balanceamento
	
	
	FB=(altura((*ptr)->dir))-(altura((*ptr)->esq)); //calcula a altura ao desempilhar
	
	if(FB == +2){ //caso o FB do n� seja 2 ent�o tem que fazer altera��o 
			
		fb = altura((*ptr)->dir->dir)-altura((*ptr)->dir->esq); //calcula a altura do filho da direita
		
		if(fb == 1){ // se for igual a um ent�o rota��o simples 
			rotacaoEsq(&(*ptr));
		}
			
		else if(fb == -1){ // se for igual a menos um ent�o rota��o dulpa
			rotacaoDir(&(*ptr)->dir);
			rotacaoEsq(&(*ptr));
		}
	}
		
	else if(FB == -2){
	
		fb = (altura((*ptr)->esq->dir))-(altura((*ptr)->esq->esq)); //calcula a altura do filho da direita
		if(fb == -1){ // se for igual a um ent�o rota��o simples 
			rotacaoDir(&(*ptr));
		}
	
		else if(fb == +1){ // se for igual a menos um ent�o rota��o dulpa
			rotacaoEsq(&(*ptr)->esq);
			rotacaoDir(&(*ptr));
		}	
	}
}
int retorno;
void pUsuario(TNo *ptr,char nome,int idade){
	int quant=1;
	char nombre[20] = (ptr->user.nome);
	TNo *aux;
	if(strcmp(nombre , nome) == 0){
		retorno=1;
	}
	else{	
		while((ptr!= NULL)&&(strcmp(nombre,nome) == 0)){
			quant++;
			
			//aux armzena o n� raiz da sub arvore pesquisada ficando 1 atrasado 
			aux = ptr;
			if(idade>ptr->user.idade){
				ptr=ptr->dir;
			}
			
			else{
				ptr = ptr->esq;
			}
		}
		if(ptr==NULL){
			retorno=0;
		}
		else{
			retorno=1;
		}
	}
}
	
//-----------------------------------------------------------------------------------------------------------------> Fim Funcoes usadas exclusivamenetes na Arvore AVL



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

void inserirRelacao(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam], TNo **ptr){
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
	TNo *ptrAux;
	usuario usuariosAux;
	
	FILE *seguir = fopen("seguir.txt", "r"); //abertura do arquivo	
	if(seguir == NULL){
		printf("\t  -> Erro na abertura do arquivo");
		system("pause");
	}
	
	while(!feof(seguir)){ // responsavel por ler at� o fim do arquivo
		fscanf(seguir, "%s\n",&nomeSeguidor); //l� os dados de quem vai comecar a seguir 
		fscanf(seguir, "%s\n",&nomeSeguido); //l� os dados de quem vai comecar a ser seguido
		
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
		printf("\t\t\t\t-> Valor inserido na Matriz de adjacencias");
		matrizUsuarios[linha][coluna] = 1;		
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios		

//-----------------------------------------------------------------------------------------------------------------> Arvore
		/* estava dando problema quando eu tentava mandar inserir ja no vetor direto, entao, foi criado auxiliares para a posicao que era da arvore 
		e para os dados que vao ser inseridos pois desta forma as alteracoes que seriam feitas na funcao sao menores e funcionaram (hihihihihi), portanto, 
		apos enviar a posicao do vetor de arvore recebe de volta os dados atualizados */
		
		ptrAux = ptr[linha];
		usuariosAux = vetorUsuarios[coluna];
		
		insereAVL(&ptrAux,usuariosAux);
		ptr[linha] = ptrAux;
//-----------------------------------------------------------------------------------------------------------------> Arvore

	
		cont=0;		
	}
}

void listarSeguidores(int existe, usuario vetorUsuarios[tam],int matrizUsuarios[tam][tam],int modo,TNo *ptr[tam]){
/*
i.ap�s o usu�rio do programa escolher um usu�rio cadastrado x, esta op��o dever� listar todos os usu�rios os quais x segue e por quais usu�rios x � seguido,
  inclusive com os tempos relacionados � cada rela��o existente; 
ii.no caso da representa��o por lista com adjac�ncias em AVL, fornecer ao usu�rio a op��o de se utilizar algum dos algoritmos de percurso em �rvores in-ordem,
   pr�-ordem ou p�s-ordem.
*/

	int segue=0,eSeguido=0;
	TNo *ptrAux;
	usuario usuariosAux;
	
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
			printf("\n\n\n -------------------- lista de adjacencias AVL ----------------------- \n\n");
			
			ptrAux = ptr[existe];
//			usuariosAux = vetorUsuarios[coluna];			
			in_ordem(ptrAux); // nesse caso irao ser listados os usuarios da rede que sao seguidos pelo passado pelo usuario do programa
			for(int i=1;i<qntCadastros;i++){
				retorno = pUsuario(ptr,vetorUsuarios[existe].nome,vetorUsuarios[existe].idade);
				if(retorno == 1){
					printf("\t\t\t %s\n", vetorUsuarios[i].nome);
				}
			
				retorno=0;
			}
			
			
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

void printaTodosUsuarios(usuario vetorUsuarios[tam]){

	int vzs=10; //Pra quando houver mais de x usuarios cadastrados, esse n�mero ser usado como base para quebraa de linha no for a abaixo
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

int verificaSeExiste(usuario vetorUsuarios[tam],char nomeListaCadastrados[20]){ /*funcao responsavel por verificar se o usuario digitado na main esta cadastrado na rede
retornando a posicao que ele se encotra no vetor responsavel por armazenar os cadastros (vetorUsuarios) */
	
	int posicao = 0;
	for(int i=1;i<qntCadastros;i++){
		if(strcmp(nomeListaCadastrados, vetorUsuarios[i].nome)==0){ //verifica onde que e igual e se existe e salva a posicao no vetor que ele esta
			posicao=i;
			break;
		}
	}
	
	if(posicao == 0){ //caso n�o encontrar
		printf("O nome digitado nao esta cadastrado na rede. Digite novamente!\n");
		system("pause");
		return 0;
	}
	else{ //caso encontrar
		return posicao; 
	}
	
}

