#include <stdio.h>
#include <stdlib.h>
//#include <string>
#include <string.h>
#include <time.h>

#include <iostream>
#include <vector>
#include <algorithm>

#include "listaBits.h"
#include "huffman.h"
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

	PrintTable2(frequency_table);
}

void codifyData(char *input_file, char *output_file, treeVector *treeList){
	FILE *file, *fileOut;
	char c, first_character, buffer[2], aux[8];
	int i = 0, j = 0;
	unsigned int frequency_table[256][256];

	for(i=0; i < 256; i++)
		for(j=0; j < 256; j++)
			frequency_table[i][j] = 0;

	file = fopen(input_file, "r");
	if(file == NULL){
		printf("Error ao ler arquivo!\n");
		exit(1);
	}

	fileOut = fopen(output_file, "w");
	if(fileOut == NULL){
		printf("Error ao ler arquivo!\n");
		exit(1);
	}


	fscanf(file,"%c",&first_character);
	//printf("Primeiro caracter: %c\n", first_character );
	if(c == EOF){
		printf("Nao foi possivel fazer a compactacao. Arquivo muito pequeno.\n");
	}

	buffer[0] = first_character;
	//printf("buffer = [%c][ ]\n", buffer[0] );
	byteToChar((int)first_character, aux);
	//ExibirBits(first_character);
	for(i=0; i< 256 ; i++){
		if (treeList[i].p != NULL ){
			for(j=0; j< ((*(treeList[i].p)).size()) ; j++){
				//if ((*(treeList[i].p))[j] != NULL) {
					if ( (*(treeList[i].p))[j].leaf == true ){
						cout << "contexto= " << (char)i << "valor= " << (*(treeList[i].p))[j].value << "frequencia= " << (*(treeList[i].p))[j].frequency << endl;
						frequency_table[i][(int)(*(treeList[i].p))[j].value] = (*(treeList[i].p))[j].frequency;
					}
				//}
			}
		}	
	}

	for(i=0; i< 256; i++){
		for(j=0; j< 256; j++){
			fwrite(&frequency_table[i][j], sizeof(unsigned int), 1, fileOut);
		}
	}
	
	fwrite(aux, sizeof(char), 8, fileOut);
	while(!feof(file)){
		fscanf(file,"%c", &c);
		buffer[1] = c;
		for(i=0; i< ((*(treeList[(int)buffer[0]].p)).size()) ; i++){
			if ( (*(treeList[(int)buffer[0]].p))[i].leaf == true && 
				(*(treeList[(int)buffer[0]].p))[i].value == c ){
				fwrite(&(*(treeList[buffer[0]].p))[i].code, sizeof(char), strlen((*(treeList[buffer[0]].p))[i].code), fileOut);
			}
		}
		//printf("buffer = [%c][%c]\n", buffer[0], buffer[1] );
		//printf("Contexto [%c][%c] = %d\n",  buffer[0], buffer[1] ,frequency_table[ (int) buffer[0] ][(int) buffer[1]] );
		swapChar(buffer);
	}
	fclose(file);
	fclose(fileOut);
}

void insertionSort(huffTree *array, unsigned int  length){

	for(int i = 1; i < length; i++) {
		huffTree key = array[i]; 
		int j = i - 1;
		while((j >= 0) && (array[j].frequency < key.frequency)) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = key;
	}
}

bool ordenaVector(const NO &a, const NO &b){
	return a.frequency > b.frequency;
}

void printTree(vector<NO>& arvore){

	int qtd_leaf = 0; 
	unsigned int filhoEsquerda = 0;
	unsigned int filhoDireita = 0;
	int i = 0;


	filhoDireita = ((2*i)+1 - (2*qtd_leaf));
	filhoEsquerda = filhoDireita + 1;	



	cout << " No_raiz(valor) "<< arvore[i].value << "| Nó_raiz(freq): "<<arvore[i].frequency<<endl<<endl;
	cout << " FEsquerda(frequency): "<<arvore[filhoEsquerda].frequency << "| FDireita(frequency): "<<arvore[filhoDireita].frequency << endl;
    cout << " filhoEsquerda(code): "<<arvore[filhoEsquerda].code << "| filhoDireita(code): "<<arvore[filhoDireita].code << endl;

	for( i= 1; i< arvore.size();i++){
		if(filhoEsquerda> arvore.size())
			break;
		if( arvore[i].leaf == true){
			qtd_leaf++;	
			continue;
		}
		filhoDireita = ((2*i)+1 - (2*qtd_leaf));
		filhoEsquerda = filhoDireita + 1;
		
		cout << " FEsquerda(frequency): "<<arvore[filhoEsquerda].frequency << "| FDireita(frequency): "<<arvore[filhoDireita].frequency << endl;
    	cout << " filhoEsquerda(code): "<<arvore[filhoEsquerda].code << "| filhoDireita(code): "<<arvore[filhoDireita].code << endl;
    	
	}

}

