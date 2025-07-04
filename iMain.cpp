#include "iGraphics.h"
#include <Windows.h>
#include <time.h>
#include <stdlib.h>

#define screenwidth 731
#define screenlength 1300

bool runState;
int gameState = -1;
int loading = 0;
bool musicOn = true;
int collisionNumber = 0;
bool char_hurt = false;
bool importantSoundsOn = false;

int X = 350;
int Y = 75;
int playerWidth = 88, playerHeight = 107;

char bc[52][50] = {"Background\"Background\\tile000.png", "Background\\tile001.png", "Background\\tile002.png", "Background\\tile003.png",
                   "Background\\tile004.png", "Background\\tile005.png", "Background\\tile006.png", "Background\\tile007.png", "Background\\tile008.png",
                   "Background\\tile009.png", "Background\\tile010.png", "Background\\tile011.png", "Background\\tile0012.png", "Background\\tile013.png",
                   "Background\\tile014.png", "Background\\tile015.png", "Background\\tile016.png", "Background\\tile017.png", "Background\\tile018.png",
                   "Background\\tile019.png", "Background\\tile020.png", "Background\\tile021.png", "Background\\tile022.png", "Background\\tile023.png",
                   "Background\\tile024.png", "Background\\tile025.png", "Background\\tile026.png", "Background\\tile027.png", "Background\\tile028.png",
                   "Background\\tile029.png", "Background\\tile030.png", "Background\\tile031.png", "Background\\tile032.png", "Background\\tile033.png",
                   "Background\\tile034.png", "Background\\tile035.png", "Background\\tile035.png", "Background\\tile036.png", "Background\\tile037.png",
                   "Background\\tile038.png", "Background\\tile039.png", "Background\\tile040.png", "Background\\tile041.png", "Background\\tile042.png",
                   "Background\\tile043.png", "Background\\tile044.png", "Background\\tile045.png", "Background\\tile046.png", "Background\\tile047.png",
                   "Background\\tile048.png", "Background\\tile049.png"};

// char back[][];
char staticBack[50] = {"Background\\BackGround.png"};

char idle[4][60] = {"Assets\\Pink_Monster_Idle.png\\Pink_Monster_Idle_4_1.png",
                    "Assets\\Pink_Monster_Idle.png\\Pink_Monster_Idle_4_2.png",
                    "Assets\\Pink_Monster_Idle.png\\Pink_Monster_Idle_4_3.png",
                    "Assets\\Pink_Monster_Idle.png\\Pink_Monster_Idle_4_4.png"};
char run[6][50] = {"Asset\\Pink_Monster_Run\\tile000.png"};
char jump_sprite[8][50] = {"Candy-Rush\\Assets\\Pink_Monster_Run\\tile000.png",
                           "Candy-Rush\\Assets\\Pink_Monster_Run\\tile001.png", "Candy-Rush\\Assets\\Pink_Monster_Run\\tile002.png", "Candy-Rush\\Assets\\Pink_Monster_Run\\tile003.png", "Candy-Rush\\Assets\\Pink_Monster_Run\\tile004.png", "Candy-Rush\\Assets\\Pink_Monster_Run\\tile005.png", "Candy-Rush\\Assets\\Pink_Monster_Run\\tile006.png", "Candy-Rush\\Assets\\Pink_Monster_Run\\tile007.png"};
char hurt[4][50] = {"Assets\\Pink_Monster_Hurt\\tile000.png", "Assets\\Pink_Monster_Hurt\\tile001.png", "Assets\\Pink_Monster_Hurt\\tile002.png", "Assets\\Pink_Monster_Hurt\\tile003.png"};

char attack[1][40] = {"Assets\\Pink_Monster_Attack\\tile000.png"};
// char enemy[][] = {};
char enemyRun[8][35] = {"Assests\\Enemy\\EnemyRun000.png", "Assests\\Enemy\\EnemyRun001.png", "Assests\\Enemy\\EnemyRun002.png", "Assests\\Enemy\\EnemyRun003.png", "Assests\\Enemy\\EnemyRun004.png", "Assests\\Enemy\\EnemyRun005.png", "Assests\\Enemy\\EnemyRun006.png", "Assests\\Enemy\\EnemyRun007.png"};

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

// char powerUpSound[] = " ";

char frostingSound[60] = "SoundEffect\\coin-collision-sound-342335.mp3";

