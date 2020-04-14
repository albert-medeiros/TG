/* 
   
   Regras:
	1-> Usuarios são inseridos atraves do arquivo.txt sendo que são dispostos nome em na primeira linha e idade logo na de baixo
	2-> A inserção de quem segue quem tbm e feita atraves do arquivo seguir.txt no qual é disposto na primeira linha quem segue e na loga na de baixo quem é seguido
    3-> Em todas as verificacoes comeca-se no 1 pois o vetor tem 51 posicoes
    4-> A variavel linha representa a posicao de quem vai comecar a seguir 
    5-> A variavel coluna representa a posicao de quem vai comecar a ser seguido
    
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>


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

typedef struct no{ //struct para armazenar os valores salvos na árvore
	struct no *esq,*dir; // aponta para o proximo no
	TipoUsuario user; //chave real
} TNo;

typedef struct lista{ //struct para armazenar os valores salvos na árvore
	struct lista *prox; // aponta para o proximo no
	TipoUsuario user; //chave real
} TLista;

struct TipoLista{
	lista *primeiro,*ultimo ;
}; 

//----------------------------------------------------------------------- STRUCT / INICIALIZA ------------------------------------------------------------------------------------



//---------------------------- Comeco funcoes para a arvore AVL ------------------	
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

// o in_ordem muda somente a formatacao a ser imprimida para o in_ordem1
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
		
	if (*ptr == NULL ){ // entra na hora de criar um novo nó
		(*ptr) = ALOCA; //aloco dinamicamente um espaço pra "ptr"
		(*ptr)->esq = NULL;
		(*ptr)->dir = NULL;
		strcpy((*ptr)->user.nome, user.nome); // o nó recebe o valor do nome
		(*ptr)->user.idade = user.idade; // o nó recebe os outros valores
	}
	
	else{
		if(user.idade<=(*ptr)->user.idade){ //verificação para saber em qual lado é inserido o valor
			insereAVL(&(*ptr)->esq,user); //passa o valor da esquerda se for menor
		}
		else if(user.idade>(*ptr)->user.idade){ //verificação para saber em qual lado é inserido o valor
			insereAVL(&(*ptr)->dir,user); //passa o valor da direita se for maior
		}
	}
	
	//FB - Pai;  
	//fb - filho;
	//Após inserir o valor é verifica do Fator de balanceamento
	
	
	FB=(altura((*ptr)->dir))-(altura((*ptr)->esq)); //calcula a altura ao desempilhar
	
	if(FB == +2){ //caso o FB do nó seja 2 então tem que fazer alteração 
			
		fb = altura((*ptr)->dir->dir)-altura((*ptr)->dir->esq); //calcula a altura do filho da direita
		
		if(fb == 1){ // se for igual a um então rotação simples 
			rotacaoEsq(&(*ptr));
		}
			
		else if(fb == -1){ // se for igual a menos um então rotação dulpa
			rotacaoDir(&(*ptr)->dir);
			rotacaoEsq(&(*ptr));
		}
	}
		
	else if(FB == -2){
	
		fb = (altura((*ptr)->esq->dir))-(altura((*ptr)->esq->esq)); //calcula a altura do filho da direita
		if(fb == -1){ // se for igual a um então rotação simples 
			rotacaoDir(&(*ptr));
		}
	
		else if(fb == +1){ // se for igual a menos um então rotação dulpa
			rotacaoEsq(&(*ptr)->esq);
			rotacaoDir(&(*ptr));
		}	
	}
}

void sucessor(TNo *q,TNo **r){
	if((*r)->esq != NULL){  //recursivamente para ir no último da esquerda
		sucessor(q,&(*r)->esq);
	}
	else{ //faz a troca e apaga o nó 
		q->user = (*r)->user;	//aluno recebe os dados dos da struct r
		q = (*r); //posição da chave
		(*r) = (*r)->dir; //passa a chave dir para o nó
		free(q);
	}
}


void retiraAVL(TNo **ptr, usuario user){
	int FB,fb;
	if((*ptr)==NULL){ //verifica se o valor está na árvore
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
			sucessor((*ptr),&(*ptr)->dir);
		}
	}
	
	if((*ptr)!=NULL){ // Para não verificar o nó que foi retirado e esperar a recursividade voltar para assim entrar dentro do if
		FB=altura((*ptr)->dir)-altura((*ptr)->esq); //calcula a altura ao desempilhar
		
		if(FB==2){ //caso o FB do nó seja 2 então tem que fazer alteração 
				
			fb = altura((*ptr)->dir->dir)-altura((*ptr)->dir->esq); //calcula a altura do filho da direita
			if((fb == 1) || (fb == 0)){ // se for igual a um então rotação simples 
				rotacaoEsq(ptr);
			}	
			else if(fb == -1){ // se for igual a menos um então rotação dulpa
				rotacaoDir(&(*ptr)->dir);
				rotacaoEsq(ptr);
			}
		}
			
		else if(FB == -2){
						
			fb = (altura((*ptr)->esq->dir))-(altura((*ptr)->esq->esq)); //calcula a altura do filho da direita
			if(fb == -1 || fb == 0){ // se for igual a um então rotação simples 
				rotacaoDir(ptr);
			}
			else if(fb == 1){ // se for igual a menos um então rotação dulpa
				rotacaoEsq(&(*ptr)->dir);
				rotacaoDir(ptr);
			}	
		}
	}
}

void pesquisa(TNo *ptr,usuario user){
	int quant=1;
	while((ptr!= NULL) && (strcmp(ptr->user.nome,user.nome) == 0)){
		quant++; //A cada ciclo soma 1 para saber o numero de comparações	
		if(user.idade > ptr->user.idade){ //direção que a chave percorre
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

//---------------------------- Fim funcoes para a arvore AVL ------------------	

//---------------------------- Comeco funcoes para a lista ------------------	

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
	
	
	int cont=1,posicaoRemover=-1,i=0;
	
	

	if(auxComeco->prox == auxFim){ //se só tem um usuario seguindo ou sendo seguido ele zera a lista novamente, o ultimo e o primero apontam pro mesmo lugar
		list->ultimo = list->primeiro;
		list->primeiro->prox = NULL;		
	}

	else if(strcmp(auxComeco->prox->user.nome,user.nome) == 0){
		list->primeiro->prox=list->primeiro->prox->prox;
		
	}

	else{ //se não for o primeiro nem o ultimo entra aqui 
			
			FLVazia(&listaFinal);
			while(auxComeco!=NULL){//strcmp(auxComeco->prox->user.nome,list->ultimo->user.nome)!=0){
				
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
	
			for(int i=0;i<cont;i++){
				usuariosAux = vetorLista[i].user;
				if(i != posicaoRemover-1){
					insereLista(usuariosAux,&listaFinal);	
				}
			}
			list->primeiro = listaFinal.primeiro;								
	}
}

// o imprimeLista1 muda somente a formatacao para o imprimeLista
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
//---------------------------- Fim funcoes para a lista ------------------	


//---------------------------- Comeco funcoes de inicializacao, insercao, impressao e retirada de relacoes e usuarios ------------------	
void inicializaGrafos(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam], TNo **ptr , TNo **ptrSeguido , TipoLista listaSegue[tam] , TipoLista listaSeguido[tam]){ 
/*
i. preenche a matriz de pesos com zeros, aloca uma posição de memória (posição 0) para as listas de adjacência e adjacência em AVL e faz com o que seus conteúdos apontem para NULL; 
ii. não é necessário oferecer essa opção ao usuário; 
iii. poderão ser utilizados os índices da lista de 1 a n
*/
	TipoLista listaAux;

