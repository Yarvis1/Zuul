#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> 
#include "Room.h"
#include "Item.h"

using namespace std;
//sets up all rooms ,created by copilot(im not creative enough)
void setupGame(vector<Room*>& rooms) {
    // Create rooms
    Room* entrance = new Room("Entrance", "You are at the entrance of a mysterious dungeon.");
    Room* hallway = new Room("Hallway", "A dimly lit hallway stretches out before you.");
    Room* treasureRoom = new Room("Treasure Room", "Glittering treasures are piled high in this room.");
    Room* armory = new Room("Armory", "Old weapons and armor are scattered around.");
    Room* library = new Room("Library", "Dusty books line the shelves, and a faint smell of parchment lingers.");
    Room* garden = new Room("Garden", "A lush, overgrown garden with vibrant flowers.");
    Room* crypt = new Room("Crypt", "A cold, dark room with ancient tombs.");
    Room* kitchen = new Room("Kitchen", "An abandoned kitchen with rusty utensils.");
    Room* diningHall = new Room("Dining Hall", "A grand hall with a long table covered in dust.");
    Room* tower = new Room("Tower", "A spiraling staircase leads to the top of a tower.");
    Room* basement = new Room("Basement", "A damp basement with a strong smell of mildew.");
    Room* prison = new Room("Prison", "Dark cells with rusted bars line the walls.");
    Room* study = new Room("Study", "A cozy study with a roaring fireplace.");
    Room* secretRoom = new Room("Secret Room", "A hidden room filled with strange artifacts.");
    Room* finalRoom = new Room("Final Room", "A room with a glowing portal. Bring the key to win!");

    // Set up exits
   entrance->addExit("north", hallway);
    hallway->addExit("south", entrance);
    hallway->addExit("east", treasureRoom);
    hallway->addExit("west", armory);
    treasureRoom->addExit("west", hallway);
    treasureRoom->addExit("north",kitchen);
    treasureRoom->addExit("east",tower);
    armory->addExit("east", hallway);
    armory->addExit("north", library);
    library->addExit("south", armory);
    library->addExit("north", garden);
    garden->addExit("south", library);
    garden->addExit("east", crypt);
    crypt->addExit("west", garden);
    crypt->addExit("north", finalRoom);
    kitchen->addExit("west", diningHall);
    kitchen->addExit("south",treasureRoom);
    diningHall->addExit("east", kitchen);
    tower->addExit("east", basement);
    tower->addExit("north",study);
    basement->addExit("west", tower);
    basement->addExit("south", prison);
    prison->addExit("north", basement);
    study->addExit("north", secretRoom);
    study->addExit("south", tower);
    secretRoom->addExit("south", study);

    finalRoom->addExit("south", crypt);

    // Add items to rooms
    entrance->addItem(Item("Torch"));
    treasureRoom->addItem(Item("Gold Coin"));
    armory->addItem(Item("Sword"));
    library->addItem(Item("Ancient Book"));
    crypt->addItem(Item("Key"));

    // Add rooms to the vector
    rooms.push_back(entrance);
    rooms.push_back(hallway);
    rooms.push_back(treasureRoom);
    rooms.push_back(armory);
    rooms.push_back(library);
    rooms.push_back(garden);
    rooms.push_back(crypt);
    rooms.push_back(kitchen);
    rooms.push_back(diningHall);
    rooms.push_back(tower);
    rooms.push_back(basement);
    rooms.push_back(prison);
    rooms.push_back(study);
    rooms.push_back(secretRoom);
    rooms.push_back(finalRoom);
}

int main() {
    vector<Room*> rooms;
    setupGame(rooms);

    Room* currentRoom = rooms[0];//start in entrance room
    vector<Item> inventory;
    char command[50];//input
    bool hasWon = false;//if game win

    cout << "Welcome to the adventure game!" << endl;
    cout << "Your goal is to reach the Final Room with the Key." << endl;

    //game loop
    while (!hasWon) {
        currentRoom->print();

        cout << "\nWhat do you want to do? (type 'help' for commands)" << endl;
        cin.getline(command, 50);
    	// help
        if (strncmp(command, "help", 50) == 0) {
            cout << "Commands: " << endl;
            cout << " - go" << endl;
            cout << " - take [item]" << endl;
            cout << " - drop [item]" << endl;
            cout << " - inventory" << endl;
            cout << " - quit" << endl;
	//go
        } else if (strcmp(command, "go") == 0) {
            char direction[50];//asks direction
            cout<<"which direction?";
	    cin.getline(direction, 50);
	    if(strcmp(direction,"north")==0&& currentRoom->getExit("north")!= NULL){
	      currentRoom =currentRoom->getExit("north");
	    }
	    if(strcmp(direction,"south")==0&& currentRoom->getExit("south")!= NULL){
	       currentRoom =currentRoom->getExit("south");
	    }
	    
	    if(strcmp(direction,"west")==0&& currentRoom->getExit("west")!= NULL){
	       currentRoom =currentRoom->getExit("west");
	    }
	   
 	    if(strcmp(direction,"east")==0&& currentRoom->getExit("east")!= NULL){
	       currentRoom =currentRoom->getExit("east");
	    }
	    else{
	    cout<<"you cant go that way"<<endl;
	    }
	    // game win condtion
	    if (strcmp(currentRoom->name, "Final Room") == 0) {
            auto it = find_if(inventory.begin(), inventory.end(), [](const Item& item) {
                   return strcmp(item.getName(), "Key") == 0;
                    });
                    if (it != inventory.end()) {
                        cout << "Congratulations! You've used the Key to activate the portal. You win!" << endl;
                        hasWon = true;
                    } else {
                        cout << "You need the Key to win. Find it!" << endl;
                    }
            
            }
	//take
        } else if (strncmp(command, "take ", 5) == 0) {
            char itemName[50];
            strncpy(itemName, command + 5, 50);
            Item item("");
            if (currentRoom->removeItem(itemName, item)) {
                inventory.push_back(item);
                cout << "You picked up " << itemName << "." << endl;
            } else {
                cout << "That item is not here." << endl;
            }
	//drop
        } else if (strncmp(command, "drop ", 5) == 0) {
            char itemName[50];
            strncpy(itemName, command + 5, 50);
            auto it = find_if(inventory.begin(), inventory.end(), [&](Item& item) {
                return strncmp(item.getName(), itemName, 50) == 0;
            });

            if (it != inventory.end()) {
                currentRoom->addItem(*it);
                inventory.erase(it);
                cout << "You dropped " << itemName << "." << endl;
            } else {
                cout << "You don't have that item." << endl;
            }
	// display inventory
        } else if (strncmp(command, "inventory", 50) == 0) {
            cout << "Your inventory:" << endl;
            if (inventory.empty()) {
                cout << "Nothing." << endl;
            } else {
                for (auto& item : inventory) {
                    cout << " - " << item.getName() << endl;
                }
            }
        } else if (strncmp(command, "quit", 50) == 0) {
            cout << "Thanks for playing!" << endl;
            break;
        } else {
            cout << "Invalid command." << endl;
        }
    }

    for (auto room : rooms) {
        delete room;
    }

    return 0;
}
