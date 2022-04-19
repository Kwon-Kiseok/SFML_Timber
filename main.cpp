#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <sstream>

using namespace sf;
using namespace std;

enum class side
{
    LEFT,
    RIGHT,
    NONE
};

void UpdateBranches(side sides[], int length, mt19937& gen)
{
    for (int i = length - 1; i >= 0; --i)
    {
        sides[i] = sides[i - 1];
    }
    int rnd = gen() % 5;
    switch (rnd)
    {
    case 0:
        sides[0] = side::LEFT;
        break;
    case 1:
        sides[0] = side::RIGHT;
        break;
    default:
        sides[0] = side::NONE;
        break;
    }
}

int main()
{
    random_device rd;   // non-deterministic generator
    mt19937 gen(rd());  // to seed mersenne twister.

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "Timber", Style::Default);

    Texture textureBackGround;
    textureBackGround.loadFromFile("graphics/background.png");

    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");

    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");

    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");

    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    // Prepare the player
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    // The player starts on the left
    side playerSide = side::LEFT;

    // Prepare the gravestone
    Texture textureRIP;
    textureRIP.loadFromFile("graphics/rip.png");
    Sprite spriteRIP;
    spriteRIP.setTexture(textureRIP);
    spriteRIP.setPosition(600, 860);

    // Prepare the axe
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);

    // Line the axe up with the tree
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;

    // Prepare the flying log
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);

    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);

    SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("sound/death.wav");
    Sound death;
    death.setBuffer(deathBuffer);

    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    Sound oot;
    oot.setBuffer(ootBuffer);

    // Some other useful log related variables
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;

    Font fontKOMIKAPP;
    fontKOMIKAPP.loadFromFile("fonts/KOMIKAP_.ttf");

    Text textScore;
    textScore.setFont(fontKOMIKAPP);
    Text textMessage;
    textMessage.setFont(fontKOMIKAPP);

    textMessage.setString("Press Enter to start!");

    textMessage.setCharacterSize(75);
    textScore.setCharacterSize(100);

    textMessage.setFillColor(Color::White);
    textScore.setFillColor(Color::White);

    textScore.setPosition(20, 20);

    FloatRect textRect = textMessage.getLocalBounds();
    textMessage.setOrigin(
        textRect.left + textRect.width * 0.5f,
        textRect.top + textRect.height * 0.5f
    );

    textMessage.setPosition(1920 * 0.5f, 1080 * 0.5f);

    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackGround);
    spriteBackground.setPosition(0, 0);

    Sprite spriteCloud_1;
    spriteCloud_1.setTexture(textureCloud);
    spriteCloud_1.setPosition(0, 0);

    Sprite spriteCloud_2;
    spriteCloud_2.setTexture(textureCloud);
    spriteCloud_2.setPosition(0, 150);

    Sprite spriteCloud_3;
    spriteCloud_3.setTexture(textureCloud);
    spriteCloud_3.setPosition(0, 300);

    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 800);

    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(810, 0);

    const int countBranches = 6;
    Sprite spriteBranches[countBranches];
    side sideBranches[countBranches];
    for (int i = 0; i < countBranches; ++i)
    {
        spriteBranches[i].setTexture(textureBranch);
        spriteBranches[i].setPosition(-2000, -2000);
        spriteBranches[i].setOrigin(220, 40);

        sideBranches[i] = side::RIGHT;
    }

    bool beeActive = false;
    float beeSpeed = 0.f;

    bool cloud_1_Active = false;
    float cloud_1_Speed = 0.f;

    bool cloud_2_Active = false;
    float cloud_2_Speed = 0.f;
    
    bool cloud_3_Active = false;
    float cloud_3_Speed = 0.f;

    RectangleShape timerBar;
    float timerBar_width = 400;
    float timerBar_height = 80;
    Vector2f timerBarSize = Vector2f(timerBar_width, timerBar_height);
    timerBar.setSize(timerBarSize);
    Vector2f timerPos = Vector2f(1920 * 0.5f - timerBar_width * 0.5f, 980.f);
    timerBar.setPosition(timerPos);
    timerBar.setFillColor(Color::Red);

    int score = 100;
    const float timeMax = 6.0f;
    float timeRemaining = timeMax;
    float timerBarWidthPerSecond = timerBar_width / timeMax;

    bool acceptInput = false;

    bool isPause = true;
    Clock clock;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
                break;
            case Event::KeyReleased:
                if (event.key.code == Keyboard::Left ||
                    event.key.code == Keyboard::Right)
                {
                    acceptInput = true;
                    spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
                }
                break;
            case Event::KeyPressed:
                switch (event.key.code)
                {
                case Keyboard::Escape:
                    window.close();
                    break;
                case Keyboard::Return:
                {
                    isPause = false;

                    score = 0;
                    timeRemaining = timeMax;
                    acceptInput = true;

                    for (int i = 0; i < countBranches; ++i)
                    {
                        sideBranches[i] = side::NONE;
                    }

                    spriteRIP.setPosition(675, 2000);
                    spritePlayer.setPosition(580, 720);
                }
                    break;
                case Keyboard::Left:
                    if(acceptInput && !isPause)   
                    {
                        playerSide = side::LEFT;
                        ++score;
                        timeRemaining += (2.f / score) + 0.15f;
                        spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
                        spritePlayer.setPosition(720, 720);
                        UpdateBranches(sideBranches, countBranches, gen);

                        spriteLog.setPosition(810, 720);
                        logSpeedX = 5000;
                        logActive = true;

                        chop.play();

                        acceptInput = false;
                    }
                    break;
                case Keyboard::Right:
                if(acceptInput && !isPause)
                {
                    playerSide = side::RIGHT;
                    ++score;
                    timeRemaining += (2.f / score) + 0.15f;
                    spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);
                    spritePlayer.setPosition(1200, 720);

                    UpdateBranches(sideBranches, countBranches, gen);

                    spriteLog.setPosition(810, 720);
                    logSpeedX = -5000;
                    logActive = true;

                    chop.play();

                    acceptInput = false;
                }
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        Time dt = clock.restart();

        // 업데이트
        if (!isPause)
        {
            // 벌
            if (!beeActive)
            {
                // 벌 초기화
                beeSpeed = gen() % 200 + 200;
                beeSpeed *= -1.f;
                float y = gen() % 500 + 500;
                spriteBee.setPosition(2000, y);
                beeActive = true;
            }
            else
            {
                // 벌 이동
                float deltaX = beeSpeed * dt.asSeconds();
                Vector2f currPos = spriteBee.getPosition();
                currPos.x += deltaX;
                spriteBee.setPosition(currPos);

                // 화면 밖에 나갔는 지 
                if (currPos.x < -100)
                {
                    beeActive = false;
                }
            }

            // 구름 1
            if (!cloud_1_Active)
            {
                cloud_1_Speed = gen() % 150 + 150;
                cloud_1_Speed *= -1;
                float y = gen() % 150 + 300;
                spriteCloud_1.setPosition(2000, y);
                cloud_1_Active = true;
            }
            else
            {
                float deltaX = cloud_1_Speed * dt.asSeconds();
                Vector2f currPos = spriteCloud_1.getPosition();
                currPos.x += deltaX;
                spriteCloud_1.setPosition(currPos);

                if (currPos.x < -300)
                {
                    cloud_1_Active = false;
                }
            }

            // 구름 2
            if (!cloud_2_Active)
            {
                cloud_2_Speed = gen() % 150 + 150;
                cloud_2_Speed *= -1;
                float y = gen() % 150 + 100;
                spriteCloud_2.setPosition(2000, y);
                cloud_2_Active = true;
            }
            else
            {
                float deltaX = cloud_2_Speed * dt.asSeconds();
                Vector2f currPos = spriteCloud_2.getPosition();
                currPos.x += deltaX;
                spriteCloud_2.setPosition(currPos);

                if (currPos.x < -300)
                {
                    cloud_2_Active = false;
                }
            }

            // 구름 3
            if (!cloud_3_Active)
            {
                cloud_3_Speed = gen() % 80 + 80;
                cloud_3_Speed *= -1;
                float y = gen() % 150;
                spriteCloud_3.setPosition(2000, y);
                cloud_3_Active = true;
            }
            else
            {
                float deltaX = cloud_3_Speed * dt.asSeconds();
                Vector2f currPos = spriteCloud_3.getPosition();
                currPos.x += deltaX;
                spriteCloud_3.setPosition(currPos);

                if (currPos.x < -300)
                {
                    cloud_3_Active = false;
                }
            }

            if (playerSide == side::LEFT)
            {
                spritePlayer.setScale(-1.0f, 1.0f);
            }
            else
            {
                spritePlayer.setScale(1.0f, 1.0f);
            }

            stringstream ss;
            ss << "Score = " << score;
            textScore.setString(ss.str());

            timeRemaining -= dt.asSeconds();
            timerBarSize.x = timeRemaining * timerBarWidthPerSecond;
            timerBar.setSize(timerBarSize);
            
            if (timeRemaining < 0.f)
            {
                timerBarSize.x = 0.f;
                timerBar.setSize(timerBarSize);
                isPause = true;

                textMessage.setString("Out of Time!!");

                FloatRect textRect = textMessage.getLocalBounds();
                textMessage.setOrigin(
                    textRect.left + textRect.width * 0.5f,
                    textRect.top + textRect.height * 0.5f
                );

                oot.play();
            }

            for (int i = 0; i < countBranches; ++i)
            {
                float height = 150 * i;

                switch (sideBranches[i])
                {
                case side::LEFT:
                    spriteBranches[i].setPosition(610, height);
                    spriteBranches[i].setRotation(180);
                    break;
                case side::RIGHT:
                    spriteBranches[i].setPosition(1330, height);
                    spriteBranches[i].setRotation(0);
                    break;
                default:
                    spriteBranches[i].setPosition(-2000, -2000);
                    break;
                }
            }

            if (logActive)
            {
                Vector2f logPos = spriteLog.getPosition();
                logPos.x += logSpeedX * dt.asSeconds();
                logPos.y += logSpeedY * dt.asSeconds();
                spriteLog.setPosition(logPos);

                if (logPos.x < -100 || logPos.x > 2000)
                {
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }

            if (sideBranches[countBranches - 1] == playerSide)
            {
                isPause = true;
                acceptInput = false;

                if (playerSide == side::LEFT)
                    spriteRIP.setPosition(580, 760);
                else
                    spriteRIP.setPosition(spritePlayer.getPosition());
                spritePlayer.setPosition(3000, 600);

                textMessage.setString("SQUISHED!");
                FloatRect textRect = textMessage.getLocalBounds();
                textMessage.setOrigin(
                    textRect.left + textRect.width * 0.5f,
                    textRect.top + textRect.height * 0.5f
                );

                death.play();
            }
        }
        // 렌더
        // world
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteCloud_3);
        window.draw(spriteCloud_2);
        window.draw(spriteCloud_1);
        window.draw(spriteTree);

        for (int i = 0; i < countBranches; ++i)
        {
            window.draw(spriteBranches[i]);
        }

        window.draw(spritePlayer);
        window.draw(spriteRIP);
        window.draw(spriteAxe);
        window.draw(spriteLog);


        window.draw(spriteBee);
        

        // ui
        window.draw(textScore);

        if(isPause)
            window.draw(textMessage);
        window.draw(timerBar);
        window.display();
    }

    return 0;
}