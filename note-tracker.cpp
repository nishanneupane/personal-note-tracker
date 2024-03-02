#include <iostream>
#include "myheader.h"
#include "myclasses.h"
#include "functions.h"
#include "constants.h"
using namespace std;

int main() {
	User u;
	int choice;
	int boxX = 4;
	int boxY = 3;
	int boxWidth = 50;
	int boxHeight = 25;
	string username, email, password, confirmPassword, address, phone;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

	gotoxy(60, 3);
	cout << "Personal Note Tracker" << endl;

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(60, 5);

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

	createLine(60, 30);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	gotoxy(63, 5);
	welcomeText();
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	gotoxy(20, 7);
	cout << "Choose an option :-";
	gotoxy(20, 8);
	cout << "1. Login ";
	gotoxy(20, 9);
	cout << "2. Register ";
	gotoxy(20, 10);
	cout << "Your Choice : ";
	cin >> choice;

	switch (choice) {
		case 1:
			createBox(boxX, boxY, boxWidth, boxHeight);
			gotoxy(boxX + 4, boxY + 2);
			cout << "Login Form" << endl;
			loginUser(username, password);
			break;
		case 2:

			createBox(boxX, boxY, boxWidth, boxHeight);
			gotoxy(boxX + 4, boxY + 2);
			cout << "\t\tRegistration Form" << endl;

			gotoxy(boxX + 4, boxY + 5);
			cout << "Username : ";
			cin >> username;
			if (!isValidUsername(username)) {
				gotoxy(boxX + 4, boxY + 25);
				cout << "Invalid Email Address." << endl;
				exit(0);
			}
			gotoxy(boxX + 4, boxY + 7);
			cout << "Email : ";
			cin >> email;
			if (!isValidEmail(email) && !(email.find("@gmail.com") != string::npos)) {
				gotoxy(boxX + 4, boxY + 25);

				cout << "Invalid Email Address." << endl;
				exit(0);
			}

			gotoxy(boxX + 4, boxY + 9);
			cout << "Address : ";
			cin.ignore();
			getline(cin, address);
			if (!address.length() > 5 && !address.length() < 60) {
				gotoxy(boxX + 4, boxY + 25);

				cout << "Min 5 Characters and Maximum 60." << endl;
				exit(0);
			}
			gotoxy(boxX + 4, boxY + 11);
			cout << "Phone : ";
			cin >> phone;
			if (!isValidNumber(phone) && phone.length() != 10) {
				gotoxy(boxX + 4, boxY + 25);

				cout << "Invalid phone number." << endl;
				exit(0);
			}
			gotoxy(boxX + 4, boxY + 15);
			cout << "Password : ";
			password = asterikPassword();
			gotoxy(boxX + 4, boxY + 17);
			cout << "Confirm Password : ";
			confirmPassword = asterikPassword();

			if (password != confirmPassword) {
				cout << "Passwords do not match." << endl;
				exit(0);
			}

			u.input(username, email, password, confirmPassword, address, phone);
			u.saveToFile();
			break;

		default:
			cout << "No Options available" << endl;
			return 0;
	}
	return 0;
}

void loginUser(string username, string password) {
	int boxX = 4;
	int boxY = 3;
	int boxWidth = 50;
	int boxHeight = 25;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	createBox(boxX, boxY, boxWidth, boxHeight);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(boxX + 4, boxY + 5);
	cout << "Username : ";
	cin >> username;
	if (!isValidUsername(username)) {
		cout << "Invalid Email Address." << endl;
		exit(0);
	}

	gotoxy(boxX + 4, boxY + 7);
	cout << "Password : ";
	password = asterikPassword();

	if (isLogin(username, password)) {
		system("cls");
		gotoxy(50, 20);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		cout << "Logged In sucessfully";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		sleep(1);
		system("cls");
		homePage(username);
	} else {
		gotoxy(boxX + 4, boxY + 9);
		cout << "unable to login";
		gotoxy(boxX + 4, boxY + 27);
		exit(0);
	}
}

void homePage(string username) {
	int choice;
	int pageNumber = 1, pageSize = 5;
	int boxX = 4;
	int boxY = 3;
	int boxWidth = 80;
	int boxHeight = 100;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// bigBox();
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	small_box();

	homePageSmallBoxOptions();

	//	getAllPosts(pageSize,pageNumber);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

	cin >> choice;

	switch (choice) {
		case 1:
			cout << "Redirecting to the Create Post ..." << endl;
			system("cls");
			createPost(username);
			break;
		case 2:
			system("cls");
			getMyPost(username);

			break;
		case 3:
			system("cls");
			Profile(username);
			break;
		case 4:
			system("cls");
			managePosts(username);
			break;
		case 5:
			exit(0);
			break;
		default:
			cout << "Invalid Options ..." << endl;
			exit(0);
	}
}


