#include <iostream>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <chrono>
#include <Windows.h>
#include <iomanip>

using namespace std;
int m_count = 0; // ������� �������� ����
int subm_l_count = 0; // ������� ������� ������
int subm_a_count = 0; // ������� ������� �������
int subm_l_c_count = 0; // ������� ������� �������� ������
int subm_a_c_count = 0; // ������� ������� �������� �������
int subm_l_s_count = 0; // ������� ������� ������ �������� � ������
int subm_a_s_count = 0; // ������� ������� ������ �������� � �������
int subm_l_d_count = 0; // ������� ������� �������� �������� � ������
int subm_a_d_count = 0; // ������� ������� �������� �������� � �������

bool fl_array_create = FALSE; // ���� �������� �������
bool fl_list_create = FALSE; // ���� �������� ������

void SetColor(int text, int bg) //������� ����� �����, ������ �� ���������
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
void menu(DblLinkedList* list, int* arr, int& arr_size); // ����
void submenu_list(DblLinkedList* list, int* arr, int& arr_size); // ������� ������
void submenu_array(DblLinkedList* list, int* arr, int& arr_size); // ������� �������
void submenu_list_create(DblLinkedList* list, int* arr, int& arr_size); // ������� �������� ������
void submenu_array_create(DblLinkedList* list, int* arr, int& arr_size); // ������� �������� �������
void submenu_list_search(DblLinkedList* list, int* arr, int& arr_size); // ������� ������ �������� ������
void submenu_array_search(DblLinkedList* list, int* arr, int& arr_size); // ������� ������ �������� �������
void submenu_list_delete(DblLinkedList* list, int* arr, int& arr_size); // ������� �������� �������� ������
void submenu_array_delete(DblLinkedList* list, int* arr, int& arr_size); // ������� �������� �������� �������
void menu_choice(DblLinkedList* list, int* arr, int& arr_size); // ���������� ����
void submenu_list_choice(DblLinkedList* list, int* arr, int& arr_size); // ���������� ������� ������
void submenu_array_choice(DblLinkedList* list, int* arr, int& arr_size); // ���������� ������� �������
void submenu_list_create_choice(DblLinkedList* list, int* arr, int& arr_size); // ���������� ������� �������� ������
void submenu_array_create_choice(DblLinkedList* list, int* arr, int& arr_size); // ���������� ������� �������� �������
void submenu_list_search_choice(DblLinkedList* list, int* arr, int& arr_size); // ���������� ������� ������ �������� ������
void submenu_array_search_choice(DblLinkedList* list, int* arr, int& arr_size); // ���������� ������� ������ �������� �������
void submenu_list_delete_choice(DblLinkedList* list, int* arr, int& arr_size); // ���������� ������� �������� �������� ������
void submenu_array_delete_choice(DblLinkedList* list, int* arr, int& arr_size); // ���������� ������� �������� �������� �������
void printDblLinkedList(DblLinkedList* list); // ����� ������

///////////////////////// PROTOTYPES //////////////////////////

int checkdigit() // �������� �� ���������� ����
{
	while (true)
	{
		int value;
		// ������ �����, ������� ����� ����������� � �������� �����
		cin >> value; // ����� �����
		if (cin.fail()) // ec�� ���������� ����������� �������� ���������,
		{
			cin.clear(); // �� ���������� cin � ������� ����� ������
			cin.ignore(32767, '\n'); // � ������� �� ������ �������� ����������� ����� 
			cout << "������������ �������� �����. ������� ����� ���������" << '\n';
		}
		else
		{
			cin.ignore(32767, '\n'); // ������� �� ������ �������� ����������� ����� 
			return value;
		}
	}
}

bool check_index(int value, int size) // �������� ��������� � ��������
{
	if (value >= 0 && value <= size)
		return TRUE;
	else
		return FALSE;
}

///////////////////////////// DBLINKEDLIST///////////////

DblLinkedList* createDblLinkedList() // �������� ������
{
	DblLinkedList* tmp = (DblLinkedList*)malloc(sizeof(DblLinkedList));

	tmp->size = 0;
	tmp->head = tmp->tail = NULL;

	return tmp;
}

void pushFront(DblLinkedList* list, int data) // ���������� ���� � ������ ������
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

void pushBack(DblLinkedList* list, int value) // ���������� ���� � ����� ������
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

Node* getNth_list_index(DblLinkedList* list, size_t index) //��������� ���� �� �������
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

bool check_getNth_list_value(DblLinkedList* list, int value) // �������� ������������� �������� ���� � ������
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

int getNth_list_value(DblLinkedList* list, int value) // ��������� ������� �� �������� ����
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

void printDblLinkedList_index(DblLinkedList* list, int index) // ����� ������ � ���������� ���������
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

void getNth_list(DblLinkedList* list, int* arr, int& arr_size, bool fl_list) // ������� ��������� �������� ��� ������� ���� ������
{
	system("cls"); // ������� �������
	chrono::steady_clock sc;
	int value;
	int index;

	if (fl_list) // TRUE - ���� ������. FALSE - ���� ��������
	{
		cout << "������� ��������, ������� �������� ���������� ��������: ";
		value = checkdigit();
		if (!check_getNth_list_value(list, value))
		{
			cout << "������ �������� ���. ������� ����� �������, ����� ����������� �����." << endl;
			_getch();
			submenu_list(list, arr, arr_size);
		}
		else
		{
			auto start = sc.now();     // ������������� ������ ������� ������� �������
			index = getNth_list_value(list, value);
			auto end = sc.now();       // ������������� ����� ������� ������� �������

			auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
			cout << "�������� ������ �������� ������ �����: " << time_span.count() << " ������" << endl;
			cout << "������� �������� " << value << ": " << index << endl;

			cout << "���������� ������: ";
			printDblLinkedList_index(list, index);
			cout << "������� ����� �������" << endl;
			_getch();
			submenu_list(list, arr, arr_size); // ����������� � �������
		}
	}
	else
	{
		cout << "������� �������, �������� ������� ���������� �������� �� 0 �� " << list->size - 1 << ": ";
		index = checkdigit();
		if (!check_index(index, list->size - 1))
		{
			cout << "�������� ������� �� ����� ���������. ������� ����� �������, ����� ����������� �����." << endl;
			_getch();
			getNth_list(list, arr, arr_size, fl_list);
		}
		auto start = sc.now();     // ������������� ������ ������� ������� �������
		value = getNth_list_index(list, index)->value;
		auto end = sc.now();       // ������������� ����� ������� ������� �������
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
		cout << "�������� ������ �������� ������ �����: " << time_span.count() << " ������" << endl;
		cout << "�������� ������� " << index << ": " << value << endl;

		cout << "���������� ������: ";
		printDblLinkedList_index(list, index);
		cout << "������� ����� �������" << endl;
		_getch();
		submenu_list(list, arr, arr_size); // ����������� � �������
	}
}
 
