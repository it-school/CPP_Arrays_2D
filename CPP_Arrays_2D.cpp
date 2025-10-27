#include <iostream>
#include <iomanip>
#include <cstdlib>   // для rand()
#include <ctime>     // для time()
#include <cmath>     // для abs()
using namespace std;

/// <summary>
/// Демонстрация различных операций с двумерными массивами:
/// ввод, обработка и анализ 2D массива.
/// </summary>
static void example1() {
	const int ROWS = 10;
	const int COLUMNS = 10;
	const int RANGE = 10;

	// Объявляем массив ROWSxCOLUMNS и заполняем нулями
	int product[ROWS][COLUMNS] = { 0 };

	// Создание таблицы умножения
	for (int row = 0; row < ROWS; ++row)
		for (int column = 0; column < COLUMNS; ++column)
			product[row][column] = row * column;

	// Вывод таблицы без первой строки и столбца (чтобы пропустить нули)
	for (int row = 1; row < ROWS; ++row) {
		for (int col = 1; col < COLUMNS; ++col)
			cout << setw(3) << product[row][col];
		cout << endl;
	}

	// Работа с одномерным массивом как с плоской копией двумерного
	int array1D[ROWS * COLUMNS]{};
	int n = 0;
	for (int row = 0; row < ROWS; ++row)
		for (int column = 0; column < COLUMNS; ++column)
			array1D[n++] = product[row][column] * 2; // удвоение элементов

	cout << endl;
	for (int i = 0; i < ROWS * COLUMNS; ++i)
		cout << array1D[i] << "  ";

	// Восстановление двумерного массива из одномерного
	n = 0;
	for (int row = 0; row < ROWS; ++row)
		for (int column = 0; column < COLUMNS; ++column)
			product[row][column] = array1D[n++];

	cout << endl;
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLUMNS; ++col)
			cout << setw(4) << product[row][col];
		cout << endl;
	}

	// Генерация случайной матрицы и вывод
	cout << "\n\n";
	int array2[ROWS][COLUMNS] = { 0 };
	srand(static_cast<unsigned>(time(nullptr))); // инициализация генератора случайных чисел
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLUMNS; ++col)
			cout << (product[row][col] = rand() % RANGE) << " ";
		cout << endl;
	}

	// Главная диагональ
	cout << endl << "Elements of Main diagonal:" << endl;
	for (int row = 0; row < ROWS; ++row)
		cout << product[row][row] << " ";
	cout << endl;

	// Побочная диагональ
	cout << endl << "Elements of Secondary diagonal:" << endl;
	for (int column = 0; column < COLUMNS; ++column)
		cout << product[ROWS - column - 1][column] << " ";
	cout << endl;

	// Транспонирование матрицы с подсветкой элементов
	cout << endl;
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLUMNS; ++col) {
			cout << (row < col ? "\x1B[94m" : (row > col ? "\x1B[93m" : "\x1B[97m"))
				<< (array2[row][col] = product[col][row]) << "\x1B[31m ";
		}
		cout << endl;
	}

	// Сумма элементов над главной диагональю
	int sumAboveMainDiag = 0;
	for (int row = 0; row < ROWS; ++row)
		for (int col = 0; col < COLUMNS; ++col)
			if (row < col)
				sumAboveMainDiag += array2[row][col];
	cout << endl << "\x1B[31mSum of elements above main diagonal: " << sumAboveMainDiag << "\033[0m\n";

	// Элементы, формирующие "британский флаг"
	cout << endl << " Elements as British flag: " << endl;
	for (int row = 0; row < ROWS; row++) {
		for (int column = 0; column < COLUMNS; column++) {
			if (row == column || row + column == min(COLUMNS, ROWS) - 1 ||
				row == ROWS / 2 || column == COLUMNS / 2)
				cout << array2[row][column] << "  ";
			else
				cout << "   ";
		}
		cout << endl;
	}

	// Нахождение максимального и минимального элемента
	int rowMaxIndex = 0, colMaxIndex = 0, rowMinIndex = 0, colMinIndex = 0;
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLUMNS; ++col) {
			if (array2[row][col] > array2[rowMaxIndex][colMaxIndex]) {
				rowMaxIndex = row;
				colMaxIndex = col;
			}
			else if (array2[row][col] < array2[rowMinIndex][colMinIndex]) {
				rowMinIndex = row;
				colMinIndex = col;
			}
		}
	}

	cout << "\nMax element is: " << array2[rowMaxIndex][colMaxIndex]
		<< ", it is situated: [" << rowMaxIndex << "][" << colMaxIndex << "]";
	cout << "\nMin element is: " << array2[rowMinIndex][colMinIndex]
		<< ", it is situated: [" << rowMinIndex << "][" << colMinIndex << "]\n\n";

	// Подсчет количества максимумов и минимумов с цветовой подсветкой
	int maxCounter = 0, minCounter = 0;
	int max = array2[rowMaxIndex][colMaxIndex];
	int min = array2[rowMinIndex][colMinIndex];
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLUMNS; ++col) {
			if (array2[row][col] == max) { cout << "\x1B[95m"; maxCounter++; }
			else if (array2[row][col] == min) { cout << "\x1B[96m"; minCounter++; }

			cout << array2[row][col] << " ";
			// This will not work here: 
			// if ((array2[row][col] == array2[rowMaxIndex][colMaxIndex]) || (array2[row][col] == array2[rowMinIndex][colMinIndex]))
			if ((array2[row][col] == max) || (array2[row][col] == min)) cout << "\033[0m";
		}
		cout << endl;
	}
	cout << "\nMax element quantity: " << maxCounter << ", Min element quantity: " << minCounter << endl;

	// Обмен соседних строк (четная-нечетная)
	int temp;
	for (int row = 0; row < ROWS; row += 2)
		for (int col = 0; col < COLUMNS; ++col)
			swap(array2[row][col], array2[row + 1][col]);

	// Обмен соседних столбцов
	for (int col = 0; col < COLUMNS; col += 2)
		for (int row = 0; row < ROWS; ++row)
			swap(array2[row][col], array2[row][col + 1]);

	// Арифметические операции над небольшими матрицами
	const int N = 5;
	int m1[N][N] = { 0 }, m2[N][N] = { 0 }, m3[N][N] = { 0 };
	for (int row = 0; row < N; ++row)
		for (int col = 0; col < N; ++col) {
			m1[row][col] = rand() % 10;
			m2[row][col] = rand() % 10;
			m3[row][col] = m1[row][col] + m2[row][col]; // сложение матриц
		}

	// Вывод матриц горизонтально
	for (int row = 0; row < N; ++row) {
		for (int col = 0; col < N; ++col) cout << m1[row][col] << " ";
		cout << "\t";
		for (int col = 0; col < N; ++col) cout << m2[row][col] << " ";
		cout << "\t";
		for (int col = 0; col < N; ++col) cout << setw(4) << m3[row][col];
		cout << endl;
	}

	// Умножение матриц поэлементно
	for (int row = 0; row < N; ++row)
		for (int col = 0; col < N; ++col)
			m3[row][col] = m1[row][col] * m2[row][col];

	// Вывод результатов умножения
	for (int row = 0; row < N; ++row) {
		for (int col = 0; col < N; ++col) cout << m1[row][col] << " ";
		cout << "\t";
		for (int col = 0; col < N; ++col) cout << m2[row][col] << " ";
		cout << "\t";
		for (int col = 0; col < N; ++col) cout << setw(4) << m3[row][col];
		cout << endl;
	}

	// 3D массив (дополнительный пример)
	const int LAYERS = 2;
	int array3D[LAYERS][ROWS][COLUMNS]{};
	for (int layer = 0; layer < LAYERS; ++layer)
		for (int row = 0; row < ROWS; ++row)
			for (int column = 0; column < COLUMNS; ++column)
				array3D[layer][row][column] = rand() % 100;

	cout << endl << "3D arrays: Layers of Matrices" << endl;
	for (int layer = 0; layer < LAYERS; ++layer) {
		for (int row = 0; row < ROWS; ++row) {
			for (int column = 0; column < COLUMNS; ++column)
				cout << setw(4) << array3D[layer][row][column];
			cout << endl;
		}
		cout << endl;
	}
}

