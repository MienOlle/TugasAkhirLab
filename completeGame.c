#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>

void sleep_clear(){
	sleep(1);
	system("cls");
}

void hangman_display(int wrong){
	if(wrong == 0){
		printf("   ________\n");
		printf("   | /    |\n");
		printf("   |/     |\n");
		printf("   |       \n");
		printf("   |       \n");
		printf("   |       \n");
		printf("   |       \n");
		printf("___|___    \n");
	}else if(wrong == 1){
		printf("   ________\n");
		printf("   | /    |\n");
		printf("   |/     |\n");
		printf("   |      0\n");
		printf("   |       \n");
		printf("   |       \n");
		printf("   |       \n");
		printf("___|___    \n");
	}else if(wrong == 2){
		printf("   ________\n");
		printf("   | /    |\n");
		printf("   |/     |\n");
		printf("   |      0\n");
		printf("   |      |\n");
		printf("   |       \n");
		printf("   |       \n");
		printf("___|___    \n");
	}else if(wrong == 3){
		printf("   ________\n");
		printf("   | /    |\n");
		printf("   |/     |\n");
		printf("   |      0\n");
		printf("   |     /|\n");
		printf("   |       \n");
		printf("   |       \n");
		printf("___|___    \n");
	}else if(wrong == 4){
		printf("   ________\n");
		printf("   | /    |\n");
		printf("   |/     |\n");
		printf("   |      0\n");
		printf("   |     /|\\\n");
		printf("   |       \n");
		printf("   |       \n");
		printf("___|___    \n");
	}else if(wrong == 5){
		printf("   ________\n");
		printf("   | /    |\n");
		printf("   |/     |\n");
		printf("   |      0\n");
		printf("   |     /|\\\n");
		printf("   |     /\n");
		printf("   |       \n");
		printf("___|___    \n");
	}else if(wrong == 6){
		printf("   ________\n");
		printf("   | /    |\n");
		printf("   |/     |\n");
		printf("   |      0\n");
		printf("   |     /|\\\n");
		printf("   |     / \\\n");
		printf("   |       \n");
		printf("___|___    \n");
	}
}

void hangman_game(){
	char keepWord[200][50],guessWord[50],numWord = 0,userInput,wordGuessed[50];
	int userGuessWord,numWrong = 0,checkWrong = 1;
	
	FILE* hangmanFile;
	
	hangmanFile = fopen("hangmanDataBase.txt","r");
	
	while(fgets(guessWord,sizeof(guessWord),hangmanFile) != NULL){
		guessWord[strcspn(guessWord,"\n")] = '\0';
		strcpy(keepWord[numWord],guessWord);
		numWord++;
	}
	
	fclose(hangmanFile);
	
	
	srand(time(NULL));
	do{
		userGuessWord = rand() % numWord;
	}while(keepWord[userGuessWord] == NULL);
	
	strcpy(guessWord,keepWord[userGuessWord]);
	
//	printf("%s\n",guessWord);		//check answer
	int length = strlen(guessWord);
	
	for(int i=0;i<length;i++){
		wordGuessed[i] = '-';
	}
	wordGuessed[length] = '\0';
	
	while(strstr(wordGuessed,"-") != NULL){
		
		hangman_display(numWrong);
		printf("\n\n%s\n",wordGuessed);
		if(numWrong == 6){
			break;
		}
		
		userInput = getchar();
		getchar();
		for(int i=0;i<length;i++){
			if(guessWord[i] == userInput){
				wordGuessed[i] = userInput;
				checkWrong = 0;
			}
		}
		
		if(checkWrong == 1){
			numWrong++;
		}
		
		checkWrong = 1;
		sleep_clear();
	}
	
	if(numWrong == 6){
		printf("You Lost! Better Luck Next Time\n");
		printf("Your word is %s\n",guessWord);
	}else{
		printf("%s\n",guessWord);
		printf("You Win! Nice Job!\n");
	}
}

