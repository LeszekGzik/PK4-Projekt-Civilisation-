#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <unordered_map>
#include "GameMap.h"
#include "GameDefinitions.h"
#include "EngineDefinitions.h"
#include "Player.h"
#include "PageControl.h"
#include "Components.h"
#include "ContextInfo.h"
#include "Improvements.h"
#include "Ability.h"
#include "Hex.h"


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
			const float BOT_BAR_THICK = 40;

			sf::Shape * TOP_BAR(sf::VideoMode vmode)
			{
				sf::RectangleShape * shape = new sf::RectangleShape(sf::Vector2f(vmode.width, 80));
				shape->setFillColor(sf::Color(117, 58, 40, 255));
				return shape;
			}

			sf::Shape * BOT_BAR(sf::VideoMode vmode)
			{
				sf::RectangleShape * shape = new sf::RectangleShape(sf::Vector2f(vmode.width, BOT_BAR_THICK));
				shape->setPosition(0, vmode.height - BOT_BAR_THICK);
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

			Button * TURN_BTN(sf::VideoMode vmode)
			{
				Button * btn = new Button("END TURN", sf::IntRect(vmode.width - 200, 10, 190, 60));
				btn->setBackColor(sf::Color(233, 116, 81, 255));
				btn->setBorderColor(sf::Color(136, 45, 23, 255));
				btn->setBorderThickness(4);
				btn->setTextPosition(sf::Vector2u(12, 8));
				btn->update();
				return btn;
			}

			Label * TURN_LABEL(sf::VideoMode vmode)
			{
				Label * label = new Label("", sf::IntRect(vmode.width - 400, vmode.height - BOT_BAR_THICK, 100, 30));
				label->setBackColor(sf::Color::Transparent);
				label->setFontSize(28);
				label->setTextPosition(sf::Vector2u(4, 4));
				label->update();
				return label;
			}
		};

		struct Buttons
		{
			sf::Vector2i TOP_POS = sf::Vector2i(280, 8);
			sf::Vector2i TOP_SIZE = sf::Vector2i(64, 64);
			int TOP_INTERVAL = 4;

			sf::Vector2i BOT_POS = sf::Vector2i(12, 36);
			sf::Vector2i BOT_SIZE = sf::Vector2i(32, 32);
			int BOT_INTERVAL = 4;
		};

		struct Labels
		{
			sf::Vector2i POS = sf::Vector2i(220, 8);
			sf::Vector2i SIZE = sf::Vector2i(64, 64);
			int INTERVAL = 100;
			int OFFSET = 4;
		};

		Gui GUI;
		Buttons BUTTONS;
		Labels LABELS;
	};

	static ConstantInitializers INIT;

	Button::Clicked::Callback<GameState> button_click_back;
	Button::Clicked::Callback<GameState> button_click_exit;
	Button::Clicked::Callback<GameState> button_click_turn;
	Button::Clicked::Callback<GameState> button_click_grid;
	Button::Clicked::Callback<GameState> button_click_ability;
	Button::MouseEnter::Callback<GameState> button_enter_ability;
	Button::MouseLeave::Callback<GameState> button_leave_ability;
	ResourcesHandler::ResourceChange::Callback<GameState> resources_change;

	
	LoopExitCode exit = Play;
	GameMap * game_map;
	Hex hex_style;
	PageControl page_control;
	ContextInfo context_info;
	sf::VideoMode current_vmode;
	sf::View gui;
	sf::View world;
	sf::RenderWindow & window;
	Player * players;

	uint16_t player_count;
	uint16_t ability_page;
	uint16_t main_page;

	std::vector<Ability*> current_abilities;
	std::unordered_map<ResourceType, Label*> resource_labels;
	InGameObject * selected_object = nullptr;
	Player * active_player;
	Label * label_turn;
	int turn_cycle;

	void init(InitSettings * settings);
	void initGui();
	void nextTurn();
	void click(sf::Event::MouseButtonEvent&);
	void move(sf::Event::MouseMoveEvent&);
	void changeSelection(InGameObject * target);
	void listAbilities(InGameObject * object);
	PixelCoords worldPosition(PixelCoords window_pos);

	void addTopButton(uint32_t img_id, Button::Clicked::Callback<GameState> & callback, int position);
	void addBotButton(uint32_t img_id, Button::Clicked::Callback<GameState> & callback, int position);
	void addResourceLabel(uint32_t img_id, ResourceType type, int position);

	void buttonClick_back(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_exit(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_turn(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_grid(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_ability(Component&, sf::Event::MouseButtonEvent);
	void buttonMouseEnter_ability(Component&, sf::Event::MouseMoveEvent);
	void buttonMouseLeave_ability(Component&, sf::Event::MouseMoveEvent);
	void resourcesChange(ResourcesHandler&, ResourceType);
};
