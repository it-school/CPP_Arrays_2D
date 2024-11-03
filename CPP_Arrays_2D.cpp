#include <iostream>
#include <iomanip>

using namespace std;

static void example1() {
	const int ROWS = 10;
	const int COLS = 10;
	const int RANGE = 10;

	// Объявляем массив ROWSxCOLS (10x10) и заполняем его нулями
	int product[ROWS][COLS] = { 0 };

	// Создаем таблицу умножения
	for (int row = 0; row < ROWS; ++row)
		for (int column = 0; column < COLS; ++column)
			product[row][column] = row * column;

	// Выводим таблицу умножения без первой строки и первого столбца с нулями
	for (int row = 1; row < ROWS; ++row)
	{
		for (int col = 1; col < COLS; ++col)
			cout << setw(3) << product[row][col];

		cout << endl;
	}

	// Для перехода использования элементов двумерного массива в виде одномерного массива используем формулу:
	// matrix[r][c] -> vector[r * COLS + c], где COLS - кол-во элементов в 1 строке матрицы (кол-во столбцов)
	int array1D[ROWS * COLS]{};

	// Переписываем из двумерного массива в одномерный значения с их удвоением
	int n = 0;
	for (int row = 0; row < ROWS; ++row)
	{
		for (int column = 0; column < COLS; ++column)
		{
			array1D[n++] = product[row][column] * 2;
		}
	}

	cout << endl;
	for (int i = 0; i < ROWS * COLS; ++i)
	{
		cout << array1D[i] << "  ";
	}

	// Восстановление двумерного массива из одномерного вектора
	n = 0;
	for (int row = 0; row < ROWS; ++row) {
		for (int column = 0; column < COLS; ++column)
		{
			product[row][column] = array1D[n++];
		}
	}

	cout << endl;
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
			cout << setw(4) << product[row][col];

		cout << endl;
	}


	// Matrix filling with random numbers within specified range
	cout << "\n\n";
	int array2[ROWS][COLS] = { 0 };
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
			cout << (product[row][col] = rand() % RANGE) << " ";
		cout << endl;
	}

	// Elements of Main diagonal
	cout << endl << "Elements of Main diagonal:" << endl;
	for (int row = 0; row < ROWS; ++row)
	{
		cout << product[row][row] << " ";
	}
	cout << endl;


	// Elements of Secondary diagonal
	cout << endl << "Elements of Secondary diagonal:" << endl;
	for (int column = 0; column < COLS; ++column)
	{
		cout << product[ROWS - column - 1][column] << " ";
	}
	cout << endl;


	// Copy values of one matrix to another with transposing
	cout << endl;
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			cout << (row < col ? "\x1B[94m" : (row > col ? "\x1B[93m" : "\x1B[97m"))
				<< (array2[row][col] = product[col][row]) << "\x1B[31m ";
		}
		cout << endl;
	}


	// Sum of elements above Main diagonal
	int sumAboveMainDiag = 0;
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (row < col)
			{
				sumAboveMainDiag += array2[row][col];
			}
		}
	}
	cout << endl << "\x1B[31mSum of elements above main diagonal: " << sumAboveMainDiag << "\033[0m\n";


	// Elements forming British flag
	cout << endl << " Elements as British flag: " << endl;
	for (int row = 0; row < ROWS; row++)
	{
		for (int column = 0; column < COLS; column++)
		{
			if (row == column)
				cout << array2[row][column] << "  ";
			else
				if (row + column == (COLS < ROWS ? COLS : ROWS) - 1)
					cout << array2[row][column] << "  ";
				else
					if (row == ROWS / 2)
						cout << array2[row][column] << "  ";
					else
						if (column == COLS / 2)
							cout << array2[row][column] << "  ";
						else
							cout << "   ";
		}
		cout << endl;
	}


	// Max and Min element of matrix
	int rowMaxIndex = 0, colMaxIndex = 0, rowMinIndex = 0, colMinIndex = 0;
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (array2[row][col] > array2[rowMaxIndex][colMaxIndex])
			{
				rowMaxIndex = row;
				colMaxIndex = col;
			}
			else
			{
				if (array2[row][col] < array2[rowMinIndex][colMinIndex])
				{
					rowMinIndex = row;
					colMinIndex = col;
				}
			}
		}
	}

	cout << "\nMax element is: " << array2[rowMaxIndex][colMaxIndex] << ", it is situated: [" << rowMaxIndex << "][" << colMaxIndex << "]";
	cout << "\nMin element is: " << array2[rowMinIndex][colMinIndex] << ", it is situated: [" << rowMinIndex << "][" << colMinIndex << "]\n\n";


	// Counting of Min and Max quantity in matrix
	int maxCounter = 0, minCounter = 0;
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (array2[row][col] == array2[rowMaxIndex][colMaxIndex])
			{
				cout << "\x1B[95m";
				maxCounter++;
			}
			else
				if (array2[row][col] == array2[rowMinIndex][colMinIndex])
				{
					cout << "\x1B[96m";
					minCounter++;
				}

			cout << array2[row][col] << " ";
			// if ((array2[row][col] == array2[rowMaxIndex][colMaxIndex]) || (array2[row][col] == array2[rowMinIndex][colMinIndex]))
			{
				cout << "\033[0m";
			}
		}
		cout << endl;
	}
	cout << "\nMax element is: " << array2[rowMaxIndex][colMaxIndex] << ", it is quantity: " << maxCounter;
	cout << "\nMin element is: " << array2[rowMinIndex][colMinIndex] << ", it is quantity: " << minCounter;



	// Exchange of neighbor rows of matrix (even and odd rows)
	cout << "\n\n";
	int max = array2[rowMaxIndex][colMaxIndex];
	int min = array2[rowMinIndex][colMinIndex];
	int temp;
	for (int row = 0; row < ROWS; row += 2)
	{
		for (int col = 0; col < COLS; ++col)
		{
			temp = array2[row][col];
			array2[row][col] = array2[row + 1][col];
			array2[row + 1][col] = temp;
		}
	}


	// Coloring of Max and Min value during matrix printing
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (array2[row][col] == max)
			{
				cout << "\x1B[95m";
			}
			if (array2[row][col] == min)
			{
				cout << "\x1B[96m";
			}

			cout << array2[row][col] << " ";
			// This will not work here: 
			// if ((array2[row][col] == array2[rowMaxIndex][colMaxIndex]) || (array2[row][col] == array2[rowMinIndex][colMinIndex]))
			if ((array2[row][col] == max) || (array2[row][col] == min))
			{
				cout << "\033[0m";
			}
		}
		cout << endl;
	}


	// Exchange of neighbour columns of matrix (even and odd)
	cout << "\n\n";
	for (int col = 0; col < COLS; col += 2)
	{
		for (int row = 0; row < ROWS; ++row)
		{
			temp = array2[row][col];
			array2[row][col] = array2[row][col + 1];
			array2[row][col + 1] = temp;
		}
	}

	// Coloring of Max and Min value during matrix printing
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (array2[row][col] == max)
			{
				cout << "\x1B[95m";
			}
			if (array2[row][col] == min)
			{
				cout << "\x1B[96m";
			}

			cout << array2[row][col] << " ";
			if ((array2[row][col] == max) || (array2[row][col] == min))
			{
				cout << "\033[0m";
			}
		}
		cout << endl;
	}

	// Matrix arifmetical operaions
	cout << "\n\n----------------------------\n\n";
	const int N = 5;
	int m1[N][N] = { 0 }, m2[N][N] = { 0 }, m3[N][N]{};

	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			m1[row][col] = rand() % 10;
			m2[row][col] = rand() % 10;
			m3[row][col] = m1[row][col] + m2[row][col]; // // Sum of corresponding values of 2 matrices and store in third matrix 
		}
	}

	// Printing matrices horisontaly
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			cout << m1[row][col] << " ";
		}

		cout << "\t";
		for (int col = 0; col < N; col++)
		{
			cout << m2[row][col] << " ";
		}

		cout << "\t";
		for (int col = 0; col < N; col++)
		{
			cout << setw(4) << m3[row][col];
		}

		cout << endl;
	}
	cout << endl;

	// Multiply of corresponding values of 2 matrices
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			m3[row][col] = m1[row][col] * m2[row][col];
		}
	}

	// Printing matrices horisontaly
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			cout << m1[row][col] << " ";
		}

		cout << "\t";
		for (int col = 0; col < N; col++)
		{
			cout << m2[row][col] << " ";
		}

		cout << "\t";
		for (int col = 0; col < N; col++)
		{
			cout << setw(4) << m3[row][col];
		}

		cout << endl;
	}


	// 3D array
	const int LAYERS = 2;
	int array3D[LAYERS][ROWS][COLS]{};
	for (int layer = 0; layer < LAYERS; layer++)
	{
		for (int row = 0; row < ROWS; row++)
		{
			for (int column = 0; column < COLS; column++)
			{
				array3D[layer][row][column] = rand() % 10;
			}
		}
	}

	cout << endl << "3D arrays: Layers of Matrices" << endl;
	for (int layer = 0; layer < LAYERS; layer++)
	{
		for (int row = 0; row < ROWS; row++)
		{
			for (int column = 0; column < COLS; column++)
			{
				cout << array3D[layer][row][column] << "  ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

/// <summary>
///	Задан Двумерный массив вещественных чисел. Найти:
/// а) максимальную сумму абсолютных значений элементов по строкам и номер строки с такой суммой;
/// б) максимальную сумму абсолютных значений элементов по столбцам и номер столбца с такой суммой
/// </summary>
static void example2() {
	const int ROWS = 10;
	const int COLS = 10;
	const int RANGE = 10;
	int array2[ROWS][COLS] = { 0 };

	int product[ROWS][COLS] = { 0 };
	int sumForRows[ROWS] = { 0 };
	int sumForCols[COLS] = { 0 };

	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			sumForRows[row] += abs(array2[row][col]);
		}
	}

	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			sumForCols[col] += abs(array2[row][col]);
		}
	}

	cout << endl << "Sums of rows absolute values: ";
	for (int row = 0; row < ROWS; ++row)
	{
		cout << sumForRows[row] << "\t";
	}

	cout << endl << "Sums of columns absolute values: ";
	for (int col = 0; col < COLS; ++col)
	{
		cout << sumForCols[col] << "\t";
	}

	int maxRowSumsIndex = 0, maxColSumsIndex = 0;
	for (int row = 1; row < ROWS; ++row)
	{
		if (sumForRows[row] > sumForRows[maxRowSumsIndex])
			maxRowSumsIndex = row;
	}
	for (int col = 1; col < COLS; ++col)
	{
		if (sumForCols[col] > sumForCols[maxColSumsIndex])
			maxColSumsIndex = col;
	}

	cout << endl << "Maximum of Sums of rows absolute values: \x1B[105m" << sumForRows[maxRowSumsIndex] << "\033[0m";
	cout << endl << "Maximum of Sums of cols absolute values: \x1B[105m" << sumForCols[maxColSumsIndex] << "\033[0m";
}

