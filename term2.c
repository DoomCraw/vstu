#define MAX_NUMBER 1000
#define MIN_NUMBER -1000

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

//получить случайное число
int GetRandNumber ();
//заполинть массив случайными числами
void FillArrayRandNums (int h, int v, int arr[h][v]);
//вывести массив на печать
void PrintArray(int h, int v, int arr[h][v], char arrName[16]);
//вывести содержимое файла на печать
void PrintFileContent (char fileName[]);
//получить сумму отрицательных чисел над главной диагональю
int GetMinusNumsUpponMainDiagonal (int h, int v, int arr[h][v]);
//получить колличество нулей из указанной строки
int GetZeroNumsCountInRow (int h, int v, int arr[h][v], int rowNum);
//получить колличество нулей из указанного столбца
int GetZeroNumsCountInCol (int h, int v, int arr[h][v], int colNum);
//создать файл заполненный случайными числами
void CreateFileRandomNums (char filName[], int elementCount);
//вывести положительные и отрицательные числа в разные файлы из файла источника
void WriteMinusPlusElements (char sourceFileName[],char minusFileName[], char plusFileName[]); 
//функция меню : введена буква a или b
int CtlSymbolAorB (void);
//функция меню : введена буква c или d
int CtlSymbolCorD (void);
//функция меню : введена буква e
int CtlSymbolE (void);

int main (int argc, char *argv[]) {
				char *locale = setlocale(LC_ALL, "");
				char ctrlChar;

				//сброс рандомайзера
				srand (time(NULL));
				//напечатать меню
				printf ("%s\n","Введите один из управляющих символов : ");
				printf ("%s\n","a или b - будут созданны 2 массива указанной размерности и выведены суммы отрицательных элементов над главной диагональю массивов : ");
				printf ("%s\n","c или d - будет создан массив указанной размерности и выведено количество нулевых элементов в 4 строке и 5 столбце: ");
				printf ("%s\n\n","e - будет создан файл со случайными числами, отрицательные числа переписаны в один файл, положительные в другой : ");
				
				ctrlChar = tolower(getchar());
				if (ctrlChar == 'a' || ctrlChar == 'b')
					CtlSymbolAorB();					
				else if (ctrlChar == 'c' || ctrlChar == 'd')
					CtlSymbolCorD();					
				else if (ctrlChar == 'e')
					CtlSymbolE();					
				else
					printf ("Ошибка : %s\n","указанный символ отсутствует в списке разрешенных");
				return 0;
}
//получить случайное число
int GetRandNumber () {
				int rndNumber = 0;

				rndNumber = (rand() % MAX_NUMBER) - (rand () % MAX_NUMBER);

				if (rndNumber > MAX_NUMBER)
								rndNumber = MAX_NUMBER;
				else if (rndNumber < MIN_NUMBER)
								rndNumber = MIN_NUMBER;
//генерировать больше нулей
				if (rndNumber < -150)
								rndNumber = 0;

				return rndNumber;
}
//заполинть массив случайными числами
void FillArrayRandNums (int h, int v, int arr[h][v]) {
				for (int i = 0; i <= h ; i++) {
								for (int j = 0; j <= v; j++) {
												arr[i][j] = GetRandNumber();  
								}
				}
}
//вывести массив на печать
void PrintArray(int h, int v, int arr[h][v],char arrName[16] ) {
				printf ("%s : \n",arrName);
				for (int i = 0; i <= h; i++) {
								for (int j = 0; j <= v; j++) {
												printf ("%4d|",arr[i][j]);
								}
								printf ("\n");
				}
}
//вывести содержимое файла на печать
void PrintFileContent (char fileName[]) {
				FILE *fileHandler;
				int number;
				int count = 0;

				fileHandler = fopen (fileName,"r");

				printf ("\n\nВывод файла : %s\n\n",fileName);
				while (fscanf (fileHandler,"%d",&number) != EOF) {
								printf ("%6d|",number);
								count = count + 4;
								if (count == 24) {
												printf ("\n");
												count = 0;
								}
				}
				printf ("\n");
				fclose (fileHandler);
}
//получить сумму отрицательных чисел над главной диагональю
int GetMinusNumsUpponMainDiagonal (int h, int v, int arr[h][v]) {
				int summ = 0;
				for (int i = 0; i < h; i++) 
								if (arr[i][i+1] < 0)
												summ += arr[i][i+1];
				return summ;
}
//получить колличество нулей из указанной строки
int GetZeroNumsCountInRow (int h, int v, int arr[h][v], int rowNum) {
				int count = 0;
				int i;

				rowNum--;
				for (i = 0; i <= v; i++)
								if (arr [rowNum][i] == 0)
												count++;
				return count;
}
//получить колличество нулей из указанного столбца
int GetZeroNumsCountInCol (int h, int v, int arr[h][v], int colNum) {
 				int count = 0;
				int i; 

				colNum--;
 				for (i = 0; i <= h; i++)
 								if (arr [i][colNum] == 0)
 												count++;
 				return count;
}
//создать файл заполненный случайными числами
void CreateFileRandomNums (char fileName[], int elemnentCount) {
				//указатель на файл
				FILE *fileHandler;

				//открываем файл на запись
				fileHandler = fopen(fileName,"w");
				
				//пишем в файл случайные числа в нужном колличестве
				for (int i = 0;i < elemnentCount;i++) {
								fprintf (fileHandler,"%d\n",GetRandNumber());
				}

				//закрываем файл
				fclose(fileHandler);
 }
