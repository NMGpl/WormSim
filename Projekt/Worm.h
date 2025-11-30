#pragma once
#include <vector>

class Worm {
	int age, hunger, size;
	int maxAge, maxHunger, maxSize;
	int headX, headY;
	std::vector <std::vector <int>> movement;
	bool dead;
public:
	Worm(int headX, int headY, int maxAge = 100, int maxHunger = 20, int maxSize = 2);
	std::vector <std::vector <int>> getMovement() const;
	void move();
	void setMovement(std::vector <std::vector <int>> movement);
	int getHeadX() const;
	int getHeadY() const;
	void setHeadCords(int headX, int headY);
	void die();
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
	void modifyHunger(int hungerChange);
	void modifyAge(int ageChange);
	int getMaxSize() const;
	void setMaxSize(int maxSize);
	int getSize() const;
	void setSize(int size);
};

