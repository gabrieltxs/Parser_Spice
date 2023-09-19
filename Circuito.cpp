#include "Circuito.h"
#include "windows.h"

// Destructor for the Circuito class
Circuito::~Circuito()
{
}

// Constructor for the Circuito class
Circuito::Circuito()
{
}

// Function to parse a circuit based on the input arguments
std::string Circuito::parseCircuit(std::map<std::string, std::string> argumento, int linha, std::string argC, int qtd_TOKEN)
{
    parser parserOBJ;
    std::string status = "ok";
    std::string token0 = argumento["token0"];

    // Check the type of the first token and call the corresponding parser function
    if (token0[0] == 'R')
        status = parserOBJ.resistor(argumento, linha, argC, qtd_TOKEN);
    else if (token0[0] == 'C')
        status = parserOBJ.capacitor(argumento, linha, argC, qtd_TOKEN);
    else if (token0[0] == 'L')
        status = parserOBJ.inductor(argumento, linha, argC, qtd_TOKEN);
    else if (token0[0] == 'V' || token0[0] == 'I')
        status = parserOBJ.sourceVI(argumento, linha, argC, qtd_TOKEN); //Independent Sources(Voltage - V) (Current - I)
    else if (token0[0] == 'G' || token0[0] == 'E')
        status = parserOBJ.sourceGE(argumento, linha, argC, qtd_TOKEN); //Linear Voltage-Controlled Current Sources(G)
                                                                        //Linear Voltage-Controlled Voltage Sources(E)
    else if (token0[0] == 'F' || token0[0] == 'H')
        status = parserOBJ.sourceFH(argumento, linha, argC, qtd_TOKEN); //Linear Current-Controlled Current Sources(F)
                                                                        //Linear Current-Controlled Voltage Sources(H)
    else if (token0[0] == 'D')
        status = parserOBJ.junctionDiode(argumento, linha, argC, qtd_TOKEN);
    else if (token0[0] == 'Q')
        status = parserOBJ.bjt(argumento, linha, argC, qtd_TOKEN);
    else if (token0[0] == 'J')
        status = parserOBJ.jfet(argumento, linha, argC, qtd_TOKEN);
    else if (token0[0] == 'M')
        status = parserOBJ.mosfet(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".SUBCKT")
        status = parserOBJ.subckt(argumento, linha, argC, qtd_TOKEN, &stackSUBCKT);
    else if (token0 == ".ENDS")
        status = parserOBJ.ends(argumento, linha, argC, qtd_TOKEN, &stackSUBCKT);
    else if (token0[0] == 'X')
        status = parserOBJ.subcktCALL(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".END")
        status = parserOBJ.end(argumento, linha, argC, qtd_TOKEN, &cktChaveFecha);
    else if (token0 == ".OPTIONS")
        status = parserOBJ.options(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".NODESET")
        status = parserOBJ.nodeset(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".IC")
        status = parserOBJ.ic(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".AC")
        status = parserOBJ.ac(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".DC")
        status = parserOBJ.dc(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".PZ")
        status = parserOBJ.pz(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".SENS")
        status = parserOBJ.sens(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".TF")
        status = parserOBJ.tf(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".TRAN")
        status = parserOBJ.tran(argumento, linha, argC, qtd_TOKEN);
    else if (token0 == ".PRINT")
        status = parserOBJ.print(argumento, linha, argC, qtd_TOKEN);
    else if (token0[0] == '*' || qtd_TOKEN == 0 || token0 == ".SAVE")
    { /* DO NOTHING */
    }

    // If none of the known tokens match, set status to indicate an error
    else
    {
        status = "(path_UNDEFINED) line " + std::to_string(linha + 1) + ":\n" + argC + "\n^\n";
    }

    return status;
}

