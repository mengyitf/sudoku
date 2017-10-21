#include "generator.h"

FILE* file = fopen("sudoku.txt","w+");
//if(file==NULL)exit(1);
int sudoku[9][9] = {
	{1,2,3, 4,5,6, 7,8,9},
	{4,5,6, 7,8,9, 1,2,3},
	{7,8,9, 1,2,3, 4,5,6},

	{2,3,1, 5,6,4, 8,9,7},
	{5,6,4, 8,9,7, 2,3,1},
	{8,9,7, 2,3,1, 5,6,4},

	{3,1,2, 6,4,5, 9,7,8},
	{6,4,5, 9,7,8, 3,1,2},
	{9,7,8, 3,1,2, 6,4,5}
};

void whenPutChar(){
	char *str;
	scanf("%s",&str);
}
int getTimes(int argc,char *argv[]){
	int times;
	if(argc==1){
		printf("Enter the amount of Sudoku you want to generate: ");
		scanf("%d",&times);
	}else if(argc==2){
		printf("This is a wrong format: %s %s\n", argv[0], argv[1]);
		printf("Input format: sudoku [ -c parameter ]\n");
		return -1;
	}else if(argc==3&&strcmp(argv[1],"-c")!=0){
		printf("This is a wrong parameter: %s\n",argv[1]);
		printf("Input format: sudoku [ -c parameter ]\n");
		return -1;
	}else{
		times = atoi(argv[2]);
	}
	while (times<1){
		printf("Please enter a value greater than 0: ");
		if(scanf("%d",&times)==0){
			whenPutChar();
		};
	}
	return times;
}
void row_exchange(int i,int u){
	int j,p,t,c,r1,r2;
	r1 = (i-1)/3*3;
	r2 = (i-1)%3*3;
	for (j = 1; j < 3; ++j){
		c = (j+u)%3;
		for (p = 0; p < 9; ++p){
			t = sudoku[r1+j][p];
			sudoku[r1+j][p] = sudoku[r1+c][p];
			sudoku[r1+c][p] = t;
		}
		u = ++u % 3;
		if(u=0)u=1;
		c = (j+u)%3;
		for (p = 0; p < 9; ++p){
			t = sudoku[p][r2+j];
			sudoku[p][r2+j] = sudoku[p][r2+c];
			sudoku[p][r2+c] = t;
		}
	}
}
void value_exchange(int i,int c){
	int j, p;
	for (j = 0; j < 9; ++j){
		for (p = 0; p < 9; ++p){
			if(sudoku[j][p]==i){
				sudoku[j][p] = c;
			}else if(sudoku[j][p]==c){
				sudoku[j][p] = i;
			}
		}
	}
}
void exchange_first(){
	int i = sudoku[0][0];
	int c = 7;		//交换因子
	value_exchange(i, c);
}
void print_into_txt(){
	int i,j;
	for (i = 0; i < 9; ++i){
		for (j = 0; j < 9; ++j){
			if (j == 0) fprintf(file,"%d", sudoku[i][j]);
			else fprintf(file," %d", sudoku[i][j]);
		}
		if (i < 8) fprintf(file,"\n");
	}
}
void col_exchange(){
	int i,j,u,t;
	for (i = 1; i < 9; ++i){
		u = (rand() % 2 + 1) * 3;
		for (j = 0; j < 9; ++j){
			t = sudoku[i][j];
			sudoku[i][j] = sudoku[(i + u) % 9][j];
			sudoku[(i + u) % 9][j] = t;
		}
	}

}
void loop_build(int times){
	int y,k,u,c,i;
	for (y = 0; y < times; ++y){
		k = 511;
		for (i = 1; i < 10; ){
			u = rand() % 2 + 1;		//位置交换
			c = rand() % 9 + 1;		//交换因子
			if((k>>(c-1))%2>0){
				value_exchange(i, c);
				row_exchange(i, u);
				k = k - (1<<(c-1));
				++i;
			}
		}
		// col_exchange();
		exchange_first();
		if (y > 0) fprintf(file,"\n\n");
		print_into_txt();
	}
	printf("%d random Sudoku numbers have been generated in the file \"sudoku.txt\"\n", times);
	fclose(file);
}
