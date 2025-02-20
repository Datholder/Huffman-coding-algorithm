#include <iostream>
#include <unordered_map>
#include<queue>
#include <vector>
using namespace std;

struct huffmanNode {
	char character;
	int frequency;
	huffmanNode* left, * right;

	huffmanNode(char ch, int f) {
		character = ch;
		frequency = f;
		left = right = nullptr;
	}
};

struct compare {
	bool operator()(huffmanNode* a, huffmanNode* b) {
		return a->frequency > b->frequency;
	}
};
huffmanNode* buildHuffmanTree(vector<pair<char, int>>& frequency);
void generalHuffmanCodes(huffmanNode* root, string code, unordered_map<char, string>& huffmanTable);
string encodeText(const string& text, unordered_map<char, string>& huffmanTable);
string decodeText(huffmanNode* root, const string encodedText);
