#include <iostream>
#include <string.h>
#include <Windows.h>
#include <locale.h>

struct reg
{
	char nome[20];
	char tel[20];
	char email[20];
	char status;
};

int tamanho(FILE *arq)
{
	fseek(arq, 0, SEEK_END);
	return ftell(arq) / sizeof(reg);
}

void cadastrar(FILE *arq)
{
	reg contato;
	char confirma;
	contato.status = ' ';
	fflush(stdin);

	printf("Cadastrando novo registro:\n");
	printf("\nNumero do registro:%d\n", tamanho(arq) + 1);
	printf("Nome..........:");
	//getchar();
	gets(contato.nome);
	printf("Telefone......:");
	gets(contato.tel);
	printf("E-mail........:");
	gets(contato.email);
	printf("\nConfirma <S/N>:");
	fflush(stdin);
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("\nGravando registro...\n\n");
		fseek(arq, 0, SEEK_END);
		fwrite(&contato, sizeof(reg), 1, arq);

	}
	system("pause");
}

void consultar(FILE *arq)
{
	reg contato;
	int nr;
	printf("\nConsulta pelo codigo.\n");
	printf("\nInforme o Codigo desejado: ");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' ')
		{
			printf("\nNome......:%s", contato.nome);
			printf("\nTelefone..:%s", contato.tel);
			printf("\nE-mail....:%s\n\n", contato.email);
		}

		else
			printf("\nRegistro excluido! \n");

	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}


void geraarqtxt(FILE *arq)
{
	char nomearq[20];
	printf("Nome do arquivo texto:");
	scanf("%s", nomearq);
	strcat(nomearq, ".txt");
	FILE *arqtxt = fopen(nomearq, "w");
	if (!arqtxt)
	{
		printf("Nao foi possivel criar o arquivo!\n");
		system("pause");
		//return;
	}
	fprintf(arqtxt, "Nome                Telefone    E-mail                   Status\n");
	fprintf(arqtxt, "-----------------------------------------------------------------\n");
	fprintf(arqtxt, "-----------------------------------------------------------------\n");
	int nr;
	reg contato;
	for (nr = 0; nr<tamanho(arq); nr++)
	{
		fseek(arq, nr * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		fprintf(arqtxt, "%-20s%-12s%-25s- %c\n", contato.nome, contato.tel, contato.email, contato.status);
	}
	fprintf(arqtxt, "--------------------------------------------------------------------\n");
	fprintf(arqtxt, "--------------------------------------------------------------------\n");
	fclose(arqtxt);
}

void excluir(FILE *arq)
{
	reg contato;
	char confirma;
	int nr;

	printf("\nInforme o codigo do registro que deseja excluir: \n");
	scanf("%d", &nr);
	if ((nr <= tamanho(arq)) && (nr>0))
	{
		fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
		fread(&contato, sizeof(reg), 1, arq);
		if (contato.status == ' ')
		{
			printf("\nNome......:%s", contato.nome);
			printf("\nTelefone..:%s", contato.tel);
			printf("\nE-mail....:%s\n", contato.email);
			printf("\nDeseja confirmar a exclusao: <S/N>\n");
			getchar();
			scanf("%c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("\nExcluindo registro...\n\n");
				fseek(arq, (nr - 1) * sizeof(reg), SEEK_SET);
				contato.status = '*';
				fwrite(&contato, sizeof(reg), 1, arq);
			}
		}
	else
		printf("Registro inexistente!!! \n");
	}
	else
	{
		printf("\nNumero de registro invalido!!!\n");
	}
	system("pause");
}


int main()
{
	int op;
	FILE *arq;

	if ((arq = fopen("dados1.dat", "rb+")) == NULL)
	{
		if ((arq = fopen("dados1.dat", "wb+")) == NULL)
		{
			printf("Falha ao abrir o arquivo!\n");
			system("pause");
		}
	}

	//existentes no arquivo agenda1.dat
	do
	{
		system("CLS");
		printf("\n<---------> AGENDA <---------> \n\n");
		printf("1.Cadastrar\n");
		printf("2.Consultar por codigo\n");
		printf("3.Gerar arquivo\n");
		printf("4.Excluir registro\n");
		printf("5.Sair\n");
		printf(">>>>>>>>>>>>   Contatos:%d  \n", tamanho(arq));
		printf("Opcao: ");
		scanf("%d", &op);
		switch (op)
		{
		case 1://cadastrar novo contato
			cadastrar(arq);
			break;
		case 2://consultar por c�digo
			consultar(arq);
			break;
		case 3://	case 3:consultanome(arq);
		     geraarqtxt(arq);
			//gerar arquivo texto com todos os contatos 
			//ordenados 22alfabeticamente
			break;
		case 4: //exclui um registro do arq
			excluir(arq); 
			break;

		case 5: fclose(arq);
		}
	} while (op != 5);
}

