#include <iostream>
#include <fstream>

struct Event;

const Event *read(std::ifstream &file);
void dump(const Event &ev);
void clear(const Event *ev);

int main(int argc, char *argv[])
{
    // Open input file
    const char *name = argv[1];
    std::ifstream file(name, std::ios::binary);
    if (!file)
    {
        std::cerr << "Errore nell'apertura del file: " << name << std::endl;
        return 1;
    }

    const Event* ev;
    while ((ev = read(file)) != nullptr)
    {
        dump(*ev);
        clear(ev);
    }
    
    return 0;
}