void insert(DblLinkedList* list, size_t index, int value) // ������� ���� � ������
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
	system("cls"); // ������� �������
	chrono::steady_clock sc;  
	int index;
	int value;

	printDblLinkedList(list);
	cout << endl << "������� ������� ������ �������� �� 0 �� " << list->size - 1 << ": ";
	index = checkdigit();
	if (!check_index(index, list->size - 1))
	{
		cout << "�������� ������� �� ����� ���������. ������� ����� �������, ����� ����������� �����." << endl;
		_getch();
		insert_list(list, arr, arr_size);
	}

	cout << "������� ����� ��������: ";
	value = checkdigit();

	auto start = sc.now();     // ������������� ������ ������� ������� �������
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
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	cout << "�������� ������� �������� ������ �����: " << time_span.count() << " ������" << endl;

	cout << "����� ������: ";
	printDblLinkedList_index(list, index);
	cout << "������ ������� ��������. ������� ����� �������" << endl;
	_getch();
	submenu_list(list, arr, arr_size);
}

void deleteNth(DblLinkedList* list, size_t index) // �������� ���� �� ������
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

void deleteNth_list(DblLinkedList* list, int* arr, int& arr_size, bool fl_del_list) // ������� �������� ���� �� ������
{
	system("cls"); // ������� �������
	chrono::steady_clock sc;
	int value;
	int index;

	cout << "�������� ������: ";
	printDblLinkedList(list);

	if (fl_del_list) // TRUE - ������� �� ��������. FALSE - ������� �� �������
	{
		cout << "������� ��������, ������� ����� ������� (�������� ������� ���������): ";
		value = checkdigit();
		if (!check_getNth_list_value(list, value))
		{
			cout << "������ �������� ���. ������� ����� �������, ����� ����������� �����." << endl;
			_getch();
			submenu_list(list, arr, arr_size);
		}
		else
		{
			auto start = sc.now();     // ������������� ������ ������� ������� �������
			index = getNth_list_value(list, value);
			deleteNth(list, index);
			auto end = sc.now();       // ������������� ����� ������� ������� �������

			auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
			cout << "�������� �������� �������� ������ �����: " << time_span.count() << " ������" << endl;

			if (!list->size)
			{
				fl_list_create = FALSE;
				cout << "��� �������� ������ ���� �������! ���������� ������ ������� ������." << endl;
			}
			else
			{
				cout << "���������� ������: ";
				printDblLinkedList(list);
			}
			cout << "������� ����� �������" << endl;
			_getch();
			submenu_list(list, arr, arr_size); // ����������� � �������
		}
	}
	else
	{
		cout << "������� �������, �������� ������� ���������� �������� �� 0 �� " << list->size - 1 << ": ";
		index = checkdigit();
		if (!check_index(index, list->size - 1))
		{
			cout << "�������� ������� �� ����� ���������. ������� ����� �������, ����� ����������� �����." << endl;
			_getch();
			deleteNth_list(list, arr, arr_size, fl_del_list);
		}
		auto start = sc.now();     // ������������� ������ ������� ������� �������
		deleteNth(list, index);
		auto end = sc.now();       // ������������� ����� ������� ������� �������
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
		cout << "�������� �������� �������� ������ �����: " << time_span.count() << " ������" << endl;

		if (!list->size)
		{
			fl_list_create = FALSE;
			cout << "��� �������� ������ ���� �������! ���������� ������ ������� ������." << endl;
		}
		else
		{
			cout << "���������� ������: ";
			printDblLinkedList(list);
		}
		cout << "������� ����� �������" << endl;
		_getch();
		submenu_list(list, arr, arr_size); // ����������� � �������
	}
}

void printDblLinkedList(DblLinkedList* list) // ����� ������
{
	Node* tmp = list->head;

	while (tmp)
	{
		cout << tmp->value << " ";
		tmp = tmp->next;
	}
	cout << endl;
}

void trans(DblLinkedList* list, int first, int second) // ����� ���������� (�� �������������, �� ��������)
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

