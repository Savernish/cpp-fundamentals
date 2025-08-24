#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

int main() {
    // --- std::vector ---
    std::cout << "--- std::vector example ---" << std::endl;
    std::vector<std::string> words = {"this", "is", "a", "sentence", "and", "this", "is", "another"};
    words.push_back("one"); // Add an element to the end

    for (const auto& word : words) {
        std::cout << word << " ";
    }
    std::cout << "\nVector size: " << words.size() << std::endl;

    // --- std::unordered_map ---
    std::cout << "\n--- std::unordered_map example ---" << std::endl;
    std::unordered_map<std::string, int> word_counts;
    for (const auto& word : words) {
        word_counts[word]++; // Increment count for the word
    }

    for (const auto& pair : word_counts) {
        std::cout << "Word: '" << pair.first << "', Count: " << pair.second << std::endl;
    }

    return 0;
}