#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H


#include "string"
#include <list>
#include "strings.h"
using namespace std;

class GameObject {

    const string *name;
    const string *description;
    const string *keyword;
public:
    GameObject(const string *_name, const string *_dec, const string *_key);
    ~GameObject();
    const string *getName() const;

    const string *getDec() const;

    const string *getKey() const;

    static void addObject(GameObject *gameObject);

    static list<GameObject*> gameObjects;
};



#endif //TEXTADV_GAMEOBJECT_H
