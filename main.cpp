#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace std;
using namespace sf;


const int screen_width = 640;
const int screen_hight = 480;

Image render;
Texture tex;
Sprite draw;
float flame_values[screen_width][screen_hight];
void initialization();
void fire_algorthim();
void render2();
void rendering();

int main()
{
    RenderWindow window(sf::VideoMode({screen_width, screen_hight}), "render_lol");
    tex.create(screen_width, screen_hight);
    render.create(screen_width, screen_hight, Color::Black);
    initialization();
    
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == Event::Closed)
            window.close();
        }
        fire_algorthim();
        render2();
        tex.update(render);
        
        window.clear();
        draw.setTexture(tex);
        window.draw(draw);
        window.display();
    }
}
void initialization()
{
    for(int i = 0; i < screen_width; i++)
    {
        flame_values[i][screen_hight - 1] = 255;
    }
}
void fire_algorthim()
{
    for(int w = screen_width - 1; w >= 0; w--)
    {
        for(int h = (screen_hight - 2); h >= 0; h--)
        {
            int pixel_down = flame_values[w][h + 1];
            //3
            int decay = rand() % 3;
            //2
            int shift = rand() % 2;
            int direction = rand() % 2;
            int direction_ = (direction == 1)? 1 : -1;
            int final_offest =  (w + (shift * direction_)); 
            if(final_offest > screen_width - 1) final_offest = (screen_width - 1);
            else if (final_offest < 0) final_offest  = 0;
            int value = pixel_down - decay;
            if (value < 0) value = 0;
            flame_values[final_offest][h] = value;
        }
    } 
}
void render2()
{
    for(int h = (screen_hight - 1); h >= 0; h--)
    {
        for(int w = screen_width - 1; w >= 0; w--)
        {
            if ((int)flame_values[w][h] > 255) flame_values[w][h] = 255;
            Color color(flame_values[w][h], 0, 0);
            render.setPixel(w, h, color);
        }
    }
}