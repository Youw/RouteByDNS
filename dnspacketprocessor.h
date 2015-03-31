#ifndef DNSPACKETPROCESSOR_H
#define DNSPACKETPROCESSOR_H

#include <unordered_map>

#include "dnsipprocessor.h"
#include "tcpdumpparser.h"

class DNSPacketProcessor
{
	DNSIPProcessor& dns_ip_processor;
	using IPDNSPackets = std::unordered_map<unsigned, TcpDumpParser::dns_packet>;
public:
	DNSPacketProcessor(DNSIPProcessor& processor);

	void process(const TcpDumpParser::dns_packet& packet);
private:
	bool hasFirstPacket(const TcpDumpParser::dns_packet& second_packet);
	static bool hasIpResolved(const TcpDumpParser::dns_packet& packet);
	TcpDumpParser::dns_packet getFirstForPacket(const TcpDumpParser::dns_packet& second_packet);
	void removeFirstForPacket(const TcpDumpParser::dns_packet& second_packet);
	static bool hasNameToResolve(const TcpDumpParser::dns_packet& packet);
	void addFrstPacket(const TcpDumpParser::dns_packet& first_packet);

	IPDNSPackets wait_packets;
};

#endif //DNSPACKETPROCESSOR_H
