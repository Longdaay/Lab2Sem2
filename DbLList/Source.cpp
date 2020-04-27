#include <iostream>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <chrono>
#include <Windows.h>
#include <iomanip>

using namespace std;
int m_count = 0; // счетчик главного меню
int subm_l_count = 0; // счетчик подменю списка
int subm_a_count = 0; // счетчик подменю массива
int subm_l_c_count = 0; // счетчик подменю создания списка
int subm_a_c_count = 0; // счетчик подменю создания массива
int subm_l_s_count = 0; // счетчик подменю поиска элемента в списке
int subm_a_s_count = 0; // счетчик подменю поиска элемента в массиве
int subm_l_d_count = 0; // счетчик подменю удаления элемента в списке
int subm_a_d_count = 0; // счетчик подменю удаления элемента в массиве

bool fl_array_create = FALSE; // флаг создания массива
bool fl_list_create = FALSE; // флаг создания списка

void SetColor(int text, int bg) //Функция смены цвета, взятая из Интернета
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

typedef struct _Node {
	int value;
	struct _Node* next;
	struct _Node* prev;
} Node;

typedef struct _DblLinkedList {
	size_t size;
	Node* head;
	Node* tail;
} DblLinkedList;

///////////////////////// PROTOTYPES //////////////////////////
void menu(DblLinkedList* list, int* arr, int& arr_size); // меню
void submenu_list(DblLinkedList* list, int* arr, int& arr_size); // подменю списка
void submenu_array(DblLinkedList* list, int* arr, int& arr_size); // подменю массива
void submenu_list_create(DblLinkedList* list, int* arr, int& arr_size); // подменю создания списка
void submenu_array_create(DblLinkedList* list, int* arr, int& arr_size); // подменю создания массива
void submenu_list_search(DblLinkedList* list, int* arr, int& arr_size); // подменю поиска элемента списка
void submenu_array_search(DblLinkedList* list, int* arr, int& arr_size); // подменю поиска элемента массива
void submenu_list_delete(DblLinkedList* list, int* arr, int& arr_size); // подменю удаления элемента списка
void submenu_array_delete(DblLinkedList* list, int* arr, int& arr_size); // подменю удаления элемента массива
void menu_choice(DblLinkedList* list, int* arr, int& arr_size); // управление меню
void submenu_list_choice(DblLinkedList* list, int* arr, int& arr_size); // управление подменю списка
void submenu_array_choice(DblLinkedList* list, int* arr, int& arr_size); // управление подменю массива
void submenu_list_create_choice(DblLinkedList* list, int* arr, int& arr_size); // управление подменю создания списка
void submenu_array_create_choice(DblLinkedList* list, int* arr, int& arr_size); // управление подменю создания массива
void submenu_list_search_choice(DblLinkedList* list, int* arr, int& arr_size); // управление подменю поиска элемента списка
void submenu_array_search_choice(DblLinkedList* list, int* arr, int& arr_size); // управление подменю поиска элемента массива
void submenu_list_delete_choice(DblLinkedList* list, int* arr, int& arr_size); // управление подменю удаления элемента списка
void submenu_array_delete_choice(DblLinkedList* list, int* arr, int& arr_size); // управление подменю удаления элемента массива
void printDblLinkedList(DblLinkedList* list); // вывод списка

///////////////////////// PROTOTYPES //////////////////////////

int checkdigit() // проверка на корректный ввод
{
	while (true)
	{
		int value;
		// вводим число, которое хотим представить в двоичной форме
		cin >> value; // число целое
		if (cin.fail()) // ecли предыдущее извелечение оказлось неудачным,
		{
			cin.clear(); // то возвращаем cin в обычный режим работы
			cin.ignore(32767, '\n'); // и удаляем из буфера значения предыдущего ввода 
			cout << "Недопустимое заданное число. Введите число правильно" << '\n';
		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем из буфера значения предыдущего ввода 
			return value;
		}
	}
}

bool check_index(int value, int size) // проверка попадания в диапазон
{
	if (value >= 0 && value <= size)
		return TRUE;
	else
		return FALSE;
}

///////////////////////////// DBLINKEDLIST///////////////

DblLinkedList* createDblLinkedList() // создание списка
{
	DblLinkedList* tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList));

	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp;
}

void pushFront(DblLinkedList* list, int data) // добавление узла в начало списка
{
	Node* tmp = (Node*)malloc(sizeof(Node));

	tmp->value = data;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head)
	{
		list->head->prev = tmp;
	}
	list->head = tmp;

	if (list->tail == NULL) 
	{
		list->tail = tmp;
	}
	list->size++;
}

void pushBack(DblLinkedList* list, int value) // добавление узла в конец списка
{
	Node* tmp = (Node*)malloc(sizeof(Node));

	tmp->value = value;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->tail) 
	{
		list->tail->next = tmp;
	}
	list->tail = tmp;

	if (list->head == NULL) 
	{
		list->head = tmp;
	}
	list->size++;
}

Node* getNth_list_index(DblLinkedList* list, size_t index) //получение узла от индекса
{
	Node* tmp = list->head;
	size_t i = 0;

	while (tmp && i < index) 
	{
		tmp = tmp->next;
		i++;
	}

	return tmp;
}

bool check_getNth_list_value(DblLinkedList* list, int value) // проверка существования значения узла в списке
{
	Node* tmp = list->head;
	size_t index = 0;

	while (tmp && tmp->value != value)
	{
		tmp = tmp->next;
		index++;
	}
	if (tmp)
		return TRUE;
	else
		return FALSE;
}

int getNth_list_value(DblLinkedList* list, int value) // получение индекса от значения узла
{
	Node* tmp = list->head;
	size_t index = 0;

	while (tmp && tmp->value != value) 
	{
		tmp = tmp->next;
		index++;
	}

	return index;
}

void printDblLinkedList_index(DblLinkedList* list, int index) // вывод списка с выделенным значением
{
	bool fl_stop = TRUE;
	int count = 0;
	Node* tmp = list->head;

	while (tmp)
	{
		if (count == index && fl_stop)
		{
			SetColor(2, 0);
			cout << tmp->value << " ";
			SetColor(7, 0);
			fl_stop = FALSE;
		}
		else
			cout << tmp->value << " ";
		tmp = tmp->next;
		count++;
	}
	cout << endl;
}

void getNth_list(DblLinkedList* list, int* arr, int& arr_size, bool fl_list) // функция получения значения или индекса узла списка
{
	system("cls"); // очищаем консоль
	chrono::steady_clock sc;
	int value;
	int index;

	if (fl_list) // TRUE - ищем индекс. FALSE - ищем значение
	{
		cout << "Введите значение, позицию которого необходимо получить: ";
		value = checkdigit();
		if (!check_getNth_list_value(list, value))
		{
			cout << "Такого значения нет. Нажмите любую клавишу, чтобы попробовать снова." << endl;
			_getch();
			submenu_list(list, arr, arr_size);
		}
		else
		{
			auto start = sc.now();     // устанавливаем начало отсчета времени события
			index = getNth_list_value(list, value);
			auto end = sc.now();       // устанавливаем конец отсчета времени события

			auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
			cout << "Скорость поиска элемента списка равна: " << time_span.count() << " секунд" << endl;
			cout << "Позиция значения " << value << ": " << index << endl;

			cout << "Полученный список: ";
			printDblLinkedList_index(list, index);
			cout << "Нажмите любую клавишу" << endl;
			_getch();
			submenu_list(list, arr, arr_size); // возращаемся в подменю
		}
	}
	else
	{
		cout << "Введите позицию, значение которой необходимо получить от 0 до " << list->size - 1 << ": ";
		index = checkdigit();
		if (!check_index(index, list->size - 1))
		{
			cout << "Значение выходит за рамки диапазона. Нажмите любую клавишу, чтобы попробовать снова." << endl;
			_getch();
			getNth_list(list, arr, arr_size, fl_list);
		}
		auto start = sc.now();     // устанавливаем начало отсчета времени события
		value = getNth_list_index(list, index)->value;
		auto end = sc.now();       // устанавливаем конец отсчета времени события
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
		cout << "Скорость поиска элемента списка равна: " << time_span.count() << " секунд" << endl;
		cout << "Значение позиции " << index << ": " << value << endl;

		cout << "Полученный список: ";
		printDblLinkedList_index(list, index);
		cout << "Нажмите любую клавишу" << endl;
		_getch();
		submenu_list(list, arr, arr_size); // возращаемся в подменю
	}
}
 
