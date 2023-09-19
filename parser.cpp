//#include "parser.h"
#include "windows.h"
#include "Circuito.h"

parser::parser()
{
}

parser::~parser()
{
}
void parser::errorPointer(std::map<std::string, std::string> tokens, int linha, std::string argumento, std::string generalForm, std::string currentToken, std::string msgErro)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12); //vermelho
    std::string spaces;
    for (int i = 0; i < argumento.find(tokens[currentToken]); i++)
        spaces += ' ';
    spaces += '^';
    std::cout << "\nparserError:";
    SetConsoleTextAttribute(hConsole, 7); //branco
    std::cout << "line " << linha + 1 << ". "
              << generalForm << ".\n"
              << argumento << "\n"
              << spaces << std::endl;
    SetConsoleTextAttribute(hConsole, 9); //azul
    std::cout << msgErro;
    SetConsoleTextAttribute(hConsole, 7); //branco
    std::cout << "\n\n"
              << std::endl;
    spaces = "";
}

void parser::floatValidator_wSymbol(std::string value, std::map<std::string, std::string> tokens, int linha, std::string argumento, std::string generalForm, std::string currentToken)
{
    //std::cout<<tokens["token3"]<<std::endl;
    std::string spaces;
    for (int i = 0; i < (value.length()); i++)
    {
        try
        {
            if (i == value.length() - 1)
            {
                if (value[i] != 48 && value[i] != 49 && value[i] != 50 && value[i] != 51 && value[i] != 52 &&
                    value[i] != 53 && value[i] != 54 && value[i] != 55 && value[i] != 56 && value[i] != 57 &&
                    value[i] != 77 && value[i] != 107 && value[i] != 109 && value[i] != 117 && value[i] != 46)
                {
                    std::string a(1, value[i]);
                    throw std::string("Invalid Sufix: " + a);
                }
            }
            else if (i == 0)
            {
                if (value[i] != 48 && value[i] != 49 && value[i] != 50 && value[i] != 51 && value[i] != 52 &&
                    value[i] != 53 && value[i] != 54 && value[i] != 55 && value[i] != 56 && value[i] != 57 &&
                    value[i] != 43 && value[i] != 45)
                {
                    std::string b(1, value[i]);
                    throw std::string("Invalid Prefix: " + b);
                }
            }
            else
            {
                if (value[i] != 48 && value[i] != 49 && value[i] != 50 && value[i] != 51 && value[i] != 52 &&
                    value[i] != 53 && value[i] != 54 && value[i] != 55 && value[i] != 56 && value[i] != 57 &&
                    value[i] != 46 && value[i] != 101 && value[i] != 45)
                {
                    std::string d(1, value[i]);
                    throw std::string("Invalid Symbold: " + d);
                }
            }
        }
        catch (std::string msg)
        {
            errorPointer(tokens, linha, argumento, generalForm, currentToken, msg);
        }
    }
}
void parser::intValidator(std::string value, std::map<std::string, std::string> tokens, int linha, std::string argumento, std::string generalForm, std::string currentToken)
{
    //std::cout<<tokens["token3"]<<std::endl;
    std::string spaces;
    for (int i = 0; i < (value.length()); i++)
    {
        try
        {
            if (value[i] != 48 && value[i] != 49 && value[i] != 50 && value[i] != 51 && value[i] != 52 && value[i] != 53 && value[i] != 54 && value[i] != 55 && value[i] != 56 && value[i] != 57)
            {
                throw std::string("Invalid Symbol.");
            }
        }
        catch (std::string msg)
        {
            errorPointer(tokens, linha, argumento, generalForm, currentToken, msg);
        }
    }
}

std::string parser::resistor(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    if (qtd_TOKEN < 3 || qtd_TOKEN > 4)
    {
        std::cout << "\nparserError:line " << linha + 1 << "." << std::endl;
        return "invalid resistor display\n";
    }
    std::string generalForm = "General form: RXXXXXXX N1 N2 VALUE";
    std::string parameter_tk;
    if (qtd_TOKEN == 4)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }

    return "ok";
}

