#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//============================================================================
void enterMatrixParametrs( const char* nameMatrix, int& rows, int& columns )
{
	do
	{
		cout << "Введите размеры " << nameMatrix << " матрицы" << endl;
		cin >> rows >> columns;
	} while ( rows < 0 || columns < 0 );
}

//=============================================================================
int** createZeroMatrix( int rows, int columns )
{
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[columns];
		for ( int j = 0; j < columns; j++ )
			matrix[i][j] = 0;
	}
	return matrix;
}

//=============================================================================
void showMatrix( const char* title, int** matrix, int rows, int columns)
{
	cout << endl << title << endl << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

//=============================================================================
int** fillOriginalMatrix( const char* title, int rows, int columns, int indikatorFillMatrix )
{
	int** matrix = createZeroMatrix( rows, columns );
	
	//случай 1 - вручную, иначе (случай 2) - случайным образом
	if (indikatorFillMatrix == 1)
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				cin >> matrix[i][j];
	}
	else
	{
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
				matrix[i][j] = rand() % 10;
	}

	showMatrix( title, matrix, rows, columns );

	return matrix;
}

//=============================================================================
void wayFillMatrix( int &indikatorFillMatrix )
{
	do
	{
		cout << "Выберите способ заполнения матриц\n" <<
			"1 - Вручную \n2 - Случайным образом\n";
		cin >> indikatorFillMatrix;
	} while ( indikatorFillMatrix < 1 || indikatorFillMatrix > 2 );
}

//=============================================================================
int getExtMatrixSize( int rows1, int rows2, int columns1, int columns2 )
{
	int dimention = 2;
	while ( dimention < rows1 || dimention < rows2 || dimention < columns1 || dimention < columns2 )
		dimention *= 2;
	return dimention;
}

//=============================================================================
int** getNeedMatrixInSize( int needDimentionMatrix, int rows, int columns, int** originMatrix, const char* title )
{
	int** matrixNeed = createZeroMatrix( needDimentionMatrix, needDimentionMatrix );
	for ( int i = 0; i < rows; i++ )
	{
		for ( int j = 0; j < columns; j++ )
			matrixNeed[i][j] = originMatrix[i][j];
	}

	showMatrix( title, matrixNeed, needDimentionMatrix, needDimentionMatrix );
	return matrixNeed;
}

//=============================================================================
int** getSubMatrix( int** matrix, int shiftRows, int shiftColumns, int dimentionRows, int dimentionColumns )
{
	int** subMatrix = createZeroMatrix( dimentionRows, dimentionColumns );
	for ( int i = 0; i < dimentionRows ; i++ )
	{
		for ( int j = 0; j < dimentionColumns ; j++ )
			subMatrix[i][j] = matrix[i + shiftRows][j + shiftColumns];
	}

	return subMatrix;
}

//=============================================================================
void resultMatrix( int** rezultMatrix, int dimention )
{
	int rowsEnd = 100, columnsEnd = 100;
	for ( int i = 0; i < dimention; i++ )
	{
		int x = 0;
		for ( int j = 0; j < dimention; j++ )
		{
			if ( rezultMatrix[i][j] != 0 )
			{
				x++;
				rowsEnd = 100;
				columnsEnd = 100;
			}
		}
		if ( x == 0 && i < rowsEnd )
		{
			rowsEnd = i;
			columnsEnd = i;
		}
	}

	int** viewRezultMatrix = getSubMatrix( rezultMatrix, 0, 0, rowsEnd, columnsEnd );
	showMatrix( "Результирующая матрица", viewRezultMatrix, rowsEnd, columnsEnd );
	
}

//=============================================================================
void deleteMatrix( int** matrix, int dimention )
{
	for (int i = 0; i < dimention; i++)
		delete[] matrix[i];
}


