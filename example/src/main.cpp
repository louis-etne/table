#include <iostream>
#include <string>
#include <vector>

#include "../../include/table.hpp"


int main() {
    std::vector<std::vector<std::string>> values{{"88", "0x7ffee784e96c", "0x7ffee784e960", "0x7ffee784e96c", "88"},
                                                 {"89", "0x7ffee784e96c", "0x7ffee784e960", "0x7ffee784e96c", "89"}};

    std::vector<std::string> headers{"Value", "Value address", "Pointer address", "Pointer contents", "Dereferenced pointer"};

    LE::Table table{values, headers};

    // table.set_bold_headers(true); Use bold font for the headers.
    // table.set_is_ascii(true);     Use only ASCII symbols.
    // table.set_padding_left(x);    Add x [unsigned] spaces at the left of each value.
    // table.set_padding_right(x);   Add x [unsigned] spaces at the right of each value.

    std::cout << table.set_bold_headers(true).set_padding_right(2);

    return 0;
}