void insert(DblLinkedList* list, size_t index, int value) // вставка узла в список
{
	Node* elm = NULL;
	Node* ins = NULL;

	elm = getNth_list_index(list, index);

	ins = (Node*)malloc(sizeof(Node));
	ins->value = value;
	ins->prev = elm;
	ins->next = elm->next;
	if (elm->next) 
	{
		elm->next->prev = ins;
	}
	elm->next = ins;

	if (!elm->prev) 
	{
		list->head = elm;
	}
	if (!elm->next) 
	{
		list->tail = elm;
	}

	list->size++;
}

void insert_list(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // очищаем консоль
	chrono::steady_clock sc;  
	int index;
	int value;

	printDblLinkedList(list);
	cout << endl << "Введите позицию нового значения от 0 до " << list->size - 1 << ": ";
	index = checkdigit();
	if (!check_index(index, list->size - 1))
	{
		cout << "Значение выходит за рамки диапазона. Нажмите любую клавишу, чтобы попробовать снова." << endl;
		_getch();
		insert_list(list, arr, arr_size);
	}

	cout << "Введите новое значение: ";
	value = checkdigit();

	auto start = sc.now();     // устанавливаем начало отсчета времени события
	if (index == 0)
		pushFront(list, value);
	else
		if (index == list->size - 1)
		{
			pushBack(list, value);
			index++;
		}
		else
			insert(list, index - 1 , value);
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	cout << "Скорость вставки элемента списка равна: " << time_span.count() << " секунд" << endl;

	cout << "Новый список: ";
	printDblLinkedList_index(list, index);
	cout << "Список успешно обновлен. Нажмите любую клавишу" << endl;
	_getch();
	submenu_list(list, arr, arr_size);
}

void deleteNth(DblLinkedList* list, size_t index) // удаление узла из списка
{
	Node* elm = NULL;

	int tmp = NULL;
	elm = getNth_list_index(list, index);

	if (elm->prev) 
	{
		elm->prev->next = elm->next;
	}
	if (elm->next) 
	{
		elm->next->prev = elm->prev;
	}
	tmp = elm->value;

	if (!elm->prev) 
	{
		list->head = elm->next;
	}
	if (!elm->next) 
	{
		list->tail = elm->prev;
	}

	free(elm);
	list->size--;
}

void deleteNth_list(DblLinkedList* list, int* arr, int& arr_size, bool fl_del_list) // функция удаления узла из списка
{
	system("cls"); // очищаем консоль
	chrono::steady_clock sc;
	int value;
	int index;

	cout << "Исходный список: ";
	printDblLinkedList(list);

	if (fl_del_list) // TRUE - удаляем по значению. FALSE - удаляем по индексу
	{
		cout << "Введите значение, которое будет удалено (удаление первого вхождения): ";
		value = checkdigit();
		if (!check_getNth_list_value(list, value))
		{
			cout << "Такого значения нет. Нажмите любую клавишу, чтобы попробовать снова." << endl;
			_getch();
			submenu_list(list, arr, arr_size);
		}
		else
		{
			auto start = sc.now();     // устанавливаем начало отсчета времени события
			index = getNth_list_value(list, value);
			deleteNth(list, index);
			auto end = sc.now();       // устанавливаем конец отсчета времени события

			auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
			cout << "Скорость удаления элемента списка равна: " << time_span.count() << " секунд" << endl;

			if (!list->size)
			{
				fl_list_create = FALSE;
				cout << "Все элементы списка были удалены! Необходимо заново создать список." << endl;
			}
			else
			{
				cout << "Полученный список: ";
				printDblLinkedList(list);
			}
			cout << "Нажмите любую клавишу" << endl;
			_getch();
			submenu_list(list, arr, arr_size); // возращаемся в подменю
		}
	}
	else
	{
		cout << "Введите позицию, значение которой необходимо получить от 0 до " << list->size - 1 << ": ";
		index = checkdigit();
		if (!check_index(index, list->size - 1))
		{
			cout << "Значение выходит за рамки диапазона. Нажмите любую клавишу, чтобы попробовать снова." << endl;
			_getch();
			deleteNth_list(list, arr, arr_size, fl_del_list);
		}
		auto start = sc.now();     // устанавливаем начало отсчета времени события
		deleteNth(list, index);
		auto end = sc.now();       // устанавливаем конец отсчета времени события
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
		cout << "Скорость удаления элемента списка равна: " << time_span.count() << " секунд" << endl;

		if (!list->size)
		{
			fl_list_create = FALSE;
			cout << "Все элементы списка были удалены! Необходимо заново создать список." << endl;
		}
		else
		{
			cout << "Полученный список: ";
			printDblLinkedList(list);
		}
		cout << "Нажмите любую клавишу" << endl;
		_getch();
		submenu_list(list, arr, arr_size); // возращаемся в подменю
	}
}

void printDblLinkedList(DblLinkedList* list) // вывод списка
{
	Node* tmp = list->head;

	while (tmp)
	{
		cout << tmp->value << " ";
		tmp = tmp->next;
	}
	cout << endl;
}

void trans(DblLinkedList* list, int first, int second) // обмен элементами (не использовался, но придуман)
{
	Node* elm1 = NULL;
	Node* elm2 = NULL;

	elm1 = getNth_list_index(list, first);
	int first_data = elm1->value;
	elm2 = getNth_list_index(list, second);
	int second_data = elm2->value;

	if (first == 0)
		pushFront(list, second_data);
	else
		insert(list, first - 1, second_data);

	deleteNth(list, first + 1);
	if (second == 0)
		pushFront(list, first_data);
	else
		insert(list, second - 1, first_data);
	deleteNth(list, second + 1);

}

///////////////////////////// DBLINKEDLIST///////////////

//////////////////////////// ARRAY /////////////////////

