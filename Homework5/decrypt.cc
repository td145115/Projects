//*****************************************************************
// File: decrypt.cc
// AUthor: Trenton Davis
// Purpose: Decryption
//
// outputs the decrypted passwords in parallel and distributed.
//***************************************************************************
#include <stdlib.h>
#include <omp.h>
#include <mpi.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

/*******************************************
 Function: getsalt(string ALLstring)
 Parameters: string ALLstring
 Return Value: string
 Purpose: this function gets the salt of a given password and returns it.
*******************************************/
string getsalt(string ALLstring){
	string SALTstring;
	for(int i = 0; i < 19; i++){
		SALTstring += ALLstring[i];
	}
	return SALTstring;
}

/*******************************************
 Function: singleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a single word. Each element of the dictionary is salted and crypted and then compared.
*******************************************/
bool singleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		permutations = dictionary[i];
		string test = crypt(permutations.c_str(), SALTstring.c_str());
		if(test == ALLstring){
			cout << "Password: " << permutations << endl;
			Answers[zz] = permutations;
			return true;
		}
	}
	return false;
}

/*******************************************
 Function: doubleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a double word. Each element of the dictionary is salted and crypted and then compared.
*******************************************/
bool doubleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int j = 0; j < numwords; j++){
			permutations = dictionary[i] + dictionary[j];
			string test = crypt(permutations.c_str(), SALTstring.c_str());
			if(test == ALLstring){
				cout << "Password: " << permutations << endl;
				Answers[zz] = permutations;
				return true;
			}
		}
	}
	return false;
}

