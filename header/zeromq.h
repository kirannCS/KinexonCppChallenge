
//
// Created by kiran on 19.2.2023.
//

#ifndef ZEROMQ_H
#define ZEROMQ_H

#include <zmq.hpp>
#include <iostream>

class ZmqPublisher {
public:
	ZmqPublisher() : context(1), publisher(context, ZMQ_PUB) {}

	void bind(std::string protocol ,short port){
		publisher.bind(protocol + "://*:" + std::to_string((int)port));
	}

	bool  send(std::string topic_to_publish, std::string data_to_publish){
		bool is_send_sucess = true;
		zmq::message_t message(data_to_publish.size());
		zmq::message_t topic(topic_to_publish.size());
		memcpy(topic.data(), topic_to_publish.data(), topic_to_publish.size()); 
		memcpy(message.data(), data_to_publish.c_str(), data_to_publish.size());
		publisher.send(topic, zmq::send_flags::sndmore); 
		auto res = publisher.send(message, zmq::send_flags::none); 
		if(!res.has_value()) is_send_sucess = false;
		message.rebuild();
		topic.rebuild();
		return is_send_sucess;
	}
	
	void close() {
		publisher.close();
		context.shutdown();
		context.close();
	}

private:
	zmq::context_t context;
	zmq::socket_t publisher;
};

#endif //ZEROMQ_H