#include "iGraphics.h"
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <direct.h>
#include "iSound.h"
#define screenwidth 731
#define screenlength 1300

int bgSoundIdx = -1;
bool importantSoundsOn = false;
bool runState = false;
int gameState = -1;
int loading = 0;
int loading1 = 0;
bool musicOn = true;
void drawHUD();
int collisionNumber = 0;
bool charHurt = false;

int playerWidth = 88, playerHeight = 140;
int X = 350;
int Y = 135;
Image bg;
int speed = -25;

void loadResources()
{
    iLoadImage(&bg, "Candy-Rush/Background/Background2.png");
}

char idle[4][80] = {"Candy-Rush/Assets/Pink_Monster_Idle.png/tile000.png",
                    "Candy-Rush/Assets/Pink_Monster_Idle.png/tile001.png",
                    "Candy-Rush/Assets/Pink_Monster_Idle.png/tile002.png",
                    "Candy-Rush/Assets/Pink_Monster_Idle.png/tile003.png"};
char run[6][50] = {"Candy-Rush/Assets/Pink_Monster_Run/tile000.png", "Candy-Rush/Assets/Pink_Monster_Run/tile001.png", "Candy-Rush/Assets/Pink_Monster_Run/tile002.png", "Candy-Rush/Assets/Pink_Monster_Run/tile003.png", "Candy-Rush/Assets/Pink_Monster_Run/tile004.png", "Candy-Rush/Assets/Pink_Monster_Run/tile005.png"};
char jumpSprite[8][50] = {"Candy-Rush/Assets/Pink_Monster_Jump/tile000.png",
                          "Candy-Rush/Assets/Pink_Monster_Jump/tile001.png", "Candy-Rush/Assets/Pink_Monster_Jump/tile002.png", "Candy-Rush/Assets/Pink_Monster_Jump/tile003.png", "Candy-Rush/Assets/Pink_Monster_Jump/tile004.png", "Candy-Rush/Assets/Pink_Monster_Jump/tile005.png", "Candy-Rush/Assets/Pink_Monster_Jump/tile006.png", "Candy-Rush/Assets/Pink_Monster_Jump/tile007.png"};
char hurt[4][50] = {"Candy-Rush/Assets/Pink_Monster_Hurt/tile000.png", "Candy-Rush/Assets/Pink_Monster_Hurt/tile001.png", "Candy-Rush/Assets/Pink_Monster_Hurt/tile002.png", "Candy-Rush/Assets/Pink_Monster_Hurt/tile003.png"};

char attack[4][60] = {"Candy-Rush/Assets/Pink_Monster_Attack/tile000.png", "Candy-Rush/Assets/Pink_Monster_Attack/tile001.png", "Candy-Rush/Assets/Pink_Monster_Attack/tile002.png", "Candy-Rush/Assets/Pink_Monster_Attack/tile003.png"};

char enemyRun[8][50] = {"Candy-Rush/Assests/Enemy/EnemyRun000.png", "Candy-Rush/Assests/Enemy/EnemyRun001.png", "Candy-Rush/Assests/Enemy/EnemyRun002.png", "Candy-Rush/Assests/Enemy/EnemyRun003.png", "Candy-Rush/Assests/Enemy/EnemyRun004.png", "Candy-Rush/Assests/Enemy/EnemyRun005.png", "Candy-Rush/Assests/Enemy/EnemyRun006.png", "Candy-Rush/Assests/Enemy/EnemyRun007.png"};

int enemyRunidx = 0;

struct Enemy
{
    int x;
    int y;
    int width;
    int height;
    bool active;

} enemy;
int collisionTimeOut = 0;
int enemyTimeOut = 0;
int enemyDeadTimer = 0;

char powerUpSound[60] = "Candy-Rush/SoundEffect/powerUp.wav";

char frostingSound[60] = "Candy-Rush/SoundEffect/coin-collision-sound-342335.wav";

