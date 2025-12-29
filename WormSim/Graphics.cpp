#include "Graphics.h"
#include "ButtonEnum.h"


Graphics::Graphics(Simulation& simulation, int x, int y) : 
	simulation(simulation), 
	//tiles(simulation.getTilesRef()), 
	config(simulation.getConfigRef()), 
	boardWidth(simulation.getBoardWidth()),
	boardHeight(simulation.getBoardHeight())
{
	this->x = x;
	this->y = y;
	prepareButtons(985, 50, 170, 30);
	prepareInputs(1165, 50, 95, 30);
	generateWormBoxRandom();
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(x, y, "WormSim");
}

void Graphics::draw() {
	BeginDrawing();
	ClearBackground(BLACK);
	DrawText("WormSim", x / 2 - 50, 10, 20, WHITE);
	drawMenu();
	drawWormBox();
	drawEgg();
	drawWorm();
	drawWormOnMouse();
	drawFoodOnMouse();
	EndDrawing();
}

void Graphics::drawMenu() {
	//DrawRectangleLines(10, 40, 275, y - 50, WHITE);										//Lewe menu (?)
	DrawRectangleLines(x - 305, 40, x - (x - 305 + 10), y - 50, WHITE);					//Prawe menu
	drawInputs();
	drawButtons();
	drawSizeFrame();
	drawInfo();
}

void Graphics::prepareButtons(int startX, int startY, int width, int height) {
	Button bRegen(startX, startY, width, height, "Reg. podloza");
	buttons.push_back(bRegen);
	Button bHunger(startX, startY + 40, width, height, "Odpornosc na glod");
	buttons.push_back(bHunger);
	Button bSize(startX, startY + 80, width, height, "Maks. wielkosc");
	buttons.push_back(bSize);
	Button bLifespan(startX, startY + 120, width, height, "Sr. czas zycia");
	buttons.push_back(bLifespan);
	Button bChildren(startX, startY + 160, width, height, "Ilosc mlodych");
	buttons.push_back(bChildren);
	Button bProductivity(startX, startY + 200, width, height, "Sr. czas prod.");
	buttons.push_back(bProductivity);
	Button bGenerateRandom(startX, y - 50, 132, 30, "Losowo");
	buttons.push_back(bGenerateRandom);
	Button bGenerateHotspot(startX + 143, y - 50, 132, 30, "Strefy");
	buttons.push_back(bGenerateHotspot);
	Button bAddWorm(startX, startY + 240, width, height, "Losowy robak");
	buttons.push_back(bAddWorm);
	Button bDeleteWorms(startX + 180, startY + 240, 95, height, "Wyczysc");
	buttons.push_back(bDeleteWorms);
	Button bSimStop(startX, startY + 280, height, height, "0");
	buttons.push_back(bSimStop);
	Button bSimSpeed1(startX + height + 10, startY + 280, height, height, ">");
	buttons.push_back(bSimSpeed1);
	Button bSimSpeed2(startX + 2 * height + 20, startY + 280, height, height, ">>");
	buttons.push_back(bSimSpeed2);
	Button bSimSpeed3(startX + 3 * height + 30, startY + 280, height, height, ">>>");
	buttons.push_back(bSimSpeed3);
	Button bPlaceWorm(startX, y - 230, 132, 30, "Postaw robaka");
	buttons.push_back(bPlaceWorm);
	Button bPlaceFood(startX + 143, y - 230, 132, 30, "Postaw jedzenie");
	buttons.push_back(bPlaceFood);
	Button bConfirm(startX + 10, 420, 254, 30, "Potwierdz");
	buttons.push_back(bConfirm);

}

void Graphics::prepareInputs(int startX, int startY, int width, int height) {
	for (int i = 0; i < 6; i++) {
		int value;
		switch (i) {
		case 0:
			value = config.getRegenSpeed();
			break;
		case 1:
			value = config.getMaxHunger();
			break;
		case 2:
			value = config.getMaxSize();
			break;
		case 3:
			value = config.getMaxAge();
			break;
		case 4:
			value = config.getNewWormsAmount();
			break;
		case 5:
			value = config.getMaxProductivity();
			break;
		}
		Input input(startX, startY, width, height, value, i);
		inputs.push_back(input);
		startY += 40;
	}
	startY += 90;
	startX -= 145;
	Input iWidth(startX, startY, width, height, config.getWidth(), 6);
	inputs.push_back(iWidth);
	startX += 135;
	Input iHeight(startX, startY, width, height, config.getHeight(), 7);
	inputs.push_back(iHeight);
}

