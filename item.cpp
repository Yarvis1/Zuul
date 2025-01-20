#include "Item.h"
#include <iostream>
#include <cstring>

using namespace std;

// constructor
Item::Item(const char* itemName) {
    strncpy(name, itemName, 50);
}

// getter 
const char* Item::getName() const {
    return name;
}

// print
void Item::print() const {
    cout << "Item: " << name <<endl;
}
