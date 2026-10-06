#include "Raylib/include/raylib.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "Math.h"
#include <iostream>

using namespace std;

class Player;
class Enemy;

struct AmmoPickup {
    float x;
    float y;
    float r = 10;
    int amount = 5;
    bool IsUsed = false;

    AmmoPickup(float x, float y, int amount)
        : x(x), y(y), amount(amount)
    {
    }
};

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

    Enemy(int hp, float x, float y, int r, float v)
        : hp(hp), x(x), y(y), r(r), v(v)
    {
    }

    void Move(Player& player1, Player& player2);
    void hit(Player& player);
    void drawUI();
};

class Player {
public:
    int ID;
    int hp;
    float x;
    float y;
    int r;
    float v;

    int vx = 0;
    int vy = 0;
    int mxsp = 10;

    int ammo;
    bool infiniteAmmo;

    float shotTimer = 0.0f;
    float shotCooldown;

    float healTimer = 0.0f;

    float ammoDropTimer = 0.0f;
    float ammoDropCooldown = 5.0f;

public:
    Player(int ID, int hp, float x, float y, int r, float v)
        : ID(ID), hp(hp), x(x), y(y), r(r), v(v)
    {
        if (ID == 1) {
            ammo = 20;
            infiniteAmmo = false;
            shotCooldown = 0.1f;
        }
        else {
            ammo = 0;
            infiniteAmmo = true;
            shotCooldown = 0.2f; // P2 fele olyan gyorsan lő
        }
    }

    void Move();
    void hit(Enemy& enemy);
    void drawUI();
    void correct();

    void shot(vector<Bullet>& bullets, vector<Enemy>& enemies, float dt);

    void heal(Player& other, float dt);

    void dropAmmo(vector<AmmoPickup>& pickups, float dt);

    void collectAmmo(vector<AmmoPickup>& pickups);
};



