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
#define ALOCA1 (TLista*)malloc(sizeof(TLista))

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

typedef struct lista{ //struct para armazenar os valores salvos na �rvore
	struct lista *prox; // aponta para o proximo no
	TipoUsuario user; //chave real
} TLista;

struct TipoLista{
	lista *primeiro,*ultimo ;
}; 

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
}

void in_ordem1(TNo *ptr,usuario user){
	if((ptr) != NULL){
		in_ordem1((ptr)->esq,user);
		if((ptr)->user.idade>user.idade){
			printf("\t\t %s - %d anos\n", (ptr)->user.nome, (ptr)->user.idade);		
		}
		in_ordem1((ptr)->dir,user);
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
		if(user.idade<=(*ptr)->user.idade){ //verifica��o para saber em qual lado � inserido o valor
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

void sucessor(TNo *q,TNo **r){
	if((*r)->esq != NULL){  //recursivamente para ir no �ltimo da esquerda
		sucessor(q,&(*r)->esq);
	}
	else{ //faz a troca e apaga o n� 
		q->user = (*r)->user;	//aluno recebe os dados dos da struct r
		q = (*r); //posi��o da chave
		(*r) = (*r)->dir; //passa a chave dir para o n�
		free(q);
	}
}


void retiraAVL(TNo **ptr, usuario user){
	int FB,fb;
	if((*ptr)==NULL){ //verifica se o valor est� na �rvore
		//printf("\n O usuario %s nao esta na arvore!\n",user.nome);
	}
	
	else if(user.idade<=(*ptr)->user.idade && (strcmp((*ptr)->user.nome,user.nome) != 0)){ //verifica o lado que tem que seguir 
		retiraAVL(&(*ptr)->esq,user);
	}
	else if(user.idade>(*ptr)->user.idade){
		retiraAVL(&(*ptr)->dir,user);
	}
	else if(strcmp((*ptr)->user.nome,user.nome) == 0){ //caso for a chave retirada
		TNo *aux = *ptr;	//copia o calor a ser retirado 
		if((*ptr)->dir == NULL){	//se a direita for NULL esq fica no lugar 
			(*ptr)=(*ptr)->esq;
			free(aux);
		}
		else if((*ptr)->esq==NULL){ //se a esq for NULL dir fica no lugar 
			(*ptr)=(*ptr)->dir;
			free(aux);
		}
		else if((*ptr)->esq==NULL && (*ptr)->dir==NULL){
			free(aux);free(ptr);
		}
		else{ // caso haja dois filhos
//			if(sor == 1){
				sucessor((*ptr),&(*ptr)->dir);
			
//			else{
//				antecessor((*ptr),&(*ptr)->esq);
//			}
		}
	}
	
	if((*ptr)!=NULL){ // Para n�o verificar o n� que foi retirado e esperar a recursividade voltar para assim entrar dentro do if
		FB=altura((*ptr)->dir)-altura((*ptr)->esq); //calcula a altura ao desempilhar
	//	printf("FB: %d\n",FB);	
		
		if(FB==2){ //caso o FB do n� seja 2 ent�o tem que fazer altera��o 
				
			fb = altura((*ptr)->dir->dir)-altura((*ptr)->dir->esq); //calcula a altura do filho da direita
			if((fb == 1) || (fb == 0)){ // se for igual a um ent�o rota��o simples 
				rotacaoEsq(ptr);
			}	
			else if(fb == -1){ // se for igual a menos um ent�o rota��o dulpa
				rotacaoDir(&(*ptr)->dir);
				rotacaoEsq(ptr);
			}
		}
			
		else if(FB == -2){
						
			fb = (altura((*ptr)->esq->dir))-(altura((*ptr)->esq->esq)); //calcula a altura do filho da direita
			if(fb == -1 || fb == 0){ // se for igual a um ent�o rota��o simples 
				rotacaoDir(ptr);
			}
			else if(fb == 1){ // se for igual a menos um ent�o rota��o dulpa
				rotacaoEsq(&(*ptr)->dir);
				rotacaoDir(ptr);
			}	
		}
	}
	
//	printf("\n\nVai verificar aqui nesse negocio:\n");in_ordem(ptr);
}


void pesquisa(TNo *ptr,usuario user){
	int quant=1;
	while((ptr!= NULL) && (strcmp(ptr->user.nome,user.nome) == 0)){
		quant++; //A cada ciclo soma 1 para saber o numero de compara��es	
		if(user.idade > ptr->user.idade){ //dire��o que a chave percorre
			ptr = ptr->dir;
		}
		else{
			ptr = ptr->esq;
		}
	}
	if(ptr==NULL){
		printf("-> ninguem :( <-");
	}
	else{
		in_ordem1(ptr, user);
	}
}


//void pesquisaParaAtualizar(TNo *ptr,TNo *ptrSeguido,usuario vetorUsuarios[tam],int existe,int existe1){
//	int quant=1,opc=0,opc1=0;
//	TNo *ptrAux;TNo *ptrAux1;
//	usuario usuariosAux;
//	
//	
//	while((ptr!= NULL)&&(strcmp(ptr->user.nome,vetorUsuarios[existe1].nome) != 0)){
//		quant++; //A cada ciclo soma 1 para saber o numero de compara��es	
//		if(vetorUsuarios[existe1].idade > ptr->user.idade){ //dire��o que a chave percorre
//			ptr = ptr->dir;
//		}
//		else{
//			ptr = ptr->esq;
//		}
//	}
//	if(ptr==NULL){
//		usuariosAux = vetorUsuarios[existe1];		
//		insereAVL(&ptrAux,usuariosAux);
//		
//		usuariosAux = vetorUsuarios[existe];		
//		insereAVL(&ptrAux1,usuariosAux);
//	}
//	else{
//		retiraAVL(&ptrAux,vetorUsuarios[existe1]);
//		retiraAVL(&ptrAux1,vetorUsuarios[existe]);
//		
//	}
//}

//void antecessor(TNo *q,TNo **r){
//	if((*r)->dir != NULL){ //recursivamente para ir no �ltimo na direita DA ESQUERDA
//		antecessor(q,&(*r)->dir);
//	}
//	else{ //faz a troca e apaga o n� 
//		q->user = (*r)->user; //copia do antecessor pro lugar da chave apagada
//		q = (*r); //posi��o da chave
//		
//		(*r) = (*r)->esq; //passa a chave esquerda para o n�	
//		
//		free(q); //apaga o n� 
//	}
//}


	
//-----------------------------------------------------------------------------------------------------------------> Fim Funcoes usadas exclusivamenetes na Arvore AVL

void imprimeLista(TipoLista list){
	TLista *Aux;
	Aux = list.primeiro->prox;
	while (Aux != NULL){
		printf("\t\t\t %s \n", Aux->user.nome);
		Aux = Aux->prox;
	}
	
}

void FLVazia(TipoLista *lista){
	lista->primeiro = ALOCA1;
	lista->ultimo = lista->primeiro ;
	lista->primeiro->prox = NULL;
}



void insereLista(TipoUsuario user, TipoLista *Lista){
	Lista->ultimo->prox = ALOCA1;
	Lista->ultimo = Lista->ultimo->prox;
	Lista->ultimo->user = user;
	Lista->ultimo->prox = NULL;
}

void removeLista(TipoUsuario user, TipoLista *list){
	

	TLista *auxComeco,*auxFim,*posicao1,*posicao2;
	TLista vetorLista[tam];
	TipoLista *listaAux = list,listaFinal,*listaVerificacao=list;
	usuario usuariosAux;
	TipoLista lstAux, lstAux1;
	auxComeco = list->primeiro;
	auxFim = list->ultimo;
	
	
	int cont=1,posicaoRemover=-1,i=0,flag=0;
	printf("\t -----------------------");
	
	

	if(auxComeco->prox == auxFim){ //se s� tem um usuario seguindo ou sendo seguido ele zera a lista novamente, o ultimo e o primero apontam pro mesmo lugar
		printf("entrou aqui 1");
		list->ultimo = list->primeiro;
		list->primeiro->prox = NULL;
		
	}

	else if(strcmp(auxComeco->prox->user.nome,user.nome) == 0){
		printf("entrou aqui 2");
		list->primeiro->prox=list->primeiro->prox->prox;
		
	}

	else{ //se n�o for o primeiro nem o ultimo entra aqui 
		printf("entrou aqui 3");
		while(strcmp(auxComeco->prox->user.nome,listaAux->ultimo->user.nome) !=0 ){
			if(strcmp(listaVerificacao->primeiro->user.nome,user.nome)==0){
				flag=1;
				break;;
			}
		}
				
		if(flag==1){
				FLVazia(&listaFinal);
			while(auxComeco!=NULL){//strcmp(auxComeco->prox->user.nome,list->ultimo->user.nome)!=0){
			printf("a -");
				
				vetorLista[i].prox = auxComeco->prox->prox;
				vetorLista[i].user = auxComeco->prox->user;
							
				if(strcmp(auxComeco->prox->user.nome,user.nome)==0){
					posicaoRemover=cont;
				}
				
				if(strcmp(auxComeco->prox->user.nome,listaAux->ultimo->user.nome)==0){
					break;
				}
				
				cont= cont+1;
	
				auxComeco->prox = auxComeco->prox->prox;			
				i++;
			}
	
			if(posicaoRemover != -1){
				for(int i=0;i<cont;i++){
					usuariosAux = vetorLista[i].user;
					if(i != posicaoRemover-1){
						insereLista(usuariosAux,&listaFinal);	
					}
				}
				list->primeiro = listaFinal.primeiro;	
			}
		}					
	}
}




void imprimeLista1(TipoLista list,usuario user){
	TLista *Aux;
	Aux = list.primeiro->prox;
	while (Aux != NULL){
		if(Aux->user.idade>user.idade){
			printf("\t\t %s - %d anos\n", Aux->user.nome, Aux->user.idade);
		}	
		Aux = Aux->prox;
	}
}



void inicializaGrafos(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam], TNo **ptr , TNo **ptrSeguido , TipoLista listaSegue[tam] , TipoLista listaSeguido[tam]){ 
/*
i. preenche a matriz de pesos com zeros, aloca uma posi��o de mem�ria (posi��o 0) para as listas de adjac�ncia e adjac�ncia em AVL e faz com o que seus conte�dos apontem para NULL; 
ii. n�o � necess�rio oferecer essa op��o ao usu�rio; 
iii. poder�o ser utilizados os �ndices da lista de 1 a n
*/
	TipoLista listaAux;

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
	
	for(int i=0;i<tam;i++){
		ptrSeguido[i] = NULL;
	}
//-----------------------------------------------------------------------------------------------------------------> Arvore	

//	for(int i=0;i<tam;i++){
//		lstSegue[i] = ALOCA1;
//		lstSegue[i]->primeiro = ALOCA1;
//		lstSegue[i]->ultimo = lstSegue[i]->primeiro ;		
//		lstSegue[i]->primeiro->prox = NULL;	
//	}
//	for(int i=0;i<tam;i++){
////		lstSeguido[i] = ALOCA1;
////		lstSeguido[i]->primeiro = ALOCA1;
////		lstSeguido[i]->ultimo = lstSeguido[i]->primeiro ;
////		lstSeguido[i]->primeiro->prox = NULL;
//		lstSeguido[i] = ALOCA1;
//		lstSeguido[i]->primeiro = ALOCA1;
//		lstSeguido[i]->ultimo = lstSeguido[i]->primeiro ;		
//		lstSeguido[i]->primeiro->prox = NULL;	
//	}
	
	for(int i=0;i<tam;i++){
		listaAux = listaSegue[i];
		FLVazia(&listaAux);
		listaSegue[i] = listaAux;
	}
	
	for(int i=0;i<tam;i++){
		listaAux = listaSeguido[i];
		FLVazia(&listaAux);
		listaSeguido[i] = listaAux;
	}
	
	
}

void inserirUsuario(usuario vetorUsuarios[tam]){

/*
i. libera, dinamicamente, uma linha e uma coluna da matriz de pesos para representar as rela��es do novo usu�rio, aloca uma posi��o de mem�ria em cada uma das listas e realiza a inser��o de tal usu�rio pelo nome (que ser� fornecido); 
ii. o programa dever� verificar se o usu�rio j� est� inserido e, caso positivo, retornar uma mensagem de erro.
*/

	char nome[20];
	int entrou=0;
	
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
					entrou=1;
					break;
				}
				
			}
			if(entrou == 1){
				printf("\n\t\t\t A insecao sera encerrada\n\n");
				system("pause");
				break;
			}
			//-----------------------------------------------------------------------------------------------------------------> Vetor de Usuarios para ser usaddo como base na hora de inserir, escluir e etc
			
			strcpy(vetorUsuarios[qntCadastros].nome,nome);
			fscanf(entrada, "%d\n",&vetorUsuarios[qntCadastros].idade); //l� os dados do arquivo
			printf("\tUsuario %s cadastrado\n",vetorUsuarios[qntCadastros].nome);			
			qntCadastros++;	
						
			
//-----------------------------------------------------------------------------------------------------------------> Vetor de Usuarios para ser usaddo como base na hora de inserir, escluir e etc
	}
	
}

