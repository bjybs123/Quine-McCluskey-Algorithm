#include <fstream>
#include "link.h"

void FiletoData(Link*, Link*, unsigned short& bit_length);

int main()
{
	Pos* pm = new Pos();
	Link* epi = new Link();
	Link* allhead = new Link();
	Link* minhead = new Link();
	Link* PI = new Link();
	unsigned short bit_length = 0;

	FiletoData(allhead, minhead, bit_length);

	allhead->print();

	allhead->Find(PI, bit_length);

	cout << "PIs\n";
	PI->print();
	cout << "Minterms\n";
	minhead->print();

	//PI->findEPI(epi, minhead, bit_length);

	pm->addLinkToPos(PI, minhead, bit_length);
	pm->printPos();
	pm->combinePos(bit_length);
	cout << "\n";

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
