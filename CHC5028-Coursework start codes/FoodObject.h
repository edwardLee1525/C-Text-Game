#ifndef TEXTADV_FOODOBJECT_H
#define TEXTADV_FOODOBJECT_H


#include "GameObject.h"

class FoodObject : public GameObject {
    int energy;

public:
    FoodObject(const string *_name, const string *_dec, const string *_key, int _energy);
    int getEnergy() const;
    static list<FoodObject*> foodObjects;

    static void addObject(FoodObject *foodObject);

    static bool isFood(string *key);
    static FoodObject* findFoodByKey(const string &key);

};


#endif //TEXTADV_FOODOBJECT_H
