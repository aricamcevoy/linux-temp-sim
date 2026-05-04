#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>

int  main() {
   std::srand(std::time(nullptr));

   std::ofstream logFile("temp_log.csv");
   logFile << "timestamp,current_temp_f,average_temp_f\n";

   const int sampleWindow = 5;
   float samples[sampleWindow] = {0};
   int index = 0;
   int count = 0;

   while (true) {
      float tempF = 70.0 + ((std::rand() % 100) - 50) / 10.0;

      samples[index] = tempF;
      index = (index + 1) % sampleWindow;

      if (count < sampleWindow) count++;
      
      float sum = 0;
      for (int i =0; i < count; i++) {
         sum += samples[i];
      }

      float avg =  sum / count;

      auto now = std::time(nullptr);

      logFile << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") 
            << ", " << tempF 
            << ", " << avg 
            << "\n";

      logFile.flush();

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

   logFile.close();
   return 0;
}
