#include "iGraphics.h"
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <direct.h>
#include "iSound.h"

#define screenwidth 731
#define screenlength 1300

int collisionNumber = 0;
bool charHurt = false;
bool importantSoundsOn = false;
bool runState = false;
int gameState = -1;
int loading = 0;
bool musicOn = true;

int playerWidth = 88, playerHeight = 140;
int X = 350;
int Y = 135;
Image bg;
int speed = -20;
void loadResources()
{
	iLoadImage(&bg, "Candy-Rush/Background/BackGround.png");
	
}

char bc[50][51] = {
    "Candy-Rush/Background/tile000.png",
    "Candy-Rush/Background/tile001.png",
    "Candy-Rush/Background/tile002.png",
    "Candy-Rush/Background/tile003.png",
    "Candy-Rush/Background/tile004.png",
    "Candy-Rush/Background/tile005.png",
    "Candy-Rush/Background/tile006.png",
    "Candy-Rush/Background/tile007.png",
    "Candy-Rush/Background/tile008.png",
    "Candy-Rush/Background/tile009.png",
    "Candy-Rush/Background/tile010.png",
    "Candy-Rush/Background/tile011.png",
    "Candy-Rush/Background/tile012.png",
    "Candy-Rush/Background/tile013.png",
    "Candy-Rush/Background/tile014.png",
    "Candy-Rush/Background/tile015.png",
    "Candy-Rush/Background/tile016.png",
    "Candy-Rush/Background/tile017.png",
    "Candy-Rush/Background/tile018.png",
    "Candy-Rush/Background/tile019.png",
    "Candy-Rush/Background/tile020.png",
    "Candy-Rush/Background/tile021.png",
    "Candy-Rush/Background/tile022.png",
    "Candy-Rush/Background/tile023.png",
    "Candy-Rush/Background/tile024.png",
    "Candy-Rush/Background/tile025.png",
    "Candy-Rush/Background/tile026.png",
    "Candy-Rush/Background/tile027.png",
    "Candy-Rush/Background/tile028.png",
    "Candy-Rush/Background/tile029.png",
    "Candy-Rush/Background/tile030.png",
    "Candy-Rush/Background/tile031.png",
    "Candy-Rush/Background/tile032.png",
    "Candy-Rush/Background/tile033.png",
    "Candy-Rush/Background/tile034.png",
    "Candy-Rush/Background/tile035.png",
    "Candy-Rush/Background/tile036.png",
    "Candy-Rush/Background/tile037.png",
    "Candy-Rush/Background/tile038.png",
    "Candy-Rush/Background/tile039.png",
    "Candy-Rush/Background/tile040.png",
    "Candy-Rush/Background/tile041.png",
    "Candy-Rush/Background/tile042.png",
    "Candy-Rush/Background/tile043.png",
    "Candy-Rush/Background/tile044.png",
    "Candy-Rush/Background/tile045.png",
    "Candy-Rush/Background/tile046.png",
    "Candy-Rush/Background/tile047.png",
    "Candy-Rush/Background/tile048.png",
    "Candy-Rush/Background/tile049.png",
};

