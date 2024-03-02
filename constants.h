using namespace std;


void drawBox(int x, int y, int width, int height) {
	// Draw a box with '*' characters
	for (int i = 0; i < height; i++) {
		gotoxy(x, y + i);
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
				cout << "*";
			} else {
				cout << " ";
			}
		}
	}
}
void createBox(int x, int y, int width, int height) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

	gotoxy(x, y);
	cout << char(201);
	for (int i = 0; i < width - 2; i++)
		cout << char(205);
	cout << char(187);

	for (int i = 1; i < height - 1; i++) {
		gotoxy(x, y + i);
		cout << char(186);
		for (int j = 0; j < width - 2; j++)
			cout << ' ';
		cout << char(186);
	}

	gotoxy(x, y + height - 1);
	cout << char(200);
	for (int i = 0; i < width - 2; i++)
		cout << char(205);
	cout << char(188);

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

bool isValidEmail(const string &email) {
	const regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4})");
	return regex_match(email, pattern);
}

bool isValidNumber(const string &number) {
	for (char c : number) {
		if (!isdigit(c)) {
			return false;
		}
	}
	return true;
}

string encryptPassword(const string &password) {
	return string(password.length(), '*');
}
bool isValidUsername(const string &username) {
	return (username.length() > 3 && username.length() < 20);
}
void createLine(int x, int length) {
	for (int i = 7; i < length; i++) {
		gotoxy(x, i);
		cout << "|";
	}
}
void welcomeText() {
	string text = "You are heartly welcome to your personal note management system . enjoy your day by writing your note on your personal digital system with the proper security.";
	int maxLength = 40;
	int x = 70;
	int y = 8;

	for (int i = 0; i < text.length(); i += maxLength) {
		string line = text.substr(i, maxLength);
		gotoxy(x, y++);
		cout << line;
	}
}

string asterikPassword() {
	string password = "";
	char ch;

	while (true) {
		ch = _getch(); // Get a character without displaying it
		if (ch == 13)  // Enter key pressed
			break;
		else if (ch == 8) {
			// Backspace key pressed
			if (!password.empty()) {
				cout << "\b \b";	 // Erase the character from the screen
				password.pop_back(); // Remove the last character from the password string
			}
		} else {
			cout << "*";	// Display an asterisk
			password += ch; // Add the character to the password string
		}
	}

	cout << endl; // Move to the next line
	return password;
}
void small_box() {
	// Define the size of the small square box
	int smallBoxSize = 25;

	// Calculate the starting position for the small box on the right side
	int smallBoxStartX = 25; // Adjust this value as needed
	int smallBoxStartY = 3;	 // Adjust this value as needed

	// Print the small square box
	gotoxy(smallBoxStartX, smallBoxStartY);
	for (int i = 0; i < smallBoxSize; i++) {
		for (int j = 0; j < smallBoxSize * 2; j++) {
			if (i == 0 || i == smallBoxSize - 1 || j == 0 || j == smallBoxSize * 2 - 1) {
				cout << "*";
			} else {
				cout << " ";
			}
		}
		gotoxy(smallBoxStartX, smallBoxStartY + i + 1);
	}
}
void bigBox() {
	int boxSize = 40;

	// Calculate the starting position for the small box on the right side
	int boxStartX = 2; // Adjust this value as needed
	int boxStartY = 2; // Adjust this value as needed

	// Print the big square box
	gotoxy(boxStartX, boxStartY);
	for (int i = 0; i < boxSize; i++) {
		for (int j = 0; j < boxSize * 2; j++) {
			if (i == 0 || i == boxSize - 1 || j == 0 || j == boxSize * 2 - 1) {
				cout << "-";
			} else {
				cout << " ";
			}
		}
		gotoxy(boxStartX, boxStartY + i + 1);
	}
}
void homePageBox(int x, int y, int width, int height) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

	gotoxy(x, y);
	cout << char(201);
	for (int i = 0; i < width - 2; i++)
		cout << char(205);
	cout << char(187);

	for (int i = 1; i < height - 1; i++) {
		gotoxy(x, y + i);
		cout << char(186);
		for (int j = 0; j < width - 2; j++)
			cout << ' ';
		cout << char(186);
	}

	gotoxy(x, y + height - 1);
	cout << char(200);
	for (int i = 0; i < width - 2; i++)
		cout << char(205);
	cout << char(188);

	for (int i = 0; i < height - 1; i++) {
		gotoxy(x + 1, y + i + 1);
		for (int j = 0; j < width - 2; j++)
			cout << ' ';
	}

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	gotoxy(88, 11);
}
void homePageSmallBoxOptions() {
	gotoxy(27, 5);
	cout << "Go for Something : ";
	gotoxy(27, 6);
	cout << "1. Create Post";
	gotoxy(27, 7);
	cout << "2. Get All Posts";
	gotoxy(27, 8);
	cout << "3. Manage profile";
	gotoxy(27, 9);
	cout << "4. Manage Posts";
	gotoxy(27, 10);
	cout << "5. Exit";
	gotoxy(27, 11);
	cout << "Your Choice : ";
	gotoxy(43, 11);
}
string getCurrentTimeAndDate() {
	time_t currentTime = time(nullptr);
	struct tm *localTime = localtime(&currentTime);
	char timeString[80];
	strftime(timeString, sizeof(timeString), "%a %b %d %H:%M:%S %Y", localTime);
	return timeString;
}
int generateRandomNumber() {
	// Seed the random number generator with the current time
	srand(static_cast<unsigned int>(time(nullptr)));

	int minDigits = 1000; // Minimum 4-digit number
	int maxDigits = 9999; // Maximum 4-digit number

	// Generate a random number between minDigits and maxDigits
	int randomNumber = minDigits + rand() % (maxDigits - minDigits + 1);

	return randomNumber;
}
void displayPostDetails(const int postId, const string &postUsername, const string &createdAt, const string &content, int k) {
	// Display the post details
	gotoxy(6, k + 1);
	cout << "Post ID: " << postId;
	gotoxy(6, k + 2);
	cout << "Username: " << postUsername;
	gotoxy(6, k + 3);
	cout << "Created At: " << createdAt;
	gotoxy(6, k + 4);
	cout << "Content: " << content;
	gotoxy(6, k + 5);
	cout << "--------------------------------";
	gotoxy(89, k+6);
}
void managePostsOptions() {
	gotoxy(87, 4);
	cout << "1. Edit Post ";
	gotoxy(87, 5);
	cout << "2. Delete Post ";
	gotoxy(87, 7);
	cout << "Your Choice : ";
}
bool isLogin(string username, string password) {
	string storedUsername, storedPassword;
	ifstream inputFile(username + ".txt");

	if (inputFile.is_open()) {
		string line;
		while (getline(inputFile, line)) {
			if (line.find("Username : ") == 0) {
				storedUsername = line.substr(11);
			} else if (line.find("Password : ") == 0) {
				storedPassword = line.substr(11);
			}
		}

		inputFile.close();

		if (storedUsername == username && storedPassword == password) {
			return true;
		}
	}

	return false;
}

void manageProfileOptions() {
	gotoxy(87, 5);
	cout << "1. Change Password";
	gotoxy(87, 6);
	cout << "2. Change Email";
	gotoxy(87, 7);
	cout << "3. Update Your Bio";
	gotoxy(87, 8);
	cout << " Your Choice : ";
	gotoxy(87, 9);
}