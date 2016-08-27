#ifndef UDPSOUNDS_H
#define UDPSOUNDS_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>	/* for fprintf */
#include <string.h>
#include <netdb.h>
#include <sstream>

using namespace std;

class Player
{
public:
	Player() {
		if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("cannot create socket\n");
            return;
        }


		/* fill in the server's address and data */
		memset((char*)&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(13231);

		/* look up the address of the server given its name */
		hp = gethostbyname("10.0.0.4");
		if (!hp) {
			fprintf(stderr, "could not obtain address of host\n");
			return;
		}

		/* put the host's address into the server address structure */
		memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);

	}
	~Player();
	

	void play(string sound) {
		ostringstream ss;
		ss << "helioboard\n";
		ss << counter++;
		ss << "\n";
		ss << "play\n";
		ss << sound;
		ss << "\n";
		string my_message = ss.str();
		printf("ABOUT TO SEND:\n%s", my_message.c_str());
		if (sendto(fd, my_message.c_str(), strlen(my_message.c_str()), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
			perror("sendto failed");
			return;
		}
		
	}

private:
	int fd;
	struct hostent *hp;     /* host information */
	struct sockaddr_in servaddr;    /* server address */
	int counter = 0;



};

#endif