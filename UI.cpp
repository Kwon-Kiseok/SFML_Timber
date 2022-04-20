#include "UI.h"
#include <sstream>

#include "Timer.h"
#include "Game.h"
#include "Player.h"
#include "SoundManager.h"
#include "SceneManager.h"

UI* UI::instance = nullptr;

UI::UI()
{
	fontKOMIKAPP = nullptr;
	textScore = nullptr;
	textMessage = nullptr;
	timerBar_width = 0;
	timerBar_height = 0;
	timer = nullptr;
	timerBarWidthPerSecond = 0;
	game = nullptr;
	soundManager = nullptr;
}

UI::~UI()
{
	delete fontKOMIKAPP;
	delete textScore;
	delete textMessage;

	fontKOMIKAPP = nullptr;
	textScore = nullptr;
	textMessage = nullptr;
}

UI* UI::GetInstance()
{
	if (nullptr == instance)
	{
		instance = new UI();
	}
	return instance;
}

void UI::init()
{
	fontKOMIKAPP = new Font();
	textScore = new Text();
	textMessage = new Text();

	fontKOMIKAPP->loadFromFile("fonts/KOMIKAP_.ttf");
	
	textScore->setFont(*fontKOMIKAPP);
	textMessage->setFont(*fontKOMIKAPP);

	textMessage->setString("Press Enter to start!");

	textMessage->setCharacterSize(75);
	textScore->setCharacterSize(100);

	textMessage->setFillColor(Color::White);
	textScore->setFillColor(Color::White);

	textScore->setPosition(20, 20);

	setTextRect();

	textMessage->setPosition(1920 * 0.5f, 1080 * 0.5f);

}

void UI::setTextRect()
{
	textRect = textMessage->getLocalBounds();
	textMessage->setOrigin(
		textRect.left + textRect.width * 0.5f,
		textRect.top + textRect.height * 0.5f
	);
}

void UI::initTimerBar()
{
	timerBar_width = 400;
	timerBar_height = 80;
	timerBarSize = Vector2f(timerBar_width, timerBar_height);
	timerBar.setSize(timerBarSize);
	timerPos = Vector2f(1920 * 0.5f - timerBar_width * 0.5f, 980.f);
	timerBar.setPosition(timerPos);
	timerBar.setFillColor(Color::Red);

	getTimer()->setTimeMax(6.0f);
	timerBarWidthPerSecond = timerBar_width / getTimer()->getTimeMax();
}

Text* UI::getTextScore()
{
	return textScore;
}

Text* UI::getTextMessage()
{
	return textMessage;
}

void UI::update()
{
	stringstream ss;
	ss << "Score = " << game->GetInstance()->GetPlayer()->GetScore();
	textScore->setString(ss.str());

	getTimer()->setRemaining(-1 * (getTimer()->getTime().asSeconds()));
	timerBarSize.x = getTimer()->getRemaining() * timerBarWidthPerSecond;
	timerBar.setSize(timerBarSize);

	if (getTimer()->getRemaining() < 0.f)
	{
		timerBarSize.x = 0.f;
		timerBar.setSize(timerBarSize);
		game->GetInstance()->SetPause(true);
		textMessage->setString("Out of Time!!");

		setTextRect();
		soundManager->GetInstance()->ootSound->play();
	}
}

void UI::draw(RenderWindow* window)
{
	window->draw(*textScore);
	if (game->GetInstance()->GetPause())
		window->draw(*textMessage);
	window->draw(timerBar);
}

Timer* UI::getTimer()
{
	return timer->GetInstance();
}

Font* UI::getFont()
{
	return fontKOMIKAPP;
}
