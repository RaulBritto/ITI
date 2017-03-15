#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "huff.h"
#include <iostream>
#include "util.h"


#define MIN 0
#define MAX 255

using namespace std;

struct node {
  unsigned int frequency;
  char value;
  unsigned int code;
  struct node *left, *right;
} ;



void FrequencyCounterContext1(char *input_file, unsigned int frequency_table[][256]){
	FILE *file;
	char c, first_character, buffer[2];
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
}

void insertionSort(huffTree *array, unsigned int  length){

	for(int i = 1; i < length; i++) {
		huffTree key = array[i]; //Pensar aqui
		int j = i - 1;
		while((j >= 0) && (array[j].frequency < key.frequency)) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
}


int removeZero(unsigned int v[], unsigned int length, char context, huffTree* list){


	int cont = 0;
	int itr = 0;
	

	cout << "Contexto " << context << endl;
	for(int i = 0; i < length; i++){
		if(v[i] != 0){
			cont++;
		} 
	}	

	cout << "cont = " << cont << endl;

	//huffTree list[cont];
	list = (huffTree*) malloc(sizeof(huffTree)*cont);

	if(list == NULL) {
		cout << "Error ao criar a lista!" << endl;
		exit(1);
	}


	for(int i = 0; i < length; i++){
		if(v[i] != 0){
			list[itr].frequency = v[i];
			list[itr].value = (char)i;
			list[itr].code = 0;
			list[itr].left = NULL;
			list[itr].right = NULL;
			cout << "list[" <<itr <<"].frequency = "  <<list[itr].frequency ;
			cout << "\tlist[" <<itr <<"].value = " <<list[itr].value << endl;
			itr++;
		}
	}

	insertionSort(list, cont);
	cout << "Depois de ordenado!"<<endl;
	for(int i = 0; i <cont ; i++){
		cout << "list[" <<i <<"].frequency = "  <<list[i].frequency ;
		cout << "\tlist[" <<i <<"].value = " <<list[i].value << endl;
	}
	
	return cont;
}


void CompressFile(char *name_input, char *name_output){

	unsigned int frequency_table[256][256];
	huffTree *list;
	int list_length;

	FrequencyCounterContext1(name_input, frequency_table);
	list_length = removeZero(frequency_table[122], 256, 122, list );


	//PrintTable2(frequency_table);


}



int main(int argc, char *argv[]){

	char name[60], name2[60];

	//if(argc != 4)		Usage();
	
    strcpy(name, argv[1]);
    strcpy(name2, argv[2]);
    
    CompressFile(name, name2);
    
    return 0;
}