std::string parser::capacitor(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string spaces = ""; //-------------------0----1--2----3----4-5---6-----
    std::string generalForm = "General form: CXXXXXXX N+ N- VALUE <IC=INCOND> ";
    std::string parameter_tk;
    std::string msgErro = "Invalid initial condition. Did you mean: <IC=INCOND> ? ";
    if (qtd_TOKEN == 4)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else if (qtd_TOKEN == 7)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token4";
        if (tokens["token4"] != "IC" || tokens["token5"] != "=")
        {
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        else
        {
            parameter_tk = "token6";
            floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        }
    }
    else
    {
        std::cout << "\nparserError:line " << linha + 1 << "." << std::endl;
        return "invalid capacitor display\n";
    }
    return "ok";
}
std::string parser::inductor(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string spaces = ""; //-------------------0----1--2----3----4-5---6-----
    std::string generalForm = "General form: LYYYYYYY N+ N- VALUE <IC=INCOND> ";
    std::string parameter_tk;
    std::string msgErro = "Invalid initial condition. Did you mean: <IC=INCOND> ? ";
    if (qtd_TOKEN == 4)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else if (qtd_TOKEN == 7)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token4";
        if (tokens["token4"] != "IC" || tokens["token5"] != "=")
        {
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        else
        {
            parameter_tk = "token6";
            floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        }
    }
    else
    {
        std::cout << "\nparserError:line " << linha + 1 << "." << std::endl;
        return "invalid inductor display\n";
    }
    return "ok";
}

std::string parser::sourceVI(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    if (qtd_TOKEN < 4 || qtd_TOKEN > 7)
    {
        std::cout << "\nparserError:line " << linha + 1 << "." << std::endl;
        return "invalid source display\n";
    }
    std::string msgErro;
    std::string spaces = "";
    std::string generalForm;
    std::string token0 = tokens["token0"];
    if (token0[0] = 'V')
        generalForm = "General form: VXXXXXXX N+ N- < DC/TRAN VALUE>";
    if (token0[0] = 'I')
        generalForm = "General form: IXXXXXXX N+ N- < DC/TRAN VALUE>";

    std::string parameter_tk;
    parameter_tk = "token1";
    intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    parameter_tk = "token2";
    intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    try
    {

        if (qtd_TOKEN == 4)
        {
            parameter_tk = "token3";
            floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        }
        else
        {
            if (tokens["token3"] != "COMPLEX"){
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12); //vermelho
                std::cout << "\nparserError:";
            SetConsoleTextAttribute(hConsole, 7); //branco

            std::cout << "line " + std::to_string(linha + 1) +
                             ". Unknown command." + generalForm +
                             "\n" + argumento;
            SetConsoleTextAttribute(hConsole, 9); //azul
            std::cout << "\nDo you mean 'COMPLEX'?" << std::endl;
            SetConsoleTextAttribute(hConsole, 7); //branco
            }
        }
    }
    catch (const std::exception &msg)
    {
        for (int i = 0; i < argumento.find(tokens["token3"]); i++)
            spaces += ' ';
        spaces += '^';
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12); //vermelho
        std::cout << "\nparserError: ";
        SetConsoleTextAttribute(hConsole, 7); //branco
        std::cout << "line " << linha + 1 << ". "
                  << generalForm << ".\n"
                  << argumento << ""
                                  "\n"
                  << spaces << std::endl;
        SetConsoleTextAttribute(hConsole, 9); //azul
        std::cout << "value must be float.\n\n"
                  << std::endl;
        SetConsoleTextAttribute(hConsole, 7); //branco
        spaces = "";
        return "invalid source display";
    }
    if (qtd_TOKEN != 4)
    {
        parameter_tk = "token4";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk); //It's suppposed to be a comma (,)
        //token5 is a comma ","
        if (tokens["token5"] != ",")
        {
            parameter_tk = "token5";
            msgErro = "It's suppposed to be a comma (,).";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token6";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    return "ok";
}

