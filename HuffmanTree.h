//  HuffmanTree.h

#ifndef __huffman__HuffmanTree__
#define __huffman__HuffmanTree__

#include <iostream>
#include <string>
#include <queue>
#include <fstream>
#include <bitset>
#include "BST.h"

using namespace std;


class CharFreq
{
public:
    	CharFreq() :letter('\0'), frequency(0), encoding("") { }
    	CharFreq(unsigned char l, float f) :letter(l), frequency(f), encoding("") { }
	
	unsigned char letter;
	float frequency;
	string encoding;
	
	bool operator>(const CharFreq &rhs) const
	{
		return frequency > rhs.frequency;
	}
};

class HuffmanTree : BST<CharFreq>
{
public:
	HuffmanTree() {}
	
	bool createCodeTree(string filename);
	
	bool encodeFile(string originalFilename, string outputFilename);
	
	bool decodeFile(string filename);
	
	void displayCode(ostream &out);

 private:

	
	inline int traverseAndPrint(string &bits, int i)
	{
		return traverseAndPrint(bits, i, root);
	}
	
	int traverseAndPrint(string &bits, int i, BSTNode *cur);

	void findEncoding(string prev, BST<CharFreq>::BSTNode* node, char letter);
	void findCode(BST<CharFreq>::BSTNode* node);
};

ostream& operator<<(ostream &out, HuffmanTree &code);

#endif /* defined(__huffman__HuffmanTree__) */
