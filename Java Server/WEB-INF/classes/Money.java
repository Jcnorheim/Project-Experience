

public class Money extends Account{
	public Money(int i){
		super(i);
		type=Type.moneymarket;
		interestRate=1.2;
	}

	public boolean validTrans(double value){
		return balance>=value;
	}
}
