#pragma clang diagnostic push
#pragma ide diagnostic ignored "LoopDoesntUseConditionVariableInspection"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <algorithm>

#include "item.h"
#include "location.h"

using namespace item;
using namespace location;
using namespace std;
using namespace this_thread; // sleep_for, sleep_until
using namespace chrono;
using chrono::system_clock;

int main() {
    bool complete = false;

    // Locations
    Location hub("Hub", "Center room connecting to other parts of the spaceship", []() -> bool {
        return true;
    },false);

    Location maintenanceshaft("Maintenance shaft", "Used by engineers to access the engines", [](){
        cout << "Dust everywhere. I don't think anyone's been down here for years." << endl;
        return true;
    }, true);

    Location cafeteria("Cafeteria", "A room with food", [&cafeteria, &maintenanceshaft]() -> bool{
        if (cafeteria.code_req) {
            cout << "The door is locked; You need to enter the code. Trust me, it's quite simple. ";
            string input;
            getline(cin, input);
            if (input == "1234") {
                cout << "How insecure. You see all the food; you won't be going hungry, let's just say that." << endl;
                sleep_for(2s);
                cafeteria.code_req = false;
                maintenanceshaft.blocked = false;
                return true;
            } else {
                cout << "A buzzer sounds. You got it wrong." << endl;
                sleep_for(2s);
                return false;
            }
        }
        return true;
    }, true, 1234);

    Location library("Library", "Enjoy a good book", [](){
        return true;
    }, true);

    Location maincorridor("Corridor", "A corridor. That's it", [](){
        cout << "Wow. Another corridor...." << endl;
      return true;
    }, false);


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
        cout << "Hurry, refuel the engines!" << endl;
      return true;
    }, false);

    // Items
    Item bat("Bat", "You can swing at things and probably break them.", [&library]() -> bool{
        cout << "You look around. You see a door saying 'Library', and you go towards it." << endl;
        sleep_for(500ms);
        cout << "You swing at the lock, and it rebounds." << endl;
        sleep_for(1s);
        cout << "You swing again, and it smashes. Don't question the physics on that.";
        library.blocked = false;

        sleep_for(2s);
        return true;
    }, {"Hub"}, false);

    int fuell = 0;
    Item fuel("Fuel", "Fuel for the engines", [&fuell]() -> bool{
        cout << "You need 60 L of fuel in the engines! Current amount: " << fuell << " L." << endl;
        sleep_for(2s);
        fuell += 1;
        if (fuell == 5) {
            cout << "The fuel tank is now full. Go back to the control room to see if the situation is fixed!" << endl;
            return true;
        }
        cout << "Fuel added!" << endl;
        sleep_for(2s);
        return true;

    }, {"Engine room"}, true);

    Item badbook("Book 1", "Orbital mechanics for dummies", []() -> bool{
        cout << "You read for a while, but nothing happened, apart from you knowing how space works now." << endl;
        sleep_for(2s);
        cout << "Let's put your new knowledge to the test: What is the specific term for the point in an orbit where a satellite is closest to the celestial body it is orbiting? ";
        string input;
        getline(cin, input);
        sleep_for(2s);
        if (input == "perigee") {
            cout << "Correct!" << endl;
            sleep_for(1s);
            return true;
        } else {
            cout << "Might need to do some more studying..." << endl;
            sleep_for(1s);
            return false;
        }
    }, {"Library"}, false);

    Location controlroom("Control room", "A room only for the most experienced of astronauts", [&badbook, &fuell, &complete]() {
        if (fuell != 5) {
            cout
                    << "The room is filled with sci-fi screens showing a mysterious planet surrounded by a ring with a white arrow at the top. ";

            if (badbook.used) {
                cout
                        << "Using your orbital mechanics knowledge, you can tell it's bad - you're going to crash into the planet, so you need to activate the engines, wherever they are."
                        << endl;
            } else {
                cout
                        << "There's red text in impact font warning about a collision, and you think that you should activate the engines to save the ship, wherever they are."
                        << endl;
            }

            sleep_for(1s);

            return true;
        } else {
            cout << "The ship has automatically activated its engines, and you are safe to explore space once again!" << endl;
            complete = true;
            return true;
        }
    }, true);

    Item cookbook("Book 2", "Jamie's 30-Minute Meals", [&cafeteria]() -> bool{
        cout << "You read the book for a while, and suddenly a voice calls out, \"Answer this question and you won't go hungry! How many garlic cloves do you add to Jamie's Quick and Easy Pasta Primavera\"? ";
        string input;
        getline(cin, input);
        sleep_for(2s);
        if (input == "2") {
            cout << "Correct! You hear locks moving and a code entry box illuminates itself." << endl;
            sleep_for(1s);
            cafeteria.unblock();
            return true;
        } else {
            cout << "What an insult. Try again." << endl;
            sleep_for(1s);
            return false;
        }
    }, {"Library"}, false);

    int hunger = 20;

    Item food("Food", "It's everybody's favourite, Nutritious Blob!", [&hunger]() -> bool{
        cout << "You eat the Nutritious Blob. It tastes disgusting." << endl;
        sleep_for(3s);
        cout << "Why does healthy food taste so bad?" << endl;
        sleep_for(2s);
        hunger = 20;
        return true;
    }, {"Cafeteria"}, true);

    Item id("Access card", "A blue card, with a magnet strip, which looks like it could grant access into a special room.", [&controlroom]() -> bool{
        cout << "You try to use the card on the reciever, and it beeps, opening the door." << endl;
        sleep_for(2s);
        controlroom.unblock();
        return true;
    }, {"Corridor"}, false);

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
    dorms.add_item(&id);
    controlroom.add_loc(&maincorridor);
    cafeteria.add_loc(&library);
    cafeteria.add_loc(&hub);
    cafeteria.add_item(&food);

    library.add_loc(&hub);
    library.add_loc(&maintenanceshaft);
    library.add_loc(&cafeteria);
    library.add_item(&badbook);
    library.add_item(&cookbook);

    Location current_room = library; //todo reset
    vector<Item> inventory;

    bool complete = false;

    while (!complete) {
        cout << "-----------------------------------" << endl;
        if (hunger < 5) cout << "Warning! You are hungry! Go eat." << endl;
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

            int i = 0;
            for (Item it: inventory) {
                if (it.name == item_n) {
                    bool useable = it.use(current_room);
                    if (!useable) {
                        cout << "You can't use that here." << endl;
                        sleep_for(1s);
                    } else {
                        inventory.erase(inventory.begin() + i);
                    }
                }
                i++;
            }

        } else {
            cout << "Please enter a valid input." << endl;
        }

        if (!cafeteria.blocked)
            hunger -= 1;

        cout << endl;
    }
}
#pragma clang diagnostic pop
#pragma clang diagnostic pop