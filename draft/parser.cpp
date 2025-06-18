#include "parser.h"
#include <iostream>

void Parser::OPSGenerate(int sym, std::string tval)
{
    switch (sym)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '=':
    case '>':
    case '<':
    case NOT_EQUALS:			//!=
    case GREATER_OR_EQUAL:	//>=
    case LESS_OR_EQUAL:		//<=
    case EQUAL:				//==

        OPSarr[OPScount].elem = tval;		//знак в опс
        OPSarr[OPScount].type = SIGN;
        OPScount++;
        break;
    case INTEGER:							//константа целочисленная в опс
        OPSarr[OPScount].elem = tval;
        OPSarr[OPScount].type = NUMBER;
        OPScount++;
        break;
    case ARRAY:
        OPSarr[OPScount].elem = tval;				//опс содержит имя массива
        OPSarr[OPScount].type = MAS;
        OPScount++;
        break;
    case VAR:
        OPSarr[OPScount].elem = tval;				//имя переменной
        OPSarr[OPScount].type = IDE;
        OPScount++;
        break;
    case INDEX:
        OPSarr[OPScount].elem = "<index>";
        OPSarr[OPScount].type = IND;
        OPScount++;
        break;
    case MJFALSE:
        OPSarr[OPScount].elem = "<jfalse>";
        OPSarr[OPScount].type = JUMPFALSE;
        OPScount++;
        break;
    case MJTRUE:
        OPSarr[OPScount].elem = "<jtrue>";
        OPSarr[OPScount].type = JUMPTRUE;
        OPScount++;
        break;
    case READ:
        OPSarr[OPScount].elem = "read";
        OPSarr[OPScount].type = INP;
        OPScount++;
        break;
    case PRINT:
        OPSarr[OPScount].elem = "print";
        OPSarr[OPScount].type = OUTP;
        OPScount++;
        break;
    default:

        break;
    }
}

void Parser::NextLexem(int sym)
{
    if ((*it).type == sym) {
        //lextype = tokens[vctrind].value;
        it++;
    }
    else
    {
        //здесь нужно вывести сообщение об ошибке, отдельное поле токен
        error_output(*it);
        system("PAUSE");
        exit(0);
    }

}

std::string Parser::LookNext()
{
    ++it;
    return (*it--).value;
    //return tokens[ind+1].value;
}

void Parser::MulDelExpr() //P->(E)|aH|k | H->[E]| λ
{
    switch ((*it).type)
    {
    case INTEGER:							//k
        OPSGenerate(INTEGER, (*it).value);
        NextLexem(INTEGER);
        break;
    case NAME:							//a
        if (LookNext() == "[") {
            OPSGenerate(ARRAY, (*it).value);
            NextLexem(NAME);
            NextLexem('[');
            LocExpr();						//E
            NextLexem(']');
            OPSGenerate(INDEX, "0");
            break;
        }
        else {
            OPSGenerate(VAR, (*it).value);
            NextLexem(NAME);
            break;
        }
    case '(':
        NextLexem('(');
        LocExpr();						//E
        NextLexem(')');
        break;

    default:
        break;
    }
}

void Parser::MulDel() // V->*PV | /PV | λ
{
    Token sym;
    switch ((*it).type)
    {
    case '*':
    case '/':
        sym = *it;
        NextLexem(sym.type);
        MulDelExpr();		//P
        OPSGenerate(sym.type, sym.value);
        MulDel();			//V
        break;

    default:				//λ
        return;
    }
}

