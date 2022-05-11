#include <stdio.h>
#include <ctype.h> // isdigit
#include <stdlib.h> // free, calloc
#include <string.h> // strcmp

typedef enum{
    ERRO,NUMERO_INTEIRO,IDENTIFICADOR,EOS
}TAtomo;

typedef struct{
    TAtomo atomo;
    int linha;
}TInfoAtomo;

// variaveis globais
char *cadeia;
int linha = 1;

int qtdSpace = 0;
int palavras[52];
int num[10];

void leArquivo(char *nomeArquivo);
TInfoAtomo obter_atomo();

int main(void)
{
    for(int i = 0;i < 52; i++)
    {
        palavras[i] = 0;
    }
        for(int i = 0;i < 10; i++)
    {
        num[i] = 0;
    }
    char *iniBuffer;
    leArquivo("entrada.txt");
    iniBuffer = cadeia;

    while(1)
    {
        TInfoAtomo InfoAtomo = obter_atomo();
        if(InfoAtomo.atomo == ERRO)
        {
            cadeia++;
        }
        else if(InfoAtomo.atomo == EOS)
        {
            printf("\nfim de analise lexica\n");
            break; // quebra o laco
        }
    }
    printf("Numeros:\n");
    for(int i = 0; i < 10;i++)
    {
        if(num[i] != 0)
        {
            printf("%d: %d\n",i,num[i]);
        }
    }
    printf("------------------\nLetras:\n");
    int i = 0;
    for(int i = 0; i < 52;i++)
    {
        int soma;
        int c;
        if(i < 26) c = 97+i;
        else c = 65+i-26;
        if(palavras[i] != 0)
        {
            printf("%c: %d\n",c,palavras[i]);
        }
    }
    printf("Linhas: %d\n",linha);
    printf("espaco em branco: %d\n",qtdSpace);
}

TInfoAtomo obter_atomo()
{
    TInfoAtomo InfoAtomo;
    InfoAtomo.atomo = ERRO;

    while(*cadeia == 0 ||  *cadeia == ' ' || *cadeia == '\n' || *cadeia == '\r')
    {
        if(*cadeia == 0 )
        {
            InfoAtomo.atomo= EOS; // finaliza o programa
            InfoAtomo.linha = linha;
            return InfoAtomo;
        }
        if(*cadeia == '\n')
            linha++;
        if(*cadeia == ' ')
            qtdSpace++;
        cadeia++;
    }
    InfoAtomo.linha = linha;
    if(isalpha(*cadeia)) //se for um indentificador
        reconhece_identificador(&InfoAtomo);
    else if(isdigit(*cadeia)) //se for um indentificador
        reconhece_numero(&InfoAtomo);
    return InfoAtomo;
}

void reconhece_identificador(TInfoAtomo *InfoAtomo){
    int i=0;
    int dim = 0;
    if(isalpha(*cadeia))
        {
            char c = *cadeia;
            //printf("c %d ",c);
            //printf("Cadeia %d ",*cadeia);

            int local = (int)(*cadeia);

            //printf("Local %d ",local);
            if(local >= 97)
            {
                dim = 97;
            }
            if(local < 97)
            {
                dim = 65 - 26;
            }
            // consome o simbolo
            //printf("indece %d\n",local-dim);
            palavras[local-dim]++;

            cadeia++;
            InfoAtomo->atomo = IDENTIFICADOR;
            return;
       }
       if( isdigit(*cadeia))
            // retorna erro caso venha um simbolo desconhecido
            return;
}

void reconhece_numero(TInfoAtomo *InfoAtomo)
{
    if(isdigit(*cadeia))
    {
        int n = (int)(*cadeia);
        n -= 48;
        //printf("%d ",n);
        num[n]++;
        cadeia++;
        InfoAtomo->atomo = NUMERO_INTEIRO;
    }
    return;
}

void leArquivo(char *nomeArquivo){
    int tamArquivo;
    // abre o arquivo
    FILE *fp;
    fp = fopen(nomeArquivo,"r");
    if( !fp ){
        printf("falha na abertura de arquivo.\n");
        exit(1);
    }

    // move ponteiro para o final
    fseek(fp, 0, SEEK_END);
    tamArquivo=ftell(fp); // pega o numero de bytes deslocas
    fseek (fp, 0, SEEK_SET);// move o ponteiro para o inicio
    // aloca um buffer com a quantide de bytes
    cadeia = (char*)calloc(tamArquivo+1,sizeof(char));

    // le todos os caracteres do arquivo
    fread(cadeia,1,tamArquivo,fp);
    //printf("%s",cadeia);
    fclose(fp);
}
