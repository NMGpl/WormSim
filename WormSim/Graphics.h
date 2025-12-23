#pragma once
#include "Button.h"
#include "Input.h"
#include "InputManager.h"
#include "Simulation.h"
#include "Worm.h"
#include "Tile.h"
#include "raylib.h"
#include "Egg.h"
#include <vector>
#include <string>

class Graphics {
	int x, y;
	int boardWidth, boardHeight;
	InputManager manager;
	Simulation& simulation;
	SimulationConfig& config;
	std::vector <Button> buttons;
	std::vector <Input> inputs;
	std::vector <std::vector <Tile>>& tiles;

	void drawMenu();
	void drawWormBox() const;
	void drawWorm();
	void drawWormOnMouse();
	void drawFoodOnMouse();
	void drawEgg();
	void drawWormPath(Worm& worm);
	void generateWormBoxRandom();
	void generateWormBoxHotspot();
	void drawWorm(int x, int y, int size) const;
	void drawEgg(int x, int y, int size) const;
	void drawTiles(const int startX, const int startY, const int width, const int height, const int size) const;
	void prepareButtons(int startX, int startY, int width, int height);
	void prepareInputs(int startX, int startY, int width, int height);
	void drawInfo();
	void drawInfoLine(const std::string& label, const std::string& value, int x, int y);
	void drawButtons();
	void drawInputs();
public:
	Graphics(Simulation& simulation, int x = 1280, int y = 720);
	void begin() const;
	void end() const;
	void draw();
};

