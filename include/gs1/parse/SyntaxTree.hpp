#ifndef GS1PARSE_SYNTAXTREE_HPP
#define GS1PARSE_SYNTAXTREE_HPP

#include <gs1/parse/SyntaxTreeVisitor.hpp>
#include <gs1/parse/Token.hpp>

namespace gs1
{
struct SyntaxNode;
struct SyntaxTerminal;
struct Stmt;
struct Expr;

// --------------------------------------------------
// Core syntax tree structure
// --------------------------------------------------

struct SyntaxNodeOrTerminal {
  virtual ~SyntaxNodeOrTerminal() {}

  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual Range GetRange() const = 0;
  virtual Range GetFullRange() const = 0;

  SyntaxNode *parent;
};

struct SyntaxNode : public SyntaxNodeOrTerminal {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual Range GetRange() const;
  virtual Range GetFullRange() const;

  virtual std::string GetBaseType() const { return "SyntaxNode"; };

  virtual std::string GetType() const { return "SyntaxNode"; };

  vector<shared_ptr<SyntaxNodeOrTerminal>> children;
};

struct SyntaxTerminal : public SyntaxNodeOrTerminal {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual Range GetRange() const;
  virtual Range GetFullRange() const;

  Token token;
  vector<Token> leadingTrivia;
  vector<Token> trailingTrivia;
};

// --------------------------------------------------
// Statements
// --------------------------------------------------

struct Stmt : public SyntaxNode {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetBaseType() const { return "Stmt"; };

  virtual std::string GetType() const { return "Stmt"; };
};

struct StmtEmpty : public Stmt {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "StmtEmpty"; };
};

struct StmtBlock : public Stmt {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "StmtBlock"; };

  vector<Stmt *> statements;
};

struct StmtIf : public Stmt {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "StmtIf"; };

  Expr *cond;
  Stmt *thenBody;
  Stmt *elseBody;
};

struct StmtLoop : public Stmt {
  unsigned int breakPosition;
  unsigned int continuePosition;
};

struct StmtFor : public StmtLoop {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "StmtFor"; };

  Expr *init;
  Expr *cond;
  Expr *step;
  Stmt *body;
};

struct StmtWhile : public StmtLoop {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "StmtWhile"; };

  Expr *cond;
  Stmt *body;
};

struct StmtBreak : public Stmt {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "StmtBreak"; };
};

struct StmtContinue : public Stmt {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "StmtContinue"; };
};

struct StmtReturn : public Stmt {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "StmtReturn"; };
};

struct StmtCommand : public Stmt {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "StmtCommand"; };

  SyntaxTerminal *name;
  vector<Expr *> args;
};

struct StmtFunctionDecl : public Stmt {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "StmtFunctionDecl"; };

  SyntaxTerminal *name;
  Stmt *body;
};

// --------------------------------------------------
// Expressions
// --------------------------------------------------

struct Expr : public Stmt {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetBaseType() const { return "Expr"; };

  virtual std::string GetType() const { return "Expr"; };
};

struct ExprId : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprId"; };

  SyntaxTerminal *name;
};

struct ExprNumberLiteral : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprNumberLiteral"; };

  SyntaxTerminal *literal;
};

struct ExprStringLiteral : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprStringLiteral"; };

  SyntaxTerminal *literal;
};

struct ExprList : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprList"; };

  vector<Expr *> elements;
};

struct ExprRange : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprRange"; };

  SyntaxTerminal *lower;
  SyntaxTerminal *upper;
};

struct ExprUnaryOp : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprUnaryOp"; };

  bool prefix;
  SyntaxTerminal *op;
  Expr *expr;
};

struct ExprBinaryOp : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprBinaryOp"; };

  SyntaxTerminal *op;
  Expr *left;
  Expr *right;
};

struct ExprTernaryOp : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprTernaryOp"; };

  Expr *cond;
  Expr *thenValue;
  Expr *elseValue;
};

struct ExprIndex : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprIndex"; };

  Expr *left;
  Expr *index;
};

struct ExprIndexDotLookup : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprIndexDotLookup"; };

  SyntaxTerminal *id;
};

struct ExprCall : public Expr {
  virtual void Accept(SyntaxTreeVisitor *v) { v->Visit(this); }

  virtual std::string GetType() const { return "ExprCall"; };

  Expr *left;
  vector<Expr *> args;
};
}

#endif
