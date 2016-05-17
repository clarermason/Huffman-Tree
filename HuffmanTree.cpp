//  HuffmanTree.cpp
//  Helper functions are findEncoding and findCode


#include "HuffmanTree.h"
#include <string>
#include <queue>
#include <vector>

string temp;

bool HuffmanTree::createCodeTree(string filename)
{
	std::priority_queue<BST<CharFreq>::BSTNode*,std::vector<BST<CharFreq>::BSTNode*>,BST<CharFreq>::FrequencyCompare > myPriorityQ;
	
	string str;
	string allText = "";
	ifstream infile;
	infile.open(filename.c_str());
	if( !infile.is_open() )
	{
		cout << "ERROR Loading file!\n";
		return false;
	}
	while(!infile.eof()) // To get you all the lines.
	{
		getline(infile,str); // Saves the line in STRING.
		allText += str + "\n";
	}
	infile.close();


	// **************************************************************
	// TODO: Fill in here
	// 1. Count occurences of every letter or sybmol that you care about in all	\Text (consider spaces ' ', newlines '\n', periods, commas, question marks, quotation marks, etc.
    // 2. Use myPriorityQ to build a tree, as described in the assignment
	// 3. Set root (inherted from BST) to the final item in myPriorityQ

	//1. Count occurences
	vector<CharFreq> myData;
   	int length = allText.length();
	CharFreq object;
	BST<CharFreq>::BSTNode* node;
	bool p = false;
	for(int i=0; i< length; i++){
	  for(int j=0; j< (int)myData.size(); j++){

		if( allText[i] == myData[j].letter){
		  myData[j].frequency++;
		  p= true;
		  break;
		}
	   }
		if(p == false){
		  object.frequency = 1;
		  object.letter = allText[i];
		  myData.push_back(object);

	  }
	  p = false;
	}
	// put into queue
	for( int k=0; k< (int)myData.size(); k++){
	  
	  node =new BST<CharFreq>::BSTNode(myData[k]);
	  myPriorityQ.push(node);
	}
  
	BST<CharFreq>::BSTNode* newnode;
	CharFreq newdata;
	int newFreq=0;
	int size= myPriorityQ.size();


	//2: build a tree
	while(size != 1){
	  BSTNode* left= myPriorityQ.top();
	  myPriorityQ.pop();
	  BSTNode* right= myPriorityQ.top();
	  myPriorityQ.pop();
	 
	  newFreq= right->data.frequency+left->data.frequency;
	  newdata.frequency=newFreq;

	  newnode= new BST<CharFreq>::BSTNode(left, right, newdata);
	  myPriorityQ.push(newnode);
	  size--;
	}

	//3: Set the root
	root= myPriorityQ.top();


	
		// **************************************************************



	
	return true;
}

// Helper function to find encodings
void HuffmanTree::findEncoding(string prev,BST<CharFreq>::BSTNode* node, char letter){

  if(node->left == nullptr && node->right == nullptr && letter==node->data.letter){
	  node->data.encoding= prev;
	  temp= node->data.encoding;
  }
	if (node->right!= nullptr){
	  string right = prev + "1";
	  findEncoding(right, node->right, letter);
  }
	if( node-> left != nullptr){
	  string left= prev + "0";
	  findEncoding(left, node->left,letter) ;
	}
}

bool HuffmanTree::encodeFile(string originalFilename, string outputFilename)
{
	string str;
	string allText = "";
	ifstream infile;
	infile.open(originalFilename.c_str());
	if( !infile.is_open() )
	{
		cout << "ERROR Loading file!\n";
		return false;
	}
	while(!infile.eof()) // To get you all the lines.
	{
		getline(infile,str); // Saves the line in STRING.
		allText += str + "\n";
	}
	infile.close();
	
	std::ofstream outStream(outputFilename.c_str(), std::ios::binary);
	
	if( !outStream.is_open() )
	{
		cout << "ERROR creating output file!\n";
		return false;
	}
	
	string currentStream="";
	
	const int WRITE_SIZE = 8;
	string prev="";
	//CharFreq arr[(allText.length())];
	string add;//string to hold encoding
	for(int i=0;i<(int)allText.length();i++)
	  {
		// **************************************************************
		// TODO: add the appropriate encoding for allText[i] to currentStream
		findEncoding(prev,root,allText[i]);
		add= temp;
		currentStream += add;
	  }
		// **************************************************************
		
		while((int)currentStream.length() > WRITE_SIZE)
		{
			string byte = currentStream.substr(0, WRITE_SIZE);
			bitset<8> set(byte);
			const char toWrite = (unsigned char)((unsigned int)set.to_ulong());
			outStream.write(&toWrite,sizeof(char));
			currentStream = currentStream.substr(WRITE_SIZE, currentStream.length()-WRITE_SIZE);
		}
	
	outStream.close();
	return false;
}

bool HuffmanTree::decodeFile(string filename)
{
	ifstream encodedfile;
	encodedfile.open(filename.c_str(), ios::binary);
	if( !encodedfile.is_open() )
	{
		cout << "ERROR opening encoded file!\n";
		return false;
	}
	
	encodedfile >> std::noskipws;	
	
	string bitStream = "";
	while(!encodedfile.eof())
	{
		unsigned char readMe;
		encodedfile >> readMe;
		bitset<8> set((unsigned long)readMe);
		bitStream += set.to_string();
	}
	
	encodedfile.close();
	
	int i=0;
	while(i != -1)
	{
		i = traverseAndPrint(bitStream, i);
	}
	return false;
}



int HuffmanTree::traverseAndPrint(string &bits, int i, BSTNode *cur)
{

  // **************************************************************
  // TODO: Write this function using recursion.
  //  This is essentially your decode function.  You need to step through the tree based on reading 0 or 1 and when you
	//      reach a leaf, print (using cout) the appropriate character.
	// i represents your current location in the string
	// cur represents the cur node in your tree
	// Don't forget that you need to keep going after printing out a character (which means restarting at th top of the tree       

  
  if(i >= (int)bits.length()){
	return -1;
  }
  
  if (cur->right != nullptr || cur->left != nullptr){
	if(bits[i] == '0' && cur->left != nullptr){
	  i++;
	 return traverseAndPrint(bits, i, cur->left);
	}
	
	else{
	  i++;
	  return traverseAndPrint(bits, i, cur->right);
	}
  }
  else{
	cout << cur->data.letter;
	return i;
  }

	// **************************************************************
}

// helper function to display code
void HuffmanTree::findCode(BST<CharFreq>::BSTNode* node){
  if(node->left == nullptr && node->right == nullptr){
	cout<<"Charater:"<< node->data.letter<<" Encoding:"<< node->data.encoding<<endl;
  }
  if(node->right!=nullptr){
	findCode(node->right);
  }
  if(node->left != nullptr){
	findCode(node->left);
  }
}
  
void HuffmanTree::displayCode(ostream &out)
{
	// **************************************************************
	// TODO: print out each letter and its code, you might want to check for special cases (space, newline, etc.)

  findCode(root); 
  
	// **************************************************************
}

ostream& operator<<(ostream &out, HuffmanTree &code)
{
	code.displayCode(out);
	return out;
}



