#include "Raylib/include/raylib.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "Math.h"
#include <iostream>

using namespace std;

class Player;
class Enemy;

struct Bullet {
    float x;
    float y;
    float r;
    float v;
    float help = 2;
    Vector2D dir;
    int myParent;
    int ID;
    bool IsUsed = false;

    Bullet(int myParent, float x, float y, int r, float v, Vector2D dir, int ID)
    : myParent(myParent), x(x), y(y), r(r), v(v), dir(dir), ID(ID)
    {
    }

    void Move();

    void check(vector<Enemy>& enemies);
};

class Enemy {
    public:
    int ID = 2;
    int hp;
    float x;
    float y;
    int r;
    float v;
    float timer = 0.0f;
    bool canHit = false;

    Enemy(int hp, float x, float y, int r, float v): hp(hp), x(x), y(y), r(r), v(v) {};

    void Move(float px, float py);
    void hit(Player& player);
    void drawUI();
};

class Player {
    public:
    int ID = 1;
    int hp;
    float x;
    float y;
    int r;
    float v;
    int vx = 0;
    int vy = 0;
    int mxsp = 10;
    public:
    Player(int hp, float x, float y, int r, float v): hp(hp), x(x), y(y), r(r), v(v) {};

    void Move();
    void hit(Enemy& enemy);
    void drawUI();
    void correct();
    void shot(vector<Bullet>& bullets);
};



int main()
{
    InitWindow(1280, 720, "My Game");
    SetTargetFPS(60);

    Player player(100,100,100,20,2);
    // Enemy enemy(1000,8000,8000,30,8);
    bool IsPaused = false;
    vector<Bullet> bullets;
    vector<Enemy> enemies;
    enum GameState {
        LOST,
        WIN,
        PAUSED,
        PLAYING,
    };
    enum GameLevel {
        EASY,
        MEDIUM,
        HARD,
        ULTRA,
    };

    GameState gameState = PLAYING;
    GameLevel glevel = EASY;
    float timer = 0.0f;
    float timer2 = 0.0f;
    float cdOnShot = 0.1f;
    float eCanMove = 5.0f;
    bool down = false;
    bool levelStarted = false;

    while (!WindowShouldClose())                                    // GAME LOOP
    {
        // INPUT
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        if (IsKeyPressed(KEY_F1) && IsPaused == false && gameState != LOST) {
            IsPaused = true;
            gameState = PAUSED;
        } else if (IsKeyPressed(KEY_F1) && IsPaused == true && gameState != LOST) {
            IsPaused = false;
            gameState = PLAYING;
        }

        float dt = GetFrameTime();                 // dt
        timer += dt;
        if (!down) {timer2 += dt;}

        for (Enemy& enemy : enemies) {
            enemy.timer += dt;
        }

        if (enemies.size() == 0) {
            levelStarted = false;
        }

        if (!levelStarted && glevel == EASY) {
            for (int i = 0; i <= 3;i++) {
                Enemy enemy(100,30*i,30*i,30,8);
                enemies.push_back(enemy);
            }
            levelStarted = true;
        }else if (!levelStarted && glevel == MEDIUM) {
            for (int i = 0; i <= 6;i++) {
                Enemy enemy(100,30*i,30*i,30,8);
                enemies.push_back(enemy);
            }
            levelStarted = true;
        }else if (!levelStarted && glevel == HARD) {
            for (int i = 0; i <= 10;i++) {
                Enemy enemy(100,30*i,30*i,30,12);
                enemies.push_back(enemy);
            }
            levelStarted = true;
        }else if (!levelStarted && glevel == ULTRA) {
            for (int i = 0; i <= 20;i++) {
                Enemy enemy(100,30*i,30*i,30,18);
                enemies.push_back(enemy);
            }
            levelStarted = true;
        }


        if (!IsPaused) {
            if (timer >= cdOnShot) {
                player.shot(bullets);
                timer = 0.0f;
            }
            player.Move();
            // enemy.Move(player.x,player.y);
            player.correct();
            // enemy.hit(player);

            for (int i = 0; i < bullets.size();) {
                Bullet& bullet = bullets[i];
                if (bullet.IsUsed) {
                    bullets.erase(bullets.begin() + i);
                } else {
                    bullet.Move();
                    bullet.check(enemies);
                    if (bullet.IsUsed) {
                        bullets.erase(bullets.begin() + i);
                    } else {
                        i++;
                    }
                }
            }
            for (int i = 0; i < enemies.size();) { // enemy loop through
                Enemy& enemy = enemies[i];
                if (enemy.hp <= 0) {
                    enemies.erase(enemies.begin() + i);
                } else {
                    if (timer2 >= eCanMove) {
                        enemy.Move(player.x,player.y);
                        enemy.hit(player);
                        down = true;
                    }
                    i++;
                }
            }
        }

        if (player.hp <= 0) {
            gameState = LOST;
            IsPaused = true;
        }


        if (enemies.size() == 0 && glevel == ULTRA) {
            gameState = WIN;
            IsPaused = true;
        }

        if (enemies.size() == 0 && glevel == HARD) {
            glevel = ULTRA;
        }
        if (enemies.size() == 0 && glevel == MEDIUM) {
            glevel = HARD;
        }
        if (enemies.size() == 0 && glevel == EASY) {
            glevel = MEDIUM;
        }



        // DRAW
        BeginDrawing();

        switch (gameState) {
            case PLAYING:
                ClearBackground(RAYWHITE);

                DrawCircle(player.x, player.y, player.r, BLUE);
                player.drawUI();

                for (int i = 0; i < enemies.size();i++) { // enemy loop through
                    Enemy& enemy = enemies[i];
                    DrawCircle(enemy.x, enemy.y, enemy.r, RED);
                    enemy.drawUI();
                }

                for (Bullet bullet : bullets ) {
                    DrawCircle(bullet.x, bullet.y, bullet.r, ORANGE);
                }
                break;
            case LOST: {
                ClearBackground(RED);
                int textWidth = MeasureText("YOU LOST",120);
                DrawText("YOU LOST",GetScreenWidth()/2.0f - textWidth/2,GetScreenHeight()/2.0f -60,120,BLACK);
                break;
            }
            case WIN: {
                ClearBackground(YELLOW);
                int textWidth = MeasureText("YOU LOST",120);
                DrawText("YOU WIN",GetScreenWidth()/2.0f - textWidth/2,GetScreenHeight()/2.0f-60,120,BLACK);
                break;
            }
            case PAUSED:
                DrawCircle(GetScreenWidth()/2.0f,GetScreenHeight()/2.0f,50,GRAY);
                DrawPoly({GetScreenWidth()/2.0f,GetScreenHeight()/2.0f},3,30,0,BLACK);
                DrawText("PAUSED",10,10,20,GRAY);
                break;
        }

        EndDrawing();
        // cout << player.hp << endl;
    }

    CloseWindow();

    return 0;
}


