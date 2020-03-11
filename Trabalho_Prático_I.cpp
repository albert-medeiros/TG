#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include avl.h

#define tam 51

typedef struct usuario{ // Dados dos alunos
	char nome[20];
	int idade;
	
}TipoAluno;

void inicializaGrafos(usuario matrizUsuarios[tam][tam]){ 
/*
i. preenche a matriz de pesos com zeros, aloca uma posi��o de mem�ria (posi��o 0) para as listas de adjac�ncia e adjac�ncia em AVL e faz com o que seus conte�dos apontem para NULL; 
ii. n�o � necess�rio oferecer essa op��o ao usu�rio; 
iii. poder�o ser utilizados os �ndices da lista de 1 a n
*/

	printf("\n\n\t -> Inicializando o Grafo: \n");
	for(int i=0; i<tam;i++){
		for(int j=0; j<tam;j++){
			//printf("%d\n");
			matrizUsuarios[i][j].idade = 0;
			strcpy(matrizUsuarios[i][j].nome, "");
		}
	}
}

void inserirUsuario(){
/*
i. libera, dinamicamente, uma linha e uma coluna da matriz de pesos para representar as rela��es do novo usu�rio, aloca uma posi��o de mem�ria em cada uma das listas e realiza a inser��o de tal usu�rio pelo nome (que ser� fornecido); 
ii. o programa dever� verificar se o usu�rio j� est� inserido e, caso positivo, retornar uma mensagem de erro.
*/

}

void inserirRelacao(){
/*
i. insere uma rela��o de �� seguidor de/seguido por� entre um par de usu�rios;
ii. nessa opera��o de inser��o, os usu�rios dever�o estar previamente inseridos na rede; 
iii. dever�o ser listados os nomes dos usu�rios da rede social para que o usu�rio do programa se guie na escolha; 
iv. a inser��o da rela��o � conclu�da ap�s a inclus�o simult�nea das informa��es nas tr�s estruturas representativas; 
v. caso a rela��o j� esteja inserida, deve-se oferecer a op��o de atualizar a o per�odo de tempo associado entre os dois usu�rios selecionados;
vi. no caso da representa��o na lista com adjac�ncias em AVL, ao se inserir uma nova rela��o, � necess�rio verificar se as AVLs que representam 
	os usu�rios foram desbalanceadas e, caso positivo, realizar as opera��es de rotacionamento de v�rtices (n�s). ? Revise os algoritmos de rotacionamento de �rvores AVL e utilize os algoritmos j� implementados em outras atividades.
*/

}

void listarSeguidores(){
/*
i.ap�s o usu�rio do programa escolher um usu�rio cadastrado x, esta op��o dever� listar todos os usu�rios os quais x segue e por quais usu�rios x � seguido, inclusive com os tempos relacionados � cada rela��o existente; 
ii. no caso da representa��o por lista com adjac�ncias em AVL, fornecer ao usu�rio a op��o de se utilizar algum dos algoritmos de percurso em �rvores in-ordem, pr�-ordem ou p�s-ordem.
*/


}

void listarSeguidoresVelhos(){
//i. lista todos os usu�rios que s�o seguidos por usu�rios mais velhos, inclusive com os quantitativos associados a cada um deles.


}

void atualizarRelacao(){
//i. ocorre similarmente � inser��o de rela��es, por�m a rela��o dever� estar previamente inserida. ii. caso a rela��o n�o esteja inserida deve-se oferecer essa op��o ao usu�rio do programa.

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
	usuario matrizUsuarios[tam][tam];
	inicializaGrafos(matrizUsuarios, );
		
}