void inserirRelacao(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam], TNo **ptr,TNo **ptrSeguido, TipoLista listaSegue[tam],TipoLista listaSeguido[tam]){
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
	TNo *ptrAux;TNo *ptrAux1;
	TipoLista lstAux, lstAux1;
	usuario usuariosAux;
	
	FILE *seguir = fopen("seguir.txt", "r"); //abertura do arquivo	
	if(seguir == NULL){
		printf("\t  -> Erro na abertura do arquivo\n\n");
		system("pause");
	}
	
	while(!feof(seguir)){ // responsavel por ler at� o fim do arquivo
		fscanf(seguir, "%s\n",&nomeSeguidor); //l� os dados de quem vai comecar a seguir 
		fscanf(seguir, "%s\n",&nomeSeguido); //l� os dados de quem vai comecar a ser seguido
		
		printf("--> %s segue %s\n", nomeSeguidor, nomeSeguido);
		
			
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
//		printf("\t\t\t\t-> Valor inserido na Matriz de adjacencias");
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
		
		ptrAux1 = ptrSeguido[coluna];
		usuariosAux = vetorUsuarios[linha];		
		insereAVL(&ptrAux1,usuariosAux);
		ptrSeguido[coluna] = ptrAux1;
		
//-----------------------------------------------------------------------------------------------------------------> Arvore

//-----------------------------------------------------------------------------------------------------------------> comeco lista

		lstAux=listaSegue[linha];
		usuariosAux = vetorUsuarios[coluna];
		insereLista(usuariosAux,&lstAux);
		listaSegue[linha] = lstAux;
		
		lstAux=listaSeguido[coluna];
		usuariosAux = vetorUsuarios[linha];
		insereLista(usuariosAux,&lstAux);
		listaSeguido[coluna] = lstAux;
		//printf("AAAAAAAAAAA -> lst: %s",lstSegue[linha]->ultimo->user.nome);

//-----------------------------------------------------------------------------------------------------------------> comeco lista

	
		cont=0;		
	}
}

