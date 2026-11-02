#include <iostream>
#include "obd2.h"

int main() {
    // Simulate receiving OBD-II responses
    //decodeOBD(0x0B, 180);  // MAP pressure
    //decodeOBD(0x33, 100);  // Barometric pressure

    // Calculate and print boost
    std::cout << "Boost pressure: " << decodeOBD(0x0B, 180) << " PSI\n";

    return 0;
}