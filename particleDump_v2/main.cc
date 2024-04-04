#include <iostream>
#include <fstream>

struct Event;

// Function prototypes
const Event *read(std::ifstream &file);
void dump(const Event &ev);
void clear(const Event *ev);

int main(int argc, char *argv[])
{
    // Open input file
    const char *name = argv[1];
    std::ifstream file(name, std::ios::binary);

    // Check if the file was opened successfully
    if (!file)
    {
        // Print an error message and return 1 to indicate an error
        std::cerr << "Errore nell'apertura del file: " << name << std::endl;
        return 1;
    }

    const Event *ev;

    // Read events from the file until there are no more
    while ((ev = read(file)) != nullptr)
    {
        dump(*ev); // Print the details of the event
        clear(ev); // Free the memory allocated to the event
    }

    return 0;
}