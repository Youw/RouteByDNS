
#include <fstream>
#include <signal.h>
#include <string>

#include "dnsipprocessor.h"
#include "dnspacketprocessor.h"
#include "tcpdumpparser.h"

TcpDumpParser* parser = nullptr;
DNSIPProcessor* dns_ip_processor = nullptr;
DNSPacketProcessor* dns_packet_processor = nullptr;

void my_handler(int){
	delete dns_packet_processor;
	dns_packet_processor = 0;
	delete dns_ip_processor;
	dns_ip_processor=0;
	delete parser;
	parser = 0;
	exit(0);
}

int main()
{
	signal (SIGINT,my_handler);
	signal (SIGTERM,my_handler);
	signal (SIGKILL,my_handler);

	parser = new TcpDumpParser(std::cin);
	std::vector<std::string> allowed_names;
	std::ifstream file_names("/etc/route_by_dns/allowed_names.txt");
	std::string buffer;
	while (file_names >> buffer) {
		allowed_names.push_back(buffer);
	}
	dns_ip_processor = new DNSIPProcessor(allowed_names);
	dns_packet_processor = new DNSPacketProcessor(*dns_ip_processor);
	while(1) {
		TcpDumpParser::dns_packet packet = parser->getNextPacket();
		dns_packet_processor->process(packet);
	}
	my_handler(0);
	return 0;
}
