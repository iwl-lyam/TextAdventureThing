#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
using namespace this_thread; // sleep_for, sleep_until
using namespace chrono; // nanoseconds, system_clock, seconds
using chrono::system_clock;

class Item {
  public:

  string name;
  string desc;
  string clue;
  string password;
  string correct;
  string incorrect;

  Item(string n, string d, string c, string p, string co, string ic) {
    name = n;
    desc = d;
    clue = c;
    password = p;
    correct = co;
    incorrect = ic;
  }
};

class Location {
  private:

  bool arrival_set = false;

  public:

  string name;
  string desc;
  vector<Location*> children;
  vector<Item> items;
  void (*on_arrival)();

  Location(string n, string d) {
    name = n;
    desc = d;
  }

  Location(string n, string d, void (*f)()) {
    name = n;
    desc = d;
    on_arrival = f;
    arrival_set = true;
  }

  void debug() {
    cout << name << endl;
    cout << desc << endl;
    cout << "Children" << endl << endl;
    for (Location *loc: children)
      loc->debug();
    for (Item item: items)
      cout << item.name << endl;
  }

  Location go(string locName) {
    for (Location* loc: children) {
      if (loc->name == locName)
        return *loc;
    }
    return *children.at(0);
  }

  void setArrival(void (*f)()) {
    on_arrival = f;
    arrival_set = true;
  }

  void arrival() {
    if (arrival_set) {
      on_arrival();
    } else {
      throw std::runtime_error("Arrival function not set");
    }
  }

  string go(string locName, Location *current) {
    string init = current->name;
    for (Location *loc: children) {
      if (loc->name == locName) {
        *current = *loc;
        return "Moving to "+loc->name+"...";
      }
    }
    return "You can't go there.";
  }

  vector<Location*> add_loc(Location* loc) {
    children.push_back(loc);
    return children;
  }

  vector<Item> add_item(Item loc) {
    items.push_back(loc);
    return items;
  }
};

int main() {
  // Location forest("Forest", "It's a forest. That's all there is to it.");
  // Location hub("Center room", "A circular room connecting to all the puzzles.");
  // Location river("River", "A fast river, don't get wet!");
  // hub.add_loc(&forest);
  // forest.add_loc(&hub);
  // hub.add_loc(&river);
  // Item map("Map", "Imagine having a PhD in Geography", "This code is very easy", "1234", "Yes you are amazing, that is very much correct", "You idiot");
  // forest.add_item(map);

  

  // Location current_room = hub;
  
  // cout << current_room.name << endl;
  // current_room.go("Forest", &current_room);
  // cout << current_room.name << endl;
  // current_room.go("Center room", &current_room);
  // cout << current_room.name << endl;

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

    }
    
    cout << endl;
  }
}