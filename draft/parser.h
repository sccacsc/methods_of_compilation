#ifndef PARSER_H
#define PARSER_H

#define	N 100
#define VAR 257
#define ARRAY 258
#define MJFALSE 260//ìåòêà ïåðåõîäà ïî "ëîæü" äëÿ ÎÏÑ
#define ERROR_P -1
#define MJTRUE 261 //ìåòêà áåçóñëîâíîãî ïåðåõîäà äëÿ ÎÏÑ
#define INDEX 262  //ìåòêà ìàññèâà äëÿ ÎÏÑ äëÿ èíäåêñàöèè


#define NONE	"-1" //äðóãîé ñèìâîë

#include "utilities.h"


#include <vector>
#include <stack>

class Parser
{
public:
    Parser(std::vector<Token> input_tokens);
    ~Parser();


private:
    enum OPSType
    {
        IDE,		//ÏÅÐÅÌÅÍÍÀß
        MAS,		//ÌÀÑÑÈÂ
        NUMBER,		//ÊÎÍÑÒÀÍÒÀ
        SIGN,		//ÎÏÅÐÀÖÈß
        POINT,		//ÒÎ×ÊÀ ÏÅÐÅÕÎÄÀ
        IND,		//ÈÍÄÅÊÑÀÒÎÐ
        JUMPFALSE,	//ÎÏÅÐÀÖÈß ÏÅÐÅÕÎÄÀ ÏÐÈ ÓÑËÎÂÈÈ FALSE
        JUMPTRUE,	//ÎÏÅÐÀÖÈß ÁÅÇÓÑËÎÂÍÎÃÎ ÏÅÐÅÕÎÄÀ
        INP,		//ÎÏÅÐÀÖÈß ×ÒÅÍÈß
        OUTP		//ÎÏÅÐÀÖÈß ÂÛÂÎÄÀ
    };

    struct OPSElem {			//ýëåìåíò îïñ
        std::string elem;		//çíà÷åíèå ýëåìåíòà ÎÏÑ?
        OPSType type;	//òèï ýëåìåíòà ÎÏÑ

    };

    struct StackElem	///ýëåìåíò ñòåêà
    {
        int* value;
        OPSType type;

    };

    std::map<std::string, std::vector<int>> massivint;			//òàáëèöà ìàññèâîâ (åãî èìÿ è ñàì ìàññèâ)
    std::map<std::string, int> variables;			//òàáëèöà ïåðåìåííûõ(èìÿ ïåðåìåííîé è åå çíà÷åíèå)


    std::vector<Token> tokens;	//Òîêåíû îò ëåêñè÷åñêîãî àíàëèçàòîðà, ýòîò âåêòîð îïðåäåëÿåòñÿ â êîíñòðóêòîðå
    std::vector<Token>::iterator it;				//Èòåðàòîð äëÿ âåêòîðà

    int n;					//ñèìâîëüíàÿ äëèíà ýëåìåíòà â ÎÏÑ
    int OPScount = 0;		/*ñ÷¸ò÷èê ýëåìåíòîâ â ÎÏÑ*/
    OPSElem OPSarr[9999]; /*ãåíåðèðóåìàÿ ÎÏÑ*/

public:

    void OPSGenerate(int sym, std::string tval);	//Ãåíåðàöèÿ ÎÏÑ
    void NextLexem(int sym);			//Ñëåäóþùàÿ ëåêñåìà, ïðîâåðÿåì ñîîòâåòñòâóåò ëè îíà òîé ÷òî â sym

    std::string LookNext();				//ñìîòðèì çíà÷åíèå ñëåäóþùåé ëåêñåìû, êîñòûëü äëÿ ìàññèâà

    void MulDelExpr();					//Óìíîæåíèå è äåëåíèå
    void MulDel();						//Ñëîæíîå âûðàæåíèå äåëåíèÿ è óìíîæåíèÿ
    void LocExpr();						//Âûðàæåíèå â ñêîáêàõ
    void PlusMinus();					//Ïëþñ è ìèíóñ
    void PlusMinusExpr();				//Ñëîæíîå âûðàæåíèå ïëþñà è ìèíóñà
    void ConditionInBrackets();			//Âûðàæåíèå â if è while
    void VarExpr();							//Ãðàììàòèêà ñ îáúÿâëåíèÿìè
    void QExpr();					//Ãðàììàòèêà Q
    void CompareExpr();						//Îïåðàòîðû ñðàâíåíèÿ

    void CreateArray(std::string name);
    void CreateVariable(std::string name);

    void OPSoutput();
    void OPSProcessing();					//Îáðàáîòêà ÎÏÑ







};




#endif // !PARSER.H