void printArray(const int* arr, const int size) // ����� �������
{
	for (int i = 0; i <= size - 1; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

void printArray_index(const int* arr, const int size, const int index) // ����� ������� � ���������� ���������
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

void getNth_array(DblLinkedList* list, int* arr, int& arr_size, bool fl_array) // ������� ��������� ������� ��� �������� �������
{
	bool fl_stop = TRUE;
	system("cls"); // ������� �������
	chrono::steady_clock sc; 
	int value = 0;
	int index = 0;

	if (fl_array) // TRUE - ���� ������. FALSE - ���� ��������
	{
		cout << "������� ��������, ������� �������� ���������� ��������: ";
		value = checkdigit();
		auto start = sc.now();     // ������������� ������ ������� ������� �������
		while (fl_stop && index <= arr_size - 1)
		{
			if (value == arr[index])
				fl_stop = FALSE;
			else
				index++;
		}
		if (index > arr_size - 1)
		{
			cout << "������ �������� ���. ������� ����� �������, ����� ����������� �����." << endl;
			_getch();
			submenu_array(list, arr, arr_size);
		}
		auto end = sc.now();       // ������������� ����� ������� ������� �������
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
		cout << "�������� ������ �������� ������� �����: " << time_span.count() << " ������" << endl;
		cout << "������� �������� " << value << ": " << index << endl;

		cout << "���������� ������: ";
		printArray_index(arr, arr_size, index);
		cout << "������� ����� �������" << endl;
		_getch();
		submenu_array(list, arr, arr_size);
	}
	else
	{
		cout << "������� �������, �������� ������� ���������� �������� (�� 0 �� " << arr_size -1 << "): ";
		index = checkdigit();
		if (!check_index(index, arr_size - 1))
		{
			cout << "�������� ������� �� ����� ���������. ������� ����� �������, ����� ����������� �����." << endl;
			_getch();
			getNth_array(list, arr, arr_size, fl_array);
		}
		auto start = sc.now();     // ������������� ������ ������� ������� �������
		value = arr[index];
		auto end = sc.now();       // ������������� ����� ������� ������� �������
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
		cout << "�������� ������ �������� ������� �����: " << time_span.count() << " ������" << endl;
		cout << "�������� ������� " << index << ": " << value << endl;

		cout << "���������� ������: ";
		printArray_index(arr, arr_size, index);
		cout << "������� ����� �������" << endl;
		_getch();
		submenu_array(list, arr, arr_size);
	}
}

int* addtoArray(int *arr, int temp, int &size) // ���������� �������� � ����� �������
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

int* insert_value_ar(int* arr, int temp, int& size, int index) // ������� �������� � ������
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

void insert_array(DblLinkedList* list, int* arr, int& arr_size) // ������� ������� �������� � ������
{
	system("cls"); // ������� �������
	chrono::steady_clock sc;
	int index;
	int value;

	printArray(arr, arr_size);
	cout << endl <<"������� ������� ������ �������� �� 0 �� " << arr_size - 1 << ": ";
	index = checkdigit();
	if (!check_index(index, arr_size - 1))
	{
		cout << "�������� ������� �� ����� ���������. ������� ����� �������, ����� ����������� �����." << endl;
		_getch();
		insert_array(list, arr, arr_size);
	}
	cout << "������� ����� ��������: ";
	value = checkdigit();
	auto start = sc.now();     // ������������� ������ ������� ������� �������
	if (index == arr_size - 1)
		index++;
	arr = insert_value_ar(arr, value, arr_size, index);
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	cout << "�������� ������� �������� ������� �����: " << time_span.count() << " ������" << endl;

	cout << "����� ������: ";
	printArray_index(arr, arr_size, index);
	cout << "������ ������� ��������. ������� ����� �������" << endl;
	_getch();
	submenu_array(list, arr, arr_size);
}

int* delete_value_ar(int* arr, int& size, int index) // �������� �������� � �������
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

void del_array(DblLinkedList* list, int* arr, int& arr_size, bool fl_del_array) // ������� �������� �������� � �������
{
	bool fl_stop = TRUE;
	system("cls"); // ������� �������
	chrono::steady_clock sc;
	int value = 0;
	int index = 0;

	cout << "�������� ������: ";
	printArray(arr, arr_size);

	if (fl_del_array) // TRUE - ������� �� ��������. FALSE - ������� �� �������
	{
		cout << "������� ��������, ������� ����� ������� (�������� ������� ���������): ";
		value = checkdigit();
		auto start = sc.now();     // ������������� ������ ������� ������� �������
		while (fl_stop && index <= arr_size - 1)
		{
			if (value == arr[index])
				fl_stop = FALSE;
			else
				index++;
		}
		if (index > arr_size - 1)
		{
			cout << "������ �������� ���. ������� ����� �������, ����� ����������� �����." << endl;
			_getch();
			submenu_array(list, arr, arr_size);
		}
		arr = delete_value_ar(arr, arr_size, index);
		auto end = sc.now();       // ������������� ����� ������� ������� �������
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
		cout << "�������� �������� �������� ������� �����: " << time_span.count() << " ������" << endl;


		if (!arr_size)
		{
			fl_array_create = FALSE;
			cout << "��� �������� ������� ���� �������! ���������� ������ ������� ������." << endl;
		}
		else
		{
			cout << "���������� ������: ";
			printArray(arr, arr_size);
		}
		cout << "������� ����� �������" << endl;
		_getch();
		submenu_array(list, arr, arr_size);
	}
	else
	{
		cout << "������� �������, �������� ������� ���������� ������� (�� 0 �� " << arr_size - 1 << "): ";
		index = checkdigit();
		if (!check_index(index, arr_size - 1))
		{
			cout << "�������� ������� �� ����� ���������. ������� ����� �������, ����� ����������� �����." << endl;
			_getch();
			del_array(list, arr, arr_size, fl_del_array);
		}
		auto start = sc.now();     // ������������� ������ ������� ������� �������
		arr = delete_value_ar(arr, arr_size, index);
		auto end = sc.now();       // ������������� ����� ������� ������� �������
		auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
		cout << "�������� �������� �������� ������� �����: " << time_span.count() << " ������" << endl;

		if (!arr_size)
		{
			fl_array_create = FALSE;
			cout << "��� �������� ������� ���� �������! ���������� ������ ������� ������." << endl;
		}
		else
		{
			cout << "���������� ������: ";
			printArray(arr, arr_size);
		}
		cout << "������� ����� �������" << endl;
		_getch();
		submenu_array(list, arr, arr_size);
	}
}

//////////////////////////// ARRAY /////////////////////

//////////////////////////// FILL /////////////////////

void fill_array_random(DblLinkedList* list, int* arr, int& arr_size) // �������������� ���������� �������
{
	system("cls"); // ������� �������
	int index = 0;
	chrono::steady_clock sc; 

	cout << "������� ����������� �������: ";
	arr_size = checkdigit();
	if (arr_size <= 0)
	{
		cout << "����������� �� ����� ���� ������������� ��� �������. ������� ����� �������, ����� ����������.";
		_getch();
		submenu_array(list, arr, arr_size);
	}
	auto start = sc.now();     // ������������� ������ ������� ������� �������
	while (index <= arr_size)
	{
		int temp = rand() % 99;
		arr = addtoArray(arr, temp, index);
		index++;
	}
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	cout << "�������� �������� ������� �����: " << time_span.count() << " ������" << endl;

	cout << "���������� ������: ";
	printArray(arr, arr_size);
	cout << "������ ������� ������. ������� ����� �������" << endl;
	_getch();
	fl_array_create = TRUE;
	submenu_array(list, arr, arr_size);
}

void fill_array_self(DblLinkedList* list, int* arr, int& arr_size) // ������ ���������� �������
{
	system("cls"); // ������� �������
	int temp;
	int index = 0;
	chrono::steady_clock sc; 
	bool fl_stop = TRUE;

	cout << "������� �������� ��������. ���� ������ ���������, �� ������� ����� ���������� ������" << endl;
	auto start = sc.now();     // ������������� ������ ������� ������� �������
	while (fl_stop)
	{
		cout << index << ": ";
		cin >> temp; // ����� �����

		if (cin.fail()) // ec�� ���������� ����������� �������� ���������,
		{
			cin.clear(); // �� ���������� cin � ������� ����� ������
			cin.ignore(32767, '\n'); // � ������� �� ������ �������� ����������� ����� 
			fl_stop = FALSE;
		}
		else
		{
			cin.ignore(32767, '\n'); // ������� �� ������ �������� ����������� ����� 
			arr = addtoArray(arr, temp, arr_size);
			arr_size++;
		}
		index++;
	}
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	cout << "�������� �������� ������� �����: " << time_span.count() << " ������" << endl;

	cout << "���������� ������: ";
	printArray(arr, arr_size);
	cout << "������ ������� ������. ������� ����� �������" << endl;
	_getch();
	fl_array_create = TRUE;
	submenu_array(list, arr, arr_size);
}

void fill_array_from_file(DblLinkedList* list, int* arr, int& arr_size) // ���������� ������� ����� ����
{
	system("cls"); // ������� �������
	ifstream fin;
	chrono::steady_clock sc; 

	fin.open("file_array.txt");
	auto start = sc.now();     // ������������� ������ ������� ������� �������
	if (fin.is_open()) // ���� ���� ������ ������
	{
		int temp = 0;
		while (!fin.eof()) // ���� �� ����� �� ����� �����
		{
			fin >> temp;
			if (fin.fail()) // ec�� ���������� ����������� �������� ���������,
			{
				fin.clear(); // �� ���������� cin � ������� ����� ������
				fin.ignore(32767, '\n'); // � ������� �� ������ �������� ����������� �����
				cout << "���� �������� ������������ �������� ������. ���������� ������� ��������� � ������ � ��������� ���� ������ ��������� (����� ��������� ���������� ������, ����������� ������ ���� �� ������)." << endl;
				cout << "������: 50 -3 45 14 0 0 0 1" << endl;
				cout << "�������, ����� ������� ���������" << endl;
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
		cout << "���� ������� �� �������! �������� ��������� � �������� � �������� ����� ��������� ���� file_array.txt ��� ���������� ������� ����� ����." << endl;
		cout << "�������, ����� ������� ���������" << endl;
		_getch();
		exit(3);
	}
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	fin.close();
	cout << "�������� �������� ������� �����: " << time_span.count() << " ������" << endl;

	cout << "���������� ������: ";
	printArray(arr, arr_size);
	cout << "������ ������� ������. ������� ����� �������" << endl;
	_getch();
	fl_array_create = TRUE;
	submenu_array(list, arr, arr_size);
}

void fill_list_random(DblLinkedList* list, int* arr, int& arr_size) // �������������� ���������� ������
{
	system("cls"); // ������� �������
	int size = 0;
	int index = 0;
	chrono::steady_clock sc;

	cout << "������� ����������� ������: ";
	size = checkdigit();
	if (size <= 0)
	{
		cout << "����������� �� ����� ���� ������������� ��� �������. ������� ����� �������, ����� ����������.";
		_getch();
		submenu_list(list, arr, arr_size);
	}
	auto start = sc.now();     // ������������� ������ ������� ������� �������
	while (index <= size - 1)
	{
		int temp = rand() % 99;
		pushBack(list, temp);
		index++;
	}
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	cout << "�������� �������� ������ �����: " << time_span.count() << " ������" << endl;

	cout << "���������� ������: ";
	printDblLinkedList(list);
	cout << "������ ������� ������. ������� ����� �������" << endl;
	_getch();
	fl_list_create = TRUE;
	submenu_list(list, arr, arr_size);
}

void fill_list_self(DblLinkedList* list, int* arr, int& arr_size) // ������ ���������� ������
{
	system("cls"); // ������� �������
	int temp;
	int index = 0;
	chrono::steady_clock sc;
	bool fl_stop = TRUE;

	cout << "������� �������� ��������. ���� ������ ���������, �� ������� ����� ���������� ������" << endl;
	auto start = sc.now();     // ������������� ������ ������� ������� �������
	while (fl_stop)
	{
		cout << index << ": ";
		cin >> temp; // ����� �����

		if (cin.fail()) // ec�� ���������� ����������� �������� ���������,
		{
			cin.clear(); // �� ���������� cin � ������� ����� ������
			cin.ignore(32767, '\n'); // � ������� �� ������ �������� ����������� ����� 
			fl_stop = FALSE;
		}
		else
		{
			cin.ignore(32767, '\n'); // ������� �� ������ �������� ����������� ����� 
			pushBack(list, temp);
		}
		index++;
	}
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	cout << "�������� �������� ������ �����: " << time_span.count() << " ������" << endl;

	cout << "���������� ������: ";
	printDblLinkedList(list);
	cout << "������ ������� ������. ������� ����� �������" << endl;
	_getch();
	fl_list_create = TRUE;
	submenu_list(list, arr, arr_size);
}

void fill_list_from_file(DblLinkedList* list, int* arr, int& arr_size) // ���������� ������� ����� ����
{
	system("cls"); // ������� �������
	ifstream fin;
	chrono::steady_clock sc;

	fin.open("file_list.txt");
	auto start = sc.now();     // ������������� ������ ������� ������� �������
	if (fin.is_open()) // ���� ���� ������ ������
	{
		int temp = 0;
		while (!fin.eof()) // ���� �� ����� �� ����� �����
		{
			fin >> temp;
			if (fin.fail()) // ec�� ���������� ����������� �������� ���������,
			{
				fin.clear(); // �� ���������� cin � ������� ����� ������
				fin.ignore(32767, '\n'); // � ������� �� ������ �������� ����������� �����
				cout << "���� �������� ������������ �������� ������. ���������� ������� ��������� � ������ � ��������� ���� ������ ��������� (����� ��������� ���������� ������, ����������� ������ ���� �� ������)." << endl;
				cout << "������: 50 -3 45 14 0 0 0 1" << endl;
				cout << "�������, ����� ������� ���������" << endl;
				_getch();
				exit(3);
			}
			else
				pushBack(list, temp);
		}
	}
	else
	{
		cout << "���� ������� �� �������! �������� ��������� � �������� � �������� ����� ��������� ���� file_list.txt ��� ���������� ������ ����� ����." << endl;
		cout << "�������, ����� ������� ���������" << endl;
		_getch();
		exit(3);
	}
	auto end = sc.now();       // ������������� ����� ������� ������� �������
	auto time_span = static_cast<chrono::duration<double>>(end - start);   // ����������� �����, ����������� �� �������
	fin.close();
	cout << "�������� �������� ������ �����: " << time_span.count() << " ������" << endl;

	cout << "���������� ������: ";
	printDblLinkedList(list);
	cout << "������ ������� ������. ������� ����� �������" << endl;
	_getch();
	fl_list_create = TRUE;
	submenu_list(list, arr, arr_size);
}

//////////////////////////// FILL /////////////////////

///////////////////////// VARIAT /////////////////////

void variant_work(DblLinkedList* list, int* arr, int& arr_size) // �������������� �������
{
	system("cls"); // ������� �������
	int temp;

	cout << "1. ���������� ��������� ������ �������� ��������� ����������� ������ �� ��������� ����� (� ��������� �� 0 �� 5):" << endl;
	cout << "������� ������: ";
	printDblLinkedList(list);

	Node* tmp = list->head;

	while (tmp)
	{
		temp = rand() % 6;
		tmp->value = tmp->value + temp;
		tmp = tmp->next;
	}
	free(tmp);

	cout << "����������� ������: ";
	printDblLinkedList(list);
	cout << endl << endl;


	cout << "2. ���������� �������� � ������������ ������ ��� ������������� �������� ������������� �������:" << endl;
	cout << "������� ������: ";
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

	cout << "����������� ������: ";
	printArray(arr, arr_size);
	cout << "������� ���������! ������� ����� �������" << endl;

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
			cout << endl << "������ ���������� ������� ������. ������� ����� �������";
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
			cout << endl << "������ ���������� ������� ������. ������� ����� �������";
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
			cout << endl << "������ ���������� ������� ������. ������� ����� �������";
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
			cout << endl << "������ ���������� ������� ������. ������� ����� �������";
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
			cout << endl << "������ ���������� ������� ������. ������� ����� �������";
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
			cout << endl << "������ ���������� ������� ������. ������� ����� �������";
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

void conf_val(DblLinkedList* list, int* arr, int& arr_size) // ����� ����� ������������� � ����������� �� �������� ��������
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
				cout << endl << "������ ���������� ������� ������. ������� ����� �������";
				SetColor(7, 0);
				_getch();
				submenu_list_create(list, arr, arr_size);
			}
		}
		else
		{
			SetColor(4, 0);
			cout << endl << "������ ���������� ������� ������. ������� ����� �������";
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
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) // ���� �������
	{
		switch (k1)
		{
		case 0x48: // ������� �����
			subm_a_d_count--;
			if (subm_a_d_count < 0) subm_a_d_count = 0;
			submenu_array_delete(list, arr, arr_size);
			break;

		case 0x50: // ������� ����
			subm_a_d_count++;
			if (subm_a_d_count > 2) subm_a_d_count = 2;
			submenu_array_delete(list, arr, arr_size);
			break;
		case 0xD: // �����������
			subconf_array_delete_val(list, arr, arr_size);
			break;
		default:
			submenu_array_delete_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // ������� �����
		subm_a_d_count--;
		if (subm_a_d_count < 0) subm_a_d_count = 0;
		submenu_array_delete(list, arr, arr_size);
		break;

	case 0x50: // ������� ����
		subm_a_d_count++;
		if (subm_a_d_count > 2) subm_a_d_count = 2;
		submenu_array_delete(list, arr, arr_size);
		break;
	case 0xD: // �����������
		subconf_array_delete_val(list, arr, arr_size);
		break;
	default:
		submenu_array_delete_choice(list, arr, arr_size);
	}
}

void submenu_list_delete_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) // ���� �������
	{
		switch (k1)
		{
		case 0x48: // ������� �����
			subm_l_d_count--;
			if (subm_l_d_count < 0) subm_l_d_count = 0;
			submenu_list_delete(list, arr, arr_size);
			break;

		case 0x50: // ������� ����
			subm_l_d_count++;
			if (subm_l_d_count > 2) subm_l_d_count = 2;
			submenu_list_delete(list, arr, arr_size);
			break;
		case 0xD: // �����������
			subconf_list_delete_val(list, arr, arr_size);
			break;
		default:
			submenu_list_delete_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // ������� �����
		subm_l_d_count--;
		if (subm_l_d_count < 0) subm_l_d_count = 0;
		submenu_list_delete(list, arr, arr_size);
		break;

	case 0x50: // ������� ����
		subm_l_d_count++;
		if (subm_l_d_count > 2) subm_l_d_count = 2;
		submenu_list_delete(list, arr, arr_size);
		break;
	case 0xD: // �����������
		subconf_list_delete_val(list, arr, arr_size);
		break;
	default:
		submenu_list_delete_choice(list, arr, arr_size);
	}
}

void submenu_array_search_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) // ���� �������
	{
		switch (k1)
		{
		case 0x48: // ������� �����
			subm_a_s_count--;
			if (subm_a_s_count < 0) subm_a_s_count = 0;
			submenu_array_search(list, arr, arr_size);
			break;

		case 0x50: // ������� ����
			subm_a_s_count++;
			if (subm_a_s_count > 2) subm_a_s_count = 2;
			submenu_array_search(list, arr, arr_size);
			break;
		case 0xD: // �����������
			subconf_array_search_val(list, arr, arr_size);
			break;
		default:
			submenu_array_search_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // ������� �����
		subm_a_s_count--;
		if (subm_a_s_count < 0) subm_a_s_count = 0;
		submenu_array_search(list, arr, arr_size);
		break;

	case 0x50: // ������� ����
		subm_a_s_count++;
		if (subm_a_s_count > 2) subm_a_s_count = 2;
		submenu_array_search(list, arr, arr_size);
		break;
	case 0xD: // �����������
		subconf_array_search_val(list, arr, arr_size);
		break;
	default:
		submenu_array_search_choice(list, arr, arr_size);
	}
}

void submenu_list_search_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) // ���� �������
	{
		switch (k1)
		{
		case 0x48: // ������� �����
			subm_l_s_count--;
			if (subm_l_s_count < 0) subm_l_s_count = 0;
			submenu_list_search(list, arr, arr_size);
			break;

		case 0x50: // ������� ����
			subm_l_s_count++;
			if (subm_l_s_count > 2) subm_l_s_count = 2;
			submenu_list_search(list, arr, arr_size);
			break;
		case 0xD: // �����������
			subconf_list_search_val(list, arr, arr_size);
			break;
		default:
			submenu_list_search_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // ������� �����
		subm_l_s_count--;
		if (subm_l_s_count < 0) subm_l_s_count = 0;
		submenu_list_search(list, arr, arr_size);
		break;

	case 0x50: // ������� ����
		subm_l_s_count++;
		if (subm_l_s_count > 2) subm_l_s_count = 2;
		submenu_list_search(list, arr, arr_size);
		break;
	case 0xD: // �����������
		subconf_list_search_val(list, arr, arr_size);
		break;
	default:
		submenu_list_search_choice(list, arr, arr_size);
	}
}

