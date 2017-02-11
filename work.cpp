#include"headfile.h"
#include"request.h"
#include"work.h"

void work(int serv_sock){
	int clnt_sock;
	sockaddr_in clnt_addr;
	while(1){
		socklen_t clnt_sz=sizeof(clnt_addr);
		clnt_sock=accept(serv_sock,(sockaddr*)&clnt_addr,&clnt_sz);
		if(clnt_sock==-1) continue;
//		printf("clnt_sock=%d\n",clnt_sock);
		pthread_t request_th;
		pthread_create(&request_th,NULL,request,(void*)&clnt_sock);
//		pthread_datach(request_th);
	}
	close(serv_sock);
}
		
