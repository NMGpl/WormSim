#pragma once
class Egg {
	int age = 0, maxAge = 20;
	bool hatched = 0;
	int posX, posY;
	int newWorms;
	void ageUp();
public:
	Egg(int posX, int posY, int newWorms);
	bool hatch();
	bool isHatched() const;
	int getX() const;
	int getY() const;
	int getNewWorms() const;
};

