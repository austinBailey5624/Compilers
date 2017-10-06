%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Define the tokens that you want to return from your lex as follows
#define ID 256
#define INTVAL 257
#define OPENPARENTHESES 258
#define CLOSEPARENTHESES 259
#define OPENCURLYBRACE 260
#define CLOSECURLYBRACE 261
#define OPENSQUAREBRACKET 262
#define CLOSESQUAREBRACKET 263
#define COMMA 264
#define SEMICOLON 265
#define SPACE 266
#define DBLVAL 267
#define CHARVAL 268
#define FLTVAL 269
#define STRVAL 270
#define VOID 271
#define SHORT 272
#define LONG 273
#define DOUBLE 274
#define CHAR 275
#define INT 276
#define FLOAT 277
#define EQ 278
#define LE 279
#define ADD 280
#define DIV 281
#define AND 282
#define BITXOR 283
#define LSH 284
#define SETADD 285
#define SETDIV 256
#define SETAND 287
#define SETRSH 288
#define NE 289
#define GT 290
#define SUB 291
#define MOD 292
#define BITOR 293
#define NOT 294
#define RSH 295
#define SETSUB 296
#define SETMOD 297
#define SETXOR 298
#define GE 299
#define LT 300
#define MUL 301
#define OR 302
#define BITAND 303
#define COM 304
#define SET 305
#define SETMUL 306
#define SETOR 307
#define SETLSH 308
#define RETURN 309
#define WHILE 310
#define SWITCH 311
#define DEFAULT 312
#define ELSE 313
#define BREAK 314
#define DO 315
#define FOR 316
#define CASE 317
#define IF 318
#define CONTINUE 319
#define GOTO 320
#define UNSIGNED 321
#define STRUCT 322
#define CONST 323
#define EXTERN 324
#define REGISTER 325
#define TYPEDEF 326
#define UNION 327
#define STATIC 328
#define AUTO 329
#define SIZEOF 330
%}

%option noyywrap nounput yylineno
%x COMMENT COMMENT2 PREPROC

ID [a-zA-Z][a-zA-Z0-9_]*
INTVAL [0-9]+|"0x"[0-9]+|"0"[0-9]+
CHARVAL \'(\\.|[^'])*\'
STRVAL \"(\\.|[^"])*\"
DBLVAL [0-9]+"."[0-9]+
FLTVAL [0-9]+"."[0-9]+f

%%
"//" {
    /****************************************
    * Matching with Single line comments in our
    * C code
    ******************************************/
    BEGIN COMMENT;
}

"#" {
    BEGIN PREPROC;
}

<PREPROC>[a-zA-Z0-9_<>\"\. ]+ {

}

<PREPROC>\n {
    printf("PREPROC\n");
    BEGIN 0;
}

"/*" {
    BEGIN COMMENT2;
}

<COMMENT2>"*/" {
    BEGIN 0;
}

<COMMENT>[\n](\r)? {
    /****************************************
    * A new line indicates end of a single
    * line comment in C
    ****************************************/

    BEGIN 0;
}

<COMMENT>[ \t] {
    /****************************************
    * Lexer ignores the comments section
    * by Ignoring anything inside a comment
    ****************************************/
}



<COMMENT>. {
}

[ \t\n\r]* {

}

"(" {
    printf("(\n");
    return OPENPARENTHESES;
}

")" {
    printf(")\n");
    return CLOSEPARENTHESES;
}

"{" {
    printf("{\n");
    return OPENCURLYBRACE;
}

"}" {
    printf("}\n");
    return CLOSECURLYBRACE;
}

"[" {
    printf("[\n");
    return OPENSQUAREBRACKET;
}

"]" {
    printf("]\n");
    return CLOSESQUAREBRACKET;
}

"," {
    printf(",\n");
    return COMMA;
}

";" {
    printf(";\n");
    return SEMICOLON;
}

"void" {
    printf("VOID\n");
    return VOID;
}

"short" {
    printf("SHORT\n");
    return SHORT;
}

"long" {
    printf("LONG\n");
    return LONG;
}

"double" {
    printf("DOUBLE\n");
    return DOUBLE;
}

"char" {
    printf("CHAR\n");
    return CHAR;
}

"int" {
    printf("INT\n");
    return INT;
}

"float" {
    printf("FLOAT\n");
    return FLOAT;
}

"==" {
    printf("EQ\n");
    return EQ;
}

