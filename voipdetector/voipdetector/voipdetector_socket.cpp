#include <WinSock2.h>
#include <errno.h>
#include <stdio.h>
#include "voipdetector_pcap.h"

extern int pcapfd;
static fd_set allset;
int
getmaxfd()
{
	return pcapfd;
}

void add_to_select_set( int sd)
{
	FD_SET(sd, &allset);
}

void remove_from_select_set( int sd)
{
	FD_CLR(sd, &allset);
}

void sockets_run( void )
{
	fd_set rset;
	struct timeval tv;
	int nready;
	
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	for ( ; ; ) {
		rset = allset;
		nready = select(getmaxfd()+1,&rset,NULL,NULL,&tv);
		if (nready < 0) {
			if (errno == EINTR)
				continue;
			continue;
		}

		if (nready > 0 && FD_ISSET(pcapfd, &rset)) {
			peekpcap(100, packet_handler);
			nready--;
		}
	}
}