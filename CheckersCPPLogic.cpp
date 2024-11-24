#include "/Users/antonsidlyar/IdeaProjects/CheckersJavaGUI/src/checkers_game_CheckersGame.h"
#include <iostream>

int board[8][8] = {

        {0, 1, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 1, 0, 1, 0, 1},// 0 represents empty space, 1 represents first player, 2 represents second player.
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {2, 0, 2, 0, 2, 0, 2, 0},
        {0, 2, 0, 2, 0, 2, 0, 2},// i will additionally use  3 for king piece of player 1 and 4 for king piece of player 2
        {2, 0, 2, 0, 2, 0, 2, 0}
};
int currentPlayer = 1; //  we will start with player 1

// if the move is inside our boarder and doesnt cross the limits
bool isWithinBounds(int x, int y) {
    return x >= 0 && x < 8 && y >= 0 && y < 8;
}

//  function to check if an additional capture is possible from a position
bool canCapture(int x, int y, int player) {
    int directions[4][2] = {{-2, -2}, {-2, 2}, {2, -2}, {2, 2}};
    int opponent = (player == 1) ? 2 : 1;

    for (auto &direction : directions) {  // iterate through capture directions
        int newX = x + direction[0]; // theoretical move
        int newY = y + direction[1]; // chu je pystota
        int midX = (x + newX) / 2;  // between enemy?
        int midY = (y + newY) / 2;

        if (isWithinBounds(newX, newY) && board[newX][newY] == 0 &&
            (board[midX][midY] == opponent || board[midX][midY] == opponent + 2)) {
            return true;
        }
    }
    return false;
}


bool isPathClear(int fromX, int fromY, int toX, int toY) {
    int dx = (toX - fromX) > 0 ? 1 : -1;
    int dy = (toY - fromY) > 0 ? 1 : -1;
    int x = fromX + dx;
    int y = fromY + dy;

    while (x != toX && y != toY) {
        if (board[x][y] != 0) return false; // path is blocked
        x += dx;
        y += dy;
    }
    return true;
}
bool canKingCapture(int fromX, int fromY, int toX, int toY, int player) {
    int dx = (toX - fromX) > 0 ? 1 : -1;
    int dy = (toY - fromY) > 0 ? 1 : -1;
    int opponent = (player == 1) ? 2 : 1;
    bool opponentFound = false;

    int x = fromX + dx;
    int y = fromY + dy;

    while (x != toX && y != toY) {
        if (board[x][y] != 0) {
            if (board[x][y] == opponent || board[x][y] == opponent + 2) { // opponent piece
                if (opponentFound) return false; // more than one opponent in the path
                opponentFound = true;
            } else {
                return false; // blocked by other piece
            }
        }
        x += dx;
        y += dy;
    }

    return opponentFound; // **True if exactly one opponent was found and path was clear**
}



bool isValidMove (int fromX, int fromY, int toX, int toY, int player ) {

    int piece = board[fromX][fromY];
    bool isKing = (piece == 3 || piece == 4); // assuming 3 and 4 are kings for players 1 and 2

    if (!isWithinBounds(toX, toY) || board[toX][toY] != 0) return false; // destination must be empty

    int dx = toX - fromX; // rivno po diagonali
    int dy = toY - fromY;

    // king movement && multi-space capture
    if (isKing && abs(dx) == abs(dy)) {
        if (isPathClear(fromX, fromY, toX, toY)) {
            return true; // simple move for king
        } else if (canKingCapture(fromX, fromY, toX, toY, player)) {  // <-- **Added check for multi-space king capture**
            return true; // king capture over multiple spaces
        }
    }

    // standard piece movement (one diagonal space or two if capturing) // capturing
    if (abs(dx) == 1 && abs(dy) == 1) {
        // normal move for non-kings (only forward)
        if ((player == 1 && dx != 1) || (player == 2 && dx != -1)) {
            return false;
        }
        return true;
    } else if (abs(dx) == 2 && abs(dy) == 2) { // capture move (two diagonal spaces)
        int midX = (fromX + toX) / 2;
        int midY = (fromY + toY) / 2;
        int opponent = (player == 1) ? 2 : 1;

        if (board[midX][midY] == opponent || board[midX][midY] == opponent + 2) {
            return true;
        }
    }

    return false;
}
// check whether the piece is the king touching the last row.
void checkKinging(int x, int y) {
    if (board[x][y] == 1 && x == 7) { // black reaches the last row
        board[x][y] = 3; // black King - first player
    } else if (board[x][y] == 2 && x == 0) { // White reaches the last row
        board[x][y] = 4; // white King - second player
    }
}

