#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include "item.h"
#include "location.h"

using namespace item;
using namespace location;
using namespace std;
using namespace this_thread; // sleep_for, sleep_until
using namespace chrono;
using chrono::system_clock;

int main() {
    Location hub("Hub", "Center room connecting to other parts of the spaceship", []() -> bool {
        cout << "Where to go?" << endl;
        return true;
    },false);
    Location cafeteria("Cafeteria", "A room with food", [&cafeteria]() -> bool{
        cout << "You need to enter the code. ";
        string input;
        getline(cin, input);
        if (input == "1234") {
          cout << "The doors open, and you see all the food. What do you eat first?" << endl;
          cafeteria.code_req = false;
          return true;
        } else {
          cout << "A buzzer sounds. You got it wrong." << endl;
          return false;
        }
    }, false, 1234);
    Location library("Library", "Enjoy a good book", [](){
        cout << "Je pense que lire est interessant, mais je ne parle d'anglais donc je ne peux pas parler de ca!!" << endl;
      return true;
    }, true);
    Location controlroom("Control room", "A room only for the most experienced of astronauts", [](){
        cout << "You look around, and instead of seeing dials and gauges, you see offices. How perculiar." << endl;
      return true;
    }, true);
    Location maincorridor("Corridor", "A corridor. That's it", [](){
        cout << "Wow. Another corridor...." << endl;
      return true;
    }, false);
    Location maintenanceshaft("Maintenance shaft", "Used by engineers to access the engines", [](){
        cout << "Dust everywhere. I don't think anyone's been down here for years." << endl;
      return true;
    }, true);
    Location dorms("Dormitory", "Where people... sleep", [&dorms]()-> bool{
      cout << "You need to enter the code. ";
      string input;
      getline(cin, input);
      if (input == "7891") {
        cout << "You see people in the beds. Are they sleeping or are they dead?" << endl;
        dorms.code_req = false;
        return true;
      } else {
        cout << "A hand comes out of the entry box and slaps you. Wake up." << endl;
        return false;
      }
    }, false, 7891);
    Location engines("Engine room", "Don't enter without ear protection, trust me.", [](){
        cout << "Should've read the sign." << endl;
      return true;
    }, false);

    Item bat("Bat", "You can swing at things and probably break them.", [&library]() -> bool{
        cout << "You look around. You see a door saying 'Library', and you go towards it." << endl;
        sleep_for(500ms);
        cout << "You swing at the lock, and it rebounds." << endl;
        sleep_for(1s);
        cout << "You swing again, and it smashes. Don't question the physics on that.";
        library.blocked = false;
        return true;
    }, {"Hub"});

    hub.add_loc(&library);
    hub.add_loc(&cafeteria);
    hub.add_loc(&maincorridor);
    hub.add_loc(&maintenanceshaft);
    hub.add_item(&bat);

    maincorridor.add_loc(&controlroom);
    maincorridor.add_loc(&dorms);
    maincorridor.add_loc(&hub);

    maintenanceshaft.add_loc(&engines);
    maintenanceshaft.add_loc(&hub);
    maintenanceshaft.add_loc(&library);

    engines.add_loc(&maintenanceshaft);
    dorms.add_loc(&maincorridor);
    controlroom.add_loc(&maincorridor);
    cafeteria.add_loc(&library);
    cafeteria.add_loc(&hub);

    library.add_loc(&hub);
    library.add_loc(&maintenanceshaft);
    library.add_loc(&cafeteria);

    Location current_room = hub;
    vector<Item> inventory;

    bool complete = false;

    while (!complete) {
        cout << "-----------------------------------" << endl;
        cout << "You are currently in: " << current_room.name << endl << current_room.desc << endl << endl << "Would you like to view the items (input 1), view possible locations (input 2), use an item (input 3), or  view your current stats (input 4)? ";
        string input;
        getline(cin, input);

        if (input == "2") {
            cout << "Possible locations:" << endl;

            for (Location *loc: current_room.children) {
                cout << "    - " << loc->name;
                if (loc->blocked) {
                    cout << " (blocked)";
                } else if (loc->code_req) {
                  cout << " (code required)";
                }
                cout << endl;
            }

            string nextLoc;
            cout << "Where do you want to go? Leave blank to cancel. ";
            getline(cin, nextLoc);
            string res = current_room.go(nextLoc, &current_room);
            cout << res << endl << endl;
            sleep_for(1s);
        } else if (input == "1") {
            cout << "Possible items:" << endl;

            for (Item *it: current_room.items)
                if (!it->used)
                    cout << "    - " << it->name << endl;

            string item_n;
            cout << "Which item do you want to add? Leave blank to cancel. ";
            getline(cin, item_n);
            pickUp(item_n, current_room, &inventory);
            if (!item_n.empty()) {
                cout << "Picking up..." << endl;
                sleep_for(1s);
            }
        } else if (input == "4") {
            cout << "Your current stats:" << endl << endl;
            sleep_for(1s);
            cout << " Your inventory:" << endl;

            for (Item it: inventory)
                cout << "    - " << it.name << endl;

            sleep_for(1s);

            cout << endl << " Your current location: " << current_room.name << endl;

            sleep_for(2s);
        } else if (input == "3") {
            cout << " Your inventory:" << endl;

            for (Item it: inventory)
                cout << "    - " << it.name << endl;

            string item_n;
            cout << "Which item do you want to add? Leave blank to cancel. ";
            getline(cin, item_n);

            for (Item it: inventory) {
                if (it.name == item_n) {
                    bool useable = it.use(current_room);
                    if (!useable) {
                        cout << "You can't use that here." << endl;
                        sleep_for(1s);
                    }
                }
            }

        } else {
            cout << "Please enter a valid input." << endl;
        }

        cout << endl;
    }
}
#pragma clang diagnostic pop
#pragma clang diagnostic pop