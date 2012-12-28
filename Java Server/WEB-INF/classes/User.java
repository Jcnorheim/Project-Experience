

import java.io.IOException;
import java.sql.SQLException;
import java.util.ArrayList;

public class User {
	protected String username;
	protected ArrayList<Account> accounts;
	protected double sum;
	protected BankSys bs=new BankSys();
	
	public User(String username, ArrayList<Account> al) throws IOException{
		this.username=username;
		accounts=al;
	}
	public boolean createAcc(String type, double balance) throws IOException{
		Account a=bs.setAcc(0, username, type, true);
		updateAcc();
		accounts.add(a);
		updateAcc();
		return true;
	}
	public boolean removeAcc(Account account, int ind) throws IOException{
		if(account.getBalance()==0){
			bs.remove(account);
			accounts.remove(ind);
			return true;
			}
		else return false;
	}
	public String accountList(){
		String re="";
		for(int i=0; i<accounts.size(); i++){
			re+=accounts.get(i).getType()+" "+i+": "+accounts.get(i).getBalance()+"\n";
		}
		return re;
	}
	public Account getAcc(int i){
		return accounts.get(i);
	}
	public double sumBalance(){
		for(Account a:accounts){
			sum+=a.getBalance();
		}
		return sum;
	}
	private void updateAcc() throws IOException{
		accounts=bs.initializeAcc(username);
	}
}
