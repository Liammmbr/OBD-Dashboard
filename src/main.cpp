#include "obd2.h"
#include <cstdint>
#include <iostream>
#include <vector>

int main() {
  // RPM: 3000
  float rpm = decodeECUResponse({0x41, 0x0C, 0x2E, 0xE0});

  // Boost: 11.603 PSI
  float map = decodeECUResponse({0x41, 0x0B, 0xB4});
  float baro = decodeECUResponse({0x41, 0x33, 0x64});
  float boost = getBoostPSI(map, baro);

  // Coolant: 194°F
  float coolant = decodeECUResponse({0x41, 0x05, 0x82});

  // Print decoded values
  std::cout << "=== OBD-II Dashboard ===\n";
  std::cout << "RPM: " << rpm << '\n';
  std::cout << "Boost: " << boost << " PSI\n";
  std::cout << "Coolant: " << coolant << " F\n";

  // Test invalid responses
  std::cout << "\n=== Error Testing ===\n";

  // Invalid response mode
  decodeECUResponse({0x42, 0x0C, 0x2E, 0xE0});

  // Unsupported PID
  decodeECUResponse({0x41, 0xFF, 0x64});

  // Missing data
  decodeECUResponse({0x41, 0x0C});

  // Missing second RPM byte
  decodeECUResponse({0x41, 0x0C, 0x2E});

  return 0;
}