//---------------------------- Comeco da inicializacao da matriz ------------------	

//todas as celulas da matriz recebe 0, garantindo que nao haja lixo
	printf("\n\n\t -> Inicializando o Grafo: \n");
	for(int i=0; i<=tam;i++){
		for(int j=0; j<tam;j++){
			matrizUsuarios[i][j] = 0;
		}
	}
//---------------------------- Fim da inicializacao da matriz ------------------		

//---------------------------- Comeco da inicializacao do vetor auxiliar ------------------
//garante que nao haja lixo no vetor			
	for(int i=0; i<tam;i++){
		vetorUsuarios[i].idade = 0;
		strcpy(vetorUsuarios[i].nome, "");
	}
//---------------------------- Fim da inicializacao do vetor auxiliar ------------------			

	
//---------------------------- Comeco da inicializacao da Arvore AVL ------------------	
//todas as celulas tem como raizes NULL
	for(int i=0;i<tam;i++){
		ptr[i] = NULL;	
	}
	
	for(int i=0;i<tam;i++){
		ptrSeguido[i] = NULL;
	}
//---------------------------- Fim da inicializacao da Arvore AVL ------------------	

//---------------------------- Comeco da inicializacao da lista ------------------
//chama a funcao responsavel por criar uma celula inicial e deixar pronta pra se inserir dados	
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
//---------------------------- Fim da inicializacao da lista ------------------			
	
}

