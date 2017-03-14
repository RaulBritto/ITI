#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define MIN 0
#define MAX 255



void Usage(){
	printf("Usage: ./ Input_File Output_file \n");
	exit(1);
}

void printTable(unsigned int p[256])
{
	int i = 0;
	
	for(i = 0; i < 256; i++)
	{
		if(p[i] == 0) continue;
		printf("indice array: %d => code: (%c) freq: %d\n", i, (char) i , p[i]);
	}
}

void PrintTable2(unsigned int  t[256][256]){
	int i, j, cont = 0;

	printf("Imprimindo tabela de contexto:\n");
	for(i=0; i < 256; i++)
		for(j=0; j < 256; j++){
			if(t[i][j] == 0) continue;
			cont++;
			printf("Contexto [%c][%c] = %d\n",(char) i, (char) j, t[i][j] );
		}
	printf("Numero de contexto encontrados: %d\n", cont );
}

void swapChar(char c[2]){
	char aux;

	aux = c[0];
	c[0] = c[1];
	c[1] = aux;

}

void FrequencyCounterContext1(char *input_file){
	FILE *file;
	char c, first_character, buffer[2];
	unsigned int frequency_table[256][256];
	int i = 0, j = 0;

	file = fopen(input_file, "r");
	if(file == NULL){
		printf("Error ao ler arquivo!\n");
		exit(1);
	}


	for(i=0; i < 256; i++)
		for(j=0; j < 256; j++)
			frequency_table[i][j] = 0;	
	
	
	fscanf(file,"%c",&first_character);	
	//printf("Primeiro caracter: %c\n", first_character );
	if(c == EOF){
		printf("Nao foi possivel fazer a compactacao. Arquivo muito pequeno.\n");
	}


	buffer[0] = first_character;
	//printf("buffer = [%c][ ]\n", buffer[0] );


	while(!feof(file)){

		fscanf(file,"%c", &c);	
		buffer[1] = c;
		//printf("buffer = [%c][%c]\n", buffer[0], buffer[1] );
		frequency_table[ (int) buffer[0] ][(int) buffer[1]]++;
		//printf("Contexto [%c][%c] = %d\n",  buffer[0], buffer[1] ,frequency_table[ (int) buffer[0] ][(int) buffer[1]] );
		swapChar(buffer);
	}	

	PrintTable2(frequency_table);
}



void FrequencyCounter(char *input_file){

	FILE *file;
	char c;
	unsigned int frequency_table[256];
	int i = 0;


	file = fopen(input_file, "r");
	if(file == NULL){
		printf("Error ao ler arquivo!\n");
		exit(1);
	}

	for(i=0; i < 255; i++){
		frequency_table[i] = 0;
	}

	while(!feof(file)){
		fscanf(file,"%c",&c);
		//printf("%c\n", c );
		i = (int) c;
		frequency_table[i]++;
	}

	printTable(frequency_table);

	fclose(file);
}

void CompressFile(char *name_input, char *name_output){
	
	FrequencyCounterContext1(name_input);

}



int main(int argc, char *argv[]){

	char name[60], name2[60];

	//if(argc != 4)		Usage();
	
    strcpy(name, argv[1]);
    strcpy(name2, argv[2]);
    
    CompressFile(name, name2);
    
    return 0;
}