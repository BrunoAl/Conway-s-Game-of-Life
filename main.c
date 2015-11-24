#include "header.h"

int main()
{
    int menuOption = mainMenu();
    int x, y, currentGen = 1;
	
    cel **table;
    
    switch(menuOption) {

        case 0:
		    printf("\n\n--Novo Jogo--\n\n");
            printf("Tamanho do mundo (x y): ");
            scanf("%d %d", &x, &y);

	    	table = defineTable(x, y);

            displayTable(x, y, table, 0);
			insertCel(x, y, table);
            break;
				
        case 1:
			table = loadTable(&x, &y, &currentGen);
	    	displayTable(x, y, table, 0);
            break;
				
        default:
			printf("\n\nFechando o Jogo...\n\n");
        	return 0;
	}

	
    gameMenu(x, y, currentGen, table);
	
    printf("\n\nFechando o Jogo...\n\n");
	
	
    return 0;
}
