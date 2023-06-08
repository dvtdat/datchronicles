#include <SDL2/SDL.h>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>

#include "..\header\level.h"
#include "..\header\global.h"
#include "..\header\graphics.h"
#include "..\header\tile.h"
#include "..\header\animatedtile.h"
#include "..\header\utils.h"
#include "tile.cpp"
#include "animatedtile.cpp"
#include "tinyxml2.cpp"

using namespace tinyxml2;

Level::Level()
{

}

Level::Level(std::string mapName, Graphics &graphics): mapName(mapName), size(Vector2(0, 0))
{
    loadMap(mapName, graphics);
}

Level::~Level()
{

}

void Level::loadMap(std::string mapName, Graphics &graphics)
{
    XMLDocument doc;
    std::stringstream ss;
    ss << "content/maps/" << mapName << ".tmx";
    // std::cout << "Open file: " << ss.str().c_str() << '\n';
    doc.LoadFile(ss.str().c_str());

    XMLElement* mapNode = doc.FirstChildElement("map");

    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("heigth", &height);
    size = Vector2(width, height);

    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);
    tileSize = Vector2(tileWidth, tileHeight);

    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if (pTileset != nullptr)
    {
        while(pTileset)
        {
            int firstgid;
            pTileset->QueryIntAttribute("firstgid", &firstgid);

            if (pTileset->FirstChildElement("image") != nullptr)
            {
                const char* source = pTileset->FirstChildElement("image")->Attribute("source");
                std::string path(source);
                std::stringstream ss;
                ss << "content" << path.substr(2, path.length() - 2);
                // std::cout << "Open file: " << ss.str().c_str() << '\n';

                SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
                tilesets.push_back(Tileset(texture, firstgid));
            }

            if (pTileset->Attribute("source") != nullptr)
            {
                const char* animationSource = pTileset->Attribute("source");
                std::string path(animationSource);
                std::stringstream ss;
                ss << "content" << path.substr(2, path.length() - 2);
                // std::cout << "Open file: " << ss.str().c_str() << '\n';

                XMLDocument tmpDoc;
                tmpDoc.LoadFile(ss.str().c_str());

                const char* source = tmpDoc.FirstChildElement("tileset")->FirstChildElement("image")->Attribute("source");
                std::string imagePath(source);
                std::stringstream imageSS;
                imageSS << "content/tilesets/" << imagePath;
                SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(imageSS.str()));
                tilesets.push_back(Tileset(texture, firstgid));
                // std::cout << "Open file: " << imageSS.str().c_str() << '\n';
                
                XMLElement* pTileA = tmpDoc.FirstChildElement("tileset")->FirstChildElement("tile");
                if (pTileA != nullptr)
                {
                    while (pTileA)
                    {
                        AnimatedTileInfo ati;
                        ati.startTileID = pTileA->IntAttribute("id") + firstgid;
                        ati.tilesetsFirstGid = firstgid;
                        XMLElement* pAnimation = pTileA->FirstChildElement("animation");
                        if (pAnimation != nullptr)
                        {
                            while (pAnimation)
                            {
                                XMLElement* pFrame = pAnimation->FirstChildElement("frame");
                                if (pFrame != nullptr)
                                {
                                    while (pFrame)
                                    {
                                        ati.tileIDs.push_back(pFrame->IntAttribute("tileid") + firstgid);
                                        ati.duration = pFrame->IntAttribute("duration");
                                        pFrame = pFrame->NextSiblingElement("frame");
                                    }
                                }
                                pAnimation = pAnimation->NextSiblingElement("animation");
                            }
                        }
                        animatedTileInfoList.push_back(ati);
                        pTileA = pTileA->NextSiblingElement("tile");
                    }
                }
            }
            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }

    XMLElement* pLayer = mapNode->FirstChildElement("layer");
    if (pLayer != nullptr)
    {
        while (pLayer)
        {
            XMLElement* pData = pLayer->FirstChildElement("data");
            if (pData != nullptr)
            {
                while (pData)
                {
                    XMLElement* pTile = pData->FirstChildElement("tile");
                    if (pTile != nullptr)
                    {
                        int tileCnt = 0;
                        while (pTile)
                        {
                            if (pTile->IntAttribute("gid") == 0)
                            {
                                tileCnt++;
                                if (pTile->NextSiblingElement("tile"))
                                {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                }
                                else break;
                            }

                            int gid = pTile->IntAttribute("gid");
                            Tileset tls;
                            int closest = 0;
                            for (int i = 0; i < tilesets.size(); ++i)
                            {
                                if (tilesets[i].firstGid <= gid)
                                {
                                    if (tilesets[i].firstGid > closest)
                                    {
                                        closest = tilesets[i].firstGid;
                                        tls = tilesets.at(i);
                                    }
                                }
                            }

                            if (tls.firstGid == -1)
                            {
                                tileCnt++;
                                if (pTile->NextSiblingElement("tile"))
                                {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                }
                                else break;
                            }

                            int xx = 0;
                            int yy = 0;
                            xx = tileCnt % width;
                            xx *= tileWidth;
                            yy += tileHeight * (tileCnt / width);
                            Vector2 finalTilePosition = Vector2(xx, yy);
                            Vector2 finalTilesetPosition = getTilesetPosition(tls, gid, tileWidth, tileHeight);

                            bool isAnimatedTile = false;
                            AnimatedTileInfo ati;
                            for (int i = 0; i < animatedTileInfoList.size(); ++i)
                            {
                                if (animatedTileInfoList.at(i).startTileID == gid)
                                {
                                    ati = animatedTileInfoList.at(i);
                                    isAnimatedTile = true;
                                    break;
                                }
                            }

                            if (isAnimatedTile)
                            {
                                std::vector<Vector2> tilesetPositions;
                                for (int i = 0; i < ati.tileIDs.size(); ++i)
                                {
                                    tilesetPositions.push_back(getTilesetPosition(tls, ati.tileIDs.at(i), tileWidth, tileHeight));
                                }
                                AnimatedTile tile(tilesetPositions, ati.duration, tls.texture, Vector2(tileWidth, tileHeight), finalTilePosition);
                                animatedTileList.push_back(tile);    
                            }
                            else
                            {
                                Tile tile(tls.texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
                                tileList.push_back(tile);
                            }
                            tileCnt++;
                            pTile = pTile->NextSiblingElement("tile");
                        } 
                    }
                    pData = pData->NextSiblingElement("data");
                }
            }
            pLayer = pLayer->NextSiblingElement("layer");
        }
    }

    XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if (pObjectGroup != nullptr)
    {
        while (pObjectGroup)
        {
            const char* name = pObjectGroup->Attribute("name");
            std::stringstream ss;
            ss << name;
            if (ss.str() == "Collisions")
            {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != nullptr)
                {
                    while (pObject)
                    {
                        float x, y, width, height;
                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        width = pObject->FloatAttribute("width");
                        height = pObject->FloatAttribute("height");

                        Rectangle tmpRect(  std::ceil(x) * globals::SPRITE_SCALE,
                                            std::ceil(y) * globals::SPRITE_SCALE,
                                            std::ceil(width) * globals::SPRITE_SCALE,
                                            std::ceil(height) * globals::SPRITE_SCALE );
                                            
                        collisionRects.push_back(Rectangle( std::ceil(x) * globals::SPRITE_SCALE,
                                                            std::ceil(y) * globals::SPRITE_SCALE,
                                                            std::ceil(width) * globals::SPRITE_SCALE,
                                                            std::ceil(height) * globals::SPRITE_SCALE));

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            
            if (ss.str() == "Spawnpoint")
            {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != nullptr)
                {
                    while (pObject)
                    {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        const char* name = pObject->Attribute("name");
                        std::stringstream ss;
                        ss << name;
                        if (ss.str() == "Player")
                        {
                            spawnPoint = Vector2(std::ceil(x) * globals::SPRITE_SCALE, std::ceil(y) * globals::SPRITE_SCALE);
                        }

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }

            if (ss.str() == "Slopes")
            {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != nullptr)
                {
                    while (pObject)
                    {
                        std::vector<Vector2> points;
                        Vector2 p1;
                        p1 = Vector2(std::ceil(pObject->FloatAttribute("x")), std::ceil(pObject->FloatAttribute("y")));

                        XMLElement* pPolyline = pObject->FirstChildElement("polyline");
                        if (pPolyline != nullptr)
                        {
                            std::vector<std::string> pairs;
                            const char* pointString = pPolyline->Attribute("points");

                            std::stringstream ss;
                            ss << pointString;
                            Utils::split(ss.str(), pairs, ' ');

                            for (int i = 0; i < pairs.size(); ++i)
                            {
                                std::vector<std::string> ps;
                                Utils::split(pairs.at(i), ps, ',');
                                points.push_back(Vector2(std::stoi(ps.at(0)), std::stoi(ps.at(1))));
                            }
                        }

                        for (int i = 0; i < points.size() - 1; i++)
                        {
                            slopes.push_back(Slope( Vector2((p1.x + points.at(i).x) * globals::SPRITE_SCALE, 
                                                            (p1.y + points.at(i).y) * globals::SPRITE_SCALE),
                                                    Vector2((p1.x + points.at(i + 1).x) * globals::SPRITE_SCALE, 
                                                            (p1.y + points.at(i + 1).y) * globals::SPRITE_SCALE)));
                        }

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }

            if (ss.str() == "Door")
            {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");
                if (pObject != nullptr)
                {
                    while (pObject)
                    {
                        float x = pObject->FloatAttribute("x");
                        float y = pObject->FloatAttribute("y");
                        float w = pObject->FloatAttribute("width");
                        float h = pObject->FloatAttribute("height");

                        Rectangle rect = Rectangle(x, y, w, h);

                        XMLElement* pProperties = pObject->FirstChildElement("properties");
                        if (pProperties != nullptr)
                        {
                            while (pProperties)
                            {
                                XMLElement* pProperty = pProperties->FirstChildElement("property");
                                if (pProperty != nullptr)
                                {
                                    while (pProperty)
                                    {
                                        const char* name = pProperty->Attribute("name");
                                        std::stringstream ss;
                                        ss << name;
                                        if (ss.str() == "destination")
                                        {
                                            const char* value = pProperty->Attribute("value");
                                            std::stringstream ss2;
                                            ss2 << value;
                                            Door door = Door(rect, ss2.str());
                                            doorList.push_back(door);
                                        }   
                                        pProperty = pProperty->NextSiblingElement("property");
                                    }
                                }
                                pProperties = pProperties->NextSiblingElement("properties");
                            }
                        }

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }

            // Other objectgroup will go here with ss.str() == "abcxyz"
            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
}

Vector2 Level::getTilesetPosition(Tileset tls, int gid, int tileWidth, int tileHeight)
{
    int tilesetWidth, tilesetHeight;
    SDL_QueryTexture(tls.texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
    
    int tsxx = gid % (tilesetWidth / tileWidth) - 1;
    tsxx *= tileWidth;

    int tsyy = 0;
    int amt = ((gid - tls.firstGid) / (tilesetWidth / tileWidth)); 
    tsyy = tileHeight * amt;
    // (gid - tls.firstGid) as account for different first gid index of different tilesets
    return Vector2(tsxx, tsyy);
}

void Level::update(int elapsedTime)
{
    for (int i = 0; i < animatedTileList.size(); ++i)
    {
        animatedTileList.at(i).update(elapsedTime);
    }
}

void Level::draw(Graphics &graphics)
{
    for (int i = 0; i < tileList.size(); ++i)
    {
        tileList.at(i).draw(graphics);
    }
    for (int i = 0; i < animatedTileList.size(); ++i)
    {
        animatedTileList.at(i).draw(graphics);
    }
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &other)
{
    std::vector<Rectangle> others;
    for (int i = 0; i < collisionRects.size(); ++i)
    {
        if (collisionRects.at(i).collidesWith(other))
        {
            others.push_back(collisionRects.at(i));
        }
    }

    return others;
}

std::vector<Slope> Level::checkSlopeCollisions(const Rectangle &other)
{
    std::vector<Slope> others;
    for (int i = 0; i < slopes.size(); ++i)
    {
        if (slopes.at(i).collidesWith(other))
        {
            others.push_back(slopes.at(i));
        }
    }
    return others;
}

std::vector<Door> Level::checkDoorCollisions(const Rectangle &other)
{
    std::vector<Door> others;
    for (int i = 0; i < doorList.size(); ++i)
    {
        if (doorList.at(i).collidesWith(other))
        {
            others.push_back(doorList.at(i));
        }
    }
    return others;
}

const Vector2 Level::getPlayerSpawnPoint() const
{
    return spawnPoint;
}