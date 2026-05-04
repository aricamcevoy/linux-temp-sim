#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

int  main() {
   std::srand(std::time(nullptr));

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

      std::cout << "Current: " << tempF << " F | Avg(" << count << "): " << avg << " F\n";

      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

   return 0;
}
