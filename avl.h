
//----------------------------------------------------------------------- A V L ------------------------------------------------------------------------------------
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

void insereAVL(TNo **ptr, TipoAluno alu){
	int FB,fb;
	
	if (*ptr == NULL){ // entra na hora de criar um novo nó
		(*ptr) = ALOCA; //aloco dinamicamente um espaço pra "ptr"
		(*ptr)->esq = NULL;
		(*ptr)->dir = NULL;
		(*ptr)->aluno.codigo = alu.codigo; // o nó recebe o valor do codigo
		(*ptr)->aluno = alu; // o nó recebe os outros valores
	}
	
	else{
		if(alu.codigo<(*ptr)->aluno.codigo){ //verificação para saber em qual lado é inserido o valor
			insereAVL(&(*ptr)->esq,alu); //passa o valor da esquerda se for menor
		}
		else if(alu.codigo>(*ptr)->aluno.codigo){ //verificação para saber em qual lado é inserido o valor
			insereAVL(&(*ptr)->dir,alu); //passa o valor da direita se for maior
		}
	}
	
	//FB - Pai;  
	//fb - filho;
	//Após inserir o valor é verifica do Fator de balanceamento
	
	FB=(altura((*ptr)->dir))-(altura((*ptr)->esq)); //calcula a altura ao desempilhar
	
	if(FB == +2){ //caso o FB do nó seja 2 então tem que fazer alteração 
			
		fb = altura((*ptr)->dir->dir)-altura((*ptr)->dir->esq); //calcula a altura do filho da direita
		
		if(fb==1){ // se for igual a um então rotação simples 
			rotacaoEsq(ptr);
		}
			
		else if(fb == -1){ // se for igual a menos um então rotação dulpa
			rotacaoDir(&(*ptr)->dir);
			rotacaoEsq(ptr);
		}
	}
		
	else if(FB == -2){
		
		fb = (altura((*ptr)->esq->dir))-(altura((*ptr)->esq->esq)); //calcula a altura do filho da direita
		if(fb== -1){ // se for igual a um então rotação simples 
			rotacaoDir(ptr);
		}
	
		else if(fb== +1){ // se for igual a menos um então rotação dulpa
			rotacaoEsq(&(*ptr)->esq);
			rotacaoDir(ptr);
		}	
	}	
}



void retiraAVL(TNo **ptr, int chave,int sor){
	int FB,fb;
	if((*ptr)==NULL){ //verifica se o valor está na árvore
		printf("\n O aluno #%d nao esta na arvore!\n",chave);
	}
	
	else if(chave<(*ptr)->aluno.codigo){ //verifica o lado que tem que seguir 
		retiraAVL(&(*ptr)->esq,chave,sor);
	}
	else if(chave>(*ptr)->aluno.codigo){
		retiraAVL(&(*ptr)->dir,chave,sor);
	}
	else{ //caso for a chave retirada
		TNo *aux = *ptr;	//copia o calor a ser retirado 
		if((*ptr)->dir == NULL){	//se a direita for NULL esq fica no lugar 
			(*ptr)=(*ptr)->esq;
			free(aux);
		}
		else if((*ptr)->esq==NULL){ //se a esq for NULL dir fica no lugar 
			(*ptr)=(*ptr)->dir;
			free(aux);
		}
		else{ // caso haja dois filhos
			if(sor == 1){
				sucessor((*ptr),&(*ptr)->dir);
			}
			else{
				antecessor((*ptr),&(*ptr)->esq);
			}
		}
	}
	
	if((*ptr)!=NULL){ // Para não verificar o nó que foi retirado e esperar a recursividade voltar para assim entrar dentro do if
		FB=altura((*ptr)->dir)-altura((*ptr)->esq); //calcula a altura ao desempilhar
	//	printf("FB: %d\n",FB);	
		
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
//----------------------------------------------------------------------- A V L------------------------------------------------------------------------------------
