package checkers_game;

import org.junit.Test;

import javax.swing.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import static org.junit.Assert.*;

public class CheckersGame {
        static {
            System.load("/Users/antonsidlyar/CLionProjects/CheckersCPPLogic/cmake-build-debug/libCheckersCPPLogic.dylib");
        }
//        @Test
//        public void testInvalidNonDiagonalMove() {
//            CheckersGame game = new CheckersGame();
//            boolean success = game.movePiece(2, 3, 2, 4); // Try to move horizontally
//            assertFalse(success); // must be false,  it is not a diagonal move
//        }
//    @Test
//    public void testCaptureMove() {
//        CheckersGame game = new CheckersGame();
//        game.movePiece(2, 1, 3, 2); //  settings for  board // making an initial valid move
//        game.movePiece(5, 2, 4, 1); //  enemy moves closer for a capture setup
//
//        boolean success = game.movePiece(3, 2, 5, 0); // capture move
//        assertTrue(success); // capture should be valid
//
//        int[][] board = game.getBoardState();
//        assertEquals(0, board[4][1]); // removaem cptured piece
//        assertEquals(1, board[5][0]); // piece moved to new position
//*    }
        private CheckersBoard boardPanel;
        private int selectedX = -1, selectedY = -1;  //  track the  currently selected piece

        //native methods
        public native int[][] getBoardState();
        public native boolean movePiece(int fromX, int fromY, int toX, int toY);

        public CheckersGame() {
            int[][] initialBoard = getBoardState();
            boardPanel = new CheckersBoard(initialBoard);

            // Handle mouse clicks for moving pieces
            boardPanel.addMouseListener(new MouseAdapter() {
                @Override
                public void mouseClicked(MouseEvent e) {
                    System.out.println("click");
                    int tileSize = boardPanel.getWidth() / 8; // Assume square board
                    int clickedX = e.getY() / tileSize;
                    int clickedY = e.getX() / tileSize;

                    if (selectedX == -1 && selectedY == -1) {
                        // first click: select a piece
                        selectedX = clickedX;
                        selectedY = clickedY;
                        System.out.println("Selected piece at: " + selectedX + ", " + selectedY);
                    } else {
                        // second click: move the piece
                        boolean turnEnded = movePiece(selectedX, selectedY, clickedX, clickedY);

                        if (turnEnded) {
                            System.out.println("Move completed.");
                            selectedX = -1;
                            selectedY = -1; // reset selection if the turn ends
                        } else {
                          //  System.out.println("Bad move or another capture is still possible");
                            selectedX = clickedX;
                            selectedY = clickedY; // update selected piece position to continue capturing
                        }

                        updateBoardState(); // refresh the board in all cases
                    }
                }
            });
        }

        // Main method for testing JNI calls
        public static void main(String[] args) {
//            SwingUtilities.invokeLater(() -> { // not needed
                CheckersGame game = new CheckersGame();
                JFrame frame = new JFrame("Checkers Game");
                frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                frame.add(game.boardPanel);
                frame.pack();
                frame.setVisible(true);
//            });

        }
        // Method to update the board after every move
        public void updateBoardState() {
            int[][] updatedBoard = getBoardState();
            boardPanel.updateBoard(updatedBoard);
        }

    }








// tests*
//            // test of the first move!!
//            if (game.movePiece(2, 1, 3, 2)) {
//            System.out.println("move is successful ");
//            } else {
//            System.out.println("move is invalid");
//            }

//
//            // updating board state( test)
//            int[][] boardState = game.getBoardState();
//            for (int[] row : boardState) {
// *tests

//            for (int cell : row) {
//            System.out.print(cell + " ");
//            }
//            System.out.println();