/*******************************************
 Function: singlewordsingledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a single word followed by a single digit. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool singlewordsingledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int j = 0; j < 10; j++){
			permutations = dictionary[i] + to_string(j);
			string test = crypt(permutations.c_str(), SALTstring.c_str());
			if(test == ALLstring){
				cout << "Password: " << permutations << endl;
				Answers[zz] = permutations;
				return true;
			}
		}
	}
	return false;
}

/*******************************************
 Function: singleworddoubledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a single word followed by a double digit. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool singleworddoubledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int j = 0; j < 10; j++){
			for(int k = 0; k < 10; k++){
				permutations = dictionary[i] + to_string(j) + to_string(k);
				string test = crypt(permutations.c_str(), SALTstring.c_str());
				if(test == ALLstring){
					cout << "Password: " << permutations << endl;
					Answers[zz] = permutations;
					return true;
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: singlewordtripledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a single word followed by a triple digit. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool singlewordtripledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int j = 0; j < 10; j++){
			for(int k = 0; k < 10; k++){
				for(int l = 0; l < 10; l++){
					permutations = dictionary[i] + to_string(j) + to_string(k) + to_string(l);
					string test = crypt(permutations.c_str(), SALTstring.c_str());
					if(test == ALLstring){
						cout << "Password: " << permutations << endl;
						Answers[zz] = permutations;
						return true;
					}
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: doublewordtripledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is 2 words followed by a triple digit. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool doublewordtripledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int m = 0; m < numwords; m++){
			for(int j = 0; j < 10; j++){
				for(int k = 0; k < 10; k++){
					for(int l = 0; l < 10; l++){
						permutations = dictionary[i] + dictionary[m] + to_string(j) + to_string(k) + to_string(l);
						string test = crypt(permutations.c_str(), SALTstring.c_str());
						if(test == ALLstring){
							cout << "Password: " << permutations << endl;
							Answers[zz] = permutations;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: doubleworddoubledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is 2 words followed by a double digit. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool doubleworddoubledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int m = 0; m < numwords; m++){
			for(int j = 0; j < 10; j++){
				for(int k = 0; k < 10; k++){
					permutations = dictionary[i] + dictionary[m] + to_string(j) + to_string(k);
					string test = crypt(permutations.c_str(), SALTstring.c_str());
					if(test == ALLstring){
						cout << "Password: " << permutations << endl;
						Answers[zz] = permutations;
						return true;
					}
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: doublewordsingledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is 2 words followed by a single digit. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool doublewordsingledigit(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int m = 0; m < numwords; m++){
			for(int j = 0; j < 10; j++){
				permutations = dictionary[i] + dictionary[m] + to_string(j);
				string test = crypt(permutations.c_str(), SALTstring.c_str());
				if(test == ALLstring){
					cout << "Password: " << permutations << endl;
					Answers[zz] = permutations;
					return true;
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: singledigitsingleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a digit followed by a single word. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool singledigitsingleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int j = 0; j < 10; j++){
			permutations = to_string(j) + dictionary[i];
			string test = crypt(permutations.c_str(), SALTstring.c_str());
			if(test == ALLstring){
				cout << "Password: " << permutations << endl;
				Answers[zz] = permutations;
				return true;
			}
		}
	}
	return false;
}

/*******************************************
 Function: doubledigitsingleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a digit followed by a single word. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool doubledigitsingleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int j = 0; j < 10; j++){
			for(int k = 0; k < 10; k++){
				permutations = to_string(j) + to_string(k) + dictionary[i];
				string test = crypt(permutations.c_str(), SALTstring.c_str());
				if(test == ALLstring){
					cout << "Password: " << permutations << endl;
					Answers[zz] = permutations;
					return true;
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: tripledigitsingleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a digit followed by a single word. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool tripledigitsingleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int j = 0; j < 10; j++){
			for(int k = 0; k < 10; k++){
				for(int l = 0; l < 10; l++){
					permutations = to_string(j) + to_string(k) + to_string(l) + dictionary[i];
					string test = crypt(permutations.c_str(), SALTstring.c_str());
					if(test == ALLstring){
						cout << "Password: " << permutations << endl;
						Answers[zz] = permutations;
						return true;
					}
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: tripledigitdoubleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a digit followed by a single word. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool tripledigitdoubleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int m = 0; m < numwords; m++){
			for(int j = 0; j < 10; j++){
				for(int k = 0; k < 10; k++){
					for(int l = 0; l < 10; l++){
						permutations = to_string(j) + to_string(k) + to_string(l) + dictionary[i] + dictionary[m];
						string test = crypt(permutations.c_str(), SALTstring.c_str());
						if(test == ALLstring){
							cout << "Password: " << permutations << endl;
							Answers[zz] = permutations;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}
/*******************************************
 Function: doubledigitdoubleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a digit followed by a single word. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool doubledigitdoubleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int m = 0; m < numwords; m++){
			for(int j = 0; j < 10; j++){
				for(int k = 0; k < 10; k++){
					permutations = to_string(j) + to_string(k) + dictionary[i] + dictionary[m];
					string test = crypt(permutations.c_str(), SALTstring.c_str());
					if(test == ALLstring){
						cout << "Password: " << permutations << endl;
						Answers[zz] = permutations;
						return true;
					}
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: singledigitdoubleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a digit followed by a single word. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool singledigitdoubleword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int m = 0; m < numwords; m++){
			for(int j = 0; j < 10; j++){
				permutations = to_string(j) + dictionary[i] + dictionary[m];
				string test = crypt(permutations.c_str(), SALTstring.c_str());
				if(test == ALLstring){
					cout << "Password: " << permutations << endl;
					Answers[zz] = permutations;
					return true;
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: wordtripledigitword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a digit followed by a single word. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool wordtripledigitword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int m = 0; m < numwords; m++){
			for(int j = 0; j < 10; j++){
				for(int k = 0; k < 10; k++){
					for(int l = 0; l < 10; l++){
						permutations = dictionary[i] + to_string(j) + to_string(k) + to_string(l)+ dictionary[m];
						string test = crypt(permutations.c_str(), SALTstring.c_str());
						if(test == ALLstring){
							cout << "Password: " << permutations << endl;
							Answers[zz] = permutations;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: worddoubledigitword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a digit followed by a single word. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool worddoubledigitword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int m = 0; m < numwords; m++){
			for(int j = 0; j < 10; j++){
				for(int k = 0; k < 10; k++){
					permutations = dictionary[i] + to_string(j) + to_string(k) + dictionary[m];
					string test = crypt(permutations.c_str(), SALTstring.c_str());
					if(test == ALLstring){
						cout << "Password: " << permutations << endl;
						Answers[zz] = permutations;
						return true;
					}
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: wordsingledigitword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: bool
 Purpose: this function checks to see if the password is a digit followed by a single word. 
 		  Each element of the dictionary appended with a digit is salted and crypted and then compared.
*******************************************/
bool wordsingledigitword(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers){
	string permutations;
	for(int i = 0; i < numwords; i++){
		for(int m = 0; m < numwords; m++){
			for(int j = 0; j < 10; j++){
				permutations = dictionary[i] + to_string(j) + dictionary[m];
				string test = crypt(permutations.c_str(), SALTstring.c_str());
				if(test == ALLstring){
					cout << "Password: " << permutations << endl;
					Answers[zz] = permutations;
					return true;
				}
			}
		}
	}
	return false;
}