#define MAX_FROSTINGS 3
int frostingIdx=0;
int totalFrostingCollected = 0;
int frostingTime = 0;
char frosting[40][35] = {"Frostings//cupcake.png", "Frostings//donut.png", "Frostings//lolipop.png", "Frostings//starCandy.png", "Frostings//sugarCandy.png", "Frostings//toffee.png"};

struct Frosting
{
    int x;
    int y;
    bool active;
};
struct Frosting frostings[MAX_FROSTINGS];

char welcomePage[30] = "UI//WelcomeNew.png";
char menuPage[30] = "UI//MenuNew.png";
char howToPlay[30] = "UI//HowToPlayNew2.png";
char musicControl[30] = "UI//MusicControlNew.png";
char about[20] = "UI//About.png";
char gameOver[20] = "UI//GameOver.png";
char purple[30] = "Button//purple.png";
char tealBlue[30] = "Button//tealBlue.png";
char pink[30] = "Button//pink.png";
char gems[30] = "ExtraLabels//Gems.png";
char heart[30] = "ExtraLabels//heart.png";
char coin[30] = "ExtraLabels//coin.png";

bool StandPosition = true;
int standCount = 0;
bool jump = false;
bool jumpUp = false;
bool jumpDown = false;
int jumpLimit = 130;
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

// char cauldron[35]="Accessory\\PowerUps\\cauldron.bmp";
char magicPotion[40] = "ExtraLabels\\MagicPotion.png";

char doubleFrostingPowerup[50] = "Candy-Rush\\ExtraLabels\\Diamond.png";
char doubleFrostingEffectPic[50] = "ExtraLabels\\double_coins.png";

bool speedUpEffect = false;
int speedUpEffectActivatorTimer= 0;
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

struct background
{
    int x;
    int y;
};
struct background bc1[80];
int bcIndex = 0;
int idleIdx = 0;
int runIdx = 0;
int jumpUpIdx = 0;
int jumpDownIdx = 0;
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
        iShowImage(1190, screenwidth - 38, purple);

        iSetColor(255, 255, 255);
        sprintf(sec, "Time: %d", second);
        iText(1160, screenwidth - 80, sec, GLUT_BITMAP_HELVETICA_10);
        iShowImage(1051, screenwidth - 52, coin);
        iSetColor(255, 255, 255);
        sprintf(point, "Score: %d", score);
        iText(1207, screenwidth - 41, point, GLUT_BITMAP_HELVETICA_10);
    }
}
// gameState -1: Welcome Page
// gameState 0 : MenuPage
// gameState 1 : Actual Game
// gameState 2 : Gameover
// gameState 3 : How to Play
// gameState 4 : Options
//gameState 5: About

