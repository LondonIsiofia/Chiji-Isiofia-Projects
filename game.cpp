#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <algorithm>


class Room{
    public:
    std::string name;
    std::string description;
    std::map<std::string, Room*> exits;
    std::vector<std::string> items;

    Room(std::string name, std::string description) : name(name), description(description) {}

    void addExit(std::string direction, Room* room)
    {
        exits[direction] = room;
    }
    void addItem(std::string item)
    {
        items.push_back(item);
    }
    void describe()
    {
        std::cout << name << ": " << description << std::endl;
        std::cout << "Items Available: ";
        for (auto& item : items)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
        std::cout << "Exits: ";
        for (auto& exit : exits)
        {
            std::cout << exit.first << " ";
        }
        std::cout << std::endl;
    }
};

class Player
{
    private:
    Room* currentRoom;
    std::vector<std::string> inventory;

    public:
    std::string name;

    Player(std::string name, Room* startRoom) : name(name), currentRoom(startRoom) {}

    Room* getCurrentRoom() const
    {
        return currentRoom;
    }

    void move (const std::string& direction)
    {
        if (currentRoom->exits.find(direction) != currentRoom->exits.end())
        {
            currentRoom = currentRoom->exits[direction];
            std::cout << "You move " << direction << "to" <<currentRoom->name << "." << std::endl;
            currentRoom->describe();
        }
        else
        {
            std::cout << "You can't go that way!" << std::endl;
        }
    }

    void pickUpItem(const std::string& item)
    {
        auto& roomItems = currentRoom->items;
        auto it = std::find(roomItems.begin(), roomItems.end(), item);
        if (it != roomItems.end())
        {
            inventory.push_back(item);
            roomItems.erase(it);
            std::cout << "You picked up: " << item << std::endl;
        }
        else
        {
            std::cout << "Item not found in this room." << std::endl;
        }
    }

    void showInventory() const
    {
        std::cout << "Inventory: ";
        for (const auto& item : inventory)
        {
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }

    bool hasItem(const std::string& item) const 
    {
        return std::find(inventory.begin(), inventory.end(), item) != inventory.end();
    }

    void addItem(const std::string& item) 
    {
        inventory.push_back(item);
    }

    void solvePuzzle()
    {
        if (currentRoom->name != "Kingdom of Science")
        {
            std::cout << "You can only solve puzzles in the Kingdom of Science!" << std::endl;
        }
        else
        {
            if (hasItem("Stones") && hasItem("Wood") && !hasItem("Stone Tool"))
            {
                std::cout << "You combined Stones and Wood to create Stone Tools!" << std::endl;
                addItem("Stone Tool");
            }
            else if (hasItem("Stone Tool") && hasItem("Wood") && !hasItem("Sticks"))
            {
                std::cout << "You combined Stone Tools and Wood to create Sticks!" << std::endl;
                addItem("Sticks");
            }
            else if (hasItem("Rope") && hasItem("Sticks") && !hasItem("Fire"))
            {
                std::cout << "You combined Rope and Sticks to create Fire!" << std::endl;
                addItem("Fire");
            }
            else if (hasItem("Wood") && hasItem("Fire") && !hasItem("Ash"))
            {
                std::cout << "You combined Fire and Wood to create Ash!" << std::endl;
                addItem("Ash");
            }
            else if (hasItem("Fire") && hasItem("Clay") && !hasItem("Pottery"))
            {
                std::cout << "You combined Fire and Clay to create Pottery!" << std::endl;
                addItem("Pottery");
            }
            else if (hasItem("Pottery") && hasItem("Grapes") && !hasItem("Wine"))
            {
                std::cout << "You combined Pottery and Grapes to create Wine!" << std::endl;
                addItem("Wine");
            }
            else if (hasItem("Pottery") && hasItem("Wine") && hasItem("Fire") && !hasItem("Ethanol"))
            {
                std::cout << "You combined Pottery, Wine, and Fire to create Ethanol!" << std::endl;
                addItem("Ethanol");
            }
            else if (hasItem("Nitric Acid") && hasItem("Ethanol") && !hasItem("The Revival Fluid"))
            {
                std::cout << "You combined Nitric Acid and Ethanol to create The Revival Fluid!" << std::endl;
                addItem("The Revival Fluid");
            }
            else if (hasItem("Seashells") && hasItem("Stone Tool") && !hasItem("Calcium Carbonate"))
            {
                std::cout << "You combined Stone Tools and Seashells to create Calcium Carbonate!" << std::endl;
                addItem("Calcium Carbonate");
            }
            else if (hasItem("Fire") && hasItem("Ethanol") && !hasItem("Glucose"))
            {
                std::cout << "You combined Fire and Ethanol to create Glucose!" << std::endl;
                addItem("Glucose");
            }
            else if (hasItem("Nitric Acid") && hasItem("Fire") && !hasItem("Potassium Nitrate"))
            {
                std::cout << "You combined Nitric Acid and Fire to create Potassium Nitrate!" << std::endl;
                addItem("Potassium Nitrate");
            }
            else if (hasItem("Glucose") && hasItem("Potassium Nitrate") && hasItem("Sulfur") && hasItem("Ash"))
            {
                std::cout << "You combined Potassium Nitrate, Glucose, Sulfur, and Ash to create Gunpowder!" << std::endl;
                addItem("Gunpowder");
            }
            else
            {
                std::cout << "You don't have the necessary items to solve a puzzle." << std::endl;
            }
        }
    };
};

class DifficultyManager
{
    public:
    int difficultyLevel;

