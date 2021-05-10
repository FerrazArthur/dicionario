#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "avlcharlib.h"
#define TABLE 23
/*
 ALUNO : ARTHUR FERRAZ
    TRABALHO 3 DE ESTRUTURAS DE DADOS : DICIONÁRIO
*/

void setHash(BST *hs[]){
	for(int i = 0; i < TABLE; i++){
		hs[i] = NULL;
	}
}
//retorna o indice dessa string 
int pos(char *value){
	int sum = 0, i;
	for(i = 0; value[i] != '\0'; i++)
		sum += (int) value[i];
	return (sum/i)%TABLE;
}
void insertHashAVL(BST *hash[], char *new){
	int i = pos(new);//encontramos o codigo hash dessa string
	if(insertAVL(&hash[i], createNodeBST(createInfo(new))))
		printf("Sucesso\n");
	else
		printf("Fracasso\n");
}
int searchHashAVL(BST *hash[], char *find){
	int i = pos(find), ret = 0;
	Info *temp = createInfo(find);
	if(searchBST(hash[i], temp) != NULL)
		ret = 1;
	free(temp);
	return ret;
}
void deleteHashAVL(BST *hash[], char *del){
	int i = pos(del);//encontramos o codigo hash dessa string
	if(deleteAVL(&hash[i], del))//não consegui implementar deleteAVL() a tempo!
		printf("Sucesso\n");
	else
		printf("Fracasso\n");
}
int main(){
	int n = 0;
	char *temp;
	BST *hash[TABLE];
	//inicializa todo elemento BST em hash para NULL;
	setHash(hash);
	while(1){
		printf("[1] Inserir palavra no dicionário\n");
		printf("[2] Consultar palavra no dicionário\n");
		printf("[3] Remover palavra do dicionário\n");
		printf("[4] Sair\n");
		scanf("%d", &n);
		switch(n){
			case 1:
				printf("Digite a palavra: ");
				scanf("%s", temp);
				insertHashAVL(hash, temp);
				break;
			case 2:
				printf("Digite a palavra: ");
				scanf("%s", temp);
				if(searchHashAVL(hash, temp))
					printf("Palavra esta no dicionário\n");
				else
					printf("Palavra não esta no dicionário\n");
				break;
			case 3:
				printf("Digite a palavra: ");
				scanf("%s", temp);
				deleteHashAVL(hash, temp);
				break;
			case 4:
				return 0;
			default:
				break;
		}
	}
	return 1;
}
