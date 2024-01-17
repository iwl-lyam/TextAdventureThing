# TextAdventureThing
It's a game according to some definitions

## item.h

`item.h` defines the namespace `item` which contains the Class `Item` and function `pickUp`.

### Class `item::Item`

This class has 6 properties:

- `string` name  
- `string` desc
- `bool` used
- `std::function<bool()>` handle
- `vector<string>` useable
- `bool` persists

This class also has 2 methods:

- Constructor
  - `string n, string d, std::function<bool()> f, vector<string> u, bool p`
- `bool` use
  - `location::Location loc`

### Function `item::pickUp`

- Returns `void`
- `string n, location::Location l, vector<Item>* i`


## location.h

`location.h` defines the namespace `loaction` which contains the Class `Location`.

### Class `location:Location`

This class has 9 properties:

- `bool` arrival_set
- `std::string` name
- `std::string` desc
- `std::vector<location::Location*>` children
- `std::vector<item::Item*>` items
- `bool` code_req
- `float` code
- `bool` blocked
- `std::function<bool()>` on_arrival

This class has 9 methods:

- Constructor
  - `const std::string n, const std::string d`
  - `const std::string n, const std::string d, std::function<bool()> f`
  - `const std::string n, const std::string d, std::function<bool()> f, bool b, float c`
  - `const std::string n, const std::string d, std::function<bool()> f, bool bc`
  - `const std::string n, const std::string d, std::function<bool()> f, float c`
- `location::Location` go
  - `const std::string locName`
  - This is the legacy method to move between Locations, please use the other one
- `std::string` go
  - `const std::string locName, location::Location* current`
- `void` setArrival
  - `std::function<bool()> f`
- `bool` arrival
- `void` unblock
- `void` block
- `std::vector<location::Location*>` add_loc
  - `location::Location*` loc
- `std::vector<item::Item*>` add_item
  - `item::Item*` loc