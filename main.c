
#include "PA3.h"

int main(void)
{
    FILE *infile = NULL, *outfile = NULL;
    Node *pList = NULL;

    srand((unsigned int)(time NULL));

    infile = fopen("musicPlaylist.csv", "r");

    int choice = 0;

    while(choice !=11)
    {
        choice = getChoice();
        runProgram(infile, outfile, &pList, choice);
    }

    fclose(infile);

    return 0;
}


