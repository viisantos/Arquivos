#include <stdio.h>
#include <string.h>
#include <locale.h>

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

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	long posicao, primeiro, ultimo, meio;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}
	
	
		f = fopen("cep_ordenado.dat","r");
	
		int cont = 0;
		fseek(f,0,SEEK_END);
		posicao = ftell(f);
		rewind(f);
		primeiro = 0;
		ultimo = (posicao/sizeof(Endereco))-1;
	
	while(primeiro <= ultimo){ 
	
		meio = (primeiro+ultimo)/2;
		
		fseek(f, meio * sizeof(Endereco), SEEK_SET);
		cont++;
		fread(&e,sizeof(Endereco),1,f);		
		//onde &e e o endereco da variavel da struct endereco, sizeof e o tamanho da struct, 1 e a quantidade de enderecos que esta sendoinserida e f eo ponteiro pro arquivo.
			if(strncmp(argv[1],e.cep,8)==0){
			
				printf("Achei! \n\n",setlocale(LC_ALL,""));
				//Essa mensagem, alem de enfatizar que ja achamos, serviu para utilizar o setlocale,
				//para que a exibição de caracteres especiais
				//no restante do código não fique comprometida.
				
				
				printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
				break;
			
			}
			else 
				if(strncmp(argv[1],e.cep,8) < 0){
				ultimo = meio-1;
				}
				else{	
					primeiro = meio+1;
				}
		
	
	}
	printf("\n Numero de enderecos lidos: %d\n", cont);
	

	fclose(f);
	return 0;

}




