#include "State.h"
#include "wordwrap.h"

/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom), strength(100) {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room* State::getCurrentRoom() const {
    return this->currentRoom;
}

int State::getStrength() {
    return strength;
}

void State::setStrength(int newStrength) {
    strength = newStrength;
}

list<GameObject *> State::inventory;

void State::addObject(GameObject *invObject) {
    inventory.push_back(invObject);
}

void State::removeObject(string key) {
    auto item1 = inventory.begin();
    for (int i = 0; i < inventory.size(); i++) {
        if ((*item1)->getKey()->compare(key) == 0) {
            inventory.remove(*item1);
            setInventory(inventory);
        }
    }
}

void State::display() {
    if (inventory.begin() != inventory.end()) {
        for (auto item= inventory.begin();item !=inventory.end(); item++) {
            wrapOut((*item)->getName());
        }
    } else {
        wrapOut(&noInventory);
    }
    wrapEndPara();
}


GameObject *State::findObject(string *key) {
    GameObject *og;
    for (auto item= inventory.begin();item !=inventory.end(); item++) {
        if ((*item)->getKey()->compare(*key) == 0) {
            og = *item;
        }
    }
    return og;
}


list<GameObject *> State::getInventory() {
    return inventory;
}


void State::setInventory(list<GameObject *> invObject) {
    inventory = invObject;
}
