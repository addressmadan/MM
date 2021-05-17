#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << endl << "extractASN1 <inputfile> <outputfile>" << endl;
		return -1;
	}

	string infile = argv[1];
	string outfile = argv[2];
	if (infile.empty())
	{
		cout << endl << "Inputfile cannot be empty." << endl;
		return -2;
	}
	if (outfile.empty())
	{
		outfile = "outfile.asn";
	}

	ifstream fin(infile);
	stringstream instr;
	instr << fin.rdbuf();
	std::string s = instr.str();
	size_t slen = s.length();
	size_t pos = 0;
	size_t leftPos = 0;
	size_t rightPos = 0;
	//std::string::iterator iter = s.begin();
	string strAsn;
	//apple /*abcd*/ ball /*mango*/ tree fruit /*sweet country*/
	while (pos < slen/*iter != s.end()*/)
	{
		if ((pos = s.find(string("/*"),pos)) <= slen)
		{
			leftPos = pos;
			if ((rightPos = s.find(string("*/"),leftPos+2)) <= slen)
			{
				strAsn += s.substr(leftPos + 2, rightPos - leftPos - 2);
				leftPos = rightPos + 2;
				pos = leftPos;
				strAsn += string("\r");
			}
			else
			{
				break;
			}			
		}
	}
	if (!strAsn.empty())
	{
		ofstream fout(outfile);
		fout << strAsn;
	}

	fin.close();
}