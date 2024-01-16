#include "Archive.h"

Archive::Archive(State *state) :
        s(state), room(nullptr), inventory() {};

void Archive::allObjects() {
    for (auto item: GameObject::gameObjects) {
        objectArchive.push_back(*item);
    }
}

int Archive::objectIndex(std::string keyword) {
    for (auto item = objectArchive.begin(); item != objectArchive.end(); item++) {
        if (*item->getKey() == keyword) {
            return (item - objectArchive.begin());
        }
    }
    return -1;
}

std::string caesarEncryptAll(const std::string& input, int shift) {
    std::string output = input;
    for (char &c : output) {
        unsigned char shifted = static_cast<unsigned char>(c) + shift;
        c = static_cast<char>(shifted);
    }
    return output;
}

std::string caesarDecryptAll(const std::string& input, int shift) {
    std::string output = input;
    for (char &c : output) {
        unsigned char shifted = static_cast<unsigned char>(c) - shift;
        c = static_cast<char>(shifted);
    }
    return output;
}

GameObject *Archive::loadObject(std::string index) {
    int objectInt = atoi(index.c_str());
    return &(objectArchive[objectInt]);
}

int Archive::save() {
    allObjects();
    std::ofstream gameSave;
    std::string saveLocation;
    this->room = s->getCurrentRoom();
    this->inventory = s->getInventory();
    wrapOut(&saveHit);
    getline(std::cin, saveLocation);
    wrapEndPara();
    gameSave.open(saveLocation + ".txt", ios::out | ios::trunc | ios::binary);
    if (gameSave.fail()) {
        wrapOut(&newFile);
        wrapEndPara();
    }

    if (!gameSave.is_open())
        return 0;

    gameSave << caesarEncryptAll(*room->getName(), 3) << std::endl;
    gameSave << caesarEncryptAll(std::to_string(this->s->getStrength()), 3) << std::endl;


    for (auto r: Room::rooms) {
        gameSave << r->getGameObjects().size() << std::endl;
        for (auto item1: r->getGameObjects()) {
            gameSave << objectIndex(*item1->getKey()) << std::endl;
        }
    }

    gameSave << inventory.size() << std::endl;
    for (auto item = inventory.begin(); item != inventory.end(); item++) {
        gameSave << objectIndex(*(*item)->getKey()) << std::endl;
    }

    gameSave.close();
    wrapOut(&saveSuc);
    wrapEndPara();
    return 0;
}


State *Archive::load() {
    allObjects();
    std::ifstream gameLoad;
    string loadLocation;

    while (true) {
        wrapOut(&loadHit);
        getline(std::cin, loadLocation);
        wrapEndPara();

        gameLoad.open(loadLocation + ".txt");

        if (gameLoad.good()) {
            std::string roomName, roomDec;
            getline(gameLoad, roomName);
            roomName = caesarDecryptAll(roomName, 3);
            Room *currentRoom;
            for (auto r: Room::rooms) {
                if (roomName == *r->getName()) {
                    currentRoom = r;
                }
            }
            State *newState = new State(currentRoom);
            std::string strengthStr;
            getline(gameLoad, strengthStr);
            strengthStr = caesarDecryptAll(strengthStr, 3);
            int strength = std::stoi(strengthStr);
            newState->setStrength(strength);

            list<GameObject *> temp;
            for (auto item: Room::rooms) {
                temp.clear();
                int countRoomOb;
                gameLoad >> countRoomOb;
                for (int i = 0; i < countRoomOb; ++i) {
                    std::string index;
                    gameLoad >> index;
                    temp.push_back(loadObject(index));
                }
                item->clearGameObjects();
                item->mergeGameObjects(temp);
            }

            int countOb;
            gameLoad >> countOb;
            temp.clear();
            for (int i = 0; i < countOb; ++i) {
                std::string index;
                gameLoad >> index;
                temp.push_back(loadObject(index));
            }
            s->inventory.clear();
            s->inventory.merge(temp);


            gameLoad.close();
            return newState;
        } else {

            if (loadLocation == "cancel") {
                return nullptr;
            }

            wrapOut(&failLoad);
            wrapEndPara();

            gameLoad.clear();
            gameLoad.close();
        }
    }
}