void listarSeguidores(int existe, usuario vetorUsuarios[tam],int matrizUsuarios[tam][tam],int modo,TNo *ptr[tam],TNo *ptrSeguido[tam],TipoLista listaSegue[tam],TipoLista listaSeguido[tam]){
/*
i.ap�s o usu�rio do programa escolher um usu�rio cadastrado x, esta op��o dever� listar todos os usu�rios os quais x segue e por quais usu�rios x � seguido,
  inclusive com os tempos relacionados � cada rela��o existente; 
ii.no caso da representa��o por lista com adjac�ncias em AVL, fornecer ao usu�rio a op��o de se utilizar algum dos algoritmos de percurso em �rvores in-ordem,
   pr�-ordem ou p�s-ordem.
*/

	int segue=0,eSeguido=0;
	TNo *ptrAux,*ptrAux1;
	TipoLista lstAux,lstAux1;
	usuario usuariosAux;
	
	switch(modo){
//-----------------------------------------------------------------------------------------------------------------> Comeco Matriz de pessos/vetor de usuarios				
		case 1:
			printf("\n\n\n -------------------- Matriz de Pesos ----------------------- \n\n");
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
			
			
			printf("\n\n -------------------- Matriz de Pesos ----------------------- \n\n");
		break;
//-----------------------------------------------------------------------------------------------------------------> Fim Matriz de pessos/vetor de usuarios				

//-----------------------------------------------------------------------------------------------------------------> Comeco listagem na lista de adjacencias	
		case 2:
			printf("\n\n\n -------------------- lista de adjacencias ----------------------- \n\n");
			printf("\n\tO usuario Segue:\n");
			lstAux = listaSegue[existe];
			if(lstAux.primeiro->prox != NULL){
				imprimeLista(lstAux);
			}
			else{
				printf("\t\t\t O usuario nao segue ninguem!\n");
			}
			
			printf("\n\tO usuario eh seguido:\n");
			lstAux1 = listaSeguido[existe];
			if(lstAux1.primeiro->prox != NULL){
				imprimeLista(lstAux1);
			}
			else{
				printf("\t\t\t O usuario nao eh seguido por ninguem!\n");
			}
			
			printf("\n\n -------------------- lista de adjacencias ----------------------- \n\n");
		
		break;
//-----------------------------------------------------------------------------------------------------------------> Fim listagem na lista de adjacencias		

//-----------------------------------------------------------------------------------------------------------------> Comeco listagem na Arvore AVL
		case 3:
			printf("\n\n\n -------------------- lista de adjacencias AVL ----------------------- \n\n");
			
			printf("\n\tO usuario Segue:\n"); 
			ptrAux = ptr[existe];
			if(ptrAux != NULL){
				in_ordem(ptrAux); // nesse caso irao ser listados os usuarios da rede que sao seguidos pelo passado pelo usuario do programa	
			}
			else{
				printf("\t\t\t O usuario nao segue ninguem!\n");				
			}
			
			printf("\n\tO usuario eh seguido:\n");
			ptrAux1 = ptrSeguido[existe];
			if(ptrAux1 != NULL){
				in_ordem(ptrAux1); // nesse caso irao ser listados os usuarios da rede que sao seguidos pelo passado pelo usuario do programa	
			}
			else{
				printf("\t\t\t O usuario nao eh seguido por ninguem!\n");				
			}
//			
			
			printf("\n\n\n -------------------- lista de adjacencias AVL -----------------------\n\n");
		
		break;
//-----------------------------------------------------------------------------------------------------------------> fim listagem na Arvore AVL			
	}
}

