#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iterator>
#include <random>
#include <stdexcept>
#include "list_de.hpp"

std::string join(const std::vector<std::string>& elements, const char* separator) {
    switch (elements.size()) {
        case 0:
            return "";
        case 1:
            return elements[0];
        default:
            std::ostringstream os;
            std::copy(elements.begin(), elements.end() - 1, std::ostream_iterator<std::string>(os, separator));
            os << *elements.rbegin();
            return os.str();
    }
}

std::random_device rd;

const int dice(const int max) {
    std::default_random_engine e1(rd());
    std::uniform_int_distribution<int> uniform_dist(0, max - 1);

    return uniform_dist(e1);
}

int main(int argc, char** argv) {
    int count = 6;
    std::vector<std::string> out;
    std::vector<std::string> wordlist;

    try {
        if (std::locale("").name().substr(0, 2) == "de") {
            wordlist = list::list_de;
        } else {
            wordlist = list::list_en;
        }
    } catch (std::runtime_error) {
        wordlist = list::list_en;
    }


    if (argc > 1) {
        count = atoi(argv[1]);
    }

    for (int c = 0; c < count; c++) {
        out.push_back(wordlist[dice(wordlist.size())]);
    }

    std::cout << join(out, " ") << std::endl;

    return 0;
}

