
#include "voipdetector_net.h"
char gdevice[256];
int gsnaplen = 1;
int greadtmt = 1;
int gpromisc = 1;
int pcapfd = -1;
void (*packet_handler_default) (vnet *, u_char *udata, const struct pcap_pkthdr *pkthdr, const u_char *packet);