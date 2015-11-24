#include "header.h"

void checkNeighbours(int x, int y, int limitX, int limitY, cel **table) {

	int i, j, neighbours = 0;
	int xi, yj;
	for(i = x-1; i <= x+1; i++) {
		for(j = y-1; j <= y+1; j++) {
			xi = i;
			yj = j;
			if(j == y && i == x)
				continue;
			
			if(j < 0)
				yj = limitY - 1;
			
			if(i < 0)
				xi = limitX - 1;
			
			if(j >= limitY)
				yj = 0;
			
			if(i >= limitX)
				xi = 0;
			
			if(table[xi][yj].status == ALIVE)
				neighbours++;
		}
 	}
	
	// 	printf("%d", neighbours);
	table[x][y].neighbours = neighbours;
}

void checkAlive(int x, int y, cel **table) {

	if(table[x][y].status == ALIVE) {

		if(table[x][y].neighbours >= 4 || table[x][y].neighbours < 2) {
			table[x][y].status = DEAD;
		}
	}
	
	else {
		
		if(table[x][y].neighbours == 3) {
			table[x][y].status = ALIVE;
		}
	}
}

void updateTable(int x, int y, cel **table) {
    /*

    fazer um for utilizando x - 1 e y - 1 como valor inicial, e x + 1 e y + 1 como valor máximo.
    exemplo:
    [1,1][2,1][3,1]
    [1,2][2,2][3,2]
    [1,3][2,3][3,3]

    para x e y = 2 (a célula do meio do display acima), testar nas células acima com o método descrito.
    caso x-1/y-1 seja menor q 0, utilizar o valor máximo da tabela.
    caso x+1/y+1 seja maior q o valor máximo da tabela, utilizar 0.
    */
    // testar todas as celulas;
    int i, j;

    for(i = 0; i < x; i++) {
    	for(j = 0; j < y; j++)
    		checkNeighbours(i, j, x, y, table);
    }

    for(i = 0; i < x; i++) {
    	for(j = 0; j < y; j++) {
				
				if(table[i][j].status == ALIVE) {

					if(table[i][j].neighbours >= 4 || table[i][j].neighbours < 2) {
						table[i][j].status = DEAD;
					}
				}
				else {
					if(table[i][j].neighbours == 3)
						table[i][j].status = ALIVE;
				}
    	}
    }
}

void displayTable( int x, int y, cel **table, int neighbours) {

    int i, j;

    printf("    ");
    for(i = 0; i < y; i++) {
        printf(" %02d", i);
    }
    printf(" x");
    printf("\n\n");
    for(i = 0; i < x; i++) {
        printf("%02d  ", i);
        for(j = 0; j < y; j++) {

			if(neighbours == 0)
			    printf(" %c", table[i][j].status);
			else
       	      	printf(" %02d", table[i][j].neighbours);
    	}
        printf("\n");
    }
	printf("y\n");
}

cel **defineTable(int x, int y) {

    int i, j;

  	cel **table;
   	table = (cel **)malloc(y * sizeof(cel));

   	printf("\n");
   	if(table == NULL) {
	    printf("Sem memoria");
    	exit;
   	}

   	for (i = 0; i < y; i++) {
	    table[i] = (cel *)malloc(x * sizeof(cel));
    	if(table[i] == NULL) {
	    	printf("Sem memoria");
	    	exit;
    	}
   	}

   	// inicializar todas as celulas mortas e sem vizinhos.
	for (i = 0; i < x; i++) {
		for(j = 0; j < y; j++) {
			table[i][j].status = DEAD;
   			table[i][j].neighbours = 0;
		}
	}


	return table;
}

void insertCel(int x, int y, cel **table)
{
    int i, j;
    int option = 1;
    while(option == 1) {
    	//printf("\nDeseja adicionar mais alguma celula? (1 - sim/0 - nao): ");
        //scanf("%d", &option)
        printf("\nEscolha uma celula para deixar viva (x y): \n(-1 -1) - para terminar o input!\n-> ");
        scanf("%d %d", &i, &j);
        if(i == -1 && j == -1)
        	//option = 0; // sai do loop
        	return;
        else if (i >= y || j >= x || (i < 0 && i != -1) || (j < 0 && j != -1)) {
            printf("\n\nCoordenada invalida.\n\n");
            option = 1;
            //continue;
        }
        else {
			printf("\n");		

        	table[j][i].status = ALIVE;

        	displayTable(x, y, table, 0);
        }
    }
}


int mainMenu() {

    int i;

    printf("================\nJOGO DA VIDA BY\nBruno Alves\nJaime Faiman\nRodrigo Prado\n================\n\n");
    printf("--Menu--\nNovo Jogo (0)\nCarregar  (1)\nSair      (2)\nSelecione uma opcao: ");
    scanf("%d", &i);

    // save in a txt file
	FILE *file;
    if(i == 1) {
		if(file =  fopen("saveFile.txt", "r"))
			fclose(file);

	else {
		printf("Nenhum save foi encontrado. Deseja criar um novo jogo?\n(1 - sim/0 - nao): ");
		scanf("%d", &i);

		if(i != 0) {
		    return -1;
		}
	}
    }
    return i;
    //printf("Selecione uma opcao: %s", answer);
    //switch(answer)
    //case 1:
}

void saveTable(int x, int y, int currentGen, cel **table) {

	FILE *file;
	int save;
	printf("Deseja salvar essa geracao? (1 - sim/0 - nao): ");
	scanf("%d", &save);

	if(save == 1) {
		file = fopen("saveFile.txt", "w");
		fprintf(file, "%d %d %d \n", x, y, currentGen);
		int i, j;
		for(i = 0; i < x; i++) {
			for(j = 0; j < y; j++) {
				fprintf(file, "%c\n", table[i][j].status);
			}
		}
		fclose(file);
	}
}

cel **loadTable(int *x, int *y, int *currentGen) {

	cel **table;
	FILE *file;
	int i, j;
	file = fopen("saveFile.txt", "r");
	fscanf(file, "%d %d %d\n", x, y, currentGen);
	table = defineTable(*x, *y);

	for(i = 0; i < *x; i++) {
		for(j = 0; j < *y; j++)
			fscanf(file, "%c\n", &table[i][j].status);
	}

	fclose(file);
	return table;

}

void gameMenu(int x, int y, int currentGen, cel **table) {

    int option;

    printf("\n--%da Geracao--\n", currentGen);
    displayTable(x, y, table, 0);                                              
    printf("\nAvancar para a proxima geracao (1)\nInserir Celula                 (2)\nSalvar                         (3)\nSair do jogo                   (4)\nSelecione uma opcao: ");
    scanf("%d", &option);

	switch(option){
		case 1:
			updateTable(x, y, table);
			currentGen++;
			break;
		case 2:
			insertCel(x, y, table);
			break;
		case 3:
			saveTable(x, y, currentGen, table);
			printf("\n\nJogo salvo com sucesso!\n");
			break;
		default:
			printf("\n\nTem certeza que deseja sair do jogo?(1 - sim/0 - nao): ");
			scanf("%d", &option);
			if(option == 1)
				return;

			break;
	}
	// recursively call
	gameMenu(x, y, currentGen, table);
}
