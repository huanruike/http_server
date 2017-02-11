#ifndef SERV_SEND_H
#define SERV_SEND_H

void Send(int sock,char *state,char *head_server,char *head_type,
		char *head_length,char *buf,int buflen);
void serv_send(int op,int sock);
void serv_send(char *path,int sock);

#endif
