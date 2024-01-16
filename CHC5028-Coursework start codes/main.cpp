#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "FoodObject.h"
#include <map>
#include "Archive.h"

using std::string;
using std::unique_ptr;
using namespace std;

string commandBuffer;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto *r2 = new Room(&r2name, &r2desc);
    auto *r1 = new Room(&r1name, &r1desc);
    auto *r3 = new Room(&r3name, &r3desc);
    auto *r4 = new Room(&r4name, &r4desc);

//    Room room3(&r1name, &r1desc);
//    Room *r3 = &room3;
    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
//    Room::addRoom(&r3name, &r3desc)
    r1->setNorth(r2);
    r2->setSouth(r1);
    r2->setWest(r3);
    r2->setEast(r4);
    r3->setEast(r2);
    r4->setWest(r2);

    auto *o1 = new GameObject(&o1name, &o1desc, &o1keyword);
    auto *o2 = new GameObject(&o2name, &o2desc, &o2keyword);
    auto *o3 = new GameObject(&o3name, &o3desc, &o3keyword);
    auto *o4 = new GameObject(&o4name, &o4desc, &o4keyword);
    auto *f4 = new FoodObject(&o4name, &o4desc, &o4keyword, 10);
    GameObject::addObject(o1);
    GameObject::addObject(o2);
    GameObject::addObject(o3);
    GameObject::addObject(o4);
    FoodObject::addObject(f4);
    r1->addObject(o1);
    r1->addObject(o2);
    r1->addObject(o3);
    r1->addObject(o4);
    r2->addObject(o2);
    r3->addObject(o3);
    r4->addObject(o1);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}


/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver = false;
    while (!gameOver and currentState->getStrength() > 0) {
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        string secondWord;
        bool exit1 = false;
        bool exit2 = false;
        bool food = false;
        GameObject *object1, *object2;
        int strength = currentState->getStrength();
        currentState->setStrength(strength - 10);
        Archive archive(currentState);


        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));

        if (commandBuffer.substr(0, endOfVerb) == "load") {
            State* loadedState = archive.load();
            if (loadedState != nullptr) {
                currentState = loadedState;
                currentState->announceLoc();
            } else {
                currentState->announceLoc();
                wrapEndPara();
            }
            commandOk = true;
        }

        if (commandBuffer.substr(0, endOfVerb) == "save") {
            archive.save();
            commandOk = true;
        }

        map<string, Room *> world{{"north", currentState->getCurrentRoom()->getNorth()},
                                  {"n",     currentState->getCurrentRoom()->getNorth()},
                                  {"south", currentState->getCurrentRoom()->getSouth()},
                                  {"s",     currentState->getCurrentRoom()->getSouth()},
                                  {"west",  currentState->getCurrentRoom()->getWest()},
                                  {"w",     currentState->getCurrentRoom()->getWest()},
                                  {"east",  currentState->getCurrentRoom()->getEast()},
                                  {"e",     currentState->getCurrentRoom()->getEast()}};

        map<string, Room *>::iterator it;
        it = world.find(commandBuffer.substr(0, endOfVerb));
        if (it != world.end()) {
            commandOk = true; /* Confirm command has been handled */
            Room *next_room = it->second; /* get the value */
            if (next_room == nullptr) { /* there isn't */
                wrapOut(&badExit);      /* Output the "can't go there" message */
                wrapEndPara();
            } else {                    /* There is */
                currentState->goTo(next_room); /* Update state to that room - this will also describe it */
            }
        }


        if (commandBuffer.length() > endOfVerb) {
            secondWord = commandBuffer.substr(endOfVerb + 1, commandBuffer.length());
            object1 = currentState->getCurrentRoom()->findObject(&secondWord);
            object2 = currentState->findObject(&secondWord);
            food = FoodObject::isFood(&secondWord);
            list<GameObject *> gameObjects = currentState->getCurrentRoom()->getGameObjects();
            list<GameObject *> invObjects = currentState->getInventory();

            for (auto item = gameObjects.begin(); item != gameObjects.end(); item++) {
                if ((*item)->getKey()->compare(secondWord) == 0) {
                    exit1 = true;
                }
            }

            for (auto item = invObjects.begin(); item != invObjects.end(); item++) {
                if (*(*item)->getKey() == secondWord) {
                    exit2 = true;
                }
            }
        }

        if (commandBuffer.compare(0, endOfVerb, "inventory") == 0) {
            commandOk = true;
            currentState->display();
        }

        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
        /* Command to go north. */
