#include "dump.h"
#include "tree.h"
#include "read.h"
#include "print.h"
#include "read_ir.h"

#define VERIFY(tree)                            \
        error = tree_verify (&tree);            \
        if (error.code != CORRECT)              \
        {                                       \
            tree_dump (&tree, error);           \
            tree_graph_dump (&tree, error);     \
            return error.code;                  \
        }

const char*     INPUT_NAME              = "../middle.txt";
const char*     OUTPUT_NAME             = "../llvm.ll";

int main ()
{
    Functions funcs = {};
    ReadStr str = {};
    Error error = {};

    FILE* file = fopen (INPUT_NAME, "r");
    read_file (file, &str);
    fclose (file);
    error = read_trees (&funcs, &str);

    IR_Struct ir = {};
    error = ir_ctor (&ir, &funcs);

    error = ir_fill (&ir, &funcs);
    error = ir_dump (&ir);

    funcs_dtor (&funcs);
    error = ir_dtor (&ir);
    return 0;
}