char back[50][50] = {
    "Candy-Rush/Background/00.png",
    "Candy-Rush/Background/10.png",
    "Candy-Rush/Background/20.png",
    "Candy-Rush/Background/30.png",
    "Candy-Rush/Background/40.png",
    "Candy-Rush/Background/50.png",
    "Candy-Rush/Background/60.png",
    "Candy-Rush/Background/70.png",
    "Candy-Rush/Background/80.png",
    "Candy-Rush/Background/90.png",
    "Candy-Rush/Background/100.png",
    "Candy-Rush/Background/110.png",
    "Candy-Rush/Background/120.png",
    "Candy-Rush/Background/130.png",
    "Candy-Rush/Background/140.png",
    "Candy-Rush/Background/150.png",
    "Candy-Rush/Background/160.png",
    "Candy-Rush/Background/170.png",
    "Candy-Rush/Background/180.png",
    "Candy-Rush/Background/190.png",
    "Candy-Rush/Background/200.png",
    "Candy-Rush/Background/210.png",
    "Candy-Rush/Background/220.png",
    "Candy-Rush/Background/230.png",
    "Candy-Rush/Background/240.png",
    "Candy-Rush/Background/250.png",
    "Candy-Rush/Background/260.png",
    "Candy-Rush/Background/270.png",
    "Candy-Rush/Background/280.png",
    "Candy-Rush/Background/290.png",
    "Candy-Rush/Background/300.png",
    "Candy-Rush/Background/310.png",
    "Candy-Rush/Background/320.png",
    "Candy-Rush/Background/330.png",
    "Candy-Rush/Background/340.png",
    "Candy-Rush/Background/350.png",
    "Candy-Rush/Background/360.png",
    "Candy-Rush/Background/370.png",
    "Candy-Rush/Background/380.png",
    "Candy-Rush/Background/390.png",
    "Candy-Rush/Background/400.png",
    "Candy-Rush/Background/410.png",
    "Candy-Rush/Background/420.png",
    "Candy-Rush/Background/430.png",
    "Candy-Rush/Background/440.png",
    "Candy-Rush/Background/450.png",
    "Candy-Rush/Background/460.png",
    "Candy-Rush/Background/470.png",
    "Candy-Rush/Background/480.png",
    "Candy-Rush/Background/490.png",
};

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
int enemyDeadTimer = 0;
int collisionTimeOut = 0;
int enemyTimeOut = 0;

char powerUpSound[60] = "Candy-Rush/SoundEffect/powerUp.wav";
// char click[70]=""Candy-Rush/SoundEffect/click.wav";

char frostingSound[60] = "Candy-Rush/SoundEffect/coin-collision-sound-342335.wav";

#define MAX_FROSTINGS 3
int frostingIdx = 0;
int totalFrostingCollected = 0;
int frostingTime = 0;
char frosting[45][40] = {"Candy-Rush/Frostings/cupcake.png", "Candy-Rush/Frostings/donut.png", "Candy-Rush/Frostings/lolipop.png", "Candy-Rush/Frostings/starCandy.png", "Candy-Rush/Frostings/sugarCandy.png", "Candy-Rush/Frostings/toffee.png"};

struct Frosting
{
    int x;
    int y;
    bool active;
};
struct Frosting frostings[MAX_FROSTINGS];

char welcomePage[30] = "Candy-Rush/UI/WelcomeNew.png";
char menuPage[30] = "Candy-Rush/UI/MenuNew.png";
char howToPlay[50] = "Candy-Rush/UI/HowToPlayNew2.png";
char musicControl[50] = "Candy-Rush/UI/MusicControlNew.png";
char about[50] = "Candy-Rush/UI/About.png";
char gameOver[50] = "Candy-Rush/UI/GameOver.png";
char purple[50] = "Candy-Rush/Button/purple.png";
char tealBlue[50] = "Candy-Rush/Button/tealBlue.png";
char pink[50] = "Candy-Rush/Button/pink.png";
char gems[50] = "Candy-Rush/ExtraLabels/Gems.png";
char heart[50] = "Candy-Rush/ExtraLabels/heart.png";
char coin[50] = "Candy-Rush/ExtraLabels/coin.png";
char obs[50] = "Candy-Rush/Frostings/Obstacle.png";
char obsIce[50] = "Candy-Rush/Frostings/ObstacleIce.png";
bool standPosition = true;
int standCount = 0;
bool jump = false;
bool jumpUp = false;
bool jumpDown = false;
int jumpLimit = 100;
int coordinateJump = 0;
bool kill = false;
int killTimer = 0;
struct powerUp
{
    int x;
    int y;
    int width;
    int height;
    bool active;
} speedUp, doubleFrostings;

char magicPotion[40] = "Candy-Rush/ExtraLabels/MagicPotion.png";