void submenu_array_create_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) // ���� �������
	{
		switch (k1)
		{
		case 0x48: // ������� �����
			subm_a_c_count--;
			if (subm_a_c_count < 0) subm_a_c_count = 0;
			submenu_array_create(list, arr, arr_size);
			break;

		case 0x50: // ������� ����
			subm_a_c_count++;
			if (subm_a_c_count > 3) subm_a_c_count = 3;
			submenu_array_create(list, arr, arr_size);
			break;
		case 0xD: // �����������
			subconf_array_create_val(list, arr, arr_size);
			break;
		default:
			submenu_array_create_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // ������� �����
		subm_a_c_count--;
		if (subm_a_c_count < 0) subm_a_c_count = 0;
		submenu_array_create(list, arr, arr_size);
		break;

	case 0x50: // ������� ����
		subm_a_c_count++;
		if (subm_a_c_count > 3) subm_a_c_count = 3;
		submenu_array_create(list, arr, arr_size);
		break;
	case 0xD: // �����������
		subconf_array_create_val(list, arr, arr_size);
		break;
	default:
		submenu_array_create_choice(list, arr, arr_size);
	}
}

void submenu_list_create_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) // ���� �������
	{
		switch (k1)
		{
		case 0x48: // ������� �����
			subm_l_c_count--;
			if (subm_l_c_count < 0) subm_l_c_count = 0;
			submenu_list_create(list, arr, arr_size);
			break;

		case 0x50: // ������� ����
			subm_l_c_count++;
			if (subm_l_c_count > 3) subm_l_c_count = 3;
			submenu_list_create(list, arr, arr_size);
			break;
		case 0xD: // �����������
			subconf_list_create_val(list, arr, arr_size);
			break;
		default:
			submenu_list_create_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // ������� �����
		subm_l_c_count--;
		if (subm_l_c_count < 0) subm_l_c_count = 0;
		submenu_list_create(list, arr, arr_size);
		break;

	case 0x50: // ������� ����
		subm_l_c_count++;
		if (subm_l_c_count > 3) subm_l_c_count = 3;
		submenu_list_create(list, arr, arr_size);
		break;
	case 0xD: // �����������
		subconf_list_create_val(list, arr, arr_size);
		break;
	default:
		submenu_list_create_choice(list, arr, arr_size);
	}
}

