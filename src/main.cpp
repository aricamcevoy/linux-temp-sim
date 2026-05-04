#include "temperature.h"

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <filesystem>

int  main() {
   std::srand(std::time(nullptr));

   const std::string filename = "temp_log.csv";
   bool fileExists = std::filesystem::exists(filename);

   std::ofstream logFile(filename, std::ios::app);

   if (!fileExists) {
      logFile << "timestamp,current_temp_f,average_temp_f\n";
   }

   const int sampleWindow = 5;
   float samples[sampleWindow] = {0};

   int index = 0;
   int count = 0;
   float avg = 0.0;

   while (true) {
      float temp = readTemp();

      updateRollingAverage(temp, samples, sampleWindow, index, count, avg);
      displayStatus(temp, avg);
      logTemp(logFile, temp, avg);


      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

   return 0;
}
