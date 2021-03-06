#include "voipdetector_pcap.h"
#include "voipdetector_socket.h"

extern int pcapfd;
int main(){ 
	pcap_if_t *alldevs;
	struct pcap_pkthdr *header;
	const u_char *pkt_data;
	pcap_t * fd;

	char errbuf[ERRBUFSIZ];
//	if(pcap_findalldevs(&alldevs, errbuf) == -1)
//	{
//		fprintf(stderr,"Error in pcap_findalldevs_ex: %s\n", errbuf);
//		exit(1);
//	}
//	//if(pcapfd = initpcap(alldevs->name,1,"",errbuf) == -1){
//	fd = initpcap("",1,"tcp",errbuf);
//	if(pcapfd == -1){
//		fprintf(stdout,"%s\n",errbuf);
//		exit(1);
//	};
	//add_to_select_set(pcapfd);
	//sockets_run();
	fd = pcap_open_offline("F:/docs/work/gateway/yingshi.pcap",errbuf);
	int res;
	u_int inum = 0, i=0;
	while((res = pcap_next_ex( fd, &header, &pkt_data)) >= 0)
	{

		if(res == 0)
			/* Timeout elapsed */
			continue;

		/* print pkt timestamp and pkt len */
	//	printf("%ld:%ld (%ld)\n", header->ts.tv_sec, header->ts.tv_usec, header->len);			

	//	/* Print the packet */
	//	for (i=1; (i < header->caplen + 1 ) ; i++)
	//	{
	//		printf("%.2x ", pkt_data[i-1]);
	//		if ( (i % 16) == 0) printf("\n");
	//	}

		
		for (i = 1; i < header->caplen; i++){
			if(pkt_data[i] == 0x67 && pkt_data[i+1] == 0x6c && pkt_data[i+2] == 0x73){
				fprintf(stdout, "%d\n", inum);
			}
		}

		//printf("\n\n");		
		inum++;
	}
	system("pause");
}