int main()
{
    InitWindow(1280, 720, "My Game");
    SetTargetFPS(60);

    Player player1(1, 100, 100, 100, 20, 2);
    Player player2(2, 100, 300, 100, 20, 2);

    bool IsPaused = false;

    vector<Bullet> bullets;
    vector<Enemy> enemies;
    vector<AmmoPickup> ammoPickups;

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

    float enemyMoveTimer = 0.0f;
    float eCanMove = 5.0f;

    bool levelStarted = false;

    while (!WindowShouldClose())
    {
        // =========================================================
        // INPUT
        // =========================================================

        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        if (IsKeyPressed(KEY_F1) && !IsPaused && gameState != LOST) {
            IsPaused = true;
            gameState = PAUSED;
        }
        else if (IsKeyPressed(KEY_F1) && IsPaused && gameState != LOST) {
            IsPaused = false;
            gameState = PLAYING;
        }


        float dt = GetFrameTime();


        // =========================================================
        // LEVEL SYSTEM
        // =========================================================

        // Ha az előző pálya elfogyott, léptetjük a szintet.
        if (enemies.size() == 0 && levelStarted) {

            levelStarted = false;

            if (glevel == EASY) {
                glevel = MEDIUM;
            }
            else if (glevel == MEDIUM) {
                glevel = HARD;
            }
            else if (glevel == HARD) {
                glevel = ULTRA;
            }
            else if (glevel == ULTRA) {
                gameState = WIN;
                IsPaused = true;
            }
        }


        // Új level spawn
        if (!levelStarted && gameState == PLAYING) {

            if (glevel == EASY) {

                for (int i = 0; i <= 3; i++) {
                    Enemy enemy(100, 30 * i, 30 * i, 30, 8);
                    enemies.push_back(enemy);
                }

            }
            else if (glevel == MEDIUM) {

                for (int i = 0; i <= 6; i++) {
                    Enemy enemy(100, 30 * i, 30 * i, 30, 8);
                    enemies.push_back(enemy);
                }

            }
            else if (glevel == HARD) {

                for (int i = 0; i <= 10; i++) {
                    Enemy enemy(100, 30 * i, 30 * i, 30, 12);
                    enemies.push_back(enemy);
                }

            }
            else if (glevel == ULTRA) {

                for (int i = 0; i <= 20; i++) {
                    Enemy enemy(100, 30 * i, 30 * i, 30, 18);
                    enemies.push_back(enemy);
                }
            }

            levelStarted = true;
        }


        // =========================================================
        // GAME UPDATE
        // =========================================================

        if (!IsPaused && gameState == PLAYING) {

            enemyMoveTimer += dt;


            // -----------------------------------------------------
            // PLAYERS MOVE
            // -----------------------------------------------------

            if (player1.hp > 0) {
                player1.Move();
                player1.correct();
            }

            if (player2.hp > 0) {
                player2.Move();
                player2.correct();
            }


            // -----------------------------------------------------
            // PLAYER 1 AMMO PICKUP
            // -----------------------------------------------------

            if (player1.hp > 0) {
                player1.collectAmmo(ammoPickups);
            }


            // -----------------------------------------------------
            // PLAYER 1 HEAL -> PLAYER 2
            // -----------------------------------------------------

            if (player1.hp > 0 && player2.hp > 0) {
                player1.heal(player2, dt);
            }


            // -----------------------------------------------------
            // PLAYER 2 AUTO AMMO DROP
            // -----------------------------------------------------

            if (player2.hp > 0) {
                player2.dropAmmo(ammoPickups, dt);
            }


            // -----------------------------------------------------
            // SHOOTING
            // -----------------------------------------------------

            if (player1.hp > 0) {
                player1.shot(bullets, enemies, dt);
            }

            if (player2.hp > 0) {
                player2.shot(bullets, enemies, dt);
            }


            // -----------------------------------------------------
            // BULLETS
            // -----------------------------------------------------

            for (int i = 0; i < bullets.size();) {

                Bullet& bullet = bullets[i];

                if (bullet.IsUsed) {
                    bullets.erase(bullets.begin() + i);
                }
                else {

                    bullet.Move();
                    bullet.check(enemies);

                    if (bullet.IsUsed) {
                        bullets.erase(bullets.begin() + i);
                    }
                    else {
                        i++;
                    }
                }
            }


            // -----------------------------------------------------
            // ENEMIES
            // -----------------------------------------------------

            if (enemyMoveTimer >= eCanMove) {

                enemyMoveTimer = 0.0f;

                for (int i = 0; i < enemies.size();) {

                    Enemy& enemy = enemies[i];

                    if (enemy.hp <= 0) {
                        enemies.erase(enemies.begin() + i);
                    }
                    else {

                        // Mindig a két player közül a közelebbit választja
                        enemy.Move(player1, player2);

                        // Az enemy ugyanazt a playert sebzi,
                        // amelyiket üldözi / amelyik közelebb van.
                        float d1 = Math::getDistance(
                            player1.x,
                            player1.y,
                            enemy.x,
                            enemy.y
                        );

                        float d2 = Math::getDistance(
                            player2.x,
                            player2.y,
                            enemy.x,
                            enemy.y
                        );

                        if (player1.hp > 0 && player2.hp > 0) {

                            if (d1 <= d2) {
                                enemy.hit(player1);
                            }
                            else {
                                enemy.hit(player2);
                            }

                        }
                        else if (player1.hp > 0) {
                            enemy.hit(player1);
                        }
                        else if (player2.hp > 0) {
                            enemy.hit(player2);
                        }

                        i++;
                    }
                }
            }


            // -----------------------------------------------------
            // AMMO PICKUP CLEANUP
            // -----------------------------------------------------

            for (int i = 0; i < ammoPickups.size();) {

                if (ammoPickups[i].IsUsed) {
                    ammoPickups.erase(ammoPickups.begin() + i);
                }
                else {
                    i++;
                }
            }
        }


        // =========================================================
        // GAME STATE
        // =========================================================

        // Csak akkor vesztünk, ha mindkét player meghal.
        if (player1.hp <= 0 && player2.hp <= 0) {
            player1.hp = 0;
            player2.hp = 0;

            gameState = LOST;
            IsPaused = true;
        }


        // =========================================================
        // DRAW
        // =========================================================

        BeginDrawing();

        switch (gameState) {

            case PLAYING:
            {
                ClearBackground(RAYWHITE);


                // -------------------------------------------------
                // PLAYER 1
                // -------------------------------------------------

                if (player1.hp > 0) {
                    DrawCircle(
                        player1.x,
                        player1.y,
                        player1.r,
                        BLUE
                    );
                }


                // -------------------------------------------------
                // PLAYER 2
                // -------------------------------------------------

                if (player2.hp > 0) {
                    DrawCircle(
                        player2.x,
                        player2.y,
                        player2.r,
                        GREEN
                    );
                }


                // -------------------------------------------------
                // PLAYER UI
                // -------------------------------------------------

                player1.drawUI();
                player2.drawUI();


                // -------------------------------------------------
                // AMMO PICKUPS
                // -------------------------------------------------

                for (AmmoPickup& pickup : ammoPickups) {

                    if (!pickup.IsUsed) {

                        DrawCircle(
                            pickup.x,
                            pickup.y,
                            pickup.r,
                            ORANGE
                        );

                        DrawText(
                            TextFormat("+%d", pickup.amount),
                            pickup.x - 8,
                            pickup.y - 6,
                            12,
                            BLACK
                        );
                    }
                }


                // -------------------------------------------------
                // ENEMIES
                // -------------------------------------------------

                for (Enemy& enemy : enemies) {

                    DrawCircle(
                        enemy.x,
                        enemy.y,
                        enemy.r,
                        RED
                    );

                    enemy.drawUI();
                }


                // -------------------------------------------------
                // BULLETS
                // -------------------------------------------------

                for (Bullet& bullet : bullets) {

                    if (bullet.myParent == 1) {
                        DrawCircle(
                            bullet.x,
                            bullet.y,
                            bullet.r,
                            ORANGE
                        );
                    }
                    else {
                        DrawCircle(
                            bullet.x,
                            bullet.y,
                            bullet.r,
                            PURPLE
                        );
                    }
                }


                // -------------------------------------------------
                // LEVEL
                // -------------------------------------------------

                const char* levelText = "";

                if (glevel == EASY) {
                    levelText = "EASY";
                }
                else if (glevel == MEDIUM) {
                    levelText = "MEDIUM";
                }
                else if (glevel == HARD) {
                    levelText = "HARD";
                }
                else if (glevel == ULTRA) {
                    levelText = "ULTRA";
                }

                DrawText(
                    TextFormat("LEVEL: %s", levelText),
                    GetScreenWidth() / 2 - 60,
                    10,
                    20,
                    BLACK
                );

                break;
            }


            case LOST:
            {
                ClearBackground(RED);

                int textWidth = MeasureText(
                    "YOU LOST",
                    120
                );

                DrawText(
                    "YOU LOST",
                    GetScreenWidth() / 2.0f - textWidth / 2,
                    GetScreenHeight() / 2.0f - 60,
                    120,
                    BLACK
                );

                break;
            }


            case WIN:
            {
                ClearBackground(YELLOW);

                int textWidth = MeasureText(
                    "YOU WIN",
                    120
                );

                DrawText(
                    "YOU WIN",
                    GetScreenWidth() / 2.0f - textWidth / 2,
                    GetScreenHeight() / 2.0f - 60,
                    120,
                    BLACK
                );

                break;
            }


            case PAUSED:
            {
                ClearBackground(RAYWHITE);

                DrawCircle(
                    GetScreenWidth() / 2.0f,
                    GetScreenHeight() / 2.0f,
                    50,
                    GRAY
                );

                DrawPoly(
                    {
                        GetScreenWidth() / 2.0f,
                        GetScreenHeight() / 2.0f
                    },
                    3,
                    30,
                    0,
                    BLACK
                );

                DrawText(
                    "PAUSED",
                    10,
                    10,
                    20,
                    GRAY
                );

                break;
            }
        }

        EndDrawing();
    }


    CloseWindow();

    return 0;
}



