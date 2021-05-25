#include "link.h"

void FiletoData(Link*, Link*, unsigned short& bit_length);

int main()
{

	Link* allhead = new Link();		//dont care항과 minterm항을 모두 연결하는 링크드 리스트 생성
	Link* minhead = new Link();		//minterm항을 연결하는 링크드 리스트 생성
	Link* PI = new Link();			//prime implicant를 연결 할 링크드 리스트 생성
	unsigned short bit_length = 0;
	int trans = -1;

	FiletoData(allhead, minhead, bit_length);		//input_minter.txt 입력받아 리스트에 저장하는 함수
	cout << "Please check result.txt file.\nThank you.\n";
	allhead->Find(PI, bit_length);			//prime implicant를 찾는 메소드 호출

	delete allhead;			//dont care항과 minterm을 연결한 리스트 할당 해제

	Pos* pm = new Pos();

	pm->addLinkToPos(PI, minhead, bit_length);		//Pi를 product of sums로 만드는 메소드

	delete minhead;		//minhead 리스트 삭제 할당해제
	delete PI;			//pi리스트 삭제 할당 해제

	pm->combinePos(bit_length);						//POS 전개 및 분배 메소드
	pm->FindMinSums(trans, bit_length)->PtoFile(trans, bit_length);			//분배가 끝난 논리식 각각이 minterm을 포함하는 논리식이기때문에 transistor가 적게 쓰인 논리식을 고르는 함수

	

	pm->getHead()->getProduct()->getHead()->deletePlus();
	delete pm->getHead()->getProduct()->getHead();
	delete pm->getHead();
	delete pm;


	return 0;
}


void FiletoData(Link* allhead, Link* minhead, unsigned short& bit_length)
{
	ifstream fin;	

	fin.open("input_minterm.txt");	
	
	if (fin.fail())		//파일열기를 실패했을 경우
	{
		cerr << "file open error\n";			//에러 메세지 출력
		exit(100);								//프로그램 종료
	}

	char* binary;								
	char MorD;
	fin >> bit_length;
	++bit_length;
	binary = new char[bit_length];			//binary를 저장할 문자열 입력된 bit length만큼 동적할당

	while (!fin.eof())
	{
		fin >> MorD;
		fin >> binary;
		if (strcmp(binary, "") == 0)
			break;
		if (MorD == 'm' || MorD == 'M')
		{
			allhead->addNode(bit_length, binary);			//만약 minterm일 경우 allhead에 연결
			minhead->addNode(bit_length, binary);			//만약 minterm일 경우 minhead에 연결
		}
		else if (MorD == 'd'|| MorD == 'D')
		{
			allhead->addNode(bit_length, binary);			//만약 dont care일 경우 allhead에 연결
		}
	}

	delete[] binary;

	fin.close();											//파일 종료

	return;
}