void Graphics::drawButtons() {
	using enum ButtonEnum;
	for (Button& button : buttons) {
		int x = button.getX();
		int y = button.getY();
		int width = button.getWidth();
		int height = button.getHeight();
		int value;
		if (manager.isMouseOver(x, y, width, height)) {
			button.setColor(RED);
			ButtonEnum e = static_cast <ButtonEnum> (button.getID());	//ID buttona na enum
			if (manager.isLMouseClicked()) {
				switch (e) {
				case REGEN:
					value = inputs[0].getValue();
					config.setRegenSpeed(value);
					break;
				case HUNGER:
					value = inputs[1].getValue();
					config.setMaxHunger(value);
					break;
				case SIZE:
					value = inputs[2].getValue();
					config.setMaxSize(value);
					break;
				case AGE:
					value = inputs[3].getValue();
					config.setMaxAge(value);
					break;
				case NEWWORMS:
					value = inputs[4].getValue();
					config.setNewWormsAmount(value);
					break;
				case PRODUCTIVITY:
					value = inputs[5].getValue();
					config.setMaxProductivity(value);
					break;
				case RANDOMGEN:
					generateWormBoxRandom();
					break;
				case HOTSPOTGEN:
					generateWormBoxHotspot();
					break;
				case RANDOMWORM:
					simulation.addWorm(1);
					break;
				case CLEAR:
					simulation.deleteWorms();
					simulation.deleteEggs();
					break;
				case PAUSE:
					simulation.setTickTime(0);
					break;
				case PLAY1X:
					simulation.setTickTime(1);
					break;
				case PLAY2X:
					simulation.setTickTime(3);
					break;
				case PLAY3X:
					simulation.setTickTime(6);
					break;
				case PLACEWORM:
					config.toggleWormOnMouse();
					config.setFoodOnMouse(false);
					break;
				case PLACEFOOD:
					config.toggleFoodOnMouse();
					config.setWormOnMouse(false);
					break;
				case CONFIRM:
					int newWidth = inputs[6].getValue();
					config.setBoardWidth(newWidth);
					int newHeight = inputs[7].getValue();
					config.setBoardHeight(newHeight);
					simulation.resizeBoard();
				}
			}
		} else button.setColor(WHITE);
		button.draw();
	}
}

void Graphics::drawWormOnMouse() {
	if (config.getWormOnMouse()) {
		int size = config.getSize();
		if (manager.isMouseOver(config.getStartX(), 40, config.getWidth() * size, config.getHeight() * size)) {
			int offsetX = ((GetMouseX() - config.getStartX()) / size);
			int mouseX = config.getStartX() + size * offsetX;
			int offsetY = ((GetMouseY() - 40) / size);
			int mouseY = 40 + size * offsetY;
			Rectangle rect = { mouseX - 1, mouseY - 1, size + 2, size + 2 };
			DrawRectangleLinesEx(rect, 2, LIGHTGRAY);
			if (manager.isLMousePressed() && manager.isLShiftClicked()) {
				simulation.addWorm(1, offsetX, offsetY);
			} else if (manager.isLMouseClicked()) {
				simulation.addWorm(1, offsetX, offsetY);
			}
		}
		if (manager.isRMouseClicked()) {
			config.setWormOnMouse(false);
		}
	}
}

void Graphics::drawFoodOnMouse() {
	if (config.getFoodOnMouse()) {
		int size = config.getSize();
		if (manager.isMouseOver(config.getStartX(), 40, config.getWidth() * size, config.getHeight() * size)) {
			int offsetX = ((GetMouseX() - config.getStartX()) / size);
			int mouseX = config.getStartX() + size * offsetX;
			int offsetY = ((GetMouseY() - 40) / size);
			int mouseY = 40 + size * offsetY;
			Rectangle rect = { mouseX - 1, mouseY - 1, size + 2, size + 2 };
			DrawRectangleLinesEx(rect, 2, PINK);
			if (manager.isLMousePressed() && manager.isLShiftClicked()) {
				simulation.addFood(1, offsetX, offsetY);
			} else if (manager.isLMouseClicked()) {
				simulation.addFood(1, offsetX, offsetY);
			}
		}
		if (manager.isRMouseClicked()) {
			config.setFoodOnMouse(false);
		}
	}
}

void Graphics::drawInputs() {
	for (Input& input : inputs) {
		int x = input.getX();
		int y = input.getY();
		int value = input.getValue();
		int width = input.getWidth();
		int height = input.getHeight();
		if (manager.isMouseOver(x, y, width, height)) {
			input.setColor(RED);
			if (manager.isLShiftClicked() && manager.isLMouseClicked()) {
				if (value + 10 > 950 && input.getId() == 6) {
					input.setValue(950);
				}
				else if (value + 10 > 670 && input.getId() == 7) {
					input.setValue(670);
				}
				else {
					input.setValue(value + 10);
				}
			}
			else if (manager.isLMouseClicked()) {
				if (value + 1 > 950 && input.getId() == 6) {
					input.setValue(950);
				}
				else if (value + 1 > 670 && input.getId() == 7) {
					input.setValue(670);
				}
				else {
					input.setValue(value + 1);
				}
			}
			if (manager.isLShiftClicked() && manager.isRMouseClicked()) {
				if (value - 10 < 1 && (input.getId() == 6 || input.getId() == 7)) {
					input.setValue(1);
				} 
				else if (value - 10 < 1) {
					input.setValue(0);
				} 
				else {
					input.setValue(value - 10);
				}
			}
			else if (manager.isRMouseClicked()) {
				if (value - 1 < 1 && (input.getId() == 6 || input.getId() == 7)) {
					input.setValue(1);
				}
				else if (value - 1 < 1) {
					input.setValue(0);
				}
				else {
					input.setValue(value - 1);
				}
			}
		} else input.setColor(WHITE);
		input.draw();
	}
}

