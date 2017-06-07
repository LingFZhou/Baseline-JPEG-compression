package Parkinglot;

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