//=============================================================================
int main()
{
	srand( time( NULL ) );

	int rows1, columns1, rows2, columns2, indikatorFillMatrix;
	system( "chcp 1251" );
	cout << "Вас приветствует программа" << endl << "быстрого перемножения матриц методом Штрассена\n\n";

	enterMatrixParametrs ( "первой", rows1, columns1 );
	enterMatrixParametrs( "второй", rows2, columns2 );
	
	wayFillMatrix( indikatorFillMatrix );
	
	int** originalMatrix1 = fillOriginalMatrix( "Матрица 1", rows1, columns1, indikatorFillMatrix );
	int** originalMatrix2 = fillOriginalMatrix( "Матрица 2", rows2, columns2, indikatorFillMatrix );

	const int extMatrixDimention = getExtMatrixSize(rows1, rows2, columns1, columns2);
	const int middleExtMatrixDimention = extMatrixDimention / 2;

	cout << "Приведенные матрицы\n";
	int** extMatrix1 = getNeedMatrixInSize( extMatrixDimention, rows1, columns1, originalMatrix1, "Матрица 1" );
	int** extMatrix2 = getNeedMatrixInSize( extMatrixDimention, rows2, columns2, originalMatrix2, "Матрица 2" );

	//Разбиение матриц на подматрицы и их заполнение
	int** matrix1Submat1 = getSubMatrix( extMatrix1, 0, 0, middleExtMatrixDimention, middleExtMatrixDimention);
	int** matrix1Submat2 = getSubMatrix( extMatrix1, 0, middleExtMatrixDimention, middleExtMatrixDimention, middleExtMatrixDimention );
	int** matrix1Submat3 = getSubMatrix( extMatrix1, middleExtMatrixDimention, 0, middleExtMatrixDimention, middleExtMatrixDimention );
	int** matrix1Submat4 = getSubMatrix( extMatrix1, middleExtMatrixDimention, middleExtMatrixDimention, middleExtMatrixDimention, middleExtMatrixDimention );

	int** matrix2Submat1 = getSubMatrix( extMatrix2, 0, 0, middleExtMatrixDimention, middleExtMatrixDimention );
	int** matrix2Submat2 = getSubMatrix( extMatrix2, 0, middleExtMatrixDimention, middleExtMatrixDimention, middleExtMatrixDimention );
	int** matrix2Submat3 = getSubMatrix( extMatrix2, middleExtMatrixDimention, 0, middleExtMatrixDimention, middleExtMatrixDimention );
	int** matrix2Submat4 = getSubMatrix( extMatrix2, middleExtMatrixDimention, middleExtMatrixDimention, middleExtMatrixDimention, middleExtMatrixDimention );

	//Создание промежуточных матриц
	int** p1 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );
	int** p2 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );
	int** p3 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );
	int** p4 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );
	int** p5 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );
	int** p6 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );
	int** p7 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );
	
	//Вычисление значений промежуточных матриц
	for ( int i = 0; i <  middleExtMatrixDimention; i++ )
	{
		for ( int j = 0; j < middleExtMatrixDimention; j++ )
		{

			for ( int z = 0; z < middleExtMatrixDimention; z++ ) 
			{

				p1[i][j] += ( matrix1Submat1[i][z] + matrix1Submat4[i][z] ) * ( matrix2Submat1[z][j] + matrix2Submat4[z][j] );
				p2[i][j] += ( matrix1Submat3[i][z] + matrix1Submat4[i][z] ) * matrix2Submat1[z][j];
				p3[i][j] += matrix1Submat1[i][z] * (matrix2Submat2[z][j] - matrix2Submat4[z][j]);
				p4[i][j] += matrix1Submat4[i][z] * (matrix2Submat3[z][j] - matrix2Submat1[z][j]);
				p5[i][j] += ( matrix1Submat1[i][z] + matrix1Submat2[i][z] ) * matrix2Submat4[z][j];
				p6[i][j] += ( matrix1Submat3[i][z] - matrix1Submat1[i][z] ) * ( matrix2Submat1[z][j] + matrix2Submat2[z][j] );
				p7[i][j] += ( matrix1Submat2[i][z] - matrix1Submat4[i][z] ) * ( matrix2Submat3[z][j] + matrix2Submat4[z][j] );
			}
		}
	}
	
	//dopMat1
	//Создание вспомогательных матриц
	int** dopMatrix1 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );
	int** dopMatrix2 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );
	int** dopMatrix3 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );
	int** dopMatrix4 = createZeroMatrix( middleExtMatrixDimention, middleExtMatrixDimention );

	//Подсчет значений вспомогательных матриц из промежуточных
	for ( int i = 0; i < middleExtMatrixDimention; i++ )
	{
		for ( int j = 0; j < middleExtMatrixDimention; j++ )
		{
			dopMatrix1[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
			dopMatrix2[i][j] = p3[i][j] + p5[i][j];
			dopMatrix3[i][j] = p2[i][j] + p4[i][j];
			dopMatrix4[i][j] = p1[i][j] - p2[i][j] + p3[i][j] + p6[i][j];
		}
	}

	//Создание результирующей матрицы
	int** rezultMatrix = createZeroMatrix(extMatrixDimention, extMatrixDimention);

	//Занесение информации из вспомогательных матриц в результирующую
	for ( int i = 0; i < middleExtMatrixDimention; i++ )
	{
		for ( int j = 0; j < middleExtMatrixDimention; j++ )
		{
			rezultMatrix[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
			rezultMatrix[i][j + middleExtMatrixDimention] = dopMatrix2[i][j];
			rezultMatrix[i + middleExtMatrixDimention][j] = dopMatrix3[i][j];
			rezultMatrix[i + middleExtMatrixDimention][j + middleExtMatrixDimention] = dopMatrix4[i][j];
		}
	}

	resultMatrix( rezultMatrix, extMatrixDimention );

	system("pause");

	//Очистка динамической памяти

	deleteMatrix( originalMatrix1, rows1 );
	deleteMatrix( originalMatrix2, rows2 );
	deleteMatrix( extMatrix1, extMatrixDimention );
	deleteMatrix( extMatrix2, extMatrixDimention );
	deleteMatrix( rezultMatrix, extMatrixDimention );
	
	deleteMatrix( matrix1Submat1, middleExtMatrixDimention );
	deleteMatrix( matrix1Submat2, middleExtMatrixDimention );
	deleteMatrix( matrix1Submat3, middleExtMatrixDimention );
	deleteMatrix( matrix1Submat4, middleExtMatrixDimention );
	deleteMatrix( matrix2Submat1, middleExtMatrixDimention );
	deleteMatrix( matrix2Submat2, middleExtMatrixDimention );
	deleteMatrix( matrix2Submat3, middleExtMatrixDimention);
	deleteMatrix( matrix2Submat4, middleExtMatrixDimention );
	deleteMatrix( dopMatrix1, middleExtMatrixDimention );
	deleteMatrix( dopMatrix2, middleExtMatrixDimention );
	deleteMatrix( dopMatrix3, middleExtMatrixDimention );
	deleteMatrix( dopMatrix4, middleExtMatrixDimention );
	deleteMatrix( p1, middleExtMatrixDimention );
	deleteMatrix( p2, middleExtMatrixDimention );
	deleteMatrix( p3, middleExtMatrixDimention );
	deleteMatrix( p4, middleExtMatrixDimention );
	deleteMatrix( p5, middleExtMatrixDimention );
	deleteMatrix( p6, middleExtMatrixDimention );
	deleteMatrix( p7, middleExtMatrixDimention );

	delete[] originalMatrix1, originalMatrix2, extMatrix1, extMatrix2, rezultMatrix;
	delete[] matrix1Submat1, matrix1Submat2, matrix1Submat3, matrix1Submat4, matrix2Submat1, matrix2Submat2, matrix2Submat3, matrix2Submat4, dopMatrix1, dopMatrix2, dopMatrix3, dopMatrix4;
	delete[] p1, p2, p3, p4, p5, p6, p7;
}
