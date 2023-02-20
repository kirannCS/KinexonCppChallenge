
#include "position_data.h"
#include "zeromq.h"

// returns current time in microseconds
unsigned long getCurrentTimeInMicroseconds() {
	using namespace std::chrono;
	return (unsigned long)duration_cast<microseconds>(
            high_resolution_clock::now().time_since_epoch())
            .count();
}

void positionGenerator(int thread_index, std::mutex &m, ZmqPublisher *publisher) {
	std::unique_ptr<PositionData> playerPos = std::make_unique<PositionData>(); // thread_index as player id
	GeneratedPosition *posMessage = new GeneratedPosition(); // Protobuf class GeneratedPosition

	std::ofstream output_file; // To write player positions (x,y) to a file for visualization
	output_file.open ("../doc/csv/player_" + std::to_string(thread_index + 1) +".csv");
	output_file << "x,y\n";

	std::string data_to_publish;
	size_t count = SIMULATION_COUNT; // Number of simulation seconds
	while(count--) {
		playerPos->generateRandPointInCircle(); // Gets player's next random (x,y,z) position
		playerPos->addNoise(); // Add noise of +- 30cm
		playerPos->printCurPosition(thread_index);

		// Store (x,y,z) into Data3d protobuf
		Data3d *xyzCoordinates = new Data3d(); // freeing memory for this ptr is implicit to the class implementation
		unsigned long cur_time_usec = getCurrentTimeInMicroseconds();
		xyzCoordinates->set_x(playerPos->getX());
		xyzCoordinates->set_y(playerPos->getY());
		xyzCoordinates->set_z(playerPos->getZ());

		// Store timestamp, sensor_id and Data3d (x,y,z) into  protobuf
		posMessage->set_timestamp_usec(cur_time_usec);
		posMessage->set_sensorid((unsigned long)thread_index+1);
		posMessage->set_allocated_position(xyzCoordinates);

		posMessage->SerializeToString(&data_to_publish);

        m.lock();
		bool res  = publisher->send("SENSOR_DATA", data_to_publish); // Publish player's position via zmq_pub skt
		if(!res) {std::cerr << "zeromq sending message failed\n";}
		m.unlock();

		// Append new (x,y) into csv file for visualisation
		std::string row = std::to_string(playerPos->getX()) + "," + std::to_string(playerPos->getY()) + "\n";
		output_file << row;

		data_to_publish.clear();
		std::this_thread::sleep_for(std::chrono::seconds(1)); // 1hz = 1sec
	}
	output_file.close();
}

int main(int argc, char **argv) {
	int n = TOTAL_NO_OF_SENSORS;
	std::vector<std::thread> threads(n);

	ZmqPublisher *publisher = new ZmqPublisher(); // For publishing sensor data
	publisher->bind("tcp", 9000); // ZMQ port used 9000

    std::mutex m1;
	for(int i = 0; i < n; i++) {
		threads[i] = std::thread(positionGenerator, i, std::ref(m1), publisher);
	}

	for(int i = 0; i < n; i++) {
		threads[i].join();
	}

	std::cout << "Program exited normally\n";
	publisher->close();
	return 0;
}