void battleship_game(){
	int checkShips = 0,chooseRow,chooseColumn,hits = 15;
	int ships[5][5] = {0};
	srand(time(NULL));
	
	//Randomize the area of the ship (1 means there is a ship, 0 means no ship, 2 means wrong chosen grid, 3 means correct chosen grid)
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			if(checkShips < 5){
				ships[i][j] = rand() % 2;
				if(ships[i][j] == 1){
					checkShips++;
				}
			}else{
				ships[i][j] = 0;
			}
		}
	}
		
	while(hits > 0){
		
		//Untuk check code jalan atau tidak
//		for(int i=0;i<5;i++){
//			for(int j=0;j<5;j++){
//				printf("%d ",ships[i][j]);
//			}
//			printf("\n");
//		}
		
		for(int i=0;i<5;i++){
			for(int j=0;j<5;j++){
				if(ships[i][j] == 2){
					printf("x  ");
				}else if(ships[i][j] == 3){
					printf("o  ");
				}else{
					printf("*  ");
				}
			}
			printf("\n");
		}
		
		printf("You have %d turns left\n\n",hits);
		printf("Choose a grid to destroy\n");
		
		restartRow:
			printf("Choose row (1-5) : ");
			scanf("%d",&chooseRow);
			getchar();
			if(chooseRow < 1 || chooseRow > 5){
				printf("\nPlease choose a row within range 1-5...\n");
				sleep(2);
				system("cls");
				for(int i=0;i<5;i++){
					for(int j=0;j<5;j++){
						if(ships[i][j] == 2){
							printf("x  ");
						}else if(ships[i][j] == 3){
							printf("o  ");
						}else{
							printf("*  ");
						}
					}
					printf("\n");
				}
				goto restartRow;
			}
		
		restartColumn:
			printf("Choose column (1-5) : ");
			scanf("%d",&chooseColumn);
			getchar();
			if(chooseColumn < 1 || chooseColumn > 5){
				printf("\nPlease choose a column within range 1-5...\n");
				sleep(2);
				system("cls");
				
				for(int i=0;i<5;i++){
					for(int j=0;j<5;j++){
						if(ships[i][j] == 2){
							printf("x  ");
						}else if(ships[i][j] == 3){
							printf("o  ");
						}else{
							printf("*  ");
						}
					}
					printf("\n");
				}
				goto restartColumn;
			}
		
		hits--;
		
		if(ships[chooseRow-1][chooseColumn-1] == 1){
			checkShips--;
			ships[chooseRow-1][chooseColumn-1] = 3;
			printf("\nHurray! You hit a ship.\n");
		}else if(ships[chooseRow-1][chooseColumn-1] == 0){
			ships[chooseRow-1][chooseColumn-1] = 2;
			printf("\nOh no.. You missed.\n");
		}else{
			printf("\nYou have tried that grid before.\nYou just wasted one shot...\n");
		}
		
		printf("Total ships left : %d\n\n",checkShips);
		sleep(1);
		if(checkShips > 0){
			printf("A little more to go...");
		}else{
			sleep(2);
			system("cls");
			break;
		}
		sleep(2);
		system("cls");
	}
	
	if(checkShips == 0){
		printf("You Won! Thanks For Playing!\n");
	}else{
		printf("You Lost.. Thanks For Playing!\n");
	}
}

//global variable for snake
int height = 20, width = 20;
int score = 0;

int xsnake, ysnake, xfood, yfood;
int button;
int gameover = 0;

void start_snake(){
	
	xsnake = height / 2;
	ysnake = width / 2;
	
}


void start_food(){
	
	type1:
		xfood = rand() % 20;
		if(xfood == 0){
			goto type1;
		}
	
	type2:
		yfood = rand() % 20;
		if(yfood == 0){
			goto type2;
		}
	
}


void layout_board(int i, int j){
	
	system("cls");
	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			if(i == 0 || i == width - 1 || j == 0 || j == height - 1){
				printf("#");
			}else if(i == xsnake && j == ysnake){
					printf("Q"); // snake head
				}else if(i == xfood && j == yfood){
					printf("*"); // food
				}else{
					printf(" ");	
				}
				
			}
			printf("\n");
		}
		printf("\nScore = %d\n", score);
	}


void user_input(){
	
	if(kbhit()){
		switch(getch()){
			case 'w':
				button = 1;
				break;
			case 'a':
				button = 2;
				break;
			case 's':
				button = 3;
				break;
			case 'd':
				button = 4;
				break;
			default:
				break;
		}
	}
	
	if(xsnake == xfood && ysnake == yfood){
	type1:
		xfood = rand() % 20;
		if(xfood == 0){
			goto type1;
		}
	
	type2:
		yfood = rand() % 20;
		if(yfood == 0){
			goto type2;
		}
		score += 1;
	}
}


void time_speed_end(){
	
	Sleep(50);
	switch(button){
		case 1:
			xsnake--;
			break;
		case 2:
			ysnake--;
			break;
		case 3:
			xsnake++;
			break;
		case 4:
			ysnake++;
			break;
		default:
			break;
	}
	
	if(xsnake < 0 || xsnake >= height || ysnake < 0 || ysnake >= width){
		gameover = 1; //if game is over
	}
	
}

