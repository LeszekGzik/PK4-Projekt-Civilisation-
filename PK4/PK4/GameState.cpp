#include "GameState.h"
#include <list>
#include <Windows.h>

GameState::ConstantInitializers GameState::INIT;


void GameState::scroll()
{
	bool moved = false;
	sf::Vector2f offset(0, 0);
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
	if (mouse_pos.x < ENGINE::scroll_distance)
	{
		offset.x = -scroll_speed;
		moved = true;
	}
	else if (window.getSize().x - mouse_pos.x < ENGINE::scroll_distance)
	{
		offset.x = scroll_speed;
		moved = true;
	}
	if (mouse_pos.y < ENGINE::scroll_distance)
	{
		offset.y = -scroll_speed;
		moved = true;
	}
	else if (window.getSize().y - mouse_pos.y < ENGINE::scroll_distance)
	{
		offset.y = scroll_speed;
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
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
				case sf::Keyboard::Key::Add:
					this->scroll_speed += this->scroll_step;
					break;
				case sf::Keyboard::Key::Subtract:
					this->scroll_speed -= this->scroll_step;
					break;
				}
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
	this->hex_style = Hex(settings->zoomout ? ENGINE::basic_unit / 4 : ENGINE::basic_unit / 2);
	this->gui = window.getDefaultView();
	this->world = window.getDefaultView();
	this->game_map = new GameMap(hex_style);
	this->player_count = settings->player.count;
	this->players.reserve(this->player_count);
	for (int i = 0; i < this->player_count; i++)
	{
		this->players.emplace(this->players.end());
		this->players[i].setId(i);
		this->players[i].setColor(settings->player.colors[i]);
		this->players[i].setName(settings->player.names[i]);
		this->players[i].getResources().eventResourceChange().reg(&this->resources_change);
	}

	this->game_map->loadFromFile(settings->file, this->players);

	if (settings->richmode)
	{
		for (int i = 0; i < this->player_count; i++)
			this->players[i].getResources().set(ResourcesSet(50, 50, 50, 50));
	}

	this->turn_cycle = -1;

	InGameObject::setStyle(&hex_style);
}

void GameState::initGui()
{
	this->main_page = page_control.add();
	this->ability_page = page_control.add();
	page_control.set(this->main_page);
	page_control.merge(this->ability_page);

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

	this->label_objects = INIT.GUI.OBJECTS_LABEL(current_vmode);
	page.addComponent(this->label_objects);

	addTopButton(5, button_click_grid, 0);

	addResourceLabel(1, ResourceType::Food, 0);
	addResourceLabel(2, ResourceType::Wood, 1);
	addResourceLabel(3, ResourceType::Iron, 2);
	addResourceLabel(4, ResourceType::Gems, 3);
}

void GameState::nextTurn()
{
	Player * temp = this->active_player;
	changeSelection(nullptr);

	do
	{
		if (++this->turn_cycle == this->player_count)
		{
			this->turn_cycle = 0;
			this->game_map->newTurn();
		}

		this->active_player = &(this->players[this->turn_cycle]);

	} while (this->active_player->getNumberOfObjects() == 0);
	
	if (this->active_player == temp)
		this->label_turn->setCaption(this->active_player->getName() + " wins");
	else
		this->label_turn->setCaption(this->active_player->getName() + " turn");
	this->label_turn->setTextColor(ColorUtils::sfColor(this->active_player->getColor()));
	
	this->label_objects->setCaption(std::to_string(this->active_player->getNumberOfObjects()));

	for (std::unordered_map<ResourceType, Label*>::iterator it = this->resource_labels.begin();
		it != this->resource_labels.end(); it++)
	{
		it->second->setCaption(std::to_string(this->active_player->getResources().get(it->first)));
	}
}

void GameState::click(sf::Event::MouseButtonEvent & mouse)
{
	PixelCoords position = worldPosition(PixelCoords(mouse.x, mouse.y));
	Field * field = game_map->getField(position);

	if (field == nullptr)
		return;

	InGameObject * object = field->objects().top();

	if (mouse.button == sf::Mouse::Button::Left)
	{
		if (this->ability_being_casted == nullptr)
		{
			if (object != nullptr)
			{
				if (this->selected_object == object)
					object = field->objects().next();
				if (object->getOwner() != *this->active_player)
				{
					field->objects().next();
				}
			}
			else
			{
				object = field->getImprovement();
			}

			changeSelection(object);
		}
		else
		{
			this->ability_being_casted->use(field);
			this->ability_being_casted = nullptr;
		}
	}
	else if (mouse.button == sf::Mouse::Button::Right)
	{
		if (this->selected_object != nullptr)
		{
			if (this->selected_object == object && field->getImprovement() != nullptr)
			{
				changeSelection(field->getImprovement());
			}
			else
			{
				this->selected_object->select(false);
				this->page_control.get(this->ability_page).clear();

				AxialCoords sel_pos = this->selected_object->getField()->getPosition();
				game_map->moveUnit(sel_pos, field->getPosition());
				this->selected_object = nullptr;
			}
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
			context_info.setAligment(ContextInfo::Aligment::Down);
			context_info.setActive(true);
			context_info.set(PixelCoords(mouse.x, mouse.y), content);
		}
		else
			context_info.setActive(false);
		delete content;
	}
}