void codifyTree(vector<NO>& arvore){
	int qtd_leaf = 0; 
	unsigned int filhoEsquerda = 0;
	unsigned int filhoDireita = 0;
	char aux[8];
	int i = 0;
	

	filhoDireita = ((2*i)+1 - (2*qtd_leaf));

	//Codifica os primeiros filhos
	
	strcpy(arvore[filhoDireita].code, "1");
	filhoEsquerda = filhoDireita + 1;
	strcpy(arvore[filhoEsquerda].code, "0");

	// cout << " filhoEsquerda(code): "<<arvore[filhoEsquerda].code << "| filhoDireita(code): "<<arvore[filhoDireita].code << endl;
	
	/*cout << " FE_value: "<< arvore[i].value << "| FE_frequency: "<<arvore[i].frequency<<endl;
	cout << " FE_code: "<<arvore[filhoEsquerda].code << "| FD_code: "<<arvore[filhoDireita].code << endl;*/

	for(i = 1 ; i < arvore.size(); i++){
		if(filhoEsquerda > arvore.size())
			break;
		if( arvore[i].leaf == true){
			qtd_leaf++;
			continue;
		}

		filhoDireita = ((2*i)+1 - (2*qtd_leaf));
		filhoEsquerda = filhoDireita + 1;
		strcpy(aux,arvore[i].code);
		strcat(aux,"0");
		strcpy(arvore[filhoEsquerda].code, aux);

		filhoEsquerda = filhoDireita + 1;
		strcpy(aux,arvore[i].code);
		strcat(aux,"1");

		strcpy(arvore[filhoDireita].code, aux);
		//cout << " FE_value: "<< arvore[i].value << "| FE_frequency: "<<arvore[i].frequency<<endl;
        //cout << " FE_code: "<<arvore[filhoEsquerda].code << "| FD_code: "<<arvore[filhoDireita].code << endl;
	}
}

void removeZero(unsigned int v[], unsigned int length, int cont, huffTree *list){

	int itr = 0;
	if(list == NULL || v == NULL) {
		cout << "Error ao criar a lista!" << endl;
		exit(1);
	}

	for(int i = 0; i < length; i++){
		if(v[i] != 0){
			list[itr].frequency = v[i];
			list[itr].value = (char) i;
			list[itr].leaf = true;
			itr++;
		}
	}

	insertionSort(list, cont);
}

void printVector(vector<NO>& arvore){

	cout << "LISTA INICIAL" << endl;
	for(int i = 0; i < arvore.size() ; i++){
		cout << "" << arvore[i].frequency << " ";
	}
	cout << "------------" << endl;

}

void buildHuffTree(huffTree list[], unsigned int length, vector<NO>& arvore){

	huffTree minRight;
	huffTree minLeft;
	unsigned int limite = length;

	for(int i = 0; i < length ; i++){
		arvore.push_back(list[i]);
	}
	

	/*
	cout << "LISTA INICIAL" << endl;
	for(int i = 0; i < length ; i++){
		cout << "list[" << i <<"].frequency = "  <<arvore[i].frequency << "\tvalue: "<< arvore[i].value << endl;
	}
	cout << "------------" << endl;
	*/
	huffTree new_node;

	while( limite >= 2){
		minRight = arvore[limite-1];
		minLeft  = arvore[limite-2];
		new_node.frequency = minRight.frequency + minLeft.frequency;
		new_node.value = -1;
		new_node.leaf = false;

		arvore.push_back(new_node);
		sort(arvore.begin(), arvore.end(), ordenaVector);
		limite = limite - 1;

		/*for(int i = 0; i < arvore.size() ; i++){
			cout<<", "<<arvore[i].frequency;
		}
		cout << endl;*/
	}
}


void CompressFile(char *name_input, char *name_output){

	unsigned int frequency_table[256][256];
	int list_length;

	// conta as frequencias contextuais do arquivo
	FrequencyCounterContext1(name_input, frequency_table);
	// remove os zeros da lista

	// fazer para todos os contextos
	// criar uma lista de ponteiro[0:255] que aponta para os contextos

	treeVector treeList[256];

	for(int i = 0; i < 256; i++){	
		list_length = countZero(frequency_table[i], 256);
		if (list_length != 0){
			huffTree *list = (huffTree*) malloc(sizeof(huffTree)*list_length);
			removeZero(frequency_table[i], 256, list_length, list);
			// plota a lista apos removido os zeros
			vector<NO> root;			
			buildHuffTree(list, list_length, root);
			codifyTree(root);

			/*
				cout << "i =" << i << endl;
				printVector(root);
			}
			**/
			//cout << "size root["<< i<< "] = " << root.size() << endl;

			treeList[i].p = &root;
			// pegar root atualizadas com os códigos 
			//arvoresContextos.push_back(&root);
			//cout << "Context: " << i << " Root: " << root[i].frequency << endl;
			free(list);

		}
		else{
			treeList[i].p = NULL;	
		}
		
	}
	
	//codifyData(name_input, name_output, treeList);
	//cout << "tamanho " << (*(treeList[122].p))[0].frequency << endl;
	for(int i = 0; i < 256; i++){
		if (treeList[i].p != NULL )
			printTree(*(treeList[i].p));
	}
	/*Imprimindo arvore*/
	//for(int i=0; i < 1; i++){
		//cout << "Karai: " << (*treeList[122].p)[0].frequency << endl;	
	//}
	
	
}


int main(int argc, char *argv[]){

	char name[60], name2[60];

	//if(argc != 4)		Usage();

    strcpy(name, argv[1]);
    strcpy(name2, argv[2]);

    CompressFile(name, name2);

    return 0;
}