void submenu_list_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) // ���� �������
	{
		switch (k1)
		{
		case 0x48: // ������� �����
			subm_l_count--;
			if (subm_l_count < 0) subm_l_count = 0;
			submenu_list(list, arr, arr_size);
			break;

		case 0x50: // ������� ����
			subm_l_count++;
			if (subm_l_count > 4) subm_l_count = 4;
			submenu_list(list, arr, arr_size);
			break;
		case 0xD: // �����������
			subconf_list_val(list, arr, arr_size);
			break;
		default:
			submenu_list_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // ������� �����
		subm_l_count--;
		if (subm_l_count < 0) subm_l_count = 0;
		submenu_list(list, arr, arr_size);
		break;

	case 0x50: // ������� ����
		subm_l_count++;
		if (subm_l_count > 4) subm_l_count = 4;
		submenu_list(list, arr, arr_size);
		break;
	case 0xD: // �����������
		subconf_list_val(list, arr, arr_size);
		break;
	default:
		submenu_list_choice(list, arr, arr_size);
	}
}

void submenu_array_choice(DblLinkedList* list, int* arr, int& arr_size)
{
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) // ���� �������
	{
		switch (k1)
		{
		case 0x48: // ������� �����
			subm_a_count--;
			if (subm_a_count < 0) subm_a_count = 0;
			submenu_array(list, arr, arr_size);
			break;

		case 0x50: // ������� ����
			subm_a_count++;
			if (subm_a_count > 4) subm_a_count = 4;
			submenu_array(list, arr, arr_size);
			break;
		case 0xD: // �����������
			subconf_array_val(list, arr, arr_size);
			break;
		default:
			submenu_array_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // ������� �����
		subm_a_count--;
		if (subm_a_count < 0) subm_a_count = 0;
		submenu_array(list, arr, arr_size);
		break;

	case 0x50: // ������� ����
		subm_a_count++;
		if (subm_a_count > 4) subm_a_count = 4;
		submenu_array(list, arr, arr_size);
		break;
	case 0xD: // �����������
		subconf_array_val(list, arr, arr_size);
		break;
	default:
		submenu_array_choice(list, arr, arr_size);
	}
}

