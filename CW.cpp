/* Year 1 Programming coursework 3 - Q2 
   Kok Wei
   3/4/2020
 */

#include <iostream>
#include <string>
#define TOTAL_ROOM 260
#define HILL_COST 20

using namespace std;

//Class attributes and methods
class BookedRoom{
private:
	int number;
	int nights;
	string name;
public:
	BookedRoom(){
		number = 0;
		nights = 0;
		name = "";
	}
	BookedRoom(int number, int nights, string name){
		this->number = number ;
		this->nights = nights;
		this->name = name;
	}
	int getNumber() {return number;}
	int getNights() {return nights;}
	string getName() {return name;}
};

//Global Variable
int num_booked_room = 0;
BookedRoom room_arr[TOTAL_ROOM];

//Functions
bool is_fully_booked(int num_booked_room) { return num_booked_room == 260; }

bool underage(int birthyear) { return 2020 - birthyear < 18; }

bool is_hill_view(int room_num) {return room_num%100>20;}

bool is_L5_and_below(int room_num) {return room_num < 600;}

bool contain_whitespace(string str) {
	char c = ' ';
	//trim all the leading and trailing white spaces
	while(str.back() == c) str.pop_back();
	while(str.front() == c) str.erase(0, 1);
	//if white space detected, will return npos which is -1
	return str.find(c) != -1;
}

bool room_invalid(int num){
	return (num < 301 || num > 940 || num%100 > 40 || num%100 == 0 || (num > 620 && num < 700));
}

bool is_available(int room_num) {
	for(int i = 0; i <TOTAL_ROOM ; i++) {
		BookedRoom room = room_arr[i];
		if(room.getNumber() == 0) {
			// it means this particular array element onwards are empty, so break out of loop to save time
			break;
		}
		else if (room.getNumber() == room_num){
			cout<<"\nRoom " << room.getNumber() <<" was already booked by: " << room.getName();
			cout<< " for " << room.getNights() << " nights" <<endl;
			return false;
		}
	} 
	return true;
}


int get_numeric_input(){
	int input;
	cin >> input;
	while(cin.fail()){
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid input, please enter a numerical number: ";
		cin >>input;
	}
	return input;
}

int checkPrice(int room_num) {
	int price = 120;
		if(is_L5_and_below(room_num)) price = 90;
		if(is_hill_view(room_num)) {
			price+=HILL_COST;
			cout << "This is a hill-view room with a price of " <<price<< " per night";
		} else {
			cout << "This is a city-view room with a price of " <<price<< " per night";
		}
	return price;	
}

int get_nights(){
	cout <<"\nHow many nights?: ";
	int nights = get_numeric_input();
	while(nights <= 0) {
		cout << "Invalid amount of nights\n";
		cout << "How many nights?: ";
		nights = get_numeric_input();
	}
	return nights;
}

int get_room_number(){
	int num;
	while(true) {
		cout <<"Enter the room number: ";
		num = get_numeric_input();
		while (room_invalid(num)) {
			cout << "There is no such room" <<endl;
			cout <<"Enter the room number: ";
			num = get_numeric_input();
		}
		if(is_available(num)) break;
	}
	return num;
}

void book_room(string name) {
	int room_num, nights,price;
	cout << "\nThere are " << TOTAL_ROOM - num_booked_room << " available rooms\n\n";
	room_num = get_room_number();
	price = checkPrice(room_num);
	nights = get_nights();
	BookedRoom room(room_num, nights, name);
	room_arr[num_booked_room++] = room;
	cout << "\nRoom " << room_num << " was booked for " << nights << " nights by " << name <<'\n';
	cout << "The total cost is RM " << price*nights << '\n';
}

void get_passport() {
	string id;
	cout << "Passport/ID number: ";
	getline(cin ,id);
	if(id.find(' ') != -1) {
		cout << "passport cannot contain empty space!\n";
		get_passport();
	}
}

string get_customer_name() {
	cin.ignore(100, '\n');
	string name ;
	cout << "Full name: ";
	getline(cin ,name);
	while (!contain_whitespace(name)) {
		cout << "Please Enter the full name: ";
		getline(cin ,name);
	}
	return name;
}

string display(string *display_string, int size) {
	string c;
	for(int i = 0 ; i<size; i++){
		cout<< '\n' << display_string[i] ;
	}
	cout <<"\nPlease select from the previous options: ";
	getline(cin ,c);
	return c;
}   

string wrong_input_repeat() {
	string c;
	cout << "\nWrong Input. Please select from the previous options: ";
	getline(cin ,c);
	return c;
}

int birthyear_menu() {

	string display_dob[] = {"1. Enter a valid year of birth", "2. Go to main menu"};
	cout <<"\nCustomer information:\n";
	cout <<"\nYear of birth: ";
	int birthyear = get_numeric_input();
		while (underage(birthyear)){
			cout << "Customers who are less than 18 years old cannot book a room\n";
			cin.ignore(100, '\n');
			string input = display(display_dob, 2);
			while (input != "1" && input != "2")
				input = wrong_input_repeat();
			if (input == "2") return -1;
			cout <<"\nYear of birth: ";
			birthyear = get_numeric_input();
		}
	return 0;
}

string main_menu(){
	string input;
	string display_main[] = {"Welcome to UNM Hotel booking system" , "1. Book a room" , "Q. Quit"};
	input = display(display_main, 3);
	while (input != "1" && input != "Q") 
		input = wrong_input_repeat();
	return input;
}

void run_program() {
	while (true) {
		if(is_fully_booked(num_booked_room)) {
			cout << "All rooms are fully booked, thank you.\n";
			break;
		}
		if (main_menu() == "Q") break ;
		if(birthyear_menu() == -1) continue;
		string name = get_customer_name();
		get_passport();
		book_room(name);
		cin.ignore(100, '\n');
	}
}

int main () {
	run_program();
	cout << "\nGoodbye!";
}