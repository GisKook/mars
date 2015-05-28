#include "voippcap.h"
#include "pcap.h"

struct voippcap{
	pcap_if_t *alldevs;
	pcap_t *adhandle;
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

int voippcap_capture( struct voippcap * pcap, int index, packet_handler handler,char errbuf[PCAP_ERRBUF_SIZE]){
	pcap_if_t * dev;
	int i;
	for(dev=pcap->alldevs, i=0; i< index-1 ;dev=dev->next, i++);
	if ((pcap->adhandle= pcap_open_live(dev->name,	// name of the device
		65536,			// portion of the packet to capture. 
		// 65536 grants that the whole packet will be captured on all the MACs.
		1,				// promiscuous mode (nonzero means promiscuous)
		1000,			// read timeout
		errbuf			// error buffer
		)) == NULL)
	{
		fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n");
		/* Free the device list */
		voippcap_destroy(pcap);
		return -1;
	}
	/* Check the link layer. We support only Ethernet for simplicity. */
	if(pcap_datalink(pcap->adhandle) != DLT_EN10MB)
	{
		fprintf(stderr,"\nThis program works only on Ethernet networks.\n");
		/* Free the device list */
		voippcap_destroy(pcap);
		return -1;
	}

	u_int netmask;
	if(dev->addresses != NULL)
		/* Retrieve the mask of the first address of the interface */
		netmask=((struct sockaddr_in *)(dev->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* If the interface is without addresses we suppose to be in a C class network */
		netmask=0xffffff; 

	char packet_filter[] = "ip and udp"; 
	struct bpf_program fcode;
	//compile the filter
	if (pcap_compile(pcap->adhandle, &fcode, packet_filter, 1, netmask) <0 )
	{
		fprintf(stderr,"\nUnable to compile the packet filter. Check the syntax.\n");
		/* Free the device list */
		voippcap_destroy(pcap);
		return -1;
	}

	//set the filter
	if (pcap_setfilter(pcap->adhandle, &fcode)<0)
	{
		fprintf(stderr,"\nError setting the filter.\n");
		/* Free the device list */
		voippcap_destroy(pcap);
		return -1;
	}

	printf("\nlistening on %s...\n", dev->description);

	/* At this point, we don't need any more the device list. Free it */
	pcap_freealldevs(pcap->alldevs);

	/* start the capture */
	pcap_loop(pcap->adhandle, 0, handler, NULL);
}