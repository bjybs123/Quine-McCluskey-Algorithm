#include <fstream>
#include "link.h"



void FiletoData(Link*, Link*, unsigned short& bit_length);

int main()
{
	Link* allhead = new Link();
	Link* minhead = new Link();
	Link* PI = new Link();
	unsigned short bit_length = 0;

	FiletoData(allhead, minhead, bit_length);

	allhead->print();

	allhead->Find(PI, bit_length);

	cout << "\n";
	PI->print();


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