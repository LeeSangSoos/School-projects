package Lab_13;


import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainClass {

	public static void main(String[] args) {
		
		ExecutorService executor = Executors.newFixedThreadPool(2);
		
		Account account = new Account();
		
		DepositTask dt = new DepositTask(account);
		WithdrawTask wt = new WithdrawTask(account);
		
		executor.execute(dt);
		executor.execute(wt);
		
		executor.shutdown();
		System.out.println("Thread 1\t\tThread 2\t\tBalance");

	}

}