void listarSeguidoresVelhos(int existe,usuario vetorUsuarios[tam],int matrizUsuarios[tam][tam],TNo *ptr[tam],TipoLista listaSegue[tam]){
//i. lista todos os usu�rios que s�o seguidos por usu�rios mais velhos, inclusive com os quantitativos associados a cada um deles.
	int segue=0,eSeguido=0;
	TNo *ptrAux;
	TipoLista lstAux,lstAux1;
	
//-----------------------------------------------------------------------------------------------------------------> Comeco Matriz de pessos/vetor de usuarios			
	printf("\n\n\n -------------------- Matriz de Pesos ----------------------- \n\n");
	
	printf("\n\t%s com %d ano(s) segue:\n\n", vetorUsuarios[existe].nome, vetorUsuarios[existe].idade);
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
//-----------------------------------------------------------------------------------------------------------------> Fim Matriz de pessos/vetor de usuarios			

//-----------------------------------------------------------------------------------------------------------------> Comeco listagem na lista de mais velhos na Arvore AVL
	printf("\n\n\n -------------------- lista de adjacencias ----------------------- \n\n");
	printf("\n\t%s com %d ano(s) segue:\n\n", vetorUsuarios[existe].nome, vetorUsuarios[existe].idade);
	lstAux=listaSegue[existe];
	if(lstAux.primeiro->prox!= NULL){
		imprimeLista1(lstAux,vetorUsuarios[existe]);	
	}
	else{
		printf("-> ninguem :( :( :() <-");
	}
	
	
	printf("\n\n-------------------- lista de adjacencias ----------------------- \n\n");
//-----------------------------------------------------------------------------------------------------------------> Fim listagem na lista de mais velhos na Arvore AVL
	

//-----------------------------------------------------------------------------------------------------------------> Comeco listagem na lista de mais velhos na Arvore AVL
	printf("\n\n\n -------------------- lista de adjacencias AVL ----------------------- \n\n");
	printf("\n\t%s com %d ano(s) segue:\n\n", vetorUsuarios[existe].nome, vetorUsuarios[existe].idade);
	ptrAux = ptr[existe];
	if(ptrAux != NULL){
		pesquisa(ptrAux,vetorUsuarios[existe]);	
	}
	else{
		printf("-> ninguem :( :( :() <-");
	}
	
	
	printf("\n\n-------------------- lista de adjacencias AVL ----------------------- \n\n");
//-----------------------------------------------------------------------------------------------------------------> Fim listagem na lista de mais velhos na Arvore AVL
	
		

}

