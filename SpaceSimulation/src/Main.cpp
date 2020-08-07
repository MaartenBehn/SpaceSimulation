#include "pch.h"

#include "Main.h"

float g = 1000;
std::vector<Knot> knots;


class Knot {

public:

	glm::vec3 pos;
	glm::vec3 velocity;

	Knot(int& maxSize, int& maxStartSpeed) {

		pos = glm::vec3(RandFloat(maxSize), RandFloat(maxSize), RandFloat(maxSize));
		velocity = glm::vec3(RandFloat(maxStartSpeed), RandFloat(maxStartSpeed), RandFloat(maxStartSpeed));
	}

	void update() {

		// Add forces
		glm::vec3 newVelocity = velocity;
		for each (Knot knot in knots)
		{
			if (pos == knot.pos)
				continue;

			glm::vec3 relaitivPos = pos - knot.pos;
			float distance = glm::length(relaitivPos);
			relaitivPos = glm::normalize(relaitivPos);
			newVelocity += relaitivPos * (g / (distance * distance));
		}
		velocity = newVelocity;

		// Add velocity to pos so the knot moves by one step.
		pos += velocity;
	}
};

int main()
{
	int knotAmmount = 1000;
	int mapSize = 100;
	int maxStartSpeed = 10;
	int simulationRounds = 100;

	std::cout << "<--------------->" << std::endl;
	std::cout << "Knot ammount: " << knotAmmount << std::endl;
	std::cout << "Map Size: " << mapSize << std::endl;
	std::cout << "Max knot start velocity: " << maxStartSpeed << std::endl;
	std::cout << "<--------------->" << std::endl;

	for (size_t i = 0; i < knotAmmount; i++)
	{
		Knot knot(mapSize, maxStartSpeed);
		knots.push_back(knot);
	}

	std::ofstream file;
	file.open("../positions.txt");

	for (size_t i = 0; i < simulationRounds; i++)
	{
		std::cout << "\r";
		std::cout << "Calculating frame: " << i << " of " << simulationRounds;
		file << "frame: " << i << "\n";

		for (size_t i = 0; i < knots.size(); i++)
		{
			Knot& knot = knots[i];
			knot.update();

			file << knot.pos.x << " " << knot.pos.y << " " << knot.pos.z << "\n";
		}
	}

	file.close();

	std::cout << std::endl;
	std::cout << "Finisched" << std::endl;
	std::cout << std::endl;
}

