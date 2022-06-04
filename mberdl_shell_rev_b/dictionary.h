/*
* This file contains the dictionary array which is 
* an array of Word structs that hold words that could be
* potential secret words. You may add or remove from the Word
* struct as you see fit for your own implementation.
* You should add more potential secret words to the dictionary.
*/

struct Word {
   char* letters;
   int counts[5];
   char unique[5];
} word;  


Word hard[10] = {
    {"speed", {1,1,2,1,0}, {'s','p', 'e', 'd', '!'}},
    {"crane", {1,1,1,1,1}, {'c', 'r', 'a', 'n', 'e'}},
    {"oasis", {1,1,2,1,0}, {'o','a', 's', 'i', '!'}},
    {"fable", {1,1,1,1,1}, {'f','a', 'b', 'l', 'e'}},
    {"sabre", {1,1,1,1,1}, {'s','a', 'b', 'r', 'e'}},
    {"ducat", {1,1,1,1,1}, {'d','u', 'c', 'a', 't'}},
    {"tares", {1,1,1,1,1}, {'t','a', 'r', 'e', 's'}},
    {"adieu", {1,1,1,1,1}, {'a','d', 'i', 'e', 'u'}},
    {"carom", {1,1,1,1,1}, {'c','a', 'r', 'o', 'm'}},
    {"jazzy", {1,1,2,1,0}, {'j','a', 'z', 'y', '!'}}
    };
Word medium[10] = {
    {"earth", {1,1,1,1,1}, {'e', 'a', 'r', 't', 'h'}},
    {"there", {1,1,2,1,0}, {'t', 'h', 'e', 'r', '!'}},
    {"afoul", {1,1,1,1,1}, {'a', 'f', 'o', 'u', 'l'}},
    {"where", {1,1,2,1,0}, {'w', 'h', 'e', 'r', '!'}},
    {"drink", {1,1,1,1,1}, {'d', 'r', 'i', 'n', 'k'}},
    {"avoid", {1,1,1,1,1}, {'a', 'v', 'o', 'i', 'd'}},
    {"dream", {1,1,1,1,1}, {'d', 'r', 'e', 'a', 'm'}},
    {"admit", {1,1,1,1,1}, {'a', 'd', 'm', 'i', 't'}},
    {"afoot", {1,1,2,1,0}, {'a', 'f', 'o', 't', '!'}},
    {"blind", {1,1,1,1,1}, {'b', 'l', 'i', 'n', 'd'}}
    };
Word easy[10] = {
    {"apple", {1,2,1,1,0}, {'a', 'p', 'l', 'e', '!'}},
    {"basis", {1,1,2,1,0}, {'b', 'a', 's', 'i', '!'}},
    {"adult", {1,1,1,1,1}, {'a', 'd', 'u', 'l', 't'}},
    {"beach", {1,1,1,1,1}, {'b', 'e', 'a', 'c', 'h'}},
    {"hello", {1,1,2,1,0}, {'h', 'e', 'l', 'o', '!'}},
    {"award", {2,1,1,1,0}, {'a', 'w', 'r', 'd', '!'}},
    {"anger", {1,1,1,1,1}, {'a', 'n', 'g', 'e', 'r'}},
    {"agent", {1,1,1,1,1}, {'a', 'g', 'e', 'n', 't'}},
    {"blame", {1,1,1,1,1}, {'b', 'l', 'a', 'm', 'e'}},
    {"error", {1,3,1,0,0}, {'e', 'r', 'o', '!', '!'}}
    };