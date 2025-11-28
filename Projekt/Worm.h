#pragma once
#include <vector>

class Worm {
	int age, hunger, size;
	int maxAge, maxHunger, maxSize;
	int headX, headY;
	std::vector <std::vector <int>> movement;
public:
	Worm(int headX, int headY, int maxAge = 10, int maxHunger = 10, int maxSize = 2);
	std::vector <std::vector <int>> getMovement() const;
	void move();
	void setMovement(std::vector <std::vector <int>> movement);
	int getHeadX() const;
	int getHeadY() const;
	void setHeadCords(int headX, int headY);
	bool isDead() const;
	void ageUp();
	int getMaxAge() const;
	void setMaxAge(int maxAge);
	int getAge() const;
	void setAge(int age);
	int getMaxHunger() const;
	void setMaxHunger(int maxHunger);
	int getHunger() const;
	void setHunger(int hunger);
	int getMaxSize() const;
	void setMaxSize(int maxSize);
	int getSize() const;
	void setSize(int size);
};

