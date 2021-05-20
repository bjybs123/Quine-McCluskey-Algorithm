#pragma once
#include <iostream>
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
	delete[] binary;
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
	bool sameState = false;
	product_node* tempLeft = leftNode;
	product_node* newNode = new product_node(bit_length);
	newNode->setBinary(leftNode->getBinary());			//비어있는 노드이기 때문에 처음 값을 임의로 왼쪽 product list에 1번째 곱의 항으로 초기화 해준다.
	leftNode = leftNode->getMultiNext();
	product_node* originTemp = newNode;
	while (leftNode)
	{
		product_node* newTemp = new product_node(bit_length);
		newTemp->setBinary(leftNode->getBinary());
		newNode->setMultiNext(newTemp);
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
		if (sameState == true)
		{
			rightNode = rightNode->getMultiNext();
			continue;
		}
		newNode->setMultiNext(newTemp);

		rightNode = rightNode->getMultiNext();
	}

	return originTemp;
}



class Product
{
private:
	product_node* head;

public:
	Product();
	void getBinaryToProduct(char*, unsigned short);
	product_node* getHead();
	void setHead(product_node* nodeIn);
	void distribute(Product*, Product*, unsigned short);
	void insert_plus(char*, unsigned short);
	void insert_multiplied_node(product_node*);
	void PrintProduct(void);
};


Product::Product()
{
	head = nullptr;
}
product_node* Product::getHead()
{
	return head;
}
void Product::getBinaryToProduct(char* inputbinary, unsigned short bit_length)
{
	return;
}
void Product::setHead(product_node* nodeIn)
{
	head = nodeIn;
}
void Product::insert_plus(char* binaryIn, unsigned short bit_length)
{
	product_node* newNode = new product_node(bit_length);
	newNode->setBinary(binaryIn);
	product_node* movingNode = head;
	if (head == nullptr)
	{
		head = newNode;
	}
	else
	{
		while (movingNode->getPlusNext())
		{
			movingNode = movingNode->getPlusNext();
		}
		movingNode->setPlusNext(newNode);
	}
}

void Product::distribute(Product* cmp1, Product* cmp2, unsigned short bit_length)
{
	Product* origin = this;
	product_node* moveNode1 = cmp1->getHead();
	product_node* moveNode2 = cmp2->getHead();
	
	if (moveNode1 == nullptr)
	{
		cout << "left side product is empty\n";
	}
	if (moveNode2 == nullptr)
	{
		cout << "right side product is empty\n";
	}

	while (moveNode1)	//좌측 product list 첫번째 항을 기준으로 분배 시작
	{
		while (moveNode2)
		{
			product_node* multipliedNode = nullptr;

			multipliedNode = multipliedNode->multiply(moveNode1, moveNode2, bit_length);
			
			insert_multiplied_node(multipliedNode);

			moveNode2 = moveNode2->getPlusNext();	//다음 더하기 항으로 이동
		}
		moveNode2 = cmp2->getHead();
		moveNode1 = moveNode1->getPlusNext();	//다음 더하기 항으로 이동
	}
}
void Product::insert_multiplied_node(product_node* nodeIn)				//have problem
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

void Product::PrintProduct(void)
{
	product_node* curTemp = getHead();

	while (curTemp != NULL)
	{
		product_node* curMultiTemp = curTemp;
		while (curMultiTemp != NULL)
		{
			cout << curMultiTemp->getBinary() << " | ";
			curMultiTemp = curMultiTemp->getMultiNext();
		}
		cout << " + ";
		curTemp = curTemp->getPlusNext();
	}
	cout << endl;

	return;
}