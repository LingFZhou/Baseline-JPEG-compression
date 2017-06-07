package Parkinglot;
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
