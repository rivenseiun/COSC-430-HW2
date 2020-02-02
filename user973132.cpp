
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <ctime>
#include <openssl/sha.h>

using namespace std;
void sha256(string  str)
{

	unsigned char result[32];
	SHA256((const unsigned char*)str.c_str(), str.length(), result);
	string hash = "";

		for (int i = 0; i < 32; i++) {
			hash = hash + (char)result[i];
		}

	

}


int main()
{
	//Authentication
	//Read user input
	char data[30];
	string username;
	string password;

	cout << "Hello. Please enter your username: " << endl;
	cin.getline(data, 30);
	username = data;
	username.erase(0, username.find_first_not_of(" "));
	username.erase(username.find_last_not_of(" ") + 1);

	cout << "Please enter your password: " << endl;
	cin.getline(data, 30);
	password = data;
	password.erase(0, password.find_first_not_of(" "));
	password.erase(password.find_last_not_of(" ") + 1);


	//Hash the password
	unsigned char result[32];
	SHA256((const unsigned char*)password.c_str(), password.length(), result);
	string hash_pwd = "";
	for (int i = 0; i < 32; i++) {
		char temp[3];
		sprintf_s(temp, 3, "%02x", result[i]);
		string str = temp;
		hash_pwd = hash_pwd + str;
	}
	hash_pwd.erase(0, hash_pwd.find_first_not_of(" "));
	hash_pwd.erase(hash_pwd.find_last_not_of(" ") + 1);

	//Match the user input
	ifstream fin;
	fin.open("user973132.cfg");
	string str;
	bool valid = 0;
	while (!fin.eof())

	{
		getline(fin, str);

		if (str.find(username) != string::npos && str.find(hash_pwd) != string::npos) {
			cout << "VALID" << endl;
			valid = 1;
			break;
		}
	}
	fin.close();

	if (valid == 1) {
		//Write user info to log
		ofstream in;
		string timestamp = __TIMESTAMP__;
		in.open("user973132.log", ios::app);
		in << username << "\t" <<timestamp << "\n";
		in.close();

		//Print the content of the secret file
		ifstream fin;
		fin.open("user973132.txt");
		string str;
		bool valid = 0;
		while (!fin.eof()) {
			getline(fin, str);
			cout << str << endl;
		}
		fin.close();



	}
	else {
		cout << "Invalid username or password" << endl;
		ofstream in;
		in.open("user973132.log", ios::app);
		in << "Invalid Access"<< "\t" << __TIMESTAMP__ << "\n";
		in.close();
	};





}









