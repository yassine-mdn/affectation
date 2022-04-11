//
// Created by yassine on 02/04/2022.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include "Output.h"
using namespace std;

void Output::help()
{
	cout << "resolution problem d'affectation\n\n"
			"affectation [-h] [-g] [-i][filename] [-v] [-o][filename] [-W] [-L] [-H][coefficient] [-S] [-M] [-g]\n\n"
			"-h\tShows help page\n"
			"-i\tTakes input file name\n\tall input files should be put in the input folder and be of the csv format\n"
			"-v\tVerbose output to the terminal\n"
			"-o\tOutputs results in to desired file in the output folder\n\tif the file already exist in the folder in will get overwritten\n"
			"-A\tUse all criterias\n"
			"-W\tUses WALD's criteria\n\tMust give Hurwiez's coefficient"
			"-L\tUses Laplace's criteria\n"
			"-H\tUses Hurwiez's criteria. Must give coefficient\n"
			"-S\tUses Savage's criteria\n"
			"-M\tUses MiniMax and MaxiMax criteria\n";
}

void Output::pretty_matrix_print(vector<std::vector<float>>& m, std::string text)
{
	size_t maxColLen[m.at(0).size()];
	for (int i = 0; i < m.at(0).size(); ++i)
	{
		maxColLen[i] = 0;
	}
	for (int i = 0; i < m.size(); ++i)
	{
		for (int j = 0; j < m.at(i).size(); ++j)
		{
			const size_t num_length{ number_of_digits(m[i][j]) };
			if (num_length > maxColLen[j] )
				maxColLen[j] = num_length;
		}
	}

	cout<<text<<endl;

	for (auto& j: m)
	{
		for (int i = 0; i < j.size(); ++i)
		{
			cout << (i == 0 ? "\n| " : "") << setw((int)maxColLen[i]) << j[i] << (i == j.size() - 1 ? " |" : " ");
		}
	}
	cout << "\n";

}

void Output::output_matrix_to_file(vector<std::vector<float>>& m, std::string path, std::string title, std::string text)
{
	fstream my_file;
	my_file.open(path, ios_base::app);
	my_file <<"\n\n";
	size_t maxColLen[m.at(0).size()];
	for (int i = 0; i < m.at(0).size(); ++i)
	{
		maxColLen[i] = 0;
	}
	for (int i = 0; i < m.size(); ++i)
	{
		for (int j = 0; j < m.at(i).size(); ++j)
		{
			const size_t num_length{ number_of_digits(m[i][j]) };
			if (num_length > maxColLen[j] )
				maxColLen[j] = num_length;
		}
	}

	my_file<<"\n###"<<title<<endl;

	for (auto& j: m)
	{
		for (int i = 0; i < j.size(); ++i)
		{
			my_file << (i == 0 ? "\n\t| " : "") << setw((int)maxColLen[i]) << j[i] << (i == j.size() - 1 ? " |" : " ");
		}
	}

	my_file << "\n";
	my_file<<text;
	my_file << "\n";
	my_file.close();

}

void Output::intialize_file(std::string path)
{
	fstream my_file;
	my_file.open(path, ios::out);
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	my_file << "\n\n##"<<path<<"\n####"<<(now->tm_year + 1900) << '-'
					 << (now->tm_mon + 1) << '-'
					 <<  now->tm_mday << '|'
					 << now->tm_hour <<':'
					 << now->tm_min
					 << "\n";
	my_file.close();
}

size_t Output::number_of_digits(float n)
{
	ostringstream str;
	str << n;
	return str.str().size();
}



