#include "keyboard.h"
#include "dictionary.h"
#include "doubly_linked_list.h"
#include <string>



DLinkedList* keyboard_list;
LLNode* currentLetter;
Word *words;
int count1 = 0;
Timer time1;
char guess[5];
int countSelect = 0;


int compareChar(void* input1, void* input2){
    if(*(char*)input1 == *(char*)input2){
        return 1;
    }
    else{
        return 0;
    }
}


void init_keyboard(int gamePlay)
{
    keyboard_list = create_dlinkedlist(compareChar); //creats dll
    int wordInd = rand() % 10;
    if(gamePlay == 1){words = &easy[wordInd]; }// picks random wordv
    if(gamePlay == 2){words = &medium[wordInd];} // picks random word
    if(gamePlay == 3){words = &hard[wordInd];} // picks random word
    time1.start(); // starts timer
    int i;
    char* letter;
    for(i = 0; i<26; i++){  // for loop to add all letters
        //char letter = i;
        letter = (char*)(malloc(sizeof(char)));
        *letter = 'a'+i;
        insertTail(keyboard_list, letter); // inserts letters so its a,b,c,d...
    }
    currentLetter = getHead(keyboard_list); // sets curr node
    
    // prints keyboard
    ////////////////////////////////////////////////////////////////////////////
    uLCD.locate(8, 14.75);
    uLCD.text_bold(1);
    uLCD.set_font_size(3,3);
    uLCD.printf("%c", *(char *)getData(currentLetter));
    uLCD.set_font_size(1,1);
    uLCD.text_bold(0);
    uLCD.locate(7,15);
    if(getPrev(currentLetter)==NULL){
        uLCD.printf("%c", *(char *)getData(getTail(keyboard_list)));
        }
        else{uLCD.printf("%c", *(char *)getData(getPrev(currentLetter)));}
    uLCD.locate(9,15);
    if(getNext(currentLetter)==NULL){
        uLCD.printf("%c", *(char *)getData(getHead(keyboard_list)));
        }
    else{
        uLCD.printf("%c", *(char *)getData(getNext(currentLetter)));
    }
    ///////////////////////////////////////////////////////////////////////////
    
    // to help with debugging and speed of tests, (prints out the word)
/*
    uLCD.locate(0, 13);
    uLCD.printf("%c", words->letters[0]);
    uLCD.locate(1, 13);
    uLCD.printf("%c", words->letters[1]);
    uLCD.locate(2, 13);
    uLCD.printf("%c", words->letters[2]);
    uLCD.locate(3, 13);
    uLCD.printf("%c", words->letters[3]);
    uLCD.locate(4, 13);
    uLCD.printf("%c", words->letters[4]);
  */
}


void moveleft()
{
    if(getPrev(currentLetter) != NULL){
        currentLetter = getPrev(currentLetter);
    }
    else{
        currentLetter = getTail(keyboard_list);
    }
    /// reprints the keyboard
    uLCD.locate(8, 14.75);
    wait_ms(200);
    uLCD.text_bold(1);
    uLCD.set_font_size(3,3);
    uLCD.printf("%c", *(char *)getData(currentLetter));
    uLCD.set_font_size(1,1);
    uLCD.text_bold(0);
    uLCD.locate(7,15);
    if(getPrev(currentLetter)==NULL){
        uLCD.printf("%c", *(char *)getData(getTail(keyboard_list)));
        }
        else{uLCD.printf("%c", *(char *)getData(getPrev(currentLetter)));}
    uLCD.locate(9,15);
    if(getNext(currentLetter)==NULL){
        uLCD.printf("%c", *(char *)getData(getHead(keyboard_list)));
        }
    else{
        uLCD.printf("%c", *(char *)getData(getNext(currentLetter)));
    }
}


void moveright()
{
    if(getNext(currentLetter) != NULL){
        currentLetter = getNext(currentLetter);
    }
    else{
        currentLetter = getHead(keyboard_list);
    }
    
    //reprints the keyboard
    uLCD.locate(8, 14.75);
    wait_ms(200);
    uLCD.text_bold(1);
    uLCD.set_font_size(3,3);
    uLCD.printf("%c", *(char *)getData(currentLetter));
    uLCD.set_font_size(1,1);
    uLCD.text_bold(0);
    uLCD.locate(7,15);
    if(getPrev(currentLetter)==NULL){
        uLCD.printf("%c", *(char *)getData(getTail(keyboard_list)));
        }
        else{uLCD.printf("%c", *(char *)getData(getPrev(currentLetter)));}
    uLCD.locate(9,15);
    if(getNext(currentLetter)==NULL){
        uLCD.printf("%c", *(char *)getData(getHead(keyboard_list)));
        }
    else{
        uLCD.printf("%c", *(char *)getData(getNext(currentLetter)));
    }
}


int select_letter()
{   
    if(countSelect<5){
        guess[countSelect] = *(char*)getData(currentLetter);
        uLCD.locate(6 + countSelect, 4 + count1);
        uLCD.printf("%c",guess[countSelect]);
        countSelect++;
    }
    if (countSelect == 5){
        int check = check_word();
        countSelect = 0;
        return check;
    }
    return 20;
}


void remove_letter()
{  
   if(countSelect>0){
    uLCD.locate(5 + countSelect, 4+count1);
    uLCD.printf(" ");
        countSelect--;
   }
}