#define MAX_FROSTINGS 6
int frostingIdx = 0;
int totalFrostingCollected = 0;
int frostingTime = 0;
char frosting[45][40] = {"Candy-Rush/Frostings/cupcake.png", "Candy-Rush/Frostings/donut.png", "Candy-Rush/Frostings/starCandy.png", "Candy-Rush/Frostings/sugarcandy.png", "Candy-Rush/Frostings/toffee.png", "Candy-Rush/Frostings/lolipop.png"};

struct Frosting
{
    int x;
    int y;
    bool active;
    int type;
};
struct Frosting frostings[MAX_FROSTINGS];

bool standPosition = true;
int standCount = 0;
bool kill = false;
int killTimer = 0;
bool jump = false;
bool jumpUp = false;
bool jumpDown = false;
int jumpLimit = 100;
int coordinateJump = 0;

struct powerUp
{
    int x;
    int y;
    int width;
    int height;
    bool active;
} speedUp, doubleFrostings;

char magicPotion[40] = "Candy-Rush/ExtraLabels/MagicPotion.png";

bool doubleFrostingsEffect = false;
int doubleFrostingsEffectActivatorTimer = 0;
int doubleFrostingsEffectDeactivatorTimer = 0;
bool speedUpEffect = false;
int speedUpEffectActivatorTimer = 0;
int speedUpEffectDeactivatorTimer = 0;

struct obstacle
{
    int obs_x;
    int obs_y;
    int obs_width;
    int obs_height;
    bool active;

} obs1;
struct obstacle1
{
    int obs_x;
    int obs_y;
    int obs_width;
    int obs_height;
    bool active;

} obs2;
struct Background
{
    int x;
    int y;
};

int bcIndex = 0;
int idleIdx = 0;
int runIdx = 0;
int jumpUpIdx = 0;
int jumpDownIdx = 5;
int hurtIdx = 0;
int attackIdx = 0;

int score = 0;
int second = 0;
char sec[10000];
int minute = 0;
int hour = 0;
char hr[1000];
int totalSecond = 0;
char point[10000];

void checkCollision();

void drawFrostings();
void rosteringFrostings();
void checkFrostingCollection();
void checkEnemyCollision();
void moveObstacle();
void setSpeedUpPower();
void moveSpeedUpPower();
void gainSpeedUpPower();
void rosteringSpeedUpPower();
void setDoubleFrostingPower();
void rosteringDoubleFrostingPower();
void moveDoubleFrostingPower();
void gainDoubleFrostingPower();

void GameOver();
void readScore();
void showChar();
//
void func_timers();
//
void highlightScoreRow(int score)
{
    int x = 400;     // Shifted X to match your tagboard position
    int width = 500; // Adjusted width to match table
    int height = 45; // Each row height based on image

    int y;

    if (score >= 1000)
        y = 512; // Top row
    else if (score >= 800)
        y = 454;
    else if (score >= 600)
        y = 396;
    else if (score >= 400)
        y = 338;
    else
        y = 280; // Bottom row//246,

    iSetTransparentColor(218, 112, 214, 0.8); // Light yellow highlight
    iFilledRectangle(x, y, width, height);
}

//

void changeTimer()
{
    if (gameState == 1)
    {
        totalSecond = (second++) + (60 * minute) + (60 * 60 * hour);
        score = score + second;
    }
}

void drawTimer()
{
    if (gameState == 1)
    {
        iShowImage(1000, screenwidth - 150, "Candy-Rush/Button/purple.png");

        iSetColor(255, 255, 255);
        sprintf(sec, "Time: %d", second);
        iText(1160, screenwidth - 80, sec, GLUT_BITMAP_HELVETICA_18);
        iShowImage(1051, screenwidth - 150, "Candy-Rush/ExtraLabels/coin.png");
        iSetColor(255, 255, 255);
        sprintf(point, "Score: %d", score);
        iText(1038, screenwidth - 80, point, GLUT_BITMAP_HELVETICA_18);
    }
}
// gameState -1: Welcome Page
// gameState 0 : MenuPage
// gameState 1 : Actual Game
// gameState 2 : Gameover
// gameState 3 : How to Play
// gameState 4 : Options
// gameState 5: About
// gameState 6:Leaderboard

