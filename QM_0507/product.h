#pragma once
#include <iostream>
#include <fstream>
using namespace std;

void my_strcpy(char* str1, char* str2)
{
	int i = 0;
	while (str2[i] != '\0')
	{
		str1[i] = str2[i];
		++i;
	}
	str1[i] = '\0';
	return;
}


bool isSame(char* str1, char* str2)
{
	int i = 0;
	int dif = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
		{
			if (str1[i] != '-' && str2[i] != '-')
				++dif;
		}
		++i;
	}
	return dif == 0 ? true : false;
}


class product_node
{
private:
	char* binary;
	product_node* plusNext;
	product_node* multiNext;

public:
	product_node(unsigned short);
	~product_node();
	void setBinary(char*);
	char* getBinary();
	void setPlusNext(product_node*);
	product_node* getPlusNext();
	void setMultiNext(product_node*);
	product_node* getMultiNext();
	void insert_multi(char*, unsigned short);
	product_node* multiply(product_node*, product_node*, unsigned short);
	void deleteMulti(void);
	void deletePlus(void);
	void PtoFile(int, unsigned short);
};


//prodeuct_node's method function

product_node::product_node(unsigned short bit_length)
{
	binary = new char[bit_length];
	plusNext = nullptr;
	multiNext = nullptr;
}
product_node::~product_node()
{

}
void product_node::setBinary(char* binaryIn)
{
	my_strcpy(binary, binaryIn);
}
char* product_node::getBinary()
{
	return binary;
}
void product_node::setPlusNext(product_node* nodeIn)
{
	plusNext = nodeIn;
}
product_node* product_node::getPlusNext()
{
	return plusNext;
}
void product_node::setMultiNext(product_node* nodeIn)
{
	multiNext = nodeIn;
}
product_node* product_node::getMultiNext()
{
	return multiNext;
}
void product_node::insert_multi(char* binaryIn, unsigned short bit_length)
{
	product_node* newNode = new product_node(bit_length);
	newNode->setBinary(binaryIn);

	product_node* movingNode = this;

	while (movingNode->getMultiNext())
	{
		movingNode = movingNode->getMultiNext();
	}
	movingNode->setMultiNext(newNode);
}

product_node* product_node::multiply(product_node* leftNode, product_node* rightNode, unsigned short bit_length)
{	

	//분배법칙을 적용할때 leftNode는 좌측에 있는 항 rightNode는 우측에 있는 항이라고 생각을 한다
	bool sameState = false;
	product_node* tempLeft = leftNode;
	product_node* newNode = new product_node(bit_length);
	newNode->setBinary(leftNode->getBinary());			//비어있는 노드이기 때문에 처음 값을 임의로 왼쪽 product list에 1번째 곱의 항으로 초기화 해준다.
	leftNode = leftNode->getMultiNext();
	product_node* originTemp = newNode;
	while (leftNode)				//먼저 좌측에 있는 항들을 새로운 노드(newNode)에 다 집어 넣어 준다
	{
		product_node* newTemp = new product_node(bit_length);
		newTemp->setBinary(leftNode->getBinary());		//newTemp노드를 새롭게 할당하고 binary값을 저장해준다
		newNode->setMultiNext(newTemp);					//
		leftNode = leftNode->getMultiNext();
		newNode = newNode->getMultiNext();
	}
	newNode = originTemp;
	while (rightNode)
	{
		sameState = false;
		product_node* newTemp = new product_node(bit_length);
		newTemp->setBinary(rightNode->getBinary());
		while (newNode->getMultiNext())
		{
			if (strcmp(newNode->getBinary(), rightNode->getBinary()) == 0)
				sameState = true;
				newNode = newNode->getMultiNext();
		}

		if (strcmp(newNode->getBinary(), rightNode->getBinary()) == 0)
			sameState = true;


		if (sameState == true)
		{
			rightNode = rightNode->getMultiNext();
			newTemp->deletePlus();
			delete newTemp;
			continue;
		}
		newNode->setMultiNext(newTemp);

		rightNode = rightNode->getMultiNext();
	}

	return originTemp;
}

void product_node::deleteMulti(void)
{
	delete[] binary;

	if (multiNext)
	{
		multiNext->deleteMulti();
		delete multiNext;
	}

	return;
}

void product_node::deletePlus(void)
{
	deleteMulti();

	if (plusNext)
	{
		plusNext->deletePlus();
		delete plusNext;
	}

	return;
}



void product_node::PtoFile(int trans, unsigned short bit_length)			//result.txt파일로 출력하기위한 메소드
{
	ofstream fout;
	product_node* curTemp = multiNext;
	fout.open("result.txt");

	fout.write(binary, bit_length-1);
	fout << endl;

	while (curTemp != NULL)
	{
		fout.write(curTemp->getBinary(), bit_length-1);
		fout << "\n";
		curTemp = curTemp->getMultiNext();
	}

	fout << "\nCost (# of transistors): ";
	fout <<  trans << endl;

	fout.close();

	return;
}


class Product
{
private:
	product_node* head;

public:
	Product();
	product_node* getHead();
	void setHead(product_node* nodeIn);
	void distribute(Product*, Product*, unsigned short);
	void insert_plus(char*, unsigned short);
	void insert_multiplied_node(product_node*);
	int isSameProduct(product_node*, product_node*);
	void DeleteSame(unsigned short);
};


