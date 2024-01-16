

#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H


#include <string>

const std::string r1name = "Room 1";
const std::string r1desc = "You are in room 1. It's really quite boring, but then, it's just for testing really. There's a passage to the north.";
const std::string r2name = "Blue Room";
const std::string r2desc = "You are the blue room. You know because it's blue. That's about all though. There's a passage to the south.";
const std::string r3name = "Red Room";
const std::string r3desc = "You are the red room. You know because it's red. That's about all though. There's a passage to the east.";
const std::string r4name = "Black Room";
const std::string r4desc = "You are the black room. You know because it's black. That's about all though. There's a passage to the west.";

const std::string o1name = "Knife(k)";
const std::string o1desc = "You can cut things with a knife.";
const std::string o1keyword = "k";
const std::string o2name = "Gun(g)";
const std::string o2desc = "You can use gun to shot.";
const std::string o2keyword = "g";
const std::string o3name = "Fire(f)";
const std::string o3desc = "You can light with fire.";
const std::string o3keyword = "f";
const std::string o4name = "Cake(c)";
const std::string o4desc = "You can eat cake to regain strength with 10.";
const std::string o4keyword = "c";

const std::string badExit = "You can't go that way.";
const std::string badCommand = "I don't understand that.";

const std::string noInventory = "Sorry, inventory is empty, you should get something from the room.";
const std::string saveHit = "Please choose one location to save: ";
const std::string saveSuc = "Congratulation, you have saved it!";

const std::string newFile = "this file not exit yet, now creat";
const std::string loadHit = "Please choose one location to load or enter 'cancel' to continue the game: ";
const std::string failLoad = "Error: File not found. Try again or enter 'cancel' to continue the game. ";

const std::string r = "Room not found.";
#endif //TEXTADV_STRINGS_H
