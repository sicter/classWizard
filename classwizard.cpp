#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <assert.h>
#include <ctime>
#include <sstream>

using namespace std;
void getSpecs(string specFilename, string& className, vector<string>& objects, vector<string>& operators, string& description);
bool createNewFile(string filename);
void createHeader(string className, vector<string> objects, vector<string> objectsTypes, vector<string> objectsNames, vector<string> operators, string description);
void createImplementation(string className, vector<string> objects, vector<string> objectsTypes, vector<string> objectsNames, vector<string> operators);

int main()
{
string specFilename;
cout << "Enter name of file with specifications: ";
	cin >> specFilename;

string description;
string className;
vector<string> objects(0);
vector<string> objectsTypes(0);
vector<string> objectsNames(0);
vector<string> operators(0);

getSpecs(specFilename, className, objects, operators, description);
for(unsigned int i = 0; i < objects.size(); i++)
	{
		int space = objects[i].find(" ");
		objectsTypes.push_back(objects[i].substr(0, space));
		objectsNames.push_back(objects[i].substr((space + 1), (objects[i].length() - space)));
	}

createHeader(className, objects, objectsTypes, objectsNames, operators, description);
cout << endl;
createImplementation(className, objects, objectsTypes, objectsNames, operators);

string sourceFile = className + ".cpp";

system("PAUSE");
return 0;
}

void getSpecs(string specFilename, string& className, vector<string>& objects, vector<string>& operators, string& description)
{
ifstream fin(specFilename);
assert(fin.is_open());

string wasteString;
string classString;
string objectString;
string operatorString; 
string descriptionString;

	//Skip initial Line which has description
	getline(fin, wasteString);
	bool gettingDescription = true;
	while(gettingDescription)
	{
		getline(fin, descriptionString);
		if(descriptionString.compare("*End*") == 0)
		{
			gettingDescription = false;
		}
		else
		{
		description = description + descriptionString;
		//cout << description << end;
		}
	}
	//Skip initial Line which has class:
	getline(fin, wasteString);
		//Get the class's name
		getline(fin, classString);
		className = classString;
	//Skip the line which has Data Objects
	getline(fin, wasteString);
		//**PRIVATE OBJECTS**
		bool gettingObjects = true;
		while(gettingObjects)
		{
			getline(fin, objectString);
			if(objectString.compare("*End*") == 0)
			{
			gettingObjects = false;
			}
			else 
			{
			objects.push_back(objectString);
			}
		}
	//Skip the line which has Operators
	getline(fin, wasteString);
		//**OPERATORS**
		bool gettingOperators = true;
		while(gettingOperators)
		{
			getline(fin, operatorString);
			if(operatorString.compare("*End*") == 0)
			{
			gettingOperators = false;
			}
			else 
			{
			operators.push_back(operatorString);
			}
		}
}

bool createNewFile(string filename)
{
	ifstream fin(filename);
	if(fin.is_open())
	{
		string overwriteYN;
		cout << "This file already exists, would you like to overwrite (y/n): ";
		cin >> overwriteYN;
		if (overwriteYN.compare("n") == 0)
		{
			fin.close();
			return false;
		}
		else
		{
			fin.close();
			ofstream fout;
			fout.open(filename);
			fout.close();
			return true;
		}
	}
	else
	{
		return true;
	}
}

