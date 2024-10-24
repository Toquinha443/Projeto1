#include <iostream>
#include <cstdlib>   // Necessário para std::system

void clearConsole() {
#ifdef _WIN32
  int result = std::system("cls");  // Comando para limpar console no Windows
#else
  int result = std::system("clear"); // Comando para limpar console no Linux/Mac
#endif
  (void)result; // Suprime o aviso de variável não utilizada
}
