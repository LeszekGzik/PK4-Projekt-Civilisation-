#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Components.h"
#include "PageControl.h"
#include "GameDefinitions.h"

enum LoopExitCode { Exit, Menu, Play };

class MainMenu
{
public:
	struct ConstantInitializers
	{
		const sf::Color RECT_GAME_SETTINGS_COLOR = sf::Color(255, 255, 255, 127);
		const std::string MENU_IMG = "gfx\\menu.jpg";
		const std::string BTN_NEWGAME_CAPTION = "NEW GAME";
		const std::string BTN_EXIT_CAPTION = "EXIT";
		const std::string BTN_OPTIONS_CAPTION = "OPTIONS";
		const std::string BTN_BACK_CAPTION = "BACK";
		const std::string BTN_START_CAPTION = "START";
		const int MAIN_BTN_WIDTH = 240;
		const int MAIN_BTN_HEIGHT = 50;
		const int MAIN_BTN_FONT_SIZE = 24;
	};
	LoopExitCode loop();
	InitSettings * getInitSettings() { return settings; }
	void setPage(int page);

	MainMenu(sf::RenderWindow& window, sf::VideoMode& vmode);
	~MainMenu();

private:
	static ConstantInitializers INIT;

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
	InitSettings * settings = NULL;

	Button::Clicked::Callback<MainMenu> button_click_exit;
	Button::Clicked::Callback<MainMenu> button_click_newgame;
	Button::Clicked::Callback<MainMenu> button_click_back_to_main;
	Button::Clicked::Callback<MainMenu> button_click_start;

	void addButton(std::string const& caption, Button::Clicked::EventDelegate func, int i);
	void addGameSettings();
	void buttonClick_exit(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_newgame(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_backToMain(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_start(Component&, sf::Event::MouseButtonEvent);
	void setupComponents();
	void setupImage();
};