void menu_choice(DblLinkedList* list, int* arr, int& arr_size) // � ����������� �� ������� �������� ����
{
	int k1;
	k1 = _getch(); // �������� ������ ������� ��� ������ �����
	if (k1 == 0xE0) // ���� �������
	{
		switch (k1)
		{
		case 0x48: // ������� �����
			m_count--;
			if (m_count < 0) m_count = 0;
			menu(list, arr, arr_size);
			break;

		case 0x50: // ������� ����
			m_count++;
			if (m_count > 3) m_count = 3;
			menu(list, arr, arr_size);
			break;
		case 0xD: // �����������
			conf_val(list, arr, arr_size);
			break;
		default:
			menu_choice(list, arr, arr_size);
		}
	}
	switch (k1)
	{
	case 0x48: // ������� �����
		m_count--;
		if (m_count < 0) m_count = 0;
		menu(list, arr, arr_size);
		break;

	case 0x50: // ������� ����
		m_count++;
		if (m_count > 3) m_count = 3;
		menu(list, arr, arr_size);
		break;
	case 0xD: // �����������
		conf_val(list, arr, arr_size);
		break;
	default:
		menu_choice(list, arr, arr_size);
	}
}

void submenu_array_delete(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // ������� �������

	if (subm_a_d_count == 0)
	{
		cout.width(15);
		cout << right << "__�������� �������� � ������������ �������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������� � �������?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "�� �������� (������ ���������)" << endl;
		SetColor(7, 0);
		cout << "�� �������" << endl;
		cout << "�����" << endl;
		submenu_array_delete_choice(list, arr, arr_size);
	}
	if (subm_a_d_count == 1)
	{
		cout.width(15);
		cout << right << "__�������� �������� � ������������ �������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������� � �������?" << endl << endl;
		SetColor(7, 0);
		cout << "�� �������� (������ ���������)" << endl;
		SetColor(5, 0);
		cout << "�� �������" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		submenu_array_delete_choice(list, arr, arr_size);
	}
	if (subm_a_d_count == 2)
	{
		cout.width(15);
		cout << right << "__�������� �������� � ������������ �������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������� � �������?" << endl << endl;
		SetColor(7, 0);
		cout << "�� �������� (������ ���������)" << endl;
		cout << "�� �������" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		submenu_array_delete_choice(list, arr, arr_size);
	}
}

