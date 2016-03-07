#include <type.h>
#include <parser.h>
#include <compiler.h>

using namespace Luna;

typedef void (*AssembledFunction)();

int main(int argc, char** argv){
    if (argc < 2) {
    	printf("No input file.");
    	return 1;
    }
    Scope* global = new Scope();
    Luna::Internal::InitOnce(global);
    FILE* fin = fopen(argv[1], "r");
    Function* script = (new Parser(fin))->Parse(global);
    fclose(fin);
    Compiler::Compile(script);
    reinterpret_cast<AssembledFunction>(script->GetCompoundFunction())();
    return 0;
}