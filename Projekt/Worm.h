#pragma once
class Worm {
	int age, hunger, size;
	int maxAge;
public:
	Worm();
	~Worm();
	void initializeWorm();
	bool isDead() const;
	void ageUp();
	void setMaxAge(int maxAge);
	int getAge() const;
	void setAge(int age);
};

