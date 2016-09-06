#ifndef UDPSOUNDS_H
#define UDPSOUNDS_H

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>	/* for fprintf */
#include <string.h>
#include <netdb.h>
#include <sstream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>




using namespace std;


class Player
{
public:
	Player(string hostname, string soundPrefix) {
		if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
            perror("cannot create socket\n");
            return;
        }


		/* fill in the server's address and data */
		memset((char*)&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(13231);

		/* look up the address of the server given its name */
		hp = gethostbyname(hostname.c_str());
		if (!hp) {
			fprintf(stderr, "could not obtain address of host\n");
			return;
		}

		/* put the host's address into the server address structure */
		memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);

		prefix = soundPrefix;
		if (prefix.back() != '/') {
			prefix += '/';
		}

		std::ifstream infile("sounds.txt");
		std::string line;
		while (std::getline(infile, line)) {
			soundz.push_back(line);
		}
	
	}
	~Player();
	

	void play(string sound) {
		ostringstream ss;
		ss << "audiomixclient/3 helioboard 0\n";
		ss << counter++;
		ss << "\n";
		ss << "/play?sample=";
		ss << url_encode(prefix + sound);
		ss << "\n";
		string my_message = ss.str();
		printf("PLAYING SOUND: %s\n", my_message.c_str());
		if (sendto(fd, my_message.c_str(), strlen(my_message.c_str()), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
			perror("sendto failed");
			return;
		}
		
	}

	string bombSound = "Explosion.wav";

	vector<string> soundz;

	string url_encode(const string &value) {
	    ostringstream escaped;
	    escaped.fill('0');
	    escaped << hex;

	    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
	        string::value_type c = (*i);

	        // Keep alphanumeric and other accepted characters intact
	        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
	            escaped << c;
	            continue;
	        }

	        // Any other characters are percent-encoded
	        escaped << uppercase;
	        escaped << '%' << setw(2) << int((unsigned char) c);
	        escaped << nouppercase;
	    }

	    return escaped.str();
	}

private:
	int fd;
	struct hostent *hp;     /* host information */
	struct sockaddr_in servaddr;    /* server address */
	int counter = 0;
	string prefix;



};

#endif