﻿/********************************************************************
	created:	2013/06/20
	created:	20:6:2013   22:12
	filename: 	\QLanguage\Parser\SyntaxTree\SyntaxTree_Stmt.cpp
	file path:	\QLanguage\Parser\SyntaxTree
	file base:	SyntaxTree_Stmt
	file ext:	cpp
	author:		lwch
	
	purpose:	
*********************************************************************/
#include "../Parser.h"
#include "SyntaxTree_Stmt.h"

namespace QLanguage
{
    SyntaxTree_Stmt::SyntaxTree_Stmt(bool bSemicolon, SyntaxTree_Base* pStmt, Type type)
        : parent(sizeof(SyntaxTree_Stmt))
        , bSemicolon(bSemicolon)
        , pStmt(pStmt)
        , _type(type)
    {
    }

    SyntaxTree_Stmt::~SyntaxTree_Stmt()
    {
    }

    void SyntaxTree_Stmt::print(ostream& stream, uint indent) const
    {
        this->printIndent(stream, indent);
        pStmt->print(stream, indent);
        switch (_type)
        {
        case Assign:
        case Call:
        case Declare:
        case Do:
            if (bSemicolon) stream << ';';
            break;
        default:
            break;
        }
    }

    // stmt -> assign_desc ";"
    // stmt -> call_desc ";"
    // stmt -> declare_desc ";"
    // stmt -> do_desc ";"
    // stmt -> if_desc
    // stmt -> for_desc
    // stmt -> while_desc
    // stmt -> return_desc
    bool Parser::reduceStmt(ushort i)
    {
        SyntaxTree_Stmt* pStmt = allocator<SyntaxTree_Stmt>::allocate();
        switch (i)
        {
        case STMT_ASSIGN_DESC:                       // stmt -> assign_desc ";"
            shifts.pop();
            construct(pStmt, true, syntaxTreeStack.top(), SyntaxTree_Stmt::Assign);
            break;
        case STMT_CALL_DESC:                         // stmt -> call_desc ";"
            shifts.pop();
            construct(pStmt, true, syntaxTreeStack.top(), SyntaxTree_Stmt::Call);
            break;
        case STMT_DECLARE_DESC:                      // stmt -> declare_desc ";"
            shifts.pop();
            construct(pStmt, true, syntaxTreeStack.top(), SyntaxTree_Stmt::Declare);
            break;
        case STMT_DO_DESC:                           // stmt -> do_desc ";"
            shifts.pop();
            construct(pStmt, true, syntaxTreeStack.top(), SyntaxTree_Stmt::Do);
            break;
        case STMT_IF_DESC:                           // stmt -> if_desc
            construct(pStmt, true, syntaxTreeStack.top(), SyntaxTree_Stmt::If);
            break;
        case STMT_FOR_DESC:                          // stmt -> for_desc
            construct(pStmt, true, syntaxTreeStack.top(), SyntaxTree_Stmt::For);
            break;
        case STMT_WHILE_DESC:                        // stmt -> while_desc
            construct(pStmt, true, syntaxTreeStack.top(), SyntaxTree_Stmt::While);
            break;
        case STMT_RETURN_DESC:                       // stmt -> return_desc
            construct(pStmt, true, syntaxTreeStack.top(), SyntaxTree_Stmt::Return);
            break;
        }
        
        context.data.insert(pStmt);
        
        syntaxTreeStack.pop();
        syntaxTreeStack.push(pStmt);
        
        return true;
    }
    
    // stmt_no_semicolon -> assign_desc
    // stmt_no_semicolon -> call_desc
    // stmt_no_semicolon -> declare_desc
    // stmt_no_semicolon -> if_desc
    // stmt_no_semicolon -> for_desc
    // stmt_no_semicolon -> while_desc
    // stmt_no_semicolon -> do_desc
    bool Parser::reduceStmtNoSemicolon(ushort i)
    {
        SyntaxTree_Stmt* pStmt = allocator<SyntaxTree_Stmt>::allocate();
        switch (i)
        {
        case STMT_NO_SEMICOLON_ASSIGN_DESC:                       // stmt_no_semicolon -> assign_desc
            construct(pStmt, false, syntaxTreeStack.top(), SyntaxTree_Stmt::Assign);
            break;
        case STMT_NO_SEMICOLON_CALL_DESC:                         // stmt_no_semicolon -> call_desc
            construct(pStmt, false, syntaxTreeStack.top(), SyntaxTree_Stmt::Call);
            break;
        case STMT_NO_SEMICOLON_DECLARE_DESC:                      // stmt_no_semicolon -> declare_desc
            construct(pStmt, false, syntaxTreeStack.top(), SyntaxTree_Stmt::Declare);
            break;
        case STMT_NO_SEMICOLON_DO_DESC:                           // stmt_no_semicolon -> do_desc
            construct(pStmt, false, syntaxTreeStack.top(), SyntaxTree_Stmt::Do);
            break;
        case STMT_NO_SEMICOLON_IF_DESC:                           // stmt_no_semicolon -> if_desc
            construct(pStmt, false, syntaxTreeStack.top(), SyntaxTree_Stmt::If);
            break;
        case STMT_NO_SEMICOLON_FOR_DESC:                          // stmt_no_semicolon -> for_desc
            construct(pStmt, false, syntaxTreeStack.top(), SyntaxTree_Stmt::For);
            break;
        case STMT_NO_SEMICOLON_WHILE_DESC:                        // stmt_no_semicolon -> while_desc
            construct(pStmt, false, syntaxTreeStack.top(), SyntaxTree_Stmt::While);
            break;
        }
        
        context.data.insert(pStmt);
        
        syntaxTreeStack.pop();
        syntaxTreeStack.push(pStmt);
        
        return true;
    }
}