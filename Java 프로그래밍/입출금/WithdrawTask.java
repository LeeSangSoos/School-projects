package Lab_13;

public class WithdrawTask implements Runnable {
	public Account account = null;
	public WithdrawTask(Account acc) {
		account = acc;
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		while(true) {
			account.withdraw((int)(Math.random() * 10) + 1);
		}
	}
}