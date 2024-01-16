

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H


#include "Room.h"

class State {
    Room *currentRoom;
    int strength;

public:
    explicit State(Room *startRoom);

    void goTo(Room *target);

    void announceLoc() const;

    Room *getCurrentRoom() const;

    static list<GameObject *> inventory;

    static void addObject(GameObject *inventory);

    static void removeObject(string key);

    GameObject *findObject(string *key);

    static void display();

    list<GameObject *> getInventory();

    static void setInventory(list<GameObject *> inventory);

    void setStrength(int newStrength);

    int getStrength();

};


#endif //TEXTADV_STATE_H