void printArray(const int* arr, const int size) // вывод массива
{
	for (int i = 0; i <= size - 1; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void printArray_index(const int* arr, const int size, const int index) // вывод массива с выделенным значением
{
	bool fl_stop = TRUE;

	for (int i = 0; i <= size - 1; i++)
	{
		if (i == index && fl_stop)
		{
			SetColor(2, 0);
			cout << arr[i] << " ";
			SetColor(7, 0);
			fl_stop = FALSE;
		}
		else
			cout << arr[i] << " ";
	}
	cout << endl;
}

void getNth_array(DblLinkedList* list, int* arr, int& arr_size, bool fl_array) // функция получения индекса или значения массива
{
	bool fl_stop = TRUE;
	system("cls"); // очищаем консоль
	chrono::steady_clock sc; 
	int value = 0;
	int index = 0;

	if (fl_array) // TRUE - ищем индекс. FALSE - ищем значение
	{
		cout << "Введите значение, позицию которого необходимо получить: ";
		value = checkdigit();
		auto start = sc.now();     // устанавливаем начало отсчета времени события
		while (fl_stop && index <= arr_size - 1)
		{
			if (value == arr[index])
				fl_stop = FALSE;
			else
				index++;
		}
		if (index > arr_size - 1)
		{
			cout << "Такого значения нет. Нажмите любую клавишу, чтобы попробовать снова." << endl;
			_getch();
			submenu_array(list, arr, arr_size);
		}
		auto end = sc.now();       // устанавливаем конец отсчета времени события
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
		cout << "Скорость поиска элемента массива равна: " << time_span.count() << " секунд" << endl;
		cout << "Позиция значения " << value << ": " << index << endl;

		cout << "Полученный массив: ";
		printArray_index(arr, arr_size, index);
		cout << "Нажмите любую клавишу" << endl;
		_getch();
		submenu_array(list, arr, arr_size);
	}
	else
	{
		cout << "Введите позицию, значение которой необходимо получить (от 0 до " << arr_size -1 << "): ";
		index = checkdigit();
		if (!check_index(index, arr_size - 1))
		{
			cout << "Значение выходит за рамки диапазона. Нажмите любую клавишу, чтобы попробовать снова." << endl;
			_getch();
			getNth_array(list, arr, arr_size, fl_array);
		}
		auto start = sc.now();     // устанавливаем начало отсчета времени события
		value = arr[index];
		auto end = sc.now();       // устанавливаем конец отсчета времени события
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
		cout << "Скорость поиска элемента массива равна: " << time_span.count() << " секунд" << endl;
		cout << "Значение позиции " << index << ": " << value << endl;

		cout << "Полученный массив: ";
		printArray_index(arr, arr_size, index);
		cout << "Нажмите любую клавишу" << endl;
		_getch();
		submenu_array(list, arr, arr_size);
	}
}

int* addtoArray(int *arr, int temp, int &size) // добавление элемента в конец массива
{
	int* newArray = new int [size + 1];

	for (int i = 0; i <= size - 1; i++)
	{
		newArray[i] = arr[i];
	}
	newArray[size] = temp;

	arr = newArray;
	return arr;
}

int* insert_value_ar(int* arr, int temp, int& size, int index) // вставка элемента в массив
{
	int* newArray = new int[size + 1];

	for (int i = 0; i <= index - 1; i++)
	{
		newArray[i] = arr[i];
	}
	newArray[index] = temp;
	for (int i = index + 1 ; i <= size; i++)
	{
		newArray[i] = arr[i - 1];
	}

	arr = newArray;
	size++;
	return arr;
}

void insert_array(DblLinkedList* list, int* arr, int& arr_size) // функция вставки элемента в массив
{
	system("cls"); // очищаем консоль
	chrono::steady_clock sc;
	int index;
	int value;

	printArray(arr, arr_size);
	cout << endl <<"Введите позицию нового значения от 0 до " << arr_size - 1 << ": ";
	index = checkdigit();
	if (!check_index(index, arr_size - 1))
	{
		cout << "Значение выходит за рамки диапазона. Нажмите любую клавишу, чтобы попробовать снова." << endl;
		_getch();
		insert_array(list, arr, arr_size);
	}
	cout << "Введите новое значение: ";
	value = checkdigit();
	auto start = sc.now();     // устанавливаем начало отсчета времени события
	if (index == arr_size - 1)
		index++;
	arr = insert_value_ar(arr, value, arr_size, index);
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	cout << "Скорость вставки элемента массива равна: " << time_span.count() << " секунд" << endl;

	cout << "Новый массив: ";
	printArray_index(arr, arr_size, index);
	cout << "Массив успешно обновлен. Нажмите любую клавишу" << endl;
	_getch();
	submenu_array(list, arr, arr_size);
}

int* delete_value_ar(int* arr, int& size, int index) // удаление элемента в массиве
{
	int* newArray = new int[size - 1];

	for (int i = 0; i <= index - 1; i++)
	{
		newArray[i] = arr[i];
	}
	for (int i = index; i <= size - 1 ; i++)
	{
		newArray[i] = arr[i + 1];
	}

	arr = newArray;
	size--;
	return arr;
}

void del_array(DblLinkedList* list, int* arr, int& arr_size, bool fl_del_array) // функция удаления элемента в массиве
{
	bool fl_stop = TRUE;
	system("cls"); // очищаем консоль
	chrono::steady_clock sc;
	int value = 0;
	int index = 0;

	cout << "Исходный массив: ";
	printArray(arr, arr_size);

	if (fl_del_array) // TRUE - удаляем по значению. FALSE - удаляем по индексу
	{
		cout << "Введите значение, которое будет удалено (удаление первого вхождения): ";
		value = checkdigit();
		auto start = sc.now();     // устанавливаем начало отсчета времени события
		while (fl_stop && index <= arr_size - 1)
		{
			if (value == arr[index])
				fl_stop = FALSE;
			else
				index++;
		}
		if (index > arr_size - 1)
		{
			cout << "Такого значения нет. Нажмите любую клавишу, чтобы попробовать снова." << endl;
			_getch();
			submenu_array(list, arr, arr_size);
		}
		arr = delete_value_ar(arr, arr_size, index);
		auto end = sc.now();       // устанавливаем конец отсчета времени события
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
		cout << "Скорость удаления элемента массива равна: " << time_span.count() << " секунд" << endl;


		if (!arr_size)
		{
			fl_array_create = FALSE;
			cout << "Все элементы массива были удалены! Необходимо заново создать массив." << endl;
		}
		else
		{
			cout << "Полученный массив: ";
			printArray(arr, arr_size);
		}
		cout << "Нажмите любую клавишу" << endl;
		_getch();
		submenu_array(list, arr, arr_size);
	}
	else
	{
		cout << "Введите позицию, значение которой необходимо удалить (от 0 до " << arr_size - 1 << "): ";
		index = checkdigit();
		if (!check_index(index, arr_size - 1))
		{
			cout << "Значение выходит за рамки диапазона. Нажмите любую клавишу, чтобы попробовать снова." << endl;
			_getch();
			del_array(list, arr, arr_size, fl_del_array);
		}
		auto start = sc.now();     // устанавливаем начало отсчета времени события
		arr = delete_value_ar(arr, arr_size, index);
		auto end = sc.now();       // устанавливаем конец отсчета времени события
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
		cout << "Скорость удаления элемента массива равна: " << time_span.count() << " секунд" << endl;

		if (!arr_size)
		{
			fl_array_create = FALSE;
			cout << "Все элементы массива были удалены! Необходимо заново создать массив." << endl;
		}
		else
		{
			cout << "Полученный массив: ";
			printArray(arr, arr_size);
		}
		cout << "Нажмите любую клавишу" << endl;
		_getch();
		submenu_array(list, arr, arr_size);
	}
}

//////////////////////////// ARRAY /////////////////////

//////////////////////////// FILL /////////////////////

void fill_array_random(DblLinkedList* list, int* arr, int& arr_size) // автоматическое заполнения массива
{
	system("cls"); // очищаем консоль
	int index = 0;
	chrono::steady_clock sc; 

	cout << "Введите размерность массива: ";
	arr_size = checkdigit();
	if (arr_size <= 0)
	{
		cout << "Размерность не может быть отрицательная или нулевая. Нажмите любую клавишу, чтобы продолжить.";
		_getch();
		submenu_array(list, arr, arr_size);
	}
	auto start = sc.now();     // устанавливаем начало отсчета времени события
	while (index <= arr_size)
	{
		int temp = rand() % 99;
		arr = addtoArray(arr, temp, index);
		index++;
	}
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	cout << "Скорость создания массива равна: " << time_span.count() << " секунд" << endl;

	cout << "Созднанный массив: ";
	printArray(arr, arr_size);
	cout << "Массив успешно создан. Нажмите любую клавишу" << endl;
	_getch();
	fl_array_create = TRUE;
	submenu_array(list, arr, arr_size);
}

void fill_array_self(DblLinkedList* list, int* arr, int& arr_size) // ручное заполнение массива
{
	system("cls"); // очищаем консоль
	int temp;
	int index = 0;
	chrono::steady_clock sc; 
	bool fl_stop = TRUE;

	cout << "Вводите числовые значения. Если хотите закончить, то введите любой нечисловой символ" << endl;
	auto start = sc.now();     // устанавливаем начало отсчета времени события
	while (fl_stop)
	{
		cout << index << ": ";
		cin >> temp; // число целое

		if (cin.fail()) // ecли предыдущее извелечение оказлось неудачным,
		{
			cin.clear(); // то возвращаем cin в обычный режим работы
			cin.ignore(32767, '\n'); // и удаляем из буфера значения предыдущего ввода 
			fl_stop = FALSE;
		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем из буфера значения предыдущего ввода 
			arr = addtoArray(arr, temp, arr_size);
			arr_size++;
		}
		index++;
	}
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	cout << "Скорость создания массива равна: " << time_span.count() << " секунд" << endl;

	cout << "Созднанный массив: ";
	printArray(arr, arr_size);
	cout << "Массив успешно создан. Нажмите любую клавишу" << endl;
	_getch();
	fl_array_create = TRUE;
	submenu_array(list, arr, arr_size);
}

void fill_array_from_file(DblLinkedList* list, int* arr, int& arr_size) // заполнение массива через файл
{
	system("cls"); // очищаем консоль
	ifstream fin;
	chrono::steady_clock sc; 

	fin.open("file_array.txt");
	auto start = sc.now();     // устанавливаем начало отсчета времени события
	if (fin.is_open()) // если файл удачно открыт
	{
		int temp = 0;
		while (!fin.eof()) // пока не дошли до конца файла
		{
			fin >> temp;
			if (fin.fail()) // ecли предыдущее извелечение оказлось неудачным,
			{
				fin.clear(); // то возвращаем cin в обычный режим работы
				fin.ignore(32767, '\n'); // и удаляем из буфера значения предыдущего ввода
				cout << "Файл содержит некорректные числовые данные. Необходимо закрыть программу и ввести в текстовый файл данные корректно (между числовыми значениями пробел, посторонних знаков быть не должно)." << endl;
				cout << "Пример: 50 -3 45 14 0 0 0 1" << endl;
				cout << "Нажмите, чтобы закрыть программу" << endl;
				_getch();
				exit(3);
			}
			else
			{
				arr = addtoArray(arr, temp, arr_size);
				arr_size++;
			}

		}
	}
	else
	{
		cout << "Файл открыть не удалось! Закройте программу и создайте в корневой папке программы файл file_array.txt для заполнения массива через файл." << endl;
		cout << "Нажмите, чтобы закрыть программу" << endl;
		_getch();
		exit(3);
	}
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	fin.close();
	cout << "Скорость создания массива равна: " << time_span.count() << " секунд" << endl;

	cout << "Созднанный массив: ";
	printArray(arr, arr_size);
	cout << "Массив успешно создан. Нажмите любую клавишу" << endl;
	_getch();
	fl_array_create = TRUE;
	submenu_array(list, arr, arr_size);
}

void fill_list_random(DblLinkedList* list, int* arr, int& arr_size) // автоматическое заполнение списка
{
	system("cls"); // очищаем консоль
	int size = 0;
	int index = 0;
	chrono::steady_clock sc;

	cout << "Введите размерность списка: ";
	size = checkdigit();
	if (size <= 0)
	{
		cout << "Размерность не может быть отрицательная или нулевая. Нажмите любую клавишу, чтобы продолжить.";
		_getch();
		submenu_list(list, arr, arr_size);
	}
	auto start = sc.now();     // устанавливаем начало отсчета времени события
	while (index <= size - 1)
	{
		int temp = rand() % 99;
		pushBack(list, temp);
		index++;
	}
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	cout << "Скорость создания списка равна: " << time_span.count() << " секунд" << endl;

	cout << "Созднанный список: ";
	printDblLinkedList(list);
	cout << "Список успешно создан. Нажмите любую клавишу" << endl;
	_getch();
	fl_list_create = TRUE;
	submenu_list(list, arr, arr_size);
}

void fill_list_self(DblLinkedList* list, int* arr, int& arr_size) // ручное заполнение списка
{
	system("cls"); // очищаем консоль
	int temp;
	int index = 0;
	chrono::steady_clock sc;
	bool fl_stop = TRUE;

	cout << "Вводите числовые значения. Если хотите закончить, то введите любой нечисловой символ" << endl;
	auto start = sc.now();     // устанавливаем начало отсчета времени события
	while (fl_stop)
	{
		cout << index << ": ";
		cin >> temp; // число целое

		if (cin.fail()) // ecли предыдущее извелечение оказлось неудачным,
		{
			cin.clear(); // то возвращаем cin в обычный режим работы
			cin.ignore(32767, '\n'); // и удаляем из буфера значения предыдущего ввода 
			fl_stop = FALSE;
		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем из буфера значения предыдущего ввода 
			pushBack(list, temp);
		}
		index++;
	}
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	cout << "Скорость создания списка равна: " << time_span.count() << " секунд" << endl;

	cout << "Созднанный список: ";
	printDblLinkedList(list);
	cout << "Список успешно создан. Нажмите любую клавишу" << endl;
	_getch();
	fl_list_create = TRUE;
	submenu_list(list, arr, arr_size);
}

void fill_list_from_file(DblLinkedList* list, int* arr, int& arr_size) // заполнение массива через файл
{
	system("cls"); // очищаем консоль
	ifstream fin;
	chrono::steady_clock sc;

	fin.open("file_list.txt");
	auto start = sc.now();     // устанавливаем начало отсчета времени события
	if (fin.is_open()) // если файл удачно открыт
	{
		int temp = 0;
		while (!fin.eof()) // пока не дошли до конца файла
		{
			fin >> temp;
			if (fin.fail()) // ecли предыдущее извелечение оказлось неудачным,
			{
				fin.clear(); // то возвращаем cin в обычный режим работы
				fin.ignore(32767, '\n'); // и удаляем из буфера значения предыдущего ввода
				cout << "Файл содержит некорректные числовые данные. Необходимо закрыть программу и ввести в текстовый файл данные корректно (между числовыми значениями пробел, посторонних знаков быть не должно)." << endl;
				cout << "Пример: 50 -3 45 14 0 0 0 1" << endl;
				cout << "Нажмите, чтобы закрыть программу" << endl;
				_getch();
				exit(3);
			}
			else
				pushBack(list, temp);
		}
	}
	else
	{
		cout << "Файл открыть не удалось! Закройте программу и создайте в корневой папке программы файл file_list.txt для заполнения списка через файл." << endl;
		cout << "Нажмите, чтобы закрыть программу" << endl;
		_getch();
		exit(3);
	}
	auto end = sc.now();       // устанавливаем конец отсчета времени события
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // высчитываем время, затраченное на событие
	fin.close();
	cout << "Скорость создания списка равна: " << time_span.count() << " секунд" << endl;

	cout << "Созднанный список: ";
	printDblLinkedList(list);
	cout << "Список успешно создан. Нажмите любую клавишу" << endl;
	_getch();
	fl_list_create = TRUE;
	submenu_list(list, arr, arr_size);
}

//////////////////////////// FILL /////////////////////

///////////////////////// VARIAT /////////////////////

void variant_work(DblLinkedList* list, int* arr, int& arr_size) // индивидуальное задание
{
	system("cls"); // очищаем консоль
	int temp;

	cout << "1. Необходимо увеличить каждое значение исходного двусвязного списка на случайное число (в диапазоне от 0 до 5):" << endl;
	cout << "Текущий список: ";
	printDblLinkedList(list);

	Node* tmp = list->head;

	while (tmp)
	{
		temp = rand() % 6;
		tmp->value = tmp->value + temp;
		tmp = tmp->next;
	}
	free(tmp);

	cout << "Обновленный список: ";
	printDblLinkedList(list);
	cout << endl << endl;


	cout << "2. Необходимо добавить в динамический массив все положительные элементы динамического массива:" << endl;
	cout << "Текущий массив: ";
	printArray(arr, arr_size);
	int current_arr_size = arr_size;
	for (int index = 0; index <= current_arr_size - 1; index++)
	{
		if (arr[index] >= 0)
		{
			arr = addtoArray(arr, arr[index], arr_size);
			arr_size++;
		}
	}

	cout << "Обновленный список: ";
	printArray(arr, arr_size);
	cout << "Задание выполнено! Нажмите любую клавишу" << endl;

	_getch();
	menu(list, arr, arr_size);
}

///////////////////////// VARIAT /////////////////////

///////////////////////// MENU ///////////////////

void subconf_array_delete_val(DblLinkedList* list, int* arr, int& arr_size)
{
	switch (subm_a_d_count)
	{
	case 0:
		del_array(list, arr, arr_size, TRUE);
		break;
	case 1:
		del_array(list, arr, arr_size, FALSE);
		break;
	case 2:
		submenu_array(list, arr, arr_size);
		break;
	default:
		break;
	}
}

void subconf_list_delete_val(DblLinkedList* list, int* arr, int& arr_size)
{
	switch (subm_l_d_count)
	{
	case 0:
		deleteNth_list(list, arr, arr_size, TRUE);
		break;
	case 1:
		deleteNth_list(list, arr, arr_size, FALSE);
		break;
	case 2:
		submenu_list(list, arr, arr_size);
		break;
	default:
		break;
	}
}

void subconf_array_search_val(DblLinkedList* list, int* arr, int& arr_size)
{
	switch (subm_a_s_count)
	{
	case 0:
		getNth_array(list, arr, arr_size, TRUE);
		break;
	case 1:
		getNth_array(list, arr, arr_size, FALSE);
		break;
	case 2:
		submenu_array(list, arr, arr_size);
		break;
	default:
		break;
	}
}

void subconf_list_search_val(DblLinkedList* list, int* arr, int& arr_size)
{
	switch (subm_l_s_count)
	{
	case 0:
		getNth_list(list, arr, arr_size, TRUE);
		break;
	case 1:
		getNth_list(list, arr, arr_size, FALSE);
		break;
	case 2:
		submenu_list(list, arr, arr_size);
		break;
	default:
		break;
	}
}

void subconf_array_create_val(DblLinkedList* list, int* arr, int& arr_size)
{
	switch (subm_a_c_count)
	{
	case 0:
		fill_array_random(list, arr, arr_size);
		break;
	case 1:
		fill_array_self(list, arr, arr_size);
		break;
	case 2:
		fill_array_from_file(list, arr, arr_size);
		break;
	case 3:
		submenu_array(list, arr, arr_size);
	default:
		break;
	}
}

void subconf_list_create_val(DblLinkedList* list, int* arr, int& arr_size)
{
	switch (subm_l_c_count)
	{
	case 0:
		fill_list_random(list, arr, arr_size);
		break;
	case 1:
		fill_list_self(list, arr, arr_size);
		break;
	case 2:
		fill_list_from_file(list, arr, arr_size);
		break;
	case 3:
		submenu_list(list, arr, arr_size);
	default:
		break;
	}
}

void subconf_list_val(DblLinkedList* list, int* arr, int& arr_size)
{
	switch (subm_l_count)
	{
	case 0:
		submenu_list_create(list, arr, arr_size);
		break;
	case 1:
		if (fl_list_create)
			insert_list(list, arr, arr_size);
		else
		{
			SetColor(4, 0);
			cout << endl << "Сперва необходимо создать список. Нажмите любую клавишу";
			SetColor(7, 0);
			_getch();
			submenu_list_create(list, arr, arr_size);
		}
		break;
	case 2:
		if (fl_list_create)
			submenu_list_delete(list, arr, arr_size);
		else
		{
			SetColor(4, 0);
			cout << endl << "Сперва необходимо создать список. Нажмите любую клавишу";
			SetColor(7, 0);
			_getch();
			submenu_list_create(list, arr, arr_size);
		}
		break;
	case 3:
		if (fl_list_create)
			submenu_list_search(list, arr, arr_size);
		else
		{
			SetColor(4, 0);
			cout << endl << "Сперва необходимо создать список. Нажмите любую клавишу";
			SetColor(7, 0);
			_getch();
			submenu_list_create(list, arr, arr_size);
		}
		break;
	case 4:
		menu(list, arr, arr_size);
	default:
		break;
	}
}

void subconf_array_val(DblLinkedList* list, int* arr, int& arr_size)
{
	switch (subm_a_count)
	{
	case 0:
		submenu_array_create(list, arr, arr_size);
		break;
	case 1:
		if (fl_array_create)
			insert_array(list, arr, arr_size);
		else
		{
			SetColor(4, 0);
			cout << endl << "Сперва необходимо создать массив. Нажмите любую клавишу";
			SetColor(7, 0);
			_getch();
			submenu_array_create(list, arr, arr_size);
		}
		break;
	case 2:
		if (fl_array_create)
			submenu_array_delete(list, arr, arr_size);
		else
		{
			SetColor(4, 0);
			cout << endl << "Сперва необходимо создать массив. Нажмите любую клавишу";
			SetColor(7, 0);
			_getch();
			submenu_array_create(list, arr, arr_size);
		}
		break;
	case 3:
		if (fl_array_create)
			submenu_array_search(list, arr, arr_size);
		else
		{
			SetColor(4, 0);
			cout << endl << "Сперва необходимо создать массив. Нажмите любую клавишу";
			SetColor(7, 0);
			_getch();
			submenu_array_create(list, arr, arr_size);
		}
		break;
	case 4:
		menu(list, arr, arr_size);
	default:
		break;
	}
}

void conf_val(DblLinkedList* list, int* arr, int& arr_size) // выбор после подтверждения в зависимости от значения текущего
{
	switch (m_count)
	{
	case 0:
		submenu_list(list, arr, arr_size);
		break;
	case 1:
		submenu_array(list, arr, arr_size);
		break;
	case 2:
		if (fl_array_create)
		{
			if (fl_list_create)
				variant_work(list, arr, arr_size);
			else
			{
				SetColor(4, 0);
				cout << endl << "Сперва необходимо создать список. Нажмите любую клавишу";
				SetColor(7, 0);
				_getch();
				submenu_list_create(list, arr, arr_size);
			}
		}
		else
		{
			SetColor(4, 0);
			cout << endl << "Сперва необходимо создать массив. Нажмите любую клавишу";
			SetColor(7, 0);
			_getch();
			submenu_array_create(list, arr, arr_size);
		}
		break;
	case 3:
		SetColor(0, 0);
		exit(0);
		break;
	default:
		break;
	}
}

void submenu_array_delete_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			subm_a_d_count--;
			if (subm_a_d_count < 0) subm_a_d_count = 0;
			submenu_array_delete(list, arr, arr_size);
			break;

		case 0x50: // стрелка вниз
			subm_a_d_count++;
			if (subm_a_d_count > 2) subm_a_d_count = 2;
			submenu_array_delete(list, arr, arr_size);
			break;
		case 0xD: // подтвердить
			subconf_array_delete_val(list, arr, arr_size);
			break;
		default:
			submenu_array_delete_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		subm_a_d_count--;
		if (subm_a_d_count < 0) subm_a_d_count = 0;
		submenu_array_delete(list, arr, arr_size);
		break;

	case 0x50: // стрелка вниз
		subm_a_d_count++;
		if (subm_a_d_count > 2) subm_a_d_count = 2;
		submenu_array_delete(list, arr, arr_size);
		break;
	case 0xD: // подтвердить
		subconf_array_delete_val(list, arr, arr_size);
		break;
	default:
		submenu_array_delete_choice(list, arr, arr_size);
	}
}

