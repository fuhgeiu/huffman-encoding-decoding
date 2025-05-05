#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>


struct HuffmanNode {

    char ch;
    int freq;

    HuffmanNode *left, *right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {

    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

void generateCodes(HuffmanNode* root, std::string code, std::unordered_map<char, std::string>& codes) {

    if (!root) return;

    if (!root->left && !root->right) {
        codes[root->ch] = code;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

HuffmanNode* buildHuffmanTree(const std::string& text, std::unordered_map<char, int>& freqMap) {

    for (char c : text) {
        freqMap[c]++;
    }

    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;
    for (auto& pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {

        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    return pq.top();
}

std::pair<std::unordered_map<char, std::string>, std::string> compress(const std::string& text) {

    std::unordered_map<char, int> freqMap;
    HuffmanNode* root = buildHuffmanTree(text, freqMap);

    std::unordered_map<char, std::string> codes;

    generateCodes(root, "", codes);

    std::string encoded = "";

    for (char c : text) {
        encoded += codes[c];
    }

    return {codes, encoded};
}

std::string decompress(const std::string& encoded, const std::unordered_map<char, std::string>& codes) {

    std::unordered_map<std::string, char> reversed;
    for (auto& pair : codes) {
        reversed[pair.second] = pair.first;
    }

    std::string current = "", decoded = "";
    for (char bit : encoded) {
        current += bit;
        if (reversed.count(current)) {
            decoded += reversed[current];
            current = "";
        }
    }

    return decoded;
}
