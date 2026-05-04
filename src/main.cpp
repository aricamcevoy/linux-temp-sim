#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>
#include <filesystem>

float readTemp();
void updateRollingAverage(float temp, float samples[], int sampleWindow, int &index, int &count, float &avg);
void displayStatus(float temp, float avg);
void logTemp(std::ofstream &logFile, float temp, float avg);

int  main() {
   std::srand(std::time(nullptr));

   const std::string filename = "temp_log.csv";
   bool exists = std::filesystem::exists(filename);

   std::ofstream logFile(filename, std::ios::app);

   if (!exists) {
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

float readTemp() {
   float temp = 70.0 + ((std::rand() % 100) - 50) / 10.0;

   return temp;
}

void updateRollingAverage(float temp, float samples[], int sampleWindow, int &index, int &count, float &avg) {
   samples[index] = temp;
   index = (index + 1) % sampleWindow;

   if (count < sampleWindow) count++;

   float sum = 0;

   for (int i =0; i < count; i++) {
      sum += samples[i];
   }

   avg =  sum / count;
}

void displayStatus(float temp, float avg) {
   std::cout << "Current: " << temp << " F | Avg: " << avg << " F" << std::endl;
}

void logTemp(std::ofstream &logFile, float temp, float avg) {
   auto now = std::time(nullptr);

   logFile << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S")
         << ", " << temp
         << ", " << avg
         << "\n";

   logFile.flush();

}