std::string parser::sourceGE(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    if (qtd_TOKEN != 6)
    {
        std::cout << "\nparserError:line " << linha + 1 << "." << std::endl;
        return "invalid source display\n";
    }
    std::string spaces = "";
    std::string generalForm;
    std::string token0 = tokens["token0"];
    if (token0[0] = 'G')
        generalForm = "General form: GXXXXXXX N+ N- < DC/TRAN VALUE>";
    if (token0[0] = 'E')
        generalForm = "General form: EXXXXXXX N+ N- < DC/TRAN VALUE>";

    std::string parameter_tk;
    parameter_tk = "token1";
    intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    parameter_tk = "token2";
    intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    parameter_tk = "token3";
    intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    parameter_tk = "token4";
    intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    parameter_tk = "token5";
    floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    return "ok";
}

std::string parser::sourceFH(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    if (qtd_TOKEN != 5)
    {
        std::cout << "\nparserError:line " << linha + 1 << "." << std::endl;
        return "invalid source display\n";
    }
    std::string spaces = "";
    std::string generalForm;
    std::string token0 = tokens["token0"];
    if (token0[0] = 'F')
        generalForm = " FXXXXXXX N+ N- VNAM VALUE";
    if (token0[0] = 'H')
        generalForm = " HXXXXXXX N+ N- VNAM VALUE";

    std::string parameter_tk;
    parameter_tk = "token1";
    intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    parameter_tk = "token2";
    intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    //token3 = 'VNAM' can be any string
    parameter_tk = "token4";
    floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    return "ok";
}

