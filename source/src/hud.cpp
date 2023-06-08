#include <string>

#include "..\header\hud.h"
#include "..\header\graphics.h"

HUD::HUD()
{

}

HUD::HUD(Graphics &graphics, Player &player): player(player)
{
    std::string source = "content/sprites/TextBox.png";
    healthBarSprite = Sprite(graphics, source, 0, 40, 64, 8, 35, 70);
    healthNumber1 = Sprite(graphics, source, 0, 56, 8, 8, 66, 70);
    currentHealthBar = Sprite(graphics, source, 0, 25, 39, 5, 83, 72);

    levelWord = Sprite(graphics, source, 81, 81, 11, 7, 38, 55);
    levelNumber = Sprite(graphics, source, 0, 56, 8, 8, 66, 52);
    expBar = Sprite(graphics, source, 0, 72, 40, 8, 83, 52);

    slash = Sprite(graphics, source, 72, 48, 8, 8, 100, 36);
    dashes = Sprite(graphics, source, 81, 51, 15, 11, 132, 26);
}

void HUD::update(int elapsedTime)
{
    healthNumber1.setSourceRectX(8 * player.getCurrentHP());
    float num = (float)player.getCurrentHP() / player.getMaxHP();
    currentHealthBar.setSourceRectW(std::floor(num * 39));
}

void HUD::draw(Graphics &graphics)
{   
    healthBarSprite.draw(graphics, healthBarSprite.getX(), healthBarSprite.getY());
    healthNumber1.draw(graphics, healthNumber1.getX(), healthNumber1.getY());
    currentHealthBar.draw(graphics, currentHealthBar.getX(), currentHealthBar.getY());

    levelWord.draw(graphics, levelWord.getX(), levelWord.getY());
    levelNumber.draw(graphics, levelNumber.getX(), levelNumber.getY());
    expBar.draw(graphics, expBar.getX(), expBar.getY());

    slash.draw(graphics, slash.getX(), slash.getY());
    dashes.draw(graphics, dashes.getX(), dashes.getY());
}