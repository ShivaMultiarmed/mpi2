// Lab4.cpp: определяет точку входа для приложения.
//
#include <boost/interprocess/sync/named_mutex.hpp>
#include "Lab4.h"
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;
using namespace boost::interprocess;

int main(int argc, char** argv)
{
	bool isWriter = string(argv[1]) == "--writer";
	int priority = stoi(argv[2]);
	const string filePath = "./some.txt";
	named_mutex fileMutex(open_or_create, "file_mutex");
	fstream fileStream;
	for (int i = 0; i < 100; i++) {
		if (isWriter) {
			scoped_lock<named_mutex> lock(fileMutex);
			fileStream = fstream(filePath, ios::out | ios::app);
			char byte = 'X';
			fileStream.write(&byte, sizeof(char));
			cout << "Writer with priority " << priority << " wrote " << "\"X\" to file: " << filePath << endl;
		}
		else {
			scoped_lock<named_mutex> lock(fileMutex, try_to_lock);
			if (lock) {
				fileStream = fstream(filePath, ios::in);
				char byte;
				fileStream.read(&byte, sizeof(char));
				cout << "Reader with priority " << priority << " read " << "\"X\" from file: " << filePath << endl;
			}
		}
		this_thread::sleep_for(chrono::milliseconds(10 * priority));
	}
	fileStream.close();
	return 0;
}
