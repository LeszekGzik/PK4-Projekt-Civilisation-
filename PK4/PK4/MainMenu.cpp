#include "MainMenu.h"

MainMenu::ConstantInitializers MainMenu::INIT;

LoopExitCode MainMenu::loop()
{
	try
	{
		setupComponents();
		setupImage();
		page_control.set(page_main);
	}
	catch (std::exception &ex)
	{

	}

	while (window.isOpen() && this->exit == LoopExitCode::Menu)
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				this->exit = LoopExitCode::Exit;
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				page_control.click(event.mouseButton);
				break;
			case sf::Event::MouseMoved:
				page_control.mouse(event.mouseMove);
				break;
			case sf::Event::TextEntered:
				page_control.text(event.text);
				break;
			}
		}
		window.clear();
		window.draw(background_sprite);
		window.draw(page_control);
		window.display();
	}

	return this->exit;
}

void MainMenu::setPage(int page)
{
	try
	{
		page_control.current().refresh();
		page_control.set(page);
	}
	catch (std::exception& ex)
	{

	}
}

void MainMenu::addButton(std::string const& caption, Button::Clicked::EventDelegate func, int i)
{
	Button * btn = new Button(caption, sf::IntRect(_main_btn_left, _main_btn_top + INIT.POSITIONS.MAIN_BTN_HEIGHT * i++, INIT.POSITIONS.MAIN_BTN_WIDTH, INIT.POSITIONS.MAIN_BTN_HEIGHT));
	btn->setFontSize(INIT.MISC.MAIN_BTN_FONT_SIZE);
	btn->setTextPosition(sf::Vector2u(48, 8));
	btn->eventClicked().reg(func);
	btn->update();
	page_control.current().addComponent(btn);
}

void MainMenu::addTextBox(sf::Vector2f & rect, int i)
{
	Page & page = page_control.current();
	sf::Vector2f position = INIT.POSITIONS.GAME_PLAYERS(rect);
	position.y += (INIT.GAME.STRIP_SIZE + INIT.POSITIONS.STRIPS_INTERVAL) * i;

	TextBox * edit = INIT.GAME.EDIT_PLAYER_NAME(position);
	Button * btn = INIT.GAME.BTN_PLAYER_COLOR(position);

	players[i].name = edit;
	players[i].color = btn;

	if (i >= INIT.GAME.DEFAULT_PLAYERS)
	{
		players[i].hide();
	}

	btn->eventClicked().reg(&button_click_color);

	page.addComponent(edit);
	page.addComponent(btn);
}

void MainMenu::addGameSettings()
{
	Page & page = page_control.current();
	sf::Vector2f position = INIT.POSITIONS.GAME_RECT_POS(sf::Vector2f(current_vmode.width, current_vmode.height));
	sf::Vector2f size = INIT.POSITIONS.GAME_RECT_SIZE(sf::Vector2f(current_vmode.width, current_vmode.height));

	page.addShape(INIT.GAME.RECT(position, size));
	page.addShape(INIT.GAME.RECT_PLAYERS(position));

	page.addComponent(INIT.GAME.LABEL_PLAYERS_NUMBER(position));
	TextBox * box = INIT.GAME.EDIT_PLAYERS_NUMBER(position);
	box->eventTextChange().reg(&textbox_edit_players_number);
	page.addComponent(box);

	for (int i = 0; i < PLAYERS_SIZE; i++)
	{
		addTextBox(position, i);
	}
}

void MainMenu::buttonClick_exit(Component &, sf::Event::MouseButtonEvent)
{
	this->exit = LoopExitCode::Exit;
}

void MainMenu::buttonClick_newgame(Component &, sf::Event::MouseButtonEvent)
{
	setPage(page_newgame);
}

void MainMenu::buttonClick_backToMain(Component &, sf::Event::MouseButtonEvent)
{
	setPage(page_main);
}

void MainMenu::buttonClick_start(Component &, sf::Event::MouseButtonEvent)
{
	std::string * names = new std::string[this->players_number];
	Color * colors = new Color[this->players_number];
	for (int i = 0; i < this->players_number; i++)
	{
		names[i] = players[i].name->getCaption();
		colors[i] = (Color)players[i].color->getTag();
	}
	PlayerSettings player(this->players_number, names, colors);
	MapSettings map(sf::Vector2i(12, 8));
	this->settings = new InitSettings(map, player);
	this->exit = LoopExitCode::Play;
}

