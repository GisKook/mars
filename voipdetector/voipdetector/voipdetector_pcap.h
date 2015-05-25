#ifndef VOIPDETECTOR_H_H
#define VOIPDETECTOR_H_H

#include "pcap.h"
#include "voipdetector_net.h"
#define ERRBUFSIZ 1024

pcap_t *initpcap(char * device,int verbose, char *filter, char * errbuf);
void peekpcap(int, pcap_handler);
int getdllen();

void packet_handler(u_char *udata, const struct pcap_pkthdr *pkthdr, const u_char *packet);
void packet_handler_lfp(vnet *, u_char *udata, const struct pcap_pkthdr *pkthdr, const u_char *packet);
void packet_handler_lra(vnet *, u_char *udata, const struct pcap_pkthdr *pkthdr, const u_char *packet);
void packet_handler_fixed(vnet *, u_char *udata, const struct pcap_pkthdr *pkthdr, const u_char *packet);
#endif