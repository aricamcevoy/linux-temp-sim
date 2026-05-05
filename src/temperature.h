#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <fstream>

float readTemp();

void updateRollingAverage(float temp, float samples[], int sampleWindow, int &sampleIndex, int &count, float &avg);

void displayStatus(float temp, float avg);

void logTemp(std::ofstream &logFile, float temp, float avg);

#endif
