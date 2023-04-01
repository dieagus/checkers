// checkers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;
class Row {
public:
    void printRow(int num) {
        cout << topline << endl;
        for (int i = 0; i < 8; i++) {
            cout << "|   " << middleline[i] << "   ";
        }
        cout << "| " << rownum[num] << endl;
        cout << bottomline << endl;
    }


    string topline = "|       |       |       |       |       |       |       |       |";
    string bottomline = "|_______|_______|_______|_______|_______|_______|_______|_______|";
    string middleline[8] = { " ", " ", " "," "," "," "," "," " };
    string rownum[8] = { "a", "b", "c", "d", "e", "f", "g", "h" };


private:


};

class Board {
public:
    void resetBoard() {
        for (int i = 2; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                rows[i].middleline[j] = " ";
            }

        }
        for (int j = 0; j < 7; j++) {
            rows[0].middleline[j + 1] = "b";
            rows[1].middleline[j] = "b";
            rows[2].middleline[j + 1] = "b";

            rows[5].middleline[j] = "w";
            rows[6].middleline[j + 1] = "w";
            rows[7].middleline[j] = "w";
            j++;
        }

    }
    void ClearScreen()
    {
        cout << string(100, '\n');
    }



    int rowHandling(string piece) {
        string letters = "abcdefgh";
        int rownum = -1;
        for (int i = 0; i < 8; i++) {
            if (piece[0] == letters[i]) {
                rownum = i;
            }
        }
        return rownum;
    }
    int colHandling(string piece) {
        string numbers = "12345678";
        int colnum = -1;
        for (int i = 0; i < 8; i++) {
            if (piece[1] == numbers[i]) {
                colnum = i;
            }
        }
        return colnum;
    }

    void nextTurn(string color) {
        string piece;
        int rownum = -1;
        int colnum = -1;
        cout << "Which piece would you like to move?(row-column)" << endl;
        cin >> piece;
        rownum = rowHandling(piece);
        colnum = colHandling(piece);
        if (rows[rownum].middleline[colnum] == color) {
            cout << "valid choice" << endl;
            if (color == "w") {
                nextMoveW(rownum, colnum);
            }
            else {
                nextMoveB(rownum, colnum);
            }

        }
        else if (rows[rownum].middleline[colnum] == "W" && color == "w") {
            cout << "White King" << endl;// need to build a move for kings
            kingMoveW(rownum, colnum);
        }
        else if (rows[rownum].middleline[colnum] == "B" && color == "b") {
            cout << "Black King" << endl;
            kingMoveB(rownum, colnum);
        }
    }

    void kingMoveW(int rownum, int colnum) {
        cout << "Where do you want to move?" << endl;
        string move;
        cin >> move;
        int rowdst = rowHandling(move);
        int coldst = colHandling(move);
        bool dir[4] = { false, false, false, false };//Up down left right
        if (rowdst - rownum > 1) {
            dir[1] = true;
        }
        if (rowdst - rownum < 1) {
            dir[0] = true;
        }
        if (coldst - colnum > 1) {
            dir[3] = true;
        }
        if (coldst - colnum < 1) {
            dir[2] = true;
        }

        if (abs(rowdst - rownum) == 2) { // check if attack jump
            if (abs(coldst - colnum) == 2) { // checks horizontal distance 
                if (rows[rowdst].middleline[coldst] == " ") { // checks if destination is empty
                    if (dir[0] && rownum > 1) {//going up!
                        if (dir[2] && colnum > 1) {//going left
                            if (rows[rowdst + 1].middleline[coldst + 1] == "b" || rows[rowdst + 1].middleline[coldst + 1] == "B") { // checks if there is something the unit is capturing
                                cout << "black unit captured" << endl;
                                blackPieces--;
                                rows[rowdst].middleline[coldst] = "W";
                                rows[rownum].middleline[colnum] = " ";
                                rows[rowdst + 1].middleline[coldst - 1] = " ";
                                doubleJumpW(rowdst, coldst);
                            }
                            else {// check to see if we would land on our own piece
                                kingMoveW(rownum, colnum);
                            }



                        }
                        else if (colnum < 6 && dir[3]) {//going right}
                            if (rows[rowdst + 1].middleline[coldst - 1] == "b" || rows[rowdst + 1].middleline[coldst - 1] == "B") { // checks if there is something the unit is capturing
                                cout << "black unit captured" << endl;
                                blackPieces--;
                                rows[rowdst].middleline[coldst] = "W";
                                rows[rownum].middleline[colnum] = " ";
                                rows[rowdst + 1].middleline[coldst - 1] = " ";
                                doubleJumpW(rowdst, coldst);
                            }
                            else {// check to see if we would land on our own piece
                                kingMoveW(rownum, colnum);
                            }
                        }
                    }
                    else if (dir[1] && rownum < 6) {//going down!
                        if (dir[2] && colnum > 1) {//going left
                            if (rows[rowdst - 1].middleline[coldst + 1] == "b" || rows[rowdst - 1].middleline[coldst + 1] == "B") {// down left
                                cout << "Black unit captured" << endl;
                                blackPieces--;
                                rows[rowdst].middleline[coldst] = "W";
                                rows[rownum].middleline[colnum] = " ";
                                rows[rowdst - 1].middleline[coldst + 1] = " ";
                                doubleJumpW(rowdst, coldst);


                            }
                            else {// check to see if we would land on our own piece
                                kingMoveW(rownum, colnum);
                            }
                        }
                        else if (dir[3] && colnum < 6) {//going right}
                            if (rows[rowdst - 1].middleline[coldst - 1] == "b" || rows[rowdst - 1].middleline[coldst - 1] == "B") { // (down right) checks if there is something the unit is capturing
                                cout << "Black unit captured" << endl;
                                blackPieces--;
                                rows[rowdst].middleline[coldst] = "W";
                                rows[rownum].middleline[colnum] = " ";
                                rows[rowdst - 1].middleline[coldst - 1] = " ";
                                doubleJumpW(rowdst, coldst);
                            }
                            else {// check to see if we would land on our own piece
                                kingMoveW(rownum, colnum);
                            }
                        }
                    }
                }
            }

        }
        else if (abs(rowdst - rownum) == 1) { // this is a single jump
            if (abs(coldst - colnum) == 1) {
                if (coldst <= 7 && coldst >= 0 && rowdst <= 7 && rowdst >= 0) {
                    if (rows[rowdst].middleline[coldst] == " ") {
                        rows[rowdst].middleline[coldst] = "W";
                        rows[rownum].middleline[colnum] = " ";
                    }
                }
            }
        }
    }


    // WORK HERE NEXT TIME ON CHANGING TO this kingw to black
    void kingMoveB(int rownum, int colnum) {
        cout << "Where do you want to move?" << endl;
        string move;
        cin >> move;
        int rowdst = rowHandling(move);
        int coldst = colHandling(move);
        bool dir[4] = { false, false, false, false };//Up down left right
        if (rowdst - rownum > 1) {//going down
            dir[1] = true;
        }
        if (rowdst - rownum < 1) {//going up
            dir[0] = true;
        }
        if (coldst - colnum > 1) {//going right
            dir[3] = true;
        }
        if (coldst - colnum < 1) {// going left
            dir[2] = true;
        }

        if (abs(rowdst - rownum) == 2) { // check if attack jump
            if (abs(coldst - colnum) == 2) { // checks horizontal distance 
                if (rows[rowdst].middleline[coldst] == " ") { // checks if destination is empty
                    if (dir[0] && rownum > 1) {//going up!
                        if (dir[2] && colnum > 1) {//going left
                            if (rows[rowdst + 1].middleline[coldst + 1] == "w" || rows[rowdst + 1].middleline[coldst + 1] == "W") { // checks (up-left) if there is something the unit is capturing
                                cout << "white unit captured" << endl;
                                whitePieces--;
                                rows[rowdst].middleline[coldst] = "B";
                                rows[rownum].middleline[colnum] = " ";
                                rows[rowdst + 1].middleline[coldst - 1] = " ";
                                doubleJumpB(rowdst, coldst);
                            }
                            else {// check to see if we would land on our own piece
                                cout << "That isnt a valid move" << endl;
                                kingMoveB(rownum, colnum);
                            }



                        }
                        else if (colnum < 6 && dir[3]) {//going right}
                            if (rows[rowdst + 1].middleline[coldst - 1] == "w" || rows[rowdst + 1].middleline[coldst - 1] == "W") { // checks(up-right) if there is something the unit is capturing
                                cout << "white unit captured" << endl;
                                whitePieces--;
                                rows[rowdst].middleline[coldst] = "B";
                                rows[rownum].middleline[colnum] = " ";
                                rows[rowdst + 1].middleline[coldst - 1] = " ";
                                doubleJumpB(rowdst, coldst);
                            }
                            else {// check to see if we would land on our own piece
                                cout << "That isnt a valid move" << endl;
                                kingMoveB(rownum, colnum);
                            }
                        }
                    }
                    else if (dir[1] && rownum < 6) {//going down!
                        if (dir[2] && colnum > 1) {//going left
                            if (rows[rowdst - 1].middleline[coldst + 1] == "w" || rows[rowdst - 1].middleline[coldst + 1] == "W") {//checks(down-left) if there is a white to capture
                                cout << "white unit captured" << endl;
                                whitePieces--;
                                rows[rowdst].middleline[coldst] = "B";
                                rows[rownum].middleline[colnum] = " ";
                                rows[rowdst - 1].middleline[coldst + 1] = " ";
                                doubleJumpB(rowdst, coldst);


                            }
                            else {// check to see if we would land on our own piece
                                cout << "That isnt a valid move" << endl;
                                kingMoveB(rownum, colnum);
                            }
                        }
                        else if (dir[3] && colnum < 6) {//going right}
                            if (rows[rowdst - 1].middleline[coldst - 1] == "w" || rows[rowdst - 1].middleline[coldst - 1] == "W") { // checks if there is something the unit is capturing
                                cout << "white unit captured" << endl;
                                whitePieces--;
                                rows[rowdst].middleline[coldst] = "B";
                                rows[rownum].middleline[colnum] = " ";
                                rows[rowdst - 1].middleline[coldst - 1] = " ";
                                doubleJumpB(rowdst, coldst);
                            }
                            else {// check to see if we would land on our own piece
                                cout << "That isnt a valid move" << endl;
                                kingMoveB(rownum, colnum);
                            }
                        }
                    }
                }
            }

        }
        else if (abs(rowdst - rownum) == 1) { // this is a single jump
            if (abs(coldst - colnum) == 1) {
                if (coldst >= 0 && coldst <= 7 && rowdst >= 0 && rowdst <= 7) {


                    if (rows[rowdst].middleline[coldst] == " ") { //need to consider capturing capital w
                        rows[rowdst].middleline[coldst] = "B";
                        rows[rownum].middleline[colnum] = " ";
                    }
                }
            }
        }
    }






    void doubleJumpW(int rownum, int colnum) {
        bool jumpOptions[4] = { false, false, false, false }; //up left, up right, down left, down right
        string jumpDir[4] = { "ul", "ur", "dl", "dr" };
        bool dJump = false;
        cout << "double" << endl;
        cout << rownum << " " << colnum << endl;
        if (rownum > 1 && colnum > 1) {// jump up and left
            if ((rows[rownum - 1].middleline[colnum - 1] == "b" || rows[rownum - 1].middleline[colnum - 1] == "B") && rows[rownum - 2].middleline[colnum - 2] == " ") {
                jumpOptions[0] = true;
                dJump = true;
            }
        }
        if (rownum > 1 && colnum < 6) { //jump up and right 
            cout << "up left" << endl;

            if ((rows[rownum - 1].middleline[colnum + 1] == "b" || rows[rownum - 1].middleline[colnum + 1] == "B") && rows[rownum - 2].middleline[colnum + 2] == " ") {
                cout << "ok to land" << endl;
                jumpOptions[1] = true;
                dJump = true;
            }
        }
        if (rownum < 6 && colnum > 1) { //jump down and left
            if ((rows[rownum + 1].middleline[colnum - 1] == "b" || rows[rownum + 1].middleline[colnum - 1] == "B") && rows[rownum + 2].middleline[colnum - 2] == " ") {
                jumpOptions[2] = true;
                dJump = true;
            }
        }
        if (rownum < 6 && colnum < 6) { //jump down and right
            if ((rows[rownum + 1].middleline[colnum + 1] == "b" || rows[rownum + 1].middleline[colnum + 1] == "B") && rows[rownum + 2].middleline[colnum + 2] == " ") {
                jumpOptions[3] = true;
                dJump = true;
            }
        }
        if (dJump) {
            string userChoice = "";
            cout << "Enter double jump option(ul, ur, dl, dr)" << endl;
            cin >> userChoice;
            if (userChoice == jumpDir[0]) {
                if (jumpOptions[0]) {
                    cout << "black unit captured" << endl;
                    blackPieces--;
                    if (rownum == 2) { // checks if destination is the first row
                        rows[rownum - 2].middleline[colnum - 2] = "W";
                    }
                    else {
                        rows[rownum - 2].middleline[colnum - 2] = "w";
                    }
                    rows[rownum].middleline[colnum] = " ";
                    rows[rownum - 1].middleline[colnum - 1] = " ";
                }
            }
            else if (userChoice == jumpDir[1]) {
                if (jumpOptions[1]) {
                    cout << "black unit captured" << endl;
                    blackPieces--;
                    if (rownum == 2) { // checks if destination is the first row
                        rows[rownum - 2].middleline[colnum + 2] = "W";
                    }
                    else {
                        rows[rownum - 2].middleline[colnum + 2] = "w";
                    }
                    rows[rownum].middleline[colnum] = " ";
                    rows[rownum - 1].middleline[colnum + 1] = " ";
                }
            }
            else if (userChoice == jumpDir[2]) {
                if (jumpOptions[2] && rows[rownum].middleline[colnum] == "W") {
                    cout << "black unit captured" << endl;
                    blackPieces--;
                    rows[rownum + 2].middleline[colnum - 2] = "W";
                    rows[rownum].middleline[colnum] = " ";
                    rows[rownum + 1].middleline[colnum - 1] = " ";
                }
            }
            else if (userChoice == jumpDir[3]) {
                if (jumpOptions[3] && rows[rownum].middleline[colnum] == "W") {
                    cout << "black unit captured" << endl;
                    blackPieces--;
                    rows[rownum + 2].middleline[colnum + 2] = "W";


                    rows[rownum].middleline[colnum] = " ";
                    rows[rownum + 1].middleline[colnum + 1] = " ";
                }
            }
            else {
                cout << "Invalid Jump" << endl;
            }
        }
    }
    void doubleJumpB(int rownum, int colnum) {
        bool jumpOptions[4] = { false, false, false, false }; //up left, up right, down left, down right
        string jumpDir[4] = { "ul", "ur", "dl", "dr" };
        bool dJump = false;
        cout << "double" << endl;
        cout << rownum << " " << colnum << endl;
        if (rownum > 1 && colnum > 1) {// jump up and left
            if ((rows[rownum - 1].middleline[colnum - 1] == "w" || rows[rownum - 1].middleline[colnum - 1] == "W") && rows[rownum - 2].middleline[colnum - 2] == " ") {
                jumpOptions[0] = true;
                dJump = true;
            }
        }
        if (rownum > 1 && colnum < 6) { //jump up and right 
            cout << "up left" << endl;

            if ((rows[rownum - 1].middleline[colnum + 1] == "w" || rows[rownum - 1].middleline[colnum + 1] == "W") && rows[rownum - 2].middleline[colnum + 2] == " ") {
                cout << "ok to land" << endl;
                jumpOptions[1] = true;
                dJump = true;
            }
        }
        if (rownum < 6 && colnum > 1) { //jump down and left
            if ((rows[rownum + 1].middleline[colnum - 1] == "w" || rows[rownum + 1].middleline[colnum - 1] == "W") && rows[rownum + 2].middleline[colnum - 2] == " ") {
                jumpOptions[2] = true;
                dJump = true;
            }
        }
        if (rownum < 6 && colnum < 6) { //jump down and right
            if ((rows[rownum + 1].middleline[colnum + 1] == "w" || rows[rownum + 1].middleline[colnum + 1] == "W") && rows[rownum + 2].middleline[colnum + 2] == " ") {
                jumpOptions[3] = true;
                dJump = true;
            }
        }
        if (dJump) {
            string userChoice = "";
            cout << "Enter double jump option(ul, ur, dl, dr)" << endl;
            cin >> userChoice;
            if (userChoice == jumpDir[0]) {
                if (jumpOptions[0] && rows[rownum].middleline[colnum] == "B") {
                    cout << "white unit captured" << endl;
                    whitePieces--;

                    rows[rownum - 2].middleline[colnum - 2] = "B"; //final landing is B
                    rows[rownum].middleline[colnum] = " "; // middle jump is empty
                    rows[rownum - 1].middleline[colnum - 1] = " ";// second jumped is empty
                }
            }
            else if (userChoice == jumpDir[1]) {
                if (jumpOptions[1] && rows[rownum].middleline[colnum] == "B") {
                    cout << "white unit captured" << endl;
                    whitePieces--;

                    rows[rownum - 2].middleline[colnum + 2] = "B";
                    rows[rownum].middleline[colnum] = " ";
                    rows[rownum - 1].middleline[colnum + 1] = " ";
                }
            }
            else if (userChoice == jumpDir[2]) {
                if (jumpOptions[2]) {//down left
                    cout << "white unit captured" << endl;
                    whitePieces--;
                    if (rownum == 5) {
                        rows[rownum + 2].middleline[colnum - 2] = "B";
                    }
                    else {
                        rows[rownum + 2].middleline[colnum - 2] = "b";
                    }
                    rows[rownum].middleline[colnum] = " ";
                    rows[rownum + 1].middleline[colnum - 1] = " ";

                }
            }
            else if (userChoice == jumpDir[3]) {
                if (jumpOptions[3]) {//downright
                    cout << "white unit captured" << endl;
                    whitePieces--;
                    if (rownum == 5) {
                        rows[rownum + 2].middleline[colnum + 2] = "B";
                    }
                    else {
                        rows[rownum + 2].middleline[colnum + 2] = "b";
                    }

                    rows[rownum].middleline[colnum] = " ";
                    rows[rownum + 1].middleline[colnum + 1] = " ";
                }
            }
            else {
                cout << "Invalid Jump" << endl;
            }
        }
    }

    void nextMoveW(int rownum, int colnum) {
        cout << "Where do you want to move?" << endl;
        string move;
        cin >> move;
        int rowdst = rowHandling(move);
        int coldst = colHandling(move);

        if (rowdst - rownum == -2) { // check if single jump
            if (abs(coldst - colnum) == 2) { // checks horizontal distance 
                if (rows[rowdst].middleline[coldst] == " ") { // checks if destination is empty
                    if (coldst - colnum > 0) { // checks jump right
                        if (rows[rowdst + 1].middleline[coldst - 1] == "b" || rows[rowdst + 1].middleline[coldst - 1] == "B") { // checks if there is something the unit is capturing
                            cout << "black unit captured" << endl;
                            blackPieces--;
                            if (rowdst == 0) { // checks if destination is the first row
                                rows[rowdst].middleline[coldst] = "W";
                            }
                            else {
                                rows[rowdst].middleline[coldst] = "w";
                            }
                            rows[rownum].middleline[colnum] = " ";
                            rows[rowdst + 1].middleline[coldst - 1] = " ";
                            doubleJumpW(rowdst, coldst);
                        }
                        else {// check to see if we would land on our own piece
                            nextMoveW(rownum, colnum);
                        }
                    }
                    else {// jumping left
                        if (rows[rowdst + 1].middleline[coldst + 1] == "b" || rows[rowdst + 1].middleline[coldst + 1] == "B") {// checks if there is something the unit is capturing
                            cout << "black unit captured" << endl;
                            blackPieces--;
                            if (rowdst == 0) {
                                rows[rowdst].middleline[coldst] = "W";
                            }
                            else {
                                rows[rowdst].middleline[coldst] = "w";
                            }
                            rows[rownum].middleline[colnum] = " ";
                            rows[rowdst + 1].middleline[coldst + 1] = " ";
                            doubleJumpW(rowdst, coldst);
                            //if(rows[rowdst+1].middleline[coldst+1] == "b" && rows[rowdst+2].middleline[coldst+2] == " ")
                        }
                        else if (rows[rowdst].middleline[coldst] == "w") {// check to see if we would land on our own piece
                            nextMoveW(rownum, colnum);
                        }
                    }

                }
            }
        }
        else if (rowdst - rownum == -1) {
            if (abs(coldst - colnum) == 1) {
                if (rows[rowdst].middleline[coldst] == " ") { //need to consider capturing capital w

                    if (rowdst == 0) {
                        rows[rowdst].middleline[coldst] = "W";
                    }
                    else {
                        rows[rowdst].middleline[coldst] = "w";
                    }
                    rows[rownum].middleline[colnum] = " ";
                }
            }
        }
    }





    void nextMoveB(int rownum, int colnum) {
        cout << "Where do you want to move?" << endl;
        string move;
        cin >> move;
        int rowdst = rowHandling(move);
        int coldst = colHandling(move);

        if (rowdst - rownum == 2) { // check if double jump
            if (coldst == colnum - 2 || coldst == colnum + 2) { // checks horizontal distance 
                if (rows[rowdst].middleline[coldst] == " ") { // checks if destination is empty
                    if (coldst - colnum > 0) { // checks direction
                        if (rows[rowdst - 1].middleline[coldst - 1] == "w" || rows[rowdst - 1].middleline[coldst - 1] == "W") { // checks if there is something the unit is capturing
                            cout << "White unit captured" << endl;
                            whitePieces--;
                            if (rowdst == 7) { // checks if destination is the first row
                                rows[rowdst].middleline[coldst] = "B";
                            }
                            else {
                                rows[rowdst].middleline[coldst] = "b";
                            }
                            rows[rownum].middleline[colnum] = " ";
                            rows[rowdst - 1].middleline[coldst - 1] = " ";
                            doubleJumpB(rowdst, coldst);
                        }
                        else if (rows[rowdst].middleline[coldst] == "b") {// check to see if we would land on our own piece
                            nextMoveB(rownum, colnum);
                        }
                    }
                    else {// jumping left
                        if (rows[rowdst - 1].middleline[coldst + 1] == "w" || rows[rowdst - 1].middleline[coldst - 1] == "W") {
                            cout << "White unit captured" << endl;
                            whitePieces--;
                            if (rowdst == 7) {
                                rows[rowdst].middleline[coldst] = "B";
                            }
                            else {
                                rows[rowdst].middleline[coldst] = "b";
                            }
                            rows[rownum].middleline[colnum] = " ";
                            rows[rowdst - 1].middleline[coldst + 1] = " ";
                            doubleJumpB(rowdst, coldst);


                        }
                        else if (rows[rowdst].middleline[coldst] == "b") {// check to see if we would land on our own piece
                            nextMoveB(rownum, colnum);
                        }
                    }
                }
            }
        }
        else if (rowdst - rownum == 1) {
            if (abs(coldst - colnum) == 1) {
                if (rows[rowdst].middleline[coldst] == " ") { //need to consider capturing capital w
                    if (rowdst == 7) {
                        rows[rowdst].middleline[coldst] = "B";
                    }
                    else {
                        rows[rowdst].middleline[coldst] = "b";
                    }
                    rows[rownum].middleline[colnum] = " ";

                }
            }
        }
    }






    void printBoard() {
        ClearScreen();
        cout << "_________________________________________________________________" << endl;
        for (int i = 0; i < 8; i++) {
            rows[i].printRow(i);
        }
        cout << "    1       2       3       4       5       6       7       8   " << "\n\n\n\n" << endl;
    }
    Row rows[8];

    void play() {
        printBoard();
        while (whitePieces > 0 && blackPieces > 0) {
            cout << "White Turn" << endl;
            cout << whitePieces << endl;
            nextTurn("w");

            printBoard();
            if (blackPieces < 1) {
                cout << "White Wins" << endl;
                break;
            }
            cout << "Black Turn" << endl;
            cout << blackPieces << endl;
            nextTurn("b");
            printBoard();
            if (whitePieces < 1) {
                cout << "Black Wins" << endl;
                break;
            }
        }
    }

private:
    int whitePieces = 12;
    int blackPieces = 12;
};


int main() {
    Board board;
    board.resetBoard();
    board.play();
}


//WHITE double jump almost works pick up from here


// f1 e2 c2 d3 e2 d1 c4 d5 d1 c2 b3 c4 c2 b3 b1 c2 sw a2 b1 sw b3 a2 sw a4 b3 sw d3 e2 sw c4 d3 a2 c4
// b3 a2 a4 b3 


// f3 e2 c4 d3 sw d3 e4 f5 e6 e4 f3 g4 f5 sb h5 g4 f3 h5 h3 g4
// above line gets you to move before double
// h5 f3 ul f1 e2 d1 f3 dr f7 e8 h5 f7 ul e8 d7 c8 e6 dl 
// skip white
//
// skip white 
//
// white king in a2 

// Possibly done?



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
