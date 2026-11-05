#pragma once
#include <cstdint>
#include <vector>

extern float mapPressure;
extern float baroPressure;

float decodeRPM(uint8_t A, uint8_t B);
float getBoostPSI(float mapPressure, float baroPressure);
float decodeOBD(uint8_t pid, uint8_t A, uint8_t B = 0);
float decodeECUResponse(const std::vector<uint8_t> &response);