void GameOver()
{
    iSetColor(128, 128, 128);
    iFilledRectangle(0, 0, screenwidth, screenlength);
    iShowImage(0, 0, "Candy-Rush/UI/candy_fair_tag_boardpng (1).png");
    // iShowImage(0, 0, "Candy-Rush/UI/GameOver.png");

    gameState = 2;
}

void iMouse(int button, int state, int mx, int my)
{
    // printf("x=%d y=%d\n",mx,my);

    if (gameState == 0) // Menu
    {
        // PLAY
        if (mx >= 550 && mx <= 751 && my >= (screenwidth - 176) && my <= (screenwidth - 90))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            gameState = 1;
        }

        // How to play
        else if (mx >= 511 && mx <= 780 && my >= (screenwidth - 296) && my <= (screenwidth - 207))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            gameState = 3;
        }
        // Options
        else if (mx >= 538 && mx <= 762 && my >= (screenwidth - 448) && my <= (screenwidth - 335))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
           
            gameState = 4;
        }
        else if (mx >= 517 && mx <= 785 && my >= (screenwidth - 580) && my <= (screenwidth - 480))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;

            gameState = 6;
        }
        else if (mx >= 553 && mx <= 751 && my >= (screenwidth - 696) && my <= (screenwidth - 609))
        { //About
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;

            gameState = 5;
        }
    }

    if (gameState == 1)
    { // play
    }
    if (gameState == 2)
    {
        if (mx >= 508 && mx <= 795 && my >= (screenwidth - 673) && my <= (screenwidth - 574))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;

            gameState = 0;
        }
    }
    if (gameState == 5) 
    {
        if (mx >= 550 && mx <= 796 && my >= (screenwidth - 580) && my <= (screenwidth - 510))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            gameState = 0;
        }
    }

    if (gameState == 3) // howtoplay
    {
        if (mx >= 461 && mx <= 884 && my >= (screenwidth - 629) && my <= (screenwidth - 573))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            gameState = 0;
        }
    }
    // gameState -1: Welcome Page
    // gameState 0 : MenuPage
    // gameState 1 : Actual Game
    // gameState 2 : Gameover
    // gameState 3 : How to Play
    // gameState 4 : Options
    // gameState 5: About
    // gameState 6:Acievements

    if (gameState == 4) // options
    {
        if (mx >= 580 && mx <= 749 && my >= (screenwidth - 244) && my <= (screenwidth - 172))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            musicOn = true;
        }
        if (mx >= 580 && mx <= 74 && my >= (screenwidth - 348) && my <= (screenwidth - 273))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            musicOn = false;
        }
        if (mx >= 550 && mx <= 785 && my >= (screenwidth - 596) && my <= (screenwidth - 510))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            gameState = 0;
        }
    }
}

void iKeyboard(unsigned char key)
{
    if (key == ' ')
    {
        if (!jump)
        {
            jump = true;
            jumpUp = true;
        }
    }
    if (key == 'k' || key == 'K')
    {
        kill = true;
        if (musicOn)
        {
            importantSoundsOn = true;
            PlaySound(TEXT("Candy-Rush/SoundEffect/mixkit-punch-through-air-2141.wav"), NULL, SND_FILENAME | SND_ASYNC);

            //   iPlaySound("Candy-Rush/SoundEffect/mixkit-punch-through-air-2141.wav", false);
        }
        importantSoundsOn = false;
    }

    if (key == 'r' || key == 'R')
    {
        gameState = 1;
    }
    else if (key == 'p' || key == 'P')
    {
        gameState = 0;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        standPosition = false;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        standPosition = true;
    }
}

/*
    function iSpecialKeyboard() is called whenver user hits special keys like-
    function keys, home, end, pg up, pg down, arraows etc. you have to use
    appropriate constants to detect them. A list is:
    GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
    GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
    GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
    GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
    */
// int bgSoundIdx = -1; //
void iSpecialKeyboard(unsigned char key)
{
    
    switch (key)
    {
    case GLUT_KEY_UP:
        iIncreaseVolume(bgSoundIdx, 5);
        break;
    case GLUT_KEY_DOWN:
        iDecreaseVolume(bgSoundIdx, 5);
        break;
        // place your codes for other keys here
    default:
        break;
    } //*/
}
void iMouseMove(int mx, int my)
{
    // place your codes here
    // printf("Mouse moves in %d,%d", mx, my);
}
void iMouseDrag(int mx, int my)
{
    // place your codes here
}