void submenu_list_delete(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // ������� �������

	if (subm_l_d_count == 0)
	{
		cout.width(15);
		cout << right << "__�������� �������� � ���������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������� � ������?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "�� �������� (������ ���������)" << endl;
		SetColor(7, 0);
		cout << "�� �������" << endl;
		cout << "�����" << endl;
		submenu_list_delete_choice(list, arr, arr_size);
	}
	if (subm_l_d_count == 1)
	{
		cout.width(15);
		cout << right << "__�������� �������� � ���������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������� � ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�� �������� (������ ���������)" << endl;
		SetColor(5, 0);
		cout << "�� �������" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		submenu_list_delete_choice(list, arr, arr_size);
	}
	if (subm_l_d_count == 2)
	{
		cout.width(15);
		cout << right << "__�������� �������� � ���������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������� � ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�� �������� (������ ���������)" << endl;
		cout << "�� �������" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		submenu_list_delete_choice(list, arr, arr_size);
	}
}

void submenu_array_search(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // ������� �������

	if (subm_a_s_count == 0)
	{
		cout.width(15);
		cout << right << "__����� �������� � ������������ �������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ���� ������� � �������?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "�� �������� (������ ���������)" << endl;
		SetColor(7, 0);
		cout << "�� �������" << endl;
		cout << "�����" << endl;
		submenu_array_search_choice(list, arr, arr_size);
	}
	if (subm_a_s_count == 1)
	{
		cout.width(15);
		cout << right << "__����� �������� � ������������ �������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ���� ������� � �������?" << endl << endl;
		SetColor(7, 0);
		cout << "�� �������� (������ ���������)" << endl;
		SetColor(5, 0);
		cout << "�� �������" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		submenu_array_search_choice(list, arr, arr_size);
	}
	if (subm_a_s_count == 2)
	{
		cout.width(15);
		cout << right << "__����� �������� � ������������ �������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ���� ������� � �������?" << endl << endl;
		SetColor(7, 0);
		cout << "�� �������� (������ ���������)" << endl;
		cout << "�� �������" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		submenu_array_search_choice(list, arr, arr_size);
	}
}

void submenu_list_search(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // ������� �������

	if (subm_l_s_count == 0)
	{
		cout.width(15);
		cout << right << "__����� �������� � ���������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ���� ������� � ������?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "�� �������� (������ ���������)" << endl;
		SetColor(7, 0);
		cout << "�� �������" << endl;
		cout << "�����" << endl;
		submenu_list_search_choice(list, arr, arr_size);
	}
	if (subm_l_s_count == 1)
	{
		cout.width(15);
		cout << right << "__����� �������� � ���������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ���� ������� � ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�� �������� (������ ���������)" << endl;
		SetColor(5, 0);
		cout << "�� �������" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		submenu_list_search_choice(list, arr, arr_size);
	}
	if (subm_l_s_count == 2)
	{
		cout.width(15);
		cout << right << "__����� �������� � ���������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ���� ������� � ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�� �������� (������ ���������)" << endl;
		cout << "�� �������" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		submenu_list_search_choice(list, arr, arr_size);
	}
}

void submenu_array_create(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // ������� �������

	if (subm_a_c_count == 0)
	{
		cout.width(15);
		cout << right << "__�������� ������������� �������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������������ ������?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "�������������, � �������� ������������" << endl;
		SetColor(7, 0);
		cout << "�������, �������� ��������" << endl;
		cout << "���������� � ������� ���������� �����" << endl;
		cout << "�����" << endl;
		submenu_array_create_choice(list, arr, arr_size);
	}
	if (subm_a_c_count == 1)
	{
		cout.width(15);
		cout << right << "__�������� ������������� �������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������������ ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�������������, � �������� ������������" << endl;
		SetColor(5, 0);
		cout << "�������, �������� ��������" << endl;
		SetColor(7, 0);
		cout << "���������� � ������� ���������� �����" << endl;
		cout << "�����" << endl;
		submenu_array_create_choice(list, arr, arr_size);
	}
	if (subm_a_c_count == 2)
	{
		cout.width(15);
		cout << right << "__�������� ������������� �������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������������ ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�������������, � �������� ������������" << endl;
		cout << "�������, �������� ��������" << endl;
		SetColor(5, 0);
		cout << "���������� � ������� ���������� �����" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		
		submenu_array_create_choice(list, arr, arr_size);
	}
	if (subm_a_c_count == 3)
	{
		cout.width(15);
		cout << right << "__�������� ������������� �������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ������������ ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�������������, � �������� ������������" << endl;
		cout << "�������, �������� ��������" << endl;
		cout << "���������� � ������� ���������� �����" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		submenu_array_create_choice(list, arr, arr_size);
	}

}

void submenu_list_create(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // ������� �������

	if (subm_l_c_count == 0)
	{
		cout.width(15);
		cout << right << "__�������� ����������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ���������� ������?" << endl << endl;
		SetColor(7, 0);
		SetColor(5, 0);
		cout << "�������������, � �������� ������������" << endl;
		SetColor(7, 0);
		cout << "�������, �������� ��������" << endl;
		cout << "���������� � ������� ���������� �����" << endl;
		cout << "�����" << endl;
		submenu_list_create_choice(list, arr, arr_size);
	}
	if (subm_l_c_count == 1)
	{
		cout.width(15);
		cout << right << "__�������� ����������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ���������� ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�������������, � �������� ������������" << endl;
		SetColor(5, 0);
		cout << "�������, �������� ��������" << endl;
		SetColor(7, 0);
		cout << "���������� � ������� ���������� �����" << endl;
		cout << "�����" << endl;
		submenu_list_create_choice(list, arr, arr_size);
	}
	if (subm_l_c_count == 2)
	{
		cout.width(15);
		cout << right << "__�������� ����������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ���������� ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�������������, � �������� ������������" << endl;
		cout << "�������, �������� ��������" << endl;
		SetColor(5, 0);
		cout << "���������� � ������� ���������� �����" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		submenu_list_create_choice(list, arr, arr_size);
	}
	if (subm_l_c_count == 3)
	{
		cout.width(15);
		cout << right << "__�������� ����������� ������__" << endl << endl;
		SetColor(3, 0);
		cout << "����� ������� ������� ���������� ������?" << endl << endl;
		SetColor(7, 0);
		cout << "�������������, � �������� ������������" << endl;
		cout << "�������, �������� ��������" << endl;
		cout << "���������� � ������� ���������� �����" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		submenu_list_create_choice(list, arr, arr_size);
	}

}