//        if ((commandBuffer.compare(0, endOfVerb, "north") == 0) || (commandBuffer.compare(0, endOfVerb, "n") == 0)) {
//            commandOk = true; /* Confirm command has been handled */
//            /* See if there's a north exit */
//            Room *northRoom = currentState->getCurrentRoom()->getNorth();
//            if (northRoom == nullptr) { /* there isn't */
//                wrapOut(&badExit);      /* Output the "can't go there" message */
//                wrapEndPara();
//            } else {                    /* There is */
//                currentState->goTo(northRoom); /* Update state to that room - this will also describe it */
//            }
//        }
//
//        if ((commandBuffer.compare(0, endOfVerb, "south") == 0) || (commandBuffer.compare(0, endOfVerb, "s") == 0)) {
//            commandOk = true; /* Confirm command has been handled */
//
//            Room *southRoom = currentState->getCurrentRoom()->getSouth();
//            if (southRoom == nullptr) { /* there isn't */
//                wrapOut(&badExit);      /* Output the "can't go there" message */
//                wrapEndPara();
//            } else {                    /* There is */
//                currentState->goTo(southRoom); /* Update state to that room - this will also describe it */
//            }
//        }
//
//        if ((commandBuffer.compare(0, endOfVerb, "west") == 0) || (commandBuffer.compare(0, endOfVerb, "w") == 0)) {
//            commandOk = true; /* Confirm command has been handled */
//
//            Room *westRoom = currentState->getCurrentRoom()->getWest();
//            if (westRoom == nullptr) { /* there isn't */
//                wrapOut(&badExit);      /* Output the "can't go there" message */
//                wrapEndPara();
//            } else {                    /* There is */
//                currentState->goTo(westRoom); /* Update state to that room - this will also describe it */
//            }
//        }
//
//        if ((commandBuffer.compare(0, endOfVerb, "east") == 0) || (commandBuffer.compare(0, endOfVerb, "e") == 0)) {
//            commandOk = true; /* Confirm command has been handled */
//            /* See if there's a north exit */
//            Room *eastRoom = currentState->getCurrentRoom()->getEast();
//            if (eastRoom == nullptr) { /* there isn't */
//                wrapOut(&badExit);      /* Output the "can't go there" message */
//                wrapEndPara();
//            } else {                    /* There is */
//                currentState->goTo(eastRoom); /* Update state to that room - this will also describe it */
//            }
//        }

        if (commandBuffer.compare(0, endOfVerb, "get") == 0) {
            commandOk = true;
            if (exit1 and !exit2) {
                currentState->addObject(object1);
                currentState->getCurrentRoom()->removeObject(secondWord);
                currentState->announceLoc();
            } else if (exit1 and exit2) {
                std::cout << "this object is already in inventory" << std::endl;
            } else if (!exit1 and exit2) {
                std::cout << "this object is not in the room" << std::endl;
            } else if (!exit1 and !exit2) {
                std::cout << "this object is not exist" << std::endl;
            }
        }

        if (commandBuffer.compare(0, endOfVerb, "drop") == 0) {
            commandOk = true;
            if (exit2 and !exit1) {
                currentState->getCurrentRoom()->addObject(object2);
                currentState->removeObject(secondWord);
                currentState->announceLoc();
            } else if (exit1 and exit2) {
                std::cout << "this object is already in the room" << std::endl;
            } else if (exit1 and !exit2) {
                std::cout << "this object is not in inventory" << std::endl;
            } else if (!exit1 and !exit2) {
                std::cout << "this object is not exist" << std::endl;
            }
        }


        if (commandBuffer.compare(0, endOfVerb, "examine") == 0) {
            commandOk = true;
            if (exit1) {
                std::cout << *object1->getDec() << std::endl;
            } else if (exit2) {
                std::cout << *object2->getDec() << std::endl;
            } else {
                std::cout << "this object is not exist" << std::endl;
            }
        }

        if (commandBuffer.compare(0, endOfVerb, "eat") == 0) {
            commandOk = true;
            if (exit2) {
                FoodObject *foodItem = FoodObject::findFoodByKey(secondWord);

                if (foodItem != nullptr) {
                    int energy = foodItem->getEnergy();
                    int newStrength = currentState->getStrength() + energy;
                    currentState->removeObject(secondWord);
                    if (newStrength > 100) {
                        newStrength = 100;
                    }
                    
                    currentState->setStrength(newStrength);
                    std::cout << "You have eaten " << *foodItem->getName() << ". Strength is now " << newStrength
                              << std::endl;
                } else {
                    std::cout << "You cannot eat this." << std::endl;
                }
            } else {
                std::cout << "This object is not in inventory." << std::endl;
                std::cout << "Strength is now " << currentState->getStrength() << std::endl;
            }
        }

//        if (commandBuffer.compare(0, endOfVerb, "eat") == 0) {
//            commandOk = true;
//            if (exit2) {
//                FoodObject* foodItem = dynamic_cast<FoodObject*>(object2);
//                if (foodItem != nullptr) {
//                    int energy = foodItem->getEnergy();
//                    int newStrength = min(100, currentState->getStrength() + energy);
//                    currentState->setStrength(newStrength);
//                    std::cout << "You have eaten " << *foodItem->getName() << ". Strength is now " << newStrength << std::endl;
//                } else {
//                    std::cout << "You cannot eat this." << std::endl;
//                }
//            } else {
//                std::cout << "You don't have that item." << std::endl;
//            }
//        }


        /* Quit command */
        if ((commandBuffer.compare(0, endOfVerb, "quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if (!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }
    }
    if (currentState->getStrength() == 0) {
        cout << "You're out of strength." << endl;
    }
}


int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}