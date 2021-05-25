#pragma once

#include "product.h"



class Node
{
private:

	Node* next;		//다은 노드를 카르키는 포인터
	int check;		
	char* binary;
	unsigned short one_num;		//노드의 binary에 1의 개수를 저장

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
	void Find(Link*, unsigned short);
	void groupCompare(Node*, Node*, unsigned short);
	void compareBinary(Node* compare1, Node* compare2, unsigned short bit_length);
	void deleteNode(char* binaryIn);
};



//Node's method functions

Node::Node()		//노드 의 생성자
{
	check = false;
	binary = NULL;
	next = nullptr;
	one_num = 0;
}
Node::~Node()		//노드 소멸자 
{
	delete[] binary;		//동적으로 할당을 받은 binary를 해제 시킨다
}
Node::Node(unsigned short length)
{
	check = false;
	next = nullptr;
	one_num = 0;
	binary = new char[length];			//전달받은 length만큼 동적으로 메모리 할당
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
	binary[i] = '\0';							//들어온 문자열을 binary에 복사. 마지막 문자를 null문자로 문자열의 끝을 알림
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
void Link::deleteNode(char* binaryIn)
{
	Node* prevNode = nullptr;
	Node* currNode = pHead;
	while (currNode && strcmp(currNode->getBinary(), binaryIn))
	{
		prevNode = currNode;
		currNode = currNode->getNext();
	}
	if (currNode)
	{
		if (prevNode)
		{
			prevNode->setNext(currNode->getNext());
			delete currNode;
		}
		else
		{
			pHead = currNode->getNext();
			delete currNode;
		}
	}
}
Link::Link()
{
	pHead = nullptr;
}
Link::~Link()
{
	Node* moving = pHead;			//리스트의 소멸자
	while (moving)					// 첫 노드부터 끝까지 삭제를 시켜준다
	{
		pHead = pHead->getNext();	//head를 다음 노드로 옮기고 
		delete moving;				//해당 노드를 삭제한다.	
		moving = pHead;				//다시 해당 포인터를 head에 위치시칸다			
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

	if (pHead == nullptr)		//노드가 연결이 안되어있으면 초기 노드 설정
	{
		pHead = newNode;
	}
	else						
	{
		Node* curNode = pHead;

		while (curNode)
		{
			if (strcmp(curNode->getBinary(), newNode->getBinary()) == 0)			//만약 현재 노드가 입력된 binary와 같다면 현재노드 할당 해제
			{
				delete newNode;
				return;
			}

			if (curNode == pHead)						//첫번쨰 노드외에 다른 노드가 존재하지 않을 경우
			{
				if (curNode->getOneNum() > newNode->getOneNum())			//현재 노드가 새로운 노드의 1의 개수보다 많을 경우 앞에 삽입
				{
					newNode->setNext(curNode);		//다음 노드를 현재 노드로 연결해준다
					pHead = newNode;				//head를 새로운 노드를 가르킨다
					return;
				}
			}
			if (curNode->getNext() == nullptr)		//마지막 노드일 경우
			{	
				curNode->setNext(newNode);			//현재 ㄴ드의 다음을 새로운 노드로 가르킨다
				newNode->setNext(nullptr);			//새로운 노드의 다음을 nullptr로 가르킨다. 
				return;
			}
			if (newNode->getOneNum() < curNode->getNext()->getOneNum())//현재 노드가 새로운 노드의 1의 개수보다 많을 경우 앞에 삽입
			{
				newNode->setNext(curNode->getNext());	//새로운 노드의 다음은 현재 노드로 가르킨다
				curNode->setNext(newNode);				
				return;
			}
			curNode = curNode->getNext();				//다음 노드 이동
		}

	}


}
void Link::Find(Link* PI, unsigned short bit_length)
{
	Node* preMark = pHead;
	Node* postMark = pHead;

	Link compared;

	while (postMark)
	{
		if ((postMark->getOneNum() - preMark->getOneNum()) == 1)		//연결리스트의 노드가 binary의 1의 개수의 차가 1이면
		{
			compared.groupCompare(preMark, postMark, bit_length);		//해당 위치를 함수에 전달하여 binary의 1의 개수가 1만큼 다른 그룹들을 비교
		}

		if ((postMark->getOneNum() - preMark->getOneNum()) != 0)		//만약에 처음 만나는 binary의 개수가 다른 노드의 차가 1이 아닌경우
		{
			while (preMark != postMark)				//그룹을 처음부터 끝까지 PI에 넣어준다 
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

	while (preMark != NULL)		//만약에 그룹에서 축소가 안된 항들을 prime implicant 링크드 리스트에 저장
	{
		if (preMark->getCheck() == false)
		{
			PI->addNode(bit_length, preMark->getBinary());
		}
		preMark = preMark->getNext();

	}

	if (compared.getHead() == NULL)
	{
		return;					//마지막 노드에 도달 할 경우 함수 종료
	}

	compared.Find(PI, bit_length);		//새로운 컬럼을 다시 검사
	return;
}
void Link::groupCompare(Node* preNode, Node* postNode, unsigned short bit_length)
{
	Node* tempPre = preNode;
	Node* tempPost = postNode;

	while (preNode->getOneNum() == tempPre->getOneNum())		//앞에있는 그룹이 같은 binary개수 노드까지만 반복하게 한다
	{
		while (tempPost != NULL && postNode->getOneNum() == tempPost->getOneNum())		//뒤에있는 그룹또한 같은 binary개수 노드만 반복하게 한다
		{
			compareBinary(tempPre, tempPost, bit_length);		//두 다른 그룹에 있는 binary들을 비교하여 축수가 가능하지 체크하고 축소한다
			tempPost = tempPost->getNext();		//뒷 그룹 다음 노드로 이동
		}
		tempPre = tempPre->getNext();		//앞에 그룹 다음 노드로 이동
		tempPost = postNode;		//뒷 그룹 처음으로 다시 이동.
	}

}
void Link::compareBinary(Node* compare1, Node* compare2, unsigned short bit_length)
{
	int dif = 0;
	char* result = new char[bit_length];
	for (int i = 0; i < bit_length; i++)
	{
		if (compare1->getBinary()[i] != compare2->getBinary()[i])		//만약 둘의 번째 비트의 원소가 다르다면
		{
			if (compare1->getBinary()[i] == '-' || compare2->getBinary()[i] == '-')		//둘중 하나의 i번쨰 노드가 - 라면 함수를 종료한다 
			{
				delete[] result;
				return;
			}
			result[i] = '-';			//해당 위치를 -로 바꾼고 dif 둘의 차이를 나타내는 변수를 증가시킨다.
			dif++;
		}
		else
		{
			result[i] = compare1->getBinary()[i];		//i번째 위치가 같다면 result에 저장한다
		}
	}
	if (dif == 1)				//만약 둘의 차이가 1이라면
	{
		addNode(bit_length, result); //현재 링크드리스트에 추가한다.

		compare1->setCheck(true);	//각 binary가 축소되었음을 체크한다
		compare2->setCheck(true);	
	}
	delete[] result;
	return;
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

	while (minTemp != NULL)	//minterm을 모아둔 리스트와 pi를 모아둔 리스트를 검사
	{
		int count = 0;
		while (piTemp != NULL)
		{
			if (isSame(piTemp->getBinary(), minTemp->getBinary()))		//만약에 한 minterm에서 해당 minterm을 포함하는 pi들을 pos형식으로 2차원 리스트에 더하기로 연결
			{
				curTemp->getProduct()->insert_plus(piTemp->getBinary(), bit_length);
				count++;
			}
			piTemp = piTemp->getNext();
		}
		piTemp = inputLink->getHead();
		minTemp = minTemp->getNext();
		if (count != 0)		//만약에 minterm을 포함하는 pi가 존재하면
		{
			if (minTemp != NULL)
			{
				Sums* temp = new Sums;		//petrick's method에서 곱으로 연결해주기 위해 새로운 sums노드 연결
				curTemp->setNext(temp);
				curTemp = temp;
			}
		}
	}
	return;
}
void Pos::combinePos(unsigned short bit_length)		//POS로 정리된 해당 특정 minterm을 포함하는 pi들의 합의 곱을 분배 법칙으로 푸는 함수
{
	Sums* curTemp = head;	//첫 노드를 가르키고 
	Sums* nextTemp = curTemp->getNext();//그 다음 곱을 가르킨다

	if (curTemp == NULL || nextTemp == NULL)	//더 이상 분배 할 곱이 없다면 함수 종료
	{
		return;
	}

	Sums* inputTemp = new Sums;		//1번째 항과 2번째 항을 분배법칙을 하고 나온 논리식과 3번째 논리식을 비교하기 위해 
	Product* inputProduct = inputTemp->getProduct();
	inputTemp->setNext(head->getNext()->getNext());		//3번쨰 항을 할당 다음으로 항당 해준다
	head = inputTemp;		



	inputProduct->distribute(curTemp->getProduct(), nextTemp->getProduct(), bit_length);			//두 더하기 항을 분배법칙을 이용해 전개
	
	

	inputProduct->DeleteSame(bit_length);
	

	cout << "\n";

	curTemp->getProduct()->getHead()->deletePlus();			//노드에 연결된 더하기 항들 할당 해제
	delete curTemp->getProduct()->getHead();				//sums노드를 할당해제
	delete curTemp;											//curTemp 할당해제

	nextTemp->getProduct()->getHead()->deletePlus();		//노드에 연결된 더하기 항들 할당 해제
	delete nextTemp->getProduct()->getHead();				//sums노드를 할당해제
	delete nextTemp;										//curTemp 할당해제

	combinePos(bit_length);									//재귀적 용법으로 3번째 부터 다시 분배법칙적용 및 전개

	return;
}



product_node* Pos::FindMinSums(int& minTrans, unsigned short bit_length)		//전개된 부울식에서 각 항이 function을 만족시키기 떄문에 각 항의 코스트가 적은 항이 최소화된 부울식이다
	
{
	product_node* minHead = NULL;
	product_node* curHead = head->getProduct()->getHead();
	int bitnum = (int)bit_length - 1;

	char* inverter = new char[bitnum];

	while (curHead)
	{
		for (int i = 0; i < bitnum; i++)
		{
			inverter[i] = '1';
		}
		product_node* temp = curHead;
		int compareTrans = 0;
		int orGate = 0;

		while (temp)
		{
			int andGate = 0;
			orGate++;

			for (int i = 0; i < bitnum; i++)
			{
				if (temp->getBinary()[i] == '0')
				{
					inverter[i] = '0';
				}

				if (temp->getBinary()[i] != '-')		//'-'가 아니면 and gate를 늘려준다
				{
					andGate++;
				}
			}

			if (andGate > 1)							//andGate의 개수 즉 andGate개수 만큼의 AND게이트 가 필요하다 예) andGate = 3 --> 3 input AND
			{
				compareTrans += (andGate * 2) + 2;
			}
			temp = temp->getMultiNext();
		}

		if (orGate > 1)								//orGate의 개수 즉 orGate개수 만큼의 OR게이트 가 필요하다 예) odGate = 3 --> 3 input OR
		{
			compareTrans += (orGate) * 2 + 2;
		}

		for (int i = 0; i < bitnum; i++)
		{
			if (inverter[i] == '0')				//inverter문자열이 0이라면 각 위치에 해당하는 변수에 인터버가 필요하다는 끗이므로 트랜지스터 개수를 2개 증가시킨다.
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

	delete[] inverter;

	return minHead;
}