void createHeader(string className, vector<string> objects, vector<string> objectsTypes, vector<string> objectsNames, vector<string> operators, string description)
{
	string headerFile = className + ".h";
	cout << "Creating header file: " << endl;
	bool replace = createNewFile(headerFile);
	if(replace == true)
	{
	 ofstream fout(headerFile);
	 fout << "// ----------------------------------------------------------------------------" << endl
	 << "//" << endl
	 << "// " << className << " class" << endl
	 << "//    Header" << endl
	 << "//" << endl
	 << "// ";
	 for(unsigned int i = 0; i < description.length(); i++)
	 {

		 if((i != 0) && (i%80 == 0))
		 {
		 fout << description.at(i) << endl;
		 fout << "// " << description.at(i);
		 }
		 else 
		 {
		 fout
			 << description.at(i);
		 }
	 }
fout << "//" << endl
	 << "// ----------------------------------------------------------------------------" << endl
	 << "//" << endl
	 << "// Generating using Edward Aryee Class Generator" << endl
	 << "// Author: " << endl
	 << "// Date: " << endl
	 << "// Modified: " << endl
	 << "//" << endl
	 << "// ----------------------------------------------------------------------------" << endl
	 << endl;

fout << "#ifndef _" << className << "_" << endl
	 << "#define _" << className << "_" << endl
     << endl
	 << "#include <iostream>" << endl
	 << "#include <fstream>" << endl
	 << "#include <string>" << endl
	 << "#include <cmath>" << endl
	 << "#include <iomanip>" << endl
	 << "#include <vector>" << endl
	 << "#include <cstdlib>" << endl
	 << "#include <assert.h>" << endl
	 << "#include <sstream>" << endl
	 << endl
	 << "using namespace std;" << endl
     << "// ----------------------------------------------------------------------------" << endl
     << "// ----------------------------------------------------------------------------" << endl
	 << endl
	 << "class " << className << endl
	 << "{" << endl
	 << "public:" << endl
	 // Potentially add method of getting the public objects
	 <<"		// ------------------------------------------------------" << endl
	 <<"		// ----- Constructors -----------------------------------" << endl
	 <<"		// ------------------------------------------------------" << endl
	 << endl
	 //Null constructor
	 << "			" << className << "();" << endl;
	 //Full alternate constructor
fout << "			" << className << "(";
	 for(unsigned int i = 0; i < objects.size(); i++)
	 {
		 if(i != objects.size() - 1)
		 {
		 fout << "const " << objectsTypes[i] << "& " << objectsNames[i] << ", ";
		 }
		 else
		 {
			 fout << "const " << objectsTypes[i] << "& " << objectsNames[i] << ");" << endl;
		 }
	 }
	 //Copy constructor 
fout << "			" << className << "(const " << className << "& " << "input" << className << ");" << endl;
fout << endl;
fout <<"		// ------------------------------------------------------" << endl
	 <<"		// ----- Destructor -------------------------------------" << endl
	 <<"		// ------------------------------------------------------" << endl
	 << endl
	 << "			" << "~" << className << "();" << endl
	 << endl;
fout <<"		// ------------------------------------------------------" << endl
	 <<"		// ----- Inspectors -------------------------------------" << endl
	 <<"		// ------------------------------------------------------" << endl
	 << endl;
fout << "//Note for vector types, the inspectors will need to be corrected" << endl;
	 for(unsigned int i = 0; i < objects.size(); i++)
	 {
	 fout << "			" << objectsTypes[i] << " get_" << objectsNames[i] << "() const;" << endl;
	 }
fout << endl;
fout <<"		// ------------------------------------------------------" << endl
	 <<"		// ----- Mutators ---------------------------------------" << endl
	 <<"		// ------------------------------------------------------" << endl
	 << endl;
fout << "//Note for vector types, the mutators will need to be corrected" << endl;
	 for(unsigned int i = 0; i < objects.size(); i++)
	 {
	 fout << "			" << "void set_" << objectsNames[i] << "(const " << objectsTypes[i] << "& " << objectsNames[i] << ");" << endl;
	 }
fout <<"		// ------------------------------------------------------" << endl
	 <<"		// ----- Facilitators -----------------------------------" << endl
	 <<"		// ------------------------------------------------------" << endl
	 << endl;
fout << "			" << "string toString();" << endl;
fout << endl;
fout <<"		// ------------------------------------------------------" << endl
	 <<"		// ----- Operators --------------------------------------" << endl
	 <<"		// ------------------------------------------------------" << endl
	 << endl;
for(unsigned int i = 0; i < operators.size(); i++)
		{
		fout << "/* \"returnType\" operator" << operators[i] << "(\"inputOneType& inputOne\",const \"inputTwoType& intputTwo\"); */" << endl;
		}
fout << endl;
fout << "	// ----------------------------------------------------------" << endl
	 << "	// ----------------------------------------------------------" << endl;
fout << endl;
fout << "private:" << endl;
	 for(unsigned int i = 0; i < objects.size(); i++)
	 {
	 fout << "		" << objectsTypes[i] << right << " " << objectsNames[i] << "_;" << endl;
	 }
fout << endl;
fout << "};" 
	 << endl;
fout << "#endif";
fout.close();
cout << "Finished writing header file " << endl;
}

	else
	{
		cout << "Nothing was written to header file" << endl;
	}

}

