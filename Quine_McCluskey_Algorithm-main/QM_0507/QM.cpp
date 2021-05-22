
#include "link.h"

void FiletoData(Link*, Link*, unsigned short& bit_length);

int main()
{
	Pos* pm = new Pos();
	Link* allhead = new Link();
	Link* minhead = new Link();
	Link* PI = new Link();
	unsigned short bit_length = 0;
	int trans = -1;


	FiletoData(allhead, minhead, bit_length);

	allhead->print();

	allhead->Find(PI, bit_length);

	cout << "\nPIs\n";
	PI->print();
	cout << "\nMinterms\n";
	minhead->print();


	pm->addLinkToPos(PI, minhead, bit_length);
	cout << "\nBefore Petrick Method\n";
	pm->printPos();
	pm->combinePos(bit_length);
	cout << "\nPetrick Method\n";
	pm->printPos();
	pm->FindMinSums(trans, bit_length)->PtoFile(trans, bit_length);
	

	delete allhead;
	delete minhead;
	delete PI;
	pm->getHead()->getProduct()->getHead()->deletePlus();
	delete pm->getHead()->getProduct()->getHead();
	delete pm->getHead();
	delete pm;

}


void FiletoData(Link* allhead, Link* minhead, unsigned short& bit_length)
{
	ifstream fin;

	fin.open("input.txt");
	
	if (fin.fail())
	{
		cerr << "error\n";
		exit(100);
	}

	char* binary;
	char MorD;
	fin >> bit_length;
	++bit_length;
	binary = new char[bit_length];

	while (!fin.eof())
	{
		fin >> MorD;
		fin >> binary;
		if (strcmp(binary, "") == 0)
			break;
		if (MorD == 'm' || MorD == 'M')
		{
			allhead->addNode(bit_length, binary);
			minhead->addNode(bit_length, binary);
		}
		else if (MorD == 'd'|| MorD == 'D')
		{
			allhead->addNode(bit_length, binary);
		}
	}

	delete[] binary;

	fin.close();

	return;
}
