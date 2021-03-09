// Winsock Tutorial http://www.c-worker.ch/tuts/wstut_op.php

#pragma warning(disable : 4996)																			// deaktiviert die Fehlermeldung bei ("127.0.0.1")

#include <winsock2.h>																													// vor windows.h includieren kann Fehler verhindern
#include <windows.h>
#include <iostream>
#include <stdio.h>																														// für MAKEWORD etc....

int startWinsock(void);																													// Prototyp


int main()
{
	long rc;
	SOCKET s;
	SOCKADDR_IN addr;
	rc = startWinsock();
	if (rc != 0)
	{
		std::cout << "Fehler: startWinsock, Fehlercode: " << WSAGetLastError() << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Winsock gestartet!\n";
		std::cout << std::endl;
		s = socket(AF_INET, SOCK_STREAM, 0);
		if (s == INVALID_SOCKET)
		{
			std::cout << "Fehler: Der Socket konnte nicht erstellt werden, Fehlercode: " << WSAGetLastError() << std::endl;
			return 1;
		}
		else
		{
			std::cout << "Socket erstellt!\n";
			std::cout << std::endl;
			memset(&addr, 0, sizeof(SOCKADDR_IN)); // alles auf 0 setzen
			addr.sin_family = AF_INET;
			addr.sin_port = htons(12345); // Port = 12345
			addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Zielrechner = lokal
			rc = connect(s, (SOCKADDR*)&addr, sizeof(SOCKADDR));
			if (rc == SOCKET_ERROR)
			{
				std::cout << "Fehler: connect gescheitert, Fehlercode: " << WSAGetLastError() << std::endl;
				return 1;
			}
			else
			{
				std::cout << "Verbunden mit 127.0.0.1!" << std::endl;
			}
		}

	}
	return 0;
}



int startWinsock(void)
{
	WSADATA wsa;
	return WSAStartup(MAKEWORD(2, 0), &wsa);
}