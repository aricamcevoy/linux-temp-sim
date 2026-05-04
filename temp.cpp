#include <iostream>
#include <cstdlib>
#include <ctime>

int  main() {
	std::srand(std::time(nullptr));

	const int sampleCount = 10;
	float sum = 0.0;

	std::cout << "Temperature Simulation\n";
	std::cout << "Taking " << sampleCount << " samples...\n\n";

	for (int i = 1; i <= sampleCount; i++) {
		float tempF = 70.0 + ((std::rand() % 100) - 50) / 10.0; 

		std::cout << "Sample " << i << ": " << tempF << " F\n";

		sum += tempF;
	}

	float average = sum / sampleCount;

	std::cout << "\nAverage Temp: " << average << " F\n";

	return 0;
}
