#pragma once

#include <iostream>

using namespace std;

bool grayCode(char*, char*);

class Node
{
private:

	Node* next;
	bool check;
	char* binary;
	unsigned short one_num;

public:
	Node();
	Node(unsigned short);
	Node* getNext();
	bool getCheck();
	void setCheck(bool);
	void setNext(Node* nextIn);
	char* getBinary();
	void setBinary(char*);
	unsigned short getOneNum();

};

class Link
{
private:
	Node* pHead;
public:
	Link();
	Node* getHead();
	void setHead(Node* headIn);
	void addNode(unsigned short bit_legth, char* input_binary);
	void print();
	void Find(Link*);
	void groupCompare(Node*, Node*);
};



//Node's method functions

Node::Node()
{
	check = false;
	binary = NULL;
	next = nullptr;
	one_num = 0;
}
Node::Node(unsigned short length)
{
	check = false;
	next = nullptr;
	one_num = 0;
	binary = new char[length];
}
bool Node::getCheck()
{
	return check;
}
void Node::setCheck(bool checkIn)
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
				curNode->setNext(newNode);
				newNode->setNext(curNode->getNext());
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
void Link::Find(Link* Pi)
{
	Node* preMark = pHead;
	Node* postMark = pHead;

	while (postMark)
	{
		if (postMark->getOneNum() != preMark->getOneNum())
		{
			Pi->groupCompare(preMark, postMark);
			preMark = postMark;
		}

		postMark = postMark->getNext();
	}

}
void Link::groupCompare(Node* preNode, Node* postNode)
{
	;
}

bool grayCode(char* comStr1, char* comStr2)
{
	int i, dif;
	i = dif = 0;
	while (comStr2[i] != '\0')
	{
		if (comStr1[i] != comStr2[i])
			++dif;
	}
	return dif == 1 ? true : false;
}