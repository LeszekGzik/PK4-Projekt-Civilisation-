#include "MainMenu.h"
#include <Windows.h>

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
		MessageBox(NULL, ex.what(), "Run-Time Exception", MB_ICONERROR | MB_OK);
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

void MainMenu::addOptions()
{
	Page & page = page_control.current();
	sf::Vector2f position = INIT.POSITIONS.GAME_RECT_POS(sf::Vector2f(current_vmode.width, current_vmode.height));
	sf::Vector2f size = INIT.POSITIONS.GAME_RECT_SIZE(sf::Vector2f(current_vmode.width, current_vmode.height));

	page.addShape(INIT.GAME.RECT(position, size));

	check_fullscreen = INIT.OPTIONS.CHCK_BOX_FULLSCREEN(position);
	page.addComponent(check_fullscreen);
	check_richmode = INIT.OPTIONS.CHCK_BOX_RICHMODE(position);
	page.addComponent(check_richmode);
	check_zoomout = INIT.OPTIONS.CHCK_BOX_ZOOM_OUT(position);
	page.addComponent(check_zoomout);
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
	this->settings = new InitSettings(
		player, this->check_fullscreen->isChecked(), this->check_richmode->isChecked(), this->check_zoomout->isChecked());
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

void MainMenu::buttonClick_options(Component &, sf::Event::MouseButtonEvent)
{
	setPage(page_options);
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
	addButton(INIT.STRINGS.MAIN_BTN_OPTIONS, &button_click_options, 1);
	addButton(INIT.STRINGS.MAIN_BTN_EXIT, &button_click_exit, 2);
	
	// NEW GAME PAGE
	page_newgame = page_control.add();
	page_control.set(page_newgame);

	addButton(INIT.STRINGS.START_BTN_START, &button_click_start, 0);
	addButton(INIT.STRINGS.START_BTN_BACK, &button_click_back_to_main, 2);
	addGameSettings();

	// OPTIONS PAGE
	page_options = page_control.add();
	page_control.set(page_options);

	addButton(INIT.STRINGS.START_BTN_BACK, &button_click_back_to_main, 2);
	addOptions();
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
	this->button_click_options.set(this, &MainMenu::buttonClick_options);
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

Component * MainMenu::ConstantInitializers::Game::LABEL_PLAYERS_NUMBER(sf::Vector2f const & rect)
{
	Component * obj = new Label("NUMBER OF PLAYERS", sf::IntRect(rect.x + 16, rect.y + 16, 250, 32));
	obj->setFontSize(FONT_SIZE);
	return obj;
}

TextBox * MainMenu::ConstantInitializers::Game::EDIT_PLAYERS_NUMBER(sf::Vector2f const & rect)
{
	TextBox * obj = new TextBox(std::to_string(DEFAULT_PLAYERS), sf::IntRect(rect.x + 250, rect.y + 16, STRIP_SIZE, STRIP_SIZE));
	obj->setMaxLength(1);
	obj->setFontSize(FONT_SIZE);
	return obj;
}

sf::Shape * MainMenu::ConstantInitializers::Game::RECT(sf::Vector2f const & pos, sf::Vector2f const & size)
{
	sf::RectangleShape * rect = new sf::RectangleShape();
	rect->setFillColor(sf::Color(255, 255, 255, 127));
	rect->setPosition(pos);
	rect->setSize(size);
	return rect;
}

sf::Shape * MainMenu::ConstantInitializers::Game::RECT_PLAYERS(sf::Vector2f const & pos)
{
	sf::RectangleShape * rect = new sf::RectangleShape();
	rect->setFillColor(sf::Color(255, 255, 255, 200));
	rect->setPosition(pos.x, pos.y + 16);
	rect->setSize(sf::Vector2f(STRIP_HEADER_LENGTH, STRIP_SIZE));
	return rect;
}

TextBox * MainMenu::ConstantInitializers::Game::EDIT_PLAYER_NAME(sf::Vector2f const & pos)
{
	TextBox * edit = new TextBox("PLAYER", sf::IntRect(pos.x, pos.y, STRIP_CONTENT_LENGTH, STRIP_SIZE));
	edit->setFontSize(INIT.GAME.FONT_SIZE);
	edit->setTextPosition(sf::Vector2u(24, 8));
	edit->setBackColor(sf::Color(255, 255, 255, 200));
	edit->update();
	return edit;
}

Button * MainMenu::ConstantInitializers::Game::BTN_PLAYER_COLOR(sf::Vector2f const & pos)
{
	Button * btn = new Button("", sf::IntRect(pos.x + STRIP_CONTENT_LENGTH + 16, pos.y, STRIP_SIZE, STRIP_SIZE));
	btn->setBackColor(ColorUtils::sfColor(Color::Red, 200));
	btn->setHighlights(false);
	btn->setBorderColor(sf::Color(0, 0, 0, 127));
	btn->setBorderThickness(2);
	btn->setTag(Color::Red);
	return btn;
}

CheckBox * MainMenu::ConstantInitializers::Options::CHCK_BOX_FULLSCREEN(sf::Vector2f const & pos)
{
	CheckBox * box = new CheckBox(std::string("FULLSCREEN"), sf::IntRect(pos.x + 16, pos.y + 16, CHCK_BOX_LENGTH, 32));
	box->setFontSize(FONT_SIZE);
	box->update();
	return box;
}

CheckBox * MainMenu::ConstantInitializers::Options::CHCK_BOX_RICHMODE(sf::Vector2f const & pos)
{
	CheckBox * box = new CheckBox(std::string("RICH MODE"), sf::IntRect(pos.x + 16, pos.y + 88, CHCK_BOX_LENGTH, 32));
	box->setFontSize(FONT_SIZE);
	box->update();
	return box;
}

CheckBox * MainMenu::ConstantInitializers::Options::CHCK_BOX_ZOOM_OUT(sf::Vector2f const & pos)
{
	CheckBox * box = new CheckBox(std::string("WORLD ZOOM OUT"), sf::IntRect(pos.x + 16, pos.y + 52, CHCK_BOX_LENGTH, 32));
	box->setFontSize(FONT_SIZE);
	box->update();
	return box;
}
