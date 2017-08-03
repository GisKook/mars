#ifndef __WCOM2TCP_CONF_H_H_
#define __WCOM2TCP_CONF_H_H_

#define CONF_PATH "./conf.json"
#define SERIAL "serial"
#define IP "ip"
#define PORT "port"
#define QUERY_IP "query_ip"
#define QUERY_PORT "query_port"

#define CONF_LEN 256
struct conf{
	char serial[CONF_LEN];
	char ip[CONF_LEN];
	char port[CONF_LEN];
	char query_ip[CONF_LEN];
	char query_port[CONF_LEN];
};

int conf_load();
int conf_update(char * key, char * value);

#endif