#ifndef VOIPDETECTOR_NET_H_H
#define VOIPDETECTOR_NET_H_H

#include "pcap.h"

enum algos {
	ALGORITHM_LFP = 1,
	ALGORITHM_LRA = 2,
	ALGORITHM_FIXED
};

typedef struct vnet vnet;
struct vnet {
	int addr;
	int mask;
	int algo;
	int fixport;
	short inuse;
	void (*op) (struct vnet *, unsigned char *udata, const struct pcap_pkthdr *pkthdr, const unsigned char *packet);
	struct vnet *next;
};


int loadnetfile(char *netfile);
void init_vnet();
void free_vnet();
vnet *get_vnet();

#endif