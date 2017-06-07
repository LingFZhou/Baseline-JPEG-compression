package Parking;
import java.io.*;
import java.util.*;


class Person{
    CommandInterface command;
    public Person(){     
    }
    public void setCommand(CommandInterface c){
      command = c;
    }
    public void process(){
      command.execute();
    } 
}

interface CommandInterface{
  public void execute();
}
class ParkCommand implements CommandInterface{
  ParkAction parkingspot;
  Level level;

  public ParkCommand(ParkAction i, Level c){
    parkingspot = i;
    level = c;
  }
  public void execute(){
    parkingspot.park(level);
    level.park(parkingspot);
  }

}
class UnparkCommand implements CommandInterface{
  ParkAction parkingspot;
  Level level;

  public UnparkCommand(ParkAction i, Level c){
    parkingspot = i;
    level = c;
  }
  public void execute(){
    parkingspot.unpark(level);
    level.unpark(parkingspot);
  }

}
class Level{
  private static final int spotCapacity = 100;
  private int levelID;
  private ParkingSpot[] parkSpots;
  private int currentAvailable;
  private int currentNotAvailable;
  private HashMap parkingspot;
  private String desc;
  
  public Level(int id, String s){
    // initialization parking spots
    desc = s;
    parkingspot = new HashMap();
    this.levelID = id;
    ParkingSpot[] parkSpots = new ParkingSpot[spotCapacity];
    for(int i = 0; i < spotCapacity; i++){
       ParkingSpot ps = new ParkingSpot( levelID * 1000 + i,2, "" );
       parkSpots[i] = ps;
    }
    currentAvailable = spotCapacity;
    currentNotAvailable = 0;
  }
  public String getDesc(){
    return desc;
  }
  public void park(ParkAction i){
    parkingspot.put(i.getDesc(), i);
    System.out.println("ParkingSpot '" + i.getDesc() + "' has " +
       "been used in '" + getDesc() + "' Level ");
  }
  public void unpark(ParkAction i){
    parkingspot.remove(i.getDesc());
    System.out.println("ParkingSpot '" + i.getDesc() + 
       " is available in '" + getDesc() + " 'Level ");
  }
  // return minimal spotID as available parking spot
  public ParkingSpot getParkingSpot(){
      for(int i = 0; i < parkSpots.length; i++){
          if( parkSpots[i].getState() == true ){
              parkSpots[i].setState(true);
              return parkSpots[i];
          }
      }
      return null;
  }
  public void putParkingSpot(){
      currentAvailable++;
      currentNotAvailable--;
  }
  public int getCurrentAvailable(){
      return this.currentAvailable;
  }
  
}


	
class ParkingLot{
  private static final int levelCapacity = 5;
  private static final int levelSpotCapacity = 100;
  private Level[] levels;
  private static ParkingLot parkingLot = new ParkingLot();
  private ParkingLot(){
  	 levels = new Level[levelCapacity];
     for(int i = 0; i < levelCapacity; i++){
        Level level = new Level(i+1, "");
        levels[i] = level;
     }
     System.out.println("Parking Lot created, Singleton mode sucessfully implemented");
     System.out.println("This Parking Lot has " + levelCapacity + " levels");
     System.out.println("Each level has " + levelSpotCapacity + " spots");
     System.out.println();
  }
  public static ParkingLot getInstance(){
	  return parkingLot;
  }
  
  public Level getAvailableLevel(){
      for( int i = 0; i < levels.length; i++){
          if( levels[i].getCurrentAvailable() > 0 ){
              return levels[i];
          }
      }
  return null;
  }
  
}

interface ParkAction{
	public void park(Level lev);
	public void unpark(Level lev);
	public String getDesc();
	public void SendMsg();
	public int getSpotID();
	public int getLevelID();
	
}

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

class DecoratorbigParkingSpot implements ParkAction{
	private int spotID;
    private boolean isAvailable;
    private int levelID;  
    private HashMap level;
    private String desc;

    public DecoratorbigParkingSpot(int id, int levelID, String s){
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
    public int getSpotID(){
        return spotID;
    }
    public int getLevelID(){
        return levelID;
    }

    public void setState(boolean occupied){
        isAvailable = !occupied;
    }
    public boolean getState(){
        return isAvailable;
    }
    public void SendMsg(){
    	System.out.println("This is number " + getSpotID() + " big spot");
    }
}

class DecoratorsmallParkingSpot implements ParkAction {
    private int spotID;
    private boolean isAvailable;
    private int levelID;  
    private HashMap level;
    private String desc;
  
    public DecoratorsmallParkingSpot(int id, int levelID, String s){
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
    public int getSpotID(){
        return spotID;
    }
    public int getLevelID(){
        return levelID;
    }

    public void setState(boolean occupied){
        isAvailable = !occupied;
    }
    public boolean getState(){
        return isAvailable;
    }
    public void SendMsg(){
    	System.out.println("This is number " + getSpotID() + " small spot");
    }
}




class Solution {
  public static void main(String[] args) {
      ParkingLot parkLot = null;
      parkLot.getInstance();
      ParkAction ps = new ParkingSpot(2,2,"parkingspot");
      Level lev = new Level(2,"level 2");
      CommandInterface command = new ParkCommand(ps, lev);
      Person person = new Person();
      person.setCommand(command);
      person.process();
      System.out.println();    		  
    		  
      ParkAction Bigps = new DecoratorbigParkingSpot(10,3,"bigParkingSpot");
      Level Biglev = new Level(3,"level 3");
      command = new ParkCommand(Bigps, Biglev);
      person.setCommand(command);
      person.process();
      Bigps.SendMsg();
      System.out.println();
      
      ParkAction Smallps = new DecoratorsmallParkingSpot(40,2,"smallParkingSpot");
      Level Smalllev = new Level(2,"level 3");
      command = new ParkCommand(Smallps, Smalllev);
      person.setCommand(command);
      person.process();
      Smallps.SendMsg();
      System.out.println();
      
      
      command = new UnparkCommand(Bigps,Biglev);
      person.setCommand(command);
      person.process();
      Bigps.SendMsg();
      System.out.println();
  }
}