#include "functions.h"
using namespace std;
COORD coord = {0, 0};
void gotoxy(int x, int y) {
	coord.X = x;
	coord.Y = y;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, coord);
}
class Post {
		int postId;
		string username;
		string content;
		string createdAt;

	public:
		void input(string content, string createdAt, int postId, string username) {
			this->content = content;
			this->createdAt = createdAt;
			this->postId = postId;
			this->username = username;
		}
		void saveToFile();
		void display();
};

class User {
		string username, email, password, confirmPassword, address, phone;

	public:
		void input(string username, string email, string password, string confirmPassword, string address, string phone) {
			this->username = username;
			this->email = email;
			this->address = address;
			this->phone = phone;
			this->password = password;
			this->confirmPassword = confirmPassword;
		}
		void saveToFile();
		string getUsername() {
			return username;
		}
};

void User::saveToFile() {
	fstream inputFile(username + ".txt");

	if (inputFile.is_open()) {
		cerr << "Already Registered a user with this username : " << endl;
		exit(0);
	}
	ofstream outputFile(username + ".txt");
	if (outputFile.is_open()) {
		outputFile << "Username : " << username << endl;
		outputFile << "Email : " << email << endl;
		outputFile << "Phone : " << phone << endl;
		outputFile << "Address : " << address << endl;
		outputFile << "Password : " << password << endl;

		outputFile.close();

		gotoxy(83, 16);
		cout << "Registration Successful.";
		gotoxy(83, 17);
		cout << " Press any key to continue ";
		gotoxy(86, 18);
		getch();

		system("cls");
		loginUser(username, password);
	} else {
		cerr << "Error while signing in." << endl;
		exit(0);
	}
}

void Post::saveToFile() {
	string filename = "post_" + to_string(postId) + ".txt";
	ifstream inputFile(filename);

	if (inputFile.is_open()) {
		cerr << "Error: note post with ID " << postId << " already exists." << endl;
		inputFile.close();
		return;
	}

	ofstream outputFile(filename);

	if (outputFile.is_open()) {
		outputFile << "postId : " << postId << endl;
		outputFile << "Username : " << username << endl;
		outputFile << "createdAt : " << createdAt << endl;
		outputFile << "Content : " << content << endl;

		outputFile.close();
		cout << "note created successfully." << endl;
	} else {
		cerr << "Error: Unable to create the note post file." << endl;
	}
}

void Post::display() {
	cout << " PostId : " << postId << endl;
	cout << " Username : " << username << endl;
	cout << " CreatedAt : " << createdAt << endl;
	cout << " Content : " << content;
}