void submenu_list_delete_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			subm_l_d_count--;
			if (subm_l_d_count < 0) subm_l_d_count = 0;
			submenu_list_delete(list, arr, arr_size);
			break;

		case 0x50: // стрелка вниз
			subm_l_d_count++;
			if (subm_l_d_count > 2) subm_l_d_count = 2;
			submenu_list_delete(list, arr, arr_size);
			break;
		case 0xD: // подтвердить
			subconf_list_delete_val(list, arr, arr_size);
			break;
		default:
			submenu_list_delete_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		subm_l_d_count--;
		if (subm_l_d_count < 0) subm_l_d_count = 0;
		submenu_list_delete(list, arr, arr_size);
		break;

	case 0x50: // стрелка вниз
		subm_l_d_count++;
		if (subm_l_d_count > 2) subm_l_d_count = 2;
		submenu_list_delete(list, arr, arr_size);
		break;
	case 0xD: // подтвердить
		subconf_list_delete_val(list, arr, arr_size);
		break;
	default:
		submenu_list_delete_choice(list, arr, arr_size);
	}
}

void submenu_array_search_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			subm_a_s_count--;
			if (subm_a_s_count < 0) subm_a_s_count = 0;
			submenu_array_search(list, arr, arr_size);
			break;

		case 0x50: // стрелка вниз
			subm_a_s_count++;
			if (subm_a_s_count > 2) subm_a_s_count = 2;
			submenu_array_search(list, arr, arr_size);
			break;
		case 0xD: // подтвердить
			subconf_array_search_val(list, arr, arr_size);
			break;
		default:
			submenu_array_search_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		subm_a_s_count--;
		if (subm_a_s_count < 0) subm_a_s_count = 0;
		submenu_array_search(list, arr, arr_size);
		break;

	case 0x50: // стрелка вниз
		subm_a_s_count++;
		if (subm_a_s_count > 2) subm_a_s_count = 2;
		submenu_array_search(list, arr, arr_size);
		break;
	case 0xD: // подтвердить
		subconf_array_search_val(list, arr, arr_size);
		break;
	default:
		submenu_array_search_choice(list, arr, arr_size);
	}
}