    DifficultyManager() : difficultyLevel(1) {}

    void adjustDifficulty(int puzzlesSolved)
    {
        if (puzzlesSolved >= 3)
        {
            difficultyLevel = 2;
        }
        else if (puzzlesSolved >= 6)
        {
            difficultyLevel = 3;
        }
        std::cout << "Difficulty adjusted to level: " << difficultyLevel << std::endl;
    }

    void provideHint()
    {
        if (difficultyLevel == 1)
        {
            std::cout << "Hint: Try combining basic elements to advance." << std::endl;
            
        }
        else if (difficultyLevel == 2)
        {
            std::cout << "Hint: Think of how Senku might solve this problem with available resources." << std::endl;
        }
        else
        {
            std::cout << "Hint: No hints available. You're on your own!" << std::endl;

        }
    }
};

int main()
{
    Room* cave = new Room("Miracle Cave", "The Cave of Miracles is a very shallow cave that appears only a few meters deep that has nitric acid ""miraculously"" dripping from the ceiling in only a single place.");
    Room* village = new Room("Ishigami Village", "A village of primitive people who were descendants of the last humans before the Stone Age.");
    Room* enemy = new Room("Empire of Might", "The Tsukasa Empire or the Empire of Might was a civilization made up of pre-petrification humans revived by Tsukasa Shishio.");
    Room* base = new Room("Kingdom of Science", "A state created by Senku Ishigami as a means to rival the Tsukasa Empire and bring science and technology back into the world.");
    Room* forest = new Room("The Stone Forest", "The forest outside the cave Senku woke up. This is the center of the world.");

    cave->addExit("east", forest);
    forest->addExit("west", cave);
    forest->addExit("north", base);
    forest->addExit("south", enemy);
    forest->addExit("east", village);
    village->addExit("west", forest);
    base->addExit("south", forest);
    enemy->addExit("north", forest);

// Items can be combined to make new items
// Goal is to defeat Tsukasa and make a generator

    cave->addItem("Nitric Acid");
    village->addItem("Iron Sand");
    forest->addItem("Rope");
    forest->addItem("Stones");
    forest->addItem("Wood");
    forest->addItem("Clay");
    forest->addItem("Grapes");
    forest->addItem("Deer");
    cave->addItem("Seashells");
    cave->addItem("Sulfur");
    village->addItem("Blast Furnace");
    village->addItem("Leather");
    village->addItem("Millet");
    village->addItem("Copper");

    Player player("Senku", cave);
    DifficultyManager aiSystem;

    std::string command;
    int puzzlesSolved = 0;

    std::cout << "Welcome to the world of Dr. Stone! You are Senku, and your goal is to rebuild civilization using science. Get EXITED!" << std::endl;
    player.getCurrentRoom()->describe();

    while (true)
    {
        std::cout << "\nEnter command (move/look/pickup [item]/inventory/solve puzzle/hint/quit): ";
        std::getline(std::cin, command);

        if (command == "quit")
        {
            std::cout << "Thanks for playing! Science Rules!" << std::endl;
            break;
        }
        else if (command == "look")
        {
            player.getCurrentRoom()->describe();
        }
        else if (command.substr(0, 4) == "move")
        {
            std::string direction = command.substr(5);
            player.move(direction);
        }
        else if (command.substr(0, 6) == "pickup")
        {
            std::string item = command.substr(7);
            player.pickUpItem(item);
        }
        else if (command == "inventory")
        {
            player.showInventory();
        }
        else if (command == "solve puzzle")
        {
            player.solvePuzzle();
            puzzlesSolved++;
            aiSystem.adjustDifficulty(puzzlesSolved);
        }
        else if (command == "hint")
        {
            aiSystem.provideHint();
        }
        else
        {
            std::cout << "Invalid command!" << std::endl;
        }
    }
    delete cave;
    delete village;
    delete enemy;
    delete base;
    delete forest;

    return 0;
}