void iMouseWheel(int dir, int mx, int my)
{
    // place your code here
}

void iDraw()
{
    // place your drawing codes here
    iClear();

    if (gameState == -1)
    {
        iShowImage(0, 0, "Candy-Rush/UI/WelcomeNew.png");
        loading++;
        /*if (musicOn)
        {
            importantSoundsOn = true;
            PlaySound(TEXT("Candy-Rush/SoundEffect/playthroughmusic.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        importantSoundsOn = false;*/
        if (loading > 15)
        {
            loading = 0;
            gameState = 0;
        }
    }
    else if (gameState == 0)
    {
        /*if (musicOn)
        {
            importantSoundsOn = true;
            PlaySound(TEXT("Candy-Rush/SoundEffect/playthroughmusic.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
        importantSoundsOn = false;*/
        iShowImage(0, 0, "Candy-Rush/UI/MenuNewLatest.png");

        score = 0;
        totalFrostingCollected = 0;
        second = 0;
        collisionNumber = 0;
        speedUpEffect = false;
        doubleFrostingsEffect = false;
    }
    else if (gameState == 1)
    {
        iStopSound(bgSoundIdx);
        func_timers();
        iClear();
        iShowLoadedImage(0, 0, &bg);
        iWrapImage(&bg, speed);

        if (speedUpEffect)
        {
            iShowImage(X - 58, Y + coordinateJump, "Candy-Rush/ExtraLabels/Adobe Express - file (40).png");
            iShowImage(1170,screenwidth-170,  "Candy-Rush/ExtraLabels/MagicPotion.png");
            drawHUD();
        }
        if (doubleFrostingsEffect)
        {
            iShowImage(1150, screenwidth - 150, "Candy-Rush/ExtraLabels/double_coins.png");
        }

        if (jump)
        {
            if (kill)
            {
                iShowImage(X, Y + coordinateJump, attack[attackIdx]);
            }
            else
            {
                runState = true;
                if (jumpUp)
                {
                    iShowImage(X, Y + coordinateJump, jumpSprite[jumpUpIdx]);
                }
                else
                {
                    iShowImage(X, Y + coordinateJump, jumpSprite[jumpDownIdx]);
                }
            }
        }
        else if (charHurt)
        {

            iShowImage(X, Y, hurt[hurtIdx]);
        }
        else if (kill)
        {
            iShowImage(X, Y, attack[attackIdx]);
        }
        else
        {
            if (!standPosition || second >= 4)
            {
                if (kill)
                {
                    iShowImage(X, Y, attack[attackIdx]);
                }
                else
                {
                    runState = true;
                    iShowImage(X, Y, run[runIdx]);
                }
            }
            else if (second < 4)
            {
                if (kill)
                {
                    iShowImage(X, Y, attack[attackIdx]);
                }
                else
                {
                    runState = false;
                    iShowImage(X, Y, idle[idleIdx]);
                }
            }
        }
        if (enemy.x != obs1.obs_x)
        {
            if (enemy.active)
            {
                iShowImage(enemy.x, enemy.y, enemyRun[enemyRunidx]);
            }
            if (obs1.active)
            {
                iShowImage(obs1.obs_x, obs1.obs_y, "Candy-Rush/Frostings/Obstacle.png");
            }
        }

        if (speedUp.active)
        {

            iShowImage(speedUp.x, speedUp.y, "Candy-Rush/ExtraLabels/MagicPotion.png");
        }

        if (doubleFrostings.active)
        {

            iShowImage(doubleFrostings.x, doubleFrostings.y, "Candy-Rush/ExtraLabels/Diamond.png");
        }

        drawFrostings();
        drawTimer();

        char frostingText[50];
        sprintf(frostingText, "%d", totalFrostingCollected);
        iShowImage(620, screenwidth - 150, "Candy-Rush/Button/tealBlue.png");
        iText(695, screenwidth - 80, frostingText, GLUT_BITMAP_HELVETICA_18);
        iShowImage(540, screenwidth - 150, "Candy-Rush/ExtraLabels/Gems.png");

        checkFrostingCollection();

        char collisionText[50];

        iShowImage(25, screenwidth - 150, "Candy-Rush/Button/pink.png");
        sprintf(collisionText, "Life : %d", 3 - collisionNumber);
        iText(67, screenwidth - 80, collisionText, GLUT_BITMAP_HELVETICA_18);
        if ((3 - collisionNumber) == 3)
        {
            iShowImage(25, screenwidth - 150, "Candy-Rush/ExtraLabels/heart.png");
            iShowImage(75, screenwidth - 150, "Candy-Rush/ExtraLabels/heart.png");
            iShowImage(123, screenwidth - 150, "Candy-Rush/ExtraLabels/heart.png");
        }
        else if ((3 - collisionNumber) == 2)
        {
            iShowImage(23, screenwidth - 150, "Candy-Rush/ExtraLabels/heart.png");
            iShowImage(75, screenwidth - 150, "Candy-Rush/ExtraLabels/heart.png");
        }
        else if ((3 - collisionNumber) == 1)
        {
            iShowImage(23, screenwidth - 150, "Candy-Rush/ExtraLabels/heart.png");
        }

        gainSpeedUpPower();
        gainDoubleFrostingPower();
        checkEnemyCollision();
        moveObstacle();
        checkCollision();
    }

    if (gameState == 2)
    {
        // here i have to place my code for tagboard
        // First draw the background tagboard image (if any)
        // iShowImage(...); ← Add your tagboard BG image if used
        iShowImage(0, 0, "Candy-Rush/UI/candy_fair_tag_boardpng (1).png");

        // Step 1: Highlight background row based on score
        highlightScoreRow(score);

        // Step 2: Now draw tagboard text on top
        //  iSetColor(255, 128, 0); // Orange text color(255,128,0)
        // iText(430, 510, "1000+     Legendary Licker", GLUT_BITMAP_HELVETICA_18);
        // iText(430, 450, "800-999   Sugar Blaster", GLUT_BITMAP_HELVETICA_18);
        // iText(430, 390, "600-799   Wizard of Sweets", GLUT_BITMAP_HELVETICA_18);
        // iText(430, 330, "400-599   Tooth Decayer", GLUT_BITMAP_HELVETICA_18);
        // iText(430, 270, "0-399     Candy Defender", GLUT_BITMAP_HELVETICA_18);

        // Optional: Show score
        char point[50];
        sprintf(point, "Your Score: %d", score); // totalFrostingCollected
        iSetColor(128, 0, 0);                    // 255,255,255
        iText(590, 200, point, GLUT_BITMAP_HELVETICA_18);

        // printf(" Score: %d", score);
        // iSetColor(255, 255, 255);
        // sprintf(point, "Score: %d", score);
        // iText(1038, screenwidth - 80, point, GLUT_BITMAP_HELVETICA_18);

        // GameOver();
        // showChar();
    }

    else if (gameState == 3)
    {

        iShowImage(0, 0, "Candy-Rush/UI/HowToPlayNew2.png");
    }

    // Options
    else if (gameState == 4)
    {

        iShowImage(0, 0, "Candy-Rush/UI/MusicControlNew.png");
    }
    else if (gameState == 5) // About
    {

        iShowImage(0, 0, "Candy-Rush/UI/About.png");
    }
}
void drawHUD()
{
    if (speedUpEffect)
    {
        float remainingTime = 1.0f - (float)speedUpEffectActivatorTimer / 5;
        iSetColor(0, 255,0);                                              // Green bar
        iFilledRectangle(1180, screenwidth - 150, 100 * remainingTime, 10); // Progress bar
    }
}
void func_timers()
{

    if (kill)
    {
        ++killTimer;
        if (killTimer > 10)
        {
            kill = false;
            killTimer = 0;
        }
    }

    if (!enemy.active)
    {
        ++enemyDeadTimer;
    }

    if (doubleFrostingsEffect)
    {
        ++doubleFrostingsEffectActivatorTimer;
        if (doubleFrostingsEffectActivatorTimer > 300)
        {
            doubleFrostingsEffect = false;
            doubleFrostingsEffectActivatorTimer = 0;
        }
    }

    if (speedUpEffect)
    {
        ++speedUpEffectActivatorTimer;
        if (speedUpEffectActivatorTimer > 80)
        {
            speedUpEffect = false;
            speed = -25;
            speedUpEffectActivatorTimer = 0;
        }
    }

    if (!obs1.active)
    {
        ++collisionTimeOut;
    }
}

