#pragma once
class Worm {
	int age, hunger, size;
	int maxAge, maxHunger, maxSize;
public:
	Worm();
	~Worm();
	void initializeWorm();
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

