
#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Generate Huffman codes by traversing the tree
void generateCodes(Node* root, string code,
                   unordered_map<char, string>& codes) {
    if (!root)
        return;

    // Leaf node represents a character
    if (!root->left && !root->right) {
        codes[root->ch] = code.empty() ? "0" : code;
        return;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

Node* buildHuffmanTree(const string& text) {
    unordered_map<char, int> freq;

    for (char ch : text)
        freq[ch]++;

    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto entry : freq)
        pq.push(new Node(entry.first, entry.second));

    if (pq.empty())
        return nullptr;

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node(
            '\0', left->freq + right->freq
        );

        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    return pq.top();
}

int main() {
    string text;

    cout << "Enter text: ";
    getline(cin, text);

    Node* root = buildHuffmanTree(text);

    if (!root) {
        cout << "No input text provided.\n";
        return 0;
    }

    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    cout << "\nHuffman Codes:\n";
    for (auto entry : codes) {
        if (entry.first == ' ')
            cout << "[space]";
        else
            cout << entry.first;

        cout << " : " << entry.second << '\n';
    }

    cout << "\nEncoded string:\n";
    for (char ch : text)
        cout << codes[ch];

    cout << '\n';

    return 0;
}
