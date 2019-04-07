#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

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


int main(int argc, char**argv){ 
	FILE *arquivo_original = fopen("peguei80.dat","r");

	Endereco v[N];	
//	char linha_endereco [3000]; 
	//Cada linha tem 300 bytes, o tamanho de uma struct. 
	//Para não precisarmos declarar a struct novamante, criamos um array de char para armazenar as informações contidas no struct endereço.
	
	//-------- Importante a cada vez que executamos este código ////
	//Como temos o append, na criação de cada arquivinho novo, isso faz com que sejam escritos novos registros.
	//Para evitar que escrevamos registros repetidos, vamos executar o seguinte:
	
		for(int k =1; k <= 8; k++){
			char nome_bloco[] = "bloco";
			char bloco_numero[20];
			
			sprintf(bloco_numero,"%s%d.dat",nome_bloco,k);//Esta função serve para concatenar cadeias de caracteres., onde o primeiro parametro
                                                                      //corresponde ao nome do arquivo, "%s%d.dat" é um template para a concatenação,é a concatenação 									      //das strings, os dois ultimos parametros são as variaveis que serão concatenadas.
			FILE *novos = fopen(bloco_numero,"w"); // Aqui, evitamos a repetição de registros.
			fclose(novos);
		}
	
	//Este "for" é responsável por criar cada um dos 8 arquivos de que precisamos.
	for(int i = 1; i <= 8; i++){
		char nome_bloco[] = "bloco";//este é um nome generico
		char bloco_numero[20]; //Este aqui especifica o nome de cada "arquivinho" de CEP.
		sprintf(bloco_numero,"%s%d.dat",nome_bloco,i);
		//Nesta linha, nome_bloco é o nome do arquivo, "%s%d.dat" é o formato de nome que desejamos, onde iremos concatenar "nome_bloco" com "i"
		
		//Agora, para cada arquivinho com o seu nome definido, vamos seguir os seguintes procedimentos:
			FILE *novos = fopen(bloco_numero,"a");
		//Nesta linha, estamos criando um novo arquivo com o nome definido no primeiro "for". O "a" é de append, que vai acrescentando novos registros, sem apagar os que já existiam.
			
			fread(v, sizeof(Endereco), N, arquivo_original);
			//nesta linha, lemos 1 linha de cada vez, do 'arquivo_original', cada uma delas de tamanho 300 bytes, 
			fwrite(v, sizeof(Endereco), N, novos);
			//fwrite(linha_endereco, 3000, 1, novos);
			//fprintf(novos,"%.3000s",linha_endereco);
			//Aqui, a saída padrão é redirecionada pro novo arquivo. cada linha do endereço é redirecionada para este arquivo.
			
			fclose(novos);
			//Fechamos o arquivo novo.
		}
		
		//Ordenar
		/*
		for(int a =1; a <= 8 ;a++){
			for(int b=1; b <= 10; b++){
				
			}*/
		}
		
	