void inserirUsuario(usuario vetorUsuarios[tam]){

/*
i. libera, dinamicamente, uma linha e uma coluna da matriz de pesos para representar as relações do novo usuário, aloca uma posição de memória em cada uma das listas e realiza a inserção de tal usuário pelo nome (que será fornecido); 
ii. o programa deverá verificar se o usuário já está inserido e, caso positivo, retornar uma mensagem de erro.
*/

//todos os dados lidos no arquivo são salvos no vetor auxiliar no qual serao feitas as comparacoes necessarias para insercao, exclusao ...

	char nome[20];
	int entrou=0;
	
	//abre o arquivo e verifica se ouve erros
	FILE *entrada = fopen("arquivo.txt", "r"); //abertura do arquivo 
	if(entrada == NULL){
		printf("\t  -> Erro na abertura do arquivo");
		system("pause");
	}
	
	//---------------------------- Comeco da leitura e insercao no vetor ------------------		
	while(!feof(entrada)){ //le o arquivo do comeco ao fim
		fscanf(entrada, "%s\n",&nome); //lê os dados do arquivo
		
		//verifica se o usuário já foi inserido e caso já tenha sido inserido encerra-se a insercao e a flag entrou recebe 1 garantindo que nao sera inserido
		//---------------------------- Comeco da verificacao se ja foi inserido ------------------		
		for(int j=1;j<=qntCadastros;j++){
			if(strcmp(vetorUsuarios[j].nome,nome) == 0){
				printf("\n\t\t - - - Usuario ' %s ' ja foi inserido - - -\n\n",nome);
				entrou=1;
				break;
			}				
		}
		//---------------------------- Fim da verificacao se ja foi inserido ------------------		
		
		if(entrou == 1){
			printf("\n\t\t\t A insecao sera encerrada\n\n");
			system("pause");
			break;
		}
		//---------------------------- Comeco da insercao na lista ------------------		
		strcpy(vetorUsuarios[qntCadastros].nome,nome);
		fscanf(entrada, "%d\n",&vetorUsuarios[qntCadastros].idade); //lê os dados do arquivo
		printf("\tUsuario %s cadastrado\n",vetorUsuarios[qntCadastros].nome);			
		qntCadastros++; //variavel global responsavel por contar quantos usuarios ja foram inseridos
		//---------------------------- Comeco da insercao na lista ------------------		
	}
	//---------------------------- Fim da leitura e insercao no vetor ------------------		
	
}

