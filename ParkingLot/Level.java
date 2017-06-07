package Parkinglot;

import java.util.HashMap;

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