﻿/********************************************************************
	created:	2013/06/15
	created:	15:6:2013   17:29
	filename: 	\QLanguage\Parser\SyntaxTree\SyntaxTree_Exp.cpp
	file path:	\QLanguage\Parser\SyntaxTree
	file base:	SyntaxTree_Exp
	file ext:	cpp
	author:		lwch
	
	purpose:	
*********************************************************************/
#include "../Parser.h"
#include "SyntaxTree_Exp.h"

namespace QLanguage
{
    SyntaxTree_Exp::SyntaxTree_Exp(Type type, SyntaxTree_Base* pOP1, SyntaxTree_Base* pOP2)
        : parent(sizeof(SyntaxTree_Exp))
        , type(type)
        , pOP1(pOP1)
        , pOP2(pOP2)
    {
    }

    SyntaxTree_Exp::SyntaxTree_Exp(Type type, SyntaxTree_Base* pOP)
        : parent(sizeof(SyntaxTree_Exp))
        , type(type)
        , pOP1(pOP)
        , pOP2(NULL)
    {
    }

    SyntaxTree_Exp::~SyntaxTree_Exp()
    {
    }

    void SyntaxTree_Exp::print(ostream& stream, uint indent)const
    {
    }

    // exp -> exp ">" "=" exp1
    // exp -> exp "<" "=" exp1
    // exp -> exp "=" "=" exp1
    // exp -> exp "&" "&" exp1
    // exp -> exp "|" "|" exp1
    bool Parser::reduceExp2Size(ushort i)
    {
        shifts.pop();
        shifts.pop();

        SyntaxTree_Exp* pExp = allocator<SyntaxTree_Exp>::allocate();
        switch (i)
        {
        case EXP_GREATER_EQUAL:
            construct(pExp, SyntaxTree_Exp::GreaterEqual, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_LESS_EQUAL:
            construct(pExp, SyntaxTree_Exp::LessEqual, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_EQUAL:
            construct(pExp, SyntaxTree_Exp::Equal, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_LOGIC_AND:
            construct(pExp, SyntaxTree_Exp::LogicAnd, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_LOGIC_OR:
            construct(pExp, SyntaxTree_Exp::LogicOr, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        }

        context.data.insert(pExp);

        syntaxTreeStack.pop();
        syntaxTreeStack.pop();
        syntaxTreeStack.push(pExp);

        return true;
    }

    // exp -> exp ">" exp1
    // exp -> exp "<" exp1
    // exp -> exp "=" exp1
    // exp -> exp "&" exp1
    // exp -> exp "|" exp1
    // exp -> exp "^" exp1
    // exp1 -> "!" exp2
    // exp1 -> "+" exp2
    // exp1 -> "-" exp2
    // exp2 -> exp2 "+" exp3
    // exp2 -> exp2 "-" exp3
    // exp3 -> exp3 "*" exp4
    // exp3 -> exp3 "/" exp4
    // exp3 -> exp3 "%" exp4
    bool Parser::reduceExp1Size(ushort i)
    {
        shifts.pop();

        SyntaxTree_Exp* pExp = allocator<SyntaxTree_Exp>::allocate();
        switch (i)
        {
        case EXP_GREATER:
            construct(pExp, SyntaxTree_Exp::Greater, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_LESS:
            construct(pExp, SyntaxTree_Exp::Less, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_ASSIGN:
            construct(pExp, SyntaxTree_Exp::Assign, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_BIT_AND:
            construct(pExp, SyntaxTree_Exp::BitAnd, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_BIT_OR:
            construct(pExp, SyntaxTree_Exp::BitOr, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_BIT_XOR:
            construct(pExp, SyntaxTree_Exp::BitXor, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_NOT:
            construct(pExp, SyntaxTree_Exp::Not, syntaxTreeStack.top());
            break;
        case EXP_POSITIVE:
            construct(pExp, SyntaxTree_Exp::Positive, syntaxTreeStack.top());
            break;
        case EXP_NEGATIVE:
            construct(pExp, SyntaxTree_Exp::Negative, syntaxTreeStack.top());
            break;
        case EXP_ADD:
            construct(pExp, SyntaxTree_Exp::Add, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_SUB:
            construct(pExp, SyntaxTree_Exp::Sub, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_MUL:
            construct(pExp, SyntaxTree_Exp::Mul, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_DIV:
            construct(pExp, SyntaxTree_Exp::Div, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        case EXP_MOD:
            construct(pExp, SyntaxTree_Exp::Mod, syntaxTreeStack[1], syntaxTreeStack.top());
            break;
        }

        context.data.insert(pExp);

        syntaxTreeStack.pop();
        switch (i)
        {
        case EXP_GREATER:
        case EXP_LESS:
        case EXP_ASSIGN:
        case EXP_BIT_AND:
        case EXP_BIT_OR:
        case EXP_BIT_XOR:
        case EXP_ADD:
        case EXP_SUB:
        case EXP_MUL:
        case EXP_DIV:
        case EXP_MOD:
            syntaxTreeStack.pop();
            break;
        }
        syntaxTreeStack.push(pExp);

        return true;
    }

    // exp4 -> call_desc
    bool Parser::reduceExpCall()
    {
        SyntaxTree_Exp* pExp = allocator<SyntaxTree_Exp>::allocate();
        construct(pExp, SyntaxTree_Exp::Call, syntaxTreeStack.top());

        context.data.insert(pExp);

        syntaxTreeStack.pop();
        syntaxTreeStack.push(pExp);

        return true;
    }

    // exp4 -> value_desc "as" type_desc
    bool Parser::reduceExpValueAsType()
    {
        shifts.pop();

        SyntaxTree_Exp* pExp = allocator<SyntaxTree_Exp>::allocate();
        construct(pExp, SyntaxTree_Exp::ValueAsType, syntaxTreeStack[1], syntaxTreeStack.top());

        context.data.insert(pExp);

        syntaxTreeStack.pop();
        syntaxTreeStack.pop();
        syntaxTreeStack.push(pExp);

        return true;
    }

    // exp4 -> value_desc
    bool Parser::reduceExpValue()
    {
        SyntaxTree_Exp* pExp = allocator<SyntaxTree_Exp>::allocate();
        construct(pExp, SyntaxTree_Exp::Value, syntaxTreeStack.top());

        context.data.insert(pExp);

        syntaxTreeStack.pop();
        syntaxTreeStack.push(pExp);

        return true;
    }
}