# KinexonCppChallenge
C++ program to generate random positions and publish them via ZeroMQ as google protocol buffers

# Contents
1. Technologies and libraries used
2. Repository structure
3. Build and Run instructions
4. Testing
5. Scope for optimizations
6. References

# 1. Technologies and libraries used
- Google Protocol buffers
- ZeroMQ Messaging Library
- CMake and Make for building
- Matplotlib for visualization


# 2. Repository structure
- src - cpp source files (rand_pos_gen.cpp and rand_pos_gen_one_skt.cpp are two different implementations based on number of skts are used, only one of them is used at a time)
- header - cpp header files
- messages - proto buffers
- doc - records of players' coordinates (.csv) generated during program execution and its visualization plots
- test - zmq subscriber and Python script to generate visualization plots


# 3. Build and Run instructions
- Build [libzmq](https://github.com/zeromq/libzmq) via cmake. First download and unzip the lib and cd to directory
  ```
  mkdir build
  cd build
  cmake ..
  sudo make -j4 install
  ```

- Build [cppzmq](https://github.com/zeromq/cppzmq) via cmake. First download and unzip the lib and cd to directory
  ```
  mkdir build
  cd build
  cmake ..
  sudo make -j4 install
  ```

- Build protocol buffers
  ```
  sudo apt-get install autoconf automake libtool curl make g++ unzip
  wget https://github.com/protocolbuffers/protobuf/releases/download/v3.11.0
  tar -xvzf protobuf-cpp-3.11.0.tar.gz
  cd protobuf-cpp-3.11.0.tar.gz
  ./configure
  make
  make install 
  sudo ldconfig
  ```

- Build Position Generator (posgen) program
  ```
  git clone https://github.com/kirannCS/KinexonCppChallenge
  cd KinexonCppChallenge
  mkdir build
  cd build
  cmake ..
  make
  ```

- Run Position Generator program
  ```
  ./posgen
  ```

# 4. Testing
1. Receive messages published by the Position Generator program. For that, run following commands on a different terminal
  ```
  cd <Project_folder>/test
  g++ -Wall subscriber.cpp ../build/messages/position.pb.cc -I ../build/messages/ -o subscriber -lzmq `pkg-config --cflags --libs protobuf`
  ./subscriber <port_number>
  ```
2. The generated random positions for all the sensors(players) are stored at dircetory <Project_folder>/doc/csv. For visualization on a 2D plot, run the following commands on a different terminal (check doc/plots to see saved plots)
  ``` 
  cd <Project_folder>/test
  python3 DrwaPlayerPositions.py
  ```
  

# 5. Scope for optimizations
- Logging mechanism
- Code optimizations
- More error handling

# 6. References
- Generate coordinates for a radom point in a circle is from the [link](https://www.tutorialspoint.com/generate-random-point-in-a-circle-in-cplusplus#)

