
#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>


#include <cmath>

#ifdef _WIN32
#include <Windows.h>
#endif



#include "StandartLibraryHeaders.h"

#include "TextPurpose.h"
#include "CTS.h"
#include "SimpleBot.h"
#include "TXTforWindows.h"
#include "DHB.h"


using namespace Cname;





//some command magic
std::unordered_map<std::string, std::function<void(const std::string&) >> commandM;

std::pair<std::string, std::string> parseinp(const std::string& inpt) {
	std::istringstream iss(inpt); //random magic 
	std::string cmd, arg;
	iss >> cmd;
	std::getline(iss, arg);
	if (!arg.empty() && arg[0] == ' ') arg.erase(0, 1);
	return { cmd, arg };
}

void register_commands() {

	commandM["hello"] = [](const std::string& name) {
		if (!name.empty()) {
			std::cout << "hello, " << name << "\n";
		}
		else {
			std::cout << "hello !\n";
		}
	};

	commandM["echo"] = [](const std::string& UserInputPrint) {std::cout << UserInputPrint << "\n"; };
	
	commandM["cls"] = [](const std::string& arg) {
		if (arg == "-red") { std::cout << RED; }
		else if (arg == "-green") { std::cout << GREEN; }
		else if (arg == "-blue") { std::cout << BLUE; }
		else if (arg == "-yellow") { std::cout << YELLOW; }
		else if (arg == "-reset") { std::cout << RESET; }
		else if (arg == "-cyan") { std::cout << CYAN; }
		else if (arg == "-fill") {
			#ifdef _WIN32

			system("cls");

			#else

			std::cout << "\033[2J\033[H";

			#endif
		}

		#ifdef _WIN32
		if (arg == "-red") { color::setcolorW(CnameColor::Red, CnameColor::Black); }
		else if (arg == "-blue") { color::setcolorW(CnameColor::Blue, CnameColor::Black); }
		else if (arg == "-green") { color::setcolorW(CnameColor::Green, CnameColor::Black); }
		else if (arg == "-yellow") { color::setcolorW(CnameColor::Yellow, CnameColor::Black); }
		else if (arg == "-aqua") { color::setcolorW(CnameColor::Aqua, CnameColor::Black); }
		else if (arg == "-purple") { color::setcolorW(CnameColor::Purple, CnameColor::Black); }/*color for windows*/
		else if (arg == "-gray") { color::setcolorW(CnameColor::Gray, CnameColor::Gray);}
		else if (arg == "-white") { color::setcolorW(CnameColor::White, CnameColor::Black); }
		else if (arg == "-reset") { color::resetW(); }
		else if (arg == "-clear") { cls(); }
		#endif

		
	}; /*color part + rst screen*/

	commandM["calc"] = [](const std::string& exprs) {
		std::istringstream iss(exprs);
		double rhs, lhs;
		char op;

		iss >> lhs >> op >> rhs;

		switch (op) {
			case '+': std::cout << rhs + lhs << "\n"; break;
			case '-': std::cout << rhs - lhs << "\n"; break;
			case '*': std::cout << rhs * lhs << "\n"; break;
			case '/':
				if (rhs == 0) { std::cout << "Divison by zero\n"; }
				else { std::cout << lhs / rhs << "\n"; } break;
			default:
				std::cout << "unknown operator\n";
		}
	};

	commandM["send"] = [](const std::string& msgcter) {
		if (CTSlogic() != 0) {
			std::cerr << "failed to initialize networking\n";
			return;
		}
		#ifdef _WIN32
		SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (clientSocket == INVALID_SOCKET) {
			std::cerr << "socket creation failed\n";
			WSACleanup();
			return;
		}
		#else
		int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (clientSocket < 0) {
			std::cerr << "socket creation failed\n";
			return;
		}
		#endif

		sockaddr_in serverAddr{};
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(8080);
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
			std::cerr << "connection failed\n";
			#ifdef _WIN32
			closesocket(clientSocket);
			WSACleanup();
			#else 
			close(clientSocket);
			#endif
			return;
		}

		send(clientSocket, msgcter.c_str(), msgcter.size(), 0);
		std::cout << " success|message sent:" << msgcter << "\n";
		#ifdef _WIN32
		closesocket(clientSocket);
		WSACleanup();
		#else
		close(clientSocket);
		#endif
	};


	commandM["bot"] = [](const std::string& vmo) {
		BOTmain(); //best code on earth
	};

	commandM["mk_pixel"] = [](const std::string& rsm) {
		for (int vvo = 0; vvo < 10; vvo++) {
			std::cout << "*\n";
			std::cout << "*";
		}
	};

	commandM["easter_egg"] = [](const std::string& vmm) {
		#ifdef _WIN32
		Beep(250, 2000);
	#else
		std::cout << "\a";
		#endif
	};

	commandM["note"] = [](const std::string& Nt) {

		const std::string Nfile = "notes.txt";

		if (Nt.empty()) {

			std::ifstream read(Nfile);
			if (!read.is_open()) { 
				std::cerr << "File cannot be opened";
				return;
			}
			std::string ln;
			std::cout << "Notes:\n";

			while (std::getline(read, ln)) {
				std::cout << "- " << ln << "\n";
			}


			return;

			
		}

		std::ofstream write(Nfile, std::ios::app);
		write << Nt << "\n";
		std::cout << "notes saved\n";

	};

	commandM["convert"] = [](const std::string& StarterValue1) {
		Convert(StarterValue1);
	};

	

	/*the exit function should be the end, do not displace it
	  the ifdefs are for specific Oses to make it a better cross-platform
	  This code will probably not be open-source, you need to buy.
	*/
	
	commandM["exit"] = [](const std::string& nmo){
		std::cout << "bye\n";
		exit(0);
	};


}

int main() {
	std::cout << "nice to cya\n";
	register_commands();
	
	std::string inpt;

	

	while (1) {
		std::cout << "]";
		std::getline(std::cin, inpt);

		if (inpt.empty()) { continue; }

		auto [ cmd, arg ] = parseinp(inpt);

		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

		if (commandM.count(cmd)) {
			commandM[cmd](arg);
		}
		else {
			std::cout << "No commands found\n";
		}
	}
} 

//end of source.cpp