void submenu_list_search_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			subm_l_s_count--;
			if (subm_l_s_count < 0) subm_l_s_count = 0;
			submenu_list_search(list, arr, arr_size);
			break;

		case 0x50: // стрелка вниз
			subm_l_s_count++;
			if (subm_l_s_count > 2) subm_l_s_count = 2;
			submenu_list_search(list, arr, arr_size);
			break;
		case 0xD: // подтвердить
			subconf_list_search_val(list, arr, arr_size);
			break;
		default:
			submenu_list_search_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		subm_l_s_count--;
		if (subm_l_s_count < 0) subm_l_s_count = 0;
		submenu_list_search(list, arr, arr_size);
		break;

	case 0x50: // стрелка вниз
		subm_l_s_count++;
		if (subm_l_s_count > 2) subm_l_s_count = 2;
		submenu_list_search(list, arr, arr_size);
		break;
	case 0xD: // подтвердить
		subconf_list_search_val(list, arr, arr_size);
		break;
	default:
		submenu_list_search_choice(list, arr, arr_size);
	}
}

void submenu_array_create_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			subm_a_c_count--;
			if (subm_a_c_count < 0) subm_a_c_count = 0;
			submenu_array_create(list, arr, arr_size);
			break;

		case 0x50: // стрелка вниз
			subm_a_c_count++;
			if (subm_a_c_count > 3) subm_a_c_count = 3;
			submenu_array_create(list, arr, arr_size);
			break;
		case 0xD: // подтвердить
			subconf_array_create_val(list, arr, arr_size);
			break;
		default:
			submenu_array_create_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		subm_a_c_count--;
		if (subm_a_c_count < 0) subm_a_c_count = 0;
		submenu_array_create(list, arr, arr_size);
		break;

	case 0x50: // стрелка вниз
		subm_a_c_count++;
		if (subm_a_c_count > 3) subm_a_c_count = 3;
		submenu_array_create(list, arr, arr_size);
		break;
	case 0xD: // подтвердить
		subconf_array_create_val(list, arr, arr_size);
		break;
	default:
		submenu_array_create_choice(list, arr, arr_size);
	}
}