// ================================================================
// PLAYER MOVEMENT
// ================================================================

void Player::Move()
{
    // PLAYER 1
    if (ID == 1) {

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
    }


    // PLAYER 2
    else {

        if (IsKeyDown(KEY_UP)) {
            if (std::abs(vy) <= mxsp) {
                vy -= v;
            }
        }

        if (IsKeyDown(KEY_DOWN)) {
            if (std::abs(vy) <= mxsp) {
                vy += v;
            }
        }

        if (IsKeyDown(KEY_LEFT)) {
            if (std::abs(vx) <= mxsp) {
                vx -= v;
            }
        }

        if (IsKeyDown(KEY_RIGHT)) {
            if (std::abs(vx) <= mxsp) {
                vx += v;
            }
        }
    }


    // FRICTION
    if (std::abs(vy) == vy) {
        vy -= 1;
    }

    if (std::abs(vx) == vx) {
        vx -= 1;
    }

    if (std::abs(vy) != vy) {
        vy += 1;
    }

    if (std::abs(vx) != vx) {
        vx += 1;
    }


    x += vx;
    y += vy;
}



// ================================================================
// ENEMY MOVEMENT
// ================================================================

void Enemy::Move(Player& player1, Player& player2)
{
    float d1 = 9999999.0f;
    float d2 = 9999999.0f;

    if (player1.hp > 0) {
        d1 = Math::getDistance(
            player1.x,
            player1.y,
            x,
            y
        );
    }

    if (player2.hp > 0) {
        d2 = Math::getDistance(
            player2.x,
            player2.y,
            x,
            y
        );
    }


    float targetX;
    float targetY;

    // Közelebbi player kiválasztása
    if (d1 <= d2) {
        targetX = player1.x;
        targetY = player1.y;
    }
    else {
        targetX = player2.x;
        targetY = player2.y;
    }


    float dx = targetX - x;
    float dy = targetY - y;

    float len = Math::getLength(dx, dy);

    if (len == 0) {
        return;
    }

    Vector2D normal = Math::getNormal(
        dx,
        dy,
        len
    );

    if (len > v) {
        x += normal.x * v;
        y += normal.y * v;
    }
}



