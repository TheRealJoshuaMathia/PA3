
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct duration
{
    int minutes;
    int seconds;
} Duration;

typedef struct record 
{
    char artist[50];
    char album[50];
    char song[50];
    char genre[50];
    Duration songLength;
    int timesPlayed;
    int rating;
} Record;

typedef struct node 
{
    Record data;
    struct node *pPrev;
    struct node *pNext;
} Node;

// Help Functions

void dislayMenu();
int choice(void);
int strToInt(char *str);
Node *MakeNode(Record newData);
int insertAtFront(Node **pList, Record newData);
void clearStream(char str[100]);
int sortArtist(Node **pList);
int sortAlbum(Node **pList);
int sortRating(Node **pList);
int sortTimesPlayed(Node **pList);
int countList(Node **pList);
void runProgram(FILE *infile, FILE *outfile, Node **pList, int choice);
int getChoice(void);

//Functions that perform menu Tasks

int load(FILE *infile, Node **pList); //1
int store(FILE *outfile, Node **pList); //2
void display(Node **pList); //3
int insert(Node **pList); //4
int delete(Node **pList); //5
int edit(Node **pList); //6
int sort(Node **pList); //7
int rate(Node **pList); //8
void play(Node **pList); //9
void shuffle(Node **pList); //10
void exit(FILE *infile, Node **pList); // 11