//  ----------------------------------------------------
//  Program: Hunt-The-Wumpus
//
//  System: Mac using XCode
//  Author: Shahryar Ahmed
//
//  ----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // toupper() function
#include <time.h> // random generator

// Declared struct WumpusGame: has int objects wumpus, player, pit1, pit2.
// Variable holds the position on the game board.
struct WumpusGame{
    int wumpus;
    int player;
    int pit1;
    int pit2;
    int bat1;
    int bat2;
    int arrow;
    int arrowCount;
};

// Function getRandomNumber calls the random number generator and returns
// a random number within the limits as set by game.
int getRandomNumber(){
    int lowerLimit = 1;
    int upperLimit = 20;
    int number = (rand() % (upperLimit - lowerLimit + 1)) + lowerLimit;
    return number;
}

// Function initializeRoomLocations takes input of an instance of struct,
// and initializes all objects to a unique random room.
void initializeRoomLocations(struct WumpusGame *g){
    
    g->player = getRandomNumber();  //generates random room for player
    
    g->wumpus = getRandomNumber();  //generates random room for wumpus
    while (g->player == g->wumpus) {
        g->wumpus = getRandomNumber();
    }
    
    g->pit1 = getRandomNumber();    //generates random room for pit1
    while (g->player == g->pit1 ||
           g->wumpus == g->pit1){
        
        g->pit1 = getRandomNumber();
    }
    
    g->pit2 = getRandomNumber();    //generates random room for pit2
    while (g->player == g->pit2 ||
           g->wumpus == g->pit2 ||
           g->pit1   == g->pit2){
        
        g->pit2 = getRandomNumber();
    }

    g->bat1 = getRandomNumber();    //generates random room for bat 1
    while (g->player == g->bat1 ||
           g->wumpus == g->bat1 ||
           g->pit1   == g->bat1 ||
           g->pit2   == g->bat1){
        
        g->bat1 = getRandomNumber();
    }
    
    g->bat2 = getRandomNumber();    //generates random room for bat 2
    while (g->player == g->bat2 ||
           g->wumpus == g->bat2 ||
           g->pit1   == g->bat2 ||
           g->pit2   == g->bat2 ||
           g->bat1   == g->bat2){
        
        g->bat2 = getRandomNumber();
        
    }
    
    g->arrow = getRandomNumber();   //generates random room for arrow
    while (g->player == g->arrow ||
           g->wumpus == g->arrow ||
           g->pit1   == g->arrow ||
           g->pit2   == g->arrow ||
           g->bat1   == g->arrow ||
           g->bat2   == g->arrow){
        
        g->arrow = getRandomNumber();
        
    }
    

}

// Function optionX exits program and displays appropriate message.
void optionX(){
    printf("\nExiting Program ...");
    exit(0);
}

// Function is used to check arrow path adjacence. The function
// recieves a struct, rooms array, and arrow path input.
int isAdjacent(struct WumpusGame *g, int **rooms, int move){
    int valid = 0;
        
    for(int i=0; i<3; i++){ //checks if player's move is valid
        if(rooms[g->arrow-1][i] == move){
            //g->arrow = move;
            valid = 1;
            break;
        }
    }
    return valid;
}

