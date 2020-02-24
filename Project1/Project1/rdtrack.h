#pragma once
#include<SFML\Graphics.hpp>

class roadtrack
{
public:


     static void drawQuad(sf::RenderWindow& w, sf::Color c, int x1, int y1, int w1, int x2, int y2, int w2)
    {
        sf::ConvexShape shape(4);
        shape.setFillColor(c);
        shape.setPoint(0, sf::Vector2f(x1 - w1, y1));
        shape.setPoint(1, sf::Vector2f(x2 - w2, y2));
        shape.setPoint(2, sf::Vector2f(x2 + w2, y2));
        shape.setPoint(3, sf::Vector2f(x1 + w1, y1));
        w.draw(shape);
    }

};
class Line
{
private:
    int width = 1920, height = 1080;
    int roadW = 2000;
    int segL = 200; //segment length
    float camD = 0.84; //camera depth


    public:
    float x, y, z; //3d center of line
    float X, Y, W; //screen coord
    float scale=0;
    float curve; 
    //Sprite sprite;

    Line()
    {
     
           curve= x = y = z = 0;
    }

    void project(int camX, int camY, int camZ)
    {
        scale = camD / (z-camZ);
        X = (1 + scale * (x - camX)) * width / 2;
        Y = (1 - scale * (y - camY)) * height / 2;
        W = scale *roadW * width / 2;
    }
};