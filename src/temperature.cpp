#include "temperature.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

float readTemp() {
   return 70.0 + ((std::rand() % 100) - 50) / 10.0;
}

void updateRollingAverage(float temp, float samples[],  int sampleWindow, int &index, int &count, float &avg) {
   samples[index] = temp;
   index = (index + 1) % sampleWindow;

   if (count < sampleWindow) {
      count++;
   }

   float sum = 0.0;

   for (int i = 0; i < count; i++) {
      sum += samples[i];
   }

   avg = sum / count;
}

void displayStatus(float temp, float avg) {
   std::cout << "Current " << temp << " F | Avg " << avg << " F" << std::endl;
}

void logTemp(std::ofstream &logFile, float temp, float avg) {
   auto now = std::time(nullptr);

   logFile << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << ", " << temp << ", " << avg << "\n";

   logFile.flush();

}
