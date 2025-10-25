#pragma once
class SimulationConfig{
	int maxAge, maxHunger, maxSize;
public:
	
	void printConfig() const;

	void setMaxAge(int newMaxAge);
	int getMaxAge() const;
	void setMaxHunger(int newMaxHunger);
	int getMaxHunger() const;
	void setMaxSize(int newMaxSize);
	int getMaxSize() const;
};

