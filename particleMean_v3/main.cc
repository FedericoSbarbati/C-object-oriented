#include <iostream>
#include <fstream>
#include <string>

#include "Event.h"
#include "MassMean.h"
#include "Constants.h"
#include "Utilities.h"

// Function to read an event from the file
const Event *read(std::ifstream &file);

// Function to dump the event data
void dump(const Event &ev);

using namespace std;

int main(int argc, char *argv[])
{
    // Open input file
    const string name = argv[1];
    ifstream file(name);

    // Create MassMean instances for K0 and Lambda0 particles
    MassMean k(0.495, 0.500);
    MassMean lambda(1.115, 1.116);

    // Loop over events in the file
    const Event *ev;
    while ((ev = read(file)) != nullptr)
    {
        // Dump event data
        // dump(*ev);

        // Add event to MassMean instances
        k.add(*ev);
        lambda.add(*ev);

        // Delete the event object
        delete ev;
    }

    // Compute the results for K0 and Lambda0 particles
    k.compute();
    lambda.compute();

    // Print the results for Lambda0 particles
    cout << endl;
    cout << "Results for Lambda0: " << endl;
    cout << "Number of accepted events: " << lambda.getNacceptedEv() << endl;
    cout << "Mean: " << lambda.getMean() << endl;
    cout << "RMS: " << lambda.getRMS() << endl;
    cout << endl
         << endl;

    // Print the results for K0 particles
    cout << "Results for K0: " << endl;
    cout << "Number of accepted events: " << k.getNacceptedEv() << endl;
    cout << "Mean: " << k.getMean() << endl;
    cout << "RMS: " << k.getRMS() << endl;
    cout << endl
         << endl;

    return 0;
}