#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include <vector>

using namespace std;

void writeFile(int A[], int size, string fileName);
void print (int A[], int size);
void altPrint(int A[], int size);
void printFile (int A[], int size, ofstream& file);
void printUsageInfo(const string& name);
void checkArguments(int argc, char *argv[]);
void parseArguments(int argc, char *argv[], bool &negative, char &order, int &seed);
void generateNumbers (int A[], int size, const bool &negative, const char &order, const int &seed);
void sortIncreasing(int A[], int size);
void sortDecreasing(int A[], int size);

int main(int argc, char *argv[]) {
	bool negative = false;
	char order = 'X';
	int seed = 1;
	checkArguments(argc, argv); // Checks to see if the arguments make sense
	parseArguments(argc, argv, negative, order, seed); // Scans for flags
	if (order == 'X') { printUsageInfo("generate-numbers"); exit(0); }
	//cout << "ORDER = " << order << endl;
	int size = atoi(argv[1]);
	size++; // because 1st value holds the amount of numbers
	int A[size];
	generateNumbers (A, size, negative, order, seed);
	//print(A, size);
	writeFile(A, size, "input.txt");
}

void run() {
	
}

void print (int A[], int size) {
	for (int i = 0; i < size; i++) {
		cout << A[i] << endl;
	}
}

void printFile (int A[], int size, ofstream& file) {
	for (int i = 0; i < size; i++) {
		file << A[i] << endl;
	}
}

void writeFile(int A[], int size, string fileName) {
	ofstream myFile;
	myFile.open(fileName, ofstream::out | ofstream::trunc); // Clears content of file
	//myFile << "K\n";
	printFile(A, size, myFile);
	myFile.close();
}

void printUsageInfo(const string& name)
{
		cout << "Usage: ./" << name << " number [-n] [-s SEED] [-o ORDER]...\n"
		//cout << "NOTE:\tFirst argument must be the amount of numbers to be generated" << endl;
		"Options:\n"
		"  -n\tAllows negative numbers to be generated\n"
		"  -s\tAllows user to input seed\n"
		"  -o\tORDER is a single character representing an the type of order: \n"
		"     R   (Random)\n"
		"     I   (Increasing)\n"
		"     D   (Decreasing)\n";
		
}

void checkArguments(int argc, char *argv[]) {
	if (argc == 1) {
		printUsageInfo("generate-numbers");
		exit(0);
	}
	try{
		if (atoi(argv[1]) == 0 || atoi(argv[1]) > 100000) {
			throw out_of_range("Enter a number from 0 to 100000");
		}
	}
	catch (out_of_range &error) {
		cout << "ERROR: " << error.what() << endl;
		exit(0);
	}
}

void parseArguments(int argc, char *argv[], bool &negative, char &order, int &seed) {
	for (int i = 2; i < argc; i++)
	{
		char* p = argv[i];
		//cout << "p = " << p << endl;

		// if option does not start from dash, report an error
		if (*p != '-') {printUsageInfo("generate-numbers");exit(0);}
			
		//cout << "p[1] = " << p[1] << endl;
		switch (p[1]) // switch on whatever comes after dash
		{
			case 'o': if (i+1 < argc) order = argv[++i][0]; break;
			case 's': if (i+1 < argc) seed = argv[++i][0]; break;
			case 'n': negative   = true; break;
			default: printUsageInfo("generate-numbers");exit(0); break;
		}
	}
}

void generateNumbers (int A[], int size, const bool &negative, const char &order, const int &seed) {
	srand(time(NULL)*seed);
	A[0] = size-1;
	for (int i = 1; i < size; i++) {
		int value;
		if (!negative) { // If only postive integers
			value = rand() % 65536; // Generates values from 0 to 65535 AKA 0 to 2^16-1
		}
		if (negative && i < size/2) {
			value = (rand() % 32768) + 1;
			value *= -1;
			// Generates values from -32768 to -1 AKA -(2^15) to -1
		} else {
			value = rand() % 32768;
			 // Generates values from 0 to 32767 AKA 0 to 2^15-1
		}
		A[i] = value;
	}
	
	if (order == 'R') {
		
	} else if (order == 'I') {
		sortIncreasing(A, size);
	} else if (order == 'D') {
		sortDecreasing(A, size);
	}
	
}

void sortIncreasing(int A[], int size)
{
	for(int i = 1; i < size; i++)
	{
		int min = A[i];
		int minIndex = i;

		for(int j = i + 1; j < size; j++)
		{
			if(min > A[j])
			{
				min = A[j];
				minIndex = j;
			}
		}
		   
		if(minIndex != i){
			A[minIndex] = A[i];
			A[i] = min;
		}
	}
}

void sortDecreasing(int A[], int size)
{
	for(int i = 1; i < size; i++)
	{
		int max = A[i];
		int maxIndex = i;

		for(int j = i + 1; j < size; j++)
		{
			if(max < A[j])
			{
				max = A[j];
				maxIndex = j;
			}
		}
		   
		if(maxIndex != i){
			A[maxIndex] = A[i];
			A[i] = max;
		}
	}
}

void altPrint(int A[], int size) {
	for (int i = 0; i < size; i++) {
		cout << "[" << A[i] << "] ";
	}
	cout << endl;
}