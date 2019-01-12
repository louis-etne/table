#include <iostream>
#include <string>
#include <vector>

#include "../../include/table.hpp"


int main() {
    std::vector<std::vector<std::string>> values{{"88", "0x7ffee784e96c", "0x7ffee784e960", "0x7ffee784e96c", "88"},
                                                 {"89", "0x7ffee784e96c", "0x7ffee784e960", "0x7ffee784e96c", "89"}};

    std::vector<std::string> headers{"Value", "Value address", "Pointer address", "Pointer contents", "Dereferenced pointer"};

    LE::Table table{values, headers};
    std::cout << table.set_bold_headers(true);

    return 0;
}