void inserirRelacao(usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam], TNo **ptr,TNo **ptrSeguido, TipoLista listaSegue[tam],TipoLista listaSeguido[tam]){
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


//nessa funcao em que os dados serao inseridos na matriz de adjacencia, lista de adjacencias e na Arvore AVL de adjacencias


	char nomeSeguido[20], nomeSeguidor[20];
	int coluna=0, linha=0,cont=0;
	TNo *ptrAux;TNo *ptrAux1;
	TipoLista lstAux, lstAux1;
	usuario usuariosAux;
	
	//---------------------------- Abertura do arquivo e comeco da leitura  ------------------
	FILE *seguir = fopen("seguir.txt", "r"); //abertura do arquivo	
	if(seguir == NULL){
		printf("\t  -> Erro na abertura do arquivo\n\n");
		system("pause");
	}
	
	while(!feof(seguir)){ // responsavel por ler até o fim do arquivo
		fscanf(seguir, "%s\n",&nomeSeguidor); //lê os dados de quem vai comecar a seguir 
		fscanf(seguir, "%s\n",&nomeSeguido); //lê os dados de quem vai comecar a ser seguido
		
		printf("--> %s segue %s\n", nomeSeguidor, nomeSeguido);		
			
//---------------------------- Comeco da verificacao se o usuario ja foi inserido no vetor ------------------			
		//percorre o vetor até achar o nome digitado pelo usuário e salva a posição que ele está pois sera usado para a isercao nas estruturas
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
		
		if(cont != 2){ // se nao entrou duas vezes não tem algum usuario e encerra a insercao do arquivo
			printf("\n\t - somente um usuário encontrado - ");
			break;
		}
//---------------------------- Fim da verificacao se o usuario ja foi inserido no vetor ------------------	

	if(matrizUsuarios[linha][coluna] == 0){ //faz a verificacao somente na matriz pois nas outras estruturas resultariam a mesma coisa
					
	//---------------------------- Comeco da insercao na matriz ------------------			
	
			matrizUsuarios[linha][coluna] = 1;		
			
	//---------------------------- Fim da insercao na matriz ------------------						
	
	//---------------------------- Comeco da insercao na arvore AVL ------------------	
	/* estava dando problema quando eu tentava mandar inserir ja no vetor direto, entao, foi criado auxiliares para a posicao que era da arvore 
	e para os dados que vao ser inseridos pois desta forma as alteracoes que seriam feitas na funcao sao menores e funcionaram (hihihihihi), portanto, 
	apos enviar a posicao do vetor de arvore recebe de volta os dados atualizados (assim como foi feito em outras partes como para a exclusao) */
			
			ptrAux = ptr[linha];
			usuariosAux = vetorUsuarios[coluna];		
			insereAVL(&ptrAux,usuariosAux);
			ptr[linha] = ptrAux;
			
			ptrAux1 = ptrSeguido[coluna];
			usuariosAux = vetorUsuarios[linha];		
			insereAVL(&ptrAux1,usuariosAux);
			ptrSeguido[coluna] = ptrAux1;
			
	//---------------------------- Fim da insercao na arvore AVL ------------------	
	
	//---------------------------- Comeco da insercao na lista ------------------	
	
			lstAux=listaSegue[linha];
			usuariosAux = vetorUsuarios[coluna];
			insereLista(usuariosAux,&lstAux);
			listaSegue[linha] = lstAux;
			
			lstAux=listaSeguido[coluna];
			usuariosAux = vetorUsuarios[linha];
			insereLista(usuariosAux,&lstAux);
			listaSeguido[coluna] = lstAux;
	
	//---------------------------- Fim da insercao na lista ------------------
	}
	else{
		printf("\n\t - Relacao ja inserida - \n");
	}
		cont=0; //zera pra nova verificacao se ja foi inserido		
	}
}

void listarSeguidores(int existe, usuario vetorUsuarios[tam],int matrizUsuarios[tam][tam],int modo,TNo *ptr[tam],TNo *ptrSeguido[tam],TipoLista listaSegue[tam],TipoLista listaSeguido[tam]){
/*
i.após o usuário do programa escolher um usuário cadastrado x, esta opção deverá listar todos os usuários os quais x segue e por quais usuários x é seguido,
  inclusive com os tempos relacionados à cada relação existente; 
ii.no caso da representação por lista com adjacências em AVL, fornecer ao usuário a opção de se utilizar algum dos algoritmos de percurso em árvores in-ordem,
   pré-ordem ou pós-ordem.
*/

	int segue=0,eSeguido=0;
	TNo *ptrAux,*ptrAux1;
	TipoLista lstAux,lstAux1;
	usuario usuariosAux;
	
	switch(modo){ //modo representa em qual estrutura sera utilizada para a impressao, o valor foi obtido no main
//---------------------------- comeco da imprecao na matriz ------------------	
		case 1:
			printf("\n\n -------------------- Matriz de Pesos ----------------------- \n\n");
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
						
			printf("\n\n -------------------- Matriz de Pesos ----------------------- \n\n");
			
		break;
//---------------------------- Fim da imprecao na matriz ------------------	

//---------------------------- Comeco da imprecao na lista ------------------	
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
//---------------------------- Fim da imprecao na lista ------------------			

//---------------------------- Comeco da imprecao na arvore AVl ------------------	
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
			
			printf("\n\n\n -------------------- lista de adjacencias AVL -----------------------\n\n");
		
		break;
//---------------------------- Fim da imprecao na arvore AVl ------------------			
	}
}

