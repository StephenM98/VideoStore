//Video Store Final Project
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ifstream customerFile, videoFile, rentedvideo;
ofstream outFile;
string customerInfo = "customerInfo.txt";
string videoInfo = "MovieList.txt";
string moviesRented = "MoviesRented.txt";


void displayMenu();
class videoType {
public:
	static void searchVideo();
	static void printvideos();
	static void printRentedvideos();
	static void addVideoToStore();
	static void showVideoDetails();
};

class customerType {
public:
	static void printInfo();
	static void addcustomer();
	static void removecustomer();
	static void showAccountNumber();
	static void rentVideo(string, string, string, string);
	static void returnVideo(string, string, string, string);


};

void displayMenu() {
	int userChoice;
	string firstName, lastName, videoToRent, videoToReturn, accountNumber;
	cout << "What do you need? " << endl;
	cout << "(1) Rent a video." << endl;
	cout << "(2) Return a video." << endl;
	cout << "(3) Show all videos in store." << endl;
	cout << "(4) Add customer." << endl;
	cout << "(5) Remove customer." << endl;
	cout << "(6) Show all videos rented." << endl;
	cout << "(7) Add video to store." << endl;
	cout << "(8) Search for video." << endl;
	cout << "(9) Show customer account number." << endl;
	cout << "(10) Show details for a movie." << endl;
	cout << "(11) Show customer details." << endl;
	cin >> userChoice;

	if (userChoice == 1) {
		cout << "Please enter first name of customer." << endl;
		cin >> firstName;
		cout << "Please enter last name of customer." << endl;
		cin >> lastName;
		cout << "Please enter account number." << endl;
		cin >> accountNumber;
		cout << "Please enter title of movie." << endl;
		cin.ignore();
		getline(cin, videoToRent);
		customerType::rentVideo(firstName, lastName, accountNumber, videoToRent);
	}
	else if (userChoice == 2) {
		cout << "Please enter first name of customer." << endl;
		cin >> firstName;
		cout << "Please enter last name of customer." << endl;
		cin >> lastName;
		cout << "Please enter customer's account number." << endl;
		cin >> accountNumber;
		cout << "Please enter title of movie being returned." << endl;
		cin.ignore();
		getline(cin, videoToReturn);
		customerType::returnVideo(firstName, lastName, accountNumber, videoToReturn);
	}
	else if (userChoice == 3) {
		videoType::printvideos();
	}
	else if (userChoice == 4) {
		customerType::addcustomer();
	}
	else if (userChoice == 5) {
		customerType::removecustomer();
	}
	else if (userChoice == 6) {
		videoType::printRentedvideos();
	}
	else if (userChoice == 7) {
		videoType::addVideoToStore();
	}
	else if (userChoice == 8) {
		videoType::searchVideo();
	}
	else if (userChoice == 9) {
		customerType::showAccountNumber();
	}
	else if (userChoice == 10) {
		videoType::showVideoDetails();
	}

	else if (userChoice == 11) {
		customerType::printInfo();
	}

	else {
		cout << "Input error: please enter (1-11)." << endl;
	}

}

void customerType::rentVideo(string firstName, string lastName, string AccountNum, string videoTitle)
{
	string line, newLine;
	int pos, copies;

	videoFile.open(videoInfo);
	outFile.open("tempmov.txt");
	while (!videoFile.eof()) {
		getline(videoFile, line);
		outFile << line << endl;
	}
	outFile.close();
	videoFile.close();

	videoFile.open("tempmov.txt");
	outFile.open(videoInfo);
	while (!videoFile.eof()) {
		getline(videoFile, line);
		pos = line.find(',');
		if (pos == -1) {
			break;
		}
		newLine = line.substr(2, pos - 2);

		if (videoTitle == newLine) {
			if (line[0] != '0') {
				copies = line[0] - '0';
				copies--;
				outFile << copies << line.substr(1, line.find('\n')) << endl;
			}
		}
		else {
			outFile << line << endl;
		}
	}
	outFile.close();
	videoFile.close();

	rentedvideo.open(moviesRented);
	outFile.open("tempmovr.txt");
	while (!rentedvideo.eof()) {
		getline(rentedvideo, line);
		outFile << line << endl;
	}
	outFile.close();
	rentedvideo.close();

	rentedvideo.open("tempmovr.txt");
	outFile.open(moviesRented);
	while (!rentedvideo.eof()) {
		getline(rentedvideo, line);
		outFile << line << endl;
	}
	outFile << videoTitle << ", " << firstName << ", " << lastName << ", " << AccountNum;
	outFile.close();
	rentedvideo.close();
}