// Function checkGameObjective take input of an instance of struct, rooms array, and moveNum.
// It prints messages related to objective.
void checkGameObjective(struct WumpusGame *g, int **rooms, int moveNum){
    
    //CHECK if PLAYER has entered a WUMPUS ROOM)
    if (g->player == g->wumpus){
        if (g->wumpus % 2 == 0){ //Player meets wumpus in an even numbered room.
            printf("You briefly feel a slimy tentacled arm as your neck is snapped.\n");
            printf("It is over.\n");
            optionX();
        }
        else{
            g->wumpus = rooms[g->wumpus-1][0];
            printf("You hear a slithering sound, as the Wumpus slips away.\n");
            printf("Whew, that was close!\n");
        }
    }
    
    //CHECK if PLAYER has entered a ROOM w/PIT (PIT1 OR PIT2)
    else if ((g->player == g->pit1) || (g->player == g->pit2)){ //player meets a pit.
        printf("Aaaaaaaaahhhhhh....\n");
        printf("    You fall into a pit and die. \n");
        optionX();
    }
    
    //CHECK if PLAYER has entered a ROOM w/BAT (BAT1 OR BAT2)
    while ((g->player == g->bat1) || (g->player == g->bat2)){ //player meets a room with bats.
        printf("Woah... you're flying!\n");
        
        int copyPlayerLocation = g->player;
        
        g->player = getRandomNumber();
        while (g->player == copyPlayerLocation){ //checks if new player room is not equal to previous room.
            g->player = getRandomNumber();
        }
        printf("You've just been transported by bats to room %d.\n", g->player);
        //BATS MOVE to NEW ROOM APART FROM OTHER BATS or PREV ROOM
        if(g->bat1 == copyPlayerLocation){
            int copyBat1 = g->bat1;
            g->bat1 = getRandomNumber();
            while (g->bat1 == g->bat2 || g->bat1 == copyBat1) {
                g->bat1 = getRandomNumber();
            }
        }
        if(g->bat2 == copyPlayerLocation){
            int copyBat2 = g->bat2;
            g->bat2 = getRandomNumber();
            while (g->bat2 == g->bat1 || g->bat2 == copyBat2) {
                g->bat2 = getRandomNumber();
            }
        }
    }
    
    //CHECK IF PLAYER has entered a ROOM w/ARROW
    if(g->player == g->arrow){
        g->arrowCount = g->arrowCount + 1;
        printf("Congratulations, you found the arrow and can once again shoot.\n");
    }
    
}

// Function checkAndPrintAdjacencyMessage take input of an instance of struct and rooms array.
// It prints messages related to adjacency.
void checkAndPrintAdjacencyMessage(struct WumpusGame *g, int **rooms){
    
    printf("You are in room %d. ", g->player);

    for(int i=0; i<3; i++){
        if(rooms[g->wumpus-1][i] == g->player){ //prints message if player is adjacent to wumpus
            printf("You smell a stench. ");
            break;
        }
    }
    for(int i=0; i<3; i++){
        if( ((rooms[g->pit1-1][i] == g->player) || (rooms[g->pit2-1][i] == g->player)) && (rooms[g->wumpus-1][i] != g->player) ){
            printf("You feel a draft. "); //prints message if player is adjacent to pit1 or pit2
            break;
        }
    }
    for(int i=0; i<3; i++){
        if( ((rooms[g->bat1-1][i] == g->player) || (rooms[g->bat2-1][i] == g->player))
           //&&
           //((rooms[g->wumpus-1][i] != g->player) || (rooms[g->pit1-1][i] != g->player) || (rooms[g->pit2-1][i] != g->player))
           ){
            printf("You hear rustling of bat wings. "); //prints message if player is adjacent to bat1 or bat2
            break;
        }
    }
    

        printf("\n\n");

}

// Function arrowLogistics, recieves an input of struct, rooms array, an array of
// inputs, and inputSize (size of inputs array). This function is responsible for
// handling arrow objectives.
int arrowLogistics(struct WumpusGame *g, int **rooms, int *inputs, int inputSize){
    
    g->arrowCount= g->arrowCount -1;
    //Sets ARROW location to PLAYER
    g->arrow = g->player;
    
    
    for(int i=0; i<inputSize; i++){
        
        if(isAdjacent(g, rooms, inputs[i])){
            
            g->arrow = inputs[i];
            
            //CHECK if PLAYER has shot WUMPUS
            if(g->wumpus == g->arrow){
                printf("Wumpus has just been pierced by your deadly arrow! \n");
                printf("Congratulations on your victory, you awesome hunter you.\n");
                optionX();
            }
            else if(g->player == g->arrow){
                printf("You just shot yourself.  \n");
                printf("Maybe Darwin was right.  You're dead.\n");
                optionX();
            }
            //WUMPUS moves to the LOWEST NUMBERED ROOM

        }
        //If WUMPUS DOES NOT get (CLEAR SHOT)
        else{

            //SETS new ARROW LOCATION to THE LOWEST-ADJACENT ROOM
            g->arrow = rooms[g->arrow-1][0];
            
            printf("Room %d is not adjacent. Arrow ricochets...\n", inputs[i]);
            
            if(g->wumpus == g->arrow){
                printf("Your arrow ricochet killed the Wumpus, you lucky dog!\n");
                printf("Accidental victory, but still you win!");
                optionX();
            }
            else if(g->player == g->arrow){
                printf("You just shot yourself, and are dying.\n");
                printf("It didn't take long, you're dead.\n");
                optionX();
            }
        }

        
    }
    //WUMPUS moves to the LOWEST NUMBERED ROOM
    g->wumpus = rooms[g->wumpus-1][0];
    return 1;
}

