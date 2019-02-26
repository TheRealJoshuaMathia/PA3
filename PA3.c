#include <PA3.h>

//Help Functions

void displayMenu(void) 
{
	printf("\t\t1.  Load");
	printf("\t\t2.  Store");
	printf("\t\t3.  Display");
	printf("\t\t4.  Insert");
	printf("\t\t5.  Delete");
	printf("\t\t6.  Edit");
	printf("\t\t7.  Sort");
	printf("\t\t8.  Rate");
	printf("\t\t9.  Play");
	printf("\t\t10. Shuffle");
	printf("\t\t11. Exit");
}

Node *MakeNode(Record newData)
{
    Node *pMem = NULL;

    pMem = (Node *) malloc(sizeof(Node));
    pMem->data = newData;

    pMem->pNext = NULL;
    pMem->pPrev = NULL;

    return pMem;
}

int insertAtFront(Node **pList, Record newData)
{
    int result = 0;
    Node *pNew = NULL;

    pNew = MakeNode(newData);

    if (*pList == NULL) {

        pList = pNew;
        result = 1;
    }

    else if (pList != NULL)
    {
        pNew->pNext = pList;
        (*pList)->pPrev = pNew;
        *pList = pNew;
        result = 1;
    }

    return result;
}

void clearStr(char str[100])
{
	strcpy(str, "");
}

int countList(Node **pList)
{
	int count = 0;
	Node *pNew = NULL;

	pNew = *pList;

	while (pNew != NULL)
	{
		count++; 
		pNew = pNew->pNext; 
	}

	return count;
}

int convertInt(char *str)
{
	int num = atoi(str);

	return num;
}

int choosechoice(void)
{
	int choice;

	do
	{
		system("cls");
		displayMenu();
		printf("Please enter your desired choice: ");
		scanf("%d", &choice);
	} while ((choice < 1) || (choice > 11));

	return choice;
}

void command(FILE* infile, FILE* outfile, Node **pList, int choice)
{
	int result = 0;
	switch (choice)
	{
		case 1: 
			result = load(infile, pList);
			break;
		case 2: 
			result = store(outfile, pList);
			break;
		case 3: 
			display(pList);
			break;
		case 4: 
			result = insert(pList);
			break;
		case 5: 
			result = delete(pList);
			break;
		case 6: 
			result = edit(pList);
			break;
		case 7: 
			result = sort(pList);
			break;
		case 8: 
			result = rate(pList);
			break;
		case 9: 
			play(pList);
			break;
		case 10: 
			shuffle(pList);
			break;
		case 11: 
			result = store(outfile, pList);
			break;
		default:
			printf("An Error Occured! Please try again.\n"); 
			break;
	}
	if (result && choice != 11) 
	{
		printf("Execution was successfully!\n");
		system("pause");
	}
	else if (choice != 11)
	{
		printf("An Error Occured! Please try again.\n"); 

	}
}

int load(FILE *infile, Node **pList)
{
	int result = 0;
	Record songData;
	char line[100];
    char delim[2] = ",";

	while (!feof(infile))
	{
		fgets(line, 100, infile); 
		if (line[0] == '"')
		{
			strcpy(songData.artist, strtok(line, "\""));
			strcpy(songData.album, strtok(NULL, delim));
			strcpy(songData.song, strtok(NULL, delim));
			strcpy(songData.genre, strtok(NULL, delim));
			songData.songLength.minutes = atoi(strtok(NULL, ":"));
			songData.songLength.seconds = atoi(strtok(NULL, delim));
			songData.timesPlayed = atoi(strtok(NULL, delim));
			songData.rating = atoi(strtok(NULL, delim));
		}
		else if (line[0] != '\n' && line[0] != '\0')
		{
			
			strcpy(songData.artist, strtok(line, delim));
			strcpy(songData.album, strtok(NULL, delim));
			strcpy(songData.song, strtok(NULL, delim));
			strcpy(songData.genre, strtok(NULL, delim));
			songData.songLength.minutes = atoi(strtok(NULL, ":"));
			songData.songLength.seconds = atoi(strtok(NULL, delim));
			songData.timesPlayed = atoi(strtok(NULL, delim));
			songData.rating = atoi(strtok(NULL, delim));
		}

		if (line[0] != '\n' && line[0] != '\0') result = insertAtFront(pList, songData);

		clearStream(line);
	}

	return result;
}

