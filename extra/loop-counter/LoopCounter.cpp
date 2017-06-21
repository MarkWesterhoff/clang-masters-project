#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Driver/Options.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Rewrite/Core/Rewriter.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

using namespace clang;  
using namespace clang::tooling;
#include <iostream>

class FindLoopVisitor : public RecursiveASTVisitor<FindLoopVisitor> {  
 public:
  explicit FindLoopVisitor(ASTContext *Context, std::string fName)
      : Context(Context), fName(fName) {}

  bool shouldTraversePostOrder() { 
    return true; 
  }

  bool VisitForStmt(Stmt* Statement){
    Statement->dump();
    std::cout << "GOT HERE" << std::endl;
    for (const auto& child : Statement->children()){
      std::cout << "child" << std::endl;
      child->dump();
    }
    return true;
  }

 private:
  ASTContext *Context;
  std::string fName;
};

class FindLoopConsumer : public clang::ASTConsumer {  
 public:
  explicit FindLoopConsumer(ASTContext *Context, std::string fName)
      : Visitor(Context, fName) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) {
    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
  }

 private:
  FindLoopVisitor Visitor;
};

class FindLoopAction : public clang::ASTFrontendAction {  
 public:
  FindLoopAction() {}

  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
      clang::CompilerInstance &Compiler, llvm::StringRef InFile) {
    const std::string fName = "doSomething";
    return std::unique_ptr<clang::ASTConsumer>(
        new FindLoopConsumer(&Compiler.getASTContext(), fName));
  }
};

static llvm::cl::OptionCategory MyToolCategory("my-tool options");

int main(int argc, const char **argv) {  
  const std::string fName = "doSomething";

  CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());

  // run the Clang Tool, creating a new FrontendAction (explained below)
  int result = Tool.run(newFrontendActionFactory<FindLoopAction>().get());
  return result;
}