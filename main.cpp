#include <chrono>
#include <fstream>
#include <iostream>

#include "trie/trie.h"

std::vector<std::string> read_lines(const char *file_path)
{
    std::ifstream file(file_path);

    std::vector<std::string> lines;

    if (file.is_open())
    {
        std::string line;

        while(std::getline(file, line))
            lines.push_back(line);

        file.close();
    }

    return lines;
}

int main()
{
    Trie *trie = new Trie();

    auto strings = read_lines("text/strings.txt");

    std::cout << "Building Trie...\n";

    auto start = std::chrono::high_resolution_clock::now();

    for(const auto &str: strings)
        trie->insert(str.data());

    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::cout << "Strings loaded in Trie: " << trie->string_count;
    std::cout <<  " (" << elapsed.count() << " ms)\n";

    while(true)
    {
        std::cout << "Search string: ";

        std::string search_string;
        std::getline(std::cin, search_string);

        start = std::chrono::high_resolution_clock::now();

        bool found = trie->contains(search_string.data());
        auto prefixed = trie->starts_with(search_string.data());

        stop = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

        if(found)
            std::cout << "\nString '" << search_string << "' found.\n";
        else
            std::cout << "\nString: '" << search_string << "' not found.\n";

        std::cout << "Strings with prefix '" << search_string << "': ";
        std::cout << prefixed.size() <<  " (" << elapsed.count() << " ms)\n\n";

        for(const auto &str: prefixed)
            std::cout << str << '\n';
    }

    return 0;
}
