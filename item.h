#ifndef ITEM_H
#define ITEM_H

#include <cstring>
#include <iostream>

// item class
class Item {
private:
    char name[50];

public:

    // constructor
    Item(const char* itemName);

    // getter 
    const char* getName() const;

    // Print 
    void print() const;
};

#endif