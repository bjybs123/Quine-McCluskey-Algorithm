//# Quine_McClusky_Algorithm
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
using namespace std;

int main() {
	ifstream read;
	read.open(input_minterm.txt); // 파일 호출
    char **dm;
    char* line[50];
	char readline[50]; //파일을 한줄씩 읽어 공간
    int l = 0;

    read.open("input.txt");  // 파일 열기

    if (read.is_open())
    {
        while (read.getline(readline, sizeof(readline)))
        {
            line[l][0] = *readline;
            l++;
        }
    }

    unsigned int bit = atoi(line[0]);

    for (int i = 0; i < l; i++) {

    }

    read.close(); // 파일 닫기



	
}