void atualizarRelacao(int existe, int existe1, usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam],TNo **ptr,TNo **ptrSeguido){
/*
i. ocorre similarmente � inser��o de rela��es, por�m a rela��o dever� estar previamente inserida. 
ii. caso a rela��o n�o esteja inserida deve-se oferecer essa op��o ao usu�rio do programa.
*/
	int confirmacao=0,confirmacao1=0;
	usuario usuariosAux;
	TNo *ptrAux,*ptrAux1;

	printf("\nVoce relamente deseja atualizar a relacao entre %s e %s? 1-sim 2-nao\n",vetorUsuarios[existe].nome,vetorUsuarios[existe1].nome);
	scanf("%d",&confirmacao);
	if(confirmacao == 1){
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios				
		if(matrizUsuarios[existe][existe1] == 0){
			printf("\n\tO usuario %s nao seguia o usuario %s deseja que comece a seguir? 1-sim 2-nao ",vetorUsuarios[existe].nome,vetorUsuarios[existe1].nome);
			scanf("%d",&confirmacao1);
			
			if(confirmacao1 == 1){
				matrizUsuarios[existe][existe1] = 1;
				
				ptrAux = ptr[existe];				
				usuariosAux = vetorUsuarios[existe1];		
				insereAVL(&ptrAux,usuariosAux);
				ptr[existe] = ptrAux;
				
				ptrAux = ptrSeguido[existe1];				
				usuariosAux = vetorUsuarios[existe];		
				insereAVL(&ptrAux,usuariosAux);
				ptrSeguido[existe1] = ptrAux;
//				
//				pesquisaParaAtualizar(ptrAux,ptrAux1, vetorUsuarios,existe,existe1);
//				ptr[existe]=ptrAux;
			}
		}
		else{
			printf("\n\tO usuario %s ja seguia o usuario %s deseja que pare a seguir? 1-sim 2-nao ",vetorUsuarios[existe].nome,vetorUsuarios[existe1].nome);
			scanf("%d",&confirmacao1);
			
			if(confirmacao1 == 1){
				matrizUsuarios[existe][existe1] = 0;
				
				ptrAux = ptr[existe];
				retiraAVL(&ptrAux,vetorUsuarios[existe1]);
				ptr[existe]=ptrAux;
				
				ptrAux = ptrSeguido[existe1];
				retiraAVL(&ptrAux,vetorUsuarios[existe]);
				ptrSeguido[existe1]=ptrAux;
				
				
			}
		}
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios		
		
	}
}

