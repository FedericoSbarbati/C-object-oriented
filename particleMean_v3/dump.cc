#include <iostream>
#include "Event.h"

using namespace std;

void dump(const Event &ev)
{
    cout << ev.getnParticle() << endl;
    cout << ev.getX() << ' ' << ev.getY() << ' ' << ev.getZ() << endl;

    for (int i = 0; i < ev.getnParticle(); i++)
    {
        Event::part_ptr p = ev.particle(i);
        cout << ' ' << p->charge << ' '
             << p->px << ' ' << p->py << ' ' << p->pz << endl;
    }

    return;
}