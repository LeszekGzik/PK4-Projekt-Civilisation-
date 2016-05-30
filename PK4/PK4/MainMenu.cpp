#include "MainMenu.h"

const sf::Color MainMenu::RECT_GAME_SETTINGS_COLOR = sf::Color(255, 255, 255, 127);
const std::string MainMenu::MENU_IMG = "gfx\\menu.jpg";
const std::string MainMenu::BTN_NEWGAME_CAPTION = "NEW GAME";
const std::string MainMenu::BTN_EXIT_CAPTION = "EXIT";
const std::string MainMenu::BTN_OPTIONS_CAPTION = "OPTIONS";
const std::string MainMenu::BTN_BACK_CAPTION = "BACK";
const std::string MainMenu::BTN_START_CAPTION = "START";

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
			case sf::Event::KeyPressed:
				page_control.keyDown(event.key);
				break;
			case sf::Event::MouseButtonPressed:
				page_control.click(event.mouseButton);
				break;
			case sf::Event::MouseMoved:
				page_control.mouse(event.mouseMove);
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
	Button * btn = new Button(caption, sf::IntRect(_main_btn_left, _main_btn_top + MAIN_BTN_HEIGHT * i++, MAIN_BTN_WIDTH, MAIN_BTN_HEIGHT));
	btn->setFontSize(MAIN_BTN_FONT_SIZE);
	btn->setTextPosition(sf::Vector2u(48, 8));
	btn->eventClicked().reg(func);
	btn->update();
	page_control.current().addComponent(btn);
}

void MainMenu::addGameSettings()
{
	float _top = current_vmode.height * 0.25;
	float _left = current_vmode.width * 0.25;
	float _width = current_vmode.width - _left * 2;
	float _height = current_vmode.height - _top * 2;

	Page & page = page_control.current();

	sf::RectangleShape * rect = new sf::RectangleShape();
	rect->setFillColor(RECT_GAME_SETTINGS_COLOR);
	rect->setPosition(_left, _top);
	rect->setSize(sf::Vector2f(_width, _height));
	page.addShape(rect);

	Component * component = new Label("TEST", sf::IntRect(_left + 32, _top + 32, 1, 1));
	page.addComponent(component);
	page.addComponent(new TextBox("BOX", sf::IntRect(_left + 32, _top + 64, 50, 50)));
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

void MainMenu::setupComponents()
{
	_main_btn_left = current_vmode.width * 0;
	_main_btn_top = current_vmode.height * 0.4;

	// MAIN PAGE
	page_main = page_control.add();
	page_control.set(page_main);

	addButton(BTN_NEWGAME_CAPTION, &button_click_newgame, 0);
	addButton(BTN_OPTIONS_CAPTION, NULL, 1);
	addButton(BTN_EXIT_CAPTION, &button_click_exit, 2);
	
	// NEW GAME PAGE
	page_newgame = page_control.add();
	page_control.set(page_newgame);

	addButton(BTN_START_CAPTION, NULL, 0);
	addButton(BTN_BACK_CAPTION, &button_click_back_to_main, 2);
	addGameSettings();
}

void MainMenu::setupImage()
{
	if (!background_tex.loadFromFile(MENU_IMG))
		throw FileLoadException(MENU_IMG);

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
}


MainMenu::~MainMenu()
{
}
