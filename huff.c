#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define MIN 0
#define MAX 255


typedef struct nodeHeap nodeHeap;
struct nodeHeap
{
	unsigned int frequency;
	char code;
};


void FrequencyCounter(char *input_file){

	FILE *file;
	char c;
	nodeHeap table[256];
	int i = 0;


	file = fopen("input_file", "r");
	if(file == NULL){
		printf("Error ao ler arquivo!\n");
		exit(1);
	}

	for(i=0; i < 255; i++){
		table[i].frequency = 0;
		table[i].code = (char) i;
	}

	while(!feof(file)){
		fscanf(file,"%c",&c);
		printf("%c\n", c );
		i = (int) c;
		table[i].frequency++;
	}

	fclose(file);
}

void CompressFile(char *name_input, char *name_output){
	
	FrequencyCounter(name_input);

}



int main(){
    char name[60], name2[60];
    printf("Digite o nome de arquivo de entrada e o de saida: ");
    scanf("%s %s", name, name2);
    CompressFile(name, name2);
    
    return 0;
}