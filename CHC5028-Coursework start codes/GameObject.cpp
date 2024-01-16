#include "GameObject.h"
list<GameObject*> GameObject::gameObjects;


GameObject::GameObject(const string *_name, const string *_desc, const string *_key) :
        name(_name), description(_desc), keyword(_key) {}

const string *GameObject::getName() const {
    return this->name;
}

const string *GameObject::getDec() const {
    return this->description;
}


GameObject::~GameObject(){
    GameObject::gameObjects.remove(this);
}


const string *GameObject::getKey() const {
    return this->keyword;
}

void GameObject::addObject(GameObject *gameObject) {
    gameObjects.push_back(gameObject);
}