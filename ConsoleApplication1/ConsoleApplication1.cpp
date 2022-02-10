#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <cstdlib>


#define WIDTH 900
#define HEIGHT 900
#define G 667000000000
#define PI 3.1415926535898

double dT = 0.000000001;

struct Sphere {
    sf::Vector2<double> pos;
    double r;
    sf::Vector2<double> a = sf::Vector2<double>(0, 0);
    sf::Vector2<double> v = sf::Vector2<double>(0, 0);
    sf::Vector2<double> v_st = sf::Vector2<double>(0, 0);
    double m;
    sf::Vector2<double> k;
};

void sphereSpeed(Sphere* sp_1, Sphere* sp_2) {
    double dist_x = sp_1->pos.x - sp_2->pos.x;
    double dist_y = sp_1->pos.y - sp_2->pos.y;
    double dist = sqrt(dist_x * dist_x + dist_y * dist_y);

    double sin = dist_x / dist;
    double cos = dist_y / dist;

    sp_1->a.x -= (G * sp_2->m) / pow(dist, 2) * sin / pow(10, 17) * dT;
    sp_1->a.y -= (G * sp_2->m) / pow(dist, 2) * cos / pow(10, 17) * dT;

    sp_2->a.x += (G * sp_1->m) / pow(dist, 2) * sin / pow(10, 17) * dT;
    sp_2->a.y += (G * sp_1->m) / pow(dist, 2) * cos / pow(10, 17) * dT;
}

