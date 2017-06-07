package AddressBookSearch;

public class AddressInfo {
	private String FirstName;
	private String LastName;
	private String PhoneNumber;
	private String CompanyName;
	public AddressInfo(){};
	public String GetFirstName(){
		return this.FirstName;
	}
	public String GetLastName(){
		return this.LastName;
	}
	public String GetPhoneNumber(){
		return this.PhoneNumber;
	}
	public String GetCompanyName(){
		return this.CompanyName;
	}
	public void SetFirstName(String f){
		this.FirstName = f;
	}
	public void SetLastName(String l){
		this.LastName = l;
	}
	public void SetPhoneNumber(String p){
		this.PhoneNumber = p.replaceAll("\\D", "");;
	}
	public void SetCompanyName(String c){
		this.CompanyName = c;
	}
	public void SetAddressInfo(String line){
		String SArray[] = line.split(",");
		this.SetFirstName(SArray[0]);
		this.SetLastName(SArray[1]);
		this.SetPhoneNumber(SArray[2]);
		this.SetCompanyName(SArray[3]);
		
	}
}
