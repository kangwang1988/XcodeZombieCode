/*
 *  ClangZombieCodePlugin.hpp
 *  ClangZombieCodeDemo
 *
 *  Created by KyleWong on 26/10/2016.
 *  Copyright © 2016 KyleWong. All rights reserved.
 *
 */

#ifndef ClangZombieCodePlugin_
#define ClangZombieCodePlugin_
#include<iostream>
#include<sstream>
#include<typeinfo>

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "ZombieCodeUtil.hpp"
/**
 * @discussion Enviroment:clang-3.9.1(release 39)
 * In terminal, use "/opt/llvm/llvm_build/bin/clang ../test.m -Xclang -load -Xclang lib/Debug/ClangCodeCheckPlugin.dylib -Xclang -plugin -Xclang ClangCodeCheckPlugin".
 * In Xcode, use "-Xclang -load -Xclang /opt/llvm/ClangCodeCheckPlugin/build/lib/Debug/ClangCodeCheckPlugin.dylib -Xclang -add-plugin -Xclang ClangCodeCheckPlugin",notice the -add-plugin instead of -plugin.
 *****XcodeHacking
 * sudo mv HackedClang.xcplugin `xcode-select -print-path`/../PlugIns/Xcode3Core.ideplugin/Contents/SharedSupport/Developer/Library/Xcode/Plug-ins
 * sudo mv HackedBuildSystem.xcspec `xcode-select -print-path`/Platforms/iPhoneSimulator.platform/Developer/Library/Xcode/Specifications
 * See HackedClang.xcplugin/HackedBuildSystem.xcspec @https://raw.githubusercontent.com/kangwang1988/kangwang1988.github.io/master/others/XcodeHacking.
 */

/* The classes below are exported */
#pragma GCC visibility push(default)
using namespace clang;
using namespace std;
using namespace llvm;

extern string gSrcRootPath;

namespace ZombieCode
{
    class ZombieCodeASTVisitor : public RecursiveASTVisitor<ZombieCodeASTVisitor>
    {
    private:
        ASTContext *context;
        string objcClsInterface;
        string objcClsImpl;
        string objcProtocol;
        bool objcIsInstanceMethod;
        bool calleeIsInstanceMethod;
        string objcSelector;
        string objcMethodSrcCode;
        string objcMethodFilename;
        string objcMethodRange;
        vector<string> hierarchy;
    public:
        void setContext(ASTContext &context);
        string pureSelFromSelector(string selector);
        bool VisitDecl(Decl *decl);
        bool VisitStmt(Stmt *s);
        bool handleUnknownReceiverInterface(ObjCMessageExpr *objcExpr,string calleeSel);
        void handleNotificationMessageExpr(ObjCMessageExpr *objcExpr);
        void handlePerformSelectorMessageExpr(ObjCMessageExpr *objcExpr);
        void handleTargetActionMessageExpr(ObjCMessageExpr *objcExpr);
    };
    class ZombieCodeASTConsumer : public ASTConsumer
    {
    private:
        ZombieCodeASTVisitor visitor;
        void HandleTranslationUnit(ASTContext &context);
    };
    
    class ZombieCodeASTAction : public PluginASTAction
    {
    public:
        unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &Compiler,llvm::StringRef InFile);
        bool ParseArgs(const CompilerInstance &CI, const std::vector<std::string>& args);
    };
}
#pragma GCC visibility pop
#endif
