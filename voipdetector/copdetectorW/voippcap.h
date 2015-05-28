#ifndef VOIPPCAP_H_H
#define VOIPPCAP_H_H
#include <string>
#include <vector>
#define PCAP_ERRBUF_SIZE 256

struct voippcap;
struct pcap_pkthdr; 
typedef void (*packet_handler)(unsigned char *param, const struct pcap_pkthdr *header, const unsigned char *pkt_data);

struct voippcap * voippcap_create();
void voippcap_destroy(struct voippcap * pcap);
std::vector<std::string> voippcap_getalldevs(struct voippcap * pcap,std::vector<std::string> &desc,char errbuf[PCAP_ERRBUF_SIZE]);
int voippcap_capture( struct voippcap * pcap, int index, packet_handler handler,char errbuf[PCAP_ERRBUF_SIZE]);

#endif