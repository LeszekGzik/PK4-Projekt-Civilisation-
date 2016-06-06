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

			Component * LABEL_PLAYERS_NUMBER(sf::Vector2f const& rect)
			{
				Component * obj = new Label("NUMBER OF PLAYERS", sf::IntRect(rect.x + 16, rect.y + 16, 250, 32));
				obj->setFontSize(FONT_SIZE);
				return obj;
			}

			TextBox * EDIT_PLAYERS_NUMBER(sf::Vector2f const& rect)
			{
				TextBox * obj = new TextBox(std::to_string(DEFAULT_PLAYERS), sf::IntRect(rect.x + 250 , rect.y + 16, STRIP_SIZE, STRIP_SIZE));
				obj->setMaxLength(1);
				obj->setFontSize(FONT_SIZE);
				return obj;
			}

			sf::Shape * RECT(sf::Vector2f const& pos, sf::Vector2f const& size)
			{
				sf::RectangleShape * rect = new sf::RectangleShape();
				rect->setFillColor(sf::Color(255, 255, 255, 127));
				rect->setPosition(pos);
				rect->setSize(size);
				return rect;
			}

			sf::Shape * RECT_PLAYERS(sf::Vector2f const& pos)
			{
				sf::RectangleShape * rect = new sf::RectangleShape();
				rect->setFillColor(sf::Color(255, 255, 255, 200));
				rect->setPosition(pos.x, pos.y + 16);
				rect->setSize(sf::Vector2f(STRIP_HEADER_LENGTH, STRIP_SIZE));
				return rect;
			}

			TextBox * EDIT_PLAYER_NAME(sf::Vector2f const& pos)
			{
				TextBox * edit = new TextBox("PLAYER", sf::IntRect(pos.x, pos.y, STRIP_CONTENT_LENGTH, STRIP_SIZE));
				edit->setFontSize(INIT.GAME.FONT_SIZE);
				edit->setTextPosition(sf::Vector2u(24, 8));
				edit->setBackColor(sf::Color(255, 255, 255, 200));
				edit->update();
				return edit;
			}

			Button * BTN_PLAYER_COLOR(sf::Vector2f const& pos)
			{
				Button * btn = new Button("", sf::IntRect(pos.x + STRIP_CONTENT_LENGTH + 16, pos.y, STRIP_SIZE, STRIP_SIZE));
				btn->setBackColor(ColorUtils::sfColor(Color::Red, 200));
				btn->setHighlights(false);
				btn->setBorderColor(sf::Color(0, 0, 0, 127));
				btn->setBorderThickness(2);
				btn->setTag(Color::Red);
				return btn;
			}
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

		Game GAME;
		Miscellaneous MISC;
		Positions POSITIONS;
		Strings STRINGS;				
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

	int _main_btn_left;
	int _main_btn_top;
	int page_main;
	int page_newgame;
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
	TextBox::TextChange::Callback<MainMenu> textbox_edit_players_number;

	void addButton(std::string const& caption, Button::Clicked::EventDelegate func, int i);
	void addTextBox(sf::Vector2f& rect, int i);
	void addGameSettings();
	void buttonClick_exit(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_newgame(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_backToMain(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_start(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_color(Component&, sf::Event::MouseButtonEvent);
	void textboxEdit_playersNumber(Component&, std::string& old);
	void setPlayersNumber(int number);
	void setupComponents();
	void setupImage();
};