void jumping()
{
    if (jump)
    {

        if (jumpUp)
        {
            coordinateJump += 7;
            if (coordinateJump >= jumpLimit)
            {
                jumpUp = false;
            }
        }
        else
        {
            jumpDown = true;
            coordinateJump -= 7;
            if (coordinateJump < 0)
            {
                jump = false;
                coordinateJump = 0;
                jumpDown = false;
                standPosition = false;
            }
        }
    }
}

void setObstacle()
{
    obs1.obs_x = 1300;
    obs1.obs_y = 135;
    obs1.obs_width = 64;
    obs1.obs_height = 61;
}
void generateObstacle()
{
    int x = rand() % 2;
    if (x == 1 && collisionTimeOut > 50)
    {
        obs1.active = true;
        collisionTimeOut = 0;
    }
}
void moveObstacle()
{
    obs1.obs_x -= 30;
    if (obs1.obs_x < 0)
    {
        obs1.active = false;
        obs1.obs_x = 1300;
    }
}
void checkCollision()
{
    if (obs1.active && second > 5)
    {

        if ((X < obs1.obs_x + obs1.obs_width && X + playerWidth > obs1.obs_x) && ((Y + coordinateJump) < obs1.obs_y + obs1.obs_height && (Y + coordinateJump) + playerHeight > obs1.obs_y) && !speedUpEffect)
        {

            obs1.active = false;
            ++collisionNumber;
            if (musicOn)
            {
                PlaySound(TEXT("Candy-Rush/SoundEffect/drop-sound-effect-240899.wav"), NULL, SND_FILENAME | SND_ASYNC);
                // iPlaySound("Candy-Rush/SoundEffect/drop-sound-effect-240899.wav", false);
            }

            charHurt = true;

            if (collisionNumber > 3)
            {
                gameState = 2;
                collisionNumber = 0;
            }
        }
    }
}

