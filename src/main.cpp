#include "temperature.h"

#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <filesystem>

float currentTemp = 0.0;
float avgTemp = 0.0;

const int sampleWindow = 5;
float samples[sampleWindow] = {0};
int sampleIndex = 0;
int count = 0;

void sensorTask() {
   while(true) {
      currentTemp = readTemp();

      updateRollingAverage(currentTemp, samples, sampleWindow, sampleIndex, count, avgTemp);

      std::this_thread::sleep_for(std::chrono::seconds(1));
   }
}

void displayTask() {
   while(true) {
      displayStatus(currentTemp, avgTemp);

      std::this_thread::sleep_for(std::chrono::seconds(2));
   }
}

void loggerTask(std::ofstream &logFile) {
   while(true) {
      logTemp(logFile, currentTemp, avgTemp);

      std::this_thread::sleep_for(std::chrono::seconds(3));
   }
}

int  main() {
   std::srand(std::time(nullptr));

   const std::string filename = "temp_log.csv";
   bool fileExists = std::filesystem::exists(filename);

   std::ofstream logFile(filename, std::ios::app);

   if (!fileExists) {
      logFile << "timestamp,current_temp_f,average_temp_f\n";
   }

   std::thread t1(sensorTask);
   std::thread t2(displayTask);
   std::thread t3(loggerTask, std::ref(logFile));

   t1.join();
   t2.join();
   t3.join();

   return 0;
}
