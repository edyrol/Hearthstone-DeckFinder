#pragma once

#include <vector>
#include <algorithm>
#include <sstream>

#include "Card.hpp"
#include "Probability.hpp"
#ifdef __linux__ 
    #include "GeneralLinux.hpp"
#elif _WIN32
    #include "GeneralWindows.hpp"
#else

#endif



//says if an element 'e' is in a list
template<class Element>
bool is_in(const Element& e, const std::vector<Element> List)
{
	for (Element e2 : List)
		if (e == e2)return true;
	return false;
}

//converts a string in upper case to a standar name, i.e. first letter in upper and the others in lower.
std::string upper_to_standar_names(const std::string s);

//Combinations
int Comb(int n, int k);
//Geometric mean
double geometric_mean(const std::vector<double>& X);
//binary exponentation
double binary_exponentiation(double x, int n);
//returns the index of a tuple in an ordered list of tuples with maximum value L-1
int mult_index(const int L, const std::vector<int>& Tuple);

//2-part recursive method. returns a list with all k-tuples indices (i.e. in order with L-1 its maximum value) with elements in a another list.
void get_tuples_indices_recursively(	const std::vector<int>& List,
										const int L,
										std::vector<int>& TuplesIndices,
										std::vector<int>& Counters,
										int level	);
std::vector<int> get_tuples_indices(const std::vector<int>& List, const int L, const int k);

//remove cards without enough matches to be considered
template <class TuplesFile>
void remove_entries_without_enough_matches(TuplesFile& Tuples, int minMatchNumber)
{
	for (int c1 = 0; c1< Tuples.Size(); ++c1)
		if (Tuples[c1]["playedMatches"].GetInt() < minMatchNumber)
			Tuples.Erase(Tuples.Begin() + c1--);
}
//calculate winRatio parameter in database
template <class TuplesFile>
void calculate_win_ratio(TuplesFile& Tuples) 
{
	for (int c1 = 0; c1 < Tuples.Size(); ++c1)
		if (Tuples[c1]["playedMatches"].GetInt()>0)
			Tuples[c1]["winRatio"].SetFloat(
				Tuples[c1]["wonMatches"].GetInt() / (double)(Tuples[c1]["playedMatches"].GetInt())
			);
}