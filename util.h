
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

// auxiliar do remove zero
int countZero(unsigned int v[], unsigned int length){

	int cont = 0;
	
	//cout << "Contexto " << context << endl;
	for(int i = 0; i < length; i++){
		if(v[i] != 0){
			cont++;
		} 
	}	

	return cont;
}