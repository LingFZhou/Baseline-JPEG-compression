package Parkinglot;

import java.util.HashMap;

class ParkingSpot implements ParkAction {
    private int spotID;
    private boolean isAvailable;
    private int levelID;  
    private HashMap level;
    private String desc;
  
  
    public ParkingSpot(int id, int levelID, String s){
      this.spotID = id;
      this.levelID = levelID;
      isAvailable = true;
      desc = s;
      level = new HashMap();
    }
    public String getDesc(){
        return desc;
      }
    public void park(Level lev){
        level.put(lev.getDesc(),lev);
      }
      public void unpark(Level lev){
        level.remove(lev.getDesc());
      }
      public void setState(boolean occupied){
          isAvailable = !occupied;
      }
      public boolean getState(){
          return isAvailable;
      }
      public int getSpotID(){
    	  return spotID;
      }
  	  public int getLevelID(){
  		  return levelID;
  	  }
  	  public void SendMsg(){
  		  
  	  }
}
