#pragma once

#include "product.h"



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
	void checkIncrease();
	
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
	void compareBinary(Node* compare1, Node* compare2, unsigned short bit_length);
	void findEPI(Link* epi, Link* minhead, unsigned short bit_length);
	void deleteNode(char* binaryIn) {
		Node* prevNode = nullptr;
		Node* currNode = pHead;
		while (currNode && strcmp(currNode->getBinary(), binaryIn))
		{
			prevNode = currNode;
			currNode = currNode->getNext();
		}
		if (currNode) {
			if (prevNode) {
				prevNode->setNext(currNode->getNext());
				delete currNode;
			}
			else {
				pHead = currNode->getNext();
				delete currNode;
			}
		}
	}
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
	delete binary;
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
void Node::checkIncrease()
{
	check++;
}

//Link's method functions

Link::Link()
{
	pHead = nullptr;
}
Link::~Link()
{
	Node* moving = pHead;
	while (moving)
	{
		pHead = pHead->getNext();
		delete moving;
		moving = pHead;
	}
	pHead = nullptr;
	return;
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

void Link::findEPI(Link* epi, Link* minhead, unsigned short bit_length)
{
	Node* piNode = pHead;
	Node* minNode = minhead->getHead();
	while (minNode)
	{
		Node* EPI = nullptr;
		while (piNode)
		{
			if (isSame(minNode->getBinary(), piNode->getBinary()) == true)
			{
				piNode->checkIncrease();
				minNode->checkIncrease();
				EPI = piNode;
			}
			piNode = piNode->getNext();
		}
		if (minNode->getCheck() == 1)
		{
			minNode = minNode->getNext();
			epi->addNode(bit_length, EPI->getBinary());
			deleteNode(EPI->getBinary());
			piNode = pHead;
			continue;
		}
		piNode = pHead;
		minNode = minNode->getNext();
	}

	Node* epiNode = epi->getHead();
	minNode = minhead->getHead();
	while (minNode)
	{
		//eliminate minterms
	}
	

}


class Sums
{
private:
	Product* producthead;
	Sums* next;

public:
	Sums();
	~Sums();

	Product* getProduct();
	void setProduct(Product*);
	Sums* getNext();
	void setNext(Sums*);
	bool compareSum(int i1, unsigned short);

};


Sums::Sums() { producthead = new Product; next = NULL; }
Sums::~Sums() { delete producthead; }

Product* Sums::getProduct()
{
	return producthead;
}
void Sums::setProduct(Product* inputProduct)
{
	producthead = inputProduct;
	return;
}
Sums* Sums::getNext(void)
{
	return next;
}
void Sums::setNext(Sums* inputnext)
{
	next = inputnext;
}
bool Sums::compareSum(int i1, unsigned short bit_length)
{
	return 1;
}


class Pos
{
private:
	Sums* head;

public:
	Pos() { head = NULL; }
	~Pos() {  };
	Sums* getHead(void);
	void setHead(Sums* headIn);
	void addLinkToPos(Link*, Link*, unsigned short);
	void combinePos(unsigned short);
	void printPos(void);
	product_node* FindMinSums(int&, unsigned short);
};


Sums* Pos::getHead(void)
{
	return head;
}
void Pos::setHead(Sums* headIn)
{
	head = headIn;
	return;
}

void Pos::addLinkToPos(Link* inputLink, Link* minLink, unsigned short bit_length)
{
	Node* piTemp = inputLink->getHead();
	Node* minTemp = minLink->getHead();

	Sums* curTemp = new Sums;
	head = curTemp;

	while (minTemp != NULL)
	{
		int count = 0;
		while (piTemp != NULL)
		{
			if (isSame(piTemp->getBinary(), minTemp->getBinary()))
			{
				curTemp->getProduct()->insert_plus(piTemp->getBinary(), bit_length);
				count++;
			}
			piTemp = piTemp->getNext();
		}
		piTemp = inputLink->getHead();
		minTemp = minTemp->getNext();
		if (count != 0)
		{
			if (minTemp != NULL)
			{
				Sums* temp = new Sums;
				curTemp->setNext(temp);
				curTemp = temp;
			}
		}
	}


	return;
}
void Pos::combinePos(unsigned short bit_length)
{
	Sums* curTemp = head;
	Sums* nextTemp = curTemp->getNext();

	if (curTemp == NULL || nextTemp == NULL)
	{
		return;
	}
	Sums* inputTemp = new Sums;

	Product* inputProduct = inputTemp->getProduct();


	inputTemp->setNext(head->getNext()->getNext());
	head = inputTemp;

	inputProduct->distribute(curTemp->getProduct(), nextTemp->getProduct(), bit_length);			//여기서 호출하면 됨
	inputProduct->DeleteSame(bit_length);

	curTemp->getProduct()->getHead()->deletePlus();
	delete curTemp->getProduct()->getHead();
	delete curTemp;

	nextTemp->getProduct()->getHead()->deletePlus();
	delete nextTemp->getProduct()->getHead();
	delete nextTemp;


	combinePos(bit_length);

	return;
}

void Pos::printPos(void)
{
	Sums* curTemp = getHead();
	while (curTemp != NULL)
	{
		curTemp->getProduct()->PrintProduct();
		curTemp = curTemp->getNext();
	}
	return;
}


product_node* Pos::FindMinSums(int& minTrans, unsigned short bit_length)
{
	product_node* minHead = NULL;
	product_node* curHead = head->getProduct()->getHead();

	int* invertor = new int[bit_length - 1];

	minTrans = -1;

	while (curHead)
	{
		for (int i = 0; i < bit_length - 1; i++)
		{
			invertor[i] = 0;
		}
		product_node* temp = curHead;
		int compareTrans = 0;
		int orGate = 0;

		while (temp)
		{
			int andGate = 0;
			orGate++;

			for (int i = 0; i < bit_length - 1; i++)
			{
				if (temp->getBinary()[i] == 0)
				{
					invertor[i] = 1;
				}

				if (temp->getBinary()[i] != '-')
				{
					andGate++;
				}
			}

			if ((int)bit_length - andGate > 1)
			{
				compareTrans += (((int)bit_length - andGate) * 2) + 2;
			}
			temp = temp->getMultiNext();
		}

		if (orGate > 1)
		{
			compareTrans += orGate * 2 + 2;
		}

		for (int i = 0; i < bit_length - 1; i++)
		{
			if (invertor[i] == 1)
			{
				compareTrans += 2;
			}
		}

		if (minTrans == -1 || minTrans > compareTrans)
		{
			minTrans = compareTrans;
			minHead = curHead;
		}

		curHead = curHead->getPlusNext();
	}

	return minHead;
}