void removerUsuario(int existe, usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam],TNo **ptr,TNo **ptrSeguido,TipoLista listaSegue[tam],TipoLista listaSeguido[tam]){
/* 
i. remove um usu�rio previamente cadastrado na rede social, inclusive, com todas as suas rela��es; 
ii. caso o usu�rio n�o esteja cadastrado, exibir uma mensagem de erro.
*/
	
	int confirmacao=0,vzs;
	char aux[20];
	TipoLista lstAux, lstAux1;
	usuario usuariosAux;
	TNo *ptrAux;
	
	printf("\n\t VOCE REALMENTE DESEJA REMOVER O USUARIO %s DA REDE? 1-sim 2-nao\n", vetorUsuarios[existe].nome);
	scanf("%d", &confirmacao);
	
	if(confirmacao == 1){
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios				
		strcpy(aux,vetorUsuarios[existe].nome);
//---------------------------- Comeco Removendo da matriz ------------------		
	for(int i=0;i<qntCadastros;i++){
		for(int j=existe;j<qntCadastros;j++){
			matrizUsuarios[i][j] = matrizUsuarios[i][j+1];
		}
	}
	
	for(int i=existe;i<qntCadastros;i++){
		for(int j=0;j<qntCadastros;j++){
			matrizUsuarios[i][j] = matrizUsuarios[i+1][j];
		}
	}

//---------------------------- Fim Removendo da matriz ------------------
//printf("\n\n\n\n________________________\n\n\n\n");
//for(int i=1;i<qntCadastros;i++){
//	for(int j=1;j<qntCadastros;j++){
//		printf("[%d]",matrizUsuarios[i][j]);
//	}
//	printf("\n");
//}


//---------------------------- Comeco Removendo da arvore ------------------

	/* a inten��o para a remocao da arvore AVl  � pasar por todas a celulas removendo o no que est� o valor removido, isso tanto na arvore que reseva os seguidores
	quanto para a arvore que estao armazenados os seguidos */
	
	for(int i=existe;i<qntCadastros;i++){
		ptr[i] = ptr[i+1];
		ptrSeguido[i] = ptrSeguido[i+1];
	}

	for(int i=1;i<qntCadastros;i++){
		ptrAux = ptr[i];
		retiraAVL(&ptrAux,vetorUsuarios[existe]);
		ptr[i]=ptrAux;
	}
	
	for(int i=1;i<qntCadastros;i++){
		ptrAux = ptrSeguido[i];
		retiraAVL(&ptrAux,vetorUsuarios[existe]);
		ptrSeguido[i]=ptrAux;
	}
	
//---------------------------- Fim Removendo da arvore ------------------	

//---------------------------- Comeco Removendo da lista ------------------	
	for(int i=existe;i<qntCadastros;i++){
		listaSegue[i] = listaSegue[i+1];
		listaSeguido[i] = listaSeguido[i+1];
	}		
	
	for(int i=1;i<qntCadastros;i++){
		printf("\n\t%d/%d\n",i,qntCadastros-1);
		if(strcmp(listaSegue[i].ultimo->user.nome,"") != 0){
			printf("\n1");
			lstAux=listaSegue[i];
			printf("\n\t2");
			usuariosAux = vetorUsuarios[existe];
			printf("\n\t\t3");
			printf("Remover o usuario: %s",usuariosAux.nome);
		//	removeLista(usuariosAux,&lstAux);
			printf("\n\t\t\t4");
			listaSegue[i] = lstAux;
			printf("\n\t\t\t\t5");
		}
		
	}

//---------------------------- Comeco Removendo da lista ------------------



//---------------------------- Comeco Removendo do vetor ------------------	
		for(int i=existe;i<qntCadastros;i++){
			vetorUsuarios[i] = vetorUsuarios[i+1];
		}
		
//---------------------------- Fim Removendo do vetor ------------------
		
		qntCadastros--;
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios				
		
		printf("\n\tO usuario %s foi removido e a rede tem  %d usuarios\n",aux,qntCadastros-1);
	}

}