/// <summary>
/// Произвести расчёт разнообразной статистики по результатам работы корпорации из 8 филиалов в течение 12 месяцев
/// </summary>
static void example3()
{
	cout << endl << " -----------------------------------------------------------------";
	cout << endl << "| Income of 8 COMPANIES for 12 MONTHS. Calculating all statistics |";
	cout << endl << " -----------------------------------------------------------------" << endl << endl;

	const int MONTHS = 12, COMPANIES = 8;
	int income[MONTHS][COMPANIES]{};

	for (int month = 0; month < MONTHS; month++)
	{
		cout << month + 1 << ") ";
		for (int company = 0; company < COMPANIES; company++)
		{
			cout << (income[month][company] = rand() % 20) << "\t";
		}
		cout << endl;
	}
	cout << endl;

	int totalIncomeByMonth[MONTHS]{}, totalIncomeByCompanies[COMPANIES]{};
	double averageIncomeByMonth[MONTHS]{}, averageIncomeByCompanies[COMPANIES]{};
	double averageInCorporation = 0;

	for (int month = 0; month < MONTHS; month++)
		totalIncomeByMonth[month] = 0;
	for (int company = 0; company < COMPANIES; company++)
		totalIncomeByCompanies[company] = 0;

	for (int month = 0; month < MONTHS; month++)
	{
		for (int company = 0; company < COMPANIES; company++)
		{
			totalIncomeByMonth[month] += income[month][company];
		}
		averageIncomeByMonth[month] = (double)totalIncomeByMonth[month] / MONTHS;
	}

	cout << "totalIncomeByMonth:" << endl;
	for (int month = 0; month < MONTHS; month++)
	{
		cout << totalIncomeByMonth[month] << "\t";
	}

	cout << endl << "averageIncomeByMonth:" << endl;
	for (int month = 0; month < MONTHS; month++)
	{
		cout << averageIncomeByMonth[month] << "\t";
	}

	for (int company = 0; company < COMPANIES; company++)
	{
		for (int month = 0; month < MONTHS; month++)
		{
			totalIncomeByCompanies[company] += income[month][company];
		}
		averageIncomeByCompanies[company] = (double)totalIncomeByCompanies[company] / COMPANIES;
	}

	cout << endl;
	cout << "totalIncomeByCompanies:" << endl;
	for (int company = 0; company < COMPANIES; company++)
	{
		cout << totalIncomeByCompanies[company] << "\t";
	}

	cout << endl << "averageIncomeByCompanies:" << endl;
	for (int company = 0; company < COMPANIES; company++)
	{
		cout << averageIncomeByCompanies[company] << "\t";
	}

	for (int company = 0; company < COMPANIES; company++)
	{
		averageInCorporation += averageIncomeByCompanies[company];
	}
	averageInCorporation /= COMPANIES;
	cout << endl << "averageInCorporation: " << averageInCorporation << endl;

	cout << "Companis with income more than average in corporation:" << endl;
	for (int company = 0; company < COMPANIES; company++)
	{
		if (averageIncomeByCompanies[company] > averageInCorporation)
			cout << company << ") " << averageIncomeByCompanies[company] << endl;
	}

	cout << endl;

	int maxMonth = 0, maxCompany = 0;
	int minMonth = 0, minCompany = 0;
	for (int company = 0; company < COMPANIES; company++)
	{
		for (int month = 0; month < MONTHS; month++)
		{
			if (income[company][month] > income[maxCompany][maxMonth])
			{
				maxCompany = company;
				maxMonth = month;
			}
			else
			{
				if (income[company][month] < income[minCompany][minMonth])
				{
					minCompany = company;
					minMonth = month;
				}
			}
		}
	}
	cout << "Max income in corporation is: " << income[maxCompany][maxMonth] << endl;
	cout << "Min income in corporation is: " << income[minCompany][minMonth] << endl;

	int maxCounter = 0, minCounter = 0;
	for (int company = 0; company < COMPANIES; company++)
	{
		for (int month = 0; month < MONTHS; month++)
		{
			if (income[maxCompany][maxMonth] == income[company][month])
			{
				maxCounter++;
			}
			// TODO: Correct min counter
			if (income[minCompany][minMonth] == income[company][month])
			{
				minCounter++;
			}
		}
	}

	cout << "Max income in corporation found: " << maxCounter << " times" << endl;
	cout << "Min income in corporation found: " << minCounter << " times" << endl;

	cout << endl << "Sort by row Total Income by Company (totalIncomeByCompanies):" << endl;
	for (int company = 0; company < COMPANIES; company++)
	{
		cout << totalIncomeByCompanies[company] << "\t";
	}

	int temp;
	for (int month = 0; month < MONTHS; month++)
	{
		for (int company = 0; company < COMPANIES - 1; company++)
		{
			if (totalIncomeByCompanies[company] < totalIncomeByCompanies[company + 1])
			{
				temp = totalIncomeByCompanies[company];
				totalIncomeByCompanies[company] = totalIncomeByCompanies[company + 1];
				totalIncomeByCompanies[company + 1] = temp;

				for (int submonth = 0; submonth < MONTHS; submonth++)
				{
					temp = income[submonth][company];
					income[submonth][company] = income[submonth][company + 1];
					income[submonth][company + 1] = temp;
				}
			}
		}
	}

	cout << endl << endl;
	for (int company = 0; company < COMPANIES; company++)
	{
		cout << totalIncomeByCompanies[company] << "\t";
	}

	cout << endl << endl;
	for (int month = 0; month < MONTHS; month++)
	{
		for (int company = 0; company < COMPANIES; company++)
		{
			cout << income[month][company] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

int main()
{
	example1(); // simple matrices examples
	example2(); // simple matrix processing
	example3(); // realword arrays2D example

	cout << endl;
	cout << endl;
}