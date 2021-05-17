#pragma once

#include <iostream>

using namespace std;



class Node
{
private:

	Node* next;
	int check;
	char* binary;
	unsigned short one_num;

public:
	Node();
	~Node();
	Node(unsigned short);
	Node* getNext();
	int getCheck();
	void setCheck(int);
	void setNext(Node* nextIn);
	char* getBinary();
	void setBinary(char*);
	unsigned short getOneNum();
	bool compareMinAndPI(Node*, unsigned short);

};

class Link
{
private:
	Node* pHead;
public:
	Link();
	~Link();
	Node* getHead();
	void setHead(Node* headIn);
	void addNode(unsigned short bit_legth, char* input_binary);
	void print();
	void Find(Link*, unsigned short);
	void groupCompare(Node*, Node*, unsigned short);
	void compareBinary(Node*, Node*, unsigned short);
};



//Node's method functions

Node::Node()
{
	check = false;
	binary = NULL;
	next = nullptr;
	one_num = 0;
}
Node::~Node()
{

}
Node::Node(unsigned short length)
{
	check = false;
	next = nullptr;
	one_num = 0;
	binary = new char[length];
}
int Node::getCheck()
{
	return check;
}
void Node::setCheck(int checkIn)
{
	check = checkIn;
}
Node* Node::getNext()
{
	return next;
}
void Node::setNext(Node* nextIn)
{
	next = nextIn;
}
char* Node::getBinary()
{
	return binary;
}
void Node::setBinary(char* binaryIn)
{

	int i = 0;
	while (binaryIn[i] != '\0')
	{
		if ((binary[i] = binaryIn[i]) == '1')
			++one_num;
		++i;
	}
	binary[i] = '\0';
}
unsigned short Node::getOneNum()
{
	return one_num;
}



//Link's method functions

