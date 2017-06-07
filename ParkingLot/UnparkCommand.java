package Parkinglot;

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