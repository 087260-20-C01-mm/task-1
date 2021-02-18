
#include "source.h"
#include <fstream>
#include <string.h>

using namespace std;

bool IsFirstBigger(char* A, char* B) {
	if (A[0] < B[0] || (A[0] == B[0] && A[1] < B[1]) || (A[0] == B[0] && A[1] == B[1] && A[2] < B[2]) || (A[0] == B[0] && A[1] == B[1] && A[2] == B[2] && A[3] < B[3])) { return false; }
	else return true;
}


bool cut(int n, char link[50]) {


	int i;
	char* s;
	s = new char[100];
	bool isSecondWritten = false;
	FILE* f, * f1, * f2,*q,*w,*e;
	f=fopen( link, "r");
	f1=fopen( "f1.txt", "w");
	f2=fopen( "f2.txt", "w");
	q = f; w = f1; e = f2;
	while (true) {
		for (i = 0; i < n; i++) {
			s = fgets(s, 500, f);
			if (s == NULL) { break; }
			fprintf(f1, s, "%s");
		}
		if (s == NULL) { break; }
		for (i = 0; i < n; i++) {
			s = fgets(s, 500, f);
			if (s == NULL) { break; }
			fprintf(f2, s, "%s");
			isSecondWritten = true;
		}
		if (s == NULL) { break; }
	}
	fclose(q);
	fclose(w);
	fclose(e);
	delete[] s;
	return isSecondWritten;
}

void tie(int n, char link[50]) {
	int i, k;
	bool skip1 = false, skip2 = false;
	char* flag;
	char* Years[2];
	char* film1;
	char* film2;
	film1 = new char[100];
	film2 = new char[100];

	ofstream f(link);
	ifstream f1("f1.txt");
	ifstream f2("f2.txt");


	i = 1; k = 1;
	while (true) {

		if (i == n + 1 && k == n + 1) { i = 1; k = 1; }
		else if (i == n + 1) {
			while (k <= n) {
				if (skip2) { f << film2 << endl; skip2 = false; k++; continue; }
				f2.getline(film2, 500, '\n');
				if (film2 == NULL || film2[0] == '\0') { break; }
				f << film2 << endl;
				k++;
			}
			if (film2 == NULL || film2[0] == '\0') { break; }
			continue;
		}
		else if (k == n + 1) {
			while (i <= n) {
				if (skip1) { f << film1 << endl; skip1 = false; i++; continue; }
				f1.getline(film1, 500, '\n');
				f << film1 << endl;
				i++;
			}
			continue;
		}

		if (!skip1) {
			f1.getline(film1, 500, '\n');
			if (film1 == NULL || film1[0] == '\0') { break; }
		}
		if (!skip2) {
			f2.getline(film2, 500, '\n');
			if (film2 == NULL || film2[0] == '\0') { f << film1 << endl; skip1 = false; continue; }
		}

		flag = strrchr(film1, ')');
		Years[0] = &flag[-4];
		flag = strrchr(film2, ')');
		Years[1] = &flag[-4];

		if (IsFirstBigger(Years[0], Years[1])) { f << film2 << endl; skip1 = true; skip2 = false; k++; }
		else { f << film1 << endl; skip2 = true; skip1 = false; i++; }
	}

	f.close();
	f1.close();
	f2.close();
	delete[] film1;
	delete[] film2;
}