void Parser::LocExpr() //E->(E)VU | aHVU | kVU
{
    switch ((*it).type)
    {
    case INTEGER:
        OPSGenerate(INTEGER, (*it).value);
        NextLexem(INTEGER);
        MulDel();						//V
        PlusMinus();					//U
        break;
    case NAME:
        if (LookNext() == "[") {
            OPSGenerate(ARRAY, (*it).value);
            NextLexem(NAME);
            NextLexem('[');
            LocExpr();
            NextLexem(']');
            OPSGenerate(INDEX, "0");
            MulDel();						//V
            PlusMinus();					//U
            break;
        }
        else {
            OPSGenerate(VAR, (*it).value);
            NextLexem(NAME);
            MulDel();						//V
            PlusMinus();					//U
            break;
        }
    case '(':
        NextLexem('(');
        LocExpr();						//E
        NextLexem(')');
        MulDel();						//V
        PlusMinus();					//U
        break;
    default:
        //Сообщение об ошибке нужно здесь?, что входные лексемы не соответсвуют L-грамматике?
        error_output(*it);
        system("PAUSE");
        exit(0);
    }

}

void Parser::PlusMinus() //U-> + TU | -TU | λ
{
    Token sym;
    switch ((*it).type)
    {
    case '+':
    case '-':
        sym = *it;
        NextLexem(sym.type);
        PlusMinusExpr();				//T
        OPSGenerate(sym.type, sym.value);
        PlusMinus();					//U
        break;
    default:							//λ
        break;
    }
}

void Parser::PlusMinusExpr() //T->(E)P | aHP | kP
{
    switch ((*it).type)
    {
    case INTEGER:
        OPSGenerate(INTEGER, (*it).value);			//Записываем значение константы в ОПС
        NextLexem(INTEGER);						//проверка что входной токен строки соответсвует константе, если соответствует-> следующий токен, если нет то вывод об ошибке
        MulDelExpr();						//P
        break;
    case NAME:
        if (LookNext()=="[")
        {
            OPSGenerate(ARRAY, (*it).value);
            NextLexem(NAME);
            NextLexem('[');
            LocExpr();							//E
            NextLexem(']');
            OPSGenerate(INDEX, "0");				//Записываем операцию индексирования в ОПС
            MulDelExpr();
            break;
        }
        else {
            OPSGenerate(VAR, (*it).value);			//Записываем переменную в ОПС
            NextLexem(NAME);
            MulDelExpr();						//P
            break;

        }
    case '(':
        NextLexem('(');
        LocExpr();							//E
        NextLexem(')');
        MulDelExpr();						//P
        break;

    default:
        //Сообщение об ошибке нужно здесь?, что входные лексемы не соответсвуют L-грамматике?
        error_output(*it);
        system("PAUSE");
        exit(0);
    }

}

void Parser::ConditionInBrackets()// С->(E)VUD | aHVUD | kVUD
{
    switch ((*it).type)
    {
    case INTEGER:						//k
        OPSGenerate(INTEGER, (*it).value);
        NextLexem(INTEGER);
        MulDel();					//V
        PlusMinus();				//U
        CompareExpr();				//D
        break;
    case NAME:						//a
        if (LookNext() == "[") {
            OPSGenerate(ARRAY, (*it).value);		//Имя массива
            NextLexem(NAME);
            NextLexem('[');			//проверяет на соответствие лексему которая подана в функцию с той, которая была считана
            LocExpr();				//E  (H->[E])
            NextLexem(']');
            OPSGenerate(INDEX, "0");
            MulDel();				//V
            PlusMinus();			//U
            CompareExpr();			//D
            break;

        }
        else {
            OPSGenerate(VAR, (*it).value);
            NextLexem(NAME);			//Имя переменной
            MulDel();					//V
            PlusMinus();				//U
            CompareExpr();				//D
            break;
        }
    case '(':
        NextLexem('(');
        LocExpr();				//E
        NextLexem(')');
        MulDel();				//V
        PlusMinus();			//U
        CompareExpr();			//D
        break;
    default:
        //Сообщение об ошибке нужно здесь?, что входные лексемы не соответсвуют L-грамматике?
        error_output(*it);
        system("PAUSE");
        exit(0);
    }
}

