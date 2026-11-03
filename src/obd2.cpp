#include <cstdint>
#include "obd2.h"

//kPa to psi conversion
const float convertKPaPsi = 0.145038;

// Decode rpms
float decodeRPM(uint8_t A, uint8_t B) {
    return ((A * 256) + B) / 4.0f;
}

// Get Boost Pressure
float getBoostPSI(float mapPressure, float baroPressure) {\
  return (mapPressure - baroPressure) * convertKPaPsi;
}

//Gets coolant temp in farenheit. formula: subtract 40 and convert from celsius to farenheit
float calculateCoolantTemp(float temp) {
  //should return 190-220 at normal operating temp. Above 230 is a concern
  return ((temp - 40.0f) * 1.8f) + 32.0f;
}

//returns the float value associated with the given pid
//I think when i write the decode ecu reponse code i will just call the funcs in that function rather than use this switch statement since ill have to know which value the pid is for anyways
float decodeOBD(uint8_t pid, uint8_t A, uint8_t B) {

  // Swtich statement for what the ecu returns

  switch (pid) {
    //MAP Pressure
    case 0x0B: {
      return static_cast<float>(A);
    }

    //Baro Pressure
    case 0x33: {
      return static_cast<float>(A);
    }

    //RPM
    case 0x0C: {
      return decodeRPM(A, B);
    }

    //Coolant temp
    case 0x05: {
      return calculateCoolantTemp(static_cast<float>(A));
  
    }

    //Unsupported PID
    default:
      return 0.0f;
  }
}