void snake_game(){
	int i, j;
	
	start_snake();
	start_food();
	
	while(!gameover){
		layout_board(i, j);
		user_input();
		time_speed_end();
	}
}

typedef struct {
    char username[255];
    char password[255];
    int points;
    int loginCount;
} User;

void quicksort(User arr[], int low, int high);
int partition(User arr[], int low, int high);
int binarySearch(User arr[], int low, int high, char key[]);
void showDashboard(char username[]);
void updatePoints(char username[], int points);
void playGame(char username[]);

void regist() {
    system("cls");
    char username[255], password[255];
    int usernameExists;

    do {
        usernameExists = 0;
        printf("Enter your username (MUST BE AT LEAST 5 CHARACTERS LONG): ");
        scanf("%s", username);
        getchar();

        if (strlen(username) < 5) {
            puts("ERROR! USERNAME MUST BE AT LEAST 5 CHARACTERS LONG");
        } else {
            FILE *checkFile = fopen("userPoints.txt", "r");
            User checkUser;

            while (fscanf(checkFile, "%[^/]/%d/%d\n", checkUser.username, &checkUser.points, &checkUser.loginCount) == 3) {
                if (strcmp(username, checkUser.username) == 0) {
                    fclose(checkFile);
                    puts("ERROR! USERNAME ALREADY EXISTS");
                    usernameExists = 1;
                    break;
                }
            }

            fclose(checkFile);
        }
    } while (strlen(username) < 5 || usernameExists);

    do {
        printf("Enter your password (MUST BE AT LEAST 8 CHARACTERS LONG): ");
        scanf("%s", password);
        getchar();
        if (strlen(password) < 8) {
            puts("ERROR! PASSWORD MUST BE AT LEAST 8 CHARACTERS LONG");
        } else {
            puts("PASSWORD IS LONG ENOUGH");
        }
    } while (strlen(password) < 8);

    FILE *passwordFile = fopen("password.txt", "a");
    fprintf(passwordFile, "%s/%s\n", username, password);
    fclose(passwordFile);

    FILE *pointsFile = fopen("userPoints.txt", "a");
    fprintf(pointsFile, "%s/0/0\n", username);
    fclose(pointsFile);

    puts("YOUR ACCOUNT HAS BEEN SUCCESSFULLY CREATED!");
    puts("Press Enter to Continue...");
    getchar();
}

void login() {
    char username[255], password[255];
    system("cls");
    do {
        printf("Enter your username (MUST BE AT LEAST 5 CHARACTERS LONG): ");
        scanf("%s", username);
        getchar();
        if (strlen(username) < 5) {
            puts("ERROR! USERNAME MUST BE AT LEAST 5 CHARACTERS LONG");
        } else {
            puts("USERNAME IS LONG ENOUGH");
        }
    } while (strlen(username) < 5);

    do {
        printf("Enter your password (MUST BE AT LEAST 8 CHARACTERS LONG): ");
        scanf("%s", password);
        getchar();
        if (strlen(password) < 8) {
            puts("ERROR! PASSWORD MUST BE AT LEAST 8 CHARACTERS LONG");
        } else {
            puts("PASSWORD IS LONG ENOUGH");
        }
    } while (strlen(password) < 8);

    FILE *fpPassword = fopen("password.txt", "r");
    int accountFound = 0;
    User users[100];
    int count = 0;

    while (fscanf(fpPassword, "%[^/]/%s\n", users[count].username, users[count].password) == 2) {
        count++;
    }

    fclose(fpPassword);

    // Search for the username and password combination
    int index = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // Successfully logged in
        printf("Hello, %s!\n", username);
        showDashboard(username);
        playGame(username);
    } else {
        puts("ACCOUNT NOT FOUND OR INVALID USERNAME/PASSWORD");
    }

    puts("Press Enter to Continue...");
    getchar();
}


void playGame(char username[]) {
    system("cls");
    printf("Welcome to the Game, %s!\n", username);

    int secretNumber = rand() % 20 + 1;
    int guess;
    int attempts = 0;

    do {
        printf("Guess the number (1-20): ");
        scanf("%d", &guess);
        getchar();
        attempts++;

        if (guess < secretNumber) {
            printf("Too low! Try again.\n");
        } else if (guess > secretNumber) {
            printf("Too high! Try again.\n");
        } else {
            printf("Congratulations, you guessed the number in %d attempts!\n", attempts);
            updatePoints(username, attempts);
            printf("Your points: %d\n", attempts);
            showDashboard(username);
        }
    } while (guess != secretNumber);
}

