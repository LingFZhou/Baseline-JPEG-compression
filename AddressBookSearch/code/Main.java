package AddressBookSearch;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.SortedMap;
import java.util.TreeMap;


public class Main {
	public static void main(String[] args){
		File file = new File("SmallAddressBook.csv");
		long startTime = System.currentTimeMillis();
		ArrayList<AddressInfo> AddressList = new ArrayList<AddressInfo>();
		
		//Read data from file
		ReadFile(file, AddressList);
		
		//Create 4 TreeMap to complete sort and search
		TreeMap<String,ArrayList<String>> FirstNameMap = new TreeMap<String,ArrayList<String>>();
		TreeMap<String,ArrayList<String>> LastNameMap = new TreeMap<String,ArrayList<String>>();
		TreeMap<String,ArrayList<String>> PhoneNumberMap = new TreeMap<String,ArrayList<String>>();
		TreeMap<String,ArrayList<String>> CompanyNameMap = new TreeMap<String,ArrayList<String>>();
		
		//Record the index of every attribute
		ArrayList<String> FirstNameIndex = new ArrayList<String>();
		ArrayList<String> LastNameIndex = new ArrayList<String>();
		ArrayList<String> PhoneNumberIndex = new ArrayList<String>();
		ArrayList<String> CompanyNameIndex = new ArrayList<String>();
		
		
		for(int i = 0;i < AddressList.size();i++){
			FirstNameIndex.add(AddressList.get(i).GetFirstName() + ':' + i);
			LastNameIndex.add(AddressList.get(i).GetLastName() + ':' + i);
			PhoneNumberIndex.add(AddressList.get(i).GetPhoneNumber() + ':' + i);
			CompanyNameIndex.add(AddressList.get(i).GetCompanyName() + ':' + i);
		}
		//Set key-value to TreeMap, and every key map to one list to ensure no data missing
		KeyValue(FirstNameIndex,FirstNameMap);
		KeyValue(LastNameIndex,LastNameMap);
		KeyValue(PhoneNumberIndex,PhoneNumberMap);
		KeyValue(CompanyNameIndex,CompanyNameMap);
		
		long endTime = System.currentTimeMillis();
		System.out.println("Welcome to AddressBook, initialized. ("+ (endTime - startTime) + "ms)");
		String s = new String();
		int flag = 1;
		int start = -1;
		while (flag != 0) { 
			if (flag == 1) { 
				System.out
						.println("What would you like to search on? (F,L,P,C)");
			}
			switch (GetChar()) { 
			//Search by first name
			case 'f':
			case 'F':
				System.out.println("Enter the partial First Name:");
				s = GetString();
				startTime = System.currentTimeMillis();
				PrintInfo(s, FirstNameMap, AddressList);
				endTime = System.currentTimeMillis();
				System.out.print(" " + (endTime - startTime) + "ms\n\n");
				flag = loop(); 
				break;
			//Search by last name	
			case 'l':
			case 'L':
				System.out.println("Enter the partial Last Name:");
				s = GetString();
				startTime = System.currentTimeMillis();
				PrintInfo(s, LastNameMap, AddressList);
				endTime = System.currentTimeMillis();
				System.out.print(" " + (endTime - startTime) + "ms\n\n");
				flag = loop(); 
				break;
			//Search by phone number
			case 'P':
			case 'p':
				System.out.println("Enter the partial Phone Number:");
				// Remove non-digit chars
				s = GetString().replaceAll("\\D", ""); 
				startTime = System.currentTimeMillis();
				PrintInfo(s, PhoneNumberMap, AddressList);
				endTime = System.currentTimeMillis();
				System.out.print(" " + (endTime - startTime) + "ms\n\n");
				flag = loop(); 
				break;
			//Search by company name
			case 'c':
			case 'C':
				System.out.println("Enter the partial Company Name:");
				s = GetString();
				startTime = System.currentTimeMillis();
				PrintInfo(s, CompanyNameMap, AddressList);
				endTime = System.currentTimeMillis();
				System.out.print(" " + (endTime - startTime) + "ms\n\n");
				flag = loop(); 
				break;
			//Invalid input
			case 'w':
			default:
				System.out.println("Invalid selection. "
						+ "Please choose the field you'd like to search on. (F,L,P,C)");
				flag = 2;
				break;
			}
		}
		
	}
	//Read file
	public static void ReadFile(File file, ArrayList<AddressInfo> AddressList){
		BufferedReader br = null;
		try{
			br = new BufferedReader(new FileReader(file));
			String line = "";
			line = br.readLine();
			while((line = br.readLine()) != null){
				AddressInfo temp = new AddressInfo();
				temp.SetAddressInfo(line);
				AddressList.add(temp);
			}
		}catch (Exception e){}
		finally{
			if(br != null){
				try{
					br.close();
					br = null;
				}catch(IOException e){
					e.printStackTrace();
				}
			}
		}
	}
	//Loop after each single completed operation
	public static int loop(){
		int LP = 1;
		while (LP != 0) {
			if (LP == 1) System.out.println("Another Search? (Y,N)");
			switch (GetChar()) { 
			case 'y':
			case 'Y':
				return 1;
			case 'n':
			case 'N':
				System.out.println("Bye");
				return 0;
			default:
				System.out.println("Invalid selection. Do you want another search? (Y,N)");
				LP = 2;
				break;
			}
		}
		return 0;
	}
	//Get sting input
	public static String GetString(){
		String s = "";
		Scanner input = new Scanner(System.in);
		s = input.next();
		return s;
	}
	//Get char input
	public static char GetChar(){
		String s = GetString();
		char[] c = s.toCharArray();
		if(c.length != 1) return 'w';
		else return c[0];	
	}
	//Replace the last character in sting with its following letter, prepare for subMap
	public static String ChangeString(String s){
		StringBuffer m = new StringBuffer(s);
		char a = m.charAt(m.length()-1);
		a = (char) (a+1);
		m.setCharAt(m.length()-1, a);
		String b = m.toString();
		return b;		
	}
	//Display phone number as XXX-XXX-XXXX
	public static String DisplayPhoneNumber(String PhoneNumber) {

		char[] number = PhoneNumber.toCharArray();
		char[] result = new char[number.length + 2];

		if (number.length >= 9) {
			result[3] = '-';
			result[7] = '-';
			for (int i = 0; i < number.length; i++) {
				if (i <= 2) {
					result[i] = number[i];
				}
				if (i > 2 && i <= 5) {
					result[i + 1] = number[i];
				}
				if (i > 5) {
					result[i + 2] = number[i];
				}
			}
			return String.valueOf(result);
		} else {
			return PhoneNumber;
		}
	}
	//Put <Sting,List> Key-Value into TreeMap
	public static void KeyValue(ArrayList<String> NameIndex,TreeMap<String,ArrayList<String>> NameMap){
		for(String string:NameIndex){
			String node = string.split(":")[0];
			String value = string.split(":")[1];
			if(NameMap.containsKey(node)){
				ArrayList<String> list2 = NameMap.get(node);
				list2.add(value);
				NameMap.put(node,list2);
			}else{
				ArrayList<String> list2 = new ArrayList<String>();
				list2.add(value);
				NameMap.put(node,list2);
			}
		}
		
	}
	//Search the result and print it
	public static void PrintInfo(String s, TreeMap InfoMap, ArrayList<AddressInfo> AddressList){
		StringBuffer sb = new StringBuffer(s);
		SortedMap SubMap = new TreeMap();
		//Use subMap to complete partial search
		SubMap = InfoMap.subMap(s, ChangeString(s));
		SortedMap CSubMap = new TreeMap();
		CSubMap.putAll(SubMap);
		int i;
		int counter=0;//Record the number of results
		int subsize = CSubMap.size();
		System.out.println("Results:");
		if(SubMap.size()==0) System.out.print("No matching record.");
		else{
			for(i = 0;i < subsize;i++){
				//Get the index list of the searched key
				List list = (List) CSubMap.get(CSubMap.firstKey());
				//print results
				for(int le = 0;le < list.size();le++){
					counter++;
					System.out.println(AddressList.get(Integer.parseInt((String) list.get(le)))
							.GetFirstName()
							+ " "
							+ AddressList.get(Integer.parseInt((String) list.get(le))).GetLastName()
							+ ", "
							+ DisplayPhoneNumber(AddressList.get(Integer.parseInt((String) list.get(le)))
									.GetPhoneNumber())
							+ ", "
							+ AddressList.get(Integer.parseInt((String) list.get(le))).GetCompanyName());
				}
				//Move forward to print results
				CSubMap.remove(CSubMap.firstKey());
				
			}
			
		}
		System.out.print("(" + counter + " total matches),");
	}
}