char doubleFrostingPowerup[50] = "Candy-Rush/ExtraLabels/Diamond.png";
char doubleFrostingEffectPic[50] = "Candy-Rush/ExtraLabels/double_coins.png";

bool speedUpEffect = false;
int speedUpEffectActivatorTimer = 0;
int speedUpEffectDeactivatorTimer = 0;

bool doubleFrostingsEffect = false;
int doubleFrostingsEffectActivatorTimer = 0;
int doubleFrostingsEffectDeactivatorTimer = 0;

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
struct Background bc1[50];
struct Background back1[50];
int bcIndex = 0;
int idleIdx = 0;
int runIdx = 0;
int jumpUpIdx = 0;
int jumpDownIdx = 5;
int hurtIdx = 0;
int attackIdx = 0;

int score = 0;
int second = 0;

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

void func_timers();
// char click[60]=""Candy-Rush/SoundEffect/click.wav";
char sec[10000];
int minute = 0;
int hour = 0;
char hr[1000];
int totalSecond = 0;
char point[10000];

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

char GameOverScene[50] = "UI/GameOver.png";
/*char welcomePage[30] = "UI//WelcomeNew.png";
char menuPage[30] = "UI//MenuNew.png";
char howToPlay[30] = "UI//HowToPlayNew.png";
char musicControl[30] = "UI//MusicControlNew.png";
char about[20] = "UI//About.png";
char gameOver[20] = "UI//GameOver.png";

*/
void GameOver()
{
    iSetColor(128, 128, 128);
    iFilledRectangle(0, 0, screenwidth, screenlength);
    iShowImage(0, 0, "Candy-Rush/UI/GameOver.png");
   /* if (musicOn)
    {
        importantSoundsOn = true;
        iPlaySound("Candy-Rush/SoundEffect/clock-ticking-sound-effect-240503.wav", true, 50);
    }
    importantSoundsOn = false;*/
    gameState = 2;
}
void iMouse(int button, int state, int mx, int my)
{
    // printf("x=%d y=%d\n",mx,my);
    // printf("%d\n",gameState);
    if (gameState == 0) // Menu
    {
        // PLAY BUTTON
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

        // How to play page
        else if (mx >= 511 && mx <= 780 && my >= (screenwidth - 300) && my <= (screenwidth - 203))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            gameState = 3;
        }
        // Options page
        else if (mx >= 538 && mx <= 762 && my >= (screenwidth - 438) && my <= (screenwidth - 335))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            // printf("Options!!\n");
            gameState = 4;
        }
        else if (mx >= 517 && mx <= 785 && my >= (screenwidth - 562) && my <= (screenwidth - 487))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            // printf("Leaderboard\n");
            gameState = 6;
        }
        else if (mx >= 548 && mx <= 751 && my >= (screenwidth - 686) && my <= (screenwidth - 609))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            // printf("About!!\n");
            gameState = 5;
        }
    }

    if (gameState == 1) // Game
    {                   // play
    }
    if (gameState == 2) // Gameover
    {
        if (mx >= 526 && mx <= 776 && my >= (screenwidth - 623) && my <= (screenwidth - 547))
        {
            if (musicOn)
            {
                importantSoundsOn = true;
                PlaySound(TEXT("Candy-Rush/SoundEffect/click.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }
            importantSoundsOn = false;
            // printf("Let's Go back to Menu\n");
            gameState = 0;
        }
    }
    if (gameState == 5) // About
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
    if (gameState == 3) // how to play
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
    // gameState 6:Leaderboard

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

/*
    function iKeyboard() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
    */
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
        // printf("I am ready to kill\n");
    }
    if (gameState == 0)
    {
        if (key == 'L' || key == 'l')
        {
            gameState = 3; // Correctly update gameState to 3
        }
    }
    // if (gameState == 2)
    // {

    //    takeInput(key); // Allow input handling in gameState 2
    // }
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
int bgSoundIdx = -1; //
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
    }
    // place your codes for other keys here
    /* if (key == GLUT_KEY_UP)
     {
         gameState = 1;
     }
     else if (key == GLUT_KEY_DOWN)
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
     }*/
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
        iShowImage(0, 0, "Candy-Rush/UI/MenuNew.png");

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
       /* int i;
        for (i = 0; i < 50; i++)
        {
            // iShowImage(bc1[i].x, bc1[i].y, bc[i]);
            iShowImage(back1[i].x, back1[i].y, back[i]);
        }*/
        if (speedUpEffect)
        {
            iShowImage(X - 58, Y + coordinateJump, "Candy-Rush/ExtraLabels/MagicPotionEffect.png");
        }
        if (doubleFrostingsEffect)
        {
            iShowImage(1150, screenwidth - 150, "Candy-Rush/ExtraLabels/double_coins.png");
        }
        // iText(1163, 704, "Score: ", GLUT_BITMAP_HELVETICA_18);
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
            // printf("Show me double coins\n");
            iShowImage(doubleFrostings.x, doubleFrostings.y, "Candy-Rush/ExtraLabels/Diamond.png");
        }

        drawFrostings();
        drawTimer();

        // Display Total Coins Collected
        char frostingText[50];
        sprintf(frostingText, "%d", totalFrostingCollected);
        iShowImage(600, screenwidth - 150, "Candy-Rush/Button/tealBlue.png");
        iText(695, screenwidth - 80, frostingText, GLUT_BITMAP_HELVETICA_18);
        iShowImage(540, screenwidth - 150, "Candy-Rush/ExtraLabels/Gems.png");

        // Check for coin collection
        checkFrostingCollection();

        char collisionText[50];
        // sprintf(collisionText, "Life : %d", 3 - collisionNumber);
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
    // Gameover Scene
    if (gameState == 2)
    {
        printf(" Score: %d", score);
        iSetColor(255, 255, 255);
        sprintf(point, "Score: %d", score);
        iText(1038, screenwidth - 80, point, GLUT_BITMAP_HELVETICA_18);

        GameOver();
        showChar();
    }
    // gameState -1: Welcome Page
    // gameState 0 : MenuPage
    // gameState 1 : Actual Game
    // gameState 2 : Gameover
    // gameState 3 : How to Play
    // gameState 4 : Options
    // gameState 5 : about

    // Leaderboard
    /*else if (gameState == 3)
    {
        iShowBMP(0, 0, halloffame);
        readScore();
    }*/

    // How to play
    /*char welcomePage[30] = "UI//WelcomeNew.png";
    char menuPage[30] = "UI//MenuNew.png";
    char howToPlay[30] = "UI//HowToPlayNew.png";
    char musicControl[30] = "UI//MusicControlNew.png";
    char about[20] = "UI//About.png";
    char gameOver[20] = "UI//GameOver.png";

    */

    else if (gameState == 3)
    {

        iShowImage(0, 0, "Candy-Rush/UI/HowToPlayNew2.png");
    }

    // Options
    else if (gameState == 4)
    {

        iShowImage(0, 0, "Candy-Rush/UI/MusicControlNew.png");
        /* if (musicOn)
          {
              iShowBMP2(screenlength / 2 - 120, screenwidth / 2 - 100, musicOnpic, 0);
          }
          else
          {
              iShowBMP2(screenlength / 2 - 120, screenwidth / 2 - 100, musicOffpic, 0);
          }*/
    }
    else if (gameState == 5) // About
    {

        iShowImage(0, 0, "Candy-Rush/UI/About.png");
    }
}

