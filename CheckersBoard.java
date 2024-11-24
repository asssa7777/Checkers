package checkers_game;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
public class CheckersBoard extends JPanel {
    private int [][] board;

    public CheckersBoard(int [][] initialBoard) {
        this.board = initialBoard;
        setPreferredSize(new Dimension(400, 400));
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        drawBoard(g);
    }

    private void drawBoard(Graphics g) {
        int tileSize = 50;
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                //  colors for the board tiles
                if ((row + col) % 2 == 0) {
                    g.setColor(Color.LIGHT_GRAY);
                } else {
                    g.setColor(Color.DARK_GRAY);
                }
                g.fillRect(col * tileSize, row * tileSize, tileSize, tileSize);

                // draw pieces
                if (board[row][col] == 1) {
                    g.setColor(Color.BLACK); // player 1 piece
                    g.fillOval(col * tileSize + 5, row * tileSize + 5, 40, 40);
                } else if (board[row][col] == 2) {
                    g.setColor(Color.WHITE); // player 2 piece
                    g.fillOval(col * tileSize + 5, row * tileSize + 5, 40, 40);
                } else if (board[row][col] == 3) {
                    g.setColor(Color.BLACK); // player 1 king
                    g.fillOval(col * tileSize + 5, row * tileSize + 5, 40, 40);
                    g.setColor(Color.YELLOW); // king crown
                    g.drawString("K", col * tileSize + 20, row * tileSize + 30);
                } else if (board[row][col] == 4) {
                    g.setColor(Color.WHITE); // player 2 king
                    g.fillOval(col * tileSize + 5, row * tileSize + 5, 40, 40);
                    g.setColor(Color.YELLOW); // king crown
                    g.drawString("K", col * tileSize + 20, row * tileSize + 30);
                }
            }
        }
    }
    public void updateBoard(int[][] newBoard) {
        this.board = newBoard;
        repaint(); // Repaint the board with the new state
    }
}
