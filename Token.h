#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <sstream>
using namespace std;
enum TokenType { COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, UNDEFINED, END };
class Token
{
private:
	//TokenType comma = COMMA;
	int tokenFromScanner;
	string tokenFromScannerString;
	string actualString;
	int lineNum;
public:
	Token() : tokenFromScanner(0), tokenFromScannerString(""), actualString(""), lineNum(0) {}
#if 0
	Token(int inputToken, string inputString, int inputLineNum)
	{
		switch (inputToken)
		{
		case 0: tokenFromScanner = "COMMA";
			break;
		case 1: tokenFromScanner = "PERIOD";
			break;
		case 2: tokenFromScanner = "Q_MARK";
			break;
		case 3: tokenFromScanner = "LEFT_PAREN";
			break;
		case 4: tokenFromScanner = "RIGHT_PAREN";
			break;
		case 5: tokenFromScanner = "COLON";
			break;
		case 6: tokenFromScanner = "COLON_DASH";
			break;
		case 7: tokenFromScanner = "MULTIPLY";
			break;
		case 8: tokenFromScanner = "ADD";
			break;
		case 9: tokenFromScanner = "SCHEMES";
			break;
		case 10: tokenFromScanner = "FACTS";
			break;
		case 11: tokenFromScanner = "RULES";
			break;
		case 12: tokenFromScanner = "QUERIES";
			break;
		case 13: tokenFromScanner = "ID";
			break;
		case 14: tokenFromScanner = "STRING";
			break;
		case 15: tokenFromScanner = "COMMENT";
			break;
		case 16: tokenFromScanner = "UNDEFINED";
			break;
		case 17: tokenFromScanner = "EOF";
			break;
		}
		actualString = inputString;
		lineNum = inputLineNum;
	}
	~Token();
#endif
	void setToken(int inputToken)
	{
		switch (inputToken)
		{
		case COMMA: 
			tokenFromScanner = COMMA; 
			tokenFromScannerString = "COMMA";
			break;
		case PERIOD: 
			tokenFromScanner = PERIOD;
			tokenFromScannerString = "PERIOD";
			break;
		case Q_MARK: 
			tokenFromScanner = Q_MARK;
			tokenFromScannerString = "Q_MARK";
			break;
		case LEFT_PAREN: 
			tokenFromScanner = LEFT_PAREN;
			tokenFromScannerString = "LEFT_PAREN";
			break;
		case RIGHT_PAREN:
			tokenFromScanner = RIGHT_PAREN;
			tokenFromScannerString = "RIGHT_PAREN";
			break;
		case COLON:
			tokenFromScanner = COLON;
			tokenFromScannerString = "COLON";
			break;
		case COLON_DASH:
			tokenFromScanner = COLON_DASH;
			tokenFromScannerString = "COLON_DASH";
			break;
		case MULTIPLY:
			tokenFromScanner = MULTIPLY;
			tokenFromScannerString = "MULTIPLY";
			break;
		case ADD:
			tokenFromScanner = ADD;
			tokenFromScannerString = "ADD";
			break;
		case SCHEMES:
			tokenFromScanner = SCHEMES;
			tokenFromScannerString = "SCHEMES";
			break;
		case FACTS:
			tokenFromScanner = FACTS;
			tokenFromScannerString = "FACTS";
			break;
		case RULES:
			tokenFromScanner = RULES;
			tokenFromScannerString = "RULES";
			break;
		case QUERIES:
			tokenFromScanner = QUERIES;
			tokenFromScannerString = "QUERIES";
			break;
		case ID:
			tokenFromScanner = ID;
			tokenFromScannerString = "ID";
			break;
		case STRING:
			tokenFromScanner = STRING;
			tokenFromScannerString = "STRING";
			break;
		case COMMENT:
			tokenFromScanner = COMMENT;
			tokenFromScannerString = "COMMENT";
			break;
		case UNDEFINED:
			tokenFromScanner = UNDEFINED;
			tokenFromScannerString = "UNDEFINED";
			break;
		case END:
			tokenFromScanner = END;
			tokenFromScannerString = "EOF";
			break;
		}
		//return tokenFromScanner;
	}
	int getToken()
	{
		return tokenFromScanner;
	}
	void setActualString(string inputString)
	{
		actualString = inputString;
		//return actualString;
	}
	string getActualString()
	{
		return actualString;
	}
	void setLineNum(int inputLineNum)
	{
		lineNum = inputLineNum;
		//return lineNum;
	}
	string toString() const
	{
		ostringstream out;
		out << "(" << tokenFromScannerString << ",\"" << actualString << "\"," << lineNum << ")"; // will output 0 right now
		return out.str();
	}
};
#endif // TOKEN_H
