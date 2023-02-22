#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

class GameScene;

// G A M E 
class Game
{
public:
    bool isGameEnded = false;
    bool isXWinner = false;
    bool isOWinner = false;

    bool isXTap = true;
    int table[3][3];
public:
    Game()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                SetCage(i, j, 0);
                //table[i][j] = 0;
            }
        }
    };
    void DoTap(int x, int y)
    {
        if (isXTap)
        {
            DoX(x, y);
        }
        else
        {
            DoO(x, y);
        }
        ChangeTap();
    }
    void DoO(int x, int y)
    {
        SetCage(x, y, -1);
        //table[y][x] = -1;
    }
    void DoX(int x, int y)
    {
        SetCage(x, y, 1);
        //table[y][x] = 1;
    }
    void CheckWinO()
    {
        for (int i = 0; i < 3; i++)
        {
            if (GetCage(0, i) == -1 && GetCage(1, i) == -1 && GetCage(2, i) == -1)
            {
                isGameEnded = true;
                isOWinner = true;
            }
            if (GetCage(i, 0) == -1 && GetCage(i, 1) == -1 && GetCage(i, 2) == -1)
            {
                isGameEnded = true;
                isOWinner = true;
            }
        }
        if (GetCage(0, 0) == -1 && GetCage(1, 1) == -1 && GetCage(2, 2) == -1)
        {
            isGameEnded = true;
            isOWinner = true;
        }
        if (GetCage(0, 2) == -1 && GetCage(1, 1) == -1 && GetCage(2, 0) == -1)
        {
            isGameEnded = true;
            isOWinner = true;
        }
    }
    void CheckWinX()
    {
        for (int i = 0; i < 3; i++)
        {
            if (GetCage(0, i) == 1 && GetCage(1, i) == 1 && GetCage(2, i) == 1)
            {
                isGameEnded = true;
                isXWinner = true;
            }
            if (GetCage(i, 0) == 1 && GetCage(i, 1) == 1 && GetCage(i, 2) == 1)
            {
                isGameEnded = true;
                isXWinner = true;
            }
        }
        if (GetCage(0, 0) == 1 && GetCage(1, 1) == 1 && GetCage(2, 2) == 1)
        {
            isGameEnded = true;
            isXWinner = true;
        }
        if (GetCage(0, 2) == 1 && GetCage(1, 1) == 1 && GetCage(2, 0) == 1)
        {
            isGameEnded = true;
            isXWinner = true;
        }
    }
    int GetCage(int x, int y)
    {
        return table[y][x];
    }
    void SetCage(int x, int y, int val)
    {
        table[y][x] = val;
    }
    bool GetisXTap()
    {
        return isXTap;
    }
    void Restart()
    {
        isXTap = true;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                SetCage(i, j, 0);
                //table[i][j] = 0;
            }
        }
    }
    void ChangeTap()
    {
        if (isXTap)
        {
            isXTap = false;
        }
        else
        {
            isXTap = true;
        }
    }
    void Info()
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << table[i][j];
            }
            cout << endl;
        }
    }
};
// G A M E

// G A M E  B U T T O N
class GameButton
{
private:
    bool active;

    int x;
    int y;

    int coordinateX;
    int coordinateY;

    int length;
    int width;

    Texture textureX;
    Sprite spriteX;

