
#include <zmq.hpp>
#include <iostream>
#include "position.pb.h"


void startSubscriber(std::string port_number)
{
	zmq::context_t context(1);
	std::string transport("tcp://172.16.254.1:"+port_number);
	zmq::socket_t subscriber(context, ZMQ_SUB);
	subscriber.connect(transport);
	subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0); // Recieve all messages
	std::vector<zmq::pollitem_t> p = {{subscriber, 0, ZMQ_POLLIN, 0}};
	GeneratedPosition *posMessage = new GeneratedPosition();	
	Data3d *xyzCoordinates = new Data3d();
	while (true) {
	      zmq::message_t rx_msg;
	      zmq::message_t topic;
	      zmq::poll(p.data(), 1, -1); //block until received
	      if (p[0].revents & ZMQ_POLLIN) {
			// received something on the first (only) socket
			subscriber.recv(&topic, ZMQ_RCVMORE); 
			subscriber.recv(&rx_msg);
			std::string rx_str;
			rx_str.assign(static_cast<char *>(rx_msg.data()), rx_msg.size());
			posMessage->ParseFromString(rx_str.c_str());
			std::cout << "Received: NodeID = " << posMessage->sensorid() << std::endl;
			*xyzCoordinates = posMessage->position();
			std::cout << "X = " << xyzCoordinates->x() << " y = " << xyzCoordinates->y() << " z = " << xyzCoordinates->z() << std::endl;
		}
	}
}


int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cout << "Sorry, you forgot to pass port number! Right usage:./subscriber <port_number>\n";
        exit(0);
    }
    startSubscriber(argv[1]);
	return 0;
}
