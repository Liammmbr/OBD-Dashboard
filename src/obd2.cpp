#include "obd2.h"
#include <cstdint>
#include <iostream>
#include <vector>

// kPa to psi conversion
const float convertKPaPsi = 0.145038;

// Decode rpms
float decodeRPM(uint8_t A, uint8_t B) { return ((A * 256) + B) / 4.0f; }

// Get Boost Pressure
float getBoostPSI(float mapPressure, float baroPressure) {
  return (mapPressure - baroPressure) * convertKPaPsi;
}

// Gets coolant temp in farenheit. formula: subtract 40 and convert from celsius
// to farenheit
float calculateCoolantTemp(float temp) {
  // should return 190-220 at normal operating temp. Above 230 is a concern
  return ((temp - 40.0f) * 1.8f) + 32.0f;
}

// CAN ID: 7E8
// Data:   04 41 0C 2E E0 00 00 00

float decodeECUResponse(const std::vector<uint8_t> &response) {

  // Check that the response contains at least a mode and a PID
  if (response.size() < 3) {
    std::cout << "Invalid response length\n";
    return 0.0f;
  }

  // Check for positive Mode 01 response
  if (response[0] != 0x41) {
    std::cout << "Invalid response mode\n";
    return 0.0f;
  }

  // Swtich statement for what the ecu returns
  uint8_t pid = response[1];
  uint8_t A = response[2];
  uint8_t B = 0;
  if (response.size() > 3) {
    B = response[3];
  }

  switch (pid) {
  // MAP Pressure
  case 0x0B: {
    return static_cast<float>(A);
  }

  // Baro Pressure
  case 0x33: {
    return static_cast<float>(A);
  }

  // RPM
  case 0x0C: {
    return decodeRPM(A, B);
  }

  // Coolant temp
  case 0x05: {
    return calculateCoolantTemp(static_cast<float>(A));
  }

  // Unsupported PID
  default:
    std::cout << "Invalid PID\n";
    return 0.0f;
  }
}