void Graphics::drawSizeFrame() {
	DrawRectangleLines(x - 295, 370, 275, 90, WHITE);
	DrawText("><:", x - 285, 380, 20, WHITE);
	DrawText("Y:", x - 150, 380, 20, WHITE);
}

void Graphics::drawInfo() {
	const int startX = x - 295;
	const int startY = y - 190;

	DrawRectangleLines(startX, startY, 275, 130, WHITE);
	int x = startX + 5;
	int y = startY + 5;

	drawInfoLine("Ilosc robakow: ", std::to_string(simulation.getWorms().size()), x, y);
	y += 15;
	drawInfoLine("Ilosc martwych robakow: ", std::to_string(simulation.getDeadWorms()), x, y);
	y += 15;
	drawInfoLine("Regeneracja podloza: ", std::to_string(config.getRegenSpeed()), x, y);
	y += 15;
	drawInfoLine("Odpornosc na glod: ", std::to_string(config.getMaxHunger()), x, y);
	y += 15;
	drawInfoLine("Maksymalna wielkosc: ", std::to_string(config.getMaxSize()), x, y);
	y += 15;
	drawInfoLine("Sredni czas zycia: ", std::to_string(config.getMaxAge()), x, y);
	y += 15;
	drawInfoLine("Ilosc mlodych: ", std::to_string(config.getNewWormsAmount()), x, y);
	y += 15;
	drawInfoLine("Sr. cz. produktywnosci:", std::to_string(config.getMaxProductivity()), x, y);
}

void Graphics::drawInfoLine(const std::string& label, const std::string& value, int x, int y) {
	DrawText(label.c_str(), x, y, 15, WHITE);
	DrawText(value.c_str(), x + 210, y, 15, WHITE);
}

void Graphics::generateWormBoxRandom() {
	simulation.generateBoardRandom(config.getWidth(), config.getHeight());
}

void Graphics::generateWormBoxHotspot() {
	simulation.generateBoardHotspot(config.getWidth(), config.getHeight(), 15);
}

void Graphics::drawWormBox() const {
	const int startY = 40;
	int startX = config.getStartX();
	int size = config.getSize();

	drawTiles(startX, startY, config.getWidth(), config.getHeight(), size);
	DrawRectangleLines(startX, startY, config.getWidth() * size, config.getHeight() * size, WHITE);
}

void Graphics::drawWorm() {
	int size = config.getSize();
	for (Worm& worm : simulation.getWorms()) {
		int x = worm.getHeadX();
		int y = worm.getHeadY();
		std::vector <std::vector <int>> segments = worm.getSegments();
		if(!segments.empty()){
			for(std::vector <int> segment : segments){
				drawWorm(segment[0], segment[1], size);
			}
		}
		drawWorm(x, y, size);
		//drawWormPath(worm);		//Rysowanie pathfindingu robaka
	}
}

void Graphics::drawEgg() {
	int size = config.getSize();
	for (Egg& egg : simulation.getEggs()) {
		int x = egg.getX();
		int y = egg.getY();
		drawEgg(x, y, size);
	}
}

void Graphics::drawWorm(int x, int y, int size) const {
	DrawRectangle(config.getStartX() + x * size, 40 + y * size, size, size, WHITE);
}

void Graphics::drawEgg(int x, int y, int size) const {
	DrawRectangle(config.getStartX() + x * size, 40 + y * size, size, size, PINK);
}

void Graphics::drawWormPath(Worm& worm) {
	std::vector <std::vector <int>> availableTiles;
	if (!worm.getMovement().empty()) {
		availableTiles = worm.getMovement();
	}
	DrawRectangleLines(295 + worm.getHeadX() * 10, 40 + worm.getHeadY() * 10, 10, 10, BLUE);
	for (int i = 0; i < availableTiles.size(); i++) {
		if (!availableTiles[i].empty()) {
			DrawRectangleLines(295 + availableTiles[i][0] * 10, 40 + availableTiles[i][1] * 10, 10, 10, PINK);
		}
	}
}

void Graphics::drawTiles(const int startX, const int startY, const int width, const int height, const int size) const {
	std::vector <std::vector <Tile>>& tiles = simulation.getTilesRef();
	for (int i = 0; i < width; i++) {																					//HEIGHT
		for (int j = 0; j < height; j++) {
			int tileFood = tiles[i][j].getFoodAmount();
			if (tileFood == 3) DrawRectangle(startX + (i * size), startY + (j * size), size, size, GREEN);
			else if (tileFood == 2) DrawRectangle(startX + (i * size), startY + (j * size), size, size, ORANGE);
			else if (tileFood == 1) DrawRectangle(startX + (i * size), startY + (j * size), size, size, RED);
			else DrawRectangle(startX + (i * size), startY + (j * size), size, size, BLACK);
			//if (!tiles[i][j].isFree()) DrawRectangle(293 + (i * size), 38 + (j * size), 14, 14, BROWN);	//Rysowanie hitboxow
		}
	}
}