int store(FILE *outfile, Node **pList)
{
	int result = 0;
	Node *pNew = NULL;

	pNew = *pList;

	outfile = fopen("musicPlayList.csv", "w");
	while (pNew != NULL)
	{
		fprintf(outfile, "\"%s\",%s,%s,%s,%d:%d,%d,%d\n", pNew->data.artist, pNew->data.album, pNew->data.song, pNew->data.genre,
			    pNew->data.songLength.minutes, pNew->data.songLength.seconds, pNew->data.timesPlayed, pNew->data.rating);
		result = 1;

		pNew = pNew->pNext;
	}
	fclose(outfile);
	return result;
}

void display(Node **pList)
{
	int choice = 0;
	Node *pNew = NULL;

	pNew = *pList;

	do
	{
		system("cls");
		printf("1. Print all records.\n");
		printf("2. Print all records that match an artist.\n\n");
		printf("Please enter you're desired choice: ");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 2);

	if (choice == 1)
	{
		system("cls");
		while (pNew != NULL)
		{
			printf("%s\n%s\n%s\n%s\n%d:%d\n%d\n%d\n", pNew->data.artist, pNew->data.album, pNew->data.song, pNew->data.genre,
				pNew->data.songLength.minutes, pNew->data.songLength.seconds, pNew->data.timesPlayed, pNew->data.rating);
			printf("*****************************************\n");

			pNew = pNew->pNext;
		}
	}
	else if (choice == 2)
	{
        char artist[50];

		printf("\nPlease enter the artist's name:");
		scanf(" %[^\n]s", &artist);

		system("cls");

		while (pNew != NULL)
		{
			if (strcmp(pNew->data.artist, artist) == 0)
			{
				printf("%s, %s, %s, %s, %d:%d, %d, %d\n", pNew->data.artist, pNew->data.album, pNew->data.song, pNew->data.genre,
					pNew->data.songLength.minutes, pNew->data.songLength.seconds, pNew->data.timesPlayed, pNew->data.rating);
			}
			pNew = pNew->pNext;
		}
	}
	system("pause");
}

int edit(Node **pList)
{
	char song[50], edit[50];
	Node *pNew = NULL;
	int attribute, edit1, edit2;
	int result = 0;

	pNew = *pList;

	system("cls");
	printf("Enter the title of the song you want to edit: ");
	scanf(" %[^\n]s", &song);

	while (pNew != NULL && strcmp(pNew->data.song, song) != 0)
	
	{
		pNew = pNew->pNext;
	}
	if (pNew != NULL)
	{
		do 
        {
			system("cls");
			printf("Which attribute would you like to edit?\n");
			printf("1. Artist\n");
			printf("2. Album\n");
			printf("3. Title\n");
			printf("4. Genre\n");
			printf("5. Song Length\n");
			printf("6. Times Played\n");
			printf("7. Rating\n");
			scanf("%d", &attribute);
		} while (attribute < 1 || attribute > 8);

		switch (attribute)
		{
		case 1: 
			printf("Enter the new artist's name: ");
			scanf(" %[^\n]s", &edit);
			strcpy(pNew->data.artist, edit);
			result = 1;
			break;
		case 2: 
			printf("Enter the new album title : ");
			scanf(" %[^\n]s", &edit);
			strcpy(pNew->data.album, edit);
			result = 1;
			break;
		case 3: 
			printf("Enter the new song title: ");
			scanf(" %[^\n]s", &edit);
			strcpy(pNew->data.song, edit);
			result = 1;
			break;
		case 4: 
			printf("Enter the new genre catagory: ");
			scanf(" %[^\n]s", &edit);
			strcpy(pNew->data.genre, edit);
			result = 1;
			break;
		case 5: 
			printf("Enter the nesong (will enter seconds next): ");
			scanf("%d", &edit1);
			printf("Enter the new seconds of song: ");
			scanf("%d", &edit2);
			pNew->data.songLength.minutes = edit;
			pNew->data.songLength.seconds = edit2;
			result = 1;
			break;
		case 6: 
			printf("Enter the new amount of plays: ");
			scanf("%d", &edit1);
			pNew->data.timesPlayed = edit;
			result = 1;
			break;
		case 7: 
			printf("Enter the new rating: ");
			scanf("%d", &edit1);
			pNew->data.rating = edit;
			result = 1;
			break;
		}
	}
	return result;
}

