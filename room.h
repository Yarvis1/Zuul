#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <map>
#include "Item.h"

using namespace std;

// Room class to represent a room in the game
class Room {
private:
   
    char description[200];
    map<const char*, Room*> exits; // maps exit directions to other rooms
    vector<Item> items;           // items in the room

public:
//constructor
    Room(const char* roomName, const char* roomDescription);
    char name[50];
    void addExit(const char* direction, Room* room);
    void addItem(const Item& item);
    bool removeItem(const char* itemName, Item& removedItem);
    //print description
    void print();
    Room* getExit(const char* direction);
};

#endif