void createImplementation(string className, vector<string> objects, vector<string> objectsTypes, vector<string> objectsNames, vector<string> operators)
{
	string implementationFile = className + ".cpp";
	cout << "Writing implementation file: " << endl;
	bool replace = createNewFile(implementationFile);
	if(replace == true)
	{

	ofstream fout(implementationFile);
	fout << "// ----------------------------------------------------------------------------" << endl
	 << "//" << endl
	 << "// " << className << " class" << endl
	 << "//    Implementation" << endl
	 << "//" << endl
	 << "//    Version: " << endl
	 << "// ";
fout << "//" << endl
	 << "// ----------------------------------------------------------------------------" << endl
	 << "//" << endl
	 << "// Generating using Edward Aryee Class Generator" << endl
	 << "// Author: " << endl
	 << "// Date: " << endl
	 << "// Modified: " << endl
	 << "//" << endl
	 << "// ----------------------------------------------------------------------------" << endl
	 << endl;

fout << "#include <iostream>" << endl
	 << "#include <fstream>" << endl
	 << "#include <string>" << endl
	 << "#include <cmath>" << endl
	 << "#include <iomanip>" << endl
	 << "#include <vector>" << endl
	 << "#include <cstdlib>" << endl
	 << "#include <assert.h>" << endl
	 << "#include <sstream>" << endl
	 << "#include \"" << className << ".h\""<< endl
	 << endl
	 << "using namespace std;" << endl;
fout << endl;
fout << "//----------------------------------------------------------------------------" << endl
	 << "//----- Constructors----------------------------------------------------------" << endl
	 << "//----------------------------------------------------------------------------" << endl;
fout << endl;
//Null Constructor
fout << className << "::" << className << "()" << endl
	 << "{" << endl;
fout << "//Add null constructor" << endl;
	/*for(unsigned int i = 0; i < objects.size(); i ++)
	{
		fout << "		" << objectsNames[i] << "_ = ";

		string classVector = "vector<" + className + ">";
		string enum{"int" = 0, "double" = 1, "float" = 2, "string" = 3, "vector<int>" = 4, 
					"vector<string>" = 5, classvector = 6} objectType;
		objectType = objectsTypes[i];

		switch(objectType)
		{
		case 0: 
		case 1:
		case 2: 
			fout << "0;" << endl;
		case 3: fout << "\"\";" << endl;
		case 4: fout << "vector<int>();" << endl;
		case 5: fout << "vector<string>()" << endl;
		case 6: fout << "vector<" << className << ">();" << endl;
		default: fout << "//Unrecognized type please add" << endl;
		}
	}*/
	fout << "}" << endl;
fout << endl;
//Alternate Constructor
fout << className << "::" << className << "(";
	for(unsigned int i = 0; i < objects.size(); i ++)
	{
		if(i != objects.size()-1)
		{
		fout << "const " << objectsTypes[i] << "& " << objectsNames[i] << ", "; 
		}
		else
		{
		fout << "const " << objectsTypes[i] << "& " << objectsNames[i] << ")" << endl;
		}
	}
fout << "{" << endl;
	for(unsigned int i = 0; i < objects.size(); i ++)
	{
		fout << "		" << objectsNames[i] << "_ = " << objectsNames[i] <<";" << endl;
	}
fout << "}" << endl;
fout << endl;
//Copy Constructor
fout << className << "::" << className << "(const " << className << "& input" << className << ")" << endl;
fout << "{" << endl
	 << "// Add copy constructor information" << endl
	 << "}" << endl;
fout << endl;
fout << "//----------------------------------------------------------------------------" << endl
	 << "//----- Destructor----------------------------------------------------------" << endl
	 << "//----------------------------------------------------------------------------" << endl;
fout << endl;
fout << className << "::~" << className << "()" << endl
	 << "	{" << endl
	 << endl
	 << "	}" << endl;
fout << endl;
fout << "//----------------------------------------------------------------------------" << endl
	 << "//----- Inspectors----------------------------------------------------------" << endl
	 << "//----------------------------------------------------------------------------" << endl;
fout << endl;
fout << "//Note for vector types, the inspectors will need to be corrected" << endl;
	for(unsigned int i = 0; i < objects.size(); i++)
	{
		fout << objectsTypes[i] << " " << className << "::get_" << objectsNames[i] << "() const" << endl
			<< "	{" << endl
			<< "    " << "return " << objectsNames[i] << "_;" << endl
			<< "	}" << endl;
	}
fout << endl;
fout << "//----------------------------------------------------------------------------" << endl
	 << "//----- Mutators----------------------------------------------------------" << endl
	 << "//----------------------------------------------------------------------------" << endl;
fout << endl;
fout << "//Note for vector types, the mutators will need to be corrected" << endl;
	for(unsigned int i = 0; i < objects.size(); i++)
	{
		fout << "void " << className << "::set_" << objectsNames[i] << "(const " << objectsTypes[i] << "&" << objectsNames[i] << ")" << endl
			<< "	{" << endl
			<< "    " << objectsNames[i] << "_ = " << objectsNames[i] << ";" << endl
			<< "	}" << endl;
	}
fout << endl;
fout << "//----------------------------------------------------------------------------" << endl
	 << "//----- Facilitators----------------------------------------------------------" << endl
	 << "//----------------------------------------------------------------------------" << endl;
fout << endl;
fout << "string " << className << "::toString()" << endl;
fout << "{" << endl
	 << "// Add toString facilitator" << endl
	 << "return \"\";" << endl
	 << "}" << endl;
fout << endl;
fout << "//----------------------------------------------------------------------------" << endl
	 << "//----- Operators----------------------------------------------------------" << endl
	 << "//----------------------------------------------------------------------------" << endl;
fout << "// fill in everything in quotation marks" << endl;
fout << endl;
		for(unsigned int i = 0; i < operators.size(); i++)
		{
		fout << "/* \"returntype\" operator" << operators[i] << "(\"inputOneType& inputOne\",const \"inputTwoType& intputTwo\")" << endl;
		fout << "{" << endl
			 << "// Add operator overload information" << endl
			 << "return something;" << endl
			 << "}*/" << endl << endl;
		}
fout << endl;
fout.close();
cout << "Finished writing implementation file " << endl;
}
	else
	{
		cout << "Nothing was written to implementation file" << endl;
	}
}
