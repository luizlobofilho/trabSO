#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// função auxiliar de tratamento de strings  
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}


/*typedef struct {
	int blocos,seg_ocupados

} Arquivo;*/



// módulo de controle dos arquivos 
char controle_arq(char *linhaArq, int j){
	char **tokens;
	int i;
	
	tokens = str_split(linhaArq, ',');
		
	if (tokens)
    {
       	int i;
       	for (i = 0; *(tokens + i); i++)
       	{
           	printf("%s\n", *(tokens + i));
           	free(*(tokens + i));
       	}
       	printf("\n");
       	free(tokens);
    }

}



int main(){

	FILE *fp,*fq; 
	char ch[20] ,*linArqProc[20], *linArqOper[20], **tokens;
	
	// abre o arquivo de processos 
	fp = fopen ("arq.txt", "r");

	// abre o arquivo de operações 
	fq = fopen ("arq2.txt", "r");

	int i,numlinha, j;
	numlinha = 0;
	i = 0;

	// lê o arquivo de processos 
	if(fp == NULL ){
		printf("Erro ao abrir o arquivo 1 ! \n");
	}else{
		while(fgets(ch,sizeof ch ,fp) != NULL ){
			linArqProc[i] = strdup(ch);
			printf("O indice i=%d e o valor da linha é: %s\n",i,linArqProc[i]);
			i++;
			numlinha++;
		}
	}
	
	for(j=0;j<numlinha;j++){
		printf("\n%s", linArqProc[j] );
	}


	numlinha = 0;
	i = 0;

	// lê o arquivo de operações 
	if(fq == NULL ){
		printf("Erro ao abrir o arquivo 2 ! \n");
	}else{
		while(fgets(ch,sizeof ch ,fq) != NULL ){
			linArqOper[i] = strdup(ch);
			printf("O indice i=%d e o valor da linha é: %s",i,linArqOper[i]);
			i++;
			numlinha++;
		}
	}

	for(j=0;j<numlinha;j++){
		// Chama a função de controle de arquivos 
		controle_arq(linArqOper[j],j);
		//printf("\n%s", linArqOper[j] );
	}
	

	fclose(fp);	
	fclose(fq);
	
	return 0;

}
