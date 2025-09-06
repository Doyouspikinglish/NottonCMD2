#ifdef _WIN32
#include <iostream>
#include <io.h>
#include <process.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include "CTS.h"
#pragma comment(lib, "ws2_32.lib")


int CTSlogic() {
	WSADATA wsadata;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		std::cerr << "WSAstartup failed";
		return 1;
	}
	return 0;
}

#else
 #include <iostream>
 #include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int CTSlogic() {
	std::cout << "POSIX sockets are ready\n";
	return 0;
}
	
#endif