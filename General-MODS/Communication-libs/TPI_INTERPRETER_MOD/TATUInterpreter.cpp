#include "TATUInterpreter.h"
#include <stdint.h>

bool TATUInterpreter::parse(unsigned char *string, uint8_t length){
    uint8_t i, j;
    str_hash = 5381;

    switch(string[0]){
        case COMMAND_SET:
            cmd.OBJ.TYPE = TATU_SET;

            if(string[4] == CODE_INFO){
                cmd.OBJ.CODE = TATU_CODE_INFO;
                HASH_DJB(9, length, string, str_hash);
                j = 9; VAR_COPY(j, length, string);
            }
            else if(string[4] == CODE_STATE){
                cmd.OBJ.CODE = TATU_CODE_STATE;
                cmd.OBJ.PIN = ((uint8_t) string[10]) - 49;
                cmd.OBJ.STATE = ((uint8_t) string[12]) - 49;
            }
            else break;

            return true;
        case COMMAND_GET:
            cmd.OBJ.TYPE = TATU_GET;
            
            if(string[4] == CODE_ALL){
                cmd.OBJ.CODE = TATU_CODE_ALL;
            }
            else if(string[4] == CODE_INFO){
                cmd.OBJ.CODE = TATU_CODE_INFO;
                HASH_DJB(9, length, string, str_hash);
                j = 9; VAR_COPY(j, length, string);
            }
            else if(string[4] == CODE_STATE){
                cmd.OBJ.CODE = TATU_CODE_STATE;
                cmd.OBJ.PIN = ((uint8_t) string[9]) - 49;
            }
            else break;

            return true;
        case COMMAND_EDIT:
            cmd.OBJ.TYPE = TATU_EDIT;
            if(string[5] == CODE_INFO){
                cmd.OBJ.CODE = TATU_CODE_INFO;
                HASH_DJB(10, length, string, str_hash);
                j = 10; VAR_COPY(j, length, string);
            }
            else if(string[5] == CODE_STATE){
                cmd.OBJ.CODE = TATU_CODE_STATE;
                cmd.OBJ.PIN = ((uint8_t) string[11]) - 49;
                cmd.OBJ.STATE = ((uint8_t) string[13]) - 49;
            }
            else break;

            return true;
        case COMMAND_POST:
            cmd.OBJ.TYPE = TATU_POST;
            return true;
    }

    return false;
}