#include "lexer.h"
#include "parser.h"
#include <fstream>
#include <sstream>

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");

    // Проверяем, что передан хотя бы один аргумент (имя файла)
    if (argc < 2) {
        std::cerr << "Ошибка: Укажите имя файла в аргументах командной строки.\n";
        std::cerr << "Пример: " << argv[0] << " example.TXT\n";
        return 1;
    }

    // argv[0] — имя программы, argv[1] — первый аргумент (имя файла)
    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл '" << argv[1] << "'\n";
        return 2;
    }
    // Создаем строковый поток
    std::stringstream buffer;
    buffer << inputFile.rdbuf(); // читаем всё из файла в поток

    // Получаем содержимое файла как строку
    std::string fileContent = buffer.str();

    inputFile.close();

    Lexer lex(fileContent);

    std::vector<Token> tokens;

    try {
        tokens = lex.get_tokens();

        Parser parser(tokens);

        parser.VarExpr();

        //parser.OPSoutput(); //debug

        parser.OPSProcessing();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (...) {  // Ловит любые другие исключения
        std::cerr << "Неизвестная ошибка!" << std::endl;
    }

    std::cout << std::endl;

}
