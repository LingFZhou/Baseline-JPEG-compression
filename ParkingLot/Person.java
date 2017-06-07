package Parkinglot;

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
