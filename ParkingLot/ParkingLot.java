package Parkinglot;

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