Product::Product()
{
	head = nullptr;
}
product_node* Product::getHead()
{
	return head;
}
void Product::setHead(product_node* nodeIn)
{
	head = nodeIn;
}
void Product::insert_plus(char* binaryIn, unsigned short bit_length)
{
	product_node* newNode = new product_node(bit_length);		//2차원 링크드 리스트에서 더하기를 연결하는 리스트의 노드 생성
	newNode->setBinary(binaryIn);		//해당 노드에 binary를 저장
	product_node* movingNode = head;	
	if (head == nullptr)		//만약 head에 노드가 존재하지 않는다면 초기화
	{
		head = newNode;
	}
	else
	{
		while (movingNode->getPlusNext())
		{
			movingNode = movingNode->getPlusNext();
		}		//마지막 노드로 이동하여 다음 노드를 연결
		movingNode->setPlusNext(newNode);
	}
}

void Product::distribute(Product* cmp1, Product* cmp2, unsigned short bit_length)
{
	Product* origin = this;
	product_node* moveNode1 = cmp1->getHead();
	product_node* moveNode2 = cmp2->getHead();

	while (moveNode1)	//좌측 product list 첫번째 항을 기준으로 분배 시작
	{
		while (moveNode2)
		{
			product_node* multipliedNode = nullptr;

			multipliedNode = multipliedNode->multiply(moveNode1, moveNode2, bit_length);		// 두 항을 곱한다
			
			insert_multiplied_node(multipliedNode);				//곱해진 항을 곱한 노드로 연결시킨다 

			moveNode2 = moveNode2->getPlusNext();	//다음 더하기 항으로 이동
		}
		moveNode2 = cmp2->getHead();
		moveNode1 = moveNode1->getPlusNext();	//다음 더하기 항으로 이동
	}
	return;
}
void Product::insert_multiplied_node(product_node* nodeIn)
{
	product_node* movingNode = head;
	if (head == nullptr)
	{
		head = nodeIn;
	}
	else
	{
		while (movingNode->getPlusNext())
		{
			movingNode = movingNode->getPlusNext();
		}
		movingNode->setPlusNext(nodeIn);
	}
}

int Product::isSameProduct(product_node* head, product_node* compareHead)		//compareHead가 head에 포함되는지 검사
{
	product_node* compare1 = head;

	int count1 = 0;
	int count2 = 0;
	while (compare1)
	{
		product_node* compare2 = compareHead;
		int state = false;

		while (compare2)
		{
			if (strcmp(compare1->getBinary(), compare2->getBinary()) == 0)
			{
				state = true;
			}
			compare2 = compare2->getMultiNext();
			if (count1 == 0)
			{
				count2++;
			}
		}

		if (state == false)
		{
			return -1;
		}
		compare1 = compare1->getMultiNext();
		count1++;
	}
	
	if (count1 == count2)
	{
		return 0;
	}

	return 1;
}

void Product::DeleteSame(unsigned short bit_length)
{
	product_node* compare1Head = head;

	if (compare1Head == NULL || compare1Head->getPlusNext() == NULL)
	{
		return;
	}
	product_node* insertHead = NULL;
	product_node* insertTemp = insertHead;

	while (compare1Head)
	{
		product_node* compare2Head = head;

		bool state = false;

		while (compare2Head)
		{
			if (compare1Head != compare2Head)
			{
				if (isSameProduct(compare2Head, compare1Head) == 1)
				{
					state = true;
				}
			}
			compare2Head = compare2Head->getPlusNext();
		}
		if (state == false)
		{
			if (insertHead == NULL)
			{
				insertHead = new product_node(bit_length);
				insertTemp = insertHead;

				insertHead->setBinary(compare1Head->getBinary());

				product_node* temp = compare1Head->getMultiNext();
				while (temp)
				{
					product_node* insert = new product_node(bit_length);
					insertTemp->setMultiNext(insert);
					insert->setBinary(temp->getBinary());

					insertTemp = insertTemp->getMultiNext();
					temp = temp->getMultiNext();
				}
			}
			else
			{
				bool state2 = true;
				insertTemp = insertHead;
				while (insertTemp)
				{
					if (isSameProduct(insertTemp, compare1Head) == 0)
					{
						state2 = false;
					}
					
					insertTemp = insertTemp->getPlusNext();
				}


				if (state2 == true)
				{
					insertTemp = NULL;
					product_node* newPlus = insertHead;
					while (newPlus->getPlusNext())
					{
						newPlus = newPlus->getPlusNext();
					}
					insertTemp = new product_node(bit_length);
					newPlus->setPlusNext(insertTemp);

					insertTemp->setBinary(compare1Head->getBinary());

					product_node* temp = compare1Head->getMultiNext();
					while (temp)
					{
						product_node* insert = new product_node(bit_length);
						insertTemp->setMultiNext(insert);
						insert->setBinary(temp->getBinary());

						insertTemp = insertTemp->getMultiNext();
						temp = temp->getMultiNext();
					}
				}

			}

		}
		compare1Head = compare1Head->getPlusNext();
	}

	compare1Head = head;
	head = insertHead;
	compare1Head->deletePlus();
	delete compare1Head;



	return;
}