/// <summary>
/// Выполнение различных расчетов и агрегаций над 2D массивом:
/// поиск максимальных сумм по строкам и столбцам.
/// </summary>
static void example2()
{
	cout << endl << " ---------------------------------------------";
	cout << endl << "|   2D Arrays: Calculations and Aggregations  |";
	cout << endl << " ---------------------------------------------" << endl << endl;

	const int ROWS = 5;
	const int COLUMNS = 7;
	int array[ROWS][COLUMNS]{};

	srand(static_cast<unsigned>(time(nullptr))); // инициализация генератора случайных чисел

	// Заполняем двумерный массив случайными числами от 0 до 9
	cout << "Generated matrix:\n";
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLUMNS; ++col) {
			array[row][col] = rand() % 10;
			cout << array[row][col] << "\t";
		}
		cout << endl;
	}

	// Вычисляем сумму элементов по строкам и выводим их
	cout << endl << "Sum of each row:" << endl;
	int totalSum = 0;                  // общая сумма по всей матрице
	int sumRows[ROWS]{};               // массив для хранения сумм по строкам
	for (int row = 0; row < ROWS; ++row) {
		sumRows[row] = 0;              // обнуляем перед подсчетом
		for (int col = 0; col < COLUMNS; ++col)
			sumRows[row] += array[row][col];
		cout << "Row " << row << ": " << sumRows[row] << endl;
		totalSum += sumRows[row];      // добавляем в общую сумму
	}

	// Вычисляем сумму элементов по столбцам
	cout << endl << "Sum of each column:" << endl;
	int sumColumns[COLUMNS]{};
	for (int col = 0; col < COLUMNS; ++col) {
		sumColumns[col] = 0;
		for (int row = 0; row < ROWS; ++row)
			sumColumns[col] += array[row][col];
		cout << "Column " << col << ": " << sumColumns[col] << endl;
	}

	cout << endl << "Total sum of all elements: " << totalSum << endl;

	// Поиск максимального и минимального элементов матрицы
	int rowMax = 0, colMax = 0;
	int rowMin = 0, colMin = 0;
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLUMNS; ++col) {
			if (array[row][col] > array[rowMax][colMax]) {
				rowMax = row;
				colMax = col;
			}
			else if (array[row][col] < array[rowMin][colMin]) {
				rowMin = row;
				colMin = col;
			}
		}
	}

	cout << endl << "Max element: " << array[rowMax][colMax]
		<< " at position [" << rowMax << "][" << colMax << "]" << endl;
	cout << "Min element: " << array[rowMin][colMin]
		<< " at position [" << rowMin << "][" << colMin << "]" << endl;

	// Подсчет количества максимальных и минимальных элементов
	int maxCount = 0, minCount = 0;
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLUMNS; ++col) {
			if (array[row][col] == array[rowMax][colMax]) maxCount++;
			if (array[row][col] == array[rowMin][colMin]) minCount++;
		}
	}

	cout << endl << "Max element repeats: " << maxCount
		<< " times, Min element repeats: " << minCount << " times." << endl;

	// Подсчет суммы чётных и нечётных элементов
	int evenSum = 0, oddSum = 0;
	for (int row = 0; row < ROWS; ++row)
		for (int col = 0; col < COLUMNS; ++col)
			(array[row][col] % 2 == 0 ? evenSum : oddSum) += array[row][col];

	cout << endl << "Sum of even elements: " << evenSum << endl;
	cout << "Sum of odd elements: " << oddSum << endl;

	// Пример поиска строки с наибольшей суммой элементов
	int maxRowIndex = 0;
	for (int row = 1; row < ROWS; ++row)
		if (sumRows[row] > sumRows[maxRowIndex]) maxRowIndex = row;

	cout << endl << "Row with maximum sum is Row " << maxRowIndex
		<< " with sum " << sumRows[maxRowIndex] << endl;

	// Сортировка строк по возрастанию их сумм (пузырьковая сортировка)
	for (int i = 0; i < ROWS - 1; ++i) {
		for (int j = 0; j < ROWS - i - 1; ++j) {
			if (sumRows[j] > sumRows[j + 1]) {
				swap(sumRows[j], sumRows[j + 1]);
				for (int k = 0; k < COLUMNS; ++k)
					swap(array[j][k], array[j + 1][k]); // синхронно переставляем строки
			}
		}
	}

	cout << endl << "Matrix sorted by row sums (ascending):" << endl;
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLUMNS; ++col)
			cout << array[row][col] << "\t";
		cout << endl;
	}
	cout << endl;
}


