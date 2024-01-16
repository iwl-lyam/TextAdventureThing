# TextAdventureThing
It's a game according to some definitions

## item.h

`item.h` defines the namespace `item` which contains the Class `Item` and function `pickUp`.

### Class `Item`

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

### Function `pickUp`

- Returns `void`
- `string n, location::Location l, vector<Item>* i`


## location.h

`location.h` defines the namespace `loaction` which contains the Class `Location`.