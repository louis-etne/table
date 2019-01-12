# Table
A header only C++ library for drawing command line tables.  

## Install
Copy __table.hpp__ into your projects directory.

## Usage 
```cpp
#include <iostream>
#include <string>
#include <vector>

#include "table.hpp"


int main() {
    std::vector<std::vector<std::string>> values{{"88", "0x7ffee784e96c", "0x7ffee784e960", "0x7ffee784e96c", "88"},
                                                 {"89", "0x7ffee784e96c", "0x7ffee784e960", "0x7ffee784e96c", "89"}};

    std::vector<std::string> headers{"Value", "Value address", "Pointer address", "Pointer contents", "Dereferenced pointer"};

    LE::Table table{values, headers};
    std::cout << table.set_bold_headers(true);

    return 0;
}
```

Running it will output:

```txt
┌───────┬────────────────┬─────────────────┬──────────────────┬──────────────────────┐
│ Value │ Value address  │ Pointer address │ Pointer contents │ Dereferenced pointer │
├───────┼────────────────┼─────────────────┼──────────────────┼──────────────────────┤
│ 88    │ 0x7ffee784e96c │ 0x7ffee784e960  │ 0x7ffee784e96c   │ 88                   │
├───────┼────────────────┼─────────────────┼──────────────────┼──────────────────────┤
│ 89    │ 0x7ffee784e96c │ 0x7ffee784e960  │ 0x7ffee784e96c   │ 89                   │
└───────┴────────────────┴─────────────────┴──────────────────┴──────────────────────┘
```

## Example
See the __example__ directory.  

Compile and run each example with:  
```bash
mkdir -p build
cd build
cmake ../
make
./table
```
