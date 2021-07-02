#include <SFML/Graphics.hpp>
#include <Windows.h>


class Bird
{
public:

    float x = 50.0f;
    float y = 200.0f;
    float r = 20.0f;
    float jumpForce = 12.0f;
    float gravity = 0.6f;
    float velocity = 0.0f;
    sf::CircleShape bird;

    void show() {
        bird.setPosition(sf::Vector2f(this->x, this->y));
        bird.setRadius(this->r/2);
        bird.setFillColor(sf::Color::White);
    }
    void update() {
        this->velocity += this->gravity;
        this->velocity *= 0.9f;
        this->y += this->velocity;
    }
    void jump() {
        this->velocity -= this->jumpForce;
    }

    Bird()
    {
    }
    ~Bird()
    {
    }

private:

};

class Pipe
{
public:
 
    float x = 400.0f;
    float y = ((rand() % 300) * -1) - 90;
    float w = 20.0f;
    float h = 400.0f;
    sf::RectangleShape pipe_1, pipe_2;

    void show() {
        pipe_1.setSize(sf::Vector2f(this->w, this->h));
        pipe_1.setPosition(sf::Vector2f(this->x, this->y));
        pipe_1.setFillColor(sf::Color::White);
        pipe_2.setSize(sf::Vector2f(this->w, this->h));
        pipe_2.setPosition(sf::Vector2f(this->x, this->y + 480));
        pipe_2.setFillColor(sf::Color::White);
    }
    void update() {
        this->x--;
    }

    Pipe()
    {
    }
    ~Pipe()
    {
    }

private:

};


int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Flappy Bird");
    window.setKeyRepeatEnabled(false);

    Bird bird;
    std::vector<Pipe> pipes;
    pipes.push_back(Pipe());

    sf::Text score;
    sf::Font arialFont;
    arialFont.loadFromFile("arial.ttf");
    score.setFont(arialFont);
    score.setPosition(sf::Vector2f(20, 20));
    score.setCharacterSize(20);
    score.setFillColor(sf::Color::Black);


    int scoreCount = 0; // 1000000000 // 100
    int frameCount = 1;
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space)
                {
                    bird.jump();
                }
            }
        }


        window.clear(sf::Color::Red);

        bird.update();
        bird.show();
        window.draw(bird.bird);
        

        if (bird.y <= 0 || bird.y + bird.r >= 400)
        {
            bird.y = 200.0f;
            pipes.clear();
            scoreCount = 0;
        }
        

        for (int i = 0; i < pipes.size(); i++)
        {
            pipes[i].update();
            pipes[i].show();
            window.draw(pipes[i].pipe_1);
            window.draw(pipes[i].pipe_2);
            if ((bird.x + bird.r >= pipes[i].x && bird.x <= pipes[i].x + pipes[i].w) && ((bird.y <= pipes[i].y + pipes[i].h) || (bird.y + bird.r >= pipes[i].y + 480)))
            {
                bird.y = 200.0f;
                pipes.clear();
                scoreCount = 0;
                break;
            }
        }
        for (int i = 0; i < pipes.size(); i++)
        {
            if (pipes[i].x <= -100)
            {
                pipes.erase(pipes.begin());
            }
            if (bird.x == pipes[i].x)
            {
                scoreCount++;
            }
        }
        if (frameCount % 100 == 0)
        {
            pipes.push_back(Pipe());
            frameCount = 1;
        }


        score.setString(std::to_string(scoreCount));
        window.draw(score);
        
        window.display();

        frameCount++;
        Sleep(10);
    }

    return 0;
}