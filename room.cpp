#include "Room.h"
#include <iostream>
#include <cstring>
//constructor
Room::Room(const char* roomName, const char* roomDescription) {
    strncpy(name, roomName, 50);
    strncpy(description, roomDescription, 200);
}

void Room::addExit(const char* direction, Room* room) {
    exits[direction] = room;
}
//add item to vector
void Room::addItem(const Item& item) {
    items.push_back(item);
}
//remove item from vector
bool Room::removeItem(const char* itemName, Item& removedItem) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (strncmp(it->getName(), itemName, 50) == 0) {
            removedItem = *it;
            items.erase(it);
            return true;
        }
    }
    return false;
}

//print description
void Room::print() {
    cout << "\nRoom: " << name << endl;
    cout << description << endl;

    cout << "\nExits:" << endl;
    for (auto& exit : exits) {
        cout << " - " << exit.first << endl;
    }

    cout << "\nItems in the room:" << endl;
    if (items.empty()) {
        cout << "None" << endl;
    } else {
        for (auto& item : items) {
            cout << " - " << item.getName() << endl;
        }
    }
}

Room* Room::getExit(const char* direction) {
    return exits.count(direction) ? exits[direction] : nullptr;
}