int rate(Node **pList)
{
	int result = 0;
	char song[50]; 
	int edit; 
	Node *pNew = NULL;

	pNew = *pList;

	printf("Enter the name of the song you want to rate: ");
	scanf(" %[^\n]s", &song);

	while (pNew != NULL && strcmp(pNew->data.song, song) != 0)
	{
		pNew = pNew->pNext;
	}

	if (pNew != NULL) 
	{
		do
		{
			system("cls");
			printf("Enter in the new rating: ");
			scanf("%d", &edit);
		} while (edit < 1 || edit > 5);
		pNew->data.rating = edit;
		result = 1;
	}
	

	return result;
}

void play(Node **pList)
{
	Node *pNew = NULL;
	char song[50];

	pNew = *pList;


	printf("Enter the name of the song you would like to play: ");
	scanf(" %[^\n]s", &song);

	while (pNew != NULL && strcmp(pNew->data.song, song) != 0)
	{
		pNew = pNew->pNext;
	}

	while (pNew != NULL) 
	{
		system("cls");
		printf("Now Playing: \n"); 
		printf("%s - %s - %s", pNew->data.song, pNew->data.artist, pNew->data.album);
		Sleep(2000);

		pNew = pNew->pNext;
	}

}

int insert(Node **pList)
{
	int result = 0;
	Record song;

	printf("Adding a new song: \n\n");
	Sleep(500);

	printf("Enter the song's artist: ");
	scanf(" %[^\n]s", &song.artist);
	printf("Enter the song's album title: ");
	scanf(" %[^\n]s", &song.album);
	printf("Enter the song's title: ");
	scanf(" %[^\n]s", &song.song);
	printf("Enter a new song genre: ");
	scanf(" %[^\n]s", &song.genre);

	do {
		printf("Enter the song's length in minutes: ");
		scanf("%d", &song.songLength.minutes);
	} while (song.songLength.minutes <= 0); 

	do {
		printf("Enter the song's length in seconds: ");
		scanf("%d", &song.songLength.seconds);
	} while (song.songLength.seconds <= 0 && song.songLength.seconds > 60);

	do {
		printf("Enter the amount of times the song has been played: ");
		scanf("%d", &song.timesPlayed);
	} while (song.timesPlayed <= 0);

	do {
		printf("Enter the song's rating 1-5: ");
		scanf("%d", &song.rating);
	} while (song.rating <= 0 || song.rating > 5);

	result = insertAtFront(pList, song);

	return result;
}