void submenu_list_create_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			subm_l_c_count--;
			if (subm_l_c_count < 0) subm_l_c_count = 0;
			submenu_list_create(list, arr, arr_size);
			break;

		case 0x50: // стрелка вниз
			subm_l_c_count++;
			if (subm_l_c_count > 3) subm_l_c_count = 3;
			submenu_list_create(list, arr, arr_size);
			break;
		case 0xD: // подтвердить
			subconf_list_create_val(list, arr, arr_size);
			break;
		default:
			submenu_list_create_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		subm_l_c_count--;
		if (subm_l_c_count < 0) subm_l_c_count = 0;
		submenu_list_create(list, arr, arr_size);
		break;

	case 0x50: // стрелка вниз
		subm_l_c_count++;
		if (subm_l_c_count > 3) subm_l_c_count = 3;
		submenu_list_create(list, arr, arr_size);
		break;
	case 0xD: // подтвердить
		subconf_list_create_val(list, arr, arr_size);
		break;
	default:
		submenu_list_create_choice(list, arr, arr_size);
	}
}

void submenu_list_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			subm_l_count--;
			if (subm_l_count < 0) subm_l_count = 0;
			submenu_list(list, arr, arr_size);
			break;

		case 0x50: // стрелка вниз
			subm_l_count++;
			if (subm_l_count > 4) subm_l_count = 4;
			submenu_list(list, arr, arr_size);
			break;
		case 0xD: // подтвердить
			subconf_list_val(list, arr, arr_size);
			break;
		default:
			submenu_list_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		subm_l_count--;
		if (subm_l_count < 0) subm_l_count = 0;
		submenu_list(list, arr, arr_size);
		break;

	case 0x50: // стрелка вниз
		subm_l_count++;
		if (subm_l_count > 4) subm_l_count = 4;
		submenu_list(list, arr, arr_size);
		break;
	case 0xD: // подтвердить
		subconf_list_val(list, arr, arr_size);
		break;
	default:
		submenu_list_choice(list, arr, arr_size);
	}
}

void submenu_array_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			subm_a_count--;
			if (subm_a_count < 0) subm_a_count = 0;
			submenu_array(list, arr, arr_size);
			break;

		case 0x50: // стрелка вниз
			subm_a_count++;
			if (subm_a_count > 4) subm_a_count = 4;
			submenu_array(list, arr, arr_size);
			break;
		case 0xD: // подтвердить
			subconf_array_val(list, arr, arr_size);
			break;
		default:
			submenu_array_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		subm_a_count--;
		if (subm_a_count < 0) subm_a_count = 0;
		submenu_array(list, arr, arr_size);
		break;

	case 0x50: // стрелка вниз
		subm_a_count++;
		if (subm_a_count > 4) subm_a_count = 4;
		submenu_array(list, arr, arr_size);
		break;
	case 0xD: // подтвердить
		subconf_array_val(list, arr, arr_size);
		break;
	default:
		submenu_array_choice(list, arr, arr_size);
	}
}

void menu_choice(DblLinkedList* list, int* arr, int& arr_size) // в зависимости от стрелок изменяем меню
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			m_count--;
			if (m_count < 0) m_count = 0;
			menu(list, arr, arr_size);
			break;

		case 0x50: // стрелка вниз
			m_count++;
			if (m_count > 3) m_count = 3;
			menu(list, arr, arr_size);
			break;
		case 0xD: // подтвердить
			conf_val(list, arr, arr_size);
			break;
		default:
			menu_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		m_count--;
		if (m_count < 0) m_count = 0;
		menu(list, arr, arr_size);
		break;

	case 0x50: // стрелка вниз
		m_count++;
		if (m_count > 3) m_count = 3;
		menu(list, arr, arr_size);
		break;
	case 0xD: // подтвердить
		conf_val(list, arr, arr_size);
		break;
	default:
		menu_choice(list, arr, arr_size);
	}
}

