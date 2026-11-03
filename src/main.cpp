#include <iostream>
#include "obd2.h"

int main() {
    // RPM: 3000
    float rpm = decodeOBD(0x0C, 0x2E, 0xE0);

    // Boost: 11.603 PSI
    float map = decodeOBD(0x0B, 0xB4);
    float baro = decodeOBD(0x33, 0x64);
    float boost = getBoostPSI(map, baro);

    // Coolant: 194°F
    float coolant = decodeOBD(0x05, 0x82);

    std::cout << "RPM: " << rpm << '\n';
    std::cout << "Boost: " << boost << " PSI\n";
    std::cout << "Coolant: " << coolant << " F\n";

    return 0;
}