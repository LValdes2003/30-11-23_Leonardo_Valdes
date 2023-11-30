#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

struct ColorConsole
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false)
{
    string script;

    // Averiguar si el archivo tiene extensión .txt
    const char* fileExtension = strrchr(filename, '.');
    if (fileExtension && strcmp(fileExtension, ".txt") != 0)
    {
        cerr << "Error: El archivo no es un archivo de texto (.txt)." << endl;
        return;
    }

    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            cerr << "Error al abrir el archivo: " << filename << endl;
            perror("fopen"); // Imprime el error
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0)
        {
            buf[c] = 0;
            script.append(buf);
        }
        fclose(f);
        f = nullptr;

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }

        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...)
    {
        cerr << "Error durante la lectura del archivo" << endl;
        if(f)
            fclose(f);
    }
}

void load_script()
{
    char filename[500];
    printf("Archivo: ");
    scanf("%499s", filename);
    load_script(filename, true);
}

// Uso:
int main()
{
    load_script();
    return 0;
}
