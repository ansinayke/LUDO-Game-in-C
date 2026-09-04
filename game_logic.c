#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

char *playerColors[] = {"RED", "GREEN", "YELLOW", "BLUE"};

char *pathLocations[] = {"B", "X", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "H"};

void game_ludo() {
 
    // Welcome message and player introduction
    
    printf("Welcome to L U D O !\n\n");
    printf("Let's have some fun :)\n\n");
    sleep(1);

    printf("Please enter the name of the players...\n");
    sleep(1);
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("%d Player = %s Player\n", i + 1, playerColors[i]);
        sleep(1);
    }
    printf("\n");

    // Random number generator
    
    srand(time(NULL));

    // Initialize player pieces

    int playerPieces[NUM_PLAYERS][NUM_PIECES];
    for (int i = 0; i < NUM_PLAYERS; i++) {
        for (int j = 0; j < NUM_PIECES; j++) {
            playerPieces[i][j] = 0;
        }
    }
    
    // Introducing the pieces
    
    printf("Each player has got four pieces to play the game as,\n");
    printf("| RED Player    | R1 R2 R3 R4 |\n");
    printf("| GREEN Player  | G1 G2 G3 G4 |\n");
    printf("| YELLOW Player | Y1 Y2 Y3 Y4 |\n");
    printf("| BLUE Player   | B1 B2 B3 B4 |\n");
    printf("\n");
    sleep(1);
    
    // Roll the dice for players to determine the starting player
  
    int highestRoll = 0;
    int highestRollPlayer = 0;
    for (int i = 0; i < NUM_PLAYERS; i++) {
        int roll = (rand() % 6) + 1;
        printf("%s Player rolled %d\n", playerColors[i], roll);
        sleep(1);
        if (roll > highestRoll) {
            highestRoll = roll;
            highestRollPlayer = i;
        }
    }
    
    // Determine the starting player
   
    printf("\n%s Player goes first.\n", playerColors[highestRollPlayer]);

    printf("\nGet ready...\n");
    fflush(stdout);
    sleep(1);
    printf("Pieces Positioned...\n");
    fflush(stdout);
    sleep(1);
    printf("\n   Let's Go!\n");
    sleep(1);

    // Initialize winner tracking
   
    int finishedPlayers[NUM_PLAYERS] = {0};
    int finishingOrder[NUM_PLAYERS] = {-1, -1, -1, -1};
    int finishCount = 0;


    // ***Game loop***
   
    int currentPlayer = highestRollPlayer;
    while (finishCount < 3) {  // Stop the loop after finding the third winner
        
	    // Display current state of the game

        printf("\n+---------------------------+\n");
        printf("|       - L  U  D  O -      |\n");
        printf("+---------------------------+\n");
        printf("| B=Base | X=Start | H=Home |\n");
        printf("+---------------------------+\n");
        for (int i = 0; i < NUM_PLAYERS; i++) {
            printf("| %s |", playerColors[i]);
            for (int j = 0; j < NUM_PIECES; j++) {
                if (playerPieces[i][j] == 0) {
                    printf(" B");
                } else if (playerPieces[i][j] == 1) {
                    printf(" X");
                } else if (playerPieces[i][j] == 58) {
                    printf(" H");
                } else {
                    printf(" %d", playerPieces[i][j]);
                }
            }
            printf(" |\n");
        }
        printf("+---------------------------+\n");

        // Skip turn if player has already finished
	
        if (finishedPlayers[currentPlayer]) {
            currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;
            continue;
        }

        // Roll the dice for the current player
        
	    int roll = (rand() % 6) + 1;
        printf("%s Player's turn...\n", playerColors[currentPlayer]);
        printf("%s Player rolled %d\n", playerColors[currentPlayer], roll);
	sleep(1);

        // Variables for sum of rolls and roll count
        
	    int totalRoll = roll;
        int rollCount = 1;

        // Check if any piece is in a place from 1 to 52 or specific condition for 52-57
        
	    int pieceMoved = 0;
        for (int i = 0; i < NUM_PIECES; i++) {
            if (playerPieces[currentPlayer][i] == 0 && totalRoll >= 6) {
                playerPieces[currentPlayer][i] = 1; // Base to start
                printf("%s Player moved a piece from base to start.\n", playerColors[currentPlayer]);
                pieceMoved = 1;
                break;
            } else if (playerPieces[currentPlayer][i] > 0 && playerPieces[currentPlayer][i] < 52) {
               
		    // Subsequent rolls if 6 is rolled & piece is in (1-52)
                
		    while (roll == 6 && rollCount < 3) {
                roll = (rand() % 6) + 1;
                totalRoll += roll;
                rollCount++;
                printf("%s Player rolled %d (Total: %d)\n", playerColors[currentPlayer], roll, totalRoll);
            }

                if (rollCount == 3 && roll == 6) {
                    printf("Three consecutive 6s rolled, turn terminated.\n");
                    totalRoll = 0;   // Reset the totalRoll to prevent any movement
                }

                int newPosition = playerPieces[currentPlayer][i] + totalRoll;
                if (newPosition > 58) {
                    printf("Invalid move, piece cannot exceed Home.\n");
                } else if (newPosition == 58) {
                    playerPieces[currentPlayer][i] = 58; // Move piece to home
                    printf("%s Player moved a piece to Home.\n", playerColors[currentPlayer]);
                } else {

                    // Capturing check
                    
		            int captured = 0;
                    for (int k = 0; k < NUM_PLAYERS; k++) {
                        if (k != currentPlayer) {
                            for (int l = 0; l < NUM_PIECES; l++) {
                                if (playerPieces[k][l] == newPosition) {
                                    playerPieces[k][l] = 0;    // Captured piece to base
                                    printf("%s Player's piece at %s was captured by %s Player!\n", playerColors[k], pathLocations[newPosition], playerColors[currentPlayer]);
                                    captured = 1;
                                    break;
                                }
                            }
                        }
                        if (captured) break;
                    }

                    playerPieces[currentPlayer][i] = newPosition;
                    printf("%s Player moved a piece to %s.\n", playerColors[currentPlayer], pathLocations[newPosition]);
                }
                pieceMoved = 1;
                break;
            } else if (playerPieces[currentPlayer][i] >= 52 && playerPieces[currentPlayer][i] <= 57) {
                int requiredRoll = 58 - playerPieces[currentPlayer][i];
                if (roll == requiredRoll) {
                    playerPieces[currentPlayer][i] = 58;        // Move piece to home (52-57)
                    printf("%s Player moved a piece to Home from %d.\n", playerColors[currentPlayer], playerPieces[currentPlayer][i] - roll);
                    pieceMoved = 1;
                    break;
                }
            }
        }

        if (!pieceMoved) {
            printf("No valid moves for %s Player.\n", playerColors[currentPlayer]);
        }

        // Check if the player has won
	
        int allHome = 1;
        for (int i = 0; i < NUM_PIECES; i++) {
            if (playerPieces[currentPlayer][i] != 58) {
                allHome = 0;
                break;
            }
        }
        if (allHome && !finishedPlayers[currentPlayer]) {
            finishedPlayers[currentPlayer] = 1;
            finishingOrder[finishCount] = currentPlayer;
            finishCount++;
            printf("\n%s Player has brought all their pieces Home! They finish in position %d.\n", playerColors[currentPlayer], finishCount);
        }

        // Switch to the next player
	
        currentPlayer = (currentPlayer + 1) % NUM_PLAYERS;
    }

    // Assign the fourth position to the remaining player
    
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (!finishedPlayers[i]) {
            finishingOrder[finishCount] = i;
            finishedPlayers[i] = 1;
            printf("\n%s Player got the 4th position as all the other players have finished the game.\n", playerColors[i]);
            break;
        }
    }

    // Display final results
    
    printf("\n+---------------------------+\n");
    printf("| Final Results of WINNERS  |\n");
    printf("+---------------------------+\n");
    for (int i = 0; i < NUM_PLAYERS; i++) {
        printf("%d. %s Player\n", i + 1, playerColors[finishingOrder[i]]);
    }
    printf("+---------------------------+\n");

}
