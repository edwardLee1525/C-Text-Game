
#include "Room.h"
#include "wordwrap.h"

/**
 * Stores a static list of all rooms.
 */
std::list<Room *> Room::rooms;

/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string *_name, const string *_desc) :
        name(_name), description(_desc), north(nullptr), south(nullptr), west(nullptr), east(nullptr), gameObjects() {};

/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.remove(this);
}

/**
 * Prints the description of a room (the name and long description)
 */
void Room::describe() const {
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();

    for (auto item: this->gameObjects) {
        wrapOut(item->getName());
    }
    wrapEndPara();
}

/**
 * Statically creates a room and then adds it to the global list.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room *Room::addRoom(const string *_name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

/**
 * Adds an existing room to the static list.
 * @param room Pointer to the room to add.
 * @return
 */
void Room::addRoom(Room *room) {
    Room::rooms.push_back(room);
}

/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
Room *Room::getNorth() const {
    return this->north;
}

/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */
void Room::setNorth(Room *_north) {
    this->north = _north;
}

Room *Room::getSouth() const {
    return this->south;
}

void Room::setSouth(Room *_south) {
    this->south = _south;
}

Room *Room::getEast() const {
    return this->east;
}

void Room::setEast(Room *_east) {
    this->east = _east;
}

Room *Room::getWest() const {
    return this->west;
}

void Room::setWest(Room *_west) {
    this->west = _west;
}

list<GameObject *> Room::getGameObjects() {
    return gameObjects;
}

void Room::setGameObjects(std::list<GameObject *> gameObjects) {
    Room::gameObjects = gameObjects;
}

void Room::addObject(GameObject *gameObject) {
    Room::gameObjects.push_back(gameObject);
}

void Room::removeObject(string key) {
//    auto it1 = gameObjects.begin();
//    for (int i = 0; i < gameObjects.size(); i++) {
//        if ((*it1)->getKey()->compare(key) == 0) {
//            this->gameObjects.remove(*it1);
//            setGameObjects(gameObjects);
//        }
//    }
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ) {
        if ((*it)->getKey()->compare(key) == 0) {
            it = gameObjects.erase(it);
        } else {
            ++it;
        }
    }
}


GameObject *Room::findObject(string *key) {
    GameObject *gO;
    for (auto item: this->gameObjects) {
        if (item->getKey()->compare(*key) == 0) {
            gO = item;
        }
    }
    return gO;
}

const string *Room::getName() const {
    return this->name;
}

const string *Room::getDec() const {
    return this->description;
}


void Room::clearGameObjects() {
    Room::gameObjects.clear();
}

void Room::mergeGameObjects(list<GameObject *> temp){
    Room::gameObjects.merge(temp);
}