void createPost(string username) {
	char ch = 'y';
	Post post;
	string content;
	int postId = generateRandomNumber();
	string createdAt = getCurrentTimeAndDate();
	int boxX = 4;
	int boxY = 3;
	int boxWidth = 100;
	int boxHeight = 10;

	createBox(boxX, boxY, boxWidth, boxHeight);

	fstream inputFile(username + ".txt");

	if (!inputFile.is_open()) {
		gotoxy(boxX + 4, boxY + 5);
		cerr << "User doesn't exist: " << endl;
		inputFile.close();
		exit(0);
	}

	while (ch == 'y') {

		gotoxy(boxX + 4, boxY + 2);
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "Enter the content of your note post (press Enter to finish, Maximum character limit 100):";
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

		gotoxy(boxX + 4, boxY + 3);
		cin.ignore();
		getline(cin, content);

		if (content != "" && content.length() <= 100) {
			post.input(content, createdAt, postId, username);
			post.saveToFile();
			//			post.display();
			system("cls");
			homePage(username);
			break;
		} else {
			cout << "Content is empty or Max limit reached, (press y to continue)" << endl;
			cin >> ch;
			system("cls");
		}
	}
}
void Profile(string username) {
	system("cls");
	int choice;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	bigBox();
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	manageProfileOptions();
	showProfile(username);

	gotoxy(87, 9);
	cin >> choice;
	switch (choice) {
		case 1:
			changepassword(username);
			break;
		case 2:
			changeemail(username);
			break;
		case 3:
			changebio(username);
			break;
		default:
			cout << "Enter valid option";
			exit(0);
	}
}

void showProfile(string username) {
	string filename = username + ".txt";

	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		cout << "Unable to find info" << endl;
		return;
	}

	// Read user profile information
	string newUsername, newEmail, newPhone, newAddress, bio;
	string line;

	while (getline(inputFile, line)) {
		if (line.find("Username : ") == 0) {
			newUsername = line.substr(11);
		} else if (line.find("Email : ") == 0) {
			newEmail = line.substr(8);
		} else if (line.find("Phone : ") == 0) {
			newPhone = line.substr(8);
		} else if (line.find("Address : ") == 0) {
			newAddress = line.substr(10);
		} else if (line.find("Bio : ") == 0) {
			bio = line.substr(6);
		}
	}

	inputFile.close();

	// Display user profile information
	gotoxy(4, 4);
	cout << " Username : " << newUsername;
	gotoxy(4, 5);
	cout << " Email : " << newEmail;
	gotoxy(4, 6);
	cout << " Phone : " << newPhone;
	gotoxy(4, 7);
	cout << " Address : " << newAddress;
	gotoxy(4, 8);
	cout << " Bio : " << bio;
}