// Function optionS: handles the shooting option. This function recieves
// a parameter of the struct, and rooms array. The function takes user
// inputs for the arrow aim. The function then calls arrowLogistics to
// handle arrow objectives.
int optionS(struct WumpusGame *g, int **rooms){
    
    int numInput;
    
    if(g->arrowCount == 0){
        printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
    }
    else{
        printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
        scanf("%d ", &numInput);
        
        int* inputs = malloc(numInput * sizeof(int));
        
        if(numInput == 1){
            scanf("%d", &inputs[0]);
            arrowLogistics(g, rooms, inputs, numInput);
        }
        else if(numInput == 2){
            scanf("%d %d", &inputs[0], &inputs[1]);
            arrowLogistics(g, rooms, inputs, numInput);
        }
        else if(numInput == 3){
            scanf("%d %d %d", &inputs[0], &inputs[1], &inputs[2]);
            arrowLogistics(g, rooms, inputs, numInput);
        }
        else{
            printf("Invalid Argument\n");
        }

    }
    
    checkAndPrintAdjacencyMessage(g, rooms);
    return 1;
}

// Function optionM takes input of an instance of struct, rooms array, and move.
// Function outputs validity of users move. Function also calls checkGameObjective
// to check if winning or losing objectives are met, and checkAndPrintAdjacencyMessage
// to print hazard detection messages.
int optionM(struct WumpusGame *g, int **rooms, const int move){
   int valid = 0;

    for(int i=0; i<3; i++){ //checks if player's move is valid
        if(rooms[g->player-1][i] == move){
            g->player = move;
            valid = 1;
            break;
        }
    }
    
    checkGameObjective(g, rooms, move);

    if (valid == 1){ //if player's move is valid.
        checkAndPrintAdjacencyMessage(g, rooms); //print location and/or adjacency messages.
    }
    else{
        printf("Invalid move.  Please retry. \n");//print if player's move is not valid.
        checkAndPrintAdjacencyMessage(g, rooms);
    }
    return valid;
}

// Function optionR takes input of an instance of struct, and rooms array.
// Function resets current objects position to user's input.
void optionR(struct WumpusGame *g, int **rooms){
    
    int player, wumpus, pit1, pit2, bat1, bat2, arrow;
    
    printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n");
    scanf("%d %d %d %d %d %d %d", &player, &wumpus, &pit1, &pit2, &bat1, &bat2, &arrow); //takes user input on new object locations.
    printf("\n");
    if ((wumpus != player) && (wumpus != pit1) && (wumpus != pit2) &&
        (player != pit1) && (player != pit2) &&
        (pit1 != pit2)){
        
        g->player = player;
        g->wumpus = wumpus;
        g->pit1 = pit1;
        g->pit2 = pit2;
        g->bat1 = bat1;
        g->bat2 = bat2;
        g->arrow = arrow;
    
    }
    checkAndPrintAdjacencyMessage(g, rooms);
}