// ================================================================
// ENEMY DAMAGE
// ================================================================

void Enemy::hit(Player& player)
{
    timer += GetFrameTime();

    if (timer >= 0.3f) {
        canHit = true;
    }


    if (
        player.hp > 0 &&
        Math::getDistance(
            player.x,
            player.y,
            x,
            y
        ) <= 50
    ) {

        if (canHit) {

            player.hp -= 5;

            if (player.hp < 0) {
                player.hp = 0;
            }

            canHit = false;
            timer = 0.0f;
        }
    }
}



// ================================================================
// PLAYER UI
// ================================================================

void Player::drawUI()
{
    float boxX;
    float boxY;

    if (ID == 1) {
        boxX = 10;
        boxY = 10;
    }
    else {
        boxX = GetScreenWidth() - 220;
        boxY = 10;
    }


    DrawRectangle(
        boxX,
        boxY,
        200,
        100,
        GRAY
    );


    // HP BAR
    float hpOnS = (200.0f / 100.0f) * hp;

    if (hpOnS < 0) {
        hpOnS = 0;
    }

    if (hpOnS > 200) {
        hpOnS = 200;
    }

    DrawRectangle(
        boxX,
        boxY,
        hpOnS,
        30,
        GREEN
    );


    // NAME
    if (ID == 1) {

        DrawText(
            "PLAYER 1",
            boxX + 5,
            boxY + 35,
            20,
            BLUE
        );

        DrawText(
            TextFormat("AMMO: %d", ammo),
            boxX + 5,
            boxY + 65,
            18,
            BLACK
        );
    }
    else {

        DrawText(
            "PLAYER 2",
            boxX + 5,
            boxY + 35,
            20,
            DARKGREEN
        );

        DrawText(
            "AMMO: INFINITE",
            boxX + 5,
            boxY + 65,
            18,
            BLACK
        );
    }
}



// ================================================================
// PLAYER SCREEN BOUNDS
// ================================================================

void Player::correct()
{
    if (x >= GetScreenWidth() - r) {
        x = GetScreenWidth() - r;
    }

    if (x <= r) {
        x = r;
    }

    if (y >= GetScreenHeight() - r) {
        y = GetScreenHeight() - r;
    }

    if (y <= r) {
        y = r;
    }
}



// ================================================================
// PLAYER SHOOTING
// ================================================================

