package FindingMine;

import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Game new_game = new Game ();
		int i, j, action;
		Scanner scan = new Scanner(System.in);
		
		while (true) {
			System.out.print("Enter the coordinate with action :");
			i = scan.nextInt();
			j = scan.nextInt();
			action = scan.nextInt();
			if(i>=15||j>=15) {
				System.out.println("Coordinate out of range. please re-enter\n");
				continue;
			}
			
			if (!new_game.UpdateStatus(i, j, action)) {
				new_game.GameOver ();
				break;
			}
			
			new_game.PrintBoard();
			
			if (new_game.GameEnd())		break;
		}
	}

}