void removerRelacao(int existe,int existe1, usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam],TNo **ptr,TNo **ptrSeguido,TipoLista listaSegue[tam],TipoLista listaSeguido[tam]){
/*
i. remove uma rela��o previamente cadastrada na rede social; 
ii. caso algum elemento da rela��o a ser removida (v�rtice ou aresta) n�o esteja inserido, exibir uma mensagem de erro.
*/	
	TNo *ptrAux;
	TipoLista lstAux, lstAux1;
	usuario usuariosAux;
	
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios			
	if(matrizUsuarios[existe][existe1] == 0){
		printf("\n\n\tO usuario %s ja nao seguia o usuario %s", vetorUsuarios[existe].nome, vetorUsuarios[existe1].nome);
	}
	else if(matrizUsuarios[existe][existe1] == 1){
		matrizUsuarios[existe][existe1] = 0;
		
		ptrAux = ptr[existe];
		retiraAVL(&ptrAux,vetorUsuarios[existe1]);
		ptr[existe]=ptrAux;
		
		ptrAux = ptrSeguido[existe1];
		retiraAVL(&ptrAux,vetorUsuarios[existe]);
		ptrSeguido[existe1]=ptrAux;
		
		
		lstAux=listaSegue[existe];
		usuariosAux = vetorUsuarios[existe1];
		removeLista(usuariosAux,&lstAux);
		listaSegue[existe] = lstAux;
		
		
		lstAux=listaSeguido[existe1];
		usuariosAux = vetorUsuarios[existe];
		removeLista(usuariosAux,&lstAux);
		listaSeguido[existe1] = lstAux;
		
	}
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios		


//	printf("removendo essa relacao aqui oh %s -> %s",vetorUsuarios[existe],vetorUsuarios[existe1]);
}

void printaTodosUsuarios(usuario vetorUsuarios[tam]){

	int vzs=10; //Pra quando houver mais de x usuarios cadastrados, esse n�mero ser usado como base para quebraa de linha no for a abaixo
	printf("\n\t\t\t\t\t- Todos usuarios -\n\t");
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
	printf("\n");
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
		printf("\n\nO nome digitado nao esta cadastrado na rede. Digite novamente!\n\n");
		system("pause");
		return 0;
	}
	else{ //caso encontrar
		return posicao; 
	}
	
}