void Parser::VarExpr()//F->int M;FQ | lambda
{						//M ->aL;      L -> [k]| λ
    if (it != tokens.end()) {
        Token tk;
        switch ((*it).type)
        {
        case INT:
            NextLexem(INT);
            switch ((*it).type)
            {
            case NAME:
                if (LookNext() == "[") {
                    //OPSGenerate(ARRAY, (*it).value);		//Имя массива
                    tk = *it;
                    NextLexem(NAME);
                    NextLexem('[');			//проверяет на соответствие лексему которая подана в функцию с той, которая была считана
                    CreateArray(tk.value);			//размер массива
                    NextLexem(INTEGER);
                    NextLexem(']');
                    //OPSGenerate(INDEX, "0");
                    break;
                }
                else {
                    //OPSGenerate(VAR, (*it).value);
                    CreateVariable((*it).value);
                    NextLexem(NAME);
                }
                break;
            default:
                //Сообщение об ошибке нужно здесь?, что входные лексемы не соответсвуют L-грамматике?
                break;
            }
            NextLexem(';');
            VarExpr();
            QExpr();

        default:
            break;
        }
    }
}

void Parser::QExpr() //Q->aH = E; Q| read(aH); Q| print(E); Q| if(C) {Q} K Q| while(C) {Q} Q | λ
{
    int pointJF, pointJ;

    switch ((*it).type)
    {
    case NAME:			//a
        if (LookNext() == "[") {
            OPSGenerate(ARRAY, (*it).value);
            NextLexem(NAME);
            NextLexem('[');
            LocExpr();		//E тк(H->[E])
            NextLexem(']');
            OPSGenerate(INDEX, "0");
            NextLexem('=');
            LocExpr();		//E
            OPSGenerate('=', "=");
            NextLexem(';');
            QExpr();
            break;
        }
        else if (LookNext() == "=") {
            OPSGenerate(VAR, (*it).value);
            NextLexem(NAME);
            NextLexem('=');
            LocExpr();		//E
            OPSGenerate('=', "=");
            NextLexem(';');
            QExpr(); //Вот тут вопросик нужно посмотреть как работает
            break;
        }

    case READ:
        NextLexem(READ);
        NextLexem('(');
        switch ((*it).type)
        {
        case NAME:
            if (LookNext() == "[") {
                OPSGenerate(ARRAY, (*it).value);
                NextLexem(NAME);
                NextLexem('[');
                LocExpr();
                NextLexem(']');
                OPSGenerate(INDEX, "0");
                NextLexem(')');
                NextLexem(';');
                OPSGenerate(READ, "0");
                QExpr();
                break;
            }
            else {
                OPSGenerate(VAR, (*it).value);
                NextLexem(NAME);
                NextLexem(')');
                NextLexem(';');
                OPSGenerate(READ, "0");
                QExpr();
                break;
            }
        default:
            //Сообщение об ошибке нужно здесь?, что входные лексемы не соответсвуют L-грамматике?
            error_output(*it);
            system("PAUSE");
            exit(0);
        }
        break;
    case PRINT:
        NextLexem(PRINT);
        NextLexem('(');
        LocExpr();
        NextLexem(')');
        NextLexem(';');
        OPSGenerate(PRINT,"0");
        QExpr();
        break;
    case IF:
        NextLexem(IF);
        NextLexem('(');
        ConditionInBrackets();
        NextLexem(')');
        pointJF = OPScount;			//Место для будущей метки jfalse в ОПС
        OPScount++;
        OPSGenerate(MJFALSE, "0");
        NextLexem('{');
        QExpr();
        NextLexem('}');
        switch ((*it).type)
        {
        case ELSE:
            NextLexem(ELSE);
            pointJ = OPScount;		//Место для будущей метки jtrue в ОПС
            OPScount++;
            OPSGenerate(MJTRUE, "0");
            OPSarr[pointJF].elem = std::to_string(OPScount); //в ОПС под индексом pointJF записываем текущее значение OPScount
            OPSarr[pointJ].type = OPSarr[pointJF].type = POINT;
            NextLexem('{');
            QExpr();
            NextLexem('}');
            OPSarr[pointJ].elem = std::to_string(OPScount); //в ОПС под индексом pointJ записываем текущее значение OPScount
            break;
        default:		//если оператора else нет, то просто метка не на блок else, а на следующий оператор
            OPSarr[pointJF].elem = std::to_string(OPScount);
            OPSarr[pointJF].type = POINT;
            break;

        }
        QExpr();
        break;
    case WHILE:			//while(C) {Q} Q
        NextLexem(WHILE);
        NextLexem('(');
        pointJ = OPScount; //запоминаем куда прыгать когда истинности условия в цикле
        ConditionInBrackets();		//условие в скобках
        NextLexem(')');
        pointJF = OPScount; //Место будущей метки m1
        OPScount++;
        OPSGenerate(MJFALSE, "0");		//генерируем jfalse-оператор в ОПС
        NextLexem('{');
        QExpr();						//выражение в квадратных скобках
        NextLexem('}');
        OPSarr[OPScount].elem = std::to_string(pointJ); // в это место записываем значение (pointj) метки m0
        OPSarr[OPScount].type = OPSarr[pointJF].type = POINT;	//делаем m1 и m0 типом point
        OPScount++;
        OPSGenerate(MJTRUE, "0");//заносим <jtrue>-оператор в следующий элемент ОПС
        OPSarr[pointJF].elem = std::to_string(OPScount); //в метку m1 заносим текущее значение OPSCount
        QExpr();
        break;

    default:
        break;
    }

}

