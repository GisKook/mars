#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stdafx.h"
#include "conf.h"
#include "cJSON.h"

struct conf g_conf;

cJSON * load_conf_file(char * path){
	FILE *f;long len;char *data;
	f = fopen(path, "rb");
	if (f != NULL){
        fseek(f,0,SEEK_END);
        len=ftell(f);
        fseek(f,0,SEEK_SET);
        data=(char*)malloc(len+1);fread(data,1,len,f);data[len]='\0';fclose(f);
        cJSON *json;
        json=cJSON_Parse(data);
        free(data); 

        return json;
    }

    return NULL;

}

int conf_update_file(cJSON * item){
    FILE * f = fopen(CONF_PATH, "w");
    char * p = cJSON_Print(item);
    fwrite(p, 1, strlen(p), f);
    fclose(f);

	return 0;
}

int conf_update(char * key, char * value){
	cJSON * json = load_conf_file(CONF_PATH);
    if (json !=  NULL){
        cJSON * json_item= cJSON_GetObjectItem(json, key);
        if (json_item){
            json_item->valuestring = value;
        }else{
            cJSON_AddStringToObject(json, key, value);
        }

        conf_update_file(json);

//        FILE * f = fopen(CONF_PATH, "w");
//        char * p = cJSON_Print(json);
//        fwrite(cJSON_Print(json), 1, strlen(p), f);
//        fclose(f);
    }else{
        cJSON * json = cJSON_CreateObject();
        cJSON_AddStringToObject(json, key, value);

        conf_update_file(json);
    }
	return 0;
}


int conf_update_serial( char * serial )
{
	cJSON * json = load_conf_file(CONF_PATH);
	cJSON * json_serial = cJSON_GetObjectItem(json, SERIAL);
	json_serial->valuestring = serial;
	cJSON_Print(json);

	return 0;
}

int conf_update_ip( char * ip)
{

	return 0;
}

int conf_update_port( char * port )
{

	return 0;
}

int parse_conf(cJSON *subitem){
	if(!subitem){
		return 1;
	}       
	memset(&g_conf, 0, sizeof(struct conf));

	cJSON * json_serial;
	cJSON * json_ip;
	cJSON * json_port;

	json_serial = cJSON_GetObjectItem(subitem, SERIAL);
	if(json_serial && json_serial->type == cJSON_String){
		memcpy(&g_conf.serial, json_serial->valuestring, strlen(json_serial->valuestring));
	}

	json_ip = cJSON_GetObjectItem(subitem, IP);
	if(json_ip&& json_ip->type == cJSON_String){
		memcpy(&g_conf.ip, json_ip->valuestring, strlen(json_ip->valuestring));

		json_port = cJSON_GetObjectItem(subitem, PORT);
		if(json_port && json_port->type == cJSON_String){
			memcpy(&g_conf.port, json_port->valuestring, strlen(json_port->valuestring));
		}

		return 0;
	}
}

int conf_load() {
	cJSON * json = load_conf_file(CONF_PATH);
    int ret = 1;
    if (json != NULL){
        ret = parse_conf(json);
        cJSON_Delete(json); 
    }

	return ret;
}