void changepassword(string username) {
	string filename = username + ".txt";

	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		cout << "Unable to find info" << endl;
		return;
	}

	// Read the existing user profile information
	string newUsername, newEmail, newPhone, newAddress, password, bio, oldPassword;
	string line;
	string changedPassword;
	while (getline(inputFile, line)) {
		if (line.find("Username : ") == 0) {
			newUsername = line.substr(11);
		} else if (line.find("Email : ") == 0) {
			// Adjust offset to account for extra spaces and hyphens
			newEmail = line.substr(8); // Adjusted offset for Email
		} else if (line.find("Phone : ") == 0) {
			// Adjust offset to account for extra spaces and hyphens
			newPhone = line.substr(8); // Adjusted offset for Phone
		} else if (line.find("Address : ") == 0) {
			newAddress = line.substr(10); // Adjusted offset for Address
		} else if (line.find("Bio : ") == 0) {
			bio = line.substr(6);
		} else if (line.find("Password : ") == 0) {
			password = line.substr(11);
		}
	}

	inputFile.close();

	// Prompt the user to enter a new bio
	gotoxy(7, 11);
	cout << "Enter your old Password: ";
	cin.ignore();
	getline(cin, oldPassword);

	if (password == oldPassword) {
		gotoxy(7, 12);
		cout << "Enter new password: ";
		cin.ignore();
		getline(cin, changedPassword);
		ofstream outputFile(filename);
		if (!outputFile.is_open()) {
			cout << "Unable to update profile" << endl;
			return;
		}

		// Write the updated profile information to the file
		outputFile << "Username : " << newUsername << endl;
		outputFile << "Email : " << newEmail << endl;
		outputFile << "Phone : " << newPhone << endl;
		outputFile << "Address : " << newAddress << endl;
		outputFile << "Bio : " << bio << endl;
		outputFile << "Password : " << changedPassword << endl;

		// Close the output file
		outputFile.close();

		gotoxy(7, 17);
		cout << "Password updated successfully" << endl;
		gotoxy(8, 18);
		cout << " Press any button to continue";
		gotoxy(9, 19);
		getch();

		system("cls");
		homePage(username);
	} else {
		gotoxy(90, 18);
		cout << "Wrong password!";
		gotoxy(90, 19);
		cout << " Press any button to continue";
		gotoxy(90, 20);
		getch();

		system("cls");
		homePage(username);
	}
}
void changeemail(string username) {
	string filename = username + ".txt";

	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		cout << "Unable to find info" << endl;
		return;
	}

	// Read the existing user profile information
	string newUsername, newEmail, newPhone, newAddress, password, bio;
	string line;
	string changedEmail;
	while (getline(inputFile, line)) {
		if (line.find("Username : ") == 0) {
			newUsername = line.substr(11);
		} else if (line.find("Email : ") == 0) {
			// Adjust offset to account for extra spaces and hyphens
			newEmail = line.substr(8); // Adjusted offset for Email
		} else if (line.find("Phone : ") == 0) {
			// Adjust offset to account for extra spaces and hyphens
			newPhone = line.substr(8); // Adjusted offset for Phone
		} else if (line.find("Address : ") == 0) {
			newAddress = line.substr(10); // Adjusted offset for Address
		} else if (line.find("Bio : ") == 0) {
			bio = line.substr(6);
		} else if (line.find("Password : ") == 0) {
			password = line.substr(11);
		}
	}

	inputFile.close();

	// Prompt the user to enter a new bio
	gotoxy(5, 11);
	cout << "Enter new Email: ";
	cin.ignore();
	getline(cin, changedEmail);
	if (!isValidEmail(changedEmail) && !(changedEmail.find("@gmail.com") != string::npos)) {
		gotoxy(88, 17);
		cout << "Invalid Email" << endl;
		gotoxy(88, 18);
		cout << " Press any button to continue";
		gotoxy(88, 19);
		getch();

		system("cls");
		homePage(username);
	}

	// Update the user's profile file with the new bio
	ofstream outputFile(filename);
	if (!outputFile.is_open()) {
		cout << "Unable to update profile" << endl;
		return;
	}

	// Write the updated profile information to the file
	outputFile << "Username : " << newUsername << endl;
	outputFile << "Email : " << changedEmail << endl;
	outputFile << "Phone : " << newPhone << endl;
	outputFile << "Address : " << newAddress << endl;
	outputFile << "Bio : " << bio << endl;
	outputFile << "Password : " << password << endl;

	// Close the output file
	outputFile.close();

	gotoxy(88, 19);
	cout << "Email updated successfully" << endl;
	gotoxy(88, 20);
	cout << " Press any button to continue";
	gotoxy(88, 21);
	getch();

	system("cls");
	homePage(username);
}
void changebio(string username) {
	string filename = username + ".txt";

	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		cout << "Unable to find info" << endl;
		return;
	}

	// Read the existing user profile information
	string newUsername, newEmail, newPhone, newAddress, bio, password;
	string line;
	while (getline(inputFile, line)) {
		if (line.find("Username : ") == 0) {
			newUsername = line.substr(11);
		} else if (line.find("Email : ") == 0) {
			// Adjust offset to account for extra spaces and hyphens
			newEmail = line.substr(8); // Adjusted offset for Email
		} else if (line.find("Phone : ") == 0) {
			// Adjust offset to account for extra spaces and hyphens
			newPhone = line.substr(8); // Adjusted offset for Phone
		} else if (line.find("Address : ") == 0) {
			newAddress = line.substr(10); // Adjusted offset for Address
		} else if (line.find("Bio : ") == 0) {
			bio = line.substr(6);
		} else if (line.find("Password : ") == 0) {
			password = line.substr(11);
		}
	}

	inputFile.close();

	// Prompt the user to enter a new bio
	gotoxy(5, 11);
	cout << "Enter your new bio: ";
	cin.ignore();
	getline(cin, bio); // Read the new bio from the user

	// Update the user's profile file with the new bio
	ofstream outputFile(filename);
	if (!outputFile.is_open()) {
		cout << "Unable to update profile" << endl;
		return;
	}

	// Write the updated profile information to the file
	outputFile << "Username : " << newUsername << endl;
	outputFile << "Email : " << newEmail << endl;
	outputFile << "Phone : " << newPhone << endl;
	outputFile << "Address : " << newAddress << endl;
	outputFile << "Bio : " << bio << endl;
	outputFile << "Password : " << password << endl;

	// Close the output file
	outputFile.close();
	gotoxy(5, 13);
	cout << "Bio updated successfully" << endl;
	gotoxy(5, 20);
	gotoxy(88, 18);
	cout << " Press any button to continue";
	gotoxy(88, 19);
	getch();

	system("cls");
	homePage(username);
}