void listarSeguidoresVelhos(int existe,usuario vetorUsuarios[tam],int matrizUsuarios[tam][tam],TNo *ptr[tam],TipoLista listaSegue[tam]){
//i. lista todos os usuários que são seguidos por usuários mais velhos, inclusive com os quantitativos associados a cada um deles.
	int segue=0,eSeguido=0;
	TNo *ptrAux;
	TipoLista lstAux,lstAux1;
	
//---------------------------- Comeco da imprecao dos mais velhos na matriz ------------------	

	printf("\n\n -------------------- Matriz de Pesos ----------------------- \n\n");
	
	printf("\n\t%s com %d ano(s) segue:\n\n", vetorUsuarios[existe].nome, vetorUsuarios[existe].idade); //dados do usuario escolhido
	for(int i=1;i<qntCadastros;i++){		
		if(matrizUsuarios[existe][i] == 1){ //verifica se existe e salva a posicao no vetor que ele esta
			if((vetorUsuarios[existe].idade < vetorUsuarios[i].idade)&&(i!=existe)){
				printf("\t\t %s - %d anos\n", vetorUsuarios[i].nome, vetorUsuarios[i].idade);
				segue=1;
			}	
		}
	}
	
	if(segue == 0){
			printf("-> ninguem :( <-");
	}
	
	printf("\n\n -------------------- Matriz de Pesos ----------------------- \n\n");
	
//---------------------------- Fim da imprecao dos mais velhos na matriz ------------------	

//---------------------------- Comeco da imprecao dos mais velhos na lista ------------------
	
	printf("\n\n -------------------- lista de adjacencias ----------------------- \n\n");
	printf("\n\t%s com %d ano(s) segue:\n\n", vetorUsuarios[existe].nome, vetorUsuarios[existe].idade);
	lstAux=listaSegue[existe];
	if(lstAux.primeiro->prox!= NULL){
		imprimeLista1(lstAux,vetorUsuarios[existe]);	
	}
	else{
		printf("-> ninguem :( :( :() <-");
	}
	
	printf("\n\n-------------------- lista de adjacencias ----------------------- \n\n");
	
//---------------------------- Fim da imprecao dos mais velhos na lista ------------------	
	
//---------------------------- Comeco da imprecao dos mais velhos na arvore AVL ------------------	

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
	
//---------------------------- Fim da imprecao dos mais velhos na arvore AVL ------------------	
}

