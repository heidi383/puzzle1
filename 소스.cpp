#define _CRT_SECURE_NO_WARNINGS
#include <bangtal>
using namespace bangtal;

#include <cstdlib> // ·£´ý
#include <ctime>


ScenePtr scene;
ObjectPtr game_board[16], game_original[16];
ObjectPtr start;


TimerPtr timer;
float animationTime = 0.01f;
int mixCount = 100;


int blank;
int game_index(ObjectPtr piece) {
	for (int i = 0; i < 16; i++)
		if (game_board[i] == piece) return i;
	return -1;
}

void game_move(int index) {
	auto piece = game_board[index];
	game_board[index] = game_board[blank];
	game_board[index]->locate(scene, 60 + 150 * (index % 4), 390 - 113 * (index / 4));
	game_board[blank] = piece;
	game_board[blank]->locate(scene, 60 + 150 * (blank % 4), 390 - 113 * (blank / 4));

	blank = index; 
}

bool check_move(int index) {
	if (blank % 4 > 0 && index == blank - 1) return true;
	if (blank % 4 < 3 && index == blank + 1) return true;
	if (blank / 4 > 0 && index == blank - 4) return true;
	if (blank / 4 < 3 && index == blank + 4) return true;

	return false;
}

int random_move() {
	int index = rand() % 16;
	while (!check_move(index)) {
		index = rand() % 16;
	}
	return index;
}

void start_game() {
	mixCount = 100;
	timer->set(animationTime);
	timer->start();

	blank = 15;
	game_board[blank]->hide();
	start->hide();
}


bool check_end() {
	for (int i = 0; i < 16; i++) {
		if (game_board[i] != game_original[i]) return false;
	}
	return true;
}

void end_game() {
	game_board[blank]->show();
	start->show();

	showMessage("¿Ï¼º!");
}

void init_game() {
	scene = Scene::create("µµ¶ó¿¡¸ù ÆÛÁñ", "µµ¶ó¿¡¸ù¹è°æ.png");
	char path[20];
	for(int i = 0; i < 16; i++) {
		sprintf(path, "images/%d.jpg", i + 1);
		game_board[i] = Object::create(path, scene, 60+150*(i%4), 390-113*(i/4));
		game_board[i]->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
			int index = game_index(piece);
			if (check_move(index)) {
				game_move(index);
				if (check_end()) {
					end_game();
				}
			}
			return true;
		});
		game_board[i] = game_original[i];
	}

	start = Object::create("START.png", scene, 200, 100);
	start->setOnMouseCallback([&](auto, auto, auto, auto)->bool{
		start_game();	
		return true;
	});

	timer = Timer::create(animationTime);
	timer->setOnTimerCallback([&](auto)->bool {
		game_move(random_move());
		mixCount--;
		if (mixCount > 0) {
			timer->set(animationTime);
			timer->start();
		}
		return true;
	});

	startGame(scene);
}

int main()
{
	srand((unsigned int)time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	init_game();

	return 0;
}