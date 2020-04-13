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

#include "opera.h"

#define tam 51
#define ALOCA (TNo*)malloc(sizeof(TNo))

//----------------------------------------------------------------------------------------------------------------->  ~ MAIN ~
main(){
	
	//declaração de variaveis e criação da struct
	int matrizUsuarios[tam][tam],opcListausuarios,vzs=10,existe=0,modo=0;
	int existe1=0,opcMenu=-1;
	char nomeListaCadastrados[20];
	usuario vetorUsuarios[tam], user;
	TNo *ptrSegue[tam],*ptrSeguido[tam]; //ptrSegue é o vetor que mostra quem o usuário segue e ptrSeguido por quem o usuario é seguido
	TipoLista listaSegue[tam],listaSeguido[tam];
	
	
	inicializaGrafos(vetorUsuarios, matrizUsuarios, ptrSegue, ptrSeguido,listaSegue,listaSeguido);
	
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
				//insere os usuários a serem cadastrados usando o arquivo e depois mostra quantos foram mostrados ( é qntCadastros menos 1 pq comeca em 1)-
				inserirUsuario(vetorUsuarios); //os usuarios sao inseridos somente no vetorUsuarios pq e com ele que se fara a verificacao das posicoes
				// que os dados estao inseridos em todas as estruturas implmentadas
				printf("\n\n\t  - - - - %d usuarios cadastrados - - - -\n\n", qntCadastros-1);
				system("pause");
				
			break;
			
			case 2:
				
				inserirRelacao(vetorUsuarios, matrizUsuarios,ptrSegue,ptrSeguido,listaSegue,listaSeguido); /* é na insercao de realacao que se preenche as estruturas ( matris de adjacencias
				lista de adjacencias e arvores. nesse caso oprtou-se por utilizar duas arvores 1 para salvar quem o usuario segue e outra pra quem o usuario é seguido para
				desta forma ficar mais simmples quando for necessario mostrar o mais velho ou seguidores e seguidos. */
				
				printf("\n\n");
				system("pause");
				
			break;
			
			case 3:
				//--------------------------------- comeco Listando os seguidores do usuário a ser escolhido -----------------------------------------------------------
				opcListausuarios=0,existe=0;modo=0;existe1=0; //zera as variaveis auxiliares para garantir a entrada dentro dos whiles
				
				// ------------------ Comeco da listagem de todos os usuarios ---------------------
				printf("\n\nVoce deseja listar todos os usuarios ? 1-sim 2-nao\n"); //lista todos os usuários cadastrados na rede
				scanf("%d",&opcListausuarios); printf("\n\n\t");
			
				if(opcListausuarios == 1){
					printaTodosUsuarios(vetorUsuarios); //funcao para imprimir todos os usuarios que estao cadastrados na rede
				}
				// ------------------ Fim da listagem de todos usuarios ---------------------
				
				// ------------------ Comeco da verificacao se o nome a ser pesquisado exite ---------------------	
				while(existe==0){
					printf("\nDigite o nome do usuario a ser verificado: ");
					scanf("%s", &nomeListaCadastrados);
					existe = verificaSeExiste(vetorUsuarios, nomeListaCadastrados);	//existe recebe o retorno da funcao que eh a posicao que o nome esta
				}
				// ------------------ Fim da verificacao se o nome a ser pesquisado exite ---------------------	

				// ------------------ Comeco da verificacao em qual estrutura será mostrado a seguencia de seguidores e seguidos ---------------------									
				while(modo == 0){
					printf("\nDigite o modo a ser listado:\n\t\t 1- Matriz de Pesos\n\t\t 2- lista de adjacencias\n\t\t 3- lista de adjacencias em Arvores AVL\n");
					scanf("%d",&modo);
					if(modo>3 || modo<0){
						modo=0;
						printf("\n\t\tO numero digitado eh invalido. Digite novamente!\n");
						system("pause");
					}	
				}
				// ------------------ Fim da verificacao em qual estrutura será mostrado a seguencia de seguidores e seguidos ---------------------
				//printf("\t\t\t %s\n",lstSegue[1]->ultimo->user.nome);								
					
				listarSeguidores(existe,vetorUsuarios,matrizUsuarios,modo,ptrSegue,ptrSeguido,listaSegue,listaSeguido); /* chama a função resposavel por listar os seguidores, para ela é passada
				a posicao em que o nome esta no vetor (exite), o vetor auxiliar onde estão inseridos os usuario (vetorUsuarios), a matriz de adjacencias
				(matrizUsuarios), em qual estrutura será mostrada (modo), vetor de arvores (ptrSegue) */
				system("pause");
			//---------------------------------- Fim Listando os seguidores do usuário a ser escolhido -----------------------------------------------------------

			break;
			
			case 4:
				//---------------------------------- Comeco Listando quem o usuario mais velho segue -----------------------------------------------------------				
				opcListausuarios=0,existe=0;modo=0;existe1=0; //zera as variaveis auxiliares para garantir a entrada dentro dos whiles
					
				// ------------------ Comeco da listagem de todos os usuarios ---------------------
				printf("\n\nVoce deseja listar todos os usuarios ? 1-sim 2-nao\n"); //lista todos os usuários cadastrados na rede
				scanf("%d",&opcListausuarios); printf("\n\n\t");
			
				if(opcListausuarios == 1){
					printaTodosUsuarios(vetorUsuarios); //funcao para imprimir todos os usuarios que estao cadastrados na rede
				}
				// ------------------ Fim da listagem de todos usuarios ---------------------
									
				// ------------------ Comeco da verificacao se o nome a ser pesquisado exite ---------------------	
				while(existe==0){
					printf("\nDigite o nome do usuario a ser verificado: ");
					scanf("%s", &nomeListaCadastrados);
					existe = verificaSeExiste(vetorUsuarios, nomeListaCadastrados);								
				}
				// ------------------ Fim da verificacao se o nome a ser pesquisado exite ---------------------	
				
				listarSeguidoresVelhos(existe,vetorUsuarios,matrizUsuarios,ptrSegue,listaSegue); /* Colocar explicacao */				
				system("pause");
				
			//---------------------------------- Fim Listando quem o usuario mais velho segue -----------------------------------------------------------

			break;
			
			case 5:
				//---------------------------------- Comeco Atualizando relacoes -----------------------------------------------------------
				opcListausuarios=0,existe=0;modo=0;existe1=0; //zera as variaveis auxiliares para garantir a entrada dentro dos whiles					
			
				// ------------------ Comeco da listagem de todos os usuarios ---------------------
				printf("\n\nVoce deseja listar todos os usuarios ? 1-sim 2-nao\n"); //lista todos os usuários cadastrados na rede
				scanf("%d",&opcListausuarios); printf("\n\n\t");
			
				if(opcListausuarios == 1){
					printaTodosUsuarios(vetorUsuarios); //funcao para imprimir todos os usuarios que estao cadastrados na rede
				}
				// ------------------ Fim da listagem de todos usuarios ---------------------	
				
				// ------------------ Comeco da verificacao se o nome a ser pesquisado exite ---------------------	
				while(existe==0||existe1==0){
					printf("\n\nDigite o nome do usuario que vai comecar de seguir: ");
					scanf("%s", &nomeListaCadastrados);
					existe = verificaSeExiste(vetorUsuarios, nomeListaCadastrados);												
				
					printf("\n\nDigite o nome do usuario que vai parar ou comecar ser seguido: ");
					scanf("%s", &nomeListaCadastrados);
					existe1 = verificaSeExiste(vetorUsuarios, nomeListaCadastrados);		
				}
				// ------------------ Fim da verificacao se o nome a ser pesquisado exite ---------------------		
							
				atualizarRelacao(existe, existe1,vetorUsuarios,matrizUsuarios,ptrSegue,ptrSeguido);	/* Colocar explicacao */		
					
			//---------------------------------- Fim Atualizando relacoes -----------------------------------------------------------				
			break;
			
			case 6:
				//---------------------------------- Comeco removendo um usuário -----------------------------------------------------------
				opcListausuarios=0,existe=0;modo=0;existe1=0; //zera as variaveis auxiliares para garantir a entrada dentro dos whiles
				
				// ------------------ Comeco da listagem de todos os usuarios ---------------------
				printf("\n\nVoce deseja listar todos os usuarios ? 1-sim 2-nao\n"); //lista todos os usuários cadastrados na rede
				scanf("%d",&opcListausuarios); printf("\n\n\t");
			
				if(opcListausuarios == 1){
					printaTodosUsuarios(vetorUsuarios); //funcao para imprimir todos os usuarios que estao cadastrados na rede
				}
				// ------------------ Fim da listagem de todos usuarios ---------------------	
						
				// ------------------ Comeco da verificacao se o nome a ser pesquisado exite ---------------------	
				while(existe==0){
					printf("\nDigite o nome do usuario a ser verificado: ");
					scanf("%s", &nomeListaCadastrados);
					existe = verificaSeExiste(vetorUsuarios, nomeListaCadastrados);								
				}
				// ------------------ Fim da verificacao se o nome a ser pesquisado exite ---------------------	
				
				removerUsuario(existe,vetorUsuarios,matrizUsuarios,ptrSegue,ptrSeguido,listaSegue,listaSeguido);/* Colocar explicacao */
				system("pause");

			//---------------------------------- Fim removendo um usuário -----------------------------------------------------------			
			break;
			
			case 7:				
				//---------------------------------- Comeco removendo uma relacao -----------------------------------------------------------
				opcListausuarios=0,existe=0;modo=0;existe1=0; //zera as variaveis auxiliares para garantir a entrada dentro dos whiles	
											
				// ------------------ Comeco da listagem de todos os usuarios ---------------------
				printf("\n\nVoce deseja listar todos os usuarios ? 1-sim 2-nao\n"); //lista todos os usuários cadastrados na rede
				scanf("%d",&opcListausuarios); printf("\n\n\t");
			
				if(opcListausuarios == 1){
					printaTodosUsuarios(vetorUsuarios); //funcao para imprimir todos os usuarios que estao cadastrados na rede
				}
				// ------------------ Fim da listagem de todos usuarios ---------------------
								
				// ------------------ Comeco da verificacao se o nome a ser pesquisado exite ---------------------	
				while(existe==0||existe1==0){
					printf("\n\nDigite o nome do usuario que vai parar de seguir: ");
					scanf("%s", &nomeListaCadastrados);
					existe = verificaSeExiste(vetorUsuarios, nomeListaCadastrados);												
				
					printf("\n\nDigite o nome do usuario que vai parar de ser seguido: ");
					scanf("%s", &nomeListaCadastrados);
					existe1 = verificaSeExiste(vetorUsuarios, nomeListaCadastrados);		
				}
				// ------------------ Fim da verificacao se o nome a ser pesquisado exite ---------------------	
				
				removerRelacao(existe,existe1,vetorUsuarios,matrizUsuarios,ptrSegue,ptrSeguido,listaSegue,listaSeguido);/* Colocar explicacao */				
				system("pause");
				//---------------------------------- Fim removendo uma relacao -----------------------------------------------------------
			break;
			
			case 0:
				system("cls");
				printf("\n\n\n\n \t\tO programa chegou ao seu fim - igual a minha vontade de Fazer faculdade :(\n\n\n\n\t\t\t");			
				system("pause");
			break;
		}
		
	}
}
