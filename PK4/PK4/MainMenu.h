#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Components.h"
#include "PageControl.h"

enum LoopExitCode { Exit, Menu, Play };

class MainMenu
{
private:
	static const sf::Color RECT_GAME_SETTINGS_COLOR;
	static const std::string MENU_IMG;
	static const std::string BTN_NEWGAME_CAPTION;
	static const std::string BTN_EXIT_CAPTION;
	static const std::string BTN_OPTIONS_CAPTION;
	static const std::string BTN_BACK_CAPTION;
	static const std::string BTN_START_CAPTION;
	static const int MAIN_BTN_WIDTH = 240;
	static const int MAIN_BTN_HEIGHT = 50;
	static const int MAIN_BTN_FONT_SIZE = 24;

	int _main_btn_left;
	int _main_btn_top;
	int page_main;
	int page_newgame;
	LoopExitCode exit = LoopExitCode::Menu;

	sf::Texture background_tex;
	sf::Sprite background_sprite;
	sf::VideoMode& current_vmode;
	sf::RenderWindow& window;
	PageControl page_control;

	Button::Clicked::Callback<MainMenu> button_click_exit;
	Button::Clicked::Callback<MainMenu> button_click_newgame;
	Button::Clicked::Callback<MainMenu> button_click_back_to_main;

	void addButton(std::string const& caption, Button::Clicked::EventDelegate func, int i);
	void addGameSettings();
	void buttonClick_exit(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_newgame(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_backToMain(Component&, sf::Event::MouseButtonEvent);
	void setupComponents();
	void setupImage();

public:
	LoopExitCode loop();
	void setPage(int page);

	MainMenu(sf::RenderWindow& window, sf::VideoMode& vmode);
	~MainMenu();
};

