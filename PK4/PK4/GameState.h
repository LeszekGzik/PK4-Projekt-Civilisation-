#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "GameMap.h"
#include "GameDefinitions.h"
#include "EngineDefinitions.h"
#include "Player.h"
#include "PageControl.h"
#include "Components.h"


class GameState
{
public:
	GameMap * getGameMap();
	LoopExitCode loop();
	void scroll();

	GameState(sf::RenderWindow &target, sf::VideoMode vmode, InitSettings * settings);
	~GameState();

private:
	struct ConstantInitializers
	{
		struct Gui
		{
			sf::Shape * TOP_BAR(sf::VideoMode vmode)
			{
				sf::RectangleShape * shape = new sf::RectangleShape(sf::Vector2f(vmode.width, 80));
				shape->setFillColor(sf::Color(117, 58, 40, 255));
				return shape;
			}

			sf::Shape * BOT_BAR(sf::VideoMode vmode)
			{
				sf::RectangleShape * shape = new sf::RectangleShape(sf::Vector2f(vmode.width, 20));
				shape->setPosition(0, vmode.height - 20);
				shape->setFillColor(sf::Color(117, 58, 40, 255));
				return shape;
			}

			ComboButton * MENU_BTN()
			{
				ComboButton * btn = new ComboButton("MENU", sf::IntRect(10, 10, 190, 60));
				btn->setBackColor(sf::Color(233, 116, 81, 255));
				btn->setBorderColor(sf::Color(136, 45, 23, 255));
				btn->setBorderThickness(4);
				btn->setTextPosition(sf::Vector2u(48, 8));
				btn->update();
				return btn;
			}

			Button * MENU_BACK_BTN()
			{
				Button * btn = new Button("BACK TO MAIN", sf::IntRect(0, 0, 0, 40));
				btn->setBackColor(sf::Color(233, 116, 81, 200));
				btn->setFontSize(24);
				return btn;
			}

			Button * MENU_EXIT_BTN()
			{
				Button * btn = new Button("EXIT", sf::IntRect(0, 0, 0, 40));
				btn->setBackColor(sf::Color(233, 116, 81, 200));
				btn->setFontSize(24);
				return btn;
			}
		};

		Gui GUI;
	};

	static ConstantInitializers INIT;

	Button::Clicked::Callback<GameState> button_click_back;
	Button::Clicked::Callback<GameState> button_click_exit;

	LoopExitCode exit = Play;
	GameMap * game_map;
	PageControl page_control;
	sf::VideoMode current_vmode;
	sf::View gui;
	sf::View world;
	sf::RenderWindow & window;
	std::vector<Player> players;

	InGameObject * selected_object = nullptr;

	void init(InitSettings * settings);
	void initGui();
	void click(sf::Event::MouseButtonEvent&);

	void buttonClick_back(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_exit(Component&, sf::Event::MouseButtonEvent);
};