/*******************************************
 Function: callall(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int zz, vector<string> &Answers)
 Parameters: int &numwords
 			 vector<string> &dictionary
 			 string SALTstring
 			 string ALLstring
 			 int zz
 			 vector<string> &Answers
 Return Value: void
 Purpose: this function calls all of the functions that are needed, and if none return true will say there is no password.
*******************************************/
void callall(int &numwords, vector<string> &dictionary, string SALTstring, string ALLstring, int i, vector<string> &Answers){
	if(singleword(numwords, dictionary, SALTstring, ALLstring, i, Answers) == false && 
		singlewordsingledigit(numwords, dictionary, SALTstring, ALLstring, i, Answers) == false &&
		singleworddoubledigit(numwords, dictionary, SALTstring, ALLstring, i, Answers) == false &&
		singlewordtripledigit(numwords, dictionary, SALTstring, ALLstring, i, Answers) == false &&
		singledigitsingleword(numwords, dictionary, SALTstring, ALLstring, i, Answers) == false &&
		doubledigitsingleword(numwords, dictionary, SALTstring, ALLstring, i, Answers) == false &&
		tripledigitsingleword(numwords, dictionary, SALTstring, ALLstring, i, Answers) == false){
		cout << "Password not found." << endl;;
	}
}

/*******************************************
 Function: main(int argc, char* argv[])
 Parameters: int argc
 			 char* argv[]
 Return Value: int
 Purpose: This is the main function for program to run, this calls all functions and sets everything up.
*******************************************/
int main(int argc, char* argv[]){
	ifstream file(argv[1]);
	string data;
	int numpasswords = 0;
	vector<string> ALLvec;
	vector<string> SALTvec;
	vector<string> possiblepermutations;

	//reading in the password file and pushing that onto the vector.
	while(!file.eof()){
		numpasswords++;
		getline(file, data);
		ALLvec.push_back(data);
	}

	//getting all of the salts in the password file.
	for(int i = 0; i < numpasswords; i++)
		SALTvec.push_back(getsalt(ALLvec[i]));

	file.close();

	vector<string> dictionary;
	ifstream dict(argv[2]);
	int numwords = 0;
	string word;

	//getting all of the words in the dictionary
	while(!dict.eof()){
		numwords++;
		getline(dict, word);
		dictionary.push_back(word);
	}

	string permutations;
	bool foundpass = false;
	int temp = 0;
	vector<string> Answers(ALLvec.size());
	int num_processes;
	int proc_num;

	MPI_Init(NULL,NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD,&num_processes);
	MPI_Comm_rank(MPI_COMM_WORLD,&proc_num);

	#pragma omp parallel for
	for(int i = proc_num; i < ALLvec.size(); i += num_processes){
		callall(numwords, dictionary, SALTvec[i], ALLvec[i], i, Answers);
	}

	MPI_Finalize();

	dict.close();

	return 0;
}