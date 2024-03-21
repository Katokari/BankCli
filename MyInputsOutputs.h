#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
using namespace std;

namespace MyInput
{
	enum enWhatToCount { Capital = 0, Small = 1, All = 2, Vowel = 3 };
	enum enMatchCase { CaseSensitive = 0, CaseInsensitive = 1 };

	bool IsAllCapital(string String)
	{
		for (int i = 0; i < String.length(); i++)
		{
			if (String[i] < 65 || String[i] > 90)
				return false;
		}
		return true;
	}

	void NumberErrChecker(string ErrMessage, float& Number)
	{
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrMessage;
			cin >> Number;
		}
	}

	void NumberErrChecker(string ErrMessage, int& Number)
	{
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrMessage;
			cin >> Number;
		}
	}

	float ReadNumber(string Message, string ErrMessage)
	{
		float Number = 0;
		cout << Message;
		cin >> Number;
		NumberErrChecker(ErrMessage, Number);
		return Number;
	}

	float ReadPositiveNumber(string Message, string ErrMessage)
	{
		float Number = 0;
		do
		{
			cout << Message;
			cin >> Number;
			NumberErrChecker(ErrMessage, Number);

		} while (Number < 0);
		return Number;
	}
	
	float ReadNumberInRange(string Message, string ErrMessage, float From, float To)
	{
		float Number = 0;
		do
		{
			cout << Message;
			cin >> Number;
			NumberErrChecker(ErrMessage, Number);

		} while (Number < From || Number > To);
		return Number;
	}

	string ReadString(string Message)
	{
		
		string str = "";
		cout << Message;
		getline(cin >> ws, str);
		return str;
	}

	char ReadChar(string Message)
	{
		char chr;
		cout << Message;
		cin >> chr;
		return chr;
	}

	string ConvertToCapitalOfEachFirstLetter(string String)
	{
		bool isFirstLetter = true;

		for (int i = 0; i < String.length(); i++)
		{
			if (String[i] != ' ' && isFirstLetter)
				String[i] = toupper(String[i]);

			isFirstLetter = (String[i] == ' ') ? true : false;
		}

		return String;
	}

	string ConvertToSmallOfEachFirstLetter(string String)
	{
		bool isFirstLetter = true;

		for (int i = 0; i < String.length(); i++)
		{
			if (String[i] != ' ' && isFirstLetter)
				String[i] = tolower(String[i]);

			isFirstLetter = (String[i] == ' ') ? true : false;
		}

		return String;
	}

	string ToLowerString(string String)
	{
		for (int i = 0; i < String.length(); i++)
		{
			String[i] = tolower(String[i]);
		}

		return String;
	}

	string ToUpperString(string String)
	{
		for (int i = 0; i < String.length(); i++)
		{
			String[i] = toupper(String[i]);
		}

		return String;
	}

	char InvertCharacterCase(char chr)
	{
		return (isupper(chr)) ? tolower(chr) : toupper(chr); 
	}

	string InvertAllStringCase(string String)
	{
		for (int i = 0; i < String.length(); i++)
		{
			InvertCharacterCase(String[i]);
		}

		return String;
	}

	bool IsVowel(char chr)
	{
		chr = tolower(chr);

		return ((chr == 'a') || (chr == 'e') || (chr == 'i') || (chr == 'u') || (chr == 'o'));
	}

	int CountLetters(string String, enWhatToCount WhatToCount = enWhatToCount::All)
	{
		if (WhatToCount == enWhatToCount::All)
			return String.length();

		int Counter = 0;
		for (int i = 0; i < String.length(); i++)
		{
			switch (WhatToCount)
			{
			case enWhatToCount::Capital:
				Counter += (isupper(String[i])) ? 1 : 0;
				break;
			case enWhatToCount::Vowel:
				Counter += (IsVowel(String[i])) ? 1 : 0;
				break;
			
			default:
				Counter += (islower(String[i])) ? 1 : 0;
				break;
			}
		}

		return Counter;
	}

	int CountLetter(string String, char chr, enMatchCase MatchCase = enMatchCase::CaseSensitive)
	{
		int Counter = 0;
		for (int i = 0; i < String.length(); i++)
			switch (MatchCase)
			{
			case enMatchCase::CaseInsensitive:
				Counter += (tolower(String[i]) == tolower(chr)) ? 1 : 0;
				break;
			
			default:
				Counter += (String[i] == chr) ? 1 : 0;
				break;
			}

		return Counter;
	}

	bool ValidateNumberInRange(float Number, float From, float To)
	{
		return (Number >= From && Number <= To);
	}

	vector<string> SplitString(string String, string Delim)
	{
		vector<string> vTokens;
		short pos = 0;
		string Token;

		while ((pos = String.find(Delim)) != std::string::npos)
		{
			Token = String.substr(0, pos);

			if (Token != "")
				vTokens.push_back(Token);
			
			String.erase(0, pos + Delim.length());
		}

		if (String != "")
			vTokens.push_back(String);

		return vTokens;
	}

	string TrimLeft(string String)
	{
		for (short i = 0; i < String.length(); i++)
			if (String[i] != ' ')
				return String.substr(i, String.length() - i);

		return "";
	}

	string TrimRight(string String)
	{
		for (short i = String.length() - 1; i >= 0; i--)
			if (String[i] != ' ')
				return String.substr(0, String.length() - i);

		return "";
	}

	string Trim(string String)
	{
		return TrimLeft(TrimRight(String));
	}

	string JoinString(vector<string>& vTokens, string Delim)
	{
		string S1 = "";
		for (string& Token : vTokens)
			S1 = S1 + Token + Delim;

		return S1.substr(0, S1.length() - Delim.length());
	}

	string JoinString(string Tokens[], int Length, string Delim)
	{
		string S1 = "";
		for (int i = 0; i < Length; i++)
			S1 = S1 + Tokens[i] + Delim;

		return S1.substr(0, S1.length() - Delim.length());
	}

	string ReverseWordsInString(string S1)
	{
		vector<string> vString = MyInput::SplitString(S1, " ");
		vector<string>::iterator iter;
		S1 = "";

		for (iter = vString.end() - 1; iter != vString.begin() - 1; iter--)
			S1 = S1 + *iter + " ";

		return S1.substr(0, S1.length() - 1);
	}

	string ReplaceWordsInString(string S1, string Source, string Dist, enMatchCase MatchCase = enMatchCase::CaseSensitive)
	{
		vector<string> vString = SplitString(S1, " ");

		for (string& Word : vString)
		{
			if (MatchCase == enMatchCase::CaseSensitive)
			{
				if (Word == Source)
					Word = Dist;
			}
			else
			{
				if (ToLowerString(Word) == ToLowerString(Source))
					Word = Dist;
			}
		}

		return JoinString(vString, " ");
	}

	string RemovePunctuationsFromString(string S1)
	{
		for (int i = 0; i < S1.length(); i++)
		{
			if(ispunct(S1[i]))
				S1 = S1.erase(i, 1);
		}
		return S1;
	}
}