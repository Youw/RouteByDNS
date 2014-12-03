
#include <string>
#include <iostream>

#include "tcpdumpparser.h"

int main() 
{
	TcpDumpParser parser(std::cin);
	while(1) {
		TcpDumpParser::dns_packet packet = parser.getNextPacket();
		std::cout << std::endl
			<< " When: " << packet.time 
			<< " from: " << packet.from 
			<< " to: " << packet.to
			<< " id: " << packet.id
			<< " type: " << packet.type
			<< " records:" << std::endl;
		for (auto& rec : packet.records) {
			std::cout << '\t' << rec.type << ' ' << rec.value << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}