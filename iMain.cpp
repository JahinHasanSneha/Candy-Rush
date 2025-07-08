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

        iShowImage(0, 0,"Candy-Rush/UI/HowToPlayNew2.png");
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

    // Immunity time
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
            // PlaySound(TEXT("Accessory/Sound_bites/Jump_sound.wav"),NULL,SND_FILENAME|SND_ASYNC);
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
                standPosition = false;
            }
        }
    }
}

/*-------Static Obstcales Setup and Movement---------*/
void setObstacle()
{
    obs1.obs_x = 1300;
    obs1.obs_y = 75;
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
            /*if (musicOn)
            {
                PlaySound(TEXT("Candy-Rush/SoundEffect/playthroughmusic.mp3"), NULL, SND_FILENAME | SND_ASYNC);
            }
*/
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
}

/*----------Reaper------------------------*/
void setEnemy()
{
    enemy.x = 1300 + 300;
    enemy.y = 75;
    enemy.width = 100;
    enemy.height = 129;
}
void generateEnemy()
{
    int x = rand() % 2;
    if (x == 1)
    {
        if (enemyDeadTimer > 50)
        {
            enemy.active = true;
            enemy.width = 100;
            enemy.height = 129;
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
        enemy.x = 1300 + 300;
        enemy.width = 100;
        enemy.height = 129;
    }
}
void checkEnemyCollision()
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
                    PlaySound(TEXT("SoundEffect/deadly-strike-352458.mp3"), NULL, SND_FILENAME | SND_ASYNC);
                }
            }
            else if (second > 10)
            {
                // printf("Enemy detected!\n");
                enemy.active = false;
                ++collisionNumber;
                if (musicOn)
                {
                    PlaySound(TEXT("SoundEffect/drop-sound-effect-240899.mp3"), NULL, SND_FILENAME | SND_ASYNC);
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
            if (X + playerWidth > frostings[i].x && X < frostings[i].x + 30 && Y + (playerHeight + coordinateJump) > frostings[i].y && (Y + coordinateJump) < frostings[i].y + 30)
            {
                frostings[i].active = false;
                totalFrostingCollected++;
                if (doubleFrostingsEffect)
                {
                    totalFrostingCollected++;
                }
                //   if (musicOn & !importantSoundsOn)
                //   {
                //      PlaySound(TEXT("SoundEffect/coin-collision-sound-342335.mp3"), NULL, SND_FILENAME | SND_ASYNC);
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
  
      
