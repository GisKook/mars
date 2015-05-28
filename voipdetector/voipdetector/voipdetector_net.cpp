#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>

#include "voipdetector_socket.h"
#include "voipdetector_pcap.h"
#include "voipdetector_net.h"


vnet *allnets[256];

extern int pcapfd, mgmtfd;


void
init_vnet()
{
	int i = 0;

	for ( ; i < 256; i++)
		allnets[i] = NULL;
}

void
free_vnet()
{
	int i = 0;
	vnet *v = NULL;

	for (i = 0; i < 256; i++) 
		while ((v = allnets[i]) != NULL) {
			allnets[i] = v->next;
			free(v);
		}
}

void
add_vnet(int ip, int mask, int algo, char *opts)
{
	vnet *v = NULL;
	int h = ip & 0x000000ff; 

	if ((v = (vnet*)malloc(sizeof(vnet))) == NULL) {
		fprintf(stdout, "add_vnet: malloc: %s\n", strerror(errno));
		return;
	}
	switch(algo) {
		case ALGORITHM_LRA:
			fprintf(stdout, "add_vnet: lra algorithm is not implemented, defaulting to lfp\n");
		case ALGORITHM_LFP:
			v->op = packet_handler_lfp;
			break;
		case ALGORITHM_FIXED:
			v->op = packet_handler_fixed;
			break;
		default:
			v->op = packet_handler_lfp;
			break;
	}
	v->addr = ip;
	v->mask = mask;
	v->fixport = htons(atoi(opts));
	v->next = allnets[h];
	allnets[h] = v;
}

vnet *
get_vnet(int ip)
{
	int h;
	vnet *v;

	h = ip & 0x000000ff; 
	for (v = allnets[h]; v != NULL; v = v->next)
		if ((ip & v->mask) == v->addr)
			return v;
	return NULL;
}

int
loadnetfile(char *netfile)
{
	FILE *fp = NULL;
	char line[1024];
	char strip[24], strmask[24], stralgo[24], stropts[128];
	int i = 0, j = 0, k = 0, buflen = 0, nalgo = 0;

	if ((fp = fopen(netfile, "r")) == NULL) {
		fprintf(stdout, "loadnetfile: fopen(%s): %s\n", netfile, strerror(errno));
		return -1;
	}
	while(fgets(line, sizeof(line) - 1, fp) != NULL) {
		k++;
		i = 0, j = 0, buflen = 0;
		memset(strip, 0x0, sizeof(strip));
		memset(strmask, 0x0, sizeof(strmask));
		memset(stralgo, 0x0, sizeof(stralgo));
		memset(stropts, 0x0, sizeof(stropts));
		buflen = strlen(line);
		/* skip white space */
		while(i < buflen && !isgraph(line[i]))
			i++;
		if (line[i] == '#')
			continue;
		while (i < buflen && isgraph(line[i]) && j < sizeof(strip) - 1 && line[i] != '/')
			strip[j++] = line[i++];
		strip[j] = '\0';
		if (strlen(strip) == 0) {
			fprintf(stdout, "loadnetfile: parse error at line %d, cannot get ip\n", k);
			continue;
		}
		i++;
		j = 0;
		while (i < buflen && isgraph(line[i]) && j < sizeof(strmask) - 1)
			strmask[j++] = line[i++];
		strmask[j] = '\0';
		if (strlen(strmask) == 0) {
			fprintf(stdout, "loadnetfile: parse error at line %d, cannot get mask\n", k);
			continue;
		}
		/* skip white space */
		while(i < buflen && !isgraph(line[i]))
			i++;
		j = 0;
		while (i < buflen && isgraph(line[i]) && j < sizeof(stralgo) - 1)
			stralgo[j++] = line[i++];
		stralgo[j] = '\0';
		if (strlen(stralgo) == 0) {
			fprintf(stdout, "loadnetfile: parse error at line %d, cannot get algorithm\n", k);
			continue;
		}
		if (strcmp(stralgo, "fixed") == 0) {
			if (strcmp(strmask, "255.255.255.255") != 0) {
				fprintf(stdout, "loadnetfile: fixed algorithm can only by used with hosts, not networks\n");
				continue;
			}
			while(i < buflen && !isgraph(line[i]))
				i++;
			j = 0;
			while (i < buflen && isgraph(line[i]) && j < sizeof(stropts) - 1)
				stropts[j++] = line[i++];
			stropts[j] = '\0';
			if (strlen(stropts) == 0) {
				fprintf(stdout, "loadnetfile: parse error at line %d, cannot get port number for fixed algorithm\n", k);
				continue;
			}
		}
		if (strcmp(stralgo, "lfp") == 0)
			nalgo = ALGORITHM_LFP;
		else
		if (strcmp(stralgo, "lra") == 0)
			nalgo = ALGORITHM_LRA;
		else
		if (strcmp(stralgo, "fixed") == 0)
			nalgo = ALGORITHM_FIXED;
		fprintf(stdout, "loadnet(%s/%s) method: %s %s\n", strip, strmask, stralgo, stropts);
		add_vnet(inet_addr(strip), inet_addr(strmask), nalgo, stropts);
	}
	fclose(fp);
	return 0;
}
