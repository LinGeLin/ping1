#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<netdb.h>
#include<errno.h>
#include<signal.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/time.h>
#include<sys/socket.h>
#include<sys/types.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct IpHeader{
	u8 ver:4;
	u8 len:4;
	u8 tos;
	u16 tot_len;
	u16 id;
	u16 frag_and_off;
	u8  ttl;
	u8  protocol;
	u16 check_sum;
	u32 src;
	u32 dest;
}IpHeader;

typedef struct IcmpHeader{
	u8 type;
	u8 code;
	u16 check_sum;
	union{
		struct{
			u16 id;
			u16 seq;
		}echo;
		u32 gateway;
		struct{
			u16 unsed;
			u16 mtu;
		}frag;
	}un;
	u8 data[0];
	#define icmp_id un.echo.id;
	#define icmp_seq un.echo.seq;
};

int main(int argc,char *argv[]){
	struct hostent* host;
	struct sockaddr_in dest;
	struct sockaddr_in src;
	int sockfd;
	pid_t pid;
	
	int length;
	int count;
	
	if(argc<2){
		printf("Usage: ping hostname [-l length] [-n count]\n");
		exit(0);
	}
	
	if((host=gethostbyname(argv[1]))==NULL){
		printf("ping: %s :can't find the hostname\n",argv[1]);
		exit(0);
	}
	
	if(argc==4){
		if(*argv[2]=="-l"){
			length=(int)(*argv[3]);
		}
		else if(*argv[2]=="-n"){
			count=(int)(*argv[3]);
		}
	}
	else if(argc==6){
		if(*argv[2]=="-l"){
			length=(int)(*argv[3]);
			count=(int)(*argv[5]);
		}
		else if(*argv[2]=="-n"){
			count=(int)(*argv[3]);
			length=(int)(*argv[5]);
		}
	} 
	return 0;	
}
