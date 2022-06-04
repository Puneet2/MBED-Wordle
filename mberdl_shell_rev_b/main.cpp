//=================================================================
// The main program file.
//
// Copyright 2022 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <stdlib.h>

// Project includes
#include "globals.h"
#include "hardware.h"
#include "graphics.h"
#include "keyboard.h"


//some LED's to use for debugging.
DigitalOut myled1(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED3);
DigitalOut myled4(LED4);
int gamePlay = 0;


void set_random_seed();

/*
* This function handles the main logic of the game. You should
* initialize the hardware in this function, make calls to 
* functions that update the keyboard and your guess of 
* the word. 
*/
int main()
{
    int guesses = 0;
    int highScore = 6;
    int returnSelect =5;
    int play = 1;
    while(play){
    play = 0;
    GameInputs inputs; 
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    pc.printf("Program Starting\n");
    //led1 hardware initialization
    
    myled1=1;  
    Timer t;
    int dt; // delta time
    
/* Put code here to initialize the game state:
   1) you will need to use a psuedo random number generator such as
     rand() to randomly select a goal word from the dictionary.
     The random function needs to be seeded before you call rand(),
     otherwise, rand() will always generate the same series of numbers.
     Call the function set_random_seed -- you need to complete its
     definition below.*/
    set_random_seed();
    uLCD.color(WHITE);
    init_keyboard(gamePlay);
    uLCD.color(GREEN);
    /*
   2) call init_keyboard() and show start screen
   
   3) initialize any other game state that you add.
*/
    
    
/* Insert code into this game loop to complete its implementation:
*/  
    returnSelect = 5;
    while(1){
        t.start(); //start a timer
        draw_lower_status(); //draw the lower status bar
        uLCD.color(WHITE);
        inputs = read_inputs(); //read the inputs of the game
        if(inputs.ay>0.5 || !inputs.b3){
            moveleft();
            }
        if(inputs.ay<-0.5 || !inputs.b4){
            moveright();
            }
        if(!inputs.b1){
            wait_ms(500);
            returnSelect = select_letter();
            if(returnSelect == 5){
                guesses++;
            }
            }
        if(!inputs.b2){
            wait_ms(500);
            remove_letter();
            }
        if(returnSelect == 0 || returnSelect == 1){
            break;
            }
        
        
        /*
        your code here, make decisions based on those inputs, update the keyboard
        make selections, update words etc.
        */
        
        t.stop();
        dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
        
        }
        if(guesses < highScore && returnSelect !=0 ){
            highScore = guesses;
            }
        else if(guesses == 0 ){
            highScore = 1;
            }
        uLCD.locate(0,15);
        uLCD.color(WHITE);
        uLCD.printf(" HIGH SCORE: %d", highScore);
        while(1){
            inputs = read_inputs();
            if(!inputs.b1){
                play = 1;
                guesses = 0; 
                break;
                }
            if(!inputs.b2){
                play = 0;
                guesses = 0;
                break;
                }
            }
    }
    returnSelect = 5;
    uLCD.cls();
}

/* This should be called in the main function above.
*
* This function sets the random seed for the game using srand(seed).
* One incomplete way to do this is given below: start a Timer and sample it
* to get a seed. The problem is that the same exact time will be read
* every time you reset the mbed.  You need to add code to introduce
* variability into when the timer is stopped.  An easy way to do this
* is to get the user to press a push button to stop the timer at a random
* time.  You can print a prompt to the screen to ask the user to push
* any button to start, then run an infinite while loop that waits for a push 
* button press to break. The Timer is then stopped and read and elapsed time
* used as the seed. (This requires using read_inputs() into a GameInputs variable.)
*/
void set_random_seed() {
    Timer t;
    t.start(); // start the timer
    wait_ms(200);
    
    
    
    GameInputs inputs = read_inputs();
    while(button2){
        if(!button4){
            gamePlay = 3; // hard
            break;
            }
        if(!button3){
            gamePlay = 1;
            break;
            }
        if(!button1){
            gamePlay = 2;
            break;
            }
    uLCD.cls();
    uLCD.color(WHITE);
    uLCD.locate(0,5);
    uLCD.printf(" Hold button 1 for"); 
    uLCD.locate(0,6);
    uLCD.printf("      Easy"); 
    uLCD.locate(0,7);
    uLCD.printf(" Hold button 3 for");
    uLCD.locate(0,8);
    uLCD.printf("     Regular"); 
    uLCD.locate(0,9);
    uLCD.printf(" Hold button 4 for");
    uLCD.locate(0,10);
    uLCD.printf("      Hard"); 
    draw_w();
    wait_ms(350);
     draw_o();
     wait_ms(350);
      draw_r();
      wait_ms(350);
       draw_d();
       wait_ms(350);
        draw_l();
        wait_ms(350);
         draw_e();
         wait_ms(700);
        
        }
        wait_ms(300);
    // add code here
    uLCD.cls();
    t.stop();  //  end the timer
    int seed = t.read_ms(); //read the number of milliseconds elapsed between the start and stop
    srand(seed); // use elapsed time as the seed
    
    //uLCD.printf("seed: %d\n", seed); // TEMP: delete this
}
// ===User implementations end===
