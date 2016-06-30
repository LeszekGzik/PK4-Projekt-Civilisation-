#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <set>
#include "Components.h"
#include "PageControl.h"
#include "GameDefinitions.h"
#include "EngineDefinitions.h"


class MainMenu
{
public:
	struct ConstantInitializers
	{
		struct Game
		{
			const float STRIP_SIZE = 42;
			const float STRIP_HEADER_LENGTH = 400;
			const float STRIP_CONTENT_LENGTH = 250;
			const int FONT_SIZE = 20;
			const int DEFAULT_PLAYERS = 2;

			Component * LABEL_PLAYERS_NUMBER(sf::Vector2f const& rect);
			TextBox * EDIT_PLAYERS_NUMBER(sf::Vector2f const& rect);
			sf::Shape * RECT(sf::Vector2f const& pos, sf::Vector2f const& size);
			sf::Shape * RECT_PLAYERS(sf::Vector2f const& pos);
			TextBox * EDIT_PLAYER_NAME(sf::Vector2f const& pos);
			Button * BTN_PLAYER_COLOR(sf::Vector2f const& pos);
		};

		struct Miscellaneous
		{
			const int MAIN_BTN_FONT_SIZE = 24;
		};

		struct Positions
		{
			const float STRIP_SIZE = 42;
			const float STRIPS_INTERVAL = 8;
			const float GAME_EDIT_WIDTH = 100;
			const sf::Vector2f GAME_PLAYERS(sf::Vector2f const& rect) { return sf::Vector2f(rect.x, rect.y + STRIP_SIZE + 32); }
			const sf::Vector2f GAME_RECT_POS(sf::Vector2f const& window) { return sf::Vector2f(window.x * 0.25, window.y * 0.25); }
			const sf::Vector2f GAME_RECT_SIZE(sf::Vector2f const& window) { return sf::Vector2f(window.x * 0.5, window.y * 0.5); }
			const int MAIN_BTN_WIDTH = 240;
			const int MAIN_BTN_HEIGHT = 50;
		};

		struct Strings
		{
			const std::string MENU_IMG = "gfx\\menu.jpg";
			const std::string MAIN_BTN_NEWGAME = "NEW GAME";
			const std::string MAIN_BTN_EXIT = "EXIT";
			const std::string MAIN_BTN_OPTIONS = "OPTIONS";
			const std::string START_BTN_BACK = "BACK";
			const std::string START_BTN_START = "START";
		};

		struct Options
		{
			const int FONT_SIZE = 20;
			const int CHCK_BOX_LENGTH = 275;

			CheckBox * CHCK_BOX_FULLSCREEN(sf::Vector2f const& pos);
			CheckBox * CHCK_BOX_RICHMODE(sf::Vector2f const& pos);
			CheckBox * CHCK_BOX_ZOOM_OUT(sf::Vector2f const& pos);
		};

		Game GAME;
		Miscellaneous MISC;
		Positions POSITIONS;
		Strings STRINGS;	
		Options OPTIONS;
	};

	LoopExitCode loop();
	InitSettings * getInitSettings() { return settings; }
	void setPage(int page);

	MainMenu(sf::RenderWindow& window, sf::VideoMode& vmode);
	~MainMenu();

private:
	struct PlayerStrip
	{
		TextBox * name = NULL;
		Button * color = NULL;
		void show();
		void hide();
	};

	static ConstantInitializers INIT;
	const int PLAYERS_SIZE = ENGINE::max_players;
	PlayerStrip players[ENGINE::max_players];
	CheckBox * check_fullscreen;
	CheckBox * check_richmode;
	CheckBox * check_zoomout;

	int _main_btn_left;
	int _main_btn_top;
	int page_main;
	int page_newgame;
	int page_options;
	int players_number = INIT.GAME.DEFAULT_PLAYERS;
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
	Button::Clicked::Callback<MainMenu> button_click_color;
	Button::Clicked::Callback<MainMenu> button_click_options;
	TextBox::TextChange::Callback<MainMenu> textbox_edit_players_number;

	void addButton(std::string const& caption, Button::Clicked::EventDelegate func, int i);
	void addTextBox(sf::Vector2f& rect, int i);
	void addGameSettings();
	void addOptions();
	void buttonClick_exit(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_newgame(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_backToMain(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_start(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_color(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_options(Component&, sf::Event::MouseButtonEvent);
	void textboxEdit_playersNumber(Component&, std::string& old);
	void setPlayersNumber(int number);
	void setupComponents();
	void setupImage();
};

