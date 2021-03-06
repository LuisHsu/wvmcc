#include <adt/Token.h>

static void free_Token(Token** token){
    if((*token)->type == Token_Identifier){
        free((void*)((*token)->value.identifier));
    }else if((*token)->type == Token_String){
        free((void*)((*token)->value.string));
    }
    free(*token);
    *token = NULL;
}

Token* new_UnknownToken(){
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = Token_Unknown;
    token->free = free_Token;
    return token;
}

Token* new_KeywordToken(const Keyword keyword){
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = Token_Keyword;
    token->value.keyword = keyword;
    token->free = free_Token;
    return token;
}

Token* new_IdentifierToken(const char *identifier){
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = Token_Identifier;
    token->value.identifier = identifier;
    token->free = free_Token;
    return token;
}
Token* new_IntegerToken(const unsigned long long int value, const unsigned int byteSize, const _Bool isUnsigned){
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = Token_Integer;
    token->value.integer = value;
    token->free = free_Token;
    token->byteSize = byteSize;
    token->isUnsigned = isUnsigned;
    return token;
}
Token* new_FloatingToken(const double value, const unsigned int byteSize){
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = Token_Floating;
    token->value.floating = value;
    token->free = free_Token;
    token->byteSize = byteSize;
    return token;
}
Token* new_CharacterToken(const uint32_t value, const unsigned int byteSize){
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = Token_Character;
    token->value.character = value;
    token->free = free_Token;
    token->byteSize = byteSize;
    return token;
}
Token* new_StringToken(const uint32_t *string, const unsigned int byteSize){
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = Token_String;
    token->value.string = string;
    token->free = free_Token;
    token->byteSize = byteSize;
    return token;
}
Token* new_PunctuatorToken(const Punctuator punctuator){
    Token* token = (Token*) malloc(sizeof(Token));
    token->type = Token_Punctuator;
    token->value.punctuator = punctuator;
    token->free = free_Token;
    return token;
}