#include "voippcap.h"
#include "pcap.h"

struct voippcap{
	pcap_if_t *alldevs;
};

std::vector<std::string> voippcap_getalldevs(struct voippcap * voippcap,std::vector<std::string> &desc,char errbuf[PCAP_ERRBUF_SIZE]){
	pcap_if_t *d;
	std::vector<std::string> devs;
	if(pcap_findalldevs(&voippcap->alldevs, errbuf) == -1)
	{
		fprintf(stderr,"Error in pcap_findalldevs: %s\n", errbuf);
		return devs;
	}
	for(d=voippcap->alldevs; d; d=d->next)
	{
		devs.push_back(d->name);
		if(d->description){
			desc.push_back(d->description);
		}else{
			desc.push_back("(No description available)");
		}
	}

	return devs;
}

struct voippcap * voippcap_create()
{ 
	struct voippcap * voippcap = (struct voippcap *)malloc(sizeof(struct voippcap));

	return voippcap;
}

void voippcap_destroy( struct voippcap * pcap )
{
	pcap_freealldevs(pcap->alldevs);
	free(pcap);
}
