#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_VARIABLES 100

typedef struct
{
    char nom[20];
    char type[20]; // "constante" ou "variable" ou "program" ou "array"
} Variable;

Variable variables[MAX_VARIABLES]; // Tableau de variables
int nombre_variables = 0;          // Nombre de variables actuellement enregistr�es

typedef enum
{
    ID_TOKEN,
    PROGRAM_TOKEN,
    CONST_TOKEN,
    VAR_TOKEN,
    OF_TOKEN,
    ARRAY_TOKEN,
    BEGIN_TOKEN,
    END_TOKEN,
    IF_TOKEN,
    ELSE_TOKEN,
    THEN_TOKEN,
    WHILE_TOKEN,
    DO_TOKEN,
    FOR_TOKEN,
    FCT_TOKEN,
    READ_TOKEN,
    WRITE_TOKEN,
    TO_TOKEN,
    PV_TOKEN,
    PT_TOKEN,
    PPT_TOKEN,
    PLUS_TOKEN,
    MOINS_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    VIR_TOKEN,
    AFF_TOKEN,
    INF_TOKEN,
    INFEG_TOKEN,
    SUP_TOKEN,
    SUPEG_TOKEN,
    DIFF_TOKEN,
    PO_TOKEN,
    PF_TOKEN,
    CO_TOKEN,
    CF_TOKEN,
    INTEGER_TOKEN,
    REAL_TOKEN,
    BOOLEAN_TOKEN,
    STRING_TOKEN,
    CHAR_TOKEN,
    FIN_TOKEN,
    NUM_TOKEN,
    ERREUR_TOKEN,
    EOF_TOKEN,
    EG_TOKEN,
    PROC_TOKEN,
    REP_TOKEN,
    UN_TOKEN,
} CODES_LEX;

// erreur types
typedef enum
{
    ID_ERR,
    PROGRAM_ERR,
    CONST_ERR,
    VAR_ERR,
    OF_ERR,
    ARRAY_ERR,
    BEGIN_ERR,
    END_ERR,
    IF_ERR,
    REAL_ERR,
    BOOLEAN_ERR,
    ELSE_ERR,
    THEN_ERR,
    WHILE_ERR,
    FCT_ERR,
    PARAM_TYPE_ERR,
    DO_ERR,
    FOR_ERR,
    READ_ERR,
    WRITE_ERR,
    TO_ERR,
    PV_ERR,
    PT_ERR,
    PPT_ERR,
    PLUS_ERR,
    MOINS_ERR,
    MULT_ERR,
    DIV_ERR,
    VIR_ERR,
    AFF_ERR,
    INF_ERR,
    INFEG_ERR,
    SUP_ERR,
    SUPEG_ERR,
    DIFF_ERR,
    PO_ERR,
    PF_ERR,
    CO_ERR,
    CF_ERR,
    INTEGER_ERR,
    STRING_ERR,
    CHAR_ERR,
    FIN_ERR,
    NUM_ERR,
    ERREUR_ERR,
    EOF_ERR,
    EG_ERR,
    CONST_VAR_BEGIN_ERR,
    VAR_BEGIN_ERR,
    PROC_ERR,
} CODES_ERR;

typedef struct
{
    CODES_LEX CODE;
    char NOM[20];
} TSym_Cour;

TSym_Cour SYM_COUR;

FILE *fichier;

char Car_Cour; // caract�re courant

// functions declaration
void VARS();
void INSTS();
void INST();
void AFFEC();
void SI();
void TANTQUE();
void ECRIRE();
void LIRE();
void EXPR();
void TERM();
void FACT();
void MULOP();
void ADDOP();
void RELOP();
void COND();
void Lire_Car();
void Erreur(CODES_ERR code);
void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR);
void PROGRAM();
void BLOCK();
void CONSTS();
void Sym_Suiv();
void lire_mot();
void lire_nombre();
void rule_2();
void POUR();
void PROC();
void REP();
// functions definition