/*----------------Timers to call functions------------*/
void func_timers()
{

    // Attack

    if (kill)
    {
        ++killTimer;
        if (killTimer > 10)
        {
            kill = false;
            killTimer = 0;
        }
    }

    // Reaper
    if (!enemy.active)
    {
        ++enemyDeadTimer;
    }

    // Immunity timer
    if (speedUpEffect)
    {
        ++speedUpEffectActivatorTimer;
        if (speedUpEffectActivatorTimer > 200)
        {
            speedUpEffectActivatorTimer = 0;
        }
    }

    // double coins
    if (doubleFrostingsEffect)
    {
        ++doubleFrostingsEffectActivatorTimer;
        if (doubleFrostingsEffectActivatorTimer > 200)
        {
            doubleFrostingsEffect = false;
            doubleFrostingsEffectActivatorTimer = 0;
        }
    }

    if (!obs1.active)
    {
        ++collisionTimeOut;
    }
}

/*--------------------Render Candy-Rush/Background-------------------------*/
void setAll()
{
    int sum = 0;
    for (int i = 0; i < 50; i++)
    {
        back1[i].y = 0;
        back1[i].x = sum; // bc1[i].y = 0;
        // bc1[i].x = sum;
        sum += 26;
    }
}/*
void change()
{
    if (gameState == 1)
    {
        for (int i = 0; i < 50; i++)
        {
            bc1[i].x -= 26;
          if (bc1[i].x < 0)
           {
                bc1[i].x = 1300 - 26;
            }
        }
            //back1[i].x -= 26;
          //  if (back1[i].x < 0)
           // {
             //   back1[i].x = 1300 - 26;
            //}
        //}
    //}
 /* if (gameState == 1)
    {
        for (int i = 0; i < 29; i++)
        {
            back1[i].x -= 48;
            if (back1[i].x < 0)
            {
                back1[i].x = 1300 - 48;
            }
        }
    }
}*/
 void jumping()
 {
     if (jump)
     {
         // if (musicOn)
         //{
         //   PlaySound(TEXT("Candy-Rush/SoundEffect/pixel-jump-319167.wav"),NULL,SND_FILENAME|SND_ASYNC);
         // }

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

 /*-------Static Obstcales Setup and Movement---------*/
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
     if (obs1.active && second > 10)
     {
         // printf("Entered checkCollsion\n");
         if ((X < obs1.obs_x + obs1.obs_width && X + playerWidth > obs1.obs_x) && ((Y + coordinateJump) < obs1.obs_y + obs1.obs_height && (Y + coordinateJump) + playerHeight > obs1.obs_y) && !speedUpEffect)
         {
             // printf("Collision detected!\n");
             obs1.active = false;
             ++collisionNumber;
             if (musicOn)
             {
                 PlaySound(TEXT("Candy-Rush/SoundEffect/drop-sound-effect-240899.wav"), NULL, SND_FILENAME | SND_ASYNC);
             }

             charHurt = true;
             if (charHurt)
             {
                 // printf("Initiate hurt anim\n");
             }
             // printf("Collision no: %d\n",collision_number);
             // gameState = 0;
             if (collisionNumber > 3)
             {
                 gameState = 2;
                 collisionNumber = 0;
                 // score=0;
                 // second=0;
             }
             // printf("Collision detected!\n");
         }
     }
     // generate_obstacle();

     // generate_obstacle();
 }

 /*----------Reaper------------------------*/
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
         // printf("Entered checkCollsion\n");
         if ((enemy.x - X) < 120)
         {
             if (kill)
             {
                 enemy.active = false;
                 kill = false;
                 if (musicOn)
                 {
                     PlaySound(TEXT("Candy-Rush/SoundEffect/deadly-strike-352458.wav"), NULL, SND_FILENAME | SND_ASYNC);
                 }
             }
         }
         if ((X < enemy.x + enemy.width && X + playerWidth > enemy.x) && ((Y + coordinateJump) < enemy.y + enemy.height && (Y + coordinateJump) + playerHeight > enemy.y) && !speedUpEffect)
         {
             if (kill)
             {
                 enemy.active = false;
                 kill = false;
                 if (musicOn)
                 {
                     PlaySound(TEXT("SoundEffect/deadly-strike-352458.wav"), NULL, SND_FILENAME | SND_ASYNC);
                 }
             }
             else if (second > 10)
             {
                 // printf("Enemy detected!\n");
                 enemy.active = false;
                 ++collisionNumber;
                 if (musicOn)
                 {
                     PlaySound(TEXT("Candy-Rush/SoundEffect/drop-sound-effect-240899.wav"), NULL, SND_FILENAME | SND_ASYNC);
                 }
                 charHurt = true;
                 if (charHurt)
                 {
                     // printf("Initiate hurt anim\n");
                 }
                 // printf("Collision no: %d\n",collision_number);
                 // gameState = 0;
                 if (collisionNumber > 3)
                 {
                     gameState = 2;
                     collisionNumber = 0;
                 }
             }
         }
     }
     // generate_obstacle();
 }

 /*-------------------------Coin Collection------------------------*/
 void SetFrostings()
 {
     for (int i = 0; i < MAX_FROSTINGS; i++)
     {
         frostings[i].x = screenlength + rand() % 300;
         ;
         frostings[i].y = Y + rand() % 200;
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
             iShowImage(frostings[i].x, frostings[i].y, frosting[frostingIdx]);
         }
     }
 }

 /*-------------PowerUp functions------------*/

 // No one can hurt me now!
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

         // printf("Collision Active!!\n");
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

     { // printf("I am immune!\n");
         speedUp.active = false;
         speedUpEffect = true;

         if (musicOn)
         {
             importantSoundsOn = true;
             PlaySound(TEXT("Candy-Rush/SoundEffect/powerUp.wav"), NULL, SND_FILENAME | SND_ASYNC);
         }
         importantSoundsOn = false;
     }
 }

 // Double your beautiful, shiny Coins
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

         // printf("I am double!\n");
         doubleFrostings.active = false;
         doubleFrostingsEffect = true;

         if (musicOn)
         {
             importantSoundsOn = true;
             PlaySound(TEXT("Candy-Rush/SoundEffect/powerUp.wav"), NULL, SND_FILENAME | SND_ASYNC);
         }
         importantSoundsOn = false;
     }
 }

 /*--------------------LeaderBoard----------------------------------------------*/
 /*
 void readScore()
 {
     FILE *fp = fopen("Score.txt", "r");
     fseek(fp, 0, SEEK_SET);
     if (fp == NULL)
     {
         printf("The file can't be found! We lost our legends. Sad.\n");
         return;
     }

     for (int i = 0; i < 5; i++)
     {
         int res = fscanf(fp, "%s %d", high_score[i].name, &high_score[i].score);
         if (res != 2)
         {
             printf("Invalid data format at line %d in Score.txt. Fix it please.\n", i + 1);
             fclose(fp);
             return;
         }
     }

     fclose(fp);

     for (int i = 0; i < 5; i++)
     {
         char showName[50];
         char showScore[10];

         sprintf(showName, "%s", high_score[i].name);
         sprintf(showScore, "%d", high_score[i].score);

         iSetColor(255, 255, 255);
         iText(550, 590, "NAME", GLUT_BITMAP_HELVETICA_18);
         iText(800, 590, "SCORE", GLUT_BITMAP_HELVETICA_18);
         iText(550, 550 - 50 * i, showName, GLUT_BITMAP_HELVETICA_18);
         iText(800, 550 - 50 * i, showScore, GLUT_BITMAP_HELVETICA_18);
     }
 }

 void newHighscore()
 {
     FILE *fp;
     fp = fopen("Score.txt", "r");
     fseek(fp, 0, SEEK_SET);
     for (int i = 0; i < 5; i++)
     {
         fscanf(fp, "%s %d", high_score[i].name, &high_score[i].score);
     }
     fseek(fp, 0, SE  // printf("X=%d, Y=%d, playerwidth=%d, Playerheight=%d\n Coordinate jump=%d\n",X,Y,playerWidth,playerHeight,coordinatejump);
         // printf("reaper.x=%d, reaper.y=%d, reaperwidth=%d, reaperheight=%d\n",reaper.x,reaper.y,reaper.width,reaper.height);
     }
     if (gameState == 2) // Gameover
     {
    EK_SET);
     fclose(fp);

     if (newscore)
     {
         for (int i = 0; i < 5; i++)
         {
             if (high_score[i].score < score)
             {

                 high_score[4].score = score;
                 strcpy(high_score[4].name, str1);

                 for (int j = 0; j < 5; j++)
                 {
                     for (int k = 4; k > j; k--)
                     {
                         if (high_score[k].score > high_score[k - 1].score)
                         {
                             // score
                             int tempScore = high_score[k - 1].score;
                             high_score[k - 1].score = high_score[k].score;
                             high_score[k].score = tempScore;

                             // name
                             char tempName[50];
                             strcpy(tempName, high_score[k - 1].name);
                             strcpy(high_score[k - 1].name, high_score[k].name);
                             strcpy(high_score[k].name, tempName);
                         }
                     }
                 }

                 fp = fopen("Score.txt", "w");

                 for (int i = 0; i < 5; i++)
                 {
                     fprintf(fp, "%s %d\n", high_score[i].name, high_score[i].score);
                 }
                 fclose(fp);

                 newscore = false;
                 break;
             }
         }
     }
 }*/
 char str1[100];
 void showChar()
 {
     iSetColor(0, 0, 0);
     // iText(400,500,"Enter your Name: ",GLUT_BITMAP_HELVETICA_18);
     // iRectangle(495,450,160,30);
     iText(screenlength / 2 - 100 + 50, 460, str1, GLUT_BITMAP_HELVETICA_18);
 }
 /*
 void takeInput(unsigned char key)
 {
     if (key == '\b')
     {
         if (len > 0)
         {
             len--;
             str1[len] = '\0';
         }
     }
     else if (key == '\r') // Press Enter to go to Menu Page
     {
         newHighscore();
         gameState = 0;
     }
     else if (len < 29 && key != '\b' && key != '\r')
     {
         str1[len] = key;
         len++;
         str1[len] = '\0';
     }
 }

 // To reset names especially when they're not included in the highscores chart
 void resetNameInput()
 {
     str1[0] = '\0';
     len = 0;
 }*/

 /*
     function iMouseMove() is called when the user presses and drags the mouse.
     (mx, my) is the position where the mouse pointer is.
     */

 void charAnimations()
 {

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

     attackIdx++;
     if (attackIdx >= 3)
         attackIdx = 0;

     /*-----------Reaper-----------*/
     enemyRunidx++;
     if (enemyRunidx >= 7)
         enemyRunidx = 0;
 }

 // Hurt_anim_ for character!!!
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

 void coinAnim()
 {
     frostingIdx++;
     if (frostingIdx >= 7)
         frostingIdx = 0;
 }
 void generateBarriers()
 {
     generateObstacle();
     generateEnemy();
     charAnimations();
 }
 void generatePowerup()
 {
     rosteringSpeedUpPower(); // respawn them
     rosteringDoubleFrostingPower();
 }
 void allfrosting()
 {
     coinAnim();
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
     setAll();
     setObstacle();
     setEnemy();

     // Powerups setup
     setSpeedUpPower();
     SetFrostings();
     setDoubleFrostingPower();

     iSetTimer(100, generateBarriers);
     iSetTimer(300, generatePowerup);
     iSetTimer(100, movePowerups); // call them in int main
     iSetTimer(500, hurtAnim);
     //iSetTimer(100, change);

     iSetTimer((100), moveEnemy);

     iSetTimer(1000, changeTimer);

     iSetTimer(5, jumping);

     // Coins

     iSetTimer(100, allfrosting);
     iInitializeSound();
     bgSoundIdx = iPlaySound("Candy-Rush/SoundEffect/playthroughmusic.wav", true, 50);
     iInitialize(screenlength, screenwidth, "Candy-Rush");

     glutMainLoop();

     return 0;
 }