int main() {



    Sphere Earth, Moon;
    std::vector<Sphere> vecPoint;

    for (short i = 0; i < 7; i++) {
        for (short j = 0; j < 7; j++) {
            Sphere point;
            point.pos.x = WIDTH / 2 + (i - 3) * (823000) / pow(10, 5) * 2;
            point.pos.y = HEIGHT / 2 + (j - 3) * (823000) / pow(10, 5) * 2;
            point.m = 2 * pow(10, 10);
            point.r = 822000 / 2;
            vecPoint.push_back(point);
        }
    };

    vecPoint[24].m = 590 * pow(10, 22);
    vecPoint[24].r = 822000 * 2;

    //sf::Color colMoon = sf::Color(200, 0, 0);


    Earth.pos.x = WIDTH / 2;
    Earth.pos.y = HEIGHT / 2;
    Earth.r = 6371000;
    Earth.m = 597 * pow(10, 22);
    Earth.v.y = 0;

    Moon.pos.x = WIDTH / 2 - 384;
    Moon.pos.y = HEIGHT / 2;
    Moon.r = 1737100;
    Moon.m = 73500 / 5 * pow(10, 22);
    Moon.v.y = -32000000;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "AAAAAAAAAA");
    sf::CircleShape shape(0);

    sf::Texture texture;
    sf::Texture textureMoon;

    int help = 0;
    texture.loadFromFile("C:\\Users\\Xenia\\Desktop\\1200px-NASA_Earth_America_2002.jpg");
    textureMoon.loadFromFile("C:\\Users\\Xenia\\Desktop\\FullMoon2010.jpg");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        Moon.pos += Moon.v * (dT * 100);
        Moon.a = sf::Vector2<double>(0, 0);

       /* if (help == 100) {
            dT = 0.000000002;
        }*/

        for (short i = 0; i < 49; i++) {
            if (i != 24) {
                double dist_x = vecPoint[i].pos.x - vecPoint[24].pos.x;
                double dist_y = vecPoint[i].pos.y - vecPoint[24].pos.y;
                double dist = sqrt(dist_x * dist_x + dist_y * dist_y);
                double sin = dist_x / dist;
                double cos = dist_y / dist;
                vecPoint[i].v_st = sf::Vector2<double>(-30 * 6 * sqrt(G * vecPoint[2].m * (dist)) * cos, 30 * 6 * sqrt(G * vecPoint[2].m * (dist)) * sin);
                vecPoint[i].a = sf::Vector2<double>(0, 0);
                
                vecPoint[i].pos = vecPoint[i].pos + vecPoint[i].v * dT + vecPoint[i].v_st * dT * dT * 1750.0;
            }
            else {
                vecPoint[i].a = sf::Vector2<double>(0, 0);
                vecPoint[i].pos = sf::Vector2<double>(WIDTH / 2, HEIGHT / 2);
            }
        }

        for (short l = 0; l < 49; l++) {
            int i = l;
            if (i >= 25) {
                i -= 25;
            }
            else {
                i += 24;
            }
            for (short k = l + 1; k < 49; k++) {
                int j = k;
                if (j >= 25) {
                    j -= 25;
                }
                else {
                    j += 24;
                }
                double dist_x = vecPoint[i].pos.x - vecPoint[j].pos.x;
                double dist_y = vecPoint[i].pos.y - vecPoint[j].pos.y;
                double dist = sqrt(dist_x * dist_x + dist_y * dist_y);
                double sin = dist_x / dist;
                double cos = dist_y / dist;
                if (dist < vecPoint[i].r / pow(10, 5) + vecPoint[j].r / pow(10, 5)) {
                    vecPoint[j].pos.x -= (vecPoint[i].r / pow(10, 5) + vecPoint[j].r / pow(10, 5) - dist) * sin;
                    vecPoint[j].pos.y -= (vecPoint[i].r / pow(10, 5) + vecPoint[j].r / pow(10, 5) - dist) * cos;
                }
            }
        }

        for (int i = 0; i < 49; ++i) {
            double dist_x = (vecPoint[i].pos.x - Moon.pos.x);
            double dist_y = (vecPoint[i].pos.y - Moon.pos.y);
            double dist = sqrt(dist_x * dist_x + dist_y * dist_y);

            double sin = dist_x / dist;
            double cos = dist_y / dist;

            vecPoint[i].a.x -= (G * Moon.m) / pow(dist, 2) * sin / pow(10, 17) * dT;
            vecPoint[i].a.y -= (G * Moon.m) / pow(dist, 2) * cos / pow(10, 17) * dT;

            Moon.a.x += (G * vecPoint[i].m) / pow(dist, 2) * sin / pow(10, 17) * dT;
            Moon.a.y += (G * vecPoint[i].m) / pow(dist, 2) * cos / pow(10, 17) * dT;
        }

        for (short i = 0; i < 49; i++) {
            for (short j = i + 1; j < 49; j++) {
                sphereSpeed(&vecPoint[i], &vecPoint[j]);
            }
        }

        Moon.v += Moon.a;

        for (short i = 0; i < 49; i++) {
            vecPoint[i].v = vecPoint[i].v + vecPoint[i].a;
        }

        for (short i = 0; i < 49; i++) {
            for (short j = i + 1; j < 49; j++) {
                double dist_x = vecPoint[i].pos.x - vecPoint[j].pos.x;
                double dist_y = vecPoint[i].pos.y - vecPoint[j].pos.y;
                double dist = sqrt(dist_x * dist_x + dist_y * dist_y);
                double sin = dist_x / dist;
                double cos = dist_y / dist;
                double dist_vx = vecPoint[i].pos.x + vecPoint[i].v.x * dT * 0.5 - vecPoint[j].pos.x - vecPoint[j].v.x * dT;
                double dist_vy = vecPoint[i].pos.y + vecPoint[i].v.y * dT * 0.5 - vecPoint[j].pos.y - vecPoint[j].v.y * dT;
                double dist_v = sqrt(dist_vx * dist_vx + dist_vy * dist_vy);

                if (dist_v < vecPoint[i].r / pow(10, 5) + vecPoint[j].r / pow(10, 5)) {
                    double Vn1 = vecPoint[i].v.x * sin + vecPoint[i].v.y * cos;
                    double Vn2 = vecPoint[j].v.x * sin + vecPoint[j].v.y * cos;
                    double Vt1 = -vecPoint[i].v.x * cos + vecPoint[i].v.y * sin;
                    double Vt2 = -vecPoint[j].v.x * cos + vecPoint[j].v.y * sin;


                    double o = Vn2;
                    Vn2 = Vn1;
                    Vn1 = o;


                    vecPoint[j].v.x = Vn2 * sin * 0.8 - Vt2 * cos;
                    vecPoint[j].v.y = Vn2 * cos * 0.8 + Vt2 * sin;
                    vecPoint[i].v.x = Vn1 * sin * 0.8 - Vt1 * cos;
                    vecPoint[i].v.y = Vn1 * cos * 0.8 + Vt1 * sin;
                }
            }
            if (help > 0) {
                if (vecPoint[i].v.x * dT > 10 || vecPoint[i].v.y * dT > 10 || vecPoint[i].v.x * dT < -10 || vecPoint[i].v.y * dT < -10) {
                    std::cout << i << " " << help << " " << vecPoint[i].v.x * dT << '\n';
                }
            }
        }

        for (short l = 0; l < 49; l++) {
            int i = l;
            if (i >= 25) {
                i -= 25;
            }
            else {
                i += 24;
            }
            for (short k = l + 1; k < 49; k++) {
                int j = k;
                if (j >= 25) {
                    j -= 25;
                }
                else {
                    j += 24;
                }
                double dist_x = vecPoint[i].pos.x - vecPoint[j].pos.x;
                double dist_y = vecPoint[i].pos.y - vecPoint[j].pos.y;
                double dist = sqrt(dist_x * dist_x + dist_y * dist_y);
                double sin = dist_x / dist;
                double cos = dist_y / dist;
                if (dist < vecPoint[i].r / pow(10, 5) + vecPoint[j].r / pow(10, 5)) {
                    vecPoint[j].pos.x -= (vecPoint[i].r / pow(10, 5) + vecPoint[j].r / pow(10, 5) - dist) * sin;
                    vecPoint[j].pos.y -= (vecPoint[i].r / pow(10, 5) + vecPoint[j].r / pow(10, 5) - dist) * cos;
                }
            }
        }


     
        window.clear();


        shape.setRadius(Moon.r / pow(10, 5));
        shape.setOrigin(Moon.r / pow(10, 5), Moon.r / pow(10, 5));
        shape.setPosition(Moon.pos.x, Moon.pos.y);
        //shape.setFillColor(colMoon);
        shape.setTexture(&textureMoon);
        textureMoon.setSmooth(true);
        //shape.setTextureRect(sf::IntRect(100, 300, 100, 100));
        window.draw(shape);

        for (short i = 0; i < 7; i++) {
            for (short j = 0; j < 7; j++) {
 //               sf::Color colMoon = sf::Color(0, 0, 200);
                //shape.setFillColor(colMoon);
                if (7 * i + j == 24) {
//                    sf::Color colMoon = sf::Color(0, 200, 0);
                    //shape.setFillColor(colMoon);
                }
                shape.setTexture(&texture);
                textureMoon.setSmooth(true);
                shape.setRadius(vecPoint[7 * i + j].r / pow(10, 5));
                shape.setOrigin(vecPoint[7 * i + j].r / pow(10, 5), vecPoint[7 * i + j].r / pow(10, 5));
                shape.setPosition(vecPoint[7 * i + j].pos.x, vecPoint[7 * i + j].pos.y);
                window.draw(shape);
            }
        }


        window.display();
        help++;
        sf::sleep(sf::milliseconds(int(1000 / 30)));
    }

    return 0;
}
