#include <iostream>
#include <vector>
#include <string>
#include <thread>

#include "item.h"
#include "location.h"

using namespace std;
using namespace this_thread; // sleep_for, sleep_until
using namespace chrono;
using chrono::system_clock;

int main() {
    Location hub("Hub", "Center room connecting to other parts of the spaceship", [](){
        cout << "Where to go?" << endl;
    });
    Location cafeteria("Cafeteria", "A room with food", [](){
        cout << "Lots of food, what do you eat first?" << endl;
    });
    Location library("Library", "Enjoy a good book", [](){
        cout << "Je pense que lire est interessant, mais je ne parle d'anglais donc je ne peux pas parler de ca!!" << endl;
    });
    Location controlroom("Control room", "A room only for the most experienced of astronauts", [](){
        cout << "You look around, and instead of seeing dials and gauges, you see offices. How perculiar." << endl;
    });
    Location maincorridor("Corridor", "A corridor. That's it", [](){
        cout << "Wow. Another corridor...." << endl;
    });
    Location maintenanceshaft("Maintenance shaft", "Used by engineers to access the engines", [](){
        cout << "Dust everywhere. I don't think anyone's been down here for years." << endl;
    });
    Location dorms("Dormitory", "Where people... sleep", [](){
        cout << "Better be quiet here." << endl;
    });
    Location engines("Engine room", "Don't enter without ear protection, trust me.", [](){
        cout << "Should've read the sign." << endl;
    });



    hub.add_loc(&library);
    hub.add_loc(&cafeteria);
    hub.add_loc(&maincorridor);
    hub.add_loc(&maintenanceshaft);

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

    while (true) {
        cout << "-----------------------------------" << endl;
        cout << "You are currently in: " << current_room.name << endl << current_room.desc << endl << endl << "Would you like to view the items (input 1) or possible locations (input 2)? ";
        string input;
        getline(cin, input);

        if (input == "2") {
            cout << "Possible locations:" << endl;

            for (Location *loc: current_room.children)
                cout << "    - " << loc->name << endl;

            string nextLoc;
            cout << "Where do you want to go? ";
            getline(cin, nextLoc);
            string res = current_room.go(nextLoc, &current_room);
            cout << res << endl << endl;
            sleep_for(1s);

            current_room.arrival();

        } else if (input == "1") {
            cout << "Possible items:" << endl;

            for (Item *it: current_room.items)
                if (!it->used)
                    cout << "    - " << it->name << endl;
        }

        cout << endl;
    }
}