void Player::shot(
    vector<Bullet>& bullets,
    vector<Enemy>& enemies,
    float dt
)
{
    shotTimer += dt;


    // ============================================================
    // PLAYER 1
    // ============================================================

    if (ID == 1) {

        if (
            IsKeyDown(KEY_SPACE) &&
            shotTimer >= shotCooldown &&
            ammo > 0
        ) {

            float mx = GetMouseX();
            float my = GetMouseY();


            Vector2D dir = {
                mx - x,
                my - y
            };


            float len = Math::getLength(
                dir.x,
                dir.y
            );


            if (len == 0) {
                return;
            }


            dir = Math::getNormal(
                dir.x,
                dir.y,
                len
            );


            Bullet bullet(
                ID,
                x,
                y,
                5,
                20,
                dir,
                bullets.size() + 1
            );


            bullets.push_back(bullet);

            ammo--;

            shotTimer = 0.0f;
        }
    }


    // ============================================================
    // PLAYER 2
    // ============================================================

    else {

        // Automatikus lövés
        if (
            shotTimer >= shotCooldown &&
            enemies.size() > 0
        ) {

            Enemy* closestEnemy = nullptr;
            float closestDistance = 9999999.0f;


            for (Enemy& enemy : enemies) {

                float distance = Math::getDistance(
                    x,
                    y,
                    enemy.x,
                    enemy.y
                );


                if (distance < closestDistance) {
                    closestDistance = distance;
                    closestEnemy = &enemy;
                }
            }


            if (closestEnemy != nullptr) {

                Vector2D dir = {
                    closestEnemy->x - x,
                    closestEnemy->y - y
                };


                float len = Math::getLength(
                    dir.x,
                    dir.y
                );


                if (len > 0) {

                    dir = Math::getNormal(
                        dir.x,
                        dir.y,
                        len
                    );


                    Bullet bullet(
                        ID,
                        x,
                        y,
                        5,
                        20,
                        dir,
                        bullets.size() + 1
                    );


                    bullets.push_back(bullet);

                    shotTimer = 0.0f;
                }
            }
        }
    }
}



// ================================================================
// PLAYER 1 HEAL
// ================================================================

void Player::heal(Player& other, float dt)
{
    if (ID != 1) {
        return;
    }

    healTimer += dt;


    float distance = Math::getDistance(
        x,
        y,
        other.x,
        other.y
    );


    // E gomb + közel van + cooldown lejárt
    if (
        IsKeyDown(KEY_E) &&
        distance <= 120 &&
        healTimer >= 1.0f &&
        other.hp > 0 &&
        other.hp < 100
    ) {

        other.hp += 20;

        if (other.hp > 100) {
            other.hp = 100;
        }

        healTimer = 0.0f;
    }
}



// ================================================================
// PLAYER 2 AMMO DROP
// ================================================================

void Player::dropAmmo(
    vector<AmmoPickup>& pickups,
    float dt
)
{
    if (ID != 2) {
        return;
    }

    ammoDropTimer += dt;


    if (ammoDropTimer >= ammoDropCooldown) {

        AmmoPickup pickup(
            x,
            y,
            5
        );


        pickups.push_back(pickup);

        ammoDropTimer = 0.0f;
    }
}



// ================================================================
// PLAYER 1 COLLECT AMMO
// ================================================================

void Player::collectAmmo(
    vector<AmmoPickup>& pickups
)
{
    if (ID != 1) {
        return;
    }


    for (AmmoPickup& pickup : pickups) {

        if (pickup.IsUsed) {
            continue;
        }


        float distance = Math::getDistance(
            x,
            y,
            pickup.x,
            pickup.y
        );


        if (distance <= r + pickup.r) {

            ammo += pickup.amount;

            pickup.IsUsed = true;
        }
    }
}



// ================================================================
// BULLET MOVE
// ================================================================

void Bullet::Move()
{
    x += v * dir.x;
    y += v * dir.y;


    if (x >= GetScreenWidth() - r) {
        IsUsed = true;
    }

    if (x <= r) {
        IsUsed = true;
    }

    if (y >= GetScreenHeight() - r) {
        IsUsed = true;
    }

    if (y <= r) {
        IsUsed = true;
    }
}



// ================================================================
// BULLET COLLISION
// ================================================================

void Bullet::check(vector<Enemy>& enemies)
{
    for (int i = 0; i < enemies.size(); i++) {

        Enemy& enemy = enemies[i];


        if (
            Math::getDistance(
                x,
                y,
                enemy.x,
                enemy.y
            ) <= r + enemy.r + help
        ) {

            enemy.hp -= 10;

            IsUsed = true;

            // Egy lövedék csak egy enemy-t találhat el
            break;
        }
    }
}



// ================================================================
// ENEMY UI
// ================================================================

void Enemy::drawUI()
{
    float barWidth = 60;
    float barHeight = 8;

    float hpWidth = (barWidth / 100.0f) * hp;


    if (hpWidth < 0) {
        hpWidth = 0;
    }

    if (hpWidth > barWidth) {
        hpWidth = barWidth;
    }


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