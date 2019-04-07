#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define N  8 //Este � a quantidade de arquivinhos ordenados




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
/*
int compara(const void *e1, const void *e2){
	return strncmp( ((Endereco*)e1) -> cep,  ((Endereco*)e2) -> cep, 8);
}*/

//FILE *f1,*f2, *extra; 
//onde *f1 � o ponteiro do primeiro arquivo, *f2 � o ponteiro para o segundo arquivo, e 

//extra servirá caso trabalhemos com quantidade impar de arquivos.


Endereco *e1,*e2,*e3; //e1 se referencia ao primeiro cep, e2  ao segundo. sera �til no momento da compara��o. e3 servir� para o calculo do tamanho do registro
int quantidade; //Quantos arquivos desejamos intercalar


char nome1[30], nome2[30], nome3[30];

void intercala(char n1[30], char n2[30], char n3[30]){
	
	//Os dois primeiros arquivos sao os que ja estao ordenados
	FILE *f1 = fopen(n1,"r"); 
	FILE *f2 = fopen(n2,"r");

	//f3 sera o arquivo da intercalacao.
	FILE *f3 = fopen(n3,"w");

	char linha[300];
	//Em cada um desses fread, estamos lendo a primeira linha de cada arquivo. jogamos o conteudo lido em "e1" e "e2"
	fread(e1,300,1,f1);
	fread(e2,300,1,f2);

	while( (!feof(f1)) && (!feof(f2)) ){

		if(strncmp(e1->cep,e2->cep,8) < 0){
			//fwrite(e1,300,1,f3); Vou escrever "1" registro de "tamanho_registro" 
			fprintf(f3,"%.300s",e1);
			fread(e1,300,1,f1);
		}
		else{
			//fwrite(e2,300,1,f3);
			fprintf(f3,"%.300s",e2);
			fread(e2, 300,1, f2);
		}

	}
	//Após a execução deste bloco while, é garantido que um dos arquivos irá acabar primeiro.
	
		while(!feof(f1)){
			//fwrite(e1,300,1,f3);
			fprintf(f3,"%.300s",e1);
			fread(e1,300,1,f1);
		}

		while(!feof(f2)){
			//fwrite(e2,300,1,f3);
			fprintf(f3,"%.300s",e2);
			fread(e2,300,1,f2);
		}

		fclose(f1);
		fclose(f2);
		fclose(f3);
}

void copiar(char n1[30],char n2[30]){
	
	
	FILE *f1 = fopen(nome1,"r");
	FILE *extra = fopen(nome3,"w");

	//ler a primeira linha de f1 para inicializar o conteudo de &p
	Endereco *p;
	fread(p,sizeof(Endereco),1,f1);

	while(!feof(f1)){
		//fwrite(p,300,1,extra);
		fprintf(extra,"%.300s",p);
		fread(p,300,1,f1);
	}
	fclose(f1);
	fclose(extra);
}

int main(int argc, char **argv){
/*
		int nIt;
		
		printf("Quantos arquivos serão intercalados?");
		scanf("%d",&quantidade);


		if(quantidade%2 != 0){
			nIt = ((quantidade/2)+1); //Terei que gerar mais um arquivo de intercalação, desta vez contendo o arquivinho que sobrou, o ultimo, o (n+1)° arquivo.
		}
		else{
			nIt = quantidade/2;
		}
		/divido a quantidade por 2 em ambos os casos porque a cada iteração trabalho com dois arquivos.
		/caso a quabntidade de arquivos for impar, eu a divido por 2 e somo +1 unidade para criar mais um arquivo de intercalação com o Ordenado que sobrou.
		Deixei este trecho comentado porque poderia ser util mais tarde
		*/
		int nIt = N;
		int cont = 0;
		
		for(int i = 1; i <= (nIt/2); i++){//deixo o for chegar inclusive em nIt, para que eu possa valida-lo se e par ou nao no final da execucao do for.
		
			
			sprintf(nome1, "blocoOrdenado%d",i+cont);
			sprintf(nome2,"blocoOrdenado%d",i+i);
            sprintf(nome3, "intercalados/Inter%d.dat",i);

			intercala(nome1,nome2,nome3);

			cont++;

			//quando chegar na ultima iteracao
			if(i == nIt){
				if(nIt %2 != 0){

					sprintf(nome1, "blocoOrdenado%d",i+cont);
					sprintf(nome3,"intercalados/Inter%d.dat",i);

					copiar(nome1,nome3);
					/*vou copiar o conteudo deste arquivo para um outro arquivo, para colocar na pasta de intercalados.
					Porque se eu criar um segundo arquivo vazio, no momento em que eu chamar intercala
					e for comparar o conteudo do n1 com n2 vazio, não vai dar certo.
					Criar um n2 vazio era minha primeira ideia, por isso a explicacao :)
					*/
					

					
				}
			}	
		}
	return 0;
	}
	
	
