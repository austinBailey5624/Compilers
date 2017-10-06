%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int list_type;
%}

%option       noyywrap nounput yylineno
%x            COMMENT PARA PRE OL UL LI

%%

"<h1>"[^<]*"</h1>" {
    /**************************************************************************
     * Matched an HTML H1 header so print it out as a LateX section title.
     * The beginning and ending tags need to be stripped off before the
     * title can be formatted in LateX.
     *************************************************************************/
    yytext[yyleng-5] = 0;
    printf( "\\section{%s} \n", yytext+4 );
}

"<h2>"[^<]*"</h2>" {
      yytext[yyleng-5] = 0;
      printf( "\\subsection{%s} \n", yytext+4);
}

"<h3>"[^<]*"</h3>" {
      yytext[yyleng-5] = 0;
      printf( "\\subsubsection{%s} \n", yytext+4);
}

"<p>"[^<]*"</p>" {
      yytext[yyleng-5] =0;
      printf( "\n", yytext+4);
}

"<pre>"[^<]*"</pre>" {
      yytext[yyleng-6] =0;
      printf( "{%s}", yytext+5);
}

"<ol>" {
		printf( "%% " );
		BEGIN OL;
}

"<p>" {
		printf( "%% " );
		BEGIN PARA;
}

"<ul>" {
		printf( "%% " );
		BEGIN UL;
}

<OL>"<li>"[^<]*"</li>" {
            yytext[yyleng-5] =0;
		printf( "\\enumerate{%s} \n", yytext+4);
}

<UL>"<li>"[^<]*"</li>" {
            yytext[yyleng-5] =0;
		printf( "\\itemize{%s} \n", yytext+4);
}


<PARA>"<small>"[^<]*"</small>" {
      yytext[yyleng-8] =0;
      printf( "\\scriptsize{%s}", yytext+7);
}
<OL>"<small>"[^<]*"</small>" {
      yytext[yyleng-8] =0;
      printf( "\\scriptsize{%s}", yytext+7);
}
<UL>"<small>"[^<]*"</small>" {
      yytext[yyleng-8] =0;
      printf( "\\scriptsize{%s}", yytext+7);
}

<PARA>"<big>"[^<]*"</big>" {
      yytext[yyleng-6] =0;
      printf( "\\Large{%s}", yytext+5);
}
<OL>"<big>"[^<]*"</big>" {
      yytext[yyleng-6] =0;
      printf( "\\Large{%s}", yytext+5);
}
<UL>"<big>"[^<]*"</big>" {
      yytext[yyleng-6] =0;
      printf( "\\Large{%s}", yytext+5);
}

<PARA>"<b>"[^<]*"</b>" {
			printf( "\\textbf{%s}", yytext);
}
<OL>"<b>"[^<]*"</b>" {
			printf( "\\textbf{%s}", yytext);
}
<UL>"<b>"[^<]*"</b>" {
			printf( "\\textbf{%s}", yytext);
}

<PARA>"<i>"[^<]*"</i>" {
			printf( "\\textit{%s}", yytext);
}
<OL>"<i>"[^<]*"</i>" {
			printf( "\\textit{%s}", yytext);
}
<UL>"<i>"[^<]*"</i>" {
			printf( "\\textit{%s}", yytext);
}

<PARA>"<strong>"[^<]*"</strong>" {
			printf( "\\textmd{%s}", yytext);
}
<OL>"<strong>"[^<]*"</strong>" {
			printf( "\\textmd{%s}", yytext);
}
<UL>"<strong>"[^<]*"</strong>" {
			printf( "\\textmd{%s}", yytext);
}

<PARA>"<em>"[^<]*"</em>" {
			printf( "\\emph{%s}", yytext);
}
<OL>"em"[^<]*"</em>" {
			printf( "\\emph{%s}", yytext);
}
<UL>"em"[^<]*"</em>" {
			printf( "\\emph{%s}", yytext);
}

<PARA>"<sup>"[^<]*"</sup>" {
			printf( "\\textsuperscript{%s}", yytext);
}
<OL>"<sup>"[^<]*"</sup>" {
			printf( "\\textsuperscript{%s}", yytext);
}
<UL>"<sup>"[^<]*"</sup>" {
			printf( "\\textsuperscript{%s}", yytext);
}

<PARA>"<sub>"[^<]*"</sub>" {
			printf( "\\textsubscript{%s}", yytext);
}
<OL>"<sub>"[^<]*"</sub>" {
			printf( "\\textsubscript{%s}", yytext);
}
<UL>"<sub>"[^<]*"</sub>" {
			printf( "\\textsubscript{%s}", yytext);
}

"</ol>" {
		printf( "\n" );
		BEGIN 0;
}

"</p>" {
		printf( "\n" );
		BEGIN 0;
}

"<!--" {
    /**************************************************************************
     * Matched an HTML comment so print it out as a LateX comment. The
     * beginning and ending tags are stripped off before the LateX comment
     * is emitted.
     *************************************************************************/
    printf( "%% " );
    BEGIN COMMENT;
}


[ \t\n\r]+ {
    /**************************************************************************
     * Matched some whitespace that is not inside of an HTML tag. We
     * just ignore the whitespace.
     *************************************************************************/
}

. {
    /**************************************************************************
     * Matched something that we did not expect to see. Issue an error and
     * exit the program with a failure message.
     *************************************************************************/
    fprintf( stderr, "Unexpected input at line %d: '%s'\n", yylineno, yytext );
    exit( 1 );
}

<COMMENT>"-->" {
    /**************************************************************************
     * Matched an HTML end comment while parsing an HTML comment. Print out
     * a new line and resume normal parsing.
     *************************************************************************/
    printf( "\n" );
    BEGIN 0;
}

<COMMENT>[\n](\r)? {
    /**************************************************************************
     * Matched a newline and possible carriage return while parsing an HTML
     * comment. Print out a new line making sure to mark the next line as a
     * comment as well.
     *************************************************************************/
    printf( "\n%% " );
}

<COMMENT>[ \t] {
    /**************************************************************************
     * Matched some white space while parsing an HTML comment. Print out
     * the white space as is.
     *************************************************************************/
    printf( "%s", yytext );
}

<COMMENT>. {
    /**************************************************************************
     * Matched any other text while parsing an HTML comment. Print out
     * the text as is.
     *************************************************************************/
    printf( "%s", yytext );
}

%%

/**************************************************************************
 * The main function for the HTML to LateX converter. Here we do three
 * things:
 *  1. Print out the LateX document header.
 *  2. Invoke the lexer to print out the LateX document
 *  3. Print out the LateX footer.
 *************************************************************************/
int main( int argc, const char *argv[] ) {
    printf( "\\documentclass[12pt]{article}\n" );
    printf( "\\usepackage{fixltx2e}\n" );
    printf( "\n" );
    printf( "\\setlength{\\parindent}{0.0in}\n" );
    printf( "\\setlength{\\parskip}{0.125in}\n" );
    printf( "\n\n" );
    printf( "\\begin{document}\n" );
    yylex();
    printf( "\\end{document}\n" );
    return 0;
}