void customerType::returnVideo(string firstName, string lastName, string accountNumber, string videoTitle)
{
	string line, newLine, line2;
	int pos, copies;
	line2 = videoTitle + ", " + firstName + " " + lastName + ", " + accountNumber;
	videoFile.open(videoInfo);
	outFile.open("tempmov.txt");
	while (!videoFile.eof()) {
		getline(videoFile, line);
		outFile << line << endl;
	}
	outFile.close();
	videoFile.close();

	videoFile.open("tempmov.txt");
	outFile.open(videoInfo);
	while (!videoFile.eof()) {
		getline(videoFile, line);
		pos = line.find(',');
		if (pos == -1) {
			break;
		}
		newLine = line.substr(2, pos - 2);

		if (videoTitle == newLine) {
			copies = line[0] - '0';
			copies++;
			outFile << copies << line.substr(1, line.find('\n')) << endl;

		}
		else {
			outFile << line << endl;
		}
	}
	outFile.close();
	videoFile.close();

	rentedvideo.open(moviesRented);
	outFile.open("tempmovr.txt");
	while (!rentedvideo.eof()) {
		getline(rentedvideo, line);
		outFile << line << endl;
	}
	outFile.close();
	rentedvideo.close();

	rentedvideo.open("tempmovr.txt");
	outFile.open(moviesRented);
	while (!rentedvideo.eof()) {
		getline(rentedvideo, line);
		if (line == line2) {

		}
		else {
			outFile << line << endl;
		}

	}
	rentedvideo.close();
	outFile.close();
}

void videoType::printvideos()
{
	string line;
	int pos;
	videoFile.open(videoInfo);
	while (!videoFile.eof()) {

		getline(videoFile, line);

		if (line[0] == '0') {
			videoFile.ignore(0, '\n');
		}

		else {
			pos = line.find(',');
			if (pos == -1) {
				break;
			}
			line = line.substr(2, pos - 2);
			cout << line << endl;
		}
	}
	videoFile.close();
}

void customerType::addcustomer()
{
	string firstName, lastName, line;
	int accountNumber;
	customerFile.open(customerInfo);
	outFile.open("tempcust.txt");
	while (!customerFile.eof()) {
		getline(customerFile, line);
		outFile << line << endl;
	}
	outFile.close();
	customerFile.close();

	customerFile.open("tempcust.txt");
	outFile.open(customerInfo);
	while (!customerFile.eof()) {
		getline(customerFile, line);
		outFile << line << endl;
	}
	cout << "Enter the Name and account number for the new user." << endl;
	cin >> firstName >> lastName >> accountNumber;
	outFile << firstName << " " << lastName << " " << accountNumber;
	outFile.close();
	customerFile.close();
}

void customerType::removecustomer()
{
	string firstName, lastName, line, line2, accountNumber;
	cout << "Enter the Name and account number for the user you would like to remove." << endl;
	cin >> firstName >> lastName >> accountNumber;
	line2 = firstName + " " + lastName + " " + accountNumber;
	customerFile.open(customerInfo);
	outFile.open("tempcust.txt");
	while (!customerFile.eof()) {
		getline(customerFile, line);
		outFile << line << endl;
	}
	outFile.close();
	customerFile.close();
	customerFile.open("tempcust.txt");
	outFile.open(customerInfo);
	while (!customerFile.eof()) {
		getline(customerFile, line);
		if (line == line2) {

		}
		else {
			outFile << line << endl;
		}
	}
	customerFile.close();
	outFile.close();
}