void MainMenu::buttonClick_color(Component & obj, sf::Event::MouseButtonEvent mouse)
{
	Color color = (Color)obj.getTag();
	if (mouse.button == sf::Mouse::Button::Left)
		color = ColorUtils::next(color);
	else if (mouse.button == sf::Mouse::Button::Right)
		color = ColorUtils::prev(color);
	obj.setBackColor(ColorUtils::sfColor(color, 200));
	obj.setTag(color);
}

void MainMenu::textboxEdit_playersNumber(Component & sender, std::string & old)
{
	std::string text = sender.getCaption();
	int i;
	bool result = false;
	try
	{
		i = std::stoi(text);
		if (i <= ENGINE::max_players && i >= ENGINE::min_players)
			result = true;
	}
	catch (std::invalid_argument& ex)
	{
	}

	if (!result)
	{
		sender.setCaption(old);
	}
	else
	{
		setPlayersNumber(i);
	}
}

void MainMenu::setPlayersNumber(int number)
{
	int diff = number - this->players_number;

	if (diff > 0)
	{
		for (int i = this->players_number; i < number; i++)
		{
			players[i].show();
		}
	}
	else if (diff < 0)
	{
		for (int i = this->players_number - 1; i > number - 1; i--)
		{
			players[i].hide();
		}
	}

	this->players_number = number;
}

void MainMenu::setupComponents()
{
	_main_btn_left = current_vmode.width * 0;
	_main_btn_top = current_vmode.height * 0.4;

	// MAIN PAGE
	page_main = page_control.add();
	page_control.set(page_main);

	addButton(INIT.STRINGS.MAIN_BTN_NEWGAME, &button_click_newgame, 0);
	addButton(INIT.STRINGS.MAIN_BTN_OPTIONS, NULL, 1);
	addButton(INIT.STRINGS.MAIN_BTN_EXIT, &button_click_exit, 2);
	
	// NEW GAME PAGE
	page_newgame = page_control.add();
	page_control.set(page_newgame);

	addButton(INIT.STRINGS.START_BTN_START, &button_click_start, 0);
	addButton(INIT.STRINGS.START_BTN_BACK, &button_click_back_to_main, 2);
	addGameSettings();
}

void MainMenu::setupImage()
{
	if (!background_tex.loadFromFile(INIT.STRINGS.MENU_IMG))
		throw FileLoadException(INIT.STRINGS.MENU_IMG);

	sf::Vector2u tex_size = background_tex.getSize();
	float scale_x = float(current_vmode.width) / tex_size.x;
	float scale_y = float(current_vmode.height) / tex_size.y;
	float scale = (abs(1.f - scale_x) < abs(1.f - scale_y)) ? scale_x : scale_y;

	background_sprite.setTexture(background_tex);
	background_sprite.setScale(scale, scale);
}


MainMenu::MainMenu(sf::RenderWindow& window, sf::VideoMode& vmode) : window(window), current_vmode(vmode)
{
	this->button_click_exit.set(this, &MainMenu::buttonClick_exit);
	this->button_click_newgame.set(this, &MainMenu::buttonClick_newgame);
	this->button_click_back_to_main.set(this, &MainMenu::buttonClick_backToMain);
	this->button_click_start.set(this, &MainMenu::buttonClick_start);
	this->button_click_color.set(this, &MainMenu::buttonClick_color);
	this->textbox_edit_players_number.set(this, &MainMenu::textboxEdit_playersNumber);
}


MainMenu::~MainMenu()
{
}

void MainMenu::PlayerStrip::show()
{
	this->color->setVisible(true);
	this->color->setEnable(true);
	this->name->setVisible(true);
	this->name->setEnable(true);
}

void MainMenu::PlayerStrip::hide()
{
	this->color->setVisible(false);
	this->color->setEnable(false);
	this->name->setVisible(false);
	this->name->setEnable(false);
}