char GameOverScene[50] = "UI\\GameOver.png";
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
    iShowImage(0, 0, GameOverScene);
    gameState = 2;
}
void iMouse(int button, int state, int mx, int my)
{
    // printf("x=%d y=%d\n",mx,my);
    // printf("%d\n",gameState);
    if (gameState == 0) // Menu
    {
        // PLAY BUTTON
        if (mx >= 553 && mx <=757 && my >= (screenwidth - 220) && my <= (screenwidth - 126))
        {
            
            gameState = 1;
        }
        
        // How to play page
        else if (mx >= 538 && mx <= 776 && my >= (screenwidth - 355) && my <= (screenwidth - 275))
        {
           
            gameState = 3;
        }
        // Options page
        else if (mx >= 559 && mx <= 762 && my >= (screenwidth - 468) && my <= (screenwidth - 380))
        {
            // printf("Options!!\n");
            gameState = 4;
        }
        else if (mx >= 526 && mx <=790 && my >= (screenwidth - 589) && my <= (screenwidth - 505))
        {
            // printf("About!!\n");
            gameState = 5;

        }
    }

    if (gameState == 1) // Game
    {//play
    }
    if (gameState == 2) // Gameover
    {
        if (mx >= 526 && mx <= 776 && my >= (screenwidth - 623) && my <= (screenwidth - 547))
        {
            // printf("Let's Go back to Menu\n");
            gameState = 0;
        }
    }
    if (gameState == 5) // About
    {
        if (mx >= 536 && mx <= 810 && my >= (screenwidth - 601) && my <= (screenwidth - 505))
        {
            gameState = 0;
        }
    }
    if (gameState == 3) // how to play
    {
        if (mx >= 461 && mx <= 884 && my >= (screenwidth - 629) && my <= (screenwidth - 573))
        {
            gameState = 0;
        }
    }
    // gameState -1: Welcome Page
// gameState 0 : MenuPage
// gameState 1 : Actual Game
// gameState 2 : Gameover
// gameState 3 : How to Play
// gameState 4 : Options
//gameState 5: About

    if (gameState == 4) // options
    {
        if (mx >= 580 && mx <= 749 && my >= (screenwidth - 244) && my <= (screenwidth - 172))
        {
            musicOn = true;
        }
        if (mx >= 580 && mx <= 74 && my >= (screenwidth - 348) && my <= (screenwidth - 273))
        {
            musicOn = false;
        }
        if (mx >=550 && mx <= 785 && my >= (screenwidth - 596) && my <= (screenwidth - 510))
        {
            gameState=0;
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
void iSpecialKeyboard(unsigned char key)
{
    // place your codes for other keys here
    if (key == GLUT_KEY_UP)
    {
        gameState = 1;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        gameState = 0;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        StandPosition = false;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        StandPosition = true;
    }
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
        iShowImage(0, 0, welcomePage);
        loading++;
        if (loading > 10)
        {
            gameState = 0;
            loading = 0;
        }
    }
    else if (gameState == 0)
    {
        iShowImage(0, 0, menuPage);
        score = 0;
        totalFrostingCollected = 0;
        second = 0;
        int collisionNumber = 0;
        speedUpEffect = false;
        doubleFrostingsEffect = false;
    }
    else if (gameState == 1)
    {
        func_timers();
        int i, j, k;
        for (i = 0; i < 50; i++)
        {
            iShowImage(bc1[i].x, bc1[i].y, bc[i]);
        }
        if (speedUpEffect || second <= 10)
        {
            iShowImage(X - 58, Y + coordinateJump, magicPotion);
        }
        if (doubleFrostingsEffect)
        {
            iShowImage(1200, screenwidth - 120, doubleFrostingEffectPic);
        }
        iText(1163, 704, "Score: ", GLUT_BITMAP_HELVETICA_10);
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
                    iShowImage(X, Y + coordinateJump, jump_sprite[jumpUpIdx]);
                }
                else
                {
                    iShowImage(X, Y + coordinateJump, jump_sprite[jumpDownIdx]);
                }
            }
        }
        else if (char_hurt)
        {

            iShowImage(X, Y, hurt[hurtIdx]);
        }
        else if (kill)
        {
            iShowImage(X, Y, attack[attackIdx]);
        }
        else
        {
            if (!StandPosition || second >= 4)
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
            /*if (obs1.active)
            {
                iShowImage(obs1.obs_x, obs1.obs_y, enemySprite[0]);
            }*/
        }

        if (speedUp.active)
        {

            iShowImage(speedUp.x, speedUp.y, magicPotion);
        }
        if (doubleFrostings.active)
        {
            // printf("Show me double coins\n");
            iShowImage(doubleFrostings.x, doubleFrostings.y, doubleFrostingPowerup);
        }

        drawFrostings();
        drawTimer();

        // Display Total Coins Collected
        char frostingText[50];
        sprintf(frostingText, "%d", totalFrostingCollected);
        iShowImage(685, screenwidth - 43, tealBlue);
        iText(695, screenwidth - 40, frostingText, GLUT_BITMAP_HELVETICA_10);
        iShowImage(540, screenwidth - 43, gems);

        // Check for coin collection
        checkFrostingCollection();

        char collisionText[50];
        sprintf(collisionText, "Life : %d", 3 - collisionNumber);
        iShowImage(25, screenwidth - 3, pink);
        iText(54, screenwidth - 30, collisionText, GLUT_BITMAP_HELVETICA_10);
        if ((3 - collisionNumber) == 3)
        {
            iShowImage(23, screenwidth - 80, heart);
            iShowImage(75, screenwidth - 80, heart);
            iShowImage(123, screenwidth - 80, heart);
        }
        else if ((3 - collisionNumber) == 2)
        {
            iShowImage(23, screenwidth - 80, heart);
            iShowImage(75, screenwidth - 80, heart);
        }
        else if ((3 - collisionNumber) == 1)
        {
            iShowImage(23, screenwidth - 80, heart);
        }

        gainSpeedUpPower();
        gainDoubleFrostingPower();
        checkEnemyCollision();
        moveObstacle();
        checkCollision();
    }

    // Gameover Scene
    else if (gameState == 2)
    {
        printf(" Score: %d", score);
        GameOver();
        showChar();
    }
    // gameState -1: Welcome Page
    // gameState 0 : MenuPage
    // gameState 1 : Actual Game
    // gameState 2 : Gameover
    // gameState 3 : How to Play
    // gameState 4 : Options

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

        iShowImage(0, 0, howToPlay);
    }

    // Options
    else if (gameState == 4)
    {

        iShowImage(0, 0, musicControl);
        /* if (musicOn)
         {
             iShowBMP2(screenlength / 2 - 120, screenwidth / 2 - 100, musicOnpic, 0);
         }
         else
         {
             iShowBMP2(screenlength / 2 - 120, screenwidth / 2 - 100, musicOffpic, 0);
         }*/
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
        if (doubleFrostingsEffectActivatorTimer> 200)
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

/*--------------------Render Background-------------------------*/
void setAll()
{
    int sum = 0;
    for (int i = 0; i < 50; i++)
    {
        bc1[i].y = 0;
        bc1[i].x = sum;
        sum += 48;
    }
}
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
    }
}
void jumping()
{
    if (jump)
    {
        if (musicOn)
        {
            // PlaySound(TEXT("Accessory\\Sound_bites\\Jump_sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
        }

        if (jumpUp)
        {
            coordinateJump += 10;
            if (coordinateJump >= jumpLimit)
            {
                jumpUp = false;
            }
        }
        else
        {
            jumpDown = true;
            coordinateJump -= 10;
            if (coordinateJump < 0)
            {
                jump = false;
                coordinateJump = 0;
                jumpDown = false;
                StandPosition = false;
            }
        }
    }
}

