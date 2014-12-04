#include "dnspacketprocessor.h"


DNSPacketProcessor::DNSPacketProcessor(DNSIPProcessor& processor):
	dns_ip_processor(processor)
{
}

void DNSPacketProcessor::process(const TcpDumpParser::dns_packet& packet)
{
	if (hasFirstPacket(packet)) {
		if (hasIpResolved(packet)) {
			TcpDumpParser::dns_packet first_packet = getFirstForPacket(packet);
			DNSIPProcessor::dns_ip dns_ip;
			dns_ip.name = first_packet.records[0].value;
			for (auto& record : packet.records) {
				if (record.type == "A") {
					dns_ip.addresses.push_back(record.value);
				}
			}
			if (dns_ip.addresses.size()) {
				dns_ip_processor.process(dns_ip);
			}
		}
		else {
			removeFirstForPacket(packet);
		}
	}
	else {
		if (hasNameToResolve(packet)) {
			addFrstPacket(packet);
		}
	}
}

bool DNSPacketProcessor::hasFirstPacket(const TcpDumpParser::dns_packet& second_packet)
{
	return 0!=wait_packets.count(second_packet.id);
}

bool DNSPacketProcessor::hasIpResolved(const TcpDumpParser::dns_packet& packet)
{
	return (packet.records.size() && packet.records[0].type != "nxdomain");
}

TcpDumpParser::dns_packet DNSPacketProcessor::getFirstForPacket(const TcpDumpParser::dns_packet& second_packet)
{
	TcpDumpParser::dns_packet packet = wait_packets[second_packet.id];
	wait_packets.erase(second_packet.id);
	return packet;
}

void DNSPacketProcessor::removeFirstForPacket(const TcpDumpParser::dns_packet& second_packet)
{
	wait_packets.erase(second_packet.id);
}

bool DNSPacketProcessor::hasNameToResolve(const TcpDumpParser::dns_packet& packet)
{
	return packet.records.size() && packet.records[0].type == "A?";
}

void DNSPacketProcessor::addFrstPacket(const TcpDumpParser::dns_packet& first_packet)
{
	wait_packets[first_packet.id] = first_packet;
}