void GameState::changeSelection(InGameObject * target)
{
	this->ability_being_casted = nullptr;

	if (this->selected_object != nullptr)
		this->selected_object->select(false);

	if (target != nullptr && target->getOwner() == *this->active_player)
	{
		this->selected_object = target;
		this->selected_object->select(true);
		listAbilities(this->selected_object);
	}
	else
	{
		this->selected_object = nullptr;
		this->page_control.get(this->ability_page).clear();
	}
}

void GameState::listAbilities(InGameObject * object)
{
	Page& page = this->page_control.get(this->ability_page);
	page.clear();
	this->current_abilities.clear();
	this->ability_being_casted = nullptr;
	Abilities const& vector = object->getAbilities();
	for (size_t i = 0; i < vector.size(); i++)
	{
		Ability * ability = vector[i];
		this->current_abilities.push_back(ability);
		addBotButton(ability->getTextureId(), Textures::tilesetAbilities(), button_click_ability, i);
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

void GameState::addTopButton(uint32_t img_id, Button::Clicked::Callback<GameState>& callback, int position)
{
	sf::IntRect pos;
	pos.top = INIT.BUTTONS.TOP_POS.y;
	pos.left = this->current_vmode.width - INIT.BUTTONS.TOP_POS.x - (INIT.BUTTONS.TOP_SIZE.x + INIT.BUTTONS.TOP_INTERVAL) * position;
	pos.height = INIT.BUTTONS.TOP_SIZE.y;
	pos.width = INIT.BUTTONS.TOP_SIZE.x;
	Button * btn = new Button("", pos);
	btn->setDisplayStyle(DisplayStyle::Image);
	btn->setImage(Textures::tilesetButtons(), img_id);
	btn->eventClicked().reg(&callback);
	page_control.current().addComponent(btn);
}

void GameState::addBotButton(uint32_t img_id, Tileset & tileset, Button::Clicked::Callback<GameState>& callback, int position)
{
	sf::IntRect pos;
	pos.top = this->current_vmode.height - INIT.BUTTONS.BOT_POS.y;
	pos.left = INIT.BUTTONS.BOT_POS.x + (INIT.BUTTONS.BOT_SIZE.x + INIT.BUTTONS.BOT_INTERVAL) * position;
	pos.height = INIT.BUTTONS.BOT_SIZE.y;
	pos.width = INIT.BUTTONS.BOT_SIZE.x;
	Button * btn = new Button("", pos);
	btn->setDisplayStyle(DisplayStyle::Image);
	btn->setImage(tileset, img_id);
	btn->eventClicked().reg(&callback);
	btn->setTag(position);
	btn->eventMouseEnter().reg(&this->button_enter_ability);
	btn->eventMouseLeave().reg(&this->button_leave_ability);
	page_control.get(this->ability_page).addComponent(btn);
}

void GameState::addResourceLabel(uint32_t img_id, ResourceType type, int position)
{
	sf::IntRect pos;
	pos.top = INIT.LABELS.POS.y;
	pos.left = INIT.LABELS.POS.x + position * (INIT.LABELS.INTERVAL + INIT.LABELS.SIZE.x);
	pos.width = INIT.LABELS.SIZE.x;
	pos.height = INIT.LABELS.SIZE.y;

	Label * label = new Label("", pos);
	label->setDisplayStyle(DisplayStyle::Image);
	label->setImage(Textures::tilesetButtons(), img_id);
	this->page_control.current().addComponent(label);

	pos.left += INIT.LABELS.OFFSET + pos.width;
	label = new Label("", pos);
	this->resource_labels[type] = label;
	this->page_control.current().addComponent(label);
}

GameState::GameState(sf::RenderWindow &window, sf::VideoMode vmode)
	: window(window), current_vmode(vmode), scroll_speed(ENGINE::scroll_speed), scroll_step(1.f)
{
	this->button_click_back.set(this, &GameState::buttonClick_back);
	this->button_click_exit.set(this, &GameState::buttonClick_exit);
	this->button_click_turn.set(this, &GameState::buttonClick_turn);
	this->button_click_grid.set(this, &GameState::buttonClick_grid);
	this->button_click_ability.set(this, &GameState::buttonClick_ability);
	this->button_enter_ability.set(this, &GameState::buttonMouseEnter_ability);
	this->button_leave_ability.set(this, &GameState::buttonMouseLeave_ability);
	this->resources_change.set(this, &GameState::resourcesChange);
}

GameState::~GameState()
{
	InGameObject::clear();
	if (game_map != nullptr)
		delete game_map;
}

#pragma region EventHandlers

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

void GameState::buttonClick_grid(Component &, sf::Event::MouseButtonEvent)
{
	game_map->showGrid(!game_map->showGrid());
}

void GameState::buttonClick_techs(Component &, sf::Event::MouseButtonEvent)
{

}

void GameState::buttonClick_ability(Component & sender, sf::Event::MouseButtonEvent)
{
	int tag = sender.getTag();
	if (tag > this->current_abilities.size())
		throw IndexOutOfRangeException("CurrentAbilites", tag);
	else
	{
		if (this->current_abilities[tag]->isTargetable())
			this->ability_being_casted = this->current_abilities[tag];
		else
			this->current_abilities[tag]->use();
	}
}

void GameState::buttonMouseEnter_ability(Component & sender, sf::Event::MouseMoveEvent)
{
	sf::IntRect const& position = sender.getPosition();

	context_info.setAligment(ContextInfo::Aligment::Up);
	context_info.set(PixelCoords(position.left, position.top), this->selected_object->getAbilities()[sender.getTag()]->getContextInfoContent());
	context_info.setActive(true);
}

void GameState::buttonMouseLeave_ability(Component & sender, sf::Event::MouseMoveEvent)
{
	context_info.setActive(false);
}

void GameState::resourcesChange(ResourcesHandler & sender, ResourceType type)
{
	this->resource_labels[type]->setCaption(std::to_string(sender.get(type)));
}

#pragma endregion

#pragma region ConstantInitializers

sf::Shape * GameState::ConstantInitializers::Gui::TOP_BAR(sf::VideoMode vmode)
{
	sf::RectangleShape * shape = new sf::RectangleShape(sf::Vector2f(vmode.width, 80));
	shape->setFillColor(COLOR_FILL);
	return shape;
}

sf::Shape * GameState::ConstantInitializers::Gui::BOT_BAR(sf::VideoMode vmode)
{
	sf::RectangleShape * shape = new sf::RectangleShape(sf::Vector2f(BOT_BAR_LENGTH, BOT_BAR_THICK));
	shape->setPosition(vmode.width - BOT_BAR_LENGTH, vmode.height - BOT_BAR_THICK);
	shape->setFillColor(COLOR_FILL);
	return shape;
}

ComboButton * GameState::ConstantInitializers::Gui::MENU_BTN()
{
	ComboButton * btn = new ComboButton("MENU", sf::IntRect(10, 10, 190, 60));
	btn->setBackColor(COLOR_BUTTON);
	btn->setBorderColor(COLOR_OUTLINE);
	btn->setBorderThickness(4);
	btn->setTextPosition(sf::Vector2u(48, 8));
	btn->update();
	return btn;
}

Button * GameState::ConstantInitializers::Gui::MENU_BACK_BTN()
{
	Button * btn = new Button("BACK TO MAIN", sf::IntRect(0, 0, 0, 40));
	btn->setBackColor(COLOR_BUTTON);
	btn->setFontSize(24);
	return btn;
}

Button * GameState::ConstantInitializers::Gui::MENU_EXIT_BTN()
{
	Button * btn = new Button("EXIT", sf::IntRect(0, 0, 0, 40));
	btn->setBackColor(COLOR_BUTTON);
	btn->setFontSize(24);
	return btn;
}

Button * GameState::ConstantInitializers::Gui::TURN_BTN(sf::VideoMode vmode)
{
	Button * btn = new Button("END TURN", sf::IntRect(vmode.width - 200, 10, 190, 60));
	btn->setBackColor(COLOR_BUTTON);
	btn->setBorderColor(COLOR_OUTLINE);
	btn->setBorderThickness(4);
	btn->setTextPosition(sf::Vector2u(12, 8));
	btn->update();
	return btn;
}

Label * GameState::ConstantInitializers::Gui::TURN_LABEL(sf::VideoMode vmode)
{
	Label * label = new Label("", sf::IntRect(vmode.width - 400, vmode.height - BOT_BAR_THICK, 100, 30));
	label->setBackColor(sf::Color::Transparent);
	label->setFontSize(28);
	label->setTextPosition(sf::Vector2u(4, 4));
	label->update();
	return label;
}

Label * GameState::ConstantInitializers::Gui::OBJECTS_LABEL(sf::VideoMode vmode)
{
	Label * label = new Label("", sf::IntRect(vmode.width - 475, vmode.height - BOT_BAR_THICK, 100, 30));
	label->setBackColor(sf::Color::Transparent);
	label->setFontSize(28);
	label->setTextPosition(sf::Vector2u(4, 4));
	label->update();
	return label;
}

#pragma endregion



