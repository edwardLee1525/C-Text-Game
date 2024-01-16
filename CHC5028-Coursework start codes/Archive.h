#ifndef TEXTADV_ARCHIVE_H
#define TEXTADV_ARCHIVE_H

#include <fstream>
#include <vector>
#include "State.h"
#include "wordwrap.h"
#include <iostream>
#include "strings.h"
#include "FoodObject.h"


class Archive {
    Room *room;
    list<GameObject *> inventory;
    State *s;


public:
    vector<GameObject> objectArchive;

    Archive(State *state);

    int objectIndex(string keyword);

    GameObject *loadObject(string index);

    void allObjects();

    int save();

    State *load();

};


#endif //TEXTADV_ARCHIVE_H