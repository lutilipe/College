#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAM 100

/*
Linhas com a expressao [CODIGO_AQUI] indicam que voce 
precisa implementar algo na linha.
*/

void modificarNotas(char nome_arquivo[]) {
	int num=-1, num_edit;
	char* nome;
	char buf[MAX_TAM];	
	float nota1, nota2;
	FILE *arq, *temp;
	int achei=0;

	arq = fopen(nome_arquivo, "r");
	
	if (arq == NULL) {
		printf("Erro ao abrir o arquivo\n");
		return;
	}

	
	printf("\nDigite o numero do aluno a modificar: ");
	scanf("%d", &num_edit);
	
	printf("\nProcurando...");
	
	temp = fopen("temp.txt", "");

	fgets(buf, MAX_TAM, arq);
	while(!feof(arq)) {
		num = atoi(strtok(buf, ","));
		nome = strtok(NULL, ",");
		nota1 = atof(strtok(NULL, ","));
		nota2 = atof(strtok(NULL, ","));
		
		if (num == num_edit) {
			printf("Digite as novas notas:\n");
			scanf("%4f %f", &nota1, &nota2);
			achei = 1;
		}
		
		//escrever os dados lidos do arquivo "nome_arquivo" no arquivo temporario
		fprintf(temp, "%d,%s,%4.1f,%4.1f\n", num, nome, nota1, nota2);
		
		fgets(buf, MAX_TAM, arq);
	}
	
	fclose(arq);
	fclose(temp);
	
	if(achei == 0)
		printf("\nAluno nao encontrado!");
	else{ 
		remove(nome_arquivo);
		rename("temp.txt", nome_arquivo);
	}
}

void leAluno(char nome_arquivo[], int num_alunos) {
	int num;
	char nome[20];
	float nota1, nota2;
	FILE *arq;
	arq = fopen(nome_arquivo,"a");
	if(arq == NULL) {
		printf("\nErro ao abrir o arquivo!");
		return;
	}

	/*
	modificar o codigo abaixo para ler os dados de "num_alunos" 
	alunos ao inves de apenas 1: 
	*/

	while (num_alunos > 0) {
	
		printf("\nDigite os dados do novo aluno");
		printf("\nNum: ");
		scanf("%d", &num);
		printf("\nNome: ");
		fflush(stdin);
		fgets(nome, MAX_TAM, stdin); 
		printf("\nNota1: ");
		scanf("%f", &nota1);
		printf("\nNota2: ");
		scanf("%f", &nota2);	
		
		fprintf(arq, "%d,%s,%4.1f,%4.1f\n", num, nome, nota1, nota2);
		num_alunos--;
	}	

	fclose(arq);
	
}

/*
imprime as notas dos alunos que estao gravados no arquivo
"nome_arquivo" (ex: GAAL.txt):
*/

void imprimeNotas(char nome_arquivo[]) {
	float notas,media;
	char buf[MAX_TAM];
	int num;
	char *nome;
	float nota1, nota2;
	FILE *arq;
	arq = fopen(nome_arquivo,"r");
	if(arq == NULL) {
		printf("\nErro ao abrir o arquivo!");
	return;
	}

	printf("\nmatricula\t nome\t\t nota1\t nota2\t");

	notas=0;
	media=0;
	fgets(buf, MAX_TAM, arq);
	while(!feof(arq)) {
		num = atoi(strtok(buf, ","));
		nome = strtok(NULL, ",");
		nota1 = atof(strtok(NULL, ","));
		nota2 = atof(strtok(NULL, ","));
		printf("\n%d \t %20s \t %4.1f \t %4.1f", num, nome, nota1, nota2);
		notas = notas + 2;
		media = media + nota1 + nota2;
		fgets(buf, MAX_TAM, arq);
	}
	printf("\nmedia = %f",media/notas);
	fclose(arq);
}

int main(int argc, char *argv[]) {

	int i;
	char nome_arquivo[10] = "GAAL.txt";
	char exibe_media='N';
	char edita_aluno = 'N';
	int le_alunos = 0;
	for(i=0; i<argc; i++) {
		//verifica se ha o parametro -d na lista de parametros:
		if(strcmp(argv[i], "-d") == 0) {
			//caso positivo, coloca o parametro seguinte na variavel nome_arquivo e acrescenta a extensao .txt:
			printf("%d -d\n", argc);
			strcpy(nome_arquivo, argv[i+1]);
			strcat(nome_arquivo, ".txt");
		}
		//verificar se tem o parametro -m na lista:
		else if(strcmp(argv[i], "-m") == 0) {
			printf("%d -m\n", argc);
			//caso positivo, coloca o primeiro caractere (o segundo eh o \0) do parametro seguinte na variavel exibe_media:
			exibe_media = argv[i+1][0];
		}
		
		//verifica se tem o parametro -e na lista:
		else if(strcmp(argv[i], "-e") == 0) {
			printf("%d -e\n", argc);
			edita_aluno = 'S';
		}
			
		//verifica se tem o parametro -l na lista:
		else if(strcmp(argv[i], "-l") == 0 && argv[i + 1]) {
			printf("%d -l\n", argc);
			le_alunos = atoi(argv[i + 1]);
		}
		
		//para exibir a ajuda
		else if(argc == 1 || strcmp(argv[i], "-help") == 0 || argv[i][0] == '?') {
			printf("\nParametros do programa:");
			printf("\n-d [XXX] ..... Sigla da disciplina. Ex: -d AEDS1");
			printf("\n-m [S ou N] ..... Exibir media. Ex: -m S");
			printf("\n-l [#] ..... Le informacao sobre # alunos. Ex: -l 4");				
			printf("\n-e ..... Modifica nota de aluno.");			
			return 1;		
		}
	}
	
	//Chamar os metodos dependendo dos parametros
	if(le_alunos > 0)
		leAluno(nome_arquivo, le_alunos);

	//se "edita_aluno" for 'S', chama o metodo para modificar notas:
	if(edita_aluno == 'S') {
		modificarNotas(nome_arquivo);
	}

	//se "exibe_media" for 'S', chama o metodo para imprimir notas:
	if(exibe_media == 'S') {
		imprimeNotas(nome_arquivo);
	}

	
return 0;
}