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
#include "tile.cpp"
#include "tinyxml2.cpp"

using namespace tinyxml2;

Level::Level()
{

}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics): mapName(mapName), spawnPoint(spawnPoint), size(Vector2(0, 0))
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
            const char* source = pTileset->FirstChildElement("image")->Attribute("source");
            std::string path(source);
			std::stringstream ss;
			ss << "content" << path.substr(2, path.length() - 2);
            // std::cout << "Open file: " << ss.str().c_str() << '\n';
			pTileset->QueryIntAttribute("firstgid", &firstgid);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
            tilesets.push_back(Tileset(texture, firstgid));

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
                            for (int i = 0; i < tilesets.size(); ++i)
                            {
                                if (tilesets[i].FirstGid <= gid)
                                {
                                    tls = tilesets.at(i);
                                    break;
                                }
                            }

                            if (tls.FirstGid == -1)
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

                            int tilesetWidth, tilesetHeight;
                            SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
                            
                            int tsxx = gid % (tilesetWidth / tileWidth) - 1;
                            tsxx *= tileWidth;

                            int tsyy = 0;
                            int amt = (gid / (tilesetWidth / tileWidth));
                            tsyy = tileHeight * amt;

                            Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

                            Tile tile(tls.Texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
                            tileList.push_back(tile);
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
            // Other objectgroup will go here with ss.str() == "abcxyz"
            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
}

void Level::update(int elapsedTime)
{

}

void Level::draw(Graphics &graphics)
{
    for (int i = 0; i < tileList.size(); ++i)
    {
        tileList.at(i).draw(graphics);
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

const Vector2 Level::getPlayerSpawnPoint() const
{
    return spawnPoint;
}