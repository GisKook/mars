#ifndef VOIPPCAP_H_H
#define VOIPPCAP_H_H
#include <string>
#include <vector>
#define PCAP_ERRBUF_SIZE 256

struct voippcap;

struct voippcap * voippcap_create();
void voippcap_destroy(struct voippcap * pcap);
std::vector<std::string> voippcap_getalldevs(struct voippcap * pcap,std::vector<std::string> &desc,char errbuf[PCAP_ERRBUF_SIZE]);

#endif