int sort(Node **pList)
{
	int result = 0;
	int choice = 0;
	

	do {
		system("cls");
		printf("Sort options: \n");
		printf("1. Sort based on artist (A-Z)\n");
		printf("2. Sort based on album title (A-Z)\n");
		printf("3. Sort based on rating (1-5)\n");
		printf("4. Sort based on times played (largest-smallest)\n");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	switch (choice)
	{
		case 1: 
			result = sortArtist(pList);
			break;
		case 2: 
			result = sortAlbum(pList);
			break;
		case 3: 
			result = sortRating(pList);
			break;
		case 4: 
			result = sortPlays(pList);
			break;
		default:
			printf("An Error Occured! Please try again.\n"); 
	}

	return result;
}

int sortArtist(Node **pList)
{
	int result = 0;
	int count = 0;
	Record line;
	Node *pNew = NULL;
	Node *pComp = NULL;

	count = countList(pList);

	for (int i = 0; i < count - 1; i++)
	{
		pNew = *pList;
		pComp = pNew->pNext;

		while (pComp != NULL)
		{
			if (strcmp(pNew->data.artist, pComp->data.artist) > 0)
			{
				line = pNew->data;
				pNew->data = pComp->data;
				pComp->data = line;
				
				result = 1;
			}
			pNew = pNew->pNext;
			pComp = pComp->pNext;
		}
	}
	
	return result;
}

int sortAlbum(Node **pList)
{
	int result = 0;
	int count = 0;
	Record line;
	Node *pNew = NULL;
	Node *pComp = NULL;

	count = countList(pList);

	for (int i = 0; i < count - 1; i++)
	{
		pNew = *pList;
		pComp = pNew->pNext;

		while (pComp != NULL)
		{
			if (strcmp(pNew->data.album, pComp->data.album) > 0)
			{
				line = pNew->data;
				pNew->data = pComp->data;
				pComp->data = line;

				result = 1;
			}
			pNew = pNew->pNext;
			pComp = pComp->pNext;
		}
	}

	return result;
}

int sortRating(Node **pList)
{
	int result = 0;
	int count = 0;
	Record line;
	Node *pNew = NULL;
	Node *pComp = NULL;

	count = countList(pList);

	for (int i = 0; i < count - 1; i++)
	{
		pNew = *pList;
		pComp = pNew->pNext;

		while (pComp != NULL)
		{
			if (pNew->data.rating > pComp->data.rating)
			{
				line = pNew->data;
				pNew->data = pComp->data;
				pComp->data = line;

				result = 1;
			}
			pNew = pNew->pNext;
			pComp = pComp->pNext;
		}
	}

	return result;
}

int sortPlays(Node **pList)
{
	int result = 0;
	int count = 0;
	Record line;
	Node *pNew = NULL;
	Node *pComp = NULL;

	count = countList(pList);

	for (int i = 0; i < count - 1; i++)
	{
		pNew = *pList;
		pComp = pNew->pNext;

		while (pComp != NULL)
		{
			if (pNew->data.timesPlayed < pComp->data.timesPlayed)
			{
				line = pNew->data;
				pNew->data = pComp->data;
				pComp->data = line;

				result = 1;
			}
			pNew = pNew->pNext;
			pComp = pComp->pNext;
		}
	}

	return result;
}

int delete(Node **pList)
{
	int result = 0;
	char song[100];
	Node *pNew = NULL;

	pNew = *pList;

	system("cls");
	printf("Enter the name of the song to delete: ");
	scanf(" %[^\n]s", &song);

	while (pNew != NULL && strcmp(pNew->data.song, song) != 0)
	{
		pNew = pNew->pNext;
	}

	if (pNew != NULL)
	{
		if (pNew->pPrev == NULL)
		{
			*pList = pNew->pNext;
			(*pList)->pNext = NULL;
			free(pNew);
			result = 1;
		}
		else if (pNew->pNext == NULL)
		{
			pNew->pPrev->pNext = NULL;
			free(pNew);
			result = 1;
		}
		else
		{
			pNew->pPrev->pNext = pNew->pNext;
			pNew->pNext->pPrev = pNew->pPrev;
			free(pNew);
			result = 1;
		}
	}

	return result;
}

void shuffle(Node **pList)
{
	int *shuffleBox = NULL;
	int count = countList(pList);
	Node *pNew = NULL;

	pNew = *pList;

	shuffleBox = (int *)malloc((sizeof(int) * count));

	for (int i = 0; i < count; i++) 
    {
        shuffleBox[i] = i;
    }

	for (int j = 0; j < count; j++)
    {
		int line = shuffleBox[j];
		int randomIndex = rand() % count;

		shuffleBox[j] = shuffleBox[randomIndex];
		shuffleBox[randomIndex] = line;
	}

	for (int k = 0; k < count; k++)
	{
		pNew = *pList;
		system("cls");

		for (int m = 0; m < shuffleBox[k]; m++) pNew = pNew->pNext;

		printf("Now Playing: \n");
		printf("%s - %s - %s", pNew->data.song, pNew->data.artist, pNew->data.album);
		Sleep(2000);
	}
	printf("\nEnd of playlist.\n");
	system("pause");
}