void updatePoints(char username[], int points) {
    FILE *fp = fopen("userPoints.txt", "r+");

    if (fp == NULL) {
        printf("Error opening userPoints.txt\n");
        return;
    }

    User user;
    long int currentPosition = 0;
    int found = 0;

    while (fscanf(fp, "%254[^/]/%d/%d\n", user.username, &user.points, &user.loginCount) == 3) {
        if (strcmp(username, user.username) == 0) {
            found = 1;
            break;
        }
        currentPosition = ftell(fp);
    }

    if (found) {
        fseek(fp, currentPosition, SEEK_SET);
        fprintf(fp, "%s/%d/%d\n", username, user.points + points, user.loginCount + 1);
    } else {
        fprintf(fp, "%s/%d/%d\n", username, points, 1);
    }

    fclose(fp);
}

void showDashboard(char username[]) {
    system("cls");
    printf("Dashboard for %s:\n", username);

    FILE *fp = fopen("userPoints.txt", "r");
    User users[100];
    int count = 0;

    while (fscanf(fp, "%[^/]/%d/%d\n", users[count].username, &users[count].points, &users[count].loginCount) == 3) {
        count++;
    }

    fclose(fp);

    User uniqueUsers[100];
    int uniqueCount = 0;

    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < uniqueCount; j++) {
            if (strcmp(users[i].username, uniqueUsers[j].username) == 0) {
                uniqueUsers[j].points += users[i].points;
                uniqueUsers[j].loginCount = users[i].loginCount;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(uniqueUsers[uniqueCount].username, users[i].username);
            uniqueUsers[uniqueCount].points = users[i].points;
            uniqueUsers[uniqueCount].loginCount = users[i].loginCount;
            uniqueCount++;
        }
    }

    quicksort(uniqueUsers, 0, uniqueCount - 1);

    printf("%-20s %-10s %-10s\n", "Username", "Points", "Login Count");
    printf("-------------------- -------------- ------------\n");

    for (int i = 0; i < uniqueCount; i++) {
        printf("%-20s %-10d %-10d\n", uniqueUsers[i].username, uniqueUsers[i].points, uniqueUsers[i].loginCount);
    }

    printf("Press Enter to Continue...");
    getchar();
}

void quicksort(User arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int partition(User arr[], int low, int high) {
    int pivot = arr[high].points;

    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j].points > pivot) {
            i++;
            User temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    User temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

int binarySearch(User arr[], int low, int high, char key[]) {
    if (low <= high) {
        int mid = (low + high) / 2;

        if (strcmp(arr[mid].username, key) == 0) {
            return mid;
        } else if (strcmp(arr[mid].username, key) < 0) {
            return binarySearch(arr, mid + 1, high, key);
        } else {
            return binarySearch(arr, low, mid - 1, key);
        }
    }

    return -1;
}

void number_guess(){
	while (1) {
        int option;
        start:
        system("cls");
        puts("1. Register");
        puts("2. Login");
        puts("3. Exit");
        printf(">> ");
        scanf("%d", &option);
        getchar();
        switch (option) {
            case 1:
                regist();
                goto start;
                break;
            case 2:
                login();
                goto start;
                break;
            case 3:
                exit(0);
            default:
                continue;
        }
        break;
    }
}

int menu(){
	int chooseMenu;
	
	printf("WELCOME TO THE ARCADE\n");
	printf("----------------------\n");
	printf("1. Snake\n");
	printf("2. Hangman\n");
	printf("3. BattleShip\n");
	printf("4. Number Guesser\n");
	printf("5. Exit\n");
	printf("Choose a game : ");
	scanf("%d",&chooseMenu);
	getchar();
	
	if(chooseMenu == 2){
		sleep_clear();
		hangman_game();
		sleep_clear();
	}else if(chooseMenu == 3){
		sleep_clear();
		battleship_game();
		sleep_clear();
	}else if(chooseMenu == 1){
		sleep_clear();
		snake_game();
		sleep_clear();
	}else if(chooseMenu == 4){
		number_guess();
	}else if(chooseMenu == 5){
		printf("Thanks for Playing\n");
		sleep_clear();
		return 1;
	}
}

int main(){
	int restart = 0;
	do{
		restart = menu();
	}while(restart != 1);

	return 0;
}