Link::Link()
{
	pHead = nullptr;
}
Link::~Link()
{
	Node* tempNode = pHead;
	while (pHead)
	{
		pHead = pHead->getNext();
	}
}
Node* Link::getHead()
{
	return pHead;
}
void Link::setHead(Node* headIn)
{
	pHead = headIn;
}
void Link::addNode(unsigned short bit_length, char* input_binary)
{
	Node* newNode = new Node(bit_length);
	newNode->setBinary(input_binary);

	if (pHead == nullptr)
	{
		pHead = newNode;
	}
	else
	{
		Node* curNode = pHead;

		while (curNode)
		{
			if (strcmp(curNode->getBinary(), newNode->getBinary()) == 0)
				return;

			if (curNode == pHead)
			{
				if (curNode->getOneNum() > newNode->getOneNum())
				{
					newNode->setNext(curNode);
					pHead = newNode;
					return;
				}
			}
			if (curNode->getNext() == nullptr)
			{
				curNode->setNext(newNode);
				newNode->setNext(nullptr);
				return;
			}
			if (newNode->getOneNum() < curNode->getNext()->getOneNum())
			{
				newNode->setNext(curNode->getNext());
				curNode->setNext(newNode);
				return;
			}
			curNode = curNode->getNext();
		}

	}


}
void Link::print()
{
	Node* tempNode = pHead;

	while (tempNode)
	{
		cout << "-->  " << tempNode->getBinary() << "\n";
		tempNode = tempNode->getNext();
	}
}
void Link::Find(Link* PI, unsigned short bit_length)
{
	Node* preMark = pHead;
	Node* postMark = pHead;

	Link compared;

	while (postMark)
	{
		if ((postMark->getOneNum() - preMark->getOneNum()) == 1)
		{
			compared.groupCompare(preMark, postMark, bit_length);
		}

		if ((postMark->getOneNum() - preMark->getOneNum()) != 0)
		{
			while (preMark != postMark)
			{
				if (preMark->getCheck() == false)
				{
					PI->addNode(bit_length, preMark->getBinary());
				}
				preMark = preMark->getNext();
			}
		}

		postMark = postMark->getNext();
	}

	while (preMark != NULL)
	{
		if (preMark->getCheck() == false)
		{
			PI->addNode(bit_length, preMark->getBinary());
		}	
		preMark = preMark->getNext();

	}

	if (compared.getHead() == NULL)
	{
		return;
	}

	compared.Find(PI, bit_length);
	return;
}
void Link::groupCompare(Node* preNode, Node* postNode, unsigned short bit_length)
{
	Node* tempPre = preNode;
	Node* tempPost = postNode;

	while (preNode->getOneNum() == tempPre->getOneNum())
	{
		while (tempPost != NULL && postNode->getOneNum() == tempPost->getOneNum())
		{
			compareBinary(tempPre, tempPost, bit_length);
			tempPost = tempPost->getNext();
		}
		tempPre = tempPre->getNext();
		tempPost = postNode;
	}

}
void Link::compareBinary(Node* compare1, Node* compare2, unsigned short bit_length)
{
	int dif = 0;
	char* result = new char[bit_length];
	for (int i = 0; i < bit_length; ++i)
	{
		if (compare1->getBinary()[i] != compare2->getBinary()[i])
		{
			if (compare1->getBinary()[i] == '-' || compare2->getBinary()[i] == '-')
			{
				delete[] result;
				return;
			}
			result[i] = '-';
			dif++;
		}
		else
		{
			result[i] = compare1->getBinary()[i];
		}
	}
	if (dif == 1)
	{
		addNode(bit_length, result);
		compare1->setCheck(true);
		compare2->setCheck(true);
	}
	delete[] result;
	return;
}
bool Node::compareMinAndPI(Node* minnode, unsigned short bit_length)
{
	int dif = 0;
	for (int i = 0; i < bit_length; i++)
	{
		if (this->getBinary()[i] != '-' && this->getBinary()[i] != minnode->getBinary()[i])
		{
			return 0;
		}
	}
	if (dif == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


class Sums

{
private:
	char*** product;
	int product_num;
	int sum_num;
	Sums* next;

public:
	Sums() {};
	~Sums() {};
	int getProduct_num();
	void setProduct_num(int);
	int getSum_num();
	void setSum_num(int);
	char* getProduct(int, int);
	bool setProduct(int, int, char*, unsigned short);
	char** getProductarr(int);
	Sums* getNext();
	void setNext(Sums*);
	void deleteProduct(int);

	bool compareSum(int i1, unsigned short);

};

Sums::Sums() { product = NULL; product_num = 0; sum_num = NULL; next = NULL; }
Sums::~Sums() {}
int Sums::getProduct_num(void) 
{
	return product_num;
}
void Sums::setProduct_num(int inputnum)
{
	product_num = inputnum;
	product = new char**[product_num];
	for (int i = 0; i < product_num; i++)
	{
		product[i] = NULL;
	}

	return;
}
int Sums::getSum_num()
{
	return sum_num;
}
void Sums::setSum_num(int inputnum)
{
	sum_num = inputnum;
	for (int i = 0; i < sum_num; i++)
	{
		product[i] = new char*[sum_num];
		for (int j = 0; j < sum_num; j++)
		{
			product[i][j] = NULL;
		}
	}
	return;
}
char* Sums::getProduct(int x, int y)
{
	return product[x][y];
}
bool Sums::setProduct(int x, int y, char* inputproduct, unsigned short bit_length)		//수정 필요
{
	for (int i = 0; i < y - 1; i++)
	{
		if (strcmp(product[x][y], inputproduct) == 0)
		{
			return false;
		}
	}

	product[x][y] = new char[bit_length];
	strcpy(product[x][y], inputproduct);

	return true;
}
char** Sums::getProductarr(int x)
{
	return product[x];
}
Sums* Sums::getNext(void)
{
	return next;
}
void Sums::setNext(Sums* inputnext)
{
	next = inputnext;
	return;
}

void Sums::deleteProduct(int del_num)
{
	for (int j = 0; j < sum_num && product[del_num][j] != NULL; j++)
	{
		delete[] product[del_num][j];
	}

	return;
}

bool Sums::compareSum(int i1, unsigned short bit_length)
{
	int count1;

	for (count1 = 0; count1 < sum_num; count1++)
	{
		if (product[i1][count1] != NULL)
			count1++;
	}

	for (int i2 = 0; i2 < i1; i2++)
	{
		int count2;
		for (count2 = 0; count2 < sum_num; count2++)
		{
			if (product[i2][count2] != NULL)
				count2++;
		}


		if (count1 >= count2)
		{
			bool state = true;
			for (int j2 = 0; j2 < count2; j2++)
			{
				bool state1 = false;
				for (int j1 = 0; j1 < count1; j1++)
				{
					if (strcmp(product[i2][j2], product[i1][j1]) == 0)
					{
						state1 = true;
					}
				}
				if (state1 == false)
				{
					state = false;
				}
			}

			if (state == true)
			{
				for (int j1 = 0; j1 < count1; j1++)
				{
					delete[] product[i1][j1];
				}
				return false;
			}
		}
		else
		{
			bool state = true;
			for (int j1 = 0; j1 < count1; j1++)
			{
				bool state1 = false;
				for (int j2 = 0; j2 < count2; j2++)
				{
					if (strcmp(product[i2][j2], product[i1][j1]) == 0)
					{
						state1 = true;
					}
				}
				if (state1 == false)
				{
					state = false;
				}
			}

			if (state == true)
			{
				for (int j2 = 0; j2 < count2; j2++)
				{
					delete[] product[i2][j2];

					for (int j = 0; j < count1; j++)
					{
						setProduct(i2, j, product[i1][j], bit_length);
					}

					for (int j1 = 0; j1 < count1; j1++)
					{
						delete[] product[i1][j1];
					}
					return false;
				}
			}
		}
	}
	return true;
}




class Pos
{
private:
	Sums* head;

public:
	Pos() { head = NULL; }

	Sums* getHead(void);
	void setHead(Sums* headIn);
	void addLinkToPos(Link*, Link*, unsigned short);
	void combinePos(unsigned short);


};


Sums* Pos::getHead(void)
{
	return phead;
}
void Pos::setHead(Sums* headIn)
{
	phead = headIn;
	return;
}

void Pos::addLinkToPos(Link* inputLink, Link* minLink, unsigned short bit_length)
{
	Node* inputTemp = inputLink->getHead();
	Node* minTemp = minLink->getHead();

	Sums* posTemp = getHead();

	while (minTemp != NULL)
	{
		posTemp = new Sums;
		posTemp->setProduct_num(minTemp->getCheck());
		
		int num = 0;

		posTemp->setSum_num(1);

		int count = 0;
		while( inputTemp != NULL )
		{
			if (inputTemp->compareMinAndPI(minTemp, bit_length))
			{
				posTemp->setProduct(count, 1, minTemp->getBinary(), bit_length);
				count++;
			}
			inputTemp = inputTemp->getNext();
		}
		posTemp = posTemp->getNext();
		minTemp = minTemp->getNext();
		inputTemp = inputLink->getHead();
	}

	return;
}
void Pos::combinePos(unsigned short bit_length)
{
	Sums* curTemp = getHead();

	if (curTemp == NULL && curTemp->getNext() == NULL)
	{
		return;
	}

	Sums* combined = new Sums;
	
	combined->setProduct_num(curTemp->getProduct_num() * curTemp->getNext()->getProduct_num());

	int i_com = 0;
	int max_size = 0;
	for (int i1 = 0; i1 < curTemp->getProduct_num(); i1++)
	{
		for (int i2 = 0; i2 < curTemp->getNext()->getProduct_num(); i2++, i_com++) 
		{
			if (max_size < curTemp->getSum_num() + curTemp->getNext()->getSum_num())
			{
				max_size = curTemp->getSum_num() + curTemp->getNext()->getSum_num();
			}
		}
	}
	combined->setSum_num(max_size);

	i_com = 0;
	int max_j_com = 0;
	for (int i1 = 0; i1 < curTemp->getProduct_num(); i1++)
	{
		for (int i2 = 0; i2 < curTemp->getNext()->getProduct_num(); i2++)
		{
			int j_com = 0;

			for (int j1 = 0; curTemp->getProduct(i1, j1) != NULL && j1 < curTemp->getSum_num() ; j1++)
			{
				if (combined->setProduct(i_com, j_com, curTemp->getProduct(i1, j1), bit_length))
				{
					j_com++;
				}
			}
			for (int j2 = 0; curTemp->getNext()->getProduct(i2, j2) != NULL && j2 < curTemp->getNext()->getSum_num(); j2++)
			{
				if (combined->setProduct(i_com, j_com, curTemp->getNext()->getProduct(i2, j2), bit_length))
				{
					j_com++;
				}
			}
			if (max_j_com < j_com)
			{
				max_j_com = j_com;
			}

			if (combined->compareSum(i_com, bit_length) == true)
			{
				i_com++;
			}
		}
	}

	combined->setNext(curTemp->getNext()->getNext());
	setHead(combined);
	
	combinePos(bit_length);
	return;
}
