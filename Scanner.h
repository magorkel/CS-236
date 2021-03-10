#ifndef SCANNER_H
#define SCANNER_H
#include "Token.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
//#include <istream>
using namespace std;
class Scanner
{
private:
	int lineNum = 1;
public:
	//vector<Token> listOfTokens;
	void scanLine(string wholeFile, vector<Token>& listOfTokens)
	{
		Token token;
		ifstream is(wholeFile);
		ostringstream out;
		char nextChar;
		while (is.get(nextChar))
		{
			if (nextChar == '\n')
			{
				++lineNum;
				continue;
			}
			else if (isspace(nextChar))
			{
				continue;
			}
			else if (isalpha(nextChar))
			{
				string word;
				token.setToken(ID);
				while (isalnum(nextChar))
				{
					word += nextChar;
					is.get(nextChar);
				}
				is.putback(nextChar);
				if (word == "Schemes")
				{
					token.setToken(SCHEMES);
				}
				else if (word == "Facts")
				{
					token.setToken(FACTS);
				}
				else if (word == "Rules")
				{
					token.setToken(RULES);
				}
				else if (word == "Queries")
				{
					token.setToken(QUERIES);
				}
				else
				{
					token.setToken(ID);
				}
				token.setActualString(word);
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				continue;
			}
			else if (nextChar == '\'')
			{
				string word;
				word = nextChar;
				int tempLineNum = 0;
				int numOfApos = 1;
				while (is.get(nextChar))
				{
					if (nextChar == '\'' && is.peek() == '\'')
					{
						word += nextChar;
						is.get(nextChar);
						word += nextChar;
						continue;
					}
					if (nextChar == '\'')
					{
						word += nextChar;
						++numOfApos;
						break;
					}
					else if (nextChar == '\n')
					{
						word += nextChar;
						++tempLineNum;
						continue;
					}
					word += nextChar;
				}
				if (numOfApos % 2 != 0)
				{
					token.setToken(UNDEFINED);
				}
				else
				{
					token.setToken(STRING);
				}
				token.setActualString(word);
				token.setLineNum(lineNum);
				lineNum += tempLineNum;
				listOfTokens.push_back(token);
				continue;
			}
#if 1
			else if (nextChar == '#')
			{
				token.setToken(COMMENT);
				string word;
				word = nextChar;
				int tempLineNum = 0;
				if (is.peek() == '|')
				{
					is.get(nextChar);
					word += nextChar;
					while (is.get(nextChar))
					{
						if (nextChar == '\n')
						{
							++tempLineNum;
						}
						word += nextChar;
						if (nextChar == '|' && is.peek() == '#')
						{
							is.get(nextChar);
							word += nextChar;
							break;
						}
					}
					if (is.eof())
					{
						token.setToken(UNDEFINED);
					}
					token.setActualString(word);
					token.setLineNum(lineNum);
					lineNum += tempLineNum;
					//listOfTokens.push_back(token);
					continue;
				}
				while (is.get(nextChar))
				{
					if (nextChar == '\n')
					{
						++tempLineNum;
						break;
					}
					else
					{
						word += nextChar;
					}
				}
				token.setActualString(word);
				token.setLineNum(lineNum);
				lineNum += tempLineNum;
				//listOfTokens.push_back(token);
				continue;
			}
#endif
			else if (nextChar == ',')
			{
				token.setToken(COMMA);
				token.setActualString(",");
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				continue;
			}
			else if (nextChar == '.')
			{
				token.setToken(PERIOD);
				token.setActualString(".");
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				continue;
			}
			else if (nextChar == '?')
			{
				token.setToken(Q_MARK);
				token.setActualString("?");
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				continue;
			}
			else if (nextChar == '(')
			{
				token.setToken(LEFT_PAREN);
				token.setActualString("(");
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				continue;
			}
			else if (nextChar == ')')
			{
				token.setToken(RIGHT_PAREN);
				token.setActualString(")");
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				continue;
			}
			else if ((nextChar == ':') && (is.peek() != '-'))
			{
				token.setToken(COLON);
				token.setActualString(":");
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				continue;
			}
			else if ((nextChar == ':') && (is.peek() == '-'))
			{
				token.setToken(COLON_DASH);
				token.setActualString(":-");
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				is.get(nextChar);
				continue;
			}
			else if (nextChar == '*')
			{
				token.setToken(MULTIPLY);
				token.setActualString("*");
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				continue;
			}
			else if (nextChar == '+')
			{
				token.setToken(ADD);
				token.setActualString("+");
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				continue;
			}

			else if (!isalpha(nextChar) && nextChar != '\n')//
			{
				string word;
				word = nextChar;
				token.setToken(UNDEFINED);
				token.setActualString(word);
				token.setLineNum(lineNum);
				listOfTokens.push_back(token);
				continue;
			}
		}
		token.setToken(END);
		token.setActualString("");
		token.setLineNum(lineNum);
		listOfTokens.push_back(token);
	}
};
#endif //SCANNER_H