void managePosts(string username) {
	int options;
	system("cls");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
	bigBox();
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	managePostsOptions();

	gotoxy(90, 9);
	cin >> options;

	switch (options) {
		case 1:
			editPost(username);
			break;
		case 2:
			deletePost(username);
			break;
		default:
			cerr << "You have entered wrong choice : ";
			exit(0);
	}
}

void editPost(string username) {
	int postId;
	gotoxy(87, 13);
	cout << "Enter Id to Edit: ";
	cin >> postId;

	string filename = "post_" + to_string(postId) + ".txt";
	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		gotoxy(5, 27);
		cerr << "Error: Post not found";
		exit(1); // Exit with an error code
	}

	string newpostId, newUsername, createdAt, content;
	string line;

	while (getline(inputFile, line)) {
		if (line.find("postId : ") == 0) {
			newpostId = line.substr(9);
		} else if (line.find("Username : ") == 0) {
			newUsername = line.substr(11);
		} else if (line.find("createdAt : ") == 0) {
			createdAt = line.substr(12);
		} else if (line.find("Content : ") == 0) {
			content = line.substr(10);
		}
	}

	inputFile.close();

	if (newUsername == username) {
		string newContent;
		gotoxy(15, 15);
		cout << "New Content: ";
		cin.ignore(); // Consume the newline character left in the input buffer
		getline(cin, newContent);

		// Open the file for writing and overwrite the existing content
		ofstream outputFile(filename);

		if (outputFile.is_open()) {
			outputFile << "postId : " << newpostId << endl;
			outputFile << "Username : " << newUsername << endl;
			outputFile << "createdAt : " << createdAt << endl;
			outputFile << "Content : " << newContent << endl;

			outputFile.close();

			gotoxy(85, 6);
			system("cls");
			homePage(username);
			//			cout << "Post updated successfully ";
			//			gotoxy(15, 20);
		} else {
			gotoxy(85, 7);
			cerr << "Error updating the post";
			exit(1);
		}
	} else {
		gotoxy(85, 7);
		cerr << "Unauthorized Access";
		exit(1);
	}
	gotoxy(88, 18);
	cout << " Press any button to continue";
	gotoxy(88, 19);
	getch();

	system("cls");
	homePage(username);
}
void deletePost(string username) {
	system("cls");
	int postId;
	gotoxy(85, 4);
	cout << "Enter Post Id to Delete: ";
	cin >> postId;

	string filename = "post_" + to_string(postId) + ".txt";
	ifstream inputFile(filename);

	if (!inputFile.is_open()) {
		gotoxy(85, 7);
		cerr << "Error: Post not found";
		exit(1);
	}

	string newpostId, newUsername, createdAt, content;
	string line;

	while (getline(inputFile, line)) {
		if (line.find("postId : ") == 0) {
			newpostId = line.substr(9);
		} else if (line.find("Username : ") == 0) {
			newUsername = line.substr(11);
		} else if (line.find("createdAt : ") == 0) {
			createdAt = line.substr(12);
		} else if (line.find("Content : ") == 0) {
			content = line.substr(10);
		}
	}
	inputFile.close();

	if (newUsername == username) {
		if (remove(filename.c_str()) == 0) {
			gotoxy(85, 5);
			cout << "Post Deleted Sucessfully";
			gotoxy(15, 20);
		} else {
			gotoxy(85, 5);
			cout << "Unauthorized";
			gotoxy(15, 20);
		}

		gotoxy(88, 18);
		cout << " Press any button to continue";
		gotoxy(88, 19);
		getch();

		system("cls");
		homePage(username);
	} else {
		gotoxy(85, 5);
		cout << "Unable to delete Post";
	}
}

void getMyPost(string username) {
	int k = 3;
	for (int postId = 1000; postId <= 9999; postId++) {
		string filename = "post_" + to_string(postId) + ".txt";

		ifstream inputFile(filename);

		if (inputFile.is_open()) {
			// Read post details from the file
			int Id = postId;
			string postUsername, createdAt, content;

			string line;
			while (getline(inputFile, line)) {
				if (line.find("Username : ") == 0) {
					postUsername = line.substr(11);
				} else if (line.find("createdAt : ") == 0) {
					createdAt = line.substr(12);
				} else if (line.find("Content : ") == 0) {
					content = line.substr(10);
				}
			}

			// Close the file
			inputFile.close();

			if (postUsername == username) {
				gotoxy(6, k); // Position the cursor
				displayPostDetails(Id, postUsername, createdAt, content, k);
				k += 6;
			}
		}
	}
	gotoxy(88, 18);
	cout << " Press any button to continue";
	gotoxy(88, 19);
	getch();

	system("cls");
	homePage(username);
}
