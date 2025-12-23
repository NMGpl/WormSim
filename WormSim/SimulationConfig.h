#pragma once
class SimulationConfig{
	int maxAge, maxHunger, maxSize, regenSpeed, maxProductivity, newWormsAmount;
	int width, height;
	const int maxWidth = 670;
	const int maxHeight = 670;
	const int startX = 295;
	bool wormOnMouse, foodOnMouse;
public:
	SimulationConfig(int maxAge = 200, int maxHunger = 20, int maxSize = 4, int regenSpeed = 50, int maxProductivity = 175, int newWormsAmount = 2, int width = 67, int height = 67);
	
	void setMaxAge(int maxAge);
	void setMaxHunger(int maxHunger);
	void setMaxSize(int maxSize);
	void setRegenSpeed(int regenSpeed);
	void setMaxProductivity(int maxProductivity);
	void setNewWormsAmount(int newWormsAmount);
	void setWidth(int width);
	void setHeight(int height);
	void setWormOnMouse(bool state);
	void setFoodOnMouse(bool state);
	void toggleWormOnMouse();
	void toggleFoodOnMouse();

	int getMaxAge() const;
	int getMaxHunger() const;
	int getMaxSize() const;
	int getRegenSpeed() const;
	int getMaxProductivity() const;
	int getNewWormsAmount() const;
	int getSize() const;
	int getStartX() const;
	bool getWormOnMouse() const;
	bool getFoodOnMouse() const;
};

