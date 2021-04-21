#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <time.h>
#include <list>
#include <cmath>
#include <iostream>
#include <chrono>
#include <ctime>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <unistd.h>

using namespace sf;
using namespace std::chrono_literals;

int rrand(int range_min, int range_max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(range_min, range_max);
    return distrib(gen);
}

struct Constants {
    static constexpr int W = 1200;
    static constexpr int H = 800;
    static constexpr float DEGTORAD = 0.017453f;
};

class Animation
{
   public:
   float Frame, speed;
   Sprite sprite;
   std::vector<IntRect> frames;

   Animation(){}

   Animation (Texture &t, int x, int y, int w, int h, int count, float Speed)
   {
     Frame = 0;
     speed = Speed;

     for (int i=0;i<count;i++)
      frames.push_back( IntRect(x+i*w, y, w, h)  );

     sprite.setTexture(t);
     sprite.setOrigin(w/2,h/2);
     sprite.setTextureRect(frames[0]);
   }


   void update()
   {
     Frame += speed;
     int n = frames.size();
     if (Frame >= n) Frame -= n;
     if (n>0) sprite.setTextureRect( frames[int(Frame)] );
   }

   bool isEnd()
   {
     return Frame+speed>=frames.size();
   }

};


class Entity
{
   public:
   float x,y,dx,dy,R,angle;
   bool life;
   std::string name;
   Animation anim;

   Entity()
   {
     life=1;
   }

   void settings(Animation &a,int X,int Y,float Angle=0,int radius=1)
   {
     anim = a;
     x=X; y=Y;
     angle = Angle;
     R = radius;
   }

   virtual void update(){};

   void draw(RenderWindow &app)
   {
     anim.sprite.setPosition(x,y);
     anim.sprite.setRotation(angle+90);
     app.draw(anim.sprite);
   }

   virtual ~Entity(){};
};


class asteroid: public Entity
{
   public:
   asteroid()
   {
       dx=rrand(-4, 4);
       dy=rrand(-4, 4);
       name="asteroid";
   }

   void update()
   {
     x+=dx;
     y+=dy;

     if (x>Constants::W) x=0;  if (x<0) x=Constants::W;
     if (y>Constants::H) y=0;  if (y<0) y=Constants::H;
   }

};


class bullet: public Entity
{
   public:
   bullet()
   {
     name="bullet";
   }

   void  update()
   {
       dx=cos(angle*Constants::DEGTORAD)*6;
       dy=sin(angle*Constants::DEGTORAD)*6;
       angle+=rrand(-3, 4);  /*try this*/
       x+=dx;
       y+=dy;

       if (x>Constants::W || x<0 || y>Constants::H || y<0) life=0;
   }

};


class player: public Entity
{
   public:
   bool thrust;

   player()
   {
     name="player";
   }

   void update()
   {
     if (thrust)
      { dx+=cos(angle*Constants::DEGTORAD)*0.2;
        dy+=sin(angle*Constants::DEGTORAD)*0.2; }
     else
      { dx*=0.99;
        dy*=0.99; }

    int maxSpeed=15;
    float speed = sqrt(dx*dx+dy*dy);
    if (speed>maxSpeed)
     { dx *= maxSpeed/speed;
       dy *= maxSpeed/speed; }

    x+=dx;
    y+=dy;

    if (x>Constants::W) x=0; if (x<0) x=Constants::W;
    if (y>Constants::H) y=0; if (y<0) y=Constants::H;

   }

};


bool isCollide(Entity *a,Entity *b)
{
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}


