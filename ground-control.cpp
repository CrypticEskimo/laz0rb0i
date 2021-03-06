#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <cmath>
#include <fstream>
#include <time.h>
using namespace std;

// Functinality includes
#include "utils.cpp"
#include "lazorboi.cpp"

const int DIR_CW = 0;
const int DIR_CCW = 1;
const int FREQ = 6000;
const string delim = " ";

int main() {

	// Initialize output states
	system("fast-gpio set-output 0");
	system("fast-gpio set-output 1");
	system("fast-gpio set-output 2");
	system("fast-gpio set-output 3");
	system("fast-gpio set-output 11");
	system("fast-gpio set-output 18");
	system("fast-gpio set-output 19");
	system("fast-gpio set 0 0");
	system("fast-gpio set 1 1");
	system("fast-gpio set 2 0");
	system("fast-gpio set 3 0");
	system("fast-gpio set 11 1");
	system("fast-gpio set 19 1");
	system("fast-gpio set 18 0");

	const char* filename = "laz0rb0i.log";
	ofstream outfile;
	outfile.open(filename);
	if(!outfile.is_open()) {
		return -1;
	}

	string input;
	int delimIndex = 0;
	int start = 0;
	int end;
	int dirA = DIR_CW;
	int dirB = DIR_CW;

	cout << "Welcome to" << endl;
	cout << ".__                                   ___.    _______   .__ " << endl;
	cout << "|  |  _____   ________  ____  _______ \\_ |__  \\   _  \\  |__|" << endl;
	cout << "|  |  \\__  \\  \\___   / /  _ \\ \\_  __ \\ | __ \\ /  /_\\  \\ |  |" << endl;
	cout << "|  |__ / __ \\_ /    / (  <_> ) |  | \\/ | \\_\\ \\\\  \\_/   \\|  |" << endl;
	cout << "|____/(____  //_____ \\ \\____/  |__|    |___  / \\_____  /|__|" << endl;
	cout << "           \\/       \\/                     \\/        \\/     " << endl;
	cout << "Type 'help' for usage information." << endl;

	// Command-line tool
	while (true) {
		cout << endl;
		cout << "> ";
		getline(cin, input);

		delimIndex = input.find(delim);
		string command = input.substr(0, delimIndex);
		string arg;
		string arg2;
		if (command.length() == input.length()) {
			arg = "\0";
			arg2 = "\0";
		} else {
			string args = input.erase(0, delimIndex + delim.length());
			string *iargs = getArgs(args, delim);
			arg = iargs[0];
			arg2 = iargs[1];
		}


		// HELP
		if (command == "help") {
			cout << "[+] run <motor_number> // Starts motor number indicated" << endl;
			cout << "[+] reverse <motor_number> // Reverses motor number indicated" << endl;
			cout << "[+] speed <motor_number> <speed> // Runs motor at a speed between 0 and 100" << endl;
			cout << "[+] string // Initiates a request to input a string to be visualized";
			cout << "[+] stop <motor_number> // Stops motor number indicated" << endl;
			cout << "[+] quit // Quits program and stops motors if running" << endl;
			time_t rawtime;
			struct tm * timeinfo;
			time (&rawtime);
			timeinfo = localtime (&rawtime);
			outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Called 'help' command" << '\n';
		}

		// RUN
		else if (command == "run") {
			time_t rawtime;
			struct tm * timeinfo;
			time (&rawtime);
			timeinfo = localtime (&rawtime);
			if (arg == "1") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Ran motor 1" << '\n';
				system("fast-gpio set 2 1");
			} else if (arg == "2") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Ran motor 2" << '\n';
				system("fast-gpio set 3 1");
			} else if (arg == "all") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Ran all motors" << '\n';
				system("fast-gpio set 2 1");
				system("fast-gpio set 3 1");
			} else {
				cout << "Usage: run <motor_number>" << endl;
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Incorrect usage of command 'run'" << '\n';
			}
		}

		// REVERSE
		else if (command == "reverse") {
			time_t rawtime;
			struct tm * timeinfo;
			time (&rawtime);
			timeinfo = localtime (&rawtime);
			if (arg == "1") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Reversed motor 1" << '\n';
				if (dirB == 0) {
					system("fast-gpio set 0 1");
					system("fast-gpio set 1 0");
					dirB = 1;
				} else {
					system("fast-gpio set 0 0");
					system("fast-gpio set 1 1");
					dirB = 0;
				}
			} else if (arg == "2") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Reversed motor 2" << '\n';
				if (dirA == 0) {
					system("fast-gpio set 19 0");
					system("fast-gpio set 18 1");
					dirA = 1;
				} else {
					system("fast-gpio set 19 1");
					system("fast-gpio set 18 0");
					dirA = 0;
				}
			} else if (arg == "all") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Reversed all motors" << '\n';
				if (dirB == 0) {
					system("fast-gpio set 0 1");
					system("fast-gpio set 1 0");
					dirB = 1;
				} else {
					system("fast-gpio set 0 0");
					system("fast-gpio set 1 1");
					dirB = 0;
				}
				if (dirA == 0) {
					system("fast-gpio set 19 0");
					system("fast-gpio set 18 1");
					dirA = 1;
				} else {
					system("fast-gpio set 19 1");
					system("fast-gpio set 18 0");
					dirA = 0;
				}
			} else {
				cout << "Usage: reverse <motor_number>" << endl;
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Incorrect usage of command 'reverse'" << '\n';
			}
		}

		// SPEED
		else if (command == "speed") {
			time_t rawtime;
			struct tm * timeinfo;
			time (&rawtime);
			timeinfo = localtime (&rawtime);

			string strArg;
			stringstream convert;
			convert << arg2;
			strArg = convert.str();

			if (arg == "1") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Set speed of motor 1 to " << arg2 << '\n';
				string pwm_command = "fast-gpio pwm 2 6000 " + strArg;
				const char *c_command = pwm_command.c_str();
				system(c_command);
			} else if (arg == "2") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Set speed of motor 2 to " << arg2 << '\n';
				string pwm_command = "fast-gpio pwm 3 6000 " + arg2;
				const char *c_command = pwm_command.c_str();
				system(c_command);
			} else if (arg == "all") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Set all motor speeds to " << arg2 << '\n';
				string pwm_command1 = "fast-gpio pwm 2 6000 " + arg2;
				string pwm_command2 = "fast-gpio pwm 3 6000 " + arg2;
				const char *c_command1 = pwm_command1.c_str();
				const char *c_command2 = pwm_command2.c_str();
				system(c_command1);
				system(c_command2);
			} else {
				cout << "Usage: speed <motor_number> <speed>" << endl;
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Incorrect usage of command 'speed'" << '\n';
			}
		}

		// STOP
		else if (command == "stop") {
			time_t rawtime;
			struct tm * timeinfo;
			time (&rawtime);
			timeinfo = localtime (&rawtime);
			if (arg == "1") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Stopped motor 1" << '\n';
				system("fast-gpio set 2 0");
			} else if (arg == "2") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Stopped motor 2" << '\n';
				system("fast-gpio set 3 0");
			} else if (arg == "all") {
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Stopped all motors" << '\n';
				system("fast-gpio set 2 0");
				system("fast-gpio set 3 0");
			} else {
				cout << "Usage: stop <motor_number>" << endl;
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Incorrect usage of command 'stop'" << '\n';
			}
		}

		// STRING
		else if (command == "string") {
			cout << "Please input a string: ";
			string userIn;
			getline(cin, userIn);
			char* charArray = stoch(userIn);
			while (!isValid(charArray)) {
				time_t rawtime;
				struct tm * timeinfo;
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				cout << "String entered is invalid. Make sure it only includes alphabetical characters and spaces." << endl;
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Incorrect usage of command 'string'" << '\n';
				getline(cin, userIn);
				charArray = stoch(userIn);
				continue;
			}
			time_t rawtime;
			struct tm * timeinfo;
			time (&rawtime);
			timeinfo = localtime (&rawtime);
			outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Started 'string' command motor cycle" << '\n';
			int index = 0;
			int speedA;
			int speedB;
			string strArgA;
			stringstream convertA;
			string strArgB;
			stringstream convertB;
			while (charArray[index + 1] != '\0') {
				time_t rawtime;
				struct tm * timeinfo;
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				dirA = getDir(charArray[index]);
				speedA = getSpeed(charArray[index]);
				dirB = getDir(charArray[index + 1]);
				speedB = getSpeed(charArray[index + 1]);
				convertA << speedA;
				strArgA = convertA.str();
				convertB << speedB;
				strArgB = convertB.str();
				if (dirA == 0) {
					outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'string' automatically reversed motor 2" << '\n';
					system("fast-gpio set 0 1");
					system("fast-gpio set 1 0");
					dirA = 1;
				} else {
					outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'string' automatically reversed motor 2" << '\n';
					system("fast-gpio set 0 0");
					system("fast-gpio set 1 1");
					dirA = 0;
				}
				if (dirB == 0) {
					outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'string' automatically reversed motor 1" << '\n';
					system("fast-gpio set 19 0");
					system("fast-gpio set 18 1");
					dirB = 1;
				} else {
					outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'string' automatically reversed motor 1" << '\n';
					system("fast-gpio set 19 1");
					system("fast-gpio set 18 0");
					dirB = 0;
				}
				string pwm_commandA = "fast-gpio pwm 3 6000 " + strArgA;
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'string' automatically set speed of motor 2 to " << speedA << '\n';
				const char *c_commandA = pwm_commandA.c_str();
				system(c_commandA);
				string pwm_commandB = "fast-gpio pwm 2 6000 " + strArgB;
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'string' automatically set speed of motor 1 to " << speedB << '\n';
				const char *c_commandB = pwm_commandB.c_str();
				system(c_commandB);
				usleep(2000000);
				index++;
			}
		}

		// SINUSOID
		else if (command == "sinusoid") {
			outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Started 'sinusoid' command motor cycle" << '\n';
			string amp1str;
			string amp2str;
			int amp1;
			int amp2;

			int index = 0;
			int speedA;
			int speedB;
			string strArgA;
			stringstream convertA;
			string strArgB;
			stringstream convertB;

			do {
				cout << "Please input an integer amplitude: ";
				cin >> amp1str;
				amp1 = stoint(amp1str);

				if (amp1 == -1) {
					time_t rawtime;
					struct tm * timeinfo;
					time (&rawtime);
					timeinfo = localtime (&rawtime);
					cout << "Invalid amplitude. Make sure its an integer and only includes digits." << endl;
					outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Incorrect usage of command 'sinusoid'" << '\n';
				}
			} while (amp1 == -1);

			do {
				cout << "Please input another integer amplitude: ";
				cin >> amp2str;
				amp2 = stoint(amp2str);
				time_t rawtime;
				struct tm * timeinfo;
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				if (amp2 == -1) {
					cout << "Invalid amplitude. Make sure its an integer and only includes digits.";
					outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Incorrect usage of command 'sinusoid'" << '\n';
				}
			} while (amp2 == -1);

			for (int i = 0; i < 100; i++) {
				time_t rawtime;
				struct tm * timeinfo;
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				speedA = amp1 * sin(0.1 * i);
				speedB = -amp2 * cos(0.2 * i);
				if (speedA < 0) {
					speedA = abs(speedA);
					dirA = 0;
				}
				else
					dirA = 1;
				if (speedB < 0) {
					speedB = abs(speedB);
					dirB = 1;
				}
				else
					dirB = 0;

				speedA = map(speedA, 0, amp1, 10, 100);
				speedB = map(speedB, 0, amp2, 10, 100);

				convertA << speedA;
				strArgA = convertA.str();
				convertB << speedB;
				strArgB = convertB.str();

				if (dirA == 0) {
					system("fast-gpio set 0 1");
					system("fast-gpio set 1 0");
					outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'sinusoid' automatically reversed motor 2" << '\n';
					dirA = 1;
				} else {
					system("fast-gpio set 0 0");
					system("fast-gpio set 1 1");
					outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'sinusoid' automatically reversed motor 2" << '\n';
					dirA = 0;
				}
				if (dirB == 0) {
					system("fast-gpio set 19 0");
					system("fast-gpio set 18 1");
					outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'sinusoid' automatically reversed motor 1" << '\n';
					dirB = 1;
				} else {
					system("fast-gpio set 19 1");
					system("fast-gpio set 18 0");
					outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'sinusoid' automatically reversed motor 1" << '\n';
					dirB = 0;
				}

				string pwm_commandA = "fast-gpio pwm 3 14000 " + strArgA;
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'sinusoid' automatically set speed of motor 2 to " << speedA << '\n';
				const char *c_commandA = pwm_commandA.c_str();
				system(c_commandA);
				string pwm_commandB = "fast-gpio pwm 2 14000 " + strArgB;
				outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "'sinusoid' automatically set speed of motor 2 to " << speedB << '\n';
				const char *c_commandB = pwm_commandB.c_str();
				system(c_commandB);
				usleep(1000000);

				system("fast-gpio pwm 2 14000 0");
				system("fast-gpio pwm 3 14000 0");
				usleep(500000);
			}
		}

		// QUIT
		else if (command == "quit") {
			time_t rawtime;
			struct tm * timeinfo;
			time (&rawtime);
			timeinfo = localtime (&rawtime);
			outfile << "[" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "] " << "Quit program" << '\n';
			system("fast-gpio set 2 0");
			system("fast-gpio set 3 0");
			break;
		}
	}
	outfile.close()
}