/// <summary>
/// Финансовый анализ: произвести расчёт разнообразной статистики по результатам работы корпорации из 8 филиалов в течение 12 месяцев
/// </summary>
static void example3()
{
	cout << endl << " -----------------------------------------------------------------";
	cout << endl << "| Income of 8 COMPANIES for 12 MONTHS. Calculating all statistics |";
	cout << endl << " -----------------------------------------------------------------" << endl << endl;

	const int MONTHS = 12, COMPANIES = 8;
	int income[MONTHS][COMPANIES]{}; // матрица доходов: строки - месяцы, столбцы - компании

	srand(static_cast<unsigned>(time(nullptr))); // инициализация генератора случайных чисел

	// Генерация доходов корпорации для каждой компании в каждом месяце
	for (int month = 0; month < MONTHS; month++) {
		cout << month + 1 << ") ";
		for (int company = 0; company < COMPANIES; company++)
			cout << (income[month][company] = rand() % 20) << "\t"; // доход от 0 до 19
		cout << endl;
	}

	// Массивы для хранения итогов по месяцам и компаниям
	int totalIncomeByMonth[MONTHS]{}, totalIncomeByCompanies[COMPANIES]{};
	double averageIncomeByMonth[MONTHS]{}, averageIncomeByCompanies[COMPANIES]{};
	double averageInCorporation = 0;

	// Обнуляем суммы (на всякий случай, хотя инициализация выше это уже сделала)
	for (int month = 0; month < MONTHS; month++) totalIncomeByMonth[month] = 0;
	for (int company = 0; company < COMPANIES; company++) totalIncomeByCompanies[company] = 0;

	// Считаем суммарный доход по месяцам
	for (int month = 0; month < MONTHS; month++) {
		for (int company = 0; company < COMPANIES; company++)
			totalIncomeByMonth[month] += income[month][company]; // суммируем по строке
		averageIncomeByMonth[month] = static_cast<double>(totalIncomeByMonth[month]) / COMPANIES; // средний доход за месяц
	}

	cout << "totalIncomeByMonth:" << endl;
	for (int month = 0; month < MONTHS; month++)
		cout << totalIncomeByMonth[month] << "\t";

	cout << endl << "averageIncomeByMonth:" << endl;
	for (int month = 0; month < MONTHS; month++)
		cout << averageIncomeByMonth[month] << "\t";

	// Считаем суммарный доход по компаниям (столбцы)
	for (int company = 0; company < COMPANIES; company++) {
		for (int month = 0; month < MONTHS; month++)
			totalIncomeByCompanies[company] += income[month][company]; // суммируем по столбцу
		averageIncomeByCompanies[company] = static_cast<double>(totalIncomeByCompanies[company]) / MONTHS; // средний доход компании
	}

	cout << endl << "totalIncomeByCompanies:" << endl;
	for (int company = 0; company < COMPANIES; company++)
		cout << totalIncomeByCompanies[company] << "\t";

	cout << endl << "averageIncomeByCompanies:" << endl;
	for (int company = 0; company < COMPANIES; company++)
		cout << averageIncomeByCompanies[company] << "\t";

	// Средний доход по корпорации
	for (int company = 0; company < COMPANIES; company++)
		averageInCorporation += averageIncomeByCompanies[company];
	averageInCorporation /= COMPANIES;
	cout << endl << "averageInCorporation: " << averageInCorporation << endl;

	// Компании с доходом выше среднего
	cout << "Companis with income more than average in corporation:" << endl;
	for (int company = 0; company < COMPANIES; company++)
		if (averageIncomeByCompanies[company] > averageInCorporation)
			cout << company << ") " << averageIncomeByCompanies[company] << endl;

	cout << endl;

	// Поиск максимального и минимального дохода в корпорации
	int maxMonth = 0, maxCompany = 0;
	int minMonth = 0, minCompany = 0;
	for (int company = 0; company < COMPANIES; company++) {
		for (int month = 0; month < MONTHS; month++) {
			if (income[month][company] > income[maxMonth][maxCompany]) {
				maxMonth = month;
				maxCompany = company;
			}
			else if (income[month][company] < income[minMonth][minCompany]) {
				minMonth = month;
				minCompany = company;
			}
		}
	}

	cout << "Max income in corporation is: " << income[maxMonth][maxCompany] << endl;
	cout << "Min income in corporation is: " << income[minMonth][minCompany] << endl;

	// Подсчет количества повторений максимального и минимального дохода
	int maxCounter = 0, minCounter = 0;
	for (int company = 0; company < COMPANIES; company++) {
		for (int month = 0; month < MONTHS; month++) {
			if (income[month][company] == income[maxMonth][maxCompany]) maxCounter++;
			if (income[month][company] == income[minMonth][minCompany]) minCounter++;
		}
	}

	cout << "Max income in corporation found: " << maxCounter << " times" << endl;
	cout << "Min income in corporation found: " << minCounter << " times" << endl;

	// Сортировка компаний по суммарному доходу по столбцам (пузырьком)
	int temp;
	for (int month = 0; month < MONTHS; month++) { // проходы по месяцам
		for (int company = 0; company < COMPANIES - 1; company++) {
			if (totalIncomeByCompanies[company] < totalIncomeByCompanies[company + 1]) {
				swap(totalIncomeByCompanies[company], totalIncomeByCompanies[company + 1]);
				for (int submonth = 0; submonth < MONTHS; submonth++) {
					swap(income[submonth][company], income[submonth][company + 1]); // синхронный swap столбцов
				}
			}
		}
	}

	// Вывод отсортированных сумм и доходов
	cout << endl << "Sorted totalIncomeByCompanies:" << endl;
	for (int company = 0; company < COMPANIES; company++)
		cout << totalIncomeByCompanies[company] << "\t";

	cout << endl << endl;
	cout << "Sorted income matrix by company totals:" << endl;
	for (int month = 0; month < MONTHS; month++) {
		for (int company = 0; company < COMPANIES; company++)
			cout << income[month][company] << "\t";
		cout << endl;
	}
	cout << endl;
}


int main()
{
	example1(); // simple matrices examples
	example2(); // simple matrix processing
	example3(); // realword arrays2D example

	cout << endl << endl;
}