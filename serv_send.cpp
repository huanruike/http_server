#include"headfile.h"
#include"serv_send.h"

void serv_send(int op,int sock){
	char state[LEN];
	
	char head_server[LEN];
	char head_type[LEN];
	char head_length[LEN];
	
	char buf[BUF_SIZE];
	
	if(op==404) strcpy(state,"HTTP/1.0 404 Not Found\r\n");
	if(op==400) strcpy(state,"HTTP/1.0 400 Bad Request\r\n");

	strcpy(head_server,"Server : WebServer\r\n");
	strcpy(head_type,"Content-type : text/html\r\n");
	strcpy(head_length,"Content-length : 2048\r\n\r\n");

	strcpy(buf,"<!DOCTYPE html><html><mate charset=\"UTF-8\"><head><title>error</title></head><body><p>error</p></body></html>\r\n");

	printf("state: %s",state);
	Send(sock,state,head_server,head_type,head_length,buf,strlen(buf));
	close(sock);
}

void serv_send(char *path,int sock){

	FILE *fp=fopen(path,"r");
	printf("serv_path: %s\n",path);
	if(fp==NULL){
		serv_send(404,sock);
		return;
	}

	char state[LEN];
	
	char head_server[LEN];
	char head_type[LEN];
	char head_length[LEN];
	
	char buf[BUF_SIZE];
	
	strcpy(state,"HTTP/1.0 200 OK\r\n");	

	strcpy(head_server,"Server : WebServer\r\n");
	strcpy(head_type,"Content-type : text/html\r\n");
	strcpy(head_length,"Content-length : 2048\r\n\r\n");

	int len;

	len=fread(buf,1,BUF_SIZE,fp);
	if(len==-1){
		serv_send(400,sock);
		error_handling("fread() error!");
		return;
	}
	printf("file state: %s",state);
	Send(sock,state,head_server,head_type,head_length,buf,len);
	fclose(fp);
	close(sock);
}

void Send(int sock,char *state,char *head_server,char *head_type,
		char *head_length,char *buf,int buflen){
	write(sock,state,strlen(state));
	write(sock,head_server,strlen(head_server));
	write(sock,head_type,strlen(head_type));
	write(sock,head_length,strlen(head_length));
	write(sock,buf,buflen);
}