void submenu_array_delete(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // очищаем консоль

	if (subm_a_d_count == 0)
	{
		cout.width(15);
		cout << right << "__Удаление элемента в динамическом массиве__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом удаляем элемент в массиве?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "По значению (первое вхождение)" << endl;
		SetColor(7, 0);
		cout << "По индексу" << endl;
		cout << "Назад" << endl;
		submenu_array_delete_choice(list, arr, arr_size);
	}
	if (subm_a_d_count == 1)
	{
		cout.width(15);
		cout << right << "__Удаление элемента в динамическом массиве__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом удаляем элемент в массиве?" << endl << endl;
		SetColor(7, 0);
		cout << "По значению (первое вхождение)" << endl;
		SetColor(5, 0);
		cout << "По индексу" << endl;
		SetColor(7, 0);
		cout << "Назад" << endl;
		submenu_array_delete_choice(list, arr, arr_size);
	}
	if (subm_a_d_count == 2)
	{
		cout.width(15);
		cout << right << "__Удаление элемента в динамическом массиве__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом удаляем элемент в массиве?" << endl << endl;
		SetColor(7, 0);
		cout << "По значению (первое вхождение)" << endl;
		cout << "По индексу" << endl;
		SetColor(5, 0);
		cout << "Назад" << endl;
		SetColor(7, 0);
		submenu_array_delete_choice(list, arr, arr_size);
	}
}

void submenu_list_delete(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // очищаем консоль

	if (subm_l_d_count == 0)
	{
		cout.width(15);
		cout << right << "__Удаление элемента в двусвязном списке__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом удаляем элемент в списке?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "По значению (первое вхождение)" << endl;
		SetColor(7, 0);
		cout << "По индексу" << endl;
		cout << "Назад" << endl;
		submenu_list_delete_choice(list, arr, arr_size);
	}
	if (subm_l_d_count == 1)
	{
		cout.width(15);
		cout << right << "__Удаление элемента в двусвязном списке__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом удаляем элемент в списке?" << endl << endl;
		SetColor(7, 0);
		cout << "По значению (первое вхождение)" << endl;
		SetColor(5, 0);
		cout << "По индексу" << endl;
		SetColor(7, 0);
		cout << "Назад" << endl;
		submenu_list_delete_choice(list, arr, arr_size);
	}
	if (subm_l_d_count == 2)
	{
		cout.width(15);
		cout << right << "__Удаление элемента в двусвязном списке__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом удаляем элемент в списке?" << endl << endl;
		SetColor(7, 0);
		cout << "По значению (первое вхождение)" << endl;
		cout << "По индексу" << endl;
		SetColor(5, 0);
		cout << "Назад" << endl;
		SetColor(7, 0);
		submenu_list_delete_choice(list, arr, arr_size);
	}
}

void submenu_array_search(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // очищаем консоль

	if (subm_a_s_count == 0)
	{
		cout.width(15);
		cout << right << "__Поиск элемента в динамическом массиве__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом ищем элемент в массиве?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "По значению (первое вхождение)" << endl;
		SetColor(7, 0);
		cout << "По индексу" << endl;
		cout << "Назад" << endl;
		submenu_array_search_choice(list, arr, arr_size);
	}
	if (subm_a_s_count == 1)
	{
		cout.width(15);
		cout << right << "__Поиск элемента в динамическом массиве__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом ищем элемент в массиве?" << endl << endl;
		SetColor(7, 0);
		cout << "По значению (первое вхождение)" << endl;
		SetColor(5, 0);
		cout << "По индексу" << endl;
		SetColor(7, 0);
		cout << "Назад" << endl;
		submenu_array_search_choice(list, arr, arr_size);
	}
	if (subm_a_s_count == 2)
	{
		cout.width(15);
		cout << right << "__Поиск элемента в динамическом массиве__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом ищем элемент в массиве?" << endl << endl;
		SetColor(7, 0);
		cout << "По значению (первое вхождение)" << endl;
		cout << "По индексу" << endl;
		SetColor(5, 0);
		cout << "Назад" << endl;
		SetColor(7, 0);
		submenu_array_search_choice(list, arr, arr_size);
	}
}

void submenu_list_search(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // очищаем консоль

	if (subm_l_s_count == 0)
	{
		cout.width(15);
		cout << right << "__Поиск элемента в двусвязном списке__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом ищем элемент в списке?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "По значению (первое вхождение)" << endl;
		SetColor(7, 0);
		cout << "По индексу" << endl;
		cout << "Назад" << endl;
		submenu_list_search_choice(list, arr, arr_size);
	}
	if (subm_l_s_count == 1)
	{
		cout.width(15);
		cout << right << "__Поиск элемента в двусвязном списке__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом ищем элемент в списке?" << endl << endl;
		SetColor(7, 0);
		cout << "По значению (первое вхождение)" << endl;
		SetColor(5, 0);
		cout << "По индексу" << endl;
		SetColor(7, 0);
		cout << "Назад" << endl;
		submenu_list_search_choice(list, arr, arr_size);
	}
	if (subm_l_s_count == 2)
	{
		cout.width(15);
		cout << right << "__Поиск элемента в двусвязном списке__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом ищем элемент в списке?" << endl << endl;
		SetColor(7, 0);
		cout << "По значению (первое вхождение)" << endl;
		cout << "По индексу" << endl;
		SetColor(5, 0);
		cout << "Назад" << endl;
		SetColor(7, 0);
		submenu_list_search_choice(list, arr, arr_size);
	}
}

