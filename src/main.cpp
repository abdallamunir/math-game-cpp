#include <iostream>
#include<cstdlib>
using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

int RandomNumberInRange(int From, int To)
{
	//function to generate random number

	int randNum = std::rand() % (To - From + 1) + From;
	return randNum;
}


string GetOpTypeSymbol(enOperationType opType)
{
	switch (opType)
	{
	case Add:
		return "+";
	case Sub:
		return "-";
	case Mult:
		return "x";
	case Div:
		return "/";
	case MixOp:
		return "Mix";
	}
}
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
	return arrQuestionLevelText[QuestionLevel - 1];
}
void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); //green bg
	else
	{
		system("color 4F");
		cout << "\a";
	}

}
short ReadHowManyQuestions()
{
	short NumberOfQuestions;
	do
	{
		cout << "How many questions you would like to answer? (1 to 10)\n";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions >10);
	return NumberOfQuestions;
}
enQuestionsLevel ReadQuestionLevel()
{
	short QuestionLevel;
	do
	{
		cout << "Enter question level: [1] Easy,[2] Med,[3] Hard,[4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel > 4);
	return (enQuestionsLevel)QuestionLevel;
}
enOperationType ReadOperationType()
{
	short OpType;
	do
	{
		cout << "Enter operation type: [1] Add,[2] Sub,[3] Mult,[4] Div,[5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType >5);
	return (enOperationType)OpType;
}
struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswer = 0;
	int PlayerAnser = 0;
	bool AnswerResult = false;

};
struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};
int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case Add:
		return Number1 + Number2;
	case Sub:
		return Number1 - Number2;
	case Mult:
		return Number1 * Number2;
	case Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}
enOperationType GeetRandomOperationType()
{
	int Op = RandomNumberInRange(1, 4);
	return (enOperationType)Op;
}
stQuestion GenerateQuesion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
	stQuestion Question;
	if (QuestionLevel == Mix)
	{
		QuestionLevel = (enQuestionsLevel)RandomNumberInRange(1, 3);//??
	}
	if (OpType == MixOp)
	{
		OpType = GeetRandomOperationType();
	}
	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case EasyLevel:
		Question.Number1 = RandomNumberInRange(1, 10);
		Question.Number2 = RandomNumberInRange(1, 10);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;

		return Question;
	case MedLevel:
		Question.Number1 = RandomNumberInRange(1, 50);
		Question.Number2 = RandomNumberInRange(1, 50);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;

		return Question;;
	case HardLevel:
		Question.Number1 = RandomNumberInRange(50, 100);
		Question.Number2 = RandomNumberInRange(50, 100);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionLevel;

		return Question;;
	}
	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuesion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}
int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}
void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question  [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n--------------\n";

}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnser != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;
		cout << "\nWrong Answer :-(\n";
		cout << "The right answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";


	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;
		cout << "Right Answer :-) \n";
	}
	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnser = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}
string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}
void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "----------------------------\n\n";
	cout << "Final Results is " <<
		GetFinalResultsText(Quizz.isPass);
	cout << "\n----------------------------\n\n";
	cout << "Number of questions     : " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level         : " << Quizz.QuestionsLevel << endl;
	cout << "Op Type                 : " << Quizz.OpType << endl;
	cout << "Number of right answers : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of wrong answers : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "----------------------------\n\n";

}
void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOperationType();

	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayMathGame();
		cout << endl << "Do you want to play again ? Y/N  ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}



int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}

