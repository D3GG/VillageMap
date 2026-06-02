# VillageMap

VillageMap is a console-based C++ application for managing tourist information about small settlements.
The system allows users to create or load settlement files, add tourist objects, list and search objects, filter them by category, update or delete entries, and generate basic settlement reports.

**Motto:** Малките места крият големи истории

## Project idea

The application represents a small information system for tourist objects in villages and small towns.
Each settlement contains general information such as name, region, population, and description.
Inside a settlement, the user can manage different types of tourist objects.

Supported tourist object types:

* Landmark
* Restaurant
* GuestHouse
* EcoPath
* Festival
* CraftWorkshop

## Main features

* Create a new settlement file
* Load an existing settlement file
* Save settlement data
* Add tourist objects
* List all tourist objects
* Show a tourist object by ID
* Delete a tourist object by ID
* Update tourist object data
* Search by name, description, or category
* Filter objects by category
* Generate a report for the current settlement
* Command-based CLI interface with separate base and inner menu states

## Technologies

* C++17
* CMake
* Standard Template Library
* GitHub Actions for build checks
* clang-format support

## Project structure

```text
VillageMap/
├── .github/workflows/       # GitHub Actions build workflow
├── docs/                    # Architecture documentation and diagrams
├── src/                     # Source code
│   ├── Application.cpp/.h   # Main application loop and command execution
│   ├── Interface.h/.cpp     # Command registry, tokenizer, and parser
│   ├── FileManager.cpp/.h   # File loading and saving
│   ├── TouristObject.cpp/.h # Abstract base class for tourist objects
│   ├── Settlement.cpp/.h    # Settlement data and object collection
│   ├── TouristObjFactory.*  # Object creation from input or file data
│   ├── ReportGenerator.*    # Settlement report generation
│   ├── Landmark.*           # Landmark tourist object
│   ├── Restaurant.*         # Restaurant tourist object
│   ├── GuestHouse.*         # Guest house tourist object
│   ├── EcoPath.*            # Eco path tourist object
│   ├── Festival.*           # Festival tourist object
│   ├── CraftWorkshop.*      # Craft workshop tourist object
│   └── main.cpp             # Program entry point
├── CMakeLists.txt
└── README.md
```

## Build instructions

### Requirements

You need:

* A C++17 compatible compiler
* CMake 3.16 or newer
* Git

### Build on Linux/macOS

```bash
git clone https://github.com/D3GG/VillageMap.git
cd VillageMap

cmake -S . -B build
cmake --build build
```

Run the program:

```bash
./build/VillageMap
```

### Build on Windows

Using PowerShell:

```powershell
git clone https://github.com/D3GG/VillageMap.git
cd VillageMap

cmake -S . -B build
cmake --build build
```

Run the program:

```powershell
.\build\Debug\VillageMap.exe
```

Depending on the selected CMake generator, the executable may also be located directly in:

```powershell
.\build\VillageMap.exe
```

## Formatting

If `clang-format` is installed, the project provides a formatting target:

```bash
cmake --build build --target format
```

## How to use

When the program starts, it opens in the base menu.
In the base menu, you can create a new settlement file or load an existing one.

Example:

```text
create bozhentsi.txt
```

or:

```text
load bozhentsi.txt
```

After creating or loading a settlement, the program switches to the inner menu.
In the inner menu, you can manage tourist objects.

## Commands

### Base menu commands

| Command          | Description                       |
| ---------------- | --------------------------------- |
| `create <file>`  | Creates a new settlement file     |
| `load <file>`    | Loads an existing settlement file |
| `help`           | Shows available commands          |
| `help <command>` | Shows help for a specific command |
| `exit`           | Exits the program                 |

### Inner menu commands

| Command             | Description                                                |
| ------------------- | ---------------------------------------------------------- |
| `info`              | Shows information about the current settlement             |
| `add <type>`        | Adds a tourist object                                      |
| `list`              | Lists all tourist objects                                  |
| `show <id>`         | Shows one tourist object by ID                             |
| `delete <id>`       | Deletes one tourist object by ID                           |
| `update <id>`       | Updates one tourist object by ID                           |
| `search <text>`     | Searches tourist objects by text                           |
| `filter <criteria>` | Filters tourist objects by category                        |
| `report`            | Generates settlement statistics                            |
| `save`              | Saves the current settlement                               |
| `close`             | Closes the current settlement and returns to the base menu |
| `help`              | Shows available commands                                   |
| `exit`              | Exits the program                                          |

## Object type names for `add`

Use one of the following type names:

```text
add landmark
add restaurant
add guesthouse
add ecopath
add festival
add craftworkshop
```

Alternative names supported by the program include:

```text
add guest_house
add eco_path
add craft_workshop
```

## Example session

```text
===== VillageMap CLI =====
Type 'help' to see available commands.

[base]> create bozhentsi.txt

Settlement name: Bozhentsi
Region: Gabrovo
Population: 105
Description: Historical village with preserved Bulgarian Revival architecture.

Created settlement 'Bozhentsi' in file 'bozhentsi.txt'.

[inner: bozhentsi.txt]> add landmark

ID: 1
Name: Old Church
Description: A historical church in the center of the village.
Rating (0-5): 4.8
Price: 0
Historical period: Bulgarian Revival
Has guide? (y/n): y

Tourist object added successfully.

[inner: bozhentsi.txt]> list
[inner: bozhentsi.txt]> report
[inner: bozhentsi.txt]> save
[inner: bozhentsi.txt]> close
[base]> exit
```

## Data storage

Settlement data is saved in a text file.
The program handles serialization and loading automatically through the file manager.

It is recommended to edit files through the application instead of manually changing the saved file content.

## Documentation

Additional architecture documentation and diagrams are available in the `docs/` directory.

## Authors

Team VillageMap

## License

This project was created for educational purposes.