// Function optionC takes input of one instance of struct, and rooms array.
// Prints message revealing locations of objects.
void optionC(struct WumpusGame *g, int **rooms){
    printf("Cheating! Game elements are in the following rooms: \n");
    printf("Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n");
    int arrowCopy = 0;
    if(g->arrow == g->player){
        arrowCopy = -1;
    }
    else{
        arrowCopy = g->arrow;
    }
    printf("%4d %5d %6d %5d %5d %5d %5d \n\n", g->player, g->wumpus, g->pit1, g->pit2, g->bat1, g->bat2, arrowCopy);

    checkAndPrintAdjacencyMessage(g, rooms);
}

//Function optionG takes input of one instance of struct, and validates player's guess of wumpus location. Calls optionX to exit
//the game if player won.
void optionG(struct WumpusGame *g){
    int roomNumber;
    printf("Enter room (1..20) you think Wumpus is in: ");
    scanf("%d", &roomNumber);
    
    if(g->wumpus == roomNumber){
        printf("You won!\n");
        optionX();
    }
}

//Function printDirections takes input of one instance of struct, and rooms array, and choice. This function prints both menu
//option D and F, the recieved parameter of choice determines whther to print the cave only or both cave and instructions.
void printDirections(struct WumpusGame *g, int **rooms, char choice){
    
    printf("\n       ______18______ \n");
    printf("      /      |       \\           \n");
    printf("     /      _9__      \\          \n");
    printf("    /      /    \\      \\        \n");
    printf("   /      /      \\      \\       \n");
    printf("  17     8        10     19       \n");
    printf("  | \\   / \\      /  \\   / |    \n");
    printf("  |  \\ /   \\    /    \\ /  |    \n");
    printf("  |   7     1---2     11  |       \n");
    printf("  |   |    /     \\    |   |      \n");
    printf("  |   6----5     3---12   |       \n");
    printf("  |   |     \\   /     |   |      \n");
    printf("  |   \\       4      /    |      \n");
    printf("  |    \\      |     /     |      \n");
    printf("  \\     15---14---13     /       \n");
    printf("   \\   /            \\   /       \n");
    printf("    \\ /              \\ /        \n");
    printf("    16---------------20\n\n");
    
    if(choice == 'D'){
        
        printf( "Hunt the Wumpus:                                             \n"
                "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
                "room has 3 tunnels leading to other rooms.                   \n"
                "                                                             \n"
                "Hazards:                                                     \n"
                "1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
                "2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
                "   fly you to some random room, which could be troublesome.  Then those bats go \n"
                "   to a new room different from where they came from and from the other bats.   \n"
                "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
                "   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
                "    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
                "    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
                "    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
                "    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
                "    room, he snaps your neck and you die!                                       \n"
                "                                                                                \n"
                "Moves:                                                                          \n"
                "On each move you can do the following, where input can be upper or lower-case:  \n"
                "1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
                "   then a room number.                                                          \n"
                "2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
                "   you specify.  Your arrow ends up in the final room.                          \n"
                "   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
                "   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
                "   by spaces. If an arrow can't go a direction because there is no connecting   \n"
                "   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
                "   continues doing this until it has traveled the designated number of rooms.   \n"
                "   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
                "   automatically pick up the arrow if you go through a room with the arrow in   \n"
                "   it.                                                                          \n"
                "3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
                "4. Enter 'C' to cheat and display current board positions.                      \n"
                "5. Enter 'D' to display this set of instructions.                               \n"
                "6. Enter 'P' to print the maze room layout.                                     \n"
                "7. Enter 'X' to exit the game.                                                  \n"
                "                                                                                \n"
                "Good luck!                                                                      \n"
                " \n\n");
        
        checkAndPrintAdjacencyMessage(g, rooms);
    }
    else{
        checkAndPrintAdjacencyMessage(g, rooms);
    }
}

