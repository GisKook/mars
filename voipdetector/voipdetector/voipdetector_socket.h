#ifndef VOIPDETECTOR_SOCKET_H_H
#define VOIPDETECTOR_SOCKET_H_H

void add_to_select_set(int);
void remove_from_select_set(int);
void sockets_run(void);

#endif