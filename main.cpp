#include "encoding_decoding.h"

int main() {

    std::string input = "Hello World";

    auto [codes, encoded] = compress(input);

    std::cout << "Huffman Codes:\n";

    for (auto& pair : codes) {
        std::string symbol = (pair.first == ' ') ? "space" : std::string(1, pair.first);
        std::cout << symbol << "\t" << pair.second << "\n";
    }

    std::cout << "\nEncoded String:\n" << encoded << "\n";

    std::string decoded = decompress(encoded, codes);

    std::cout << "\nDecoded String:\n" << decoded << "\n";

    return 0;
}
