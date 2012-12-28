

import java.io.IOException;
import java.util.ArrayList;
import java.io.*;


public class BankSys {
	protected log fileio = new log();
	protected Account a=null, from=null, to=null, move=null;
	public Account setAcc(int index, String user, String type, boolean add) throws IOException{
		if(!add){
		if(type.toLowerCase().equals("checking"))
			a=new Checking(index);
		else if(type.toLowerCase().equals("saving"))
			a=new Saving(index);
		else if(type.toLowerCase().equals("moneymarket"))
			a=new Money(index);
		}
		else {
		fileio.addAcc(user, type);
		}
		return a;
	}
	
	public ArrayList<Account> initializeAcc(String username)throws IOException{
		ArrayList<Account> accounts=fileio.getAccs(username);
		return accounts;
	}
	public void change(Account a, double balance, boolean out)throws IOException{
		fileio.modify(a.getIndex(), balance, true);
		if(out)
		from=a;
		else
		to=a;
	}
	public void remove(Account a)throws IOException{
		fileio.modify(a.getIndex(), 0, false);
		move=a;
	}
	public void remove(int index)throws IOException{
		fileio.modify(index, 0, false);
		
	}
	
}
