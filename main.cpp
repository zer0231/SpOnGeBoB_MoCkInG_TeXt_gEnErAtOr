#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <Windows.h> // use < > for all system and library headers
#include <winuser.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <complex>
#include <string>
using namespace std;
// 2. forward declaration (also see later)
void toClipboard(HWND hwnd, const std::string &s);//To copy text on clipboard

void convert(string& AAA)//To convert text
{
    for(int i =0;i<AAA.length();i++)
    {
        
    	if(i%2 ==0){
        AAA[i]= toupper(AAA[i]);
 		}
    }
}
int main (){

	string AAA;
cout<<"Enter a string"<<endl;
getline(cin, AAA);
convert(AAA);
	cout << AAA << endl;
	// 1. strlen takes a const char*, so have to call the strings c_str() method
	// (but it would be better to use len = AAA.length() instead)
	size_t len = strlen(AAA.c_str());
	cout << len << " char(s)" << endl;
	// get desktop windows and the call toClipboard
	HWND hwnd = GetDesktopWindow();
	toClipboard(hwnd, AAA);
	cin.clear();
	cin.ignore(255, '\n');
	cin.get();

	return 0; 
}

// 2. declare functions at file scope 
void toClipboard(HWND hwnd, const std::string &s){
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size()+1);
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size()+1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
}
