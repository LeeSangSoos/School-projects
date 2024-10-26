package FindingMine;

import java.util.Random;

public class Board {
	String[][] board;
	int N;
	
	public Board (int n) {
		this.board = new String[n][n];
		this.N = n;
		InitBoard ();
	}
	
	void InitBoard () {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				board[i][j] = " ";
			}
		}
	}
	
	String getPoint (int i, int j) {
		return this.board [i][j];
	}
}

class MineBoard extends Board {
	// You can also add private variable here
	public MineBoard(int n, int num_mine) {
		super(n);
		
		
		/* You can also edit here */
		
		InitBoard (num_mine);
	}
	
	// Initializes board with randomly created mines. 
	void InitBoard(int num_mine) {
		long seed = System.currentTimeMillis();
		Random rand = new Random ();
		rand.setSeed(seed);
		
		for (int i = 0; i < num_mine; i++) {
			while(true) {
				int a = rand.nextInt(N);
				int b = rand.nextInt(N);
				if(board[a][b]!="M") {
					board[a][b] = "M";
					break;
				}
			}
		}
	}
	
	/* You can freely add functions below */
}

class HintBoard extends Board {
	public HintBoard(int n, MineBoard mine) {
		super(n);
		
		InitBoard (mine);
	}
	
	// Initialize Hint Board with hint numbers (the number of mines among adjacent tiles.)
	// If there's no mine Set as 0.
	void InitBoard (MineBoard mine) {
		/* Fill here. */
		int amount=0;
		for(int i=0;i<N;i++) {
			for(int j=0;j<N;j++) {
				if(mine.board[i][j]!="M") {
					if(i-1>-1&&j-1>-1) {
					if(mine.board[i-1][j-1]=="M")
						amount++;
					}
					if(i-1>-1) {
					if(mine.board[i-1][j]=="M")
						amount++;
					}
					if(i-1>-1&&j+1<15) {
					if(mine.board[i-1][j+1]=="M")
						amount++;
					}
					if(j-1>-1) {
					if(mine.board[i][j-1]=="M")
						amount++;
					}
					if(j+1<15) {
					if(mine.board[i][j+1]=="M")
						amount++;
					}
					if(i+1<15&&j-1>-1) {
					if(mine.board[i+1][j-1]=="M")
						amount++;
					}
					if(i+1<15) {
					if(mine.board[i+1][j]=="M")
						amount++;
					}
					if(i+1<15&&j+1<15) {
					if(mine.board[i+1][j+1]=="M")
						amount++;
					}
					board[i][j]=Integer.toString(amount);
				}
				else
					board[i][j]="M";
				amount=0;
			}
		}	
	}
}
