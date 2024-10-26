package Lab_13;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Account {
	// Create a lock
	private static Lock lock = new ReentrantLock();
	
	// Create a condition
	private static Condition newDeposit = lock.newCondition();
	
	// Balance Value is private 
	private int balance = 1;
	public int getBalance() {
		return balance;
	}
	
	public void withdraw(int amount) {
		// get the lock 
		lock.lock();
		// await until balance is larger than amount,
		try {
			if(this.balance>amount) {
				this.balance=this.balance-amount;
				System.out.println("\t\t\t"+"Withdraw "+amount+"\t\t"+this.balance);
			}
			else {
				System.out.println("\t\t\t"+"Wait for a deposit");
				newDeposit.await();
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// unlock the lock
		lock.unlock();
	}
	
	public void deposit(int amount) {
		// get the lock 
		lock.lock();
		// add amount to account balance
		this.balance=this.balance+amount;
		// print current balance
		System.out.println("Deposit "+amount+"\t\t\t\t\t"+this.balance);
		// signal to withdraw tasks
		newDeposit.signalAll();
		// unlock the lock
		lock.unlock();
	}
	
	

}