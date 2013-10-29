#include <iostream>
#include "core.h"

using namespace std;

int main(int argc, char* args[]) {
	if (init()) {
		cout << "initialization successful" << endl;
	}

	mainLoop();

	cleanup();

	return 0;
}