#include "GameState.h"
#include <list>

GameState::ConstantInitializers GameState::INIT;

void GameState::scroll()
{
	bool moved = false;
	sf::Vector2f offset(0, 0);
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	if (mouse_pos.x < ENGINE::scroll_distance)
	{
		offset.x = -ENGINE::scroll_speed;
		moved = true;
	}
	else if (window.getSize().x - mouse_pos.x < ENGINE::scroll_distance)
	{
		offset.x = ENGINE::scroll_speed;
		moved = true;
	}
	if (mouse_pos.y < ENGINE::scroll_distance)
	{
		offset.y = -ENGINE::scroll_speed;
		moved = true;
	}
	else if (window.getSize().y - mouse_pos.y < ENGINE::scroll_distance)
	{
		offset.y = ENGINE::scroll_speed;
		moved = true;
	}
	
	if (moved)
		world.move(offset);
}

GameMap * GameState::getGameMap()
{
	return game_map; 
}

LoopExitCode GameState::loop()
{
	initGui();
	nextTurn();

	while (window.isOpen() && exit == LoopExitCode::Play)
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				exit = LoopExitCode::Exit;
				window.close();
				break;
			case sf::Event::MouseMoved:
				if (!page_control.mouse(event.mouseMove))
					move(event.mouseMove);
				break;
			case sf::Event::MouseButtonPressed:
				if (!page_control.click(event.mouseButton))
					click(event.mouseButton);
				break;
			case sf::Event::TextEntered:
				page_control.text(event.text);
				break;
			}
		}

		scroll(); 

		window.clear();
		window.setView(world);
		window.draw(*game_map);
		window.setView(gui);
		window.draw(page_control);
		window.draw(context_info);
		window.display();
	}

	return exit;
}

void GameState::init(InitSettings * settings)
{
	this->gui = window.getDefaultView();
	this->world = window.getDefaultView();
	this->game_map = new GameMap(settings->map.size, hex_style);
	this->game_map->showGrid(true);
	this->player_count = settings->player.count;
	this->players = new Player[this->player_count];
	for (int i = 0; i < this->player_count; i++)
	{
		this->players[i].setId(i);
		this->players[i].setColor(settings->player.colors[i]);
		this->players[i].setName(settings->player.names[i]);
	}

	this->turn_cycle = -1;

	InGameObject::setStyle(&hex_style);
	
	for (int i = 0; i < this->player_count; i++)
		game_map->getField(OffsetCoords(5 + i, 5))->newUnit<Archer>(this->players[i]);
	game_map->getField(OffsetCoords(2, 2))->newImprovement<Farm>(this->players[0]);
}

void GameState::initGui()
{
	int i = page_control.add();
	page_control.set(i);
	Page& page = page_control.current();

	page.addShape(INIT.GUI.TOP_BAR(current_vmode));
	page.addShape(INIT.GUI.BOT_BAR(current_vmode));

	ComboButton * btn = INIT.GUI.MENU_BTN();
	ComboButton::ComboItem * item;
	item = INIT.GUI.MENU_BACK_BTN();
	item->eventClicked().reg(&button_click_back);
	btn->addItem(item);
	item = INIT.GUI.MENU_EXIT_BTN();
	item->eventClicked().reg(&button_click_exit);
	btn->addItem(item);
	page.addComponent(btn);

	Component * cmp = INIT.GUI.TURN_BTN(current_vmode);
	cmp->eventClicked().reg(&button_click_turn);
	page.addComponent(cmp);

	this->label_turn = INIT.GUI.TURN_LABEL(current_vmode);
	page.addComponent(this->label_turn);
}

void GameState::nextTurn()
{
	if (++this->turn_cycle == this->player_count)
	{
		this->turn_cycle = 0;
		this->game_map->newTurn();
	}

	this->active_player = &(this->players[this->turn_cycle]);
	this->label_turn->setCaption(this->active_player->getName() + " turn");
	this->label_turn->setTextColor(ColorUtils::sfColor(this->active_player->getColor()));
}

void GameState::click(sf::Event::MouseButtonEvent & mouse)
{
	PixelCoords position = worldPosition(PixelCoords(mouse.x, mouse.y));
	Field * field = game_map->getField(position);

	if (field == nullptr)
		return;

	if (mouse.button == sf::Mouse::Button::Left)
	{
		InGameObject * object = field->objects().top();

		if (object != nullptr && object->getOwner() == *active_player)
		{
			if (this->selected_object != nullptr)
			{
				this->selected_object->select(false);
				if (this->selected_object == object)
				{
					this->selected_object = field->objects().next();
				}
				else
					this->selected_object = object;
			}
			else
				this->selected_object = object;

			this->selected_object->select(true);
		} 
		else if (this->selected_object != nullptr)
		{
			this->selected_object->select(false);
			this->selected_object = nullptr;
		}

		/*if (this->selected_object != object)
		{
			if (this->selected_object != nullptr)
				this->selected_object->select(false);

			if (object != nullptr)
				object->select(true);

			this->selected_object = object;
		}
		else if (object != nullptr)
		{
			this->selected_object->select(false);
			this->selected_object = field->objects().next();
			this->selected_object->select(true);
		}*/
	}
	else if (mouse.button == sf::Mouse::Button::Right)
	{
		if (this->selected_object != nullptr)
		{
			this->selected_object->select(false);
			AxialCoords sel_pos = this->selected_object->getPosition();
			game_map->moveUnit(sel_pos, field->getPosition());
			this->selected_object = nullptr;
		}
	}
}

void GameState::move(sf::Event::MouseMoveEvent & mouse)
{
	PixelCoords position = worldPosition(PixelCoords(mouse.x, mouse.y));
	Field * field = game_map->getField(position);
	if (field == nullptr)
	{
		context_info.setActive(false);
	}
	else
	{
		ContextInfoContent * content = field->getContextInfoContent();
		if (content != nullptr)
		{
			context_info.setActive(true);
			context_info.set(PixelCoords(mouse.x, mouse.y), content);
		}
		else
			context_info.setActive(false);
		delete content;
	}
}

PixelCoords GameState::worldPosition(PixelCoords window_pos)
{
	sf::Vector2f center = world.getCenter();
	sf::Vector2f offset;
	offset.x = center.x - current_vmode.width / 2;
	offset.y = center.y - current_vmode.height / 2;
	return PixelCoords(window_pos.x + offset.x, window_pos.y + offset.y);
}

void GameState::buttonClick_back(Component &, sf::Event::MouseButtonEvent)
{
	exit = LoopExitCode::Menu;
}

void GameState::buttonClick_exit(Component &, sf::Event::MouseButtonEvent)
{
	exit = LoopExitCode::Exit;
}

void GameState::buttonClick_turn(Component &, sf::Event::MouseButtonEvent)
{
	nextTurn();
}

GameState::GameState(sf::RenderWindow &window, sf::VideoMode vmode, InitSettings * settings) 
	: window(window), current_vmode(vmode)
{
	init(settings);
	this->button_click_back.set(this, &GameState::buttonClick_back);
	this->button_click_exit.set(this, &GameState::buttonClick_exit);
	this->button_click_turn.set(this, &GameState::buttonClick_turn);
}

GameState::~GameState()
{
	InGameObject::clear();
	if (game_map != nullptr)
		delete game_map;
	delete[player_count] players;
}


