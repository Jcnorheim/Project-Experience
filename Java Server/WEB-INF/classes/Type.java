

public enum Type {
	checking(0), saving(1), moneymarket(2);
	private int index;
	private Type(int v){
		index=v;
	}
	public int getIndex(){
		return index;
	}
	public static Type getType(int i){
		if(i==0)
			return checking;
		if(i==1)
			return saving;
		else return moneymarket;
	}
}