int check_word()
{
    if(count1<5){
    int i;
    int correct = 0;
    uLCD.locate(1, 0);
    uLCD.printf("Correct Letters:");
    for(i = 0; i<5; i++){
        if(compareChar(&guess[i], &words->letters[i])){ //letters match 
            uLCD.color(GREEN);
            uLCD.locate(6 + i, 4 + count1);
            uLCD.printf("%c", guess[i]);
            correct++;
        }
        else{ // letters do not match
            int notExists = 1;
            int k;
            for(k = 0; k<5; k++){
                if(compareChar(&guess[i], &words->unique[k])){
                    uLCD.locate(6+k,2);
                    uLCD.color(WHITE);
                    uLCD.printf("%c", words->unique[k]);
                    uLCD.color(0xFFFF00);
                    uLCD.locate(6 + i, 4 + count1);
                    uLCD.printf("%c", guess[i]);
                    notExists = 0;
                }
            }
            if(notExists){ // no match what so ever delete the letter from keyboard
                delete_letter_keyboard(guess[i]);
                currentLetter = getHead(keyboard_list);
                uLCD.color(RED);
                uLCD.locate(6 + i, 4 + count1);
                uLCD.printf("%c",guess[i]);
            }
        } 
    }
    uLCD.color(WHITE);
    if(correct == 5){ // they won
        won();
        return 1;
    }
    // reprints keyboard
    ///////////////////////////////////////////////////////////////////////////
    uLCD.color(WHITE);
    uLCD.locate(8, 14.75);
    uLCD.text_bold(1);
    uLCD.set_font_size(3,3);
    uLCD.printf("%c", *(char *)getData(currentLetter));
    uLCD.set_font_size(1,1);
    uLCD.text_bold(0);
    uLCD.locate(7,15);
    if(getPrev(currentLetter)==NULL){
        uLCD.printf("%c", *(char *)getData(getTail(keyboard_list)));
        }
        else{uLCD.printf("%c", *(char *)getData(getPrev(currentLetter)));}
    uLCD.locate(9,15);
    if(getNext(currentLetter)==NULL){
        uLCD.printf("%c", *(char *)getData(getHead(keyboard_list)));
        }
    else{
        uLCD.printf("%c", *(char *)getData(getNext(currentLetter)));
    }
    ///////////////////////////////////////////////////////////////////////////
    count1++;
}
else{// they ran out of guesses and lost
    lost();
    return 0;
}
return 5;
}

void delete_letter_keyboard(char letter){
    LLNode* curr = getHead(keyboard_list);
    int found = 0;
    while(curr){
        if(compareChar(getData(curr),&letter)){
            found = 1;
            break;
        }
        curr = getNext(curr);
    }
    if(found){
        deleteNode(keyboard_list,curr);
    }
}

void won(){
        uLCD.color(WHITE);
        uLCD.cls();
        uLCD.locate(1,5);
        draw_y();
        draw_o2();
        draw_u();
        draw_w2();
        draw_o3();
        draw_n();
        time1.stop();
        int readTime = time1.read();
        int min = readTime/60;
        int sec = readTime%60;
        uLCD.printf(" Time it took:");
        uLCD.locate(1,6);
        uLCD.printf("Min: %d  Sec: %d ", min, sec);
        uLCD.locate(0,8);
        uLCD.color(WHITE);
        uLCD.printf("  DO YOU WANT TO");
        uLCD.locate(0,9);
        uLCD.printf("   PLAY AGAIN");
        uLCD.locate(0,10);
        uLCD.printf("PRESS BUTTON 1 FOR");
        uLCD.locate(0,11);
        uLCD.color(GREEN);
        uLCD.printf("      YES");
        uLCD.locate(0,12);
        uLCD.color(WHITE);
        uLCD.printf("PRESS BUTTON 2 FOR");
        uLCD.locate(0,13);
        uLCD.color(RED);
        uLCD.printf("       NO");
        currentLetter = NULL;
        destroyList(keyboard_list);
        count1 = 0;
        countSelect = 0;
    }

void lost(){
    uLCD.color(WHITE);
    uLCD.cls();
    uLCD.color(RED);
    uLCD.locate(0, 3);
    uLCD.printf(" YOU HAVE LOST AS"); 
    uLCD.locate(0, 4);
    uLCD.printf(" YOU HAVE RUN OUT");
    uLCD.locate(0, 5);
    uLCD.printf("   OF GUESSES");
    uLCD.locate(0,6);
    uLCD.color(WHITE);
    uLCD.printf("  DO YOU WANT TO");
    uLCD.locate(0,7);
    uLCD.printf("   PLAY AGAIN");
    uLCD.locate(0,8);
    uLCD.printf("PRESS BUTTON 1 FOR");
    uLCD.locate(0,9);
    uLCD.color(GREEN);
    uLCD.printf("      YES");
    uLCD.locate(0,10);
    uLCD.color(WHITE);
    uLCD.printf("PRESS BUTTON 2 FOR");
    uLCD.locate(0,11);
    uLCD.color(RED);
    uLCD.printf("       NO");
    count1 = 0;
    countSelect = 0;
    currentLetter = NULL;
    destroyList(keyboard_list);
    }