void videoType::printRentedvideos()
{
	string line, name, newLine;
	int pos;
	rentedvideo.open(moviesRented);
	while (!rentedvideo.eof()) {
		getline(rentedvideo, line);
		pos = line.find(',');
		newLine = line.substr(0, pos);
		name = line.substr(pos + 1, ',');
		cout << newLine << " " << name << endl;

	}
	rentedvideo.close();
}

void videoType::addVideoToStore()
{
	string line, newMovie;
	int accountNumber;
	videoFile.open(videoInfo);
	outFile.open("tempmov.txt");
	while (!videoFile.eof()) {
		getline(videoFile, line);
		outFile << line << endl;
	}
	outFile.close();
	videoFile.close();

	videoFile.open("tempmov.txt");
	outFile.open(videoInfo);
	while (!videoFile.eof()) {
		getline(videoFile, line);
		outFile << line << endl;
	}
	cout << "Enter the Amount of copies, the title of the movie, two stars of the movie, the director, the producer and the production company. Please seperate these inputs with a comma" << endl;
	cout << endl;
	cin.ignore();
	getline(cin, newMovie);
	outFile << newMovie;
	outFile.close();
	videoFile.close();
}

void videoType::searchVideo()
{
	string userSearch;
	cout << "Enter title of video: ";
	cin.ignore();
	getline(cin, userSearch);
	string line, newLine;
	int pos;
	bool found = false;
	videoFile.open(videoInfo);
	while (!videoFile.eof()) {
		getline(videoFile, line);
		pos = line.find(',');
		if (pos == -1) {
			break;
		}
		newLine = line.substr(2, pos - 2);
		if (userSearch == newLine) {
			if (line[0] != '0') {
				found = true;
				cout << "Yes we have that movie in store." << endl;
			}

		}
	}
	if (!found) {
		cout << "Sorry we don't have that movie in stock." << endl;
	}

	videoFile.close();
}

void customerType::showAccountNumber()
{
	string firstName, lastName;
	cout << "Enter first and last name of customer." << endl;
	cin >> firstName >> lastName;
	string fullName = firstName + " " + lastName;
	string someName1, someName2, someFullName;

	int accountNumber = 0;
	customerFile.open(customerInfo);
	while (customerFile) {
		customerFile >> someName1 >> someName2;
		someFullName = someName1 + " " + someName2;


		if (fullName == someFullName) {
			customerFile >> accountNumber;

		}
		else {
			customerFile.ignore(200, '\n');
		}
	}
	if (accountNumber != 0) {
		cout << fullName << "'s account number is " << accountNumber << endl;
	}
	else {
		cout << "Sorry, we did not have that customer in our database." << endl;
	}
	customerFile.close();

}

void videoType::showVideoDetails() {
	string userMovieChoice, line, newLine;
	int pos;
	bool found = false;
	cout << "Show details for what movie? " << endl;
	cin.ignore();
	getline(cin, userMovieChoice);
	videoFile.open(videoInfo);
	while (!videoFile.eof()) {
		getline(videoFile, line);
		pos = line.find(',');
		if (pos == -1) {
			break;
		}
		newLine = line.substr(2, pos - 2);
		if (userMovieChoice == newLine) {
			if (line[0] != '0') {
				found = true;
				cout << line << endl;
			}

		}
	}

	if (!found) {
		cout << "Sorry we do not have that movie in stock." << endl;
	}
	videoFile.close();
}

void customerType::printInfo()
{
	string userSearch;
	cout << "Show details for what customer? " << endl;
	cin.ignore();
	getline(cin, userSearch);
	string firstName, lastName, fullName, line;
	int pos;
	bool found = false;
	customerFile.open(customerInfo);
	while (!customerFile.eof()) {
		customerFile >> firstName >> lastName;
		fullName = firstName + " " + lastName;
		if (userSearch == fullName) {
			getline(customerFile, line);
			found = true;
			cout << line << endl;
			break;
		}
		else {
			customerFile.ignore(200, '\n');
		}

	}
	if (!found) {
		cout << "Sorry we don't have that customer on file." << endl;
	}
	customerFile.close();
}

int main() {
	char userChoice = 'y';
	while (userChoice == 'y') {
		displayMenu();
		cout << "Enter 'y' to continue or 'q' to quit." << endl;
		cin >> userChoice;

	}
	system("PAUSE");
}