package Parkinglot;

interface ParkAction{
	public void park(Level lev);
	public void unpark(Level lev);
	public String getDesc();
	public void SendMsg();
	public int getSpotID();
	public int getLevelID();
	
}
