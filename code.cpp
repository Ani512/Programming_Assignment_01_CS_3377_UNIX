#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include "version.h"

using namespace std;

int count(string, char);
bool check_number(string);

static double VERSION = 1.2;

int main() {
  string str, protocol, domain, port, path, parameters;
  int wrongPro = 0, wrongDom = 0, wrongPort = 0, wrongPath = 0, wrongParam = 0;
  int overallError = 0;

  // Calling the Version Function
printVersion(VERSION);

// INPUT
  cout << "Enter a url:" << endl;
  cin >> str;

// PROTOCOL
  size_t p = str.find_first_of("://");  // Finds the position of the string specified
  protocol = str.substr(0, p);  // Removes that string from the url

  // Protocol Validation
  if (protocol.compare("http")==0 || protocol.compare("https")==0 ||
  protocol.compare("ftp")==0 || protocol.compare("ftps")==0) {
    wrongPro = 0;
    overallError = 0;
  } else {
    wrongPro = 1;
    overallError = 1;
  }

  str = str.substr(p+3);  // Removing the protocol from the url

// DOMAIN
  int portExists = 0;
  size_t d = str.find_first_of(":");

  // Domain Validation and checking if the PORT is present in the URL
  if (d == 0 || d > 2048 || d < 0) {
    d = str.find_first_of("/");
  } else {
    portExists = 1;
  }

  domain = str.substr(0, d);  // Seperating the domain

  int periods = count(domain, '.'); // Domain validation part 2

  if (periods != 2) {
    wrongDom = 1;
    overallError = 1;
  }

  if (portExists == 1) {
    str = str.substr(d+1);
  } else {
    str = str.substr(d);
  }

  size_t subd = domain.find_last_of(".");
  string subdomain = domain.substr(subd+1); // Finding the subdomain from the domain

  // SUBDOMAIN validation
  if (subdomain.compare("com") ==0 || subdomain.compare("net") ==0 || subdomain.compare("edu") ==0
  || subdomain.compare("biz") ==0 || subdomain.compare("gov") ==0) {
    wrongDom = 0;
  } else {
    wrongDom = 1;
    overallError = 1;
  }

// PORT
  if (portExists == 1) {
    size_t po = str.find_first_of("/");
    port = str.substr(0, po);

    if (check_number(port) == true) {
      str = str.substr(po);

      // PORT Validation
      if (stoi(port) <1 || stoi(port) >65535) {
        wrongPort = 1;
        overallError = 1;
      }
    } else {
        port = "";
        wrongPort = 2;  // PORT does NOT exist
      }
  } else {
    port = "";  // PORT Does not exist
  }

// PATH
int paramExist = 0;
if (str[0] == '/') {
  size_t pa = 0;
  pa = str.find_first_of("?");  // Checking if parameters exist in the URL

  if (pa != 0 && pa < 2048 && pa > 0) {
    paramExist = 1;
    path = str.substr(0, pa);
    str = str.substr(pa);
  }

  // PATH Validation
  if (pa == 0 || pa > 2048 || pa < 0) {
    pa = str.find(".html");
    path = str.substr(0, pa+5);

    if (pa == 0 || pa > 2048 || pa < 0) {
      pa = str.find(".htm");
      path = str.substr(0, pa+4);
    }
  }
} else {
  overallError = 1;
  wrongPath = 1;
}

// PARAMETERS
  if (paramExist == 0) {
    wrongParam = 2; // Parameters do not exist in this URL
  } else {
    parameters = str;
    if (parameters[0] != '?') { // Parameters begin with ?
      wrongParam = 1;
    }
  }

// OUTPUT
  if (overallError == 1) {
    cout << "\nInvalid URL with following erroneous components:" << endl;
    if (wrongPro == 1) {
      cout << "Protocol:    " << protocol << " is not a valid protocol." << endl;
    }
    if (wrongDom == 1) {
      cout << "Domain:      " << domain << " is not a valid domain name." << endl;
    }
    if (wrongPort == 1) {
      cout << "Port:        " << port << " must be between 1 and 65535 beginning with a :" << endl;
    }
    if (wrongPath == 1) {
      cout << "File Path:   " << path << " is not a valid path." << endl;
    }
    if (wrongParam == 1) {
      cout << "Parameters:  " << parameters << " should always begin with a ?" << endl;
    }
  } else {
      cout << "\nProtocol:    " << protocol << endl;
      cout << "Domain:      " << domain << endl;
      if (portExists) {
        cout << "Port:        " << port << endl;
      }
      cout << "File Path:   " << path << endl;
      if (paramExist) {
        cout << "Parameters:  " << parameters << endl;
      }
  }

  return 0;
}

// function to find ocurrance of a specific charecter in a string
int count(string s, char c) {
  int res = 0;

  for (int i = 0 ; i < s.length() ; i++) {
    if (s[i] == c) {
      res++;
    }
  }
  return res;
}

// Function to check if all the charecters in the port are integers
bool check_number(string str) {
  int check = 0;
  for (int i = 0 ; i < str.length() ; i++) {
    if (isdigit(str[i]) == false) {
      check = 1;
    }
  }
  if (check == 0) {
    return true;
  } else {
    return false;
  }
}

// https://cs.utdallas.edu:80/directory/faculty/people.html?name=Robert
// Comment is this
