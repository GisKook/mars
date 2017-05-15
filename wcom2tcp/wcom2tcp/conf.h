#ifndef __WCOM2TCP_CONF_H_H_
#define __WCOM2TCP_CONF_H_H_

#define CONF_PATH "./conf.json"
#define SERIAL "serial"
#define IP "ip"
#define PORT "port"

#define CONF_LEN 256
struct conf{
	char serial[CONF_LEN];
	char ip[CONF_LEN];
	char port[CONF_LEN];
};

int conf_load();

int conf_update_serial(char * serial);
int conf_update_ip(char * serial);
int conf_update_port(unsigned short port);
int conf_update(char * key, char * value);

#endif