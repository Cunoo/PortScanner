//AUTHOR LOCALHOST


#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <netinet/tcp.h>
#include <netinet/ip.h>


char l_IP[16] = {0};

int sockt, first_port, last_port, err;

struct sockaddr_in sa;

void port_scanner();



int main(int argc, char *argv[]){


	printf("Test of port scanner by Cunoo\n");
	port_scanner();

	return 0;
}


void port_scanner(){
	/*printf("Hello Please enter the IP adress and first port and last port\n",argv[0]);

	if(agrc < 4){
		printf("Invalid configuration please try again!\n");
		exit(1);
		return 0;
	} else {
		printf("Invalid option please try again!\n");
		exit(1);
	}
	*/
	
	printf("set a IPv4 adress: ");
	scanf("%s", &l_IP);
	
	printf("\nfirst port: ");
	if(!scanf("%d", &first_port) == 1){
		printf("Invalid option!! \n");
		exit(2);
	}
	
	printf("\nlast port: ");
	if(!scanf("%d", &last_port) == 1){
		printf("Invalid option!!\n");
		exit(2);
	}

	//strcpy(l_IP,argv[1]); //Copy IPV4!! adress
	

	//strcpy(first_port, argv[2]); //Copy first port

	//strcpy(last_port, argv[3]); //Copy last port

	strncpy((char*)&sa, "", sizeof sa);

	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(l_IP);
	
	//direct ip address, use it
	if(isdigit(l_IP[0]))
	{
		printf("Doing inet_addr...");
		sa.sin_addr.s_addr = inet_addr(l_IP);
		printf("Done\n");
	}
	else
	{
		herror(l_IP);
		exit(2);
	}

	printf("PORT	STATE	SERVICE\n");
	for(int i = first_port; i<= last_port; i++){
	sa.sin_port = htons(i);
	sockt = socket(AF_INET, SOCK_STREAM, 0);
	//check for errors sockt

	if(sockt < 0){
	perror("\n Socket (sockt)");
	}
	//Connect using that socket and sockaddr struc
	err = connect(sockt, (struct sockaddr*)&sa, sizeof sa);
	//not connected
		if(err < 0){
				fflush(stdout);
		} else {
			//connected
			
			int ftp_port = 21;
			int telnet_port = 23;
			int HTTP_port = 80;
			//printf("%-8d open\n",  i);
			if(i == ftp_port){
				printf("%-8d OPEN	FTP-TCP\n", ftp_port);
				} else if(i == telnet_port){
					printf("%-8d OPEN	TELNET-TCP\n", telnet_port);
					} else if (i == HTTP_port){
						printf("%-8d OPEN	HTTP\n", HTTP_port);
						} else {
							printf("%-8d open\n",  i);
							}
		
		}
		close(sockt);

	}

}