// Function to set the line from the circuit input
void Circuito::setLine_from_ckt(std::string argumento)
{
    oDisplay_aux = argumento;

    // Loop through the characters in the input string
    for (int lcount = 0; lcount < oDisplay_aux.length(); lcount++)
    {
        if (oDisplay_aux[lcount] == '=' || oDisplay_aux[lcount] == ',')
        {
            tokens[token_NUM + std::to_string(token_NUM_var)] = oDisplay_aux[lcount];
            token_NUM_var++;
            oDisplayRegistry = "";
            lcount++;
        }

    AQUI:
        if (oDisplay_aux[lcount] != ' ' && oDisplay_aux[lcount] != '\t')
        {
            // Continue collecting characters until a space or tab is encountered
            while (((oDisplay_aux[lcount] != ' ' && oDisplay_aux[lcount] != '\t') && (lcount) < oDisplay_aux.length()))
            {
                // Handle parentheses separately
                if (oDisplay_aux[lcount] == '(' && token_NUM_var > 0)
                {
                    parentheses.push(lcount);
                    lcount++;
                    if (oDisplayRegistry == "")
                    {
                        goto AQUI;
                    }
                    else
                    {
                        goto fimWhile;
                    }
                }
                else if (oDisplay_aux[lcount] == ')' && token_NUM_var > 0)
                {
                    if (parentheses.empty())
                    {
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 12); // Red text color
                        std::string parserError = "parserError:";
                        std::cout << parserError;
                        SetConsoleTextAttribute(hConsole, 7); // Back to white text color
                        throw std::string("line " + std::to_string(linha + 1) +
                                          " column " + std::to_string(oDisplay_aux.find(')') + 1) +
                                          ". Invalid argument:\n" + oDisplay_aux + "\n\nerror on parentheses syntax.");
                    }
                    parentheses.pop();
                    lcount++;
                    if (oDisplayRegistry == "")
                    {
                        goto AQUI;
                    }
                    else
                    {
                        goto fimWhile;
                    }
                }
                // Handle '=' and ',' characters
                else if (oDisplay_aux[lcount] == '=' || oDisplay_aux[lcount] == ',')
                {
                    if (oDisplayRegistry != "")
                    {
                        tokens[token_NUM + std::to_string(token_NUM_var)] = oDisplayRegistry;
                        token_NUM_var++;
                        oDisplayRegistry = "";
                    }
                    else
                    {
                        tokens[token_NUM + std::to_string(token_NUM_var)] = oDisplay_aux[lcount];
                        token_NUM_var++;
                        oDisplayRegistry = "";
                        lcount++;
                        goto AQUI;
                    }
                }
                // Collect characters for other cases
                else
                {
                    oDisplayRegistry += oDisplay_aux[lcount];
                    lcount++;
                }
            }
        fimWhile:
            tokens[token_NUM + std::to_string(token_NUM_var)] = oDisplayRegistry;
            token_NUM_var++;
            oDisplayRegistry = "";
            blockToken = true;
        }
    }

    // Check for unmatched parentheses
    if (!parentheses.empty())
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12); // Red text color
        std::cout << "parserError: ";
        SetConsoleTextAttribute(hConsole, 7); // Back to white text color
        throw std::string("line " + std::to_string(linha + 1) +
                          " column " + std::to_string(oDisplay_aux.find('(') + 1) +
                          ". Invalid argument:\n" + oDisplay_aux + "\n\nerror on parentheses syntax.");
    }

    // Call the parseCircuit function and handle any errors
    if (parseCircuit(tokens, linha, oDisplay_aux, token_NUM_var) != "ok")
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12); // Red text color
        std::cout << "parserError:";
        SetConsoleTextAttribute(hConsole, 7); // Back to white text color
        std::cout << parseCircuit(tokens, linha, oDisplay_aux, token_NUM_var);
    }

    token_NUM_var = 0;
    linha++;
    tokens.clear();
}

// Function to run the circuit from a file
void Circuito::runFile(std::string filename)
{
    this->filename = filename;
    std::string oDisplay_input = "";
    std::ifstream openedFile(this->filename);

    getline(openedFile, oDisplay_input); // Read and ignore the first line (TITLE)
    system("cls"); // Clear the console screen

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 6); // Yellow text color
    std::cout << oDisplay_input << std::endl;
    SetConsoleTextAttribute(hConsole, 7); // Back to white text color

    getline(openedFile, oDisplay_input);

    try
    {
        // Read and process lines from the file
        while (!openedFile.fail())
        {
            this->setLine_from_ckt(oDisplay_input);
            getline(openedFile, oDisplay_input);
        }

        // Check if the circuit is missing an ".END" statement
        if (cktChaveFecha)
        {
            SetConsoleTextAttribute(hConsole, 12); // Red text color
            std::cout << "parseError:";
            SetConsoleTextAttribute(hConsole, 7); // Back to white text color
            std::cout << "Missing argument '.END'." << std::endl;
            SetConsoleTextAttribute(hConsole, 9); // Blue text color
            std::cout << "\nYou must end the circuit.";
            SetConsoleTextAttribute(hConsole, 7); // Back to white text color
        }
    }
    catch (std::string msg)
    {
        std::cout << msg << std::endl;
    }

    openedFile.close();
}