std::string parser::junctionDiode(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    //---------------------------------------1-------2--3---4------5------6----7-8-9----10
    std::string generalForm = "General form: DXXXXXXX N+ N- MNAME <AREA> <OFF> <IC=VD> <TEMP=T>";
    std::string parameter_tk;
    std::string msgErro;
    if (qtd_TOKEN == 4)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token3 is MNAME
    }
    else if (qtd_TOKEN == 5)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token3 is MNAME
        if (tokens["token4"] != "OFF")
        {
            parameter_tk = "token4";
            floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        }
    }
    else if (qtd_TOKEN == 6)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token3 is MNAME
        parameter_tk = "token4";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        if (tokens["token5"] != "OFF")
        {
            parameter_tk = "token5";
            msgErro = "Did you mean 'OFF'  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
    }
    else if (qtd_TOKEN == 7)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token3 is MNAME
        if (tokens["token4"] != "IC" && tokens["token4"] != "TEMP")
        {
            parameter_tk = "token4";
            msgErro = "Did you mean 'IC' or 'TEMP'  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        if (tokens["token5"] != "=")
        {
            parameter_tk = "token5";
            msgErro = "Did you mean '='  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token6";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else if (qtd_TOKEN == 8)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token3 is MNAME
        if (tokens["token4"] != "OFF")
        {
            parameter_tk = "token4";
            floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        }
        if (tokens["token5"] != "IC" && tokens["token5"] != "TEMP")
        {
            parameter_tk = "token5";
            msgErro = "Did you mean 'IC' or 'TEMP'  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        if (tokens["token6"] != "=")
        {
            parameter_tk = "token6";
            msgErro = "Did you mean '='  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token7";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else if (qtd_TOKEN == 9)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token3 is MNAME

        parameter_tk = "token4";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);

        if (tokens["token5"] != "OFF") // off and area
        {
            parameter_tk = "token5";
            msgErro = "Did you mean 'OFF'  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        if (tokens["token6"] != "IC" && tokens["token6"] != "TEMP") // ic or temp
        {
            parameter_tk = "token5";
            msgErro = "Did you mean 'IC' or 'TEMP'  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        if (tokens["token7"] != "=") // =
        {
            parameter_tk = "token7";
            msgErro = "Did you mean '='  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token8"; // value
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else if (qtd_TOKEN == 10)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token3 is MNAME
        if (tokens["token4"] != "IC")
        {
            parameter_tk = "token4";
            msgErro = "Did you mean 'IC' ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        if (tokens["token5"] != "=")
        {
            parameter_tk = "token5";
            msgErro = "Did you mean '='  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token6";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        if (tokens["token7"] != "TEMP")
        {
            parameter_tk = "token7";
            msgErro = "Did you mean 'TEMP'  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        if (tokens["token8"] != "=")
        {
            parameter_tk = "token8";
            msgErro = "Did you mean '='  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token9";
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else if (qtd_TOKEN == 12)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token3 is MNAME

        parameter_tk = "token4"; // area
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);

        if (tokens["token5"] != "OFF") // off
        {
            parameter_tk = "token5";
            msgErro = "Did you mean 'OFF'  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        if (tokens["token6"] != "IC") // ic
        {
            parameter_tk = "token6";
            msgErro = "Did you mean 'IC'  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        if (tokens["token7"] != "=") // =
        {
            parameter_tk = "token7";
            msgErro = "Did you mean '='  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token8"; // value
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        if (tokens["token9"] != "IC") // TEMP
        {
            parameter_tk = "token9";
            msgErro = "Did you mean 'IC'  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        if (tokens["token10"] != "=") // =
        {
            parameter_tk = "token10";
            msgErro = "Did you mean '='  ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token11"; // value
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else
    {
        //std::cout << "qtd_token: " << qtd_TOKEN << std::endl;
        std::cout << "\nparserError:line " << linha + 1 << "." << std::endl;
        return "invalid junction diode display\n";
    }

    return "ok";
}

//Bipolar Junction Transistors (BJTs)
std::string parser::bjt(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    if (qtd_TOKEN < 4)
    {
        std::cout << "\nparserError:line " << linha + 1 << "." << std::endl;
        return "invalid junction diode display\n";
    } //---------------------------------------0-------1---2--3--4----5------6-----7----8-9-10--11----12-13-14
    std::string generalForm = "General form: QXXXXXXX NC NB NE <NS> MNAME <AREA> <OFF> <IC=VBE, VCE> <TEMP=T>";
    std::string parameter_tk;
    std::string msgErro;
    if (qtd_TOKEN == 5)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token4 is MNAME
    }
    return "ok";
}
//Junction Field-Effect Transistors (JFETs)
std::string parser::jfet(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    if (qtd_TOKEN < 5)
    {
        std::cout << "\nparserError:line " << linha + 1 << "." << std::endl;
        return "invalid JFET display\n";
    } //---------------------------------------0-------1---2--3--4----5------6-----7----8-9-10--11----12-13-14
    std::string generalForm = "General form: JXXXXXXX ND NG NS MNAME <AREA> <OFF> <IC=VDS, VGS> <TEMP>";
    std::string parameter_tk;
    std::string msgErro;
    if (qtd_TOKEN == 5)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token4 is MNAME
    }
    return "ok";
}
//MOSFET
std::string parser::mosfet(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    if (qtd_TOKEN < 6)
    {
        std::cout << "\nparserError:line " << linha + 1 << "." << std::endl;
        return "invalid MOSFET display\n";
    }
    std::string generalForm = "General form: MXXXXXXX ND NG NS NB MNAME <L=VAL> <W=VAL> <AD=VAL> <AS=VAL> + <PD=VAL> <PS=VAL> <NRD=VAL> <NRS=VAL> <OFF> + <IC=VDS, VGS, VBS> <TEMP=T> ";
    std::string parameter_tk;
    std::string msgErro;
    if (qtd_TOKEN == 6)
    {
        parameter_tk = "token1";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token4";
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        // token5 is MNAME
    }
    return "ok";
}
std::string parser::subckt(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN, int *stackSUBCKT)
{
    if (qtd_TOKEN < 3)
    {
        return "invalid subcircuit display\n";
    } //------------------------------------------0----1------2---3----4---5---...
    std::string generalForm = "General form: .SUBCKT subnam N1 &ltN2; N3 ...>";
    std::string parameter_tk;
    std::string msgErro;
    // token 0 .SUBCKT
    // token 1 subname
    for (int i = 0; i < qtd_TOKEN - 2; i++) //verifying all nodes
    {
        parameter_tk = "token" + std::to_string(i + 2);
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    //std::cout << "stack:" << *stackSUBCKT << std::endl;
    *stackSUBCKT = *stackSUBCKT + 1;
    //std::cout << "stack:" << *stackSUBCKT << std::endl;

    return "ok";
}
std::string parser::ends(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN, int *stackSUBCKT)
{
    //std::cout << "stack1:" << *stackSUBCKT << std::endl;
    if (qtd_TOKEN != 2)
    {
        std::string generalForm = "General Form: .ENDS &ltSUBNAM;>";
        std::string parameter_tk = "token0";
        std::string msgErro = "Did you mean '.ENDS SUBCKTNAME' ?";
        errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
    }

    if (*stackSUBCKT <= 0)
    {
        std::string generalForm = "General Form: .ENDS &ltSUBNAM;>";
        std::string parameter_tk = "token0";
        std::string msgErro = "No subcircuit declaration for this .ENDS";
        errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
    }
    else
    {
        *stackSUBCKT = *stackSUBCKT - 1;
    }
    //std::cout << "stack2:" << *stackSUBCKT << std::endl;
    return "ok";
}
std::string parser::subcktCALL(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    if (qtd_TOKEN < 3)
    {
        return "invalid subcircuit call display\n";
    } //------------------------------------------0----1------2---3----4---5---...
    std::string generalForm = "General form: .SUBCKT subnam N1 &ltN2; N3 ...>";
    std::string parameter_tk;
    std::string msgErro;
    // token 0 .SUBCKT
    // token 1 subname
    for (int i = 0; i < qtd_TOKEN - 2; i++) //verifying all nodes
    {
        parameter_tk = "token" + std::to_string(i + 1);
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }

    return "ok";
}
std::string parser::end(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN, bool *cktChaveFecha)
{
    if (qtd_TOKEN != 1)
        errorPointer(tokens, linha, argumento, "General form:'.END'", "token1", "Did you mean '.END'?");
    else
    {
        *cktChaveFecha = false;
    }
    return "ok";
}
//options
std::string parser::options(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{

    std::string parameter_tk;
    std::string parameter_tk_temp;
    std::string parameter_tk_temp_2;
    std::string generalForm = "General Form: .OPTIONS OPT1 OPT2 ... (or OPT=OPTVAL ...)";
    if (qtd_TOKEN < 3)
    {
        return "Invalid OPTIONS display\n";
    }
    for (size_t i = 1; i < qtd_TOKEN; i++)
    {
        parameter_tk = "token" + std::to_string(i);
        if (tokens[parameter_tk] == "ABSTOL" || tokens[parameter_tk] == "BADMOS3" || tokens[parameter_tk] == "CHGTOL" || tokens[parameter_tk] == "DEFAD" ||
            tokens[parameter_tk] == "DEFAS" || tokens[parameter_tk] == "DEFL" || tokens[parameter_tk] == "DEFW" || tokens[parameter_tk] == "GMIN" ||
            tokens[parameter_tk] == "ITL1" || tokens[parameter_tk] == "ITL2" || tokens[parameter_tk] == "ITL3" || tokens[parameter_tk] == "ITL4" ||
            tokens[parameter_tk] == "ITL5" || tokens[parameter_tk] == "KEEPOPINFO" || tokens[parameter_tk] == "METHOD" || tokens[parameter_tk] == "PIVREL" ||
            tokens[parameter_tk] == "PIVTOL" || tokens[parameter_tk] == "RELTOL" || tokens[parameter_tk] == "TEMP" || tokens[parameter_tk] == "TNOM" ||
            tokens[parameter_tk] == "TRTOL" || tokens[parameter_tk] == "TRYTOCOMPACT" || tokens[parameter_tk] == "VNTOL")
        {
            for (std::list<std::string>::iterator it = optionsList.begin(); it != optionsList.end(); ++it)
            {
                if (tokens[*it] == tokens[parameter_tk])
                {
                    errorPointer(tokens, linha, argumento, generalForm, *it, "Redeclaration of parameter in .OPTIONS command.");
                }
            }

            parameter_tk_temp = "token" + std::to_string(i + 1);
            parameter_tk_temp_2 = "token" + std::to_string(i + 2);
            if (tokens[parameter_tk_temp] == "=")
            {
                floatValidator_wSymbol(tokens[parameter_tk_temp_2], tokens, linha, argumento, generalForm, parameter_tk_temp_2);
                optionsList.push_back(parameter_tk);
                i = i + 2;
            }
            else
            {
                errorPointer(tokens, linha, argumento, generalForm, parameter_tk_temp, "Invalid options display.\nFor more info check : http://bwrcs.eecs.berkeley.edu/Classes/IcBook/SPICE/UserGuide/analyses_fr.html");
            }
        }
        else
        {
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, "Invalid options display.\nFor more info check : http://bwrcs.eecs.berkeley.edu/Classes/IcBook/SPICE/UserGuide/analyses_fr.html");
        }
    }

    return "ok";
}
//nodeset
std::string parser::nodeset(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string insideNode = "";
    std::string parameter_tk;
    std::string parameter_tk_temp;
    std::string generalForm = "General Form: .NODESET V(NODNUM)=VAL V(NODNUM)=VAL ... ";
    std::string msgErro;
    for (int i = 1; i < qtd_TOKEN; i++)
    {
        parameter_tk = "token" + std::to_string(i);
        if (tokens[parameter_tk] != "V")
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean 'V' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk_temp = "token" + std::to_string(i + 1); //node
        intValidator(tokens[parameter_tk_temp], tokens, linha, argumento, generalForm, parameter_tk_temp);
        //parameter_tk = "token" + std::to_string(i+2); ===========> '='
        parameter_tk_temp = "token" + std::to_string(i + 3); //value
        floatValidator_wSymbol(tokens[parameter_tk_temp], tokens, linha, argumento, generalForm, parameter_tk_temp);
        i = i + 3;
    }
    if (qtd_TOKEN < 5)
    {
        return "Invalid NODESET display\n";
    }

    return "ok";
}
//.IC: Set Initial Conditions
std::string parser::ic(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string insideNode = "";
    std::string parameter_tk;
    std::string parameter_tk_temp;
    std::string generalForm = "General Form: .IC V(NODNUM)=VAL V(NODNUM)=VAL ... ";
    std::string msgErro;
    for (int i = 1; i < qtd_TOKEN; i++)
    {
        parameter_tk = "token" + std::to_string(i);
        if (tokens[parameter_tk][0] != 'V')
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean 'V' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk_temp = "token" + std::to_string(i + 1); //node
        intValidator(tokens[parameter_tk_temp], tokens, linha, argumento, generalForm, parameter_tk_temp);
        //parameter_tk = "token" + std::to_string(i+2); ===========> '='
        parameter_tk_temp = "token" + std::to_string(i + 3); //value
        floatValidator_wSymbol(tokens[parameter_tk_temp], tokens, linha, argumento, generalForm, parameter_tk_temp);
        i = i + 3;
    }
    if (qtd_TOKEN < 5)
    {
        return "Invalid Initial Conditions display\n";
    }

    return "ok";
}
//AC: Small-Signal AC Analysis
std::string parser::ac(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string parameter_tk;
    std::string generalForm = "General Form: .AC DEC ND FSTART FSTOP | .AC OCT NO FSTART FSTOP | .AC LIN NP FSTART FSTOP";
    std::string msgErro;
    parameter_tk = "token1";
    if (tokens[parameter_tk] != "DEC" && tokens[parameter_tk] != "OCT" && tokens[parameter_tk] != "LIN")
    {
        msgErro = "Wrong definition '" + tokens[parameter_tk] + "', did you mean one of these: DEC | OCT | LIN  ?";
        errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
    }
    parameter_tk = "token2"; //node
    intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    parameter_tk = "token3"; //FSTART
    floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    parameter_tk = "token4"; //FSTOP
    floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    if (qtd_TOKEN != 5)
        return "Invalid AC Analysis display.";

    return "ok";
}
//.DC: DC Transfer Function
std::string parser::dc(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string parameter_tk;
    std::string generalForm = "General Form: .DC SRCNAM VSTART VSTOP VINCR [SRC2 START2 STOP2 INCR2]";
    std::string msgErro;
    parameter_tk = "token0";
    if (qtd_TOKEN != 5 && qtd_TOKEN != 9)
    {
        msgErro = "Invalid '.DC' display";
        errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
    }
    else
    {
        parameter_tk = "token1";
        //do nothing, token1 is name and any name is valid
        parameter_tk = "token2"; //VSTART
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3"; //BSTOP
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token4"; //VINCR
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        if (qtd_TOKEN == 9)
        {
            parameter_tk = "token5";
            //do nothing, token5 is the src2 name and any name is valid
            parameter_tk = "token6"; //VSTART (SRC2)
            floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
            parameter_tk = "token7"; //BSTOP (SRC2)
            floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
            parameter_tk = "token8"; //VINCR (SRC2)
            floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        }
    }
    return "ok";
}
//.PZ: Pole-Zero Analysis
std::string parser::pz(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string parameter_tk;
    std::string generalForm = "General Form: .PZ NODE1 NODE2 NODE3 NODE4 (CUR||VOL) (POL||ZER||PZ)";
    std::string msgErro;
    parameter_tk = "token0";
    if (qtd_TOKEN != 7)
    {
        msgErro = "Invalid '.PZ' display";
        errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
    }
    else
    {
        parameter_tk = "token1"; //node1
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token2"; //node2
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3"; //node3
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token4"; //node4
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);

        parameter_tk = "token5";
        if (tokens["token5"] != "CUR" && tokens["token5"] != "VOL")
        {
            msgErro = "Invalid command '" + tokens["token5"] + "' , did you mean 'CUR' or 'VOL' ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token6";
        if (tokens["token6"] != "POL" && tokens["token6"] != "ZER" && tokens["token6"] != "PZ")
        {
            msgErro = "Invalid command '" + tokens["token6"] + "' , did you mean 'POL' || 'ZER' || 'PZ' ?";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
    }
    return "ok";
}
//.SENS
std::string parser::sens(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string insideNode = "";
    std::string parameter_tk;
    std::string generalForm = ".SENS OUTVAR | .SENS OUTVAR AC 'DEC|OCT|LIN' 'ND|NO|NP' FSTART FSTOP";
    std::string msgErro;

    if (qtd_TOKEN == 4)
    {
        parameter_tk = "token1";
        if (tokens[parameter_tk] != "V" && tokens[parameter_tk] != "I")
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean 'V' or 'I' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        //token2 is name or number
    }
    else if (qtd_TOKEN == 6)
    {
        parameter_tk = "token1";
        if (tokens[parameter_tk] != "V" && tokens[parameter_tk] != "I")
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean 'V' or 'I' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        //token2 is name or number
        parameter_tk = "token3"; //,
        if (tokens[parameter_tk][0] != ',')
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean ',' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        //token4 is name or number
    }
    else if (qtd_TOKEN == 8)
    {
        parameter_tk = "token1"; //OUTVAR
        if (tokens[parameter_tk] != "V" && tokens[parameter_tk] != "I")
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean 'V' or 'I' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        //token 2 is outvar content, can be numbers or string
        parameter_tk = "token3"; //AC
        if (tokens[parameter_tk] != "AC")
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean 'AC' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token4"; //'DEC|OCT|LIN'
        if (tokens[parameter_tk] != "DEC" && tokens[parameter_tk] != "OCT" && tokens[parameter_tk] != "LIN")
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean 'DEC' | 'OCT' | 'LIN' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        parameter_tk = "token5"; //'ND|NO|NP'
        intValidator(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token6"; //FSTART
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token7"; //FSTOP
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else
    {
        return "Invalid SENS display\n";
    }

    return "ok";
}
//.TF - Transfer Function Analysis
std::string parser::tf(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string insideNode = "";
    std::string parameter_tk;
    std::string generalForm = ".TF OUTVAR INSRC. OUTVAR is the small-signal output variable and INSRC is the small-signal input source";
    std::string msgErro;

    if (qtd_TOKEN == 6)
    {
        parameter_tk = "token1";
        if (tokens[parameter_tk] != "V" && tokens[parameter_tk] != "I")
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean 'V' or 'I' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        //token2 is name or number
        parameter_tk = "token3"; //,
        if (tokens[parameter_tk][0] != ',')
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean ',' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        //token4 is name or number
        //token5 INSRC
    }
    else if (qtd_TOKEN == 4)
    {
        parameter_tk = "token1";
        if (tokens[parameter_tk] != "V" && tokens[parameter_tk] != "I")
        {
            msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean 'V' or 'I' ? ";
            errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
        }
        //token2 is name or number, part of the OUTVAR
        //token4 INSRC
    }
    else
    {
        return "Invalid Transfer Function Analysis display\n";
    }

    return "ok";
}
//.TRAN: Transient Analysis
std::string parser::tran(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string insideNode = "";
    std::string parameter_tk;
    std::string generalForm = ".TRAN TSTEP TSTOP <TSTART <TMAX>> ";
    std::string msgErro;

    if (qtd_TOKEN == 3)
    {
        parameter_tk = "token2"; //TSTEP
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3"; //TSTOP
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else if (qtd_TOKEN == 4)
    {
        parameter_tk = "token2"; //TSTEP
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3"; //TSTOP
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token4"; //TSTART
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else if (qtd_TOKEN == 5)
    {
        parameter_tk = "token2"; //TSTEP
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token3"; //TSTOP
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token4"; //TSTART
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
        parameter_tk = "token5"; //TMAX
        floatValidator_wSymbol(tokens[parameter_tk], tokens, linha, argumento, generalForm, parameter_tk);
    }
    else
    {
        return "Invalid Transient Analysis display\n";
    }

    return "ok";
}
//BATCH OUTPUT
//.SAVE Lines ?
//.PRINT Lines DC, AC, TRAN, NOISE, or DISTO
std::string parser::print(std::map<std::string, std::string> tokens, int linha, std::string argumento, int qtd_TOKEN)
{
    std::string insideNode = "";
    std::string parameter_tk;
    std::string generalForm = ".PRINT PRTYPE OV1 &ltOV2; ... OV8> ";
    std::string msgErro;

    parameter_tk = "token1";
    if (tokens[parameter_tk] != "DC" && tokens[parameter_tk] != "AC" && tokens[parameter_tk] != "TRAN" && tokens[parameter_tk] != "NOISE" && tokens[parameter_tk] != "DISTO")
    {
        msgErro = "Wrong definition '" + (tokens[parameter_tk]) + "' , did you mean DC | AC | TRAN | NOISE | DISTO ? ";
        errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
    }
    for (int i = 2; i < qtd_TOKEN;)
    {
        if (tokens["token" + i][0] == 'I')
        {
            if (tokens["token" + (i + 1)][0] != 'V')
            {
                msgErro = "Wrong definition '" + (tokens["token" + (i + 1)]) + "' , did you mean I(VXXXXXXX) ? ";
                errorPointer(tokens, linha, argumento, generalForm, parameter_tk, msgErro);
            }
        }
    }

    if (qtd_TOKEN < 3)
    {
        return "Invalid PRINT display\n";
    }

    return "ok";
}
