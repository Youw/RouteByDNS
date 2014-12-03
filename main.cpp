
#include <string>
#include <iostream>

#include "tcpdumpparser.h"

int main() 
{
	TcpDumpParser parser(std::cin);
	while(1) {
		TcpDumpParser::packet packet = parser.getNextPacket();
		std::cout << "When: " << packet.time;
	}
	return 0;
}