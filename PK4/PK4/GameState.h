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
	void init(InitSettings * settings);

	GameState(sf::RenderWindow &target, sf::VideoMode vmode);
	~GameState();

private:
	struct ConstantInitializers
	{
		struct Gui
		{
			const float BOT_BAR_THICK = 40;
			const float BOT_BAR_LENGTH = 500;

			sf::Color COLOR_FILL = sf::Color(213, 194, 153, 255);
			sf::Color COLOR_OUTLINE = sf::Color(183, 155, 98, 255);
			sf::Color COLOR_BUTTON = sf::Color(220, 190, 130, 255);

			sf::Shape * TOP_BAR(sf::VideoMode vmode);
			sf::Shape * BOT_BAR(sf::VideoMode vmode);
			ComboButton * MENU_BTN();
			Button * MENU_BACK_BTN();
			Button * MENU_EXIT_BTN();
			Button * TURN_BTN(sf::VideoMode vmode);
			Label * TURN_LABEL(sf::VideoMode vmode);
			Label * OBJECTS_LABEL(sf::VideoMode vmode);
		};

		struct Buttons
		{
			sf::Vector2i TOP_POS = sf::Vector2i(280, 8);
			sf::Vector2i TOP_SIZE = sf::Vector2i(64, 64);
			int TOP_INTERVAL = 4;

			sf::Vector2i BOT_POS = sf::Vector2i(12, 68);
			sf::Vector2i BOT_SIZE = sf::Vector2i(64, 64);
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
	Button::Clicked::Callback<GameState> button_click_techs;
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
	std::vector<Player> players;
	float scroll_speed;
	float scroll_step;

	uint16_t player_count;
	uint16_t ability_page;
	uint16_t main_page;

	std::vector<Ability*> current_abilities;
	std::unordered_map<ResourceType, Label*> resource_labels;
	Ability * ability_being_casted = nullptr;
	InGameObject * selected_object = nullptr;
	Player * active_player;
	Label * label_turn;
	Label * label_objects;
	int turn_cycle;

	void initGui();
	void nextTurn();
	void click(sf::Event::MouseButtonEvent&);
	void move(sf::Event::MouseMoveEvent&);
	void changeSelection(InGameObject * target);
	void listAbilities(InGameObject * object);
	PixelCoords worldPosition(PixelCoords window_pos);

	void addTopButton(uint32_t img_id, Button::Clicked::Callback<GameState> & callback, int position);
	void addBotButton(uint32_t img_id, Tileset & tileset, Button::Clicked::Callback<GameState> & callback, int position);
	void addResourceLabel(uint32_t img_id, ResourceType type, int position);

	void buttonClick_back(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_exit(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_turn(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_grid(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_techs(Component&, sf::Event::MouseButtonEvent);
	void buttonClick_ability(Component&, sf::Event::MouseButtonEvent);
	void buttonMouseEnter_ability(Component&, sf::Event::MouseMoveEvent);
	void buttonMouseLeave_ability(Component&, sf::Event::MouseMoveEvent);
	void resourcesChange(ResourcesHandler&, ResourceType);
};
