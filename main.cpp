
#include <fstream>
#include <string>
#include <string>

#include "dnsipprocessor.h"
#include "dnspacketprocessor.h"
#include "tcpdumpparser.h"

int main() 
{
	TcpDumpParser parser(std::cin);
#ifndef WIN32
	std::vector<std::string> allowed_names;
	std::ifstream file_names("/etc/route_by_dns/allowed_names.txt");
	std::string buffer;
	while (file_names >> buffer) {
		allowed_names.push_back(buffer);
	}
	DNSIPProcessor dns_ip_processor(allowed_names);
#else
	//test&debug
	DNSIPProcessor dns_ip_processor({".google.","vk.com"});
#endif
	DNSPacketProcessor dns_packet_processor(dns_ip_processor);
	while(1) {
		TcpDumpParser::dns_packet packet = parser.getNextPacket();
		dns_packet_processor.process(packet);
	}
	return 0;
}