void setEnemy()
{
    enemy.x = 1300 + 200;
    enemy.y = 107;
    enemy.width = 190;
    enemy.height = 235;
}
void generateEnemy()
{
    int x = rand() % 2;
    if (x == 1)
    {
        if (enemyDeadTimer > 50)
        {
            enemy.active = true;
            enemy.width = 190;
            enemy.height = 235;
            enemyDeadTimer = 0;
        }
    }
}
void moveEnemy()
{
    /*if (speedUpEffect)
     {
         enemy.x -= 80;
     }
     else
     {*/
    enemy.x -= 30;
    if (enemy.x < 0)
    {
        enemy.active = false;
        enemy.x = 1300 + 150;
        enemy.width = 190;
        enemy.height = 235;
    }
}

void checkEnemyCollision()
{
    if (enemy.active)
    {
        enemy.width = 190;
        enemy.height = 235;

        if ((enemy.x - X) < 120)
        {
            if (kill)
            {
                enemy.active = false;
                kill = false;
                if (musicOn)
                {
                    PlaySound(TEXT("SoundEffect/deadly-strike-352458.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    //  iPlaySound("Candy-Rush/SoundEffect/mixkit-punch-through-air-2141.wav", false);
                }
            }
        }
        if (((Y + coordinateJump) < enemy.y + enemy.height && (Y + coordinateJump) + playerHeight > enemy.y) && !speedUpEffect && (X < enemy.x + enemy.width && X + playerWidth > enemy.x))
        {
            if (kill)
            {
                enemy.active = false;
                kill = false;
                if (musicOn)
                {
                    // PlaySound(TEXT("SoundEffect/deadly-strike-352458.wav"), NULL, SND_FILENAME | SND_ASYNC);
                }
                iPlaySound("Candy-Rush/SoundEffect/mixkit-punch-through-air-2141.wav", false);
            }
            else if (second > 10)
            {

                enemy.active = false;
                ++collisionNumber;
                if (musicOn)
                {
                    PlaySound(TEXT("Candy-Rush/SoundEffect/drop-sound-effect-240899.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    // iPlaySound("Candy-Rush/SoundEffect/drop-sound-effect-240899.wav", false);
                }
                charHurt = true;

                if (collisionNumber > 3)
                {
                    gameState = 2;
                    collisionNumber = 0;
                }
            }
        }
    }
    generateObstacle();
}

void SetFrostings()
{
    for (int i = 0; i < MAX_FROSTINGS; i++)
    {
        frostings[i].x = screenlength + rand() % 300;
        ;
        frostings[i].y = Y + rand() % 200;
        frostings[i].type = i % 3;
        frostings[i].active = true;
    }
}
void moveFrostings()
{
    for (int i = 0; i < MAX_FROSTINGS; i++)
    {
        if (frostings[i].active)
        {
            frostings[i].x -= 30;
            if (frostings[i].x < 0)
            {
                frostings[i].x = screenlength + rand() % 200;
                frostings[i].y = Y;
            }
        }
    }
}
void checkFrostingCollection()
{
    for (int i = 0; i < MAX_FROSTINGS; i++)
    {
        if (frostings[i].active)
        {
            if (X + playerWidth > frostings[i].x && X < frostings[i].x + 30 && Y + (playerHeight + coordinateJump) > frostings[i].y && (Y + coordinateJump) < frostings[i].y + 30)
            {
                frostings[i].active = false;
                totalFrostingCollected++;
                if (doubleFrostingsEffect)
                {
                    totalFrostingCollected++;
                }
                if (musicOn & !importantSoundsOn)
                {
                    PlaySound(TEXT("Candy-Rush/SoundEffect/coin-collision-sound-342335.wav"), NULL, SND_FILENAME | SND_ASYNC);
                    // iPlaySound("Candy-Rush/SoundEffect/coin-collision-sound-342335.wav", false);
                }
                printf("Coin collected at (%d, %d)! Total: %d\n", frostings[i].x, frostings[i].y, totalFrostingCollected);
            }
        }
        else
        {
            ++frostingTime;
        }
        rosteringFrostings();
    }

    score = second + totalFrostingCollected;
}
void rosteringFrostings()
{

    for (int i = 0; i < MAX_FROSTINGS; i++)
    {

        if (!frostings[i].active)
        {
            frostings[i].x = rand() % screenlength + X + 10;
            frostings[i].y = Y + rand() % 200;
            frostings[i].active = true;
        }
    }
}
void drawFrostings()
{
    for (int i = 0; i < MAX_FROSTINGS; i++)
    {
        if (frostings[i].active)
        {
            iShowImage(frostings[i].x, frostings[i].y, frosting[frostings[i].type]);
        }
    }
}

void setSpeedUpPower()
{
    speedUp.x = 1300 + 1000;
    speedUp.y = Y + rand() % 200;
    speedUp.width = 60;
    speedUp.height = 90;
    speedUp.active = true;
}
void rosteringSpeedUpPower()
{
    int x = rand() % 4;
    if (x == 1)
    {

        speedUp.x = 1300 + 1000;
        speedUp.y = Y + rand() % 200;
        speedUp.width = 60;
        speedUp.height = 90;
        speedUp.active = true;
    }
}

void moveSpeedUpPower()
{
    speedUp.x -= 50;
    if (speedUp.x < 0)
    {
        speedUp.active = false;
        speedUp.x = 1300 + 1000;
    }
}
void gainSpeedUpPower()
{
    if ((X < speedUp.x + speedUp.width && X + playerWidth > speedUp.x) && ((Y + coordinateJump) < speedUp.y + speedUp.height && (Y + coordinateJump) + playerHeight > speedUp.y))

    {
        speedUp.active = false;
        speedUpEffect = true;
        speed = speed - 80;
        drawHUD();

        if (musicOn)
        {
            importantSoundsOn = true;
            PlaySound(TEXT("Candy-Rush/SoundEffect/powerUp.wav"), NULL, SND_FILENAME | SND_ASYNC);
            // iPlaySound("Candy-Rush/SoundEffect/powerUp.wav", false);
        }
        importantSoundsOn = false;
    }
}

void setDoubleFrostingPower()
{
    doubleFrostings.x = 1300 + 1000;
    doubleFrostings.y = Y + rand() % 200;
    doubleFrostings.width = 146;
    doubleFrostings.height = 130;
    doubleFrostings.active = true;
}
void rosteringDoubleFrostingPower()
{
    int x = rand() % 4;
    if (x == 1)
    {

        doubleFrostings.x = 1300 + 1000;
        doubleFrostings.y = Y + rand() % 200;
        doubleFrostings.width = 146;
        doubleFrostings.height = 130;
        doubleFrostings.active = true;
    }
}

void moveDoubleFrostingPower()
{
    doubleFrostings.x -= 50;
    if (doubleFrostings.x < 0)
    {
        doubleFrostings.active = false;
        doubleFrostings.x = 1300 + 1000;
    }
}
void gainDoubleFrostingPower()
{
    if ((X < doubleFrostings.x + doubleFrostings.width && X + playerWidth > doubleFrostings.x) && ((Y + coordinateJump) < doubleFrostings.y + doubleFrostings.height && (Y + coordinateJump) + playerHeight > doubleFrostings.y))
    {

        doubleFrostings.active = false;
        doubleFrostingsEffect = true;

        if (musicOn)
        {
            importantSoundsOn = true;
            PlaySound(TEXT("Candy-Rush/SoundEffect/powerUp.wav"), NULL, SND_FILENAME | SND_ASYNC);
            // iPlaySound("Candy-Rush/SoundEffect/powerUp.wav", false);
        }
        importantSoundsOn = false;
    }
}



void charAnimations()
{
    attackIdx++;
    if (attackIdx >= 3)
        attackIdx = 0;
    enemyRunidx++;
    if (enemyRunidx >= 7)
        enemyRunidx = 0;
    idleIdx++;
    if (idleIdx >= 4)
        idleIdx = 0;

    runIdx++;
    if (runIdx >= 6)
        runIdx = 0;

    jumpUpIdx++;
    if (jumpUpIdx >= 5)
        jumpUpIdx = 4;

    jumpDownIdx++;
    if (jumpDownIdx >= 8)
        jumpDownIdx = 7;
}

void hurtAnim()
{
    if (charHurt)
    {
        hurtIdx++;
        if (hurtIdx >= 3)
        {
            hurtIdx = 0;
            charHurt = false;
        }
    }
}

void frostingAnim()
{
    frostingIdx++;
    if (frostingIdx >= 7)
        frostingIdx = 0;
}
void generatePowerup()
{
    rosteringSpeedUpPower();
    rosteringDoubleFrostingPower();
}
void generateBarriers()
{
    generateObstacle();
    generateEnemy();
    charAnimations();
}

void allfrosting()
{
    frostingAnim();
    moveFrostings();
    rosteringFrostings();
}
void movePowerups()
{

    moveSpeedUpPower();
    moveDoubleFrostingPower();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    loadResources();
    srand(time(0));

    setObstacle();
    setEnemy();
    speed = -25;

    setSpeedUpPower();
    SetFrostings();
    setDoubleFrostingPower();

    iSetTimer(100, generateBarriers);
    iSetTimer(300, generatePowerup);
    iSetTimer(100, movePowerups);
    iSetTimer(500, hurtAnim);

    iSetTimer((100), moveEnemy);

    iSetTimer(1000, changeTimer);

    iSetTimer(5, jumping);

    iSetTimer(100, allfrosting);
    iInitializeSound();
    bgSoundIdx = iPlaySound("Candy-Rush/SoundEffect/playthroughmusic.wav", true, 50);
    iInitialize(screenlength, screenwidth, "Candy-Rush");

    glutMainLoop();

    return 0;
}
