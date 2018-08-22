//
//  ZombieCodeUtil.hpp
//  ClangZombieCodeDemo
//
//  Created by KyleWong on 14/10/2016.
//
//

#ifndef ZombieCodeUtil_hpp
#define ZombieCodeUtil_hpp
#include <string>
#include <algorithm>
#include <functional>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <sys/stat.h>
#include "json.hpp"

#define kAppMainEntryClass  "UIApplication"
#define kAppMainEntrySelector  "main"

using namespace std;
using namespace nlohmann;

static vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

static inline void remove_blank(string &str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    str.erase(remove(str.begin(), str.end(), '\t'), str.end());
}

static inline bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
    str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

static bool file_exists(const string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

static inline string absolutePathFromRelative(string relativePath){
    vector<string> pathComs = split(relativePath,'/');
    vector<string> absoPathVec;
    ostringstream oss;
    for(vector<string>::iterator it = pathComs.begin();it!=pathComs.end();it++){
        string path = *it;
        if(!path.compare("") || !path.compare("."))
            continue;
        if(!path.compare("..")){
            absoPathVec.pop_back();
        }
        else{
            absoPathVec.push_back(string("/")+path);
        }
    }
    copy(absoPathVec.begin(), absoPathVec.end(), ostream_iterator<string>(oss));
    return oss.str();
}

class ZombieCodeUtil{
public:
    static void setFilename(string fname,bool forceSet);
    static void appendObjcClsMethodImpl(bool isInstanceMethod,string cls,string selector,string filename,unsigned rangeFrom,unsigned rangeTo,string sourcecode);
    static void appendObjcMethodImplCall(bool isInstanceMethod,string cls,string selector,bool calleeIsInstanceMethod,string calleeCls,string calleeSel);
    static void appendObjcCls(string cls,string supCls,vector<string> protoVec);
    static void appendObjcClsInterf(string cls,bool isInstanceInterf,string selector);
    static void appendObjcProto(string proto,vector<string> refProto,bool isInSrcDir);
    static void appendObjcProtoInterf(string proto,bool isInstanceInterf,string selector);
    static void appendObjcAddNotificationCall(bool isInstanceMethod,string cls,string selector,bool calleeIsInstanceMethod,string calleeCls,string calleeSel,string notif);
    static void appendObjcPostNotificationCall(bool isInstanceMethod, string cls, string selector, string notif);
    static void appendObjcProtoInterfCall(bool isInstanceMethod,string cls,string selector,string proto,string protoSel);
    static void appendOpenUrl(string url);
    static bool writeJsonToFile(json j,string filename);
    static void synchronize();
};

#endif /* ZombieCodeUtil_hpp */
