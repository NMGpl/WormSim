#pragma once
#include <vector>

class Worm {
	int age, hunger, size;
	int maxAge, maxHunger, maxSize, maxProductivity;
	int headX, headY;
	std::vector <std::vector <int>> segments;
	std::vector <std::vector <int>> movement;
	bool dead;
public:
	Worm(int headX, int headY, int maxAge = 100, int maxHunger = 20, int maxSize = 2, int maxProductivity = 100);
	std::vector <std::vector <int>>& getMovement();
	void move();
	void moveSegments();
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
	void modifySize(int sizeChange);
	void grow();
	int getMaxSize() const;
	void setMaxSize(int maxSize);
	int getSize() const;
	int getMaxProductivity() const;
	void setMaxProductivity(int maxProductivity);
	std::vector <std::vector <int>> getSegments() const;
};

