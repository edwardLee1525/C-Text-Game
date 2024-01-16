#include "FoodObject.h"
list<FoodObject*> FoodObject::foodObjects;

FoodObject::FoodObject(const string *_name, const string *_dec, const string *_key, int _energy)
        : GameObject(_name, _dec, _key) {
    if (_energy >= 1 && _energy <= 10) {
        energy = _energy;
    } else {
        energy = 1;
    }
}

void FoodObject::addObject(FoodObject *foodObject) {
    foodObjects.push_back(foodObject);
}

int FoodObject::getEnergy() const {
    return energy;
}

bool FoodObject::isFood(string *key)  {
    for (auto item : FoodObject::foodObjects) {
        if (item->getKey()->compare(*key) == 0) {
            return true;
        }
    }
    return false;
}

FoodObject* FoodObject::findFoodByKey(const string &key) {
    for (auto& item : foodObjects) {
        if (item->getKey()->compare(key) == 0) {
            return item;
        }
    }
    return nullptr;
}