/*-------Static Obstcales Setup and Movement---------*/
void set_obstacle()
{
    obs1.obs_x = 1300;
    obs1.obs_y = 75;
    obs1.obs_width = 64;
    obs1.obs_height = 61 ;
}
void generate_obstacle()
{
    int x = rand() % 2;
if (x == 1 && collisionTimeOut > 50)
    {
        obs1.active = true;
        collisionTimeOut = 0;
       
    }
}
void move_obstacle()
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
            /*if (musicOn)
            {
                PlaySound(TEXT("Candy-Rush\\SoundEffect\\playthroughmusic.mp3"), NULL, SND_FILENAME | SND_ASYNC);
            }
*/
            char_hurt = true;
            if (char_hurt)
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
}

/*----------Reaper------------------------*/
void set_enemy()
{
    enemy.x = 1300 + 300;
    enemy.y = 75;
    enemy.width = 100;
    enemy.height = 129;
}
void generate_enemy()
{
    int x = rand() % 2;
    if (x == 1)
    {
        if (enemyDeadTimer > 50)
        {
            enemy.active = true;
            enemy.width = 100;
         enemy.height = 129;
           enemyDeadTimer= 0;
        }

      
    }
}
void move_enemy()
{
    enemy.x -= 30;
    if (enemy.x < 0)
    {
        enemy.active = false;
        enemy.x = 1300 + 300;
        enemy.width = 100;
        enemy.height = 129;
    }
}
void check_enemy_Collision()
{
    if (enemy.active)
    {
        enemy.width = 100;
        enemy.height = 129;
        // printf("Entered checkCollsion\n");
        if ((enemy.x - X) < 150)
        {
            if (kill)
            {
                enemy.active = false;
                kill = false;
               /* if (musicOn)
                {
                    PlaySound(TEXT("Candy-Rush\SoundEffect\deadly-strike-352458.mp3"), NULL, SND_FILENAME | SND_ASYNC);
                }*/
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
                    PlaySound(TEXT("SoundEffect\\deadly-strike-352458.mp3"), NULL, SND_FILENAME | SND_ASYNC);
                }
            }
            else if (second > 10)
            {
                // printf("Enemy detected!\n");
                enemy.active = false;
                ++collisionNumber;
                if (musicOn)
                {
                    PlaySound(TEXT("SoundEffect\\drop-sound-effect-240899.mp3"), NULL, SND_FILENAME | SND_ASYNC);
                }
                char_hurt = true;
                if (char_hurt)
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
       frostings[i].x = screenlength + rand() % 400;
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
            if (X + playerWidth > frostings[i].x && X < frostings[i].x + 30 && Y + (playerHeight + coordinateJump) > frostings[i].y && (Y + coordinateJump) <frostings[i].y + 30)
            {
                frostings[i].active = false;
                totalFrostingCollected++;
                if (doubleFrostingsEffect)
                {
                    totalFrostingCollected++;
                }
             //   if (musicOn & !importantSoundsOn)
             //   {
              //      PlaySound(TEXT("SoundEffect\\coin-collision-sound-342335.mp3"), NULL, SND_FILENAME | SND_ASYNC);
              //  }
                // printf("Coin collected at (%d, %d)! Total: %d\n", coins[i].x, coins[i].y, totalCoinsCollected);
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
    speedUp.x-=50;
    if(speedUp.x<0)
    {
        speedUp.active = false;
        speedUp.x = 1300+ 1000;
    }
}
void gainSpeedUpower()
{
    if((X <speedUp.x + speedUp.width && X+playerWidth>speedUp.x) && ((Y+coordinateJump)<speedUp.y+speedUp.height && (Y+coordinateJump)+playerHeight>speedUp.y))

     {  // printf("I am immune!\n");
        speedUp.active = false;
        speedUpEffect = true;

        if (musicOn)
        {
            importantSoundsOn = true;
          //  PlaySound(TEXT("Accessory\\Sound_bites\\Powerup_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
void GainDoubleFrostingPower()
{
    if ((X < doubleFrostings.x + doubleFrostings.width && X + playerWidth > doubleFrostings.x) && ((Y + coordinateJump) < doubleFrostings.y + doubleFrostings.height && (Y + coordinateJump) + playerHeight > doubleFrostings.y))
    {

        // printf("I am double!\n");
        doubleFrostings.active = false;
        doubleFrostingsEffect = true;

        if (musicOn)
        {
            importantSoundsOn= true;
           // PlaySound(TEXT("Accessory\\Sound_bites\\Powerup_sound.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
       importantSoundsOn= false;
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
}

void showChar()
{
    iSetColor(0, 0, 0);
    // iText(400,500,"Enter your Name: ",GLUT_BITMAP_HELVETICA_18);
    // iRectangle(495,450,160,30);
    iText(screenlength / 2 - 100 + 50, 460, str1, GLUT_BITMAP_HELVETICA_18);
}

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




        
      
void char_animations()
{

    idleIdx++;
    if (idleIdx >= 6)
        idleIdx = 0;

    runIdx++;
    if (runIdx >= 8)
        runIdx = 0;

    jumpUpIdx++;
    if (jumpUpIdx >= 6)
        jumpUpIdx = 5;

    jumpDownIdx++;
    if (jumpDownIdx >= 11)
        jumpDownIdx = 10;

    attackIdx++;
    if (attackIdx >= 10)
        attackIdx = 0;

    /*-----------Reaper-----------*/
    enemyRunidx++;
    if (enemyRunidx >= 7)
       enemyRunidx = 0;
}

// Hurt_anim_ for character!!!
void hurt_anim()
{
    if (char_hurt)
    {
        hurtIdx++;
        if (hurtIdx >= 3)
        {
            hurtIdx = 0;
            char_hurt = false;
        }
    }
}

void coin_anim()
{
    frostingIdx++;
    if ( frostingIdx >= 8)
        frostingIdx = 0;
}
void generate_barriers()
{
    generate_obstacle();
    generate_enemy();
    char_animations();
}
void generate_powerup()
{
    rosteringSpeedUpPower(); // respawn them
    rosteringDoubleFrostingPower();
}
void allfrosting()
{
    coin_anim();
    moveFrostings();
    rosteringFrostings();
}
void move_powerups()
{

   moveSpeedUpPower();
    moveDoubleFrostingPower();
}

int main()
{
    srand(time(0));
    setAll();
    set_obstacle();
    set_enemy();

    // Powerups setup
    setSpeedUpPower();
    setDoubleFrostingPower();

    iSetTimer(100, generate_barriers);
    iSetTimer(300, generate_powerup);
    iSetTimer(100, move_powerups); // call them in int main
    iSetTimer(500, hurt_anim);
    iSetTimer(100, change);

    iSetTimer((100), move_enemy);

    iSetTimer(1000, changeTimer);

    iSetTimer(5, jumping);

    // Coins
    SetFrostings();
    iSetTimer(100, allfrosting);

    iInitialize(screenlength, screenwidth, "Candy-Rush");
    return 0;
}
