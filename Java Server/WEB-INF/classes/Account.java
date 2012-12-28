
import java.io.IOException;

public abstract class Account {

	protected double interestRate;
	protected double balance;
	protected Type type;
	protected int index;
	protected BankSys bs=new BankSys();
	
	public Account(int i){
		index=i;
	}
	public double checkBalance(){
		return balance;
	}
	public void makeDeposite(double value, boolean update)throws IOException{
		balance+=value;
		if(update)
		bs.change(this, balance, false);
	}
	public boolean trans(Account acount, double value)throws IOException{
		if(validTrans(value)){
		acount.makeDeposite(value, true);
		balance-=value;
		bs.change(this, balance, true);
		return true;
		}
		else return false;
	}
	public boolean validTrans(double value){
		return balance>=value;
	}
	public Type getType(){
		return type;
	}
	public double getBalance(){
		return balance;
	}
	public int getIndex(){
		return index;
	}
}
