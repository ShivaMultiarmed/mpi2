#include <cstdlib>
#include <filesystem>
#include <string>
#include <iostream>
#include <thread>

using namespace std;

int main() {
	filesystem::path program = "Lab4.exe";
	
	for (int priority = 0; priority < 100; priority++) {
		string writerArg;
		int probability = rand() % 100;
		if (probability < 50) {
			writerArg = "--writer";
		}
		else {
			writerArg = "--reader";
		}
		string args = writerArg + " " + to_string(priority);
		string command = "start /b " + program.string() + " " + args;
		system(command.c_str());
		cout << "Launching: " + command << endl;
	}
	this_thread::sleep_for(chrono::milliseconds(10000));
	
	return 0;
}