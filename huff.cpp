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


void removeZero(unsigned int v[], unsigned int length, char context, int cont, huffTree* list){

	
	//cout << "cont = " << cont << endl;
	int itr = 0;
	//huffTree list[cont];
	//list = (huffTree*) malloc(sizeof(huffTree)*cont);

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
	//		cout << "list[" <<itr <<"].frequency = "  <<list[itr].frequency ;
	//		cout << "\tlist[" <<itr <<"].value = " <<list[itr].value << endl;
			itr++;
		}
	}

	insertionSort(list, cont);
	//cout << "Depois de ordenado!"<<endl;
	//for(int i = 0; i <cont ; i++){
	//	cout << "list[" << i <<"].frequency = "  <<list[i].frequency << "\tvalue: "<< list[i].value << endl;	
	//}
	
	//return cont;
}

huffTree* buildHuffTree(huffTree list[], unsigned int length){

	huffTree *root;
	huffTree *min1;
	huffTree *min2;

	huffTree* new_node = (huffTree*) malloc(sizeof(huffTree));

	for(int i = 0; i < length ; i++){
		cout << "list[" << i <<"].frequency = "  <<list[i].frequency << "\tvalue: "<< list[i].value << endl;	
	}

	while( length >= 2)
	{
		min1 = &list[length-1];
		min2 = &list[length-2];
		
		cout << "length " << length << endl;
		cout << "min1 " << min1->frequency << endl;
		cout << "min2 " << min2->frequency << endl;	
		
		new_node->frequency = min1->frequency + min2->frequency;
		new_node->value = -1;
		new_node->code = 0;
		new_node->right = min1;
		new_node->left = min2;

		length = length - 1;
		
		// * é conteudo, não * é endereço
		list[length-1] = *new_node;
		insertionSort(list, length);
	}
	// & é o endereço
	root = &list[0];
	cout << "ultimo: " << root->frequency << endl;

	return root;

}

void printTree(huffTree * root){

	cout << "Print Tree" << endl;

	if(root == NULL) 
		return;

	if(root != NULL){
		printTree (root->left);
		cout << " Freq: " << root->frequency << endl;
		printTree(root->right);
	}

}

void CompressFile(char *name_input, char *name_output){

	unsigned int frequency_table[256][256];
	int list_length;

	// conta as frequencias contextuais do arquivo
	FrequencyCounterContext1(name_input, frequency_table);
	// remove os zeros da lista
	list_length = countZero(frequency_table[122], 256);
	huffTree *list = (huffTree*) malloc(sizeof(huffTree)*list_length);
	removeZero(frequency_table[122], 256, 122, list_length, list );
	// plota a lista apos removido os zeros
	//cout << "-------- Saida -----"<<endl;
	//for(int i = 0; i < list_length ; i++){
	//	cout << "list[" <<i <<"].frequency = "  <<list[i].frequency << "\tvalue: "<< list[i].value << endl;	
	//}
	// construindo a arvore
	huffTree *root;
	root = buildHuffTree(list, list_length);
	//printTree(root);
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