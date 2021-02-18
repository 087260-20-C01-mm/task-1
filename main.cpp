#include <iostream>
#include "source.h"
#include <stdio.h>
#include <locale.h>
int main() {
    setlocale(LC_ALL,"Rus");
    std::cout << "¬ведите путь к файлу" << std::endl;
	char* link;
	link = new char[50];
	gets(link);
	int n = 1;
	while (true) {
		if (!cut(n,link)) { break; }
		tie(n,link);
		n *= 2;
	}
	return 0;
}