void submenu_list(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // ������� �������

	if (subm_l_count == 0)
	{
		cout.width(15);
		cout << right << "__���������� ������__" << endl;
		SetColor(5, 0);
		cout << "������� ���������� ������" << endl;
		SetColor(7, 0);
		cout << "�������� �������" << endl;
		cout << "������� �������" << endl;
		cout << "�������� �������" << endl;
		cout << "�����" << endl;
		submenu_list_choice(list, arr, arr_size);
	}
	if (subm_l_count == 1)
	{
		cout.width(15);
		cout << right << "__���������� ������__" << endl;
		cout << "������� ���������� ������" << endl;
		SetColor(5, 0);
		cout << "�������� �������" << endl;
		SetColor(7, 0);
		cout << "������� �������" << endl;
		cout << "�������� �������" << endl;
		cout << "�����" << endl;
		submenu_list_choice(list, arr, arr_size);
	}
	if (subm_l_count == 2)
	{
		cout.width(15);
		cout << right << "__���������� ������__" << endl;
		cout << "������� ���������� ������" << endl;
		cout << "�������� �������" << endl;
		SetColor(5, 0);
		cout << "������� �������" << endl;
		SetColor(7, 0);
		cout << "�������� �������" << endl;
		cout << "�����" << endl;
		submenu_list_choice(list, arr, arr_size);
	}
	if (subm_l_count == 3)
	{
		cout.width(15);
		cout << right << "__���������� ������__" << endl;
		cout << "������� ���������� ������" << endl;
		cout << "�������� �������" << endl;
		cout << "������� �������" << endl;
		SetColor(5, 0);
		cout << "�������� �������" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		submenu_list_choice(list, arr, arr_size);
	}
	if (subm_l_count == 4)
	{
		cout.width(15);
		cout << right << "__���������� ������__" << endl;
		cout << "������� ���������� ������" << endl;
		cout << "�������� �������" << endl;
		cout << "������� �������" << endl;
		cout << "�������� �������" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		submenu_list_choice(list, arr, arr_size);
	}
}

void submenu_array(DblLinkedList* list, int* arr, int& arr_size)
{
	system("cls"); // ������� �������

	if (subm_a_count == 0)
	{
		cout.width(15);
		cout << right << "__������������ ������__" << endl;
		SetColor(5, 0);
		cout << "������� ������������ ������" << endl;
		SetColor(7, 0);
		cout << "�������� �������" << endl;
		cout << "������� �������" << endl;
		cout << "�������� �������" << endl;
		cout << "�����" << endl;
		submenu_array_choice(list, arr, arr_size);
	}
	if (subm_a_count == 1)
	{
		cout.width(15);
		cout << right << "__������������ ������__" << endl;
		cout << "������� ������������ ������" << endl;
		SetColor(5, 0);
		cout << "�������� �������" << endl;
		SetColor(7, 0);
		cout << "������� �������" << endl;
		cout << "�������� �������" << endl;
		cout << "�����" << endl;
		submenu_array_choice(list, arr, arr_size);
	}
	if (subm_a_count == 2)
	{
		cout.width(15);
		cout << right << "__������������ ������__" << endl;
		cout << "������� ������������ ������" << endl;
		cout << "�������� �������" << endl;
		SetColor(5, 0);
		cout << "������� �������" << endl;
		SetColor(7, 0);
		cout << "�������� �������" << endl;
		cout << "�����" << endl;
		submenu_array_choice(list, arr, arr_size);
	}
	if (subm_a_count == 3)
	{
		cout.width(15);
		cout << right << "__������������ ������__" << endl;
		cout << "������� ������������ ������" << endl;
		cout << "�������� �������" << endl;
		cout << "������� �������" << endl;
		SetColor(5, 0);
		cout << "�������� �������" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		submenu_array_choice(list, arr, arr_size);
	}
	if (subm_a_count == 4)
	{
		cout.width(15);
		cout << right << "__������������ ������__" << endl;
		cout << "������� ������������ ������" << endl;
		cout << "�������� �������" << endl;
		cout << "������� �������" << endl;
		cout << "�������� �������" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		submenu_array_choice(list, arr, arr_size);
	}
}

void menu(DblLinkedList* list, int* arr, int &arr_size) // ����
{
	system("cls"); // ������� �������

	if (m_count == 0)
	{
		cout.width(15);
		cout << right << "__����__" << endl;
		SetColor(5, 0);
		cout << "���������� ������" << endl;
		SetColor(7, 0);
		cout << "������������ ������" << endl;
		cout << "������� �� ��������" << endl;
		cout << "�����" << endl;
		menu_choice(list, arr, arr_size);
	}
	if (m_count == 1)
	{
		cout.width(15);
		cout << right << "__����__" << endl;
		cout << "���������� ������" << endl;
		SetColor(5, 0);
		cout << "������������ ������" << endl;
		SetColor(7, 0);
		cout << "������� �� ��������" << endl;
		cout << "�����" << endl;
		menu_choice(list, arr, arr_size);
	}
	if (m_count == 2)
	{
		cout.width(15);
		cout << right << "__����__" << endl;
		cout << "���������� ������" << endl;
		cout << "������������ ������" << endl;
		SetColor(5, 0);
		cout << "������� �� ��������" << endl;
		SetColor(7, 0);
		cout << "�����" << endl;
		menu_choice(list, arr, arr_size);
	}
	if (m_count == 3)
	{
		cout.width(15);
		cout << right << "__����__" << endl;
		cout << "���������� ������" << endl;
		cout << "������������ ������" << endl;
		cout << "������� �� ��������" << endl;
		SetColor(5, 0);
		cout << "�����" << endl;
		SetColor(7, 0);
		menu_choice(list, arr, arr_size);
	}
}

///////////////////////// MENU ///////////////////

int main()
{
	setlocale(0, ""); // ����������� 
	DblLinkedList* list = createDblLinkedList(); // ������� ������ ������
	int size = 0;
	int* arr = (int*)malloc(size); // ������� ������ ������
	arr[0] = 0;

	srand(time(NULL));
	menu(list, arr, size);

	return 0;
}