    Texture textureO;
    Sprite spriteO;
public:
    GameButton() = default;
    GameButton(int Ix, int Iy)
    {
        active = true;
        textureX.loadFromFile("XO.png", IntRect(0,0,112,112));
        spriteX.setTexture(textureX);
        textureO.loadFromFile("XO.png", IntRect(112, 0, 112, 112));
        spriteO.setTexture(textureO);
        coordinateX = Ix;
        coordinateY = Iy;
        length = 112;
        width = 112;
        x = 111 + 133 * coordinateX;
        y = 111 + 133 * coordinateY;
        spriteX.setPosition((float)x, (float)y);
        spriteO.setPosition((float)x, (float)y);

    }
    void Check(RenderWindow& window, Game& game)
    {
        if (Mouse::isButtonPressed(Mouse::Left) && (Mouse::getPosition(window).x > x && Mouse::getPosition(window).x < x + length) && (Mouse::getPosition(window).y > y && Mouse::getPosition(window).y < y + width))
        {
            DoEvent(window, game);
        }
    };
    void DoEvent(RenderWindow &window, Game& game)
    {
        if (active)
        {
            game.DoTap(coordinateX, coordinateY);
            game.Info();
            active = false;
            cout << coordinateX << " " << coordinateY << endl;
        }
    }
    void Show(RenderWindow& window, Game& game)
    {
        if (!active)
        {
            if (game.GetCage(coordinateX, coordinateY) == 1)
            {
                window.draw(spriteX);
            }
            else if (game.GetCage(coordinateX, coordinateY) == -1)
            {
                window.draw(spriteO);
            }
        }
    }
    void ChangeActive()
    {
        active = true;
    }
};
// G A M E  B U T T O N

// G A M E  T A B L E
class GameTable
{
public:
    bool active;

    Game* game;

    GameButton gb00 = GameButton(0, 0);
    GameButton gb01 = GameButton(0, 1);
    GameButton gb02 = GameButton(0, 2);
    GameButton gb10 = GameButton(1, 0);
    GameButton gb11 = GameButton(1, 1);
    GameButton gb12 = GameButton(1, 2);
    GameButton gb20 = GameButton(2, 0);
    GameButton gb21 = GameButton(2, 1);
    GameButton gb22 = GameButton(2, 2);
public:
    GameTable() = default;
    GameTable(bool IActive, Game* Igame)
    {
        game = Igame;
        active = IActive;
    }
    void Check(RenderWindow& window, Game& game)
    {
        if (active)
        {
            gb00.Check(window, game);
            gb01.Check(window, game);
            gb02.Check(window, game);

            gb10.Check(window, game);
            gb11.Check(window, game);
            gb12.Check(window, game);

            gb20.Check(window, game);
            gb21.Check(window, game);
            gb22.Check(window, game);
        }
    }
    void Show(RenderWindow& window, Game& game)
    {
        if (active)
        {
            gb00.Show(window, game);
            gb01.Show(window, game);
            gb02.Show(window, game);
            gb10.Show(window, game);
            gb11.Show(window, game);
            gb12.Show(window, game);
            gb20.Show(window, game);
            gb21.Show(window, game);
            gb22.Show(window, game);
        }
    }
    void ChangeButtonActives()
    {
        gb00.ChangeActive();
        gb01.ChangeActive();
        gb02.ChangeActive();
        gb10.ChangeActive();
        gb11.ChangeActive();
        gb12.ChangeActive();
        gb20.ChangeActive();
        gb21.ChangeActive();
        gb22.ChangeActive();
    }
    void ChangeActive()
    {
        if (active)
        {
            active = false;
        }
        else
        {
            active = true;
        }
    }
    void Restart()
    {
        active = true;
    }
};
// G A M E  T A B L E

// A I
class AI
{
private:
public:
};
// A I

// B U T T O N
class Button
{
public:
    string name;

    int x;
    int y;

    int length;
    int width;
    Button() = default;
    bool Check(RenderWindow& window, Event& event)
    {
        if ((event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) && (Mouse::getPosition(window).x > x && Mouse::getPosition(window).x < x + length) && (Mouse::getPosition(window).y > y && Mouse::getPosition(window).y < y + width))
        {
            return true;
        }
        return false;
    };
    virtual void DoEvent(GameScene& activeScene, GameScene& notActiveScene, GameTable& gameTable) {};
};
// B U T T O N

