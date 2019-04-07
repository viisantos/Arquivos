#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#define qtd 8 

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

Endereco *e;


int main(){

	char n1[40];
	char l[300]; //onde "l" � o ponteiro para a linha (registro)
	sprintf(n1,"cep.dat");

	FILE *f1 = fopen(n1,"r");
	FILE *f2 = fopen("peguei80.dat","w");
	int linha = 0;

	
	srand((unsigned)time(NULL));

	for(int i = 1; i <= qtd; i++){
		fseek(f1, (rand()%100000)* 300 , SEEK_SET);//setar a cabe�a de leitura numa posicao aleatoria
		fread(l,300,1,f1); //Armazena em "l" "1" linha do arquivo f1, de tamanho "sizeof(Endereco)"
		fprintf(f2,"%.300s",l); //Escreve em f2 o conte�do de "l", obtido  antes de entrar no for.
		
	}
	fclose(f1);
	fclose(f2);
	return 0;
}

