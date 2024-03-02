using namespace std;


bool isValidEmail(const string &email);
bool isValidUsername(const string &username);
bool isValidNumber(const string &number);
string encryptPassword(const string &password);
void loginUser(string username, string password);
bool isLogin(string username, string password);
void createLine(int n, int m);
void welcomeText();
void small_box();
void homePage(string username);
int generateRandomNumber();
void bigBox();
void homePageBox();
void homePageSmallBoxOptions();
string getCurrentTimeAndDate();
void createPost(string username);
void displayPostDetails(const int postId, const string &postUsername, const string &createdAt, const string &content, int k);
void manageProfileOptions();
void Profile(string username);
void changepassword(string username);
void changebio(string username);
void changeemail(string username);
void showProfile(string username);
void managePosts(string username);
void managePostsOptions();
void editPost(string username);
void deletePost(string username);

void getMyPost(string username);

string asterikPassword();