#include <stdlib.h>
#include <stdio.h>
// #include <pthread.h>

/*
Variaveis globais
*/
int sudoku[9][9];
// int sudoku[9][9] = {{0, 0, 0, 0, 0, 0, 0, 9, 0},
//                       {1, 9, 0, 4, 7, 0, 6, 0, 8},
//                       {0, 5, 2, 8, 1, 9, 4, 0, 7},
//                       {2, 0, 0, 0, 4, 8, 0, 0, 0},
//                       {0, 0, 9, 0, 0, 0, 5, 0, 0},
//                       {0, 0, 0, 7, 5, 0, 0, 0, 9},
//                       {9, 0, 7, 3, 6, 4, 1, 8, 0},
//                       {5, 0, 6, 0, 8, 1, 0, 7, 4},
//                       {0, 8, 0, 0, 0, 0, 0, 0, 0}};;


/*
Verifica se o numero pode estar na linha especificada
*/
int checkRow(int row, int num){
	int i;
	for (i = 0; i < 9; ++i)
	{
		if (sudoku[row][i] == num)
			return 0;
	}
	return 1;
};


/*
Verifica se o numero pode estar na coluna especificada
*/
int checkCol(int col, int num){
	int i;
	for (i = 0; i < 9; ++i)
	{
		if (sudoku[i][col] == num)
			return 0;
	}
	return 1;
};

/*
	Verifica se o numero pode estar quadrado em que o elemento esta.
*/
int checkSquare(int row, int col, int num){
	//Pega o valo da coluna e da liha do primeiro elemento do quadrado 
	int rowStart = (row/3)*3;
	int colStart = (col/3)*3;
	int i;
	for (i = 0; i < 9; ++i)
	{
		if (sudoku[rowStart + (i%3)][colStart + (i/3)] == num)
			return 0;
	}
	return 1;
};


/*
	Verifica se e possivel colocar o numero em questao na posicao
*/
int checkNumber(int row, int col, int num){
	if (sudoku[row][col] != 0)
	{
		return 0;
	}
	int t1 = checkSquare(row,col,num);
	int t2 = checkCol(col,num);
	int t3 = checkRow(row,num);
	
	if (t1&&t2&&t3)
	{
		return 1;
	}
	return 0;
};

/*
	Coloca o numero se possivel
*/
int putNumber(){
	return 1;
}


int printSudoku(){
	int i,j;
	for (i = 0; i < 9; ++i)
	{
		
		if( i%3 == 0){
			printf("------------------------------\n");
		}		
		
		for (j = 0; j < 9; ++j)
		{
			if(j%3 == 0)
				printf("|");
			if (sudoku[i][j] == 0)
			{
				printf("   ", sudoku[i][j] );
			}
			else{		
				printf(" %d ", sudoku[i][j] );
			}
			
		}
		printf("\n");
	}
	printf("------------------------------\n");

};



int solveSudoku(int row, int col)
{
    if(row<9 && col<9)
    {
    	//Se a posicao que estamos checando ja tiver um valor vamos para a proxima
        if(sudoku[row][col] != 0)
        {
        	//se tiver uma posicao a direita vamos verificar ela
            if((col+1)<9) return solveSudoku(row, col+1);
            //se tiver nao tiver uma posicao a direita vai para a primeira posicao da linha de baixo
            else if((row+1)<9) return solveSudoku(row+1, 0);
            //se nao tiver mais o que checar acabou o sudoku
            else return 1;
        }
        //se a posicao estiver vazia(valor na posicao = 0) vamos tentar colocar algum numero nela;
        else
        {
        	int i;
        	//Tentndo colocar os numeros de 1 a 9 na posicao
            for(i=0; i<9; ++i)
            {
            	//Ve se o numero pode estar naquela posicao
                if(checkNumber(row, col, i+1))
                {
                	//se pode ele coloca o numero na posicao
                    sudoku[row][col] = i+1;
                    //continua resolvendo para a proxima posicao
                    //se tiver uma posicao a direita, vai recursivamente analisar a proxima posicao
                    if((col+1)<9)
                    {
                    	//se nao conseguir resolver o sudoku, remove o numero que tentamos colocar (valor na posicao volta a ser 0)
                        if(solveSudoku(row, col +1)) return 1;
                        else sudoku[row][col] = 0;
                    }
                    else if((row+1)<9)
                    {
                    	//se nao conseguir resolver o sudoku, remove o numero que tentamos colocar (valor na posicao volta a ser 0)
                        if(solveSudoku(row+1, 0)) return 1;
                        else sudoku[row][col] = 0;
                    }
                    //Resolvido o sudku
                    else return 1;
                }
            }
        //Falha caso tenha tentado colocar todos os numeros de 1-9 mas nenhum de certo,
        //voltando para o for da posicao chamada antes dessa, alterando o valor dela e assim por diante
        return 0;
    	}
    }
    //Varreu tudo e nao deu problema :D
    else return 1;
}

int main(int argc, char const *argv[])
{
	int i,j;
	int mat[9][9];
	if(argc > 1){
		printf("%s\n",argv[1]);
		for (i = 0; i < 9; ++i)
		{
			for (j = 0; j < 9; ++j)
			{
				mat[i][j] = (int)(argv[1][9*i + j]) - '0';
				sudoku[i][j] = (int)((argv[1][9*i + j]) - '0');
			}
		}
	}
	printSudoku();
	if(solveSudoku(0,0))
		printSudoku();
	else{
		printf("Impossivel resolver o sudoku\n");
	}

	return 0;
}