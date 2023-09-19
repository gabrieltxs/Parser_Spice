//============================================================================//
// The MIT License (MIT)
// Copyright (c) GABRIEL TEIXEIRA ANDRADE SOUSA
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//============================================================================//

#include <iostream>
#include <fstream>
#include <chrono>
#include <cxxopts.hpp> // Inclua a biblioteca cxxopts para análise de argumentos de linha de comando
#include "Circuito.h"
#include "windows.h"

int main(int argc, char* argv[])
{
    try
    {
        // Crie uma instância do analisador cxxopts
        cxxopts::Options options("Simulador de Circuitos", "Um programa de simulação de circuitos");

        // Adicione uma opção de linha de comando para especificar o caminho do arquivo de entrada
        options.add_options()
            ("f,filename", "Caminho do arquivo de entrada", cxxopts::value<std::string>());

        // Analise os argumentos de linha de comando
        auto args = options.parse(argc, argv);

        // Verifique se a opção "filename" foi fornecida
        if (args.count("filename") == 0)
        {
            std::cerr << "Erro: Caminho do arquivo de entrada está faltando. Use a opção -f ou --filename para especificar o arquivo de entrada." << std::endl;
            return 1; // Retorne um código de erro
        }

        // Obtenha o nome do arquivo de entrada a partir dos argumentos analisados
        std::string filename = args["filename"].as<std::string>();

        // Crie uma instância da classe Circuito
        Circuito mainCKT;

        // Execute a simulação do circuito com o arquivo de entrada especificado
        mainCKT.runFile(filename);

        // O restante do seu código pode permanecer inalterado

        return 0;
    }
    catch (const cxxopts::OptionException& e)
    {
        std::cerr << "Erro ao analisar os argumentos de linha de comando: " << e.what() << std::endl;
        return 1;
    }
}
