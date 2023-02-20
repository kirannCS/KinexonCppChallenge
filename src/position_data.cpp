#include "../header/position_data.h"

// generates and returns thread-safe random  float number 
float PositionData::getRandomFloatNumber (float start, float end) {
	thread_local std::mt19937 generator(std::random_device{}());
	std::uniform_real_distribution<> dist(start,end); 
	return (float)dist(generator);
}

// generates and returns thread-safe random  int number 
int PositionData::getRandomIntNumber (int start, int end) {
	thread_local std::mt19937 generator(std::random_device{}());
	std::uniform_int_distribution<> dist(start,end); 
	return dist(generator);
}

//User defined  constructor of PositionData class
PositionData::PositionData() {
	// Assign random initial coordinates (x,y,z) to the player
	x = getRandomFloatNumber(0, XLIM);
	y = getRandomFloatNumber(0, YLIM);
	z = getRandomFloatNumber(1.0, ZLIM);
	// step_count indicates how many secs player would run in the same direction before he/she changes direction
	step_count = (unsigned short)getRandomIntNumber(MIN_STEP_COUNT,  MAX_STEP_COUNT);
}

// Adds noise of +- 30 (NOISE_THRESHOLD) to (X,Y) coordinates
void PositionData::addNoise() {
	float randx = getRandomFloatNumber(1.0, NOISE_THRESHOLD);
	float randy = getRandomFloatNumber(1.0, NOISE_THRESHOLD);
	
	if(((int)randx + (int)randy) % 2) { // if (x+y) is even add -ve noise
		x = abs(x - (randx / 100)); // dividing by 100 to convert cm to m  
		y = abs(y - (randy / 100)); 
	} else {
		x = x + (randx / 100); // Add positive noise 
		y = y + (randy / 100); 
	}
}

float PositionData::uniform() {
	return getRandomFloatNumber(0,RAND_MAX)/ RAND_MAX;
}

// Generates random (x,y, z) point in a circle - allows player to move in a random direction
// but not faster than human possible velocity (distance restricted with radius denoted as MAX_DIST_IN_ONE_SEC)
void PositionData::generateRandPointInCircle() {
	static float ang = 2 * PI * uniform();
	if(step_count <= 0) { // when step_count = 0, player to change his running direction with new angle
		ang = 2 * PI * uniform();
		// step_count is set to a different random number
		step_count = getRandomIntNumber(MIN_STEP_COUNT,  MAX_STEP_COUNT); 
	}
	float radius = MAX_DIST_IN_ONE_SEC;
	float hyp = sqrt(uniform()) * radius;
	while(true) {
		x = x + hyp * cos(ang);
		y = y + hyp * sin(ang);
		if(x < XLIM && y < YLIM && x > 0 && y > 0) // to make sure (x,y) coordinates are within (0, 100) limits
			break;
		// Otherwise change player direction and thus gurantee new (x,y) coordinates within (0,100)
		ang =  2 * PI * uniform(); 
	}
	step_count--;
	z = getRandomFloatNumber(1.0, ZLIM); // (1<=Z<=ZLIM) Assuming player is lying on ground, sitting, standing or in-air
}

// Print (x,y,z) coordinates of a player on console - used for console debugging
void PositionData::printCurPosition(unsigned short index) const {
	std::cout << "Player " + std::to_string(index) + " position == [" << x << "," << y << "," << z <<"]" << "\n";
}