void lire_mot()
{
    char mot[20];
    int indice = 0;

    // Lecture du premier caract�re (lettre)
    mot[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des caract�res suivants (lettres ou chiffres)
    while (isalpha(Car_Cour) || isdigit(Car_Cour))
    {
        mot[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caract�re de fin de cha�ne
    mot[indice] = '\0';

    strcpy(SYM_COUR.NOM, mot);
    // V�rifier si le mot est un mot-cl�
    if (strcasecmp(mot, "program") == 0)
    {
        SYM_COUR.CODE = PROGRAM_TOKEN;
    }
    else if (strcasecmp(mot, "const") == 0)
    {
        SYM_COUR.CODE = CONST_TOKEN;
    }
    else if (strcasecmp(mot, "var") == 0)
    {
        SYM_COUR.CODE = VAR_TOKEN;
    }
    else if (strcasecmp(mot, "begin") == 0)
    {
        SYM_COUR.CODE = BEGIN_TOKEN;
    }
    else if (strcasecmp(mot, "end") == 0)
    {
        SYM_COUR.CODE = END_TOKEN;
    }
    else if (strcasecmp(mot, "if") == 0)
    {
        SYM_COUR.CODE = IF_TOKEN;
    }
    else if (strcasecmp(mot, "else") == 0)
    {
        SYM_COUR.CODE = ELSE_TOKEN;
    }
    else if (strcasecmp(mot, "then") == 0)
    {
        SYM_COUR.CODE = THEN_TOKEN;
    }
    else if (strcasecmp(mot, "while") == 0)
    {
        SYM_COUR.CODE = WHILE_TOKEN;
    }
    else if (strcasecmp(mot, "do") == 0)
    {
        SYM_COUR.CODE = DO_TOKEN;
    }
    else if (strcasecmp(mot, "read") == 0)
    {
        SYM_COUR.CODE = READ_TOKEN;
    }
    else if (strcasecmp(mot, "write") == 0)
    {
        SYM_COUR.CODE = WRITE_TOKEN;
    }
    else if (strcasecmp(mot, "of") == 0)
    {
        SYM_COUR.CODE = OF_TOKEN;
    }
    else if (strcasecmp(mot, "array") == 0)
    {
        SYM_COUR.CODE = ARRAY_TOKEN;
    }
    else if (strcasecmp(mot, "integer") == 0)
    {
        SYM_COUR.CODE = INTEGER_TOKEN;
    }
    else if (strcasecmp(mot, "string") == 0)
    {
        SYM_COUR.CODE = STRING_TOKEN;
    }
    else if (strcasecmp(mot, "char") == 0)
    {
        SYM_COUR.CODE = CHAR_TOKEN;
    }
    else if (strcasecmp(mot, "real") == 0)
    {
        SYM_COUR.CODE = REAL_TOKEN;
    }
    else if (strcasecmp(mot, "boolean") == 0)
    {
        SYM_COUR.CODE = BOOLEAN_TOKEN;
    }
    else if (strcasecmp(mot, "for") == 0)
    {
        SYM_COUR.CODE = FOR_TOKEN;
    }
    else if (strcasecmp(mot, "to") == 0)
    {
        SYM_COUR.CODE = TO_TOKEN;
    }
    else if (strcasecmp(mot, "function") == 0)
    {
        SYM_COUR.CODE = FCT_TOKEN;
    }
    else if (strcasecmp(mot, "procedure") == 0)
    {
        SYM_COUR.CODE = PROC_TOKEN;
    }
    else if (strcasecmp(mot, "repeat") == 0)
    {
        SYM_COUR.CODE = REP_TOKEN;
    }
    else if (strcasecmp(mot, "until") == 0)
    {
        SYM_COUR.CODE = UN_TOKEN;
    }

    else
    {
        // If it's not a keyword, it's an identifier
        SYM_COUR.CODE = ID_TOKEN;
        rule_5(SYM_COUR.NOM);
    }

    // Stockage du mot dans le jeton
    strcpy(SYM_COUR.NOM, mot);
}

void lire_nombre()
{
    char nombre[11];
    int indice = 0;

    // Lecture du premier chiffre
    nombre[indice++] = Car_Cour;
    Lire_Car();

    // Lecture des chiffres suivants
    while (isdigit(Car_Cour))
    {
        nombre[indice++] = Car_Cour;
        Lire_Car();
    }

    // Ajout du caract�re de fin de cha�ne
    nombre[indice] = '\0';

    // Stockage du nombre dans le jeton
    SYM_COUR.CODE = NUM_TOKEN;
    strcpy(SYM_COUR.NOM, nombre);
}

void Sym_Suiv()
{
    while (Car_Cour == ' ' || Car_Cour == '\n' || Car_Cour == '\t')
    {
        Lire_Car();
    }
    if (Car_Cour == '{')
    {
        Lire_Car();
        if (Car_Cour == '*')
        {
            int r = 0;
            while (r == 0 && Car_Cour != EOF)
            {
                Lire_Car();
                if (Car_Cour == '*')
                {
                    Lire_Car();
                    if (Car_Cour == '}')
                    {
                        r = 1;
                    }
                }
            }
            if (r == 1)
            {
                Lire_Car();
                Sym_Suiv();
                return;
            }
            else
            {
                printf("ERREUR: Commentaire non ferm�\n");
            }
        }
    }
    if (isalpha(Car_Cour))
    {
        lire_mot();
    }
    else if (isdigit(Car_Cour))
    {
        lire_nombre();
    }
    else
    {
        switch (Car_Cour)
        {
        case ';':
            SYM_COUR.CODE = PV_TOKEN;
            Lire_Car();
            break;

        case '+':
            SYM_COUR.CODE = PLUS_TOKEN;
            Lire_Car();
            break;

        case ']':
            SYM_COUR.CODE = CF_TOKEN;
            SYM_COUR.NOM[0] = Car_Cour;
            SYM_COUR.NOM[1] = '\0';
            Lire_Car();
            break;

        case '[':
            SYM_COUR.CODE = CO_TOKEN;
            SYM_COUR.NOM[0] = Car_Cour;
            SYM_COUR.NOM[1] = '\0';
            Lire_Car();
            break;

        case '-':
            SYM_COUR.CODE = MOINS_TOKEN;
            Lire_Car();
            break;

        case '*':
            SYM_COUR.CODE = MULT_TOKEN;
            Lire_Car();
            break;

        case '/':
            SYM_COUR.CODE = DIV_TOKEN;
            Lire_Car();
            break;

        case ',':
            SYM_COUR.CODE = VIR_TOKEN;
            Lire_Car();
            break;

        case ':':
            SYM_COUR.CODE = PPT_TOKEN;
            SYM_COUR.NOM[0] = Car_Cour;
            SYM_COUR.NOM[1] = '\0';
            Lire_Car();
            if (Car_Cour == '=')
            {
                SYM_COUR.CODE = AFF_TOKEN;
                SYM_COUR.NOM[0] = Car_Cour;
                SYM_COUR.NOM[1] = '\0';
                Lire_Car();
            }
            /*else {
                SYM_COUR.CODE = ERREUR_TOKEN;
            }*/
            break;

        case '<':
            Lire_Car();
            if (Car_Cour == '=')
            {
                SYM_COUR.CODE = INFEG_TOKEN;
                Lire_Car();
            }
            else if (Car_Cour == '>')
            {
                SYM_COUR.CODE = DIFF_TOKEN;
                Lire_Car();
            }
            else
            {
                SYM_COUR.CODE = INF_TOKEN;
            }
            break;

        case '>':
            Lire_Car();
            if (Car_Cour == '=')
            {
                SYM_COUR.CODE = SUPEG_TOKEN;
                Lire_Car();
            }
            else
            {
                SYM_COUR.CODE = SUP_TOKEN;
            }
            break;

        case '(':
            SYM_COUR.CODE = PO_TOKEN;
            Lire_Car();
            break;
        case '=':
            SYM_COUR.CODE = EG_TOKEN;
            Lire_Car();
            break;

        case ')':
            SYM_COUR.CODE = PF_TOKEN;
            Lire_Car();
            break;

        case '.':
            SYM_COUR.CODE = PT_TOKEN;
            Lire_Car();
            break;

        case EOF:
            SYM_COUR.CODE = FIN_TOKEN;
            break;

        default:
            SYM_COUR.CODE = ERREUR_TOKEN;
            Lire_Car();
        }
    }
}

void Lire_Car()
{
    Car_Cour = fgetc(fichier);
}

void Erreur(CODES_ERR code)
{
    printf("Erreur: %d\n", code);
    printf("Current Token: %d\n", SYM_COUR.CODE);
    printf("Current Lexeme: %s\n", SYM_COUR.NOM);
    exit(EXIT_FAILURE);
}

void Test_Symbole(CODES_LEX cl, CODES_ERR COD_ERR)
{
    if (SYM_COUR.CODE == cl)
    {
        Sym_Suiv();
    }
    else
        Erreur(COD_ERR);
}

void PROGRAM()
{
    Test_Symbole(PROGRAM_TOKEN, PROGRAM_ERR);
    if (SYM_COUR.CODE == ID_TOKEN)
    {
        strcpy(variables[nombre_variables].nom, SYM_COUR.NOM);
        strcpy(variables[nombre_variables].type, "PROGRAM");
        nombre_variables++;
        Sym_Suiv();
    }
    Test_Symbole(PV_TOKEN, PV_ERR);
    printf("LIGNE PROGRAMME TESTEE AVEC SUCCES\n");
    BLOCK();

    // Test_Symbole(PT_TOKEN, PT_ERR);
    //  Check for the dot after BLOCK
    if (SYM_COUR.CODE == PT_TOKEN)
    {
        Sym_Suiv(); // Consume the dot
        printf("Program execution completed.\nBRAVO: le programme est correcte!!!");
    }
    else
    {
        Erreur(PT_ERR);
        printf("PAS BRAVO: fin de programme erron�e!!!!\n");

        // Add this line to consume symbols until the end of the file
        while (SYM_COUR.CODE != FIN_TOKEN)
        {
            printf("Current Token: %d\n", SYM_COUR.CODE);
            printf("Current Lexeme: %s\n", SYM_COUR.NOM);
            Sym_Suiv();
        }
    }
}

void BLOCK()
{
    CONSTS();
    VARS();
    PROC();
    FUNCTION();
    INSTS();
}

void CONSTS()
{
    switch (SYM_COUR.CODE)
    {
    case CONST_TOKEN:
        Sym_Suiv();
        if (SYM_COUR.CODE == ID_TOKEN)
        {
            rule_2(SYM_COUR.NOM, "CONSTANT");
            Sym_Suiv();
        }
        else
        {
            Erreur(ID_ERR);
        }
        Test_Symbole(EG_TOKEN, EG_ERR);
        Test_Symbole(NUM_TOKEN, NUM_ERR);
        Test_Symbole(PV_TOKEN, PV_ERR);
        while (SYM_COUR.CODE == ID_TOKEN)
        {
            rule_2(SYM_COUR.NOM, "CONSTANT");
            Sym_Suiv();
            Test_Symbole(EG_TOKEN, EG_ERR);
            Test_Symbole(NUM_TOKEN, NUM_ERR);
            Test_Symbole(PV_TOKEN, PV_ERR);
        };
        break;
    case VAR_TOKEN:
        break;
    case BEGIN_TOKEN:
        break;
    case FCT_TOKEN:
        break;
    default:
        Erreur(CONST_VAR_BEGIN_ERR);
        break;
    }
}

void VARS()
{
    switch (SYM_COUR.CODE)
    {
    case VAR_TOKEN:
        Sym_Suiv();
        if (SYM_COUR.CODE == ID_TOKEN)
        {
            rule_2(SYM_COUR.NOM, "VARIABLE");
            Sym_Suiv();
        }
        else
        {
            Erreur(ID_ERR);
        }
        if (SYM_COUR.CODE == PPT_TOKEN)
        {
            TYPE();
        }
        while (SYM_COUR.CODE == VIR_TOKEN)
        {
            Sym_Suiv();
            if (SYM_COUR.CODE == ID_TOKEN)
            {
                rule_2(SYM_COUR.NOM, "VARIABLE");
                Sym_Suiv();
            }
            else
            {
                Erreur(ID_ERR);
            }
            if (SYM_COUR.CODE == PPT_TOKEN)
            {
                TYPE();
            }
        }

        Test_Symbole(PV_TOKEN, PV_ERR);
        break;
    case BEGIN_TOKEN:
        break;
    case FCT_TOKEN:
        break;
    default:
        Erreur(VAR_BEGIN_ERR);
        break;
    }
}

void INSTS()
{
    // begin INST { ; INST } end
    if (SYM_COUR.CODE == BEGIN_TOKEN)
    {
        Sym_Suiv();
        INST();

        while (SYM_COUR.CODE == PV_TOKEN)
        {
            Sym_Suiv();
            INST();
        }

        if (SYM_COUR.CODE == END_TOKEN)
        {
            Sym_Suiv();
        }
        else
        {
            Erreur(FIN_ERR);
        }
    }
    else
    {
        Erreur(BEGIN_ERR);
    }
}

void INST()

{

    // INSTS | AFFEC | SI | TANTQUE | ECRIRE | LIRE | e
    switch (SYM_COUR.CODE)
    {
    case BEGIN_TOKEN:
        INSTS();
        break;
    case ID_TOKEN:

        AFFEC();
        break;
    case IF_TOKEN:
        SI();
        break;
    case WHILE_TOKEN:
        TANTQUE();
        break;
    case WRITE_TOKEN:
        ECRIRE();
        break;
    case READ_TOKEN:
        LIRE();
        break;
    case FOR_TOKEN:
        POUR();
    case REP_TOKEN:
        REP();

    default:
        break;
    }
}

void AFFEC()
{
    // ID := EXPR
    if (SYM_COUR.CODE == ID_TOKEN)
    {
        rule_3(SYM_COUR.NOM);
        rule_4(SYM_COUR.NOM);
        Sym_Suiv();
    }
    else
    {
        Erreur(ID_ERR);
    }
    Test_Symbole(AFF_TOKEN, AFF_ERR);
    EXPR();
}

void SI()
{
    Test_Symbole(IF_TOKEN, IF_ERR);
    COND();
    Test_Symbole(THEN_TOKEN, THEN_ERR);
    INST();
    Test_Symbole(ELSE_TOKEN, ELSE_ERR);
    INST();
}

void TANTQUE()
{
    Test_Symbole(WHILE_TOKEN, WHILE_ERR);
    COND();
    Test_Symbole(DO_TOKEN, DO_ERR);
    INST();
}

void ECRIRE()
{
    Test_Symbole(WRITE_TOKEN, WRITE_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    EXPR();

    printf("ana salit mn write\n");
    while (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        EXPR();
    }

    Test_Symbole(PF_TOKEN, PF_ERR);
    printf("ana salit mn write\n");
}

void LIRE()
{
    Test_Symbole(READ_TOKEN, READ_ERR);
    Test_Symbole(PO_TOKEN, PO_ERR);
    if (SYM_COUR.CODE == ID_TOKEN)
    {
        rule_3(SYM_COUR.NOM);
        rule_4(SYM_COUR.NOM);
        Sym_Suiv();
    }
    else
    {
        Erreur(ID_ERR);
    }

    while (SYM_COUR.CODE == VIR_TOKEN)
    {
        Sym_Suiv();
        Test_Symbole(ID_TOKEN, ID_ERR);
    }

    Test_Symbole(PF_TOKEN, PF_ERR);
}

void COND()
{
    EXPR();
    RELOP();
    EXPR();
}

void EXPR()
{

    // TERM { ADDOP TERM }
    TERM();

    while (SYM_COUR.CODE == PLUS_TOKEN || SYM_COUR.CODE == MOINS_TOKEN)
    {
        ADDOP();
        TERM();
    }
}

void TERM()
{
    FACT();

    while (SYM_COUR.CODE == MULT_TOKEN || SYM_COUR.CODE == DIV_TOKEN)
    {
        MULOP();
        FACT();
    }
}

void FACT()
{
    switch (SYM_COUR.CODE)
    {
    case ID_TOKEN:
        rule_3(SYM_COUR.NOM);
        Sym_Suiv();
        break;
    case NUM_TOKEN:
        Test_Symbole(NUM_TOKEN, NUM_ERR);
        break;
    case PO_TOKEN:
        Test_Symbole(PO_TOKEN, PO_ERR);
        EXPR();
        Test_Symbole(PF_TOKEN, PF_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

void RELOP()
{
    switch (SYM_COUR.CODE)
    {
    case EG_TOKEN:
    case DIFF_TOKEN:
    case INF_TOKEN:
    case SUP_TOKEN:
    case INFEG_TOKEN:
    case SUPEG_TOKEN:
        Test_Symbole(SYM_COUR.CODE, EG_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

void ADDOP()
{
    switch (SYM_COUR.CODE)
    {
    case PLUS_TOKEN:
        Test_Symbole(SYM_COUR.CODE, PLUS_ERR);
        break;
    case MOINS_TOKEN:
        Test_Symbole(SYM_COUR.CODE, MOINS_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

void MULOP()
{
    switch (SYM_COUR.CODE)
    {
    case MULT_TOKEN:
        Test_Symbole(SYM_COUR.CODE, MULT_ERR);
        break;
    case DIV_TOKEN:
        Test_Symbole(SYM_COUR.CODE, DIV_ERR);
        break;
    default:
        Erreur(ERREUR_ERR);
        break;
    }
}

void rule_2(char *identifiant, char *type)
{
    // V�rifier si l'identifiant est d�j� dans le tableau
    for (int i = 0; i < nombre_variables; i++)
    {
        if (strcmp(variables[i].nom, identifiant) == 0)
        {
            // Si l'identifiant est d�j� pr�sent, afficher un message d'erreur et quitter le programme
            printf("ERROR %s IS ALREADY DECLARED AS %s\n", variables[i].nom, variables[i].type);
            exit(EXIT_FAILURE);
        }
    }

    // Si l'identifiant n'est pas d�j� pr�sent, l'ajouter au tableau
    strcpy(variables[nombre_variables].nom, identifiant);
    strcpy(variables[nombre_variables].type, type);
    nombre_variables++;
}

void rule_3(char *identifiant)
{
    int declared = 0; // Variable pour suivre si l'identifiant est d�clar�

    for (int i = 0; i < nombre_variables; i++)
    {
        if (strcmp(variables[i].nom, identifiant) == 0)
        {
            declared = 1; // L'identifiant a �t� trouv� dans la liste des variables d�clar�es
            break;
        }
    }

    if (!declared)
    { // Si l'identifiant n'est pas d�clar�
        printf("ERROR %s IS NOT DECLARED \n", identifiant);
        exit(EXIT_FAILURE);
    }
}

void rule_4(char *identifiant)
{
    for (int i = 0; i < nombre_variables; i++)
    {
        if (strcmp(variables[i].nom, identifiant) == 0 && strcmp(variables[i].type, "CONSTANT") == 0)
        {
            printf("ERROR %s IS ALREADY DECLARED AS A CONSTANT\n", identifiant);
            exit(EXIT_FAILURE);
        }
    }
}

void rule_5(char *identifiant)
{
    for (int i = 0; i < nombre_variables; i++)
    {
        if (strcmp(variables[i].nom, identifiant) == 0 && strcmp(variables[i].type, "PROGRAM") == 0)
        {
            printf("ERROR %s IS THE PROGRAM IDENTIFIER AND CANNOT BE USED IN THE PROGRAM\n", identifiant);
            exit(EXIT_FAILURE);
        }
    }
}

void ARRAY()
{
    Test_Symbole(ARRAY_TOKEN, ARRAY_ERR);
    Test_Symbole(CO_TOKEN, CO_ERR);
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    Test_Symbole(PT_TOKEN, PT_ERR);
    Test_Symbole(PT_TOKEN, PT_ERR);
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    Test_Symbole(CF_TOKEN, CF_ERR);
    Test_Symbole(OF_TOKEN, OF_ERR);
    if (SYM_COUR.CODE != INTEGER_TOKEN && SYM_COUR.CODE != STRING_TOKEN && SYM_COUR.CODE != CHAR_TOKEN)
    {
        Erreur(ERREUR_ERR);
    }
}

void POUR()
{
    Test_Symbole(FOR_TOKEN, FOR_ERR);
    Test_Symbole(ID_TOKEN, ID_ERR);
    Test_Symbole(AFF_TOKEN, AFF_ERR);
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    Test_Symbole(TO_TOKEN, TO_ERR);
    Test_Symbole(NUM_TOKEN, NUM_ERR);
    Test_Symbole(DO_TOKEN, DO_ERR);
    INST();
}

void TYPE()
{
    Sym_Suiv();
    if (SYM_COUR.CODE == ARRAY_TOKEN)
    {
        ARRAY();
        Sym_Suiv();
    }
    else if (SYM_COUR.CODE == INTEGER_TOKEN)
    {
        Test_Symbole(INTEGER_TOKEN, INTEGER_ERR);
    }
    else if (SYM_COUR.CODE == STRING_TOKEN)
    {
        Test_Symbole(STRING_TOKEN, STRING_ERR);
    }
    else if (SYM_COUR.CODE == CHAR_TOKEN)
    {
        Test_Symbole(CHAR_TOKEN, CHAR_ERR);
    }
}

void PROC()
{ // FUNCTION := function ID { (function_parameters

    switch (SYM_COUR.CODE)
    {
    case PROC_TOKEN:

        Test_Symbole(PROC_TOKEN, PROC_ERR);
        // Test_Symbole(ID_TOKEN, ID_ERR); // Function name
        if (SYM_COUR.CODE == ID_TOKEN)
        {
            rule_2(SYM_COUR.NOM, "VARIABLE");
            Sym_Suiv();
        }
        else
        {
            Erreur(ID_ERR);
        }
        if (SYM_COUR.CODE == PO_TOKEN)
        {
            Sym_Suiv();
            // Parse function parameters
            while (SYM_COUR.CODE != PPT_TOKEN)
            {

                // Parse parameter name (identifier)
                if (SYM_COUR.CODE == ID_TOKEN)
                {
                    rule_2(SYM_COUR.NOM, "VARIABLE");
                    Sym_Suiv();
                }
                else
                {
                    Erreur(ID_ERR);
                }

                // Check for a comma ',' if more parameters are present
                if (SYM_COUR.CODE == VIR_TOKEN)
                {
                    Sym_Suiv();
                }
            }
            Sym_Suiv();
        }
        else
        {
            Test_Symbole(PPT_TOKEN, PPT_ERR);
        }

        // Parse parameter type (e.g., integer, real, etc.)
        if (SYM_COUR.CODE == INTEGER_TOKEN || SYM_COUR.CODE == REAL_TOKEN ||
            SYM_COUR.CODE == STRING_TOKEN || SYM_COUR.CODE == BOOLEAN_TOKEN ||
            SYM_COUR.CODE == CHAR_TOKEN)
        {
            Sym_Suiv();
        }
        else
        {
            Erreur(PARAM_TYPE_ERR);
        }

        Test_Symbole(PF_TOKEN, PF_ERR);
        Test_Symbole(PV_TOKEN, PV_ERR);

        BLOCK();
        Test_Symbole(PV_TOKEN, PV_ERR);
        break;
    case BEGIN_TOKEN:
        break;
    }
}

void FUNCTION()
{ // FUNCTION := function ID { (function_parameters
    switch (SYM_COUR.CODE)
    {
    case FCT_TOKEN:
        printf("rani dkhalt lfct\n");
        Test_Symbole(FCT_TOKEN, FCT_ERR);
        // Test_Symbole(ID_TOKEN, ID_ERR); // Function name
        if (SYM_COUR.CODE == ID_TOKEN)
        {
            rule_2(SYM_COUR.NOM, "VARIABLE");
            Sym_Suiv();
        }
        else
        {
            Erreur(ID_ERR);
        }
        if (SYM_COUR.CODE == PO_TOKEN)
        {
            Sym_Suiv();
            // Parse function parameters
            while (SYM_COUR.CODE != PPT_TOKEN)
            {

                // Parse parameter name (identifier)
                if (SYM_COUR.CODE == ID_TOKEN)
                {
                    rule_2(SYM_COUR.NOM, "VARIABLE");
                    Sym_Suiv();
                }
                else
                {
                    Erreur(ID_ERR);
                }

                // Check for a comma ',' if more parameters are present
                if (SYM_COUR.CODE == VIR_TOKEN)
                {
                    Sym_Suiv();
                }
            }
            Sym_Suiv();
        }
        else
        {
            Test_Symbole(PPT_TOKEN, PPT_ERR);
        }

        // Parse parameter type (e.g., integer, real, etc.)
        if (SYM_COUR.CODE == INTEGER_TOKEN || SYM_COUR.CODE == REAL_TOKEN ||
            SYM_COUR.CODE == STRING_TOKEN || SYM_COUR.CODE == BOOLEAN_TOKEN ||
            SYM_COUR.CODE == CHAR_TOKEN)
        {
            Sym_Suiv();
        }
        else
        {
            Erreur(PARAM_TYPE_ERR);
        }

        Test_Symbole(PF_TOKEN, PF_ERR);
        Test_Symbole(PPT_TOKEN, PPT_ERR);

        if (SYM_COUR.CODE == INTEGER_TOKEN || SYM_COUR.CODE == REAL_TOKEN ||
            SYM_COUR.CODE == STRING_TOKEN || SYM_COUR.CODE == BOOLEAN_TOKEN ||
            SYM_COUR.CODE == CHAR_TOKEN)
        {
            Sym_Suiv();
        }
        else
        {
            Erreur(ERREUR_ERR);
        }
        Test_Symbole(PV_TOKEN, PV_ERR);
        BLOCK();
        Test_Symbole(PV_TOKEN, PV_ERR);
        break;
    case BEGIN_TOKEN:
        break;
    }
}

void REP(){
    switch (SYM_COUR.CODE)
    {
    case REP_TOKEN:

        Test_Symbole(REP_TOKEN, PROC_ERR);
        // Test_Symbole(ID_TOKEN, ID_ERR); // Function name
        }

    INST();
    Test_Symbole(UN_TOKEN, PROC_ERR);
    INST();
}


int main()
{
    fichier = fopen("if.txt", "r");
    if (fichier == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // PREMIER_SYM();
    Lire_Car();
    Sym_Suiv();

    PROGRAM();

    printf("Program execution completed.\n");

    if (SYM_COUR.CODE == FIN_TOKEN)
    {
        printf("BRAVO: le programme est correcte!!!\n");
    }
    else
    {
        printf("PAS BRAVO: fin de programme erron�e!!!!\n");
        printf("Current Token: %d\n", SYM_COUR.CODE);
        printf("Current Lexeme: %s\n", SYM_COUR.NOM);
        Sym_Suiv(); // Move this line inside the else block
    }

    fclose(fichier);
    return 0;
}