int main()
{
    RenderWindow app(VideoMode(Constants::W, Constants::H), "Asteroids!");
    app.setFramerateLimit(60);

    Texture t1,t2,t3,t4,t5,t6,t7;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_red.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");

    t1.setSmooth(true);
    t2.setSmooth(true);

    Sprite background(t2);

    Animation sExplosion(t3, 0,0,256,256, 48, 0.5);
    Animation sRock(t4, 0,0,64,64, 16, 0.2);
    Animation sRock_small(t6, 0,0,64,64, 16, 0.2);
    Animation sBullet(t5, 0,0,32,64, 16, 0.8);
    Animation sPlayer(t1, 40,0,40,40, 1, 0);
    Animation sPlayer_go(t1, 40,40,40,40, 1, 0);
    Animation sExplosion_ship(t7, 0,0,192,192, 64, 0.5);


    std::list<Entity*> entities;
    int k = 100;
    int points = 0;

    for(int i=0;i<25;i++)
    {
      asteroid *a = new asteroid();
      a->settings(sRock, rrand(0, Constants::W), rrand(0, Constants::H), rrand(0, 360), 25);
      entities.push_back(a);
    }

    player *p = new player();
    p->settings(sPlayer,200,200,0,20);
    entities.push_back(p);

    /////main loop/////
    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::KeyPressed)
             if (event.key.code == Keyboard::Space)
              {
                bullet *b = new bullet();
                b->settings(sBullet,p->x,p->y,p->angle,10);
                entities.push_back(b);
              }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle+=3;
        if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle-=3;
        if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust=true;
        else p->thrust=false;


        for(auto a:entities)
            for(auto b:entities)
            {
                if (a->name=="asteroid" && b->name=="bullet")
                if ( isCollide(a,b) )
                {
                    a->life=false;
                    b->life=false;

                    points+=10;
                    std::cout << "Score: " << points << " points!" << std::endl;

                    Entity *e = new Entity();
                    e->settings(sExplosion,a->x,a->y);
                    e->name="explosion";
                    entities.push_back(e);


                    for(int i=0;i<2;i++)
                    {
                        if (a->R==15) continue;
                        Entity *e = new asteroid();
                        e->settings(sRock_small,a->x,a->y,rrand(0, 360),15);
                        entities.push_back(e);
                    }

                }

                if (a->name=="player" && b->name=="asteroid")
                    if ( isCollide(a,b) )
                        {
                            b->life=false;
                            --k;
                            if (k == 0) a->life=false;

                            Entity *e = new Entity();
                            e->settings(sExplosion_ship,a->x,a->y);
                            e->name="explosion";
                            entities.push_back(e);

                            p->settings(sPlayer,Constants::W/2,Constants::H/2,0,20);
                            p->dx=0; p->dy=0;
                        }
            }


        if (p->thrust)  p->anim = sPlayer_go;
        else   p->anim = sPlayer;


        for(auto e:entities)
            if (e->name=="explosion")
                if (e->anim.isEnd()) e->life=0;

        if (rrand(0, 150)==0)
        {
            asteroid *a = new asteroid();
            a->settings(sRock, 0,rrand(0, Constants::H), rrand(0, 360), 25);
            entities.push_back(a);
        }

        for(auto i=entities.begin();i!=entities.end();)
        {
            Entity *e = *i;

            e->update();
            e->anim.update();

            if (!e->life) {
                i=entities.erase(i);
                delete e;
            }
            else i++;
        }

        sf::Font font;
        font.loadFromFile("arial.ttf");
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cout << "Error..." << std::endl;
        }
        sf::Text text;
        text.setFont(font);
        text.setString("GAME OVER");
        text.setCharacterSize(40);
        text.setFillColor(sf::Color::Red);
        text.setStyle(sf::Text::Bold);
        text.setPosition(420, 350);

        sf::Text score;
        score.setFont(font);
        score.setString("Score: ");
        score.setCharacterSize(30);
        score.setFillColor(sf::Color::Red);
        score.setStyle(sf::Text::Bold);
        //score.setPosition(420, 350);

        sf::Text lives;
        lives.setFont(font);
        lives.setString("Life: ");
        lives.setCharacterSize(30);
        lives.setFillColor(sf::Color::Red);
        lives.setStyle(sf::Text::Bold);
        lives.setPosition(0, 30);

        sf::Text lives_num;
        lives_num.setFont(font);
        lives_num.setString(std::to_string(k));
        lives_num.setCharacterSize(30);
        lives_num.setFillColor(sf::Color::Red);
        lives_num.setStyle(sf::Text::Bold);
        lives_num.setPosition(100, 30);

        sf::Text score_num;
        score_num.setFont(font);
        score_num.setString(std::to_string(points));
        score_num.setCharacterSize(30);
        score_num.setFillColor(sf::Color::Red);
        score_num.setStyle(sf::Text::Bold);
        score_num.setPosition(100, 0);

        //////draw//////
        app.draw(background);
        for(auto i:entities) i->draw(app);
        app.draw(score);
        app.draw(score_num);
        app.draw(lives);
        app.draw(lives_num);
        if (k == 0) {
            app.draw(text);
        }
        app.display();
        if (k == 0) {
            sleep(2);
        }
    }

    return 0;
}
