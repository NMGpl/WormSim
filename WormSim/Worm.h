#pragma once
#include <vector>

class Worm {
	int age, hunger, size;
	int maxAge, maxHunger, maxSize, maxProductivity;
	int headX, headY;
	int eggCooldown;
	std::vector <std::vector <int>> segments;
	std::vector <std::vector <int>> movement;
	bool dead;

	void moveSegments();
public:
	Worm(int headX, int headY, int maxAge = 100, int maxHunger = 20, int maxSize = 2, int maxProductivity = 100);
	
	void move();
	void die();
	void ageUp();
	void grow();

	void modifyHunger(int hungerChange);
	void modifyAge(int ageChange);
	void modifySize(int sizeChange);

	void setHeadCords(int headX, int headY);
	void setMaxAge(int maxAge);
	void setAge(int age);
	void setMaxHunger(int maxHunger);
	void setHunger(int hunger);
	void setMaxSize(int maxSize);
	void setMaxProductivity(int maxProductivity);
	void setMovement(std::vector <std::vector <int>> movement);
	void modifyEggCooldown(int eggCooldown);
	

	int getHeadX() const;
	int getHeadY() const;
	int getMaxAge() const;
	int getAge() const;
	int getMaxHunger() const;
	int getHunger() const;
	int getMaxSize() const;
	int getSize() const;
	int getMaxProductivity() const;
	std::vector <std::vector <int>> getSegments() const;
	std::vector <std::vector <int>>& getMovement();
	bool isDead() const;
	int getEggCooldown() const;
};

