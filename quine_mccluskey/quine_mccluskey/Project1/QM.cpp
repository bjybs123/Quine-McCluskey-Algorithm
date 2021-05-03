#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

struct Data			//비트 데이터 저장 구조체
{
public:
	bool check = false;
	char* binary;
	unsigned short int one_num = 0;

	Data* link;
};

unsigned short int Ones_number(const char*);		//1의 갯수 확인 함수
void AddNode(Data**, unsigned int, char*);		//노드 추가 함수
void FileToData(Data**, Data**, unsigned short int&);
void PrintNode(Data* head);		//노드 출럭 함수
void CompareBinary(Data**, Data*, Data*, unsigned short int);
void compareGroup(Data** insert, Data* group1, Data* group2, unsigned short bit_length);

void compareGroup(Data** insert, Data* group1, Data* group2, unsigned short bit_length)
{
	Data* tempNode = group1;
	Data* compareNode = group2;
	int tempOneNum = tempNode->one_num;



	while (tempNode != nullptr && tempNode->one_num == tempOneNum)
	{
		while (compareNode != nullptr && (compareNode->one_num == tempOneNum + 1))
		{
			CompareBinary(insert, tempNode, compareNode, bit_length);
			compareNode = compareNode->link;
		}
		tempNode = tempNode->link;
	}
}


int main() 
{

	Data* allhead = NULL;
	Data* minhead = NULL;
	unsigned short int bit_length;		//bit의 수 + 1('\n')

	FileToData(&allhead, &minhead, bit_length);

	Data* PIHead = NULL;

	//Find(allhead, PIHead);
	compareGroup(&PIHead, allhead, minhead, 4);

	cout << "M+D" << endl;
	PrintNode(allhead);
	cout << "\nM" << endl;
	PrintNode(minhead);
	cout << "\nCompare" << endl;
	PrintNode(PIHead);
	return 0;
}

unsigned short int Ones_number(const char* binary)
{
	int count = 0;
	unsigned short int ones = 0;
	while (binary[count])
	{
		if (binary[count] == '1')
			++ones;
		++count;
	}
	return ones;
}

void AddNode(Data** head, unsigned int bit_length, char* input_binary) //Linked list 추가
{

	Data* temp = new Data;
	temp->binary = new char[bit_length];

	strcpy(temp->binary, input_binary);
	temp->one_num = Ones_number(input_binary);

	if ((*head == NULL))
	{		

		temp->link = *head;
		*head = temp;
	}
	else
	{
		Data* cur = *head;
		Data* next = cur->link;

		while (true)
		{
			if (strcmp(cur->binary, temp->binary) == 0)			// 같은 binary 가질 경우 현재 값 저장 안함
			{
				delete[] temp->binary;
				delete temp;
				return;
			}

			if (cur == *head)			//리스트 맨 앞에 저장되야 할 경우
			{
				if (cur->one_num > temp->one_num)
				{
					temp->link = cur;
					*head = temp;

					return;
				}
			}

			if (next == NULL)			//리스트 마지막에 저장되야 할 경우
			{
				cur->link = temp;
				temp->link = next;
			
				return;
			}

			if (temp->one_num < next->one_num)		//앞의 노드와 현재 노드 사이에 올 경우
			{
				cur->link = temp;
				temp->link = next;

				return;
			}

			cur = cur->link;
			next = cur->link;
		}
	}
}

void FileToData(Data **allhead, Data**minhead, unsigned short int& bit_length)	//파일로부터 데이터를 입력받는 함수
{
	ifstream fin;
	
	fin.open("input_minterm.txt");

	if (fin.fail())
	{
		cerr << "error\n";
		exit;
	}


	char* binary;
	char MorD;
	fin >> bit_length;
	bit_length++;
	binary = new char[bit_length];
	cout << "bit_length : " << bit_length-1 << "\n\n";

	while (!fin.eof())			//EOF까지 
	{
		fin >> MorD;
		fin >> binary;
		if (MorD == 'm')
		{
			AddNode(allhead, bit_length, binary);
			AddNode(minhead, bit_length, binary);
		}
		else if (MorD == 'd')
		{
			AddNode(allhead, bit_length, binary);
		}

	}

	delete[] binary;

	fin.close(); // 파일 닫기

	return;
}

void PrintNode(Data* head)		//Linked list 출력
{
	Data* temp = head;

	while (temp != NULL)
	{
		cout << temp->binary << '\t' << temp->one_num << endl;
		temp = temp->link;
	}

	return;
}

void CompareBinary(Data** inputhead, Data* compare1, Data* compare2, unsigned short int bit_length)
{
	int dif = 0;
	char* result = new char[bit_length + 1];
	int i;
	for (i = 0; i < bit_length; i++)
	{
		if (compare1->binary[i] != compare2->binary[i])
		{
			if (compare1->binary[i] == '-' || compare2->binary[i] == '-')
			{
				delete[] result;
				return;
			}
			result[i] = '-';
			dif++;
		}
		else
		{
			result[i] = compare1->binary[i];
		}
	}
	result[i] = '\0';

	if (dif == 1)
	{
		AddNode(inputhead, bit_length, result);
		compare1->check = true;
		compare2->check = true;
	}
	delete[] result;
	return;
}