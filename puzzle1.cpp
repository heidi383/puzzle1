#include <bangtal>
using namespace bangtal;

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);


	auto scene = Scene::create("도라에몽 퍼즐", "도라에몽배경.jpg");

	startGame(scene);

}