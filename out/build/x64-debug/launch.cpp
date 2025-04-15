#include <cstdlib>
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

void clearFile(string fileName) {
	fstream target(fileName, ios::trunc);
	target.close();
}

int main() {
	filesystem::path program = "Lab4.exe";
	for (int priority = 0; priority < 50; priority++) {
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
	

	while (true) {
		this_thread::sleep_for(chrono::seconds(1));
		clearFile("./some.txt");
	} 

	
	return 0;
}