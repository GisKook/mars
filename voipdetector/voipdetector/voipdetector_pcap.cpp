
#include "pcap.h"
#include "voipdetector_pcap.h"
#include <WinSock2.h>

#define	MINPACKETSIZ	(getdllen() + sizeof(struct ip) + sizeof(struct udphdr) + 20)
static pcap_t *pd = NULL;
static int dllen = 14;

extern int gsnaplen;
extern int greadtmt;
extern int gpromisc;

pcap_t *initpcap( char * device,int verbose, char * filter, char * errbuf )
{
	bpf_u_int32 netp;
	bpf_u_int32 maskp;
	char netstr[64], maskstr[64];
	struct bpf_program fprog;
	struct in_addr in;
	char dev[256]={0};
	char perrbuf[PCAP_ERRBUF_SIZE];

	if (strlen(device) == 0) {
		pcap_if_t *alldevs;

		if(pcap_findalldevs(&alldevs, errbuf) == -1)
		{
			fprintf(stderr,"Error in pcap_findalldevs_ex: %s\n", errbuf);
			_snprintf(errbuf, ERRBUFSIZ - 2, "cannot find any available device to sniff on: %s\n", perrbuf);
			return NULL;
		}
		strncpy(dev, alldevs->name, sizeof(dev) - 2);
	}
	if ((pd = pcap_open_live(dev, 65536, 1, 1000, perrbuf)) == NULL) {
		_snprintf(errbuf, ERRBUFSIZ - 2, "pcap_open_live: %s\n", perrbuf);
		return NULL;
	}

	pcap_lookupnet(dev, &netp, &maskp, perrbuf);
	in.s_addr = netp;
	strncpy(netstr, inet_ntoa(in), sizeof(netstr) - 2);
	in.s_addr = maskp;
	strncpy(maskstr, inet_ntoa(in), sizeof(maskstr) - 2);

	switch(pcap_datalink(pd)) {
		case DLT_EN10MB:
			dllen = 14;
			break;
		case DLT_IEEE802:
			dllen = 22;
			break;
		case DLT_FDDI:
			dllen = 21;
			break;
		case DLT_PPP:
			dllen = 12;
			break;
		case DLT_NULL:
			dllen = 4;
			break;
	}
	if (verbose)
		fprintf(stdout, "%s has been opened in  %s mode. (%s/%s)\n", dev, (gpromisc ? "promisc" : "non-promisc"), netstr, maskstr);
	int result = 0;
	if (strlen(filter) > 0) {
		result = pcap_compile(pd, &fprog, filter, 0, netp);
		if(result == -1){
			fprintf(stdout,"pcap_compile error %s\n",pcap_geterr(pd));
		}
		pcap_setfilter(pd, &fprog);
		pcap_freecode(&fprog);
		if (pcap_setnonblock(pd, 1, perrbuf) == -1) {
			fprintf(stdout, "pcap_setnonblock: %s\n", perrbuf);
			exit(1);
		}
	}

	//return pcap_fileno(pd);
	return pd;
}

void peekpcap( int cnt, pcap_handler phandler)
{
	while (pcap_dispatch(pd, cnt, phandler, (u_char *)dllen) != 0)
		;
}

void packet_handler( u_char *udata, const struct pcap_pkthdr *pkthdr, const u_char *packet )
{
	//	int offset = (int)udata;
	//	struct ip *ip;
	//	struct udphdr *udp;
	//	vnet *v;
	//
	//	if (pkthdr->len < MINPACKETSIZ)
	//		return;
	//
	//	ip = (struct ip *)(packet + offset);
	//	if (ip->ip_p == IPPROTO_UDP) {
	//		udp = (struct udphdr *)(packet + offset + sizeof(struct ip));
	//		if (ntohs(udp->uh_sport) < 5000 || ntohs(udp->uh_dport) < 5000)
	//			return;
	//	}
	//	if ((v = get_vnet(ip->ip_src.s_addr)) == NULL)
	//		if ((v = get_vnet(ip->ip_dst.s_addr)) == NULL) {
	//			(packet_handler_default) (NULL, udata, pkthdr, (const u_char *)ip);
	//			return;
	//		}
	//	(v->op) (v, udata, pkthdr, (const u_char *)ip);
}

int getdllen()
{
	return dllen;
}

void packet_handler_lfp( vnet *, u_char *udata, const struct pcap_pkthdr *pkthdr, const u_char *packet )
{

}

void packet_handler_lra( vnet *, u_char *udata, const struct pcap_pkthdr *pkthdr, const u_char *packet )
{

}

void packet_handler_fixed( vnet *, u_char *udata, const struct pcap_pkthdr *pkthdr, const u_char *packet )
{

}