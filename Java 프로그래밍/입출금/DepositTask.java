package Lab_13;

public class DepositTask implements Runnable {
	public Account account = null;
	

	public DepositTask(Account acc) {
		account = acc;
	}
	
	@Override
	public void run() {
		// TODO Auto-generated method stub
		try {
			while(true) {
				account.deposit((int)(Math.random() * 10) + 1);
				Thread.sleep(1000);
			}
		}
		catch (InterruptedException ex) {
			ex.printStackTrace();
		}
	}
}