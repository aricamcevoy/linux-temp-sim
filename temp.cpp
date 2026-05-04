#include <iostream>
#include <cstdlib>

int  main() {
	for (int i = 0; i < 5; i++) {
		float temp = 70 + (rand() % 10 - 5); // simulate temp

		std::cout << "Temp Reading: " << temp << " F" <<
std::endl;
	}
	return 0;
}