"<=" {
    printf("LE\n");
    return LE;
}

"+" {
    printf("ADD\n");
    return ADD;
}

"/" {
    printf("DIV\n");
    return DIV;
}

"&&" {
    printf("AND\n");
    return AND;
}

"^" {
    printf("BITXOR\n");
    return BITXOR;
}

"<<" {
    printf("LSH\n");
    return LSH;
}

"+=" {
    printf("SETADD\n");
    return SETADD;
}

"/=" {
    printf("SETDIV\n");
    return SETDIV;
}

"&=" {
    printf("SETAND\n");
    return SETAND;
}

">>=" {
    printf("SETRSH\n");
    return SETRSH;
}

"!=" {
    printf("NE\n");
    return NE;
}

">" {
    printf("GT\n");
    return GT;
}

"-" {
    printf("SUB\n");
    return SUB;
}

"%" {
    printf("MOD\n");
    return MOD;
}

"|" {
    printf("BITOR\n");
    return BITOR;
}

"!" {
    printf("NOT\n");
    return NOT;
}

">>" {
    printf("RSH\n");
    return RSH;
}

"-=" {
    printf("SETSUB\n");
    return SETSUB;
}

"%=" {
    printf("SETMOD\n");
    return SETMOD;
}

"^=" {
    printf("SETXOR\n");
    return SETXOR;
}

">=" {
    printf("GE\n");
    return GE;
}

"<" {
    printf("LT\n");
    return LT;
}

"*" {
    printf("MUL\n");
    return MUL;
}

"||" {
    printf("OR\n");
    return OR;
}

"&" {
    printf("BITAND\n");
    return BITAND;
}

"~" {
    printf("COM\n");
    return COM;
}

"=" {
    printf("SET\n");
    return SET;
}

"*=" {
    printf("SETMUL\n");
    return SETMUL;
}

"|=" {
    printf("SETOR\n");
    return SETOR;
}

"<<=" {
    printf("SETLSH\n");
    return SETLSH;
}

"return" {
    printf("RETURN\n");
    return RETURN;
}

"while" {
    printf("WHILE\n");
    return WHILE;
}

"switch" {
    printf("SWITCH\n");
    return SWITCH;
}

"default" {
    printf("DEFAULT\n");
    return DEFAULT;
}

"else" {
    printf("ELSE\n");
    return ELSE;
}

"break" {
    printf("BREAK\n");
    return BREAK;
}

"do" {
    printf("DO\n");
    return DO;
}

"for" {
    printf("FOR\n");
    return FOR;
}

"case" {
    printf("CASE\n");
    return CASE;
}

"if" {
    printf("IF\n");
    return IF;
}

"continue" {
    printf("CONTINUE\n");
    return CONTINUE;
}

"goto" {
    printf("GOTO\n");
    return GOTO;
}

"unsigned" {
    printf("UNSIGNED\n");
    return UNSIGNED;
}

"struct" {
    printf("STRUCT\n");
    return STRUCT;
}

"const" {
    printf("CONST\n");
    return CONST;
}

"extern" {
    printf("EXTERN\n");
    return EXTERN;
}

"register" {
    printf("REGISTER\n");
    return REGISTER;
}

"typedef" {
    printf("TYPEDEF\n");
    return TYPEDEF;
}

"union" {
    printf("UNION\n");
    return UNION;
}

"static" {
    printf("STATIC\n");
    return STATIC;
}

"auto" {
    printf("AUTO\n");
    return AUTO;
}

"sizeof" {
    printf("SIZEOF\n");
    return(SIZEOF);
}


{ID} {
    /**************************************
    * If an identifier is matched, then
    * print ID and return a token ID
    **************************************/

    printf("ID\n");
    return ID;
}

{INTVAL} {
    printf("INTVAL\n");
    return INTVAL;
}

{CHARVAL} {
    printf("CHARVAL\n");
    return CHARVAL;
}

{STRVAL} {
    printf("STRVAL\n");
    return STRVAL;
}

{DBLVAL} {
    printf("DBLVAL\n");
    return DBLVAL;
}

{FLTVAL} {
    printf("FLTVAL\n");
    return FLTVAL;
}
%%
int main(int argc, const char* argv[]) {

    int exit2 = 0;
    int run;
    while(exit2==0)
    {
        if (yylex() ==0)
        {
            exit2=1;
        }
    }

    return 0;
}