void Player::Move() {
    if (IsKeyDown(KEY_W)) {
        if (std::abs(vy) <= mxsp) {
            vy -= v;
        }
    }
    if (IsKeyDown(KEY_S)) {
        if (std::abs(vy) <= mxsp) {
            vy += v;
        }
    }
    if (IsKeyDown(KEY_A)) {
        if (std::abs(vx) <= mxsp) {
            vx -= v;
        }
    }
    if (IsKeyDown(KEY_D)) {
        if (std::abs(vx) <= mxsp) {
            vx += v;
        }
    }
    if (std::abs(vy) == vy) { vy -= 1;}
    if (std::abs(vx) == vx) { vx -= 1;}
    if (std::abs(vy) != vy) { vy += 1;}
    if (std::abs(vx) != vx) { vx += 1;}

    x += vx;
    y += vy;
}

void Enemy::Move(float px, float py) {
    float dx = px - x;
    float dy = py - y;

    float len = Math::getLength(dx, dy);

    Vector2D normal = Math::getNormal(dx, dy, len);

    if (len > v) {
        x += normal.x * v;
        y += normal.y * v;
    }
}

void Enemy::hit(Player& player) {
    if (timer >= 0.3f) {canHit = true;}
    if (Math::getDistance(player.x,player.y,x,y) <= 50) {
        if (player.hp > 0 && canHit) {player.hp -= 0.05;canHit = false;timer = 0.0f;}
    }
}

void Player::drawUI() {
    DrawRectangle(10, 10, 200, 100, GRAY);
    float hpOnS = (200 / 100) * hp;
    DrawRectangle(10,10,hpOnS,100,GREEN);
}

void Player::correct() {
    if (x >= GetScreenWidth() - r) {
        x = GetScreenWidth() - r;
    }
    if (x <= 0 + r) {
        x = 0 + r;
    }
    if (y >= GetScreenHeight() - r) {
        y = GetScreenHeight() - r;
    }
    if (y <= 0 + r) {
        y = 0 + r;
    }
}

void Bullet::Move() {
    x += v * dir.x;
    y += v * dir.y;

    if (x >= GetScreenWidth() - r) {
        IsUsed = true;
    }
    if (x <= 0 + r) {
        IsUsed = true;
    }
    if (y >= GetScreenHeight() - r) {
        IsUsed = true;
    }
    if (y <= 0 + r) {
        IsUsed = true;
    }
}

void Bullet::check(vector<Enemy>& enemies) {
    for (int i = 0; i < enemies.size(); i++) {
        Enemy& enemy = enemies[i];
        if (Math::getDistance(x,y,enemy.x,enemy.y) <= r + enemy.r + help) {
            enemy.hp -= 10;
            IsUsed = true;
        }
    }
}

void Player::shot(vector<Bullet>& bullets) {
    if (IsKeyDown(KEY_SPACE)) {
        float mx = GetMouseX();
        float my = GetMouseY();

        Vector2D dir = {mx - x, my - y};

        float len = Math::getLength(dir.x, dir.y);
        dir = Math::getNormal(dir.x, dir.y, len);

        Bullet bullet(ID, x, y, 5, 20, dir, bullets.size() + 1);
        bullets.push_back(bullet);
    }
}

void Enemy::drawUI() {
    float barWidth = 60;
    float barHeight = 8;

    float hpWidth = (barWidth / 100.0f) * hp;

    DrawRectangle(
        x - barWidth / 2,
        y - r - 15,
        barWidth,
        barHeight,
        GRAY
    );

    DrawRectangle(
        x - barWidth / 2,
        y - r - 15,
        hpWidth,
        barHeight,
        GREEN
    );
}