#include "mpc.h"

int main(int argc, char** argv) {
/* Build a new parser, 'Adjective' to recognise descriptions */
    mpc_parser_t* Numeral = mpc_new("numeral");
    mpc_parser_t* Decpoint = mpc_new("decpoint");
    mpc_parser_t* Block = mpc_new("block");
    mpc_parser_t* Decimal = mpc_new("decimal");

    mpca_lang(MPC_LANG_DEFAULT,
        "
            numeral  : \'0\',\'1\', \'2\',\'3\', \'4\',\'5\', \'6\',\'7\', \'8\',\'9\'; \
            decpoint : \'.\';                                                           \
            block    : <numeral>+;                                                      \
            decimal  : <block><decpoint><block>;                                        \
        ",
        Numeral, Decpoint, Block, Decimal);

    /* do some parsing here... */

    mpc_cleanup(4, Numeral, Decpoint, Block, Decimal);

    return 0;

}
