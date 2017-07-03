//
//  XcodeEditorCPPWrapper.m
//  CodeSimilarityChecker
//
//  Created by KyleWong on 13/02/2017.
//  Copyright © 2017 KyleWong. All rights reserved.
//

#import "XcodeEditorCPPWrapper.h"
#import "XcodeEditor.h"

#include <vector>
#include <string>
using namespace std;

vector<string> getSourcesByProject(string prjPath){
    NSString *prjPathNS = [NSString stringWithCString:prjPath.c_str() encoding:NSUTF8StringEncoding];
    NSString *prjFileFolder = [prjPathNS stringByDeletingLastPathComponent];
    XCProject *project = [XCProject projectWithFilePath:prjPathNS];
    NSArray<XCSourceFile*> *filesAry = project.files;
    vector<string> filesVec;
    for(XCSourceFile *file in filesAry){
        if(file.type ==  SourceCodeObjC || file.type == SourceCodeObjCPlusPlus ||
           file.type == SourceCodeCPlusPlus || file.type == SourceCodeSwift)
            filesVec.push_back(string([[prjFileFolder stringByAppendingPathComponent:file.pathRelativeToProjectRoot] UTF8String]));
    }
    return filesVec;
}
