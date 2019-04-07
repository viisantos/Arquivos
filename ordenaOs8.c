#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)

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

int compara(const void *e1, const void *e2)
{
	return strncmp( ((Endereco*)e1)->cep, ((Endereco*)e2)->cep ,8);
}

int main(int argc, char**argv)
{
	
	
	FILE *f, *saida;
	Endereco *e;
	long posicao, qtd, metade;

	
	for(int l = 1; l <= 8; l++){
		
		char bloco_numero[20]; //Este aqui especifica o nome de cada "arquivinho" de CEP.
		char ordenado[20];		
		sprintf(bloco_numero,"bloco%d.dat",l);		
		f = fopen(bloco_numero,"r");
		fseek(f,0,SEEK_END);
		posicao = ftell(f);
		qtd = posicao/sizeof(Endereco);
		e = (Endereco*) malloc(qtd*sizeof(Endereco));
		rewind(f);

		if(fread(e,sizeof(Endereco),qtd,f) == qtd)
		{
			printf("Lido = OK\n");
		}
		qsort(e,qtd,sizeof(Endereco),compara);
		printf("Ordenado = OK\n");
		sprintf(ordenado,"%s%d.dat","blocoOrdenado",l);
		saida = fopen(ordenado,"w");
		fwrite(e,sizeof(Endereco),qtd,saida);
		fclose(saida);
		printf("Escrito = OK\n");
		free(e);
		fclose(f);	
    }
	
}

