#include "library_HuffmanCoding.h"

// Tạo cây huffman dựa trên những cặp node có kí tự và tần xuất xuất hiện khác nhau,
// lưu chúng trong priority_queue theo thứ tự ưu tiên min_heap. (lưu ý priority_queue mặc định có
// thứ tự ưu tiên là max-heap nên cần struct compare hoạt động theo cách function call operator để
// so sánh và đưa những node có frequency thấp lên top của queue.

huffmanNode* buildHuffmanTree(vector<pair<char, int>>& frequency) {
	priority_queue<huffmanNode*, vector<huffmanNode*>, compare> pq;
	for (auto it : frequency) {
		pq.push(new huffmanNode(it.first, it.second));
	}
	while (pq.size() > 1) {
		huffmanNode* leftNode = pq.top(); pq.pop();
		huffmanNode* rightNode = pq.top(); pq.pop();
		huffmanNode* parent = new huffmanNode('\0', leftNode->frequency + rightNode->frequency);
		parent->left = leftNode;
		parent->right = rightNode;
		pq.push(parent);
	}
	return pq.top();
}

//Xây dựng mã huffman từ cây huffman theo nguyên tắc đi về trái thì biểu diễn code bằng bit 0
//đi về phải thì biểu diễn bằng bit 1.
void generalHuffmanCodes(huffmanNode* root, string code, unordered_map<char, string>& huffmanTable) {
	if (!root) return;
	
	if (root->character != '\0')
		huffmanTable[root->character] = code;
	generalHuffmanCodes(root->left, code + "0", huffmanTable);
	generalHuffmanCodes(root->right, code + "1", huffmanTable);
}

//Mã hoá văn bản dựa trên mã huffman đã tạo bằng cách duyệt toàn bộ ký tự có trong văn bản (ký tự là key),
//và nối mã đã được mã hoá riêng cho kí tự (mã đã được mã hoá là value)
string encodeText(const string& text, unordered_map<char, string>& huffmanTable) {
	string encodedText = "";
	for (char ch: text) {
		encodedText += huffmanTable[ch];
	}
	return encodedText;
}


//Quá trình giải mã
//Dựa trên mã đã được mã hoá lưu trong encodedText duyệt huffmanTree để giải mã.
//Duyệt mã đã được mã hoá trong encodedText bằng cách so sánh bit (bit 0 đi về bên trái, bit 1 đi về bên phải)
//khi đến node lá nối ký tự vào chuỗi ta sẽ được chuỗi ký tự được giải mã (văn bản).
string decodeText(huffmanNode* root, const string encodedText) {
	string decodedText = "";
	huffmanNode* current = root;
	for (char bit : encodedText) {
		if (bit == '0') current = current->left;
		else current = current->right;

		if (!current->left && !current->right) { // node lá
			decodedText += current->character;
			current = root; // đưa node duyệt trở về gốc để tiếp tục quá trình giải mã.
		}
	}
	return decodedText;
}