//вывести положительные и отрицательные числа в разные файлы из файла источника
void WriteMinusPlusElements (char sourceFileName[],char negativeFileName[], char positiveFileName[]) { 

				FILE *sourceFileHandler, *negativeFileHandler, *positiveFileHandler;
				int number;

				sourceFileHandler		= fopen (sourceFileName,"r");
				negativeFileHandler = fopen (negativeFileName,"w");
				positiveFileHandler = fopen (positiveFileName,"w");

				while (fscanf (sourceFileHandler,"%d",&number) != EOF) {
								if (number < 0)
												fprintf (negativeFileHandler,"%d\n",number);
								else if (number > 0)
												fprintf (positiveFileHandler,"%d\n",number);
				}
				fclose (sourceFileHandler);
				fclose (negativeFileHandler);
				fclose (positiveFileHandler);
}
//функция меню : введена буква a или b
int CtlSymbolAorB () {
				int S1,S2,S3;
				int N1,N2;
//ввести размерности массивов
				printf ("Введите размерность массива R :");
				scanf ("%d",&N1);
				printf ("Введите размерность массива Q :");
				scanf ("%d",&N2);
//обьявить массивы
				int R[N1][N1];
				int Q[N2][N2];
//заполнить массивы случайными значениями
				FillArrayRandNums(N1,N1,R);
				FillArrayRandNums(N2,N2,Q);
//вычислить суммы элементов массивов над главной диагональю
				S2 = GetMinusNumsUpponMainDiagonal(N1,N1,R);
				S3 = GetMinusNumsUpponMainDiagonal(N2,N2,Q);
				S1 = S2 + S3;
//вывести массивы и результаты вычислениий на экран 
				PrintArray(N1,N1,R,"R");
				printf ("\n\n");
				PrintArray(N2,N2,Q,"Q");
				printf ("\n\n");
				printf ("Сумма отрицательных элементов над главной диагональю массива R:\n");
				printf("S2 = %d\n",S2);
				printf ("Сумма отрицательныx элементов над главной диагональю массива Q:\n");
				printf("S3 = %d\n",S3);
				printf ("Сумма S2 + S3:\n");
				printf("S1 = %d\n",S1);

				return 0;
}
//функция меню : введена буква c или d
int CtlSymbolCorD () {
				int N,rowZeroCount,colZeroCount;

				printf ("Введите размерность матрицы R :");
				scanf ("%d",&N);

				if (N < 4) { 
								printf ("Ошибка : Размерность матрицы должна быть не менее 4х\n");
								return 1;
				}

				int R[N][N];
				FillArrayRandNums(N,N,R);
				PrintArray (N,N,R,"R");
				rowZeroCount = GetZeroNumsCountInRow (N,N,R,4);
				colZeroCount = GetZeroNumsCountInCol (N,N,R,5);

				printf ("Колличество нулей в 4ой строке  : %6d\n",rowZeroCount);
				printf ("Колличество нулей в 5ом столбце : %6d\n",colZeroCount);

				return 0;
}
//функция меню : введена буква e
int CtlSymbolE () {
				CreateFileRandomNums ("./fileRndNums.txt",100);
				WriteMinusPlusElements("./fileRndNums.txt","negativeNums.txt","positiveNums.txt");
				PrintFileContent ("./fileRndNums.txt");
				PrintFileContent ("./negativeNums.txt");
				PrintFileContent ("./positiveNums.txt");
				return 0;
}