void submenu_array_create(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // очищаем консоль

	if (subm_a_c_count == 0)
	{
		cout.width(15);
		cout << right << "__Создание динамического массива__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем динамический массив?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		SetColor(7, 0);
		cout << "Вручную, заполняя значения" << endl;
		cout << "Заполнение с помощью текстового файла" << endl;
		cout << "Назад" << endl;
		submenu_array_create_choice(list, arr, arr_size);
	}
	if (subm_a_c_count == 1)
	{
		cout.width(15);
		cout << right << "__Создание динамического массива__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем динамический массив?" << endl << endl;
		SetColor(7, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		SetColor(5, 0);
		cout << "Вручную, заполняя значения" << endl;
		SetColor(7, 0);
		cout << "Заполнение с помощью текстового файла" << endl;
		cout << "Назад" << endl;
		submenu_array_create_choice(list, arr, arr_size);
	}
	if (subm_a_c_count == 2)
	{
		cout.width(15);
		cout << right << "__Создание динамического массива__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем динамический массив?" << endl << endl;
		SetColor(7, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		cout << "Вручную, заполняя значения" << endl;
		SetColor(5, 0);
		cout << "Заполнение с помощью текстового файла" << endl;
		SetColor(7, 0);
		cout << "Назад" << endl;
		
		submenu_array_create_choice(list, arr, arr_size);
	}
	if (subm_a_c_count == 3)
	{
		cout.width(15);
		cout << right << "__Создание динамического массива__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем динамический массив?" << endl << endl;
		SetColor(7, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		cout << "Вручную, заполняя значения" << endl;
		cout << "Заполнение с помощью текстового файла" << endl;
		SetColor(5, 0);
		cout << "Назад" << endl;
		SetColor(7, 0);
		submenu_array_create_choice(list, arr, arr_size);
	}

}

void submenu_list_create(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // очищаем консоль

	if (subm_l_c_count == 0)
	{
		cout.width(15);
		cout << right << "__Создание двусвязного списка__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем двусвязный список?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		SetColor(7, 0);
		cout << "Вручную, заполняя значения" << endl;
		cout << "Заполнение с помощью текстового файла" << endl;
		cout << "Назад" << endl;
		submenu_list_create_choice(list, arr, arr_size);
	}
	if (subm_l_c_count == 1)
	{
		cout.width(15);
		cout << right << "__Создание двусвязного списка__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем двусвязный список?" << endl << endl;
		SetColor(7, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		SetColor(5, 0);
		cout << "Вручную, заполняя значения" << endl;
		SetColor(7, 0);
		cout << "Заполнение с помощью текстового файла" << endl;
		cout << "Назад" << endl;
		submenu_list_create_choice(list, arr, arr_size);
	}
	if (subm_l_c_count == 2)
	{
		cout.width(15);
		cout << right << "__Создание двусвязного списка__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем двусвязный список?" << endl << endl;
		SetColor(7, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		cout << "Вручную, заполняя значения" << endl;
		SetColor(5, 0);
		cout << "Заполнение с помощью текстового файла" << endl;
		SetColor(7, 0);
		cout << "Назад" << endl;
		submenu_list_create_choice(list, arr, arr_size);
	}
	if (subm_l_c_count == 3)
	{
		cout.width(15);
		cout << right << "__Создание двусвязного списка__" << endl << endl;
		SetColor(3, 0);
		cout << "Каким образом создаем двусвязный список?" << endl << endl;
		SetColor(7, 0);
		cout << "Автоматически, с указаной размерностью" << endl;
		cout << "Вручную, заполняя значения" << endl;
		cout << "Заполнение с помощью текстового файла" << endl;
		SetColor(5, 0);
		cout << "Назад" << endl;
		SetColor(7, 0);
		submenu_list_create_choice(list, arr, arr_size);
	}

}

void submenu_list(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // очищаем консоль

	if (subm_l_count == 0)
	{
		cout.width(15);
		cout << right << "__Двусвязный список__" << endl;
		SetColor(5, 0);
		cout << "Создать двусвязный список" << endl;
		SetColor(7, 0);
		cout << "Вставить элемент" << endl;
		cout << "Удалить элемент" << endl;
		cout << "Получить элемент" << endl;
		cout << "Назад" << endl;
		submenu_list_choice(list, arr, arr_size);
	}
	if (subm_l_count == 1)
	{
		cout.width(15);
		cout << right << "__Двусвязный список__" << endl;
		cout << "Создать двусвязный список" << endl;
		SetColor(5, 0);
		cout << "Вставить элемент" << endl;
		SetColor(7, 0);
		cout << "Удалить элемент" << endl;
		cout << "Получить элемент" << endl;
		cout << "Назад" << endl;
		submenu_list_choice(list, arr, arr_size);
	}
	if (subm_l_count == 2)
	{
		cout.width(15);
		cout << right << "__Двусвязный список__" << endl;
		cout << "Создать двусвязный список" << endl;
		cout << "Вставить элемент" << endl;
		SetColor(5, 0);
		cout << "Удалить элемент" << endl;
		SetColor(7, 0);
		cout << "Получить элемент" << endl;
		cout << "Назад" << endl;
		submenu_list_choice(list, arr, arr_size);
	}
	if (subm_l_count == 3)
	{
		cout.width(15);
		cout << right << "__Двусвязный список__" << endl;
		cout << "Создать двусвязный список" << endl;
		cout << "Вставить элемент" << endl;
		cout << "Удалить элемент" << endl;
		SetColor(5, 0);
		cout << "Получить элемент" << endl;
		SetColor(7, 0);
		cout << "Назад" << endl;
		submenu_list_choice(list, arr, arr_size);
	}
	if (subm_l_count == 4)
	{
		cout.width(15);
		cout << right << "__Двусвязный список__" << endl;
		cout << "Создать двусвязный список" << endl;
		cout << "Вставить элемент" << endl;
		cout << "Удалить элемент" << endl;
		cout << "Получить элемент" << endl;
		SetColor(5, 0);
		cout << "Назад" << endl;
		SetColor(7, 0);
		submenu_list_choice(list, arr, arr_size);
	}
}

void submenu_array(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // очищаем консоль

	if (subm_a_count == 0)
	{
		cout.width(15);
		cout << right << "__Динамический массив__" << endl;
		SetColor(5, 0);
		cout << "Создать динамический массив" << endl;
		SetColor(7, 0);
		cout << "Вставить элемент" << endl;
		cout << "Удалить элемент" << endl;
		cout << "Получить элемент" << endl;
		cout << "Назад" << endl;
		submenu_array_choice(list, arr, arr_size);
	}
	if (subm_a_count == 1)
	{
		cout.width(15);
		cout << right << "__Динамический массив__" << endl;
		cout << "Создать динамический массив" << endl;
		SetColor(5, 0);
		cout << "Вставить элемент" << endl;
		SetColor(7, 0);
		cout << "Удалить элемент" << endl;
		cout << "Получить элемент" << endl;
		cout << "Назад" << endl;
		submenu_array_choice(list, arr, arr_size);
	}
	if (subm_a_count == 2)
	{
		cout.width(15);
		cout << right << "__Динамический массив__" << endl;
		cout << "Создать динамический массив" << endl;
		cout << "Вставить элемент" << endl;
		SetColor(5, 0);
		cout << "Удалить элемент" << endl;
		SetColor(7, 0);
		cout << "Получить элемент" << endl;
		cout << "Назад" << endl;
		submenu_array_choice(list, arr, arr_size);
	}
	if (subm_a_count == 3)
	{
		cout.width(15);
		cout << right << "__Динамический массив__" << endl;
		cout << "Создать динамический массив" << endl;
		cout << "Вставить элемент" << endl;
		cout << "Удалить элемент" << endl;
		SetColor(5, 0);
		cout << "Получить элемент" << endl;
		SetColor(7, 0);
		cout << "Назад" << endl;
		submenu_array_choice(list, arr, arr_size);
	}
	if (subm_a_count == 4)
	{
		cout.width(15);
		cout << right << "__Динамический массив__" << endl;
		cout << "Создать динамический массив" << endl;
		cout << "Вставить элемент" << endl;
		cout << "Удалить элемент" << endl;
		cout << "Получить элемент" << endl;
		SetColor(5, 0);
		cout << "Назад" << endl;
		SetColor(7, 0);
		submenu_array_choice(list, arr, arr_size);
	}
}

void menu(DblLinkedList* list, int* arr, int &arr_size) // меню
{
	system("cls"); // очищаем консоль

	if (m_count == 0)
	{
		cout.width(15);
		cout << right << "__МЕНЮ__" << endl;
		SetColor(5, 0);
		cout << "Двусвязный список" << endl;
		SetColor(7, 0);
		cout << "Динамический массив" << endl;
		cout << "Задание по варианту" << endl;
		cout << "Выход" << endl;
		menu_choice(list, arr, arr_size);
	}
	if (m_count == 1)
	{
		cout.width(15);
		cout << right << "__МЕНЮ__" << endl;
		cout << "Двусвязный список" << endl;
		SetColor(5, 0);
		cout << "Динамический массив" << endl;
		SetColor(7, 0);
		cout << "Задание по варианту" << endl;
		cout << "Выход" << endl;
		menu_choice(list, arr, arr_size);
	}
	if (m_count == 2)
	{
		cout.width(15);
		cout << right << "__МЕНЮ__" << endl;
		cout << "Двусвязный список" << endl;
		cout << "Динамический массив" << endl;
		SetColor(5, 0);
		cout << "Задание по варианту" << endl;
		SetColor(7, 0);
		cout << "Выход" << endl;
		menu_choice(list, arr, arr_size);
	}
	if (m_count == 3)
	{
		cout.width(15);
		cout << right << "__МЕНЮ__" << endl;
		cout << "Двусвязный список" << endl;
		cout << "Динамический массив" << endl;
		cout << "Задание по варианту" << endl;
		SetColor(5, 0);
		cout << "Выход" << endl;
		SetColor(7, 0);
		menu_choice(list, arr, arr_size);
	}
}

///////////////////////// MENU ///////////////////

int main()
{
	setlocale(0, ""); // локализация 
	DblLinkedList* list = createDblLinkedList(); // создаем пустой список
	int size = 0;
	int* arr = (int*)malloc(size); // создаем пустой массив
	arr[0] = 0;

	srand(time(NULL));
	menu(list, arr, size);

	return 0;
}