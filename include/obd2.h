#pragma once
#include <cstdint>

extern float mapPressure;
extern float baroPressure;

float decodeRPM(uint8_t A, uint8_t B);
float getBoostPSI(float mapPressure, float baroPressure);
float decodeOBD(uint8_t pid, uint8_t A);