#ifndef SOUNDS_H
#define SOUNDS_H

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include <thread> 


using namespace std;
using namespace curlpp::options;

class Player
{
public:
	Player();
	~Player();
	
	static void request(string sound) {
		try
			{
				// That's all that is needed to do cleanup of used resources (RAII style).
				curlpp::Cleanup myCleanup;

				// Our request to be sent.
				curlpp::Easy myRequest;

				// Set the URL.
				myRequest.setOpt<Url>("http://localhost:13231" + sound);

				// Send request and get a result.
				// By default the result goes to standard output.
				ostringstream os;
				os << myRequest;
			}

			catch(curlpp::RuntimeError & e)
			{
				// std::cout << e.what() << std::endl;
			}

			catch(curlpp::LogicError & e)
			{
				// std::cout << e.what() << std::endl;
			}

	}

	static void play(string sound) {
		thread requestThread(Player::request, sound);
		requestThread.detach();
		
	}

	
	static void callAudioAPI(int x, int y) {
		try
			{
				// That's all that is needed to do cleanup of used resources (RAII style).
				curlpp::Cleanup myCleanup;

				// Our request to be sent.
				curlpp::Easy myRequest;

				// Set the URL.
				myRequest.setOpt<Url>("http://Trijeet.local:6449/helioboard/init");

				// Send request and get a result.
				// By default the result goes to standard output.
				ostringstream os;
				os << myRequest;
			}

			catch(curlpp::RuntimeError & e)
			{
				std::cout << e.what() << std::endl;
			}

			catch(curlpp::LogicError & e)
			{
				std::cout << e.what() << std::endl;
			}

	}

	static void drone(int x, int y) {
		thread requestThread(Player::callAudioAPI, x, y);
		requestThread.detach();

	}
};

#endif
