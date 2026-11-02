#include <iostream>
#include <cstdint>
#include "obd2.h"

//kPa to psi
const float convertKPaPsi = 0.145038;

float mapPressure = 0;
float baroPressure = 0;

// Decode rpms
float decodeRPM(uint8_t A, uint8_t B) {
    return ((A * 256) + B) / 4.0f;
}

// Get Boost Pressure
float getBoostPSI(float mapPressure, float baroPressure) {
    return (mapPressure - baroPressure) * convertKPaPsi;
}

//Mode 01 PID 0B (Intake manifold absolute pressure) - Mode 01 PID 33 (Absolute Barometric Pressure)

float decodeOBD(uint8_t pid, uint8_t A) {

  // Swtich statement for what the ecu returns

  switch (pid) {
    case 0x0B: {
      return static_cast<float>(A);
    }
  }
}