// move function with multiple capture functionality
JNIEXPORT jboolean JNICALL Java_checkers_1game_CheckersGame_movePiece
        (JNIEnv *env, jobject obj, jint fromX, jint fromY, jint toX, jint toY) {
    int piece = board[fromX][fromY];
    int player = (piece == 1 || piece == 3) ? 1 : 2;
    // ensure correct turn
    if (player != currentPlayer) return JNI_FALSE;
    // check for valid move
    if (!isValidMove(fromX, fromY, toX, toY, player)) return JNI_FALSE;

    int dx = toX - fromX;
    int dy = toY - fromY;
    // handle capture move for kings (multi-space capture)
    if (abs(dx) > 1 && abs(dy) > 1 && (piece == 3 || piece == 4)) {
        int x = fromX + ((dx > 0) ? 1 : -1);
        int y = fromY + ((dy > 0) ? 1 : -1);

        while (x != toX && y != toY) {
            if (board[x][y] != 0 && board[x][y] != player) {
                board[x][y] = 0; // capture the opponent piece
                break;
            }
            x += (dx > 0) ? 1 : -1;
            y += (dy > 0) ? 1 : -1;
        }
    }
    // handle capture move
    else  if (abs(dx) == 2 && abs(dy) == 2) {
        int midX = (fromX + toX) / 2;
        int midY = (fromY + toY) / 2;

        // remove the captured piece
        board[midX][midY] = 0;
    }
    // move the piece
    board[toX][toY] = piece;
    board[fromX][fromY] = 0;

    // check if the piece becomes a king
    checkKinging(toX, toY);

    // check for additional captures
    if (abs(dx) == 2 && abs(dy) == 2 && canCapture(toX, toY, player)) {
        return JNI_FALSE; // Player can continue capturing  // could return number and additionally have possibility to tell then just invalid move.
    }

// Switch turn
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
    return JNI_TRUE; // Move ends turn
}


// Return the current board state ...
JNIEXPORT jobjectArray JNICALL Java_checkers_1game_CheckersGame_getBoardState(JNIEnv *env, jobject obj) {
    jobjectArray result = env->NewObjectArray(8, env->FindClass("[I"), nullptr);
    for (int i = 0; i < 8; i++) {
        jintArray row = env->NewIntArray(8);
        env->SetIntArrayRegion(row, 0, 8, board[i]); // part of board into row
        env->SetObjectArrayElement(result, i, row);  // row into result
        env->DeleteLocalRef(row);
    }
    return result;
}


//// Implement movePiece() to move a piece and return whether the move was good ( valid )
//JNIEXPORT jboolean JNICALL Java_checkers_1game_CheckersGame_movePiece(JNIEnv *env, jobject obj, jint fromX, jint fromY, jint toX, jint toY) {
//    // Implement logic for moving pieces (just a placeholder here)
//    if (board[fromX][fromY] != 0 && board[toX][toY] == 0) {
//        board[toX][toY] = board[fromX][fromY];
//        board[fromX][fromY] = 0;
//        currentPlayer = (currentPlayer == 1) ? 2 : 1;
//        return JNI_TRUE;
//    }
//    return JNI_FALSE;
//}

