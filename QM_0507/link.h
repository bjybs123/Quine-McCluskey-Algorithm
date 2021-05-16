#pragma once

#include <iostream>

using namespace std;

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
	void checkIncrease()
	{
		check++;
	}
	
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

void Link::findEPI(Link* epi, Link* minhead, unsigned short bit_length)
{
	int includeNum;
	Node* piNode = pHead;
	Node* minNode = minhead->getHead();
	while (minNode)
	{
		Node* EPI = nullptr;
		includeNum = 0;
		while (piNode)
		{
			if (isSame(minNode->getBinary(), piNode->getBinary()) == true)
			{
				piNode->checkIncrease();
				EPI = piNode;
				++includeNum;
			}
			piNode = piNode->getNext();
		}
		if (includeNum == 1)
		{
			epi->addNode(bit_length, EPI->getBinary());
			deleteNode(EPI->getBinary());
		}
		minNode->setCheck(includeNum);
		piNode = pHead;
		minNode = minNode->getNext();
	}


	/*  Print check
	
	cout << "\n\nminHead\n";
	minNode = minhead->getHead();
	while (minNode)
	{

		cout << "binary : " << minNode->getBinary() << "\n";
		cout << "minnode check : " << minNode->getCheck() <<  "\n";
		minNode = minNode->getNext();
	}

	cout << "\n\npiHead\n";
	piNode = pHead;
	while (piNode)
	{
		cout << "binary : " << piNode->getBinary() << "\n";
		cout << "pinode check : " << piNode->getCheck() << "\n";
		piNode = piNode->getNext();
	}
	*/
}





