//  p5.cpp

#include <iostream>
#include "HuffmanTree.h"
using namespace std;
// I encoded "Alice's Adventures Under Ground" by Lewis Carroll
// The original file is 104k, my encoded version is 60k, so i saved about 43%
// the gzip is 40k, so is is about 20k smaller

int main(int argc, const char * argv[])
{
	HuffmanTree hc;

	string file;
	
	cout<<"Please enter a file to encode: "<<endl;
	cin>> file;
   
	string output="output.txt";

	hc.createCodeTree(file);
	hc.encodeFile(file, output);
	hc.decodeFile(output);
	// create code tree
	//
	// encode file
	//
	// decode file
	//
	cout << hc<<endl;	
	return 0;
}

