void atualizarRelacao(int existe, int existe1, usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam],TNo **ptr,TNo **ptrSeguido,TipoLista listaSegue[tam],TipoLista listaSeguido[tam]){
/*
i. ocorre similarmente à inserção de relações, porém a relação deverá estar previamente inserida. 
ii. caso a relação não esteja inserida deve-se oferecer essa opção ao usuário do programa.
*/
	int confirmacao=0,confirmacao1=0;
	usuario usuariosAux;
	TNo *ptrAux,*ptrAux1;
	TipoLista lstAux, lstAux1;

	printf("\nVoce relamente deseja atualizar a relacao entre %s e %s? 1-sim 2-nao\n",vetorUsuarios[existe].nome,vetorUsuarios[existe1].nome);
	scanf("%d",&confirmacao);
	if(confirmacao == 1){
//-----------------------------------------------------------------------------------------------------------------> Matriz de pessos/vetor de usuarios				
		if(matrizUsuarios[existe][existe1] == 0){ //faz a verificacao se o usuario segue ou nao, faz somente na matriz pois como as outras sao iguais daria o mesmo resulta
			printf("\n\tO usuario %s nao seguia o usuario %s deseja que comece a seguir? 1-sim 2-nao ",vetorUsuarios[existe].nome,vetorUsuarios[existe1].nome);
			scanf("%d",&confirmacao1);
			
			if(confirmacao1 == 1){
				//---------------------------- Comeco da insercao na matriz ------------------
				matrizUsuarios[existe][existe1] = 1;
				//---------------------------- Fim da insercao na matriz ------------------
				
				//---------------------------- Comeco da insercao na arvore AVL ------------------
				ptrAux = ptr[existe];				
				usuariosAux = vetorUsuarios[existe1];		
				insereAVL(&ptrAux,usuariosAux);
				ptr[existe] = ptrAux;
				
				ptrAux = ptrSeguido[existe1];				
				usuariosAux = vetorUsuarios[existe];		
				insereAVL(&ptrAux,usuariosAux);
				ptrSeguido[existe1] = ptrAux;
				//---------------------------- Fim da insercao na arvore AVL ------------------
				
				//---------------------------- Comeco da insercao na lista ------------------
				lstAux=listaSegue[existe];
				usuariosAux = vetorUsuarios[existe1];
				insereLista(usuariosAux,&lstAux);
				listaSegue[existe] = lstAux;
		
				lstAux=listaSeguido[existe1];
				usuariosAux = vetorUsuarios[existe];
				insereLista(usuariosAux,&lstAux);
				listaSeguido[existe1] = lstAux;
				//---------------------------- Fim da insercao na lista ------------------				
			}
		}
		else{
			printf("\n\tO usuario %s ja seguia o usuario %s deseja que pare a seguir? 1-sim 2-nao ",vetorUsuarios[existe].nome,vetorUsuarios[existe1].nome);
			scanf("%d",&confirmacao1);
			
			if(confirmacao1 == 1){
				//---------------------------- Comeco da remocao na matriz ------------------
				matrizUsuarios[existe][existe1] = 0;
				//---------------------------- Fim da remocao na matriz ------------------
				
				//---------------------------- Comeco da remocao na arvore AVL ------------------
				ptrAux = ptr[existe];
				retiraAVL(&ptrAux,vetorUsuarios[existe1]);
				ptr[existe]=ptrAux;
				
				ptrAux = ptrSeguido[existe1];
				retiraAVL(&ptrAux,vetorUsuarios[existe]);
				ptrSeguido[existe1]=ptrAux;
				//---------------------------- Fim da remocao na arvore AVL ------------------
				
				//---------------------------- Comeco da remocao na lista ------------------				
				lstAux=listaSegue[existe];
				usuariosAux = vetorUsuarios[existe1];
				removeLista(usuariosAux,&lstAux);
				listaSegue[existe] = lstAux;				
				
				lstAux=listaSeguido[existe1];
				usuariosAux = vetorUsuarios[existe];
				removeLista(usuariosAux,&lstAux);
				listaSeguido[existe1] = lstAux;
				//---------------------------- Fim da remocao na lista ------------------								
			}
		}	
	}
}