void Parser::CompareExpr()//D-> <E|>E|<=E|>=E|==E|!=E
{
    Token sym;

    switch ((*it).type)
    {
    case'<':
    case'>':
    case EQUAL:				//==
    case NOT_EQUALS:			//!=
    case GREATER_OR_EQUAL:	//>=
    case LESS_OR_EQUAL:		//<=
        sym = *it;
        NextLexem(sym.type);
        LocExpr();				//E
        OPSGenerate(sym.type, sym.value);
        break;
    default:
        //Сообщение об ошибке нужно здесь?, что входные лексемы не соответсвуют L-грамматике?
        error_output(*it);
        system("PAUSE");
        exit(0);
    }

}

void Parser::CreateArray(std::string name)
{
    if ((*it).type == INTEGER) {						//вектору задаем размер, главное чтобы он не изменил размерность
        massivint[name].resize(std::stoi((*it).value));
    }
}

void Parser::CreateVariable(std::string name)
{
    if ((*it).type == NAME) {					//в map записываем по имени но без значения
        variables[name] = 0;
    }
}

void Parser::OPSProcessing()
{
    int len = OPScount;
    int current = 0, look, ps = 0;
    std::stack <StackElem> st;				//стек для опс
    StackElem element1;
    StackElem element2;
    int* left_operand;
    int right_operand;
    int point;
    std::string sym;
    int res;

    while (current < len) {
        switch (OPSarr[current].type)
        {
        case NUMBER:			//константа целое число
            element1.value = new int (stoi(OPSarr[current].elem));	//берем первый слева элемент опс и заносим в StackElement
            element1.type = NUMBER;
            st.push(element1);							//StackElement заносим в стек
            current++;									//переходим к следующему элементу
            break;
        case IDE:			//ссылку на переменную записываем в стек
            element1.value = &variables[OPSarr[current].elem];	//значение элемента стека указывает на переменную под названием OPSarr[current].elem, переменная находится в таблице переменных variables
            element1.type = IDE;
            st.push(element1);
            current++;
            break;
        case MAS:			//ссылку на массив записываем в стек
            element1.value = massivint[OPSarr[current].elem].data();	//data возвращает указатель на первый элемент вектора(массива)
            element1.type = MAS;
            st.push(element1);
            current++;
            break;
        case IND:					//реализация индексирования
            element1 = st.top(); st.pop();			//индекс массива
            element2 = st.top(); st.pop();			//сам массив, ссылка указывает на начало
            StackElem elem;
            elem.value = (element2.value + *(element1.value));		//индексируем массив и ссылку на элемент под индексом записываем в elem
            elem.type = MAS;
            st.push(elem);
            current++;
            break;
        case SIGN:
            sym = OPSarr[current].elem;		//значение самого знака в виде строки
                //переменная для результата операций

            element2 = st.top(); st.pop();		//правое значение
            element1 = st.top(); st.pop();		//левое значение

            left_operand = element1.value;
            right_operand = *element2.value;

            if (sym == "=") {
                *left_operand = right_operand;
                current++;
            }
            else if (sym == "+") {
                res = *left_operand + right_operand;
                element1.value = new int(res);
                element1.type = NUMBER;
                st.push(element1);
                current++;
            }
            else if (sym == "-") {
                res = *left_operand - right_operand;
                element1.value = new int(res);
                element1.type = NUMBER;
                st.push(element1);
                current++;
            }
            else if (sym == "*") {
                res = *left_operand * right_operand;
                element1.value = new int(res);
                element1.type = NUMBER;
                st.push(element1);
                current++;
            }
            else if (sym == "/") {
                res = *left_operand / right_operand;		//здесь всегда будет целая часть
                element1.value = new int(res);
                element1.type = NUMBER;
                st.push(element1);
                current++;

            }
            else if (sym == ">") {
                res = 0;
                if (*left_operand > right_operand) res = 1;
                element1.value = new int(res);
                element1.type = NUMBER;
                st.push(element1);
                current++;

            }
            else if (sym == "<") {
                res = 0;
                if (*left_operand < right_operand) res = 1;
                element1.value = new int(res);
                element1.type = NUMBER;
                st.push(element1);
                current++;
            }
            else if (sym == "!=") {
                res = 0;
                if (*left_operand != right_operand) res = 1;
                element1.value = new int(res);
                element1.type = NUMBER;
                st.push(element1);
                current++;
            }
            else if (sym == "==") {
                res = 0;
                if (*left_operand == right_operand) res = 1;
                element1.value = new int(res);
                element1.type = NUMBER;
                st.push(element1);
                current++;
            }
            else if (sym == ">=") {
                res = 0;
                if (*left_operand >= right_operand) res = 1;
                element1.value = new int(res);
                element1.type = NUMBER;
                st.push(element1);
                current++;
            }
            else if (sym == "<=") {
                res = 0;
                if (*left_operand <= right_operand) res = 1;
                element1.value = new int(res);
                element1.type = NUMBER;
                st.push(element1);
                current++;

            }
            break;
        case POINT:
            point = stoi(OPSarr[current].elem);				//сама точка
            current++;
            if (OPSarr[current].type == JUMPFALSE) {

                element1 = st.top(); st.pop();
                if (*element1.value == 1)					//если истинно то продвигаемся дальше
                    current++;
                else
                    current = point;					//если нет то прыгаем на метку false

            };
            if (OPSarr[current].type == JUMPTRUE) current = point;		//здесь просто переход на метку
            break;

        case OUTP:
            element1 = st.top(); st.pop();
            switch (element1.type)
            {
            case IDE:
            case NUMBER:
            case MAS:
                std::cout << *element1.value<<'\n';
                current++;
                break;

            default:
                break;
            }
            break;
        case INP:
            element1 = st.top(); st.pop();
            switch (element1.type)
            {
            case IDE:
            case MAS:
                std::cin >> *element1.value;
                current++;
                break;
            default:
                break;
            }
            break;
        default:
            break;

        }
    }

}

void Parser::OPSoutput()
{
    for (int i = 0; i < OPScount + 1; i++)
    {
        std::cout << OPSarr[i].elem << " ";

    }
    std::cout << "\n";
}




Parser::Parser(std::vector<Token> input_tokens) {
    tokens = input_tokens;
    it = tokens.begin();

}
Parser::~Parser()
{
}