// G A M E  S C E N E
class GameScene
{
private:
    bool active;
    Texture texture;
    Sprite sprite;
    Button* button1;
    Button* button2;

    
public:
    GameScene() = default;
    GameScene(string file, Button& IButton1, Button& IButton2, bool IActive)
    {
        active = IActive;
        texture.loadFromFile(file);
        sprite.setTexture(texture);
        button1 = &IButton1;
        button2 = &IButton2;
    }
    void SetTexture(string file)
    {
        texture.loadFromFile(file);
        sprite.setTexture(texture);
    }
    void Show(RenderWindow& window)
    {
        if (active)
        {
            window.draw(sprite);
        }
    }
    void Check(RenderWindow& window, GameScene& notActiveScene, GameTable& gameTable, Event& event)
    {
        if (active)
        {
            if (button1->Check(window, event))
            {
                button1->DoEvent(*this, notActiveScene, gameTable);
            }
            if (button2->Check(window, event))
            {
                button2->DoEvent(*this, notActiveScene, gameTable);
            }
        }
    }
    void ChangeActive()
    {
        if (active)
        {
            active = false;
        }
        else
        {
            active = true;
        }
    }
};
// G A M E  S C E N E

// Q U I T  B U T T O N
class QuitButton : public Button
{
public:
    QuitButton() = default;
    QuitButton(string Iname, int Ix, int Iy, int Ilength, int Iwidth)
    {
        name = Iname;
        x = Ix;
        y = Iy;
        length = Ilength;
        width = Iwidth;
    }
    void DoEvent(GameScene& activeScene, GameScene& notActiveScene, GameTable& gameTable)
    {
        exit(0);
    }
};
// Q U I T  B U T T O N

// N E W  G A M E  B U T T O N
class NewGameButton : public Button
{
public:
    NewGameButton() = default;
    NewGameButton(string Iname, int Ix, int Iy, int Ilength, int Iwidth)
    {
        name = Iname;
        x = Ix;
        y = Iy;
        length = Ilength;
        width = Iwidth;
    }
    void DoEvent(GameScene& activeScene, GameScene& notActiveScene, GameTable& gameTable)
    {
        gameTable.game->Restart();
        gameTable.ChangeButtonActives();
        gameTable.Restart();
        activeScene.ChangeActive();
        notActiveScene.ChangeActive();
    }
};
// N E W  G A M E  B U T T O N

// R E S T A R T  B U T T O N
class RestartButton : public Button
{
public:
    RestartButton() = default;
    RestartButton(string Iname, int Ix, int Iy, int Ilength, int Iwidth)
    {
        name = Iname;
        x = Ix;
        y = Iy;
        length = Ilength;
        width = Iwidth;
    }
    void DoEvent(GameScene& activeScene, GameScene& notActiveScene, GameTable& gameTable)
    {
        gameTable.game->Restart();
        //gameTable.ChangeActive();
        gameTable.Restart();
        gameTable.ChangeButtonActives();
        cout << "RESTART" << endl;
    }
};
// R E S T A R T  B U T T O N

// M E N U  B U T T O N
class MenuButton : public Button
{
public:
    MenuButton() = default;
    MenuButton(string Iname, int Ix, int Iy, int Ilength, int Iwidth)
    {
        name = Iname;
        x = Ix;
        y = Iy;
        length = Ilength;
        width = Iwidth;
    }
    void DoEvent(GameScene& activeScene, GameScene& notActiveScene, GameTable& gameTable)
    {
        activeScene.ChangeActive();
        notActiveScene.ChangeActive();
        gameTable.ChangeActive();
    }
};
// M E N U  B U T T O N




// M A I N
int main()
{
    RenderWindow window(VideoMode(600, 1000), "TIC TAC TOE",Style::Close);

    NewGameButton newGameButton("New Game", 108, 360, 384, 112);
    QuitButton quitButton("Quit", 172, 550, 256, 112);
    MenuButton menuButton("Menu", 172, 800, 256, 112);
    RestartButton restartButton("Restart", 140, 650, 320, 112);

    GameScene menu("MenuBackGround.png", newGameButton, quitButton, true);
    GameScene game("GameBackGround.png", menuButton, restartButton, false);

    Game gameT;
    gameT.Info();

    sf::Music music;
    if (!music.openFromFile("gambit.wav"))
        return -1;
    music.setLoop(true);
    music.play();

    GameTable gameTable(false, &gameT);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        menu.Check(window, game, gameTable, event);
        game.Check(window, menu, gameTable, event);

        gameTable.Check(window,gameT);
        menu.Show(window);
        game.Show(window);
        gameTable.Show(window, gameT);

        window.display();
    }

    return 0;
}