void removerUsuario(int existe, usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam],TNo **ptr,TNo **ptrSeguido,TipoLista listaSegue[tam],TipoLista listaSeguido[tam]){
/* 
i. remove um usuário previamente cadastrado na rede social, inclusive, com todas as suas relações; 
ii. caso o usuário não esteja cadastrado, exibir uma mensagem de erro.
*/
	
	int confirmacao=0,vzs;
	char aux[20];
	TipoLista lstAux, lstAux1;
	usuario usuariosAux;
	TNo *ptrAux;
	
	printf("\n\t VOCE REALMENTE DESEJA REMOVER O USUARIO %s DA REDE? 1-sim 2-nao\n", vetorUsuarios[existe].nome);
	scanf("%d", &confirmacao);
	
	if(confirmacao == 1){

		strcpy(aux,vetorUsuarios[existe].nome);


//---------------------------- Comeco Removendo da lista ------------------	
/* para a remocao da lista é primeiro verificado na matriz em quais posicoes em que o usuario segue ou é seguido, pulando as posicoes onde nao acontece essa relacao */
	
	for(int i=0;i<qntCadastros;i++){
		if(matrizUsuarios[i][existe] == 1){
				usuariosAux = vetorUsuarios[existe];
				removeLista(usuariosAux,&listaSegue[i]);
		}
		
		if(matrizUsuarios[existe][i] == 1){
				usuariosAux = vetorUsuarios[existe];
				removeLista(usuariosAux,&listaSeguido[i]);
		}
	}
	
//---------------------------- fim Removendo da lista ------------------

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

//---------------------------- Comeco Removendo da arvore ------------------

	/* a intenção para a remocao da arvore AVl  é pasar por todas a celulas removendo o no que está o valor removido, isso tanto na arvore que reseva os seguidores
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

//---------------------------- Comeco Removendo do vetor ------------------
	
		for(int i=existe;i<qntCadastros;i++){
			vetorUsuarios[i] = vetorUsuarios[i+1];
		}
		
//---------------------------- Fim Removendo do vetor ------------------		
		qntCadastros--; //contador de usuarios diminui junto com que é removido
		
		printf("\n\tO usuario %s foi removido e a rede tem  %d usuarios\n",aux,qntCadastros-1);
	}
}

void removerRelacao(int existe,int existe1, usuario vetorUsuarios[tam], int matrizUsuarios[tam][tam],TNo **ptr,TNo **ptrSeguido,TipoLista listaSegue[tam],TipoLista listaSeguido[tam]){
/*
i. remove uma relação previamente cadastrada na rede social; 
ii. caso algum elemento da relação a ser removida (vértice ou aresta) não esteja inserido, exibir uma mensagem de erro.
*/	
	TNo *ptrAux;
	TipoLista lstAux, lstAux1;
	usuario usuariosAux;
	
	if(matrizUsuarios[existe][existe1] == 0){ //faz a verificacao se a relacao existia ou nao, faz so na matriz pq as outras iriam da o mesmo resultado
		printf("\n\n\tO usuario %s ja nao seguia o usuario %s", vetorUsuarios[existe].nome, vetorUsuarios[existe1].nome);
	}
	else if(matrizUsuarios[existe][existe1] == 1){
//---------------------------- Comeco Removendo da matriz ------------------					
		matrizUsuarios[existe][existe1] = 0;
//---------------------------- Fim Removendo da matriz ------------------							

//---------------------------- Comeco Removendo da arvore AVL ------------------					
		ptrAux = ptr[existe];
		retiraAVL(&ptrAux,vetorUsuarios[existe1]);
		ptr[existe]=ptrAux;
		
		ptrAux = ptrSeguido[existe1];
		retiraAVL(&ptrAux,vetorUsuarios[existe]);
		ptrSeguido[existe1]=ptrAux;
//---------------------------- Fim Removendo da arvore AVL ------------------							

//---------------------------- Comeco Removendo da lista ------------------							
		lstAux=listaSegue[existe];
		usuariosAux = vetorUsuarios[existe1];
		removeLista(usuariosAux,&lstAux);
		listaSegue[existe] = lstAux;		
		
		lstAux=listaSeguido[existe1];
		usuariosAux = vetorUsuarios[existe];
		removeLista(usuariosAux,&lstAux);
		listaSeguido[existe1] = lstAux;
//---------------------------- Fim Removendo da lista ------------------							
		
	}
}
//---------------------------- Comeco printa todos os usuarios ------------------	
void printaTodosUsuarios(usuario vetorUsuarios[tam]){

	int vzs=10; //Pra quando houver mais de x usuarios cadastrados, esse número ser usado como base para quebraa de linha no for a abaixo
	printf("\n\t\t\t\t\t- Todos usuarios -\n\t");
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
	printf("\n");
}
//---------------------------- Fim printa todos os usuarios ------------------	

//---------------------------- Comeco funcao para verificar se existe e retornar a posicao ------------------	
int verificaSeExiste(usuario vetorUsuarios[tam],char nomeListaCadastrados[20]){ /*funcao responsavel por verificar se o usuario digitado na main esta cadastrado na rede
retornando a posicao que ele se encotra no vetor responsavel por armazenar os cadastros (vetorUsuarios) */
	
	int posicao = 0;
	for(int i=1;i<qntCadastros;i++){
		if(strcmp(nomeListaCadastrados, vetorUsuarios[i].nome)==0){ //verifica onde que e igual e se existe e salva a posicao no vetor que ele esta
			posicao=i;
			break;
		}
	}
	
	if(posicao == 0){ //caso não encontrar
		printf("\n\nO nome digitado nao esta cadastrado na rede. Digite novamente!\n\n");
		system("pause");
		return 0;
	}
	else{ //caso encontrar
		return posicao; 
	}	
}
//---------------------------- Comeco funcao para verificar se existe e retornar a posicao ------------------	
//---------------------------- Fim funcoes de inicializacao, insercao, impressao e retirada de relacoes e usuarios ------------------	