int main(int argc, const char * argv[]) {
    
    struct WumpusGame g; //creates a game board g
    g.arrowCount = 1; //sets initial arrow count to 1
    
    int r = 20, c = 3, i;
    
    //DYNAMIC ALLOCATION of ROOMS ARRAY
    int** rooms = (int**)malloc(r * sizeof(int*));
    for (i = 0; i < r; i++)
        rooms[i] = (int*)malloc(c * sizeof(int));
    
    //HARDCODING ADJACENT ROOMS
    rooms[0][0] = 2;
    rooms[0][1] = 5;
    rooms[0][2] = 8;
    
    rooms[1][0] = 1;
    rooms[1][1] = 3;
    rooms[1][2] = 10;
    
    rooms[2][0] = 2;
    rooms[2][1] = 4;
    rooms[2][2] = 12;
    
    rooms[3][0] = 3;
    rooms[3][1] = 5;
    rooms[3][2] = 14;
    
    rooms[4][0] = 1;
    rooms[4][1] = 4;
    rooms[4][2] = 6;
    
    rooms[5][0] = 5;
    rooms[5][1] = 7;
    rooms[5][2] = 15;
    
    rooms[6][0] = 6;
    rooms[6][1] = 8;
    rooms[6][2] = 17;
    
    rooms[7][0] = 1;
    rooms[7][1] = 7;
    rooms[7][2] = 9;
    
    rooms[8][0] = 8;
    rooms[8][1] = 10;
    rooms[8][2] = 18;
    
    rooms[9][0] = 2;
    rooms[9][1] = 9;
    rooms[9][2] = 11;
    
    rooms[10][0] = 10;
    rooms[10][1] = 12;
    rooms[10][2] = 19;
    
    rooms[11][0] = 3;
    rooms[11][1] = 11;
    rooms[11][2] = 13;
    
    rooms[12][0] = 12;
    rooms[12][1] = 14;
    rooms[12][2] = 20;
    
    rooms[13][0] = 4;
    rooms[13][1] = 13;
    rooms[13][2] = 15;
    
    rooms[14][0] = 6;
    rooms[14][1] = 14;
    rooms[14][2] = 16;
    
    rooms[15][0] = 15;
    rooms[15][1] = 17;
    rooms[15][2] = 20;
    
    rooms[16][0] = 7;
    rooms[16][1] = 16;
    rooms[16][2] = 18;
    
    rooms[17][0] = 9;
    rooms[17][1] = 17;
    rooms[17][2] = 19;
    
    rooms[18][0] = 11;
    rooms[18][1] = 18;
    rooms[18][2] = 20;
    
    rooms[19][0] = 13;
    rooms[19][1] = 16;
    rooms[19][2] = 19;
    
    //******[END OF ADJACENT ROOMS HARDCODING]******

    srand(1); //seeding the random generator
    int mValid = 0;
    int moveNum = 1;
    char playerInput = ' ';
    int playerInput2;
    
    initializeRoomLocations(&g); //rooms are initialized randomly (when game begins).
 
    checkAndPrintAdjacencyMessage(&g, rooms);
    while (playerInput != 'X') {
        printf("%d. Enter your move (or 'D' for directions): ", moveNum);
        scanf(" %c", &playerInput);
        playerInput = toupper(playerInput); //toupper converts all lowercase inputs to upper case for simpler comparisons.
        
        switch (playerInput) { //switch case for the menu of game. Calls functions depending on user's input.
            case 'M':
                scanf("%d", &playerInput2);
                mValid = optionM(&g, rooms, playerInput2);
                if (mValid){
                    moveNum++;
                }
                break;
            case 'R':
                optionR(&g, rooms);
                break;
            case 'C':
                optionC(&g, rooms);
                //optionX();
                break;
            case 'D':
                printDirections(&g, rooms, 'D');
                break;
            case 'P':
                printDirections(&g, rooms, 'M');
                break;
            case 'G':
                optionG(&g);
                break;
            case 'S':
                if(optionS(&g, rooms)){
                    moveNum++;
                }
                break;
            case 'X':
                optionX();
                break;
            default:
                break;
        }
        
    }
    
    //Freeing array
    for (int i = 0; i < r; i++){
           free(rooms[i]);
    }
    free(rooms);
