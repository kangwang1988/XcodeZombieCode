#include <iostream>
#include <string>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <fstream>
#include <iterator>
#include "json.hpp"
#include "ZombieCodeUtil.hpp"

using namespace std;
using namespace nlohmann;

void appendUsedClsMethodCall(string clsMethod,string callerClsMethod,json &clsMethodJson,json &clsInterfHierachyJson,json &clsWithAnySrcCodeJson,json &usedClsMethodJson,json &unusedClsMethodJson);

string kKeyInterfSelDictFilename = "filename";
string kKeyInterfSelDictSourceCode = "sourceCode";
string kKeyInterfSelDictRange = "range";
string kKeyInterfSelDictCallees = "callee";
string kKeyInterfSelDictSuperClass = "superClass";
string kKeyInterfSelDictProtos = "protos";
string kKeyInterfSelDictInterfs = "interfs";
string kKeyInterfSelDictIsInSrcDir = "isInSrcDir";
string kKeyInterfSelDictNotifCallers = "notifCallers";

json implicitCallStackJson = {
    //System defined
    {"-[UICollectionViewLayout layoutAttributesClass]","+[UICollectionViewLayout alloc]"},
    {"-[UICollectionViewLayout invalidationContextClass]","+[UICollectionViewLayout alloc]"},
    {"-[UICollectionViewLayout prepareLayout]","+[UICollectionViewLayout alloc]"},
    {"-[UICollectionViewLayout layoutAttributesForElementsInRect:]","+[UICollectionViewLayout alloc]"},
    {"-[UICollectionViewLayout layoutAttributesForItemAtIndexPath:]","+[UICollectionViewLayout alloc]"},
    {"-[UICollectionViewLayout layoutAttributesForSupplementaryViewOfKind:atIndexPath:]","+[UICollectionViewLayout alloc]"},
    {"-[UICollectionViewLayout layoutAttributesForDecorationViewOfKind:atIndexPath:]","+[UICollectionViewLayout alloc]"},
    {"-[UICollectionViewLayout shouldInvalidateLayoutForBoundsChange]","+[UICollectionViewLayout alloc]"},
    {"-[UICollectionViewLayout invalidationContextForPreferredLayoutAttributes:withOriginalAttributes:]","+[UICollectionViewLayout alloc]"},
    {"-[UICollectionViewLayout targetContentOffsetForProposedContentOffset:withScrollingVelocity:]","+[UICollectionViewLayout alloc]"},
    {"-[UICollectionViewLayout targetContentOffsetForProposedContentOffset:]","+[UICollectionViewLayout alloc]"},
    {"-[UIResponder targetForAction:withSender:]","+[UIResponder alloc]"},
    {"-[UIResponder canPerformAction:withSender:]","+[UIResponder alloc]"},
    {"-[UIResponder remoteControlReceivedWithEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder motionCancelled:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder motionEnded:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder motionBegan:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder pressesCancelled:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder pressesEnded:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder pressesChanged:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder pressesBegan:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder touchesEstimatedPropertiesUpdated:]","+[UIResponder alloc]"},
    {"-[UIResponder touchesCancelled:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder touchesEnded:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder touchesMoved:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder touchesBegan:withEvent:]","+[UIResponder alloc]"},
    {"-[UIResponder isFirstResponder]","+[UIResponder alloc]"},
    {"-[UIResponder resignFirstResponder]","+[UIResponder alloc]"},
    {"-[UIResponder canResignFirstResponder]","+[UIResponder alloc]"},
    {"-[UIResponder becomeFirstResponder]","+[UIResponder alloc]"},
    {"-[UIResponder canBecomeFirstResponder]","+[UIResponder alloc]"},
    {"-[UIResponder nextResponder]","+[UIResponder alloc]"},
    {"-[UILabel textRectForBounds:limitedToNumberOfLines:]","+[UILabel alloc]"},
    {"-[UILabel drawTextInRect:]","+[UILabel alloc]"},
    {"-[UITextField borderRectForBounds:]","+[UITextField alloc]"},
    {"-[UITextField textRectForBounds:]","+[UITextField alloc]"},
    {"-[UITextField placeholderRectForBounds:]","+[UITextField alloc]"},
    {"-[UITextField editingRectForBounds:]","+[UITextField alloc]"},
    {"-[UITextField clearButtonRectForBounds:]","+[UITextField alloc]"},
    {"-[UITextField leftViewRectForBounds:]","+[UITextField alloc]"},
    {"-[UITextField rightViewRectForBounds:]","+[UITextField alloc]"},
    {"-[UITextField drawTextInRect:]","+[UITextField alloc]"},
    {"-[UITextField drawPlaceholderInRect:]","+[UITextField alloc]"},
    {"-[UIView alignmentRectForFrame:]","+[UIView alloc]"},
    {"-[UIView frameForAlignmentRect:]","+[UIView alloc]"},
    {"-[UIView alignmentRectInsets]","+[UIView alloc]"},
    {"-[UIView viewForBaselineLayout]","+[UIView alloc]"},
    {"-[UIView initWithFrame:]","-[UIView alloc]"},
    {"-[UIView layoutSubviews:]","+[UIView alloc]"},
    {"-[UIView drawRect:]","+[UIView alloc]"},
    {"+[UIView layerClass]","+[UIView alloc]"},
    {"-[UIView hitTest:withEvent:]","+[UIView alloc]"},
    {"-[UIView pointInside:withEvent:]","+[UIView alloc]"},
    {"-[UIView didAddSubview:]","+[UIView alloc]"},
    {"-[UIView willRemoveSubview:]","+[UIView alloc]"},
    {"-[UIView willMoveToSuperview:]","+[UIView alloc]"},
    {"-[UIView didMoveToSuperview]","+[UIView alloc]"},
    {"-[UIView willMoveToWindow:]","+[UIView alloc]"},
    {"-[UIView didMoveToWindow]","+[UIView alloc]"},
    {"-[UIView layoutSubviews]","+[UIView alloc]"},
    {"-[UIControl beginTrackingWithTouch:withEvent:]","+[UIControl alloc]"},
    {"-[UIControl continueTrackingWithTouch:withEvent:]","+[UIControl alloc]"},
    {"-[UIControl endTrackingWithTouch:withEvent:]","+[UIControl alloc]"},
    {"-[UIControl cancelTrackingWithEvent:]","+[UIControl alloc]"},
    {"-[UIControl setEnabled:]","+[UIControl alloc]"},
    {"-[UIControl setSelected:]","+[UIControl alloc]"},
    {"-[UIControl setSelected:animated:]","+[UIControl alloc]"},
    {"-[UIControl setHighlighted:]","+[UIControl alloc]"},
    {"-[UIControl setHighlighted:animated:]","+[UIControl alloc]"},
    {"-[UIViewController loadView]","+[UIViewController alloc]"},
    {"-[UIViewController loadViewIfNeeded]","+[UIViewController alloc]"},
    {"-[UIViewController viewDidLoad]","+[UIViewController alloc]"},
    {"-[UIViewController performSegueWithIdentifier:sender:]","+[UIViewController alloc]"},
    {"-[UIViewController shouldPerformSegueWithIdentifier:sender:]","+[UIViewController alloc]"},
    {"-[UIViewController prepareForSegue:sender:]","+[UIViewController alloc]"},
    {"-[UIViewController canPerformUnwindSegueAction:fromViewController:]","+[UIViewController alloc]"},
    {"-[UIViewController allowedChildViewControllersForUnwindingFromSource:]","+[UIViewController alloc]"},
    {"-[UIViewController childViewControllerContainingSegueSource:]","+[UIViewController alloc]"},
    {"-[UIViewController viewControllerForUnwindSegueAction:fromViewController:withSender:]","+[UIViewController alloc]"},
    {"-[UIViewController unwindForSegue:towardsViewController:]","+[UIViewController alloc]"},
    {"-[UIViewController segueForUnwindingToViewController:fromViewController:identifier:]","+[UIViewController alloc]"},
    {"-[UIViewController viewWillAppear:]","+[UIViewController alloc]"},
    {"-[UIViewController viewDidAppear:]","+[UIViewController alloc]"},
    {"-[UIViewController viewWillDisappear:]","+[UIViewController alloc]"},
    {"-[UIViewController viewDidDisappear:]","+[UIViewController alloc]"},
    {"-[UIViewController viewWillLayoutSubviews]","+[UIViewController alloc]"},
    {"-[UIViewController viewDidLayoutSubviews]","+[UIViewController alloc]"},
    {"-[UIViewController didReceiveMemoryWarning]","+[UIViewController alloc]"},
    {"-[UIViewController supportedInterfaceOrientations]","+[UIViewController alloc]"},
    {"-[UIViewController shouldAutorotate]","+[UIViewController alloc]"},
    {"-[UIViewController prefersStatusBarHidden]","+[UIViewController alloc]"},
    {"-[UIViewController preferredStatusBarUpdateAnimation]","+[UIViewController alloc]"},
    {"-[UIViewController modalTransitionStyle]","+[UIViewController alloc]"},
    {"-[UIViewController preferredStatusBarStyle]","+[UIViewController alloc]"},
    {"-[UIViewController willRotateToInterfaceOrientation:duration:]","+[UIViewController alloc]"},
    {"-[UIViewController didRotateFromInterfaceOrientation:]","+[UIViewController alloc]"},
    {"-[UIViewController willAnimateRotationToInterfaceOrientation:duration:]","+[UIViewController alloc]"},
    {"-[UIViewController willAnimateFirstHalfOfRotationToInterfaceOrientation:duration:]","+[UIViewController alloc]"},
    {"-[UIViewController didAnimateFirstHalfOfRotationToInterfaceOrientation:]","+[UIViewController alloc]"},
    {"-[UIViewController willAnimateSecondHalfOfRotationFromInterfaceOrientation:duration:]","+[UIViewController alloc]"},
    {"-[UITableViewCell setHighlighted:animated:]","+[UITableViewCell alloc]"},
    {"-[UITableViewCell setSelected:animated:]","+[UITableViewCell alloc]"},
    {"-[UITableViewCell initWithStyle:reuseIdentifier:]","+[UITableViewCell alloc]"},
    {"-[UITableViewCell initWithStyle:reuseIdentifier:]","+[UITableViewCell alloc]"},
    {"-[UITableViewCell initWithStyle:reuseIdentifier:]","+[UITableViewCell alloc]"},
    {"-[UITableViewCell prepareForReuse]","+[UITableViewCell alloc]"},
    {"-[UITableViewCell willTransitionToState:]","+[UITableViewCell alloc]"},
    {"-[UITableViewCell didTransitionToState:]","+[UITableViewCell alloc]"},
    {"-[NSObject init]","+[NSObject alloc]"},
    {"-[NSObject copyWithZone]","+[NSObject alloc]"},
    {"-[NSObject dealloc]","+[NSObject alloc]"},
    {"-[NSObject description]","+[NSObject alloc]"},
    {"-[NSObject debugDescription]","+[NSObject alloc]"},
    {"-[NSObject valueForKey:]","+[NSObject alloc]"},
    {"-[NSObject mutableArrayValueForKey:]","+[NSObject alloc]"},
    {"-[NSObject mutableOrderedSetValueForKey:]","+[NSObject alloc]"},
    {"-[NSObject mutableSetValueForKey:]","+[NSObject alloc]"},
    {"-[NSObject valueForKeyPath:]","+[NSObject alloc]"},
    {"-[NSObject mutableArrayValueForKeyPath:]","+[NSObject alloc]"},
    {"-[NSObject mutableOrderedSetValueForKeyPath:]","+[NSObject alloc]"},
    {"-[NSObject mutableSetValueForKeyPath:]","+[NSObject alloc]"},
    {"-[NSObject valueForUndefinedKey:]","+[NSObject alloc]"},
    {"-[NSObject dictionaryWithValuesForKeys:]","+[NSObject alloc]"},
    {"+[NSObject load]","+[NSObject alloc]"},
    {"+[NSObject initialize]","+[NSObject alloc]"},
    {"-[NSOperation start]","+[NSOperation alloc]"},
    {"-[NSOperation main]","+[NSOperation alloc]"},
    {"-[NSOperation resume]","+[NSOperation alloc]"},
    {"-[NSOperation finish]","+[NSOperation alloc]"},
    {"-[NSOperation isCancelled]","+[NSOperation alloc]"},
    {"-[NSOperation isFinished]","+[NSOperation alloc]"},
    {"-[NSOperation isReady]","+[NSOperation alloc]"},
    {"-[NSOperation isPaused]","+[NSOperation alloc]"}
};

typedef enum{
    ClsMethodTokenMethodType,
    ClsMethodTokenClass,
    ClsMethodTokenSel
}ClsMethodTokenType;

string joinedClsMethod(bool isInstanceMethod,string cls,string sel){
    return string(isInstanceMethod?"-":"+")+"["+cls+" "+sel+"]";
}

string getClsMethodToken(string clsMethod,ClsMethodTokenType tokenType){
    clsMethod = trim(clsMethod);
    switch (tokenType) {
        case ClsMethodTokenMethodType:
        {
            size_t pos = clsMethod.find("[");
            string str = clsMethod.substr(0,pos);
            if(pos != string::npos)
                return trim(str);
            break;
        }
        case ClsMethodTokenClass:
        {
            size_t pos = clsMethod.find("[");
            if(pos != string::npos){
                string str = clsMethod.substr(pos+1,clsMethod.length()-pos+1);
                pos = str.find(" ");
                if(pos != string::npos){
                    str = str.substr(0,pos);
                    return trim(str);
                }
            }
            break;
        }
        case ClsMethodTokenSel:
        {
            size_t pos = clsMethod.rfind(" ");
            if(pos != string::npos){
                string str = clsMethod.substr(pos+1,clsMethod.length()-pos-2);
                return trim(str);
            }
            break;
        }
        default:
            break;
    }
    return "";
}

string exec(const char* cmd) {
    char buffer[128];
    string result = "";
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

json readJsonFromFile(const string& file){
    ifstream ifs(file);
    string str((istreambuf_iterator<char>(ifs)),
                    istreambuf_iterator<char>());
    return json::parse(str);
}

template<class T>
vector<T> mergeVector(vector<T> vec1,vector<T> vec2){
    vector<T> mergedVec;
    mergedVec.reserve(vec1.size() + vec2.size() );
    mergedVec.insert( mergedVec.end(), vec1.begin(), vec1.end() );
    mergedVec.insert( mergedVec.end(), vec2.begin(), vec2.end() );
    sort( mergedVec.begin(), mergedVec.end() );
    mergedVec.erase(unique( mergedVec.begin(), mergedVec.end() ), mergedVec.end() );
    return mergedVec;
}

int writeJsonToFile(json j,const string & file){
    fstream fs;
    string clsMethodJsonFile = file;
    fs.open(clsMethodJsonFile,ofstream::out | ofstream::trunc);
    if(!j.is_null())
        fs<<j;
    fs.close();
    return 0;
}

vector<string> jsonPartFiles(string folderDir,string suffix){
    stringstream ss;
    ss<<"find "<<folderDir<<" -type f -name \"*."<<suffix<<"\"";
    string findOpt = exec(ss.str().c_str());
    return split(findOpt,'\n');
}

json joinJsonPartFiles(vector<string> splittedElems,json &dupClsMethodJson){
    json allJson;
    for(vector<string>::iterator it=splittedElems.begin();it!=splittedElems.end();++it){
        json jpj = readJsonFromFile(*it);
        if(jpj.is_null())
            continue;
        for (json::iterator it = jpj.begin(); it != jpj.end(); ++it) {
            string key = it.key();
            json valueNew = it.value();
            if(allJson.find(key)==allJson.end()){
                allJson[key]=valueNew;
                continue;
            }
            json valueOld = json(allJson[key]);
            if(valueOld.is_null() || valueNew.is_null()){
                allJson[key]=(valueOld.is_null()?valueNew:valueOld);
                continue;
            }
            if(valueOld.type()!=valueNew.type()){
                continue;
            }
            if(valueOld.is_string() && valueNew.is_string()){
                continue;
            }
            if(valueOld.is_array() && valueNew.is_array()){
                vector<string> vecAB = mergeVector(valueOld.get<vector<string>>(), valueNew.get<vector<string>>());
                valueNew = json();
                for(vector<string>::iterator it = vecAB.begin();it!=vecAB.end();it++)
                    valueNew.push_back(*it);
                allJson[key]=valueNew;
                continue;
            }
            for(json::iterator itOld = valueOld.begin();itOld!=valueOld.end();itOld++){
                string subOldKey = itOld.key();
                json subOldValue = itOld.value();
                if(valueNew.find(subOldKey)==valueNew.end()){
                    valueNew[subOldKey]=subOldValue;
                    continue;
                }
                json subNewValue = valueNew[subOldKey];
                if(subOldValue.is_null() || subNewValue.is_null()){
                    valueNew[subOldKey]=(subOldValue.is_null()?subNewValue:subOldValue);
                    continue;
                }
                if(subOldValue.type()!=subNewValue.type()){
                    continue;
                }
                if(subOldValue.is_array() && subNewValue.is_array()){
                    vector<string> vecAB = mergeVector(subOldValue.get<vector<string>>(), subNewValue.get<vector<string>>());
                    subNewValue = json();
                    for(vector<string>::iterator it = vecAB.begin();it!=vecAB.end();it++)
                        subNewValue.push_back(*it);
                    valueNew[subOldKey]=subNewValue;
                    continue;
                }
                if(subOldValue.is_string() && subNewValue.is_string()){
                    if(!subOldValue.get<string>().compare(subNewValue.get<string>())){
                    }
                    else if(!subOldValue.get<string>().length() || !subNewValue.get<string>().length()){
                        if(!subNewValue.get<string>().length()){
                            subNewValue=subOldValue;
                            valueNew[subOldKey]=subNewValue;
                        }
                    }
                    else if(!subOldKey.compare(kKeyInterfSelDictFilename) ||
                            !subOldKey.compare(kKeyInterfSelDictRange) ||
                            !subOldKey.compare(kKeyInterfSelDictSourceCode)){
                        json cmJson =json(dupClsMethodJson[key]);
                        json fnJson = json(cmJson[subOldKey]);
                        vector<string> fnVec;
                        if(fnJson.is_array())
                            fnVec = fnJson.get<vector<string>>();
                        if(find(fnVec.begin(),fnVec.end(),subOldValue)==fnVec.end())
                            fnJson.push_back(subOldValue);
                        if(find(fnVec.begin(),fnVec.end(),subNewValue)==fnVec.end())
                            fnJson.push_back(subNewValue);
                        cmJson[subOldKey] = fnJson;
                        dupClsMethodJson[key]=cmJson;
                    }
                    else{
                    }
                    continue;
                }
            }
            allJson[key]=valueNew;
        }
    }
    return allJson;
}

json analyzeClsJsonWithAnySrcCode(json &clsMethodJson){
    vector<string> clsVector;
    for(json::iterator it = clsMethodJson.begin();it!=clsMethodJson.end();it++){
        string clsMethod = it.key();
        json clsMethodInfo = it.value();
        string cls = getClsMethodToken(clsMethod, ClsMethodTokenClass);
        if(clsMethodInfo.find(kKeyInterfSelDictSourceCode)!=clsMethodInfo.end() && find(clsVector.begin(),clsVector.end(),cls)==clsVector.end()){
            clsVector.push_back(cls);
        }
    }
    return json(clsVector);
}

int filterJsonWithSrcCodeOption(json &json4Filter,json &clsMethodJson,bool anySrcCode){
    int erasedCnt = 0;
    for(json::iterator it = json4Filter.begin();it!=json4Filter.end();){
        string clsMethod = it.key();
        json clsMethodInfo = json(json(clsMethodJson[clsMethod])[kKeyInterfSelDictSourceCode]);
        string clsMethodSrcCode = "";
        if(clsMethodInfo.is_string())
            clsMethodSrcCode = clsMethodInfo.get<string>();
        if((anySrcCode && !clsMethodSrcCode.length()) ||
           (!anySrcCode && clsMethodSrcCode.length())){
            it=json4Filter.erase(it);
            erasedCnt++;
        }
        else
            ++it;
    }
    return erasedCnt;
}

json abbrClsMethodsJsonFromClsMethodJson(json &clsMethodJson){
    json abbrClsMethods;
    for(json::iterator it=clsMethodJson.begin();it!=clsMethodJson.end();it++){
        string clsMethod = it.key();
        string isInstanceType = getClsMethodToken(clsMethod,ClsMethodTokenMethodType);
        string cls = getClsMethodToken(clsMethod, ClsMethodTokenClass);
        string sel = getClsMethodToken(clsMethod, ClsMethodTokenSel);
        json methodJson = json(abbrClsMethods[cls]);
        vector<string> methodVec;
        if(methodJson.is_array())
            methodVec = methodJson.get<vector<string>>();
        if(find(methodVec.begin(), methodVec.end(),sel)==methodVec.end()){
            methodJson.push_back(isInstanceType+sel);
        }
        abbrClsMethods[cls]=methodJson;
    }
    return abbrClsMethods;
}

void appendUsedClsMethodCallees(string clsMethod,json &clsMethodJson,json &clsInterfHierachyJson, json &clsWithAnySrcCodeJson,json &usedClsMethodJson,json &unusedClsMethodJson){
    json callees = json(json(clsMethodJson[clsMethod])[kKeyInterfSelDictCallees]);
    for(json::iterator it = callees.begin();it!=callees.end();it++){
        string calleeClsMethod = it.value();
        string clsCallee = getClsMethodToken(calleeClsMethod, ClsMethodTokenClass);
        appendUsedClsMethodCall(calleeClsMethod, clsMethod,clsMethodJson,clsInterfHierachyJson, clsWithAnySrcCodeJson,usedClsMethodJson,unusedClsMethodJson);
    }
}

void appendClsAllocMethod(string clsName,string callerClsMethod,json &clsMethodJson,json &clsInterfHierachyJson,json &clsWithAnySrcCodeJson,json &usedClsMethodJson,json &unusedClsMethodJson){
    while(clsName.length() && clsName.compare("NSObject")){
        string clsAllocKey = string("+[")+clsName+" alloc]";
        if(usedClsMethodJson.find(clsAllocKey)==usedClsMethodJson.end()){
            usedClsMethodJson[clsAllocKey]=callerClsMethod;
            appendUsedClsMethodCallees(clsAllocKey,clsMethodJson, clsInterfHierachyJson, clsWithAnySrcCodeJson,usedClsMethodJson, unusedClsMethodJson);
        }
        json supClassJson = json(json(clsInterfHierachyJson[clsName])[kKeyInterfSelDictSuperClass]);
        clsName = supClassJson.is_string()?supClassJson.get<string>():"";
    }
}

void appendUsedClsMethodCall(string clsMethod,string callerClsMethod,json &clsMethodJson,json &clsInterfHierachyJson,json &clsWithAnySrcCodeJson,json &usedClsMethodJson,json &unusedClsMethodJson){
    string clsMethodType = getClsMethodToken(clsMethod, ClsMethodTokenMethodType);
    string clsName = getClsMethodToken(clsMethod, ClsMethodTokenClass);
    string clsMethodSel = getClsMethodToken(clsMethod, ClsMethodTokenSel);
    json tempJson = json(json(clsInterfHierachyJson[clsName])[kKeyInterfSelDictInterfs]);
    vector<string> clsInterfsVec = tempJson.is_array()?tempJson.get<vector<string>>():vector<string>();
    if(!clsName.length() || !clsMethodSel.length()){
        return;
    }
    if(usedClsMethodJson.find(clsMethod)!=usedClsMethodJson.end())
        return;
    if(!clsMethodType.compare("+") && !clsMethodSel.compare("alloc")){
        appendClsAllocMethod(clsName, callerClsMethod,clsMethodJson,clsInterfHierachyJson,clsWithAnySrcCodeJson,usedClsMethodJson, unusedClsMethodJson);
    }
    string exactClsMethod;
    if(clsMethodJson.find(clsMethod)!=clsMethodJson.end() || find(clsInterfsVec.begin(),clsInterfsVec.end(),clsMethod)!=clsInterfsVec.end()){
        exactClsMethod = clsMethod;
    }
    else{
        string refCls = clsName;
        bool found = false;
        do{
            tempJson = json(json(clsInterfHierachyJson[refCls])[kKeyInterfSelDictInterfs]);
            string refClsMethod = joinedClsMethod(!clsMethodType.compare("-"), refCls, clsMethodSel);
            vector<string> clsInterfVec = tempJson.is_array()?tempJson.get<vector<string>>():vector<string>();
            if(clsMethodJson.find(refClsMethod)!=clsMethodJson.end() || find(clsInterfVec.begin(),clsInterfVec.end(),refClsMethod)!=clsInterfVec.end()){
                exactClsMethod = refClsMethod;
                found = true;
            }
            json supClassJson = json(json(clsInterfHierachyJson[refCls])[kKeyInterfSelDictSuperClass]);
            if(!refCls.compare("NSObject"))
                break;
            refCls = (supClassJson.is_string()?supClassJson.get<string>():"");
        }while(!found && refCls.length());
    }
    if(exactClsMethod.length()){
        usedClsMethodJson[exactClsMethod] = callerClsMethod;
        clsMethodType = getClsMethodToken(exactClsMethod, ClsMethodTokenMethodType);
        clsName = getClsMethodToken(exactClsMethod, ClsMethodTokenClass);
        clsMethodSel = getClsMethodToken(exactClsMethod, ClsMethodTokenSel);
        appendClsAllocMethod(clsName, callerClsMethod,clsMethodJson,clsInterfHierachyJson,clsWithAnySrcCodeJson,usedClsMethodJson, unusedClsMethodJson);
        string clsAllocKey = joinedClsMethod(!clsMethodType.compare("-"), clsName, "alloc");
        if(!clsMethodType.compare("-") && usedClsMethodJson.find(clsAllocKey)==usedClsMethodJson.end()){
            usedClsMethodJson[clsAllocKey]=callerClsMethod;
            appendUsedClsMethodCallees(clsAllocKey,clsMethodJson, clsInterfHierachyJson, clsWithAnySrcCodeJson,usedClsMethodJson, unusedClsMethodJson);
        }
        if(unusedClsMethodJson.find(exactClsMethod)!=unusedClsMethodJson.end())
            unusedClsMethodJson.erase(exactClsMethod);
    }
    else
        return;
    appendUsedClsMethodCallees(exactClsMethod,clsMethodJson,clsInterfHierachyJson,clsWithAnySrcCodeJson,usedClsMethodJson,unusedClsMethodJson);
}

json analyzeRepeatCodeOfClsMethodJson(json &clsMethodJson){
    json hashClsMethodMap;
    stringstream ss;
    for(json::iterator it = clsMethodJson.begin();it!=clsMethodJson.end();){
        ss.str(string());
        string clsMethod = it.key();
        json clsMethodInfoJson = it.value();
        if(clsMethodInfoJson.find(kKeyInterfSelDictSourceCode)==clsMethodInfoJson.end()){
            if(clsMethodInfoJson.find(kKeyInterfSelDictCallees)==clsMethodInfoJson.end())
                it = clsMethodJson.erase(it);
            else
                it++;
            continue;
        }
        string clsMethodSrcCode = clsMethodInfoJson[kKeyInterfSelDictSourceCode];
        ss<<hash<string>{}(clsMethodSrcCode);
        string key = ss.str();
        json srcHashJson = json(hashClsMethodMap[key]);
        vector<string> srcHashVector;
        if(srcHashJson.is_array()){
            srcHashVector = srcHashJson.get<vector<string>>();
        }
        if(find(srcHashVector.begin(),srcHashVector.end(),clsMethod)==srcHashVector.end()){
            srcHashJson.push_back(clsMethod);
        }
        hashClsMethodMap[key]=srcHashJson;
        it++;
    }
    json repeatCodeJson;
    for(json::iterator it = hashClsMethodMap.begin();it!=hashClsMethodMap.end();it++){
        json value = it.value();
        if(value.size()>1){
            repeatCodeJson[it.key()]=it.value();
        }
    }
    return repeatCodeJson;
}

string searchUsedCallerByClassWithSpecificProtocol(string clsMethod,string originCls,string byCls,string specificProtocol,json &clsInterfHierachyJson,json &protoInterfHierachyJson,json &protoInterfCallJson,json &usedClsMethodJson){
    string methodType = getClsMethodToken(clsMethod, ClsMethodTokenMethodType);
    string sel = getClsMethodToken(clsMethod, ClsMethodTokenSel);
    json tempJson = json(json(protoInterfHierachyJson[specificProtocol])[kKeyInterfSelDictInterfs]);
    vector<string> protoAPIVec = tempJson.is_array()?tempJson.get<vector<string>>():vector<string>();
    string clsAllocKey = string("+")+"["+originCls+" "+"alloc]";
    json protoInfoJson = json(protoInterfHierachyJson[specificProtocol]);
    string protoIsInSrcDirStr = "0";
    if(protoInfoJson.find(kKeyInterfSelDictIsInSrcDir)!=protoInfoJson.end() && protoInfoJson[kKeyInterfSelDictIsInSrcDir].is_string())
        protoIsInSrcDirStr = protoInfoJson[kKeyInterfSelDictIsInSrcDir].get<string>();
    if(!specificProtocol.compare("MTLManagedObjectSerializing") ||
        !specificProtocol.compare("MTLJSONSerializing") ||
        !specificProtocol.compare("AMapNaviManagerDelegate") ||
        !specificProtocol.compare("CrashlyticsDelegate") ||
        !specificProtocol.compare("AidProtocolDelegate") ||
        !specificProtocol.compare("IFlySpeechSynthesizerDelegate") ||
        !specificProtocol.compare("MAMapViewDelegate") ||
        !specificProtocol.compare("MAOverlay") ||
        !specificProtocol.compare("UTICrashCaughtListener")
       )
            protoIsInSrcDirStr = "0";
    string protocolClsMethod = joinedClsMethod(!methodType.compare("-"), specificProtocol,sel);
    string auxProtocolClsMethod = joinedClsMethod(methodType.compare("-"), specificProtocol,sel);
    if( (!methodType.compare("+") || usedClsMethodJson.find(clsAllocKey)!=usedClsMethodJson.end())){
        //系统级别Delegate
        if(!protoIsInSrcDirStr.compare("0") &&
           (find(protoAPIVec.begin(),protoAPIVec.end(),protocolClsMethod)!=protoAPIVec.end() ||
            find(protoAPIVec.begin(),protoAPIVec.end(),auxProtocolClsMethod)!=protoAPIVec.end()))
            return clsAllocKey;
        json protocolClsMethodCallerJson = protoInterfCallJson[protocolClsMethod];
        if(!protocolClsMethodCallerJson.is_array())
            protocolClsMethodCallerJson = protoInterfCallJson[auxProtocolClsMethod];
        //用户自定义Delegate
        if(!protoIsInSrcDirStr.compare("1") && protocolClsMethodCallerJson.is_array()){
            for(json::iterator it = protocolClsMethodCallerJson.begin();it!=protocolClsMethodCallerJson.end();it++){
                string caller = *it;
                if(usedClsMethodJson.find(caller)!=usedClsMethodJson.end())
                    return caller;
            }
        }
    }
    if(!specificProtocol.compare("MTLJSONSerializing") && (has_suffix(sel,"JSONTransformer")) && sel.find(":")==string::npos){
        return clsAllocKey;
    }
    if(!specificProtocol.compare("NSObject"))
        return "";
    json protoProtos = json(json(protoInterfHierachyJson[specificProtocol])[kKeyInterfSelDictProtos]);
    for(json::iterator it = protoProtos.begin();it!=protoProtos.end();it++){
        string callerClsMethod = searchUsedCallerByClassWithSpecificProtocol(clsMethod, originCls, byCls, *it, clsInterfHierachyJson, protoInterfHierachyJson, protoInterfCallJson, usedClsMethodJson);
        if(callerClsMethod.length())
            return callerClsMethod;
    }
    return "";
}

//沿着继承层次结构向上检查各祖先protocol
string searchUsedCallerByClassWithProtocols(string clsMethod,string originCls,string byCls,json &clsInterfHierachyJson,json &protoInterfHierachyJson,json &protoInterfCallJson,json &usedClsMethodJson){
    string methodType = getClsMethodToken(clsMethod,ClsMethodTokenMethodType);
    string sel = getClsMethodToken(clsMethod,ClsMethodTokenSel);
    if(!byCls.length() || !sel.length()){
        return "";
    }
    //TODO:Protocol的继承关系那里可能有坑
    json clsProtocols = json(json(clsInterfHierachyJson[byCls])[kKeyInterfSelDictProtos]);
    json supClassJson = json(json(clsInterfHierachyJson[byCls])[kKeyInterfSelDictSuperClass]);
    string supClass = (supClassJson.is_string()?supClassJson.get<string>():"");
    for(json::iterator protoIt = clsProtocols.begin();protoIt!=clsProtocols.end();protoIt++){
        string specificProtocol = *protoIt;
        string callerClsMethod = searchUsedCallerByClassWithSpecificProtocol(clsMethod, originCls, byCls, specificProtocol, clsInterfHierachyJson, protoInterfHierachyJson, protoInterfCallJson, usedClsMethodJson);
        if(callerClsMethod.length())
            return callerClsMethod;
    }
    if(!byCls.compare("NSObject"))
        return "";
    return searchUsedCallerByClassWithProtocols(joinedClsMethod(!methodType.compare("-"),supClass, sel),originCls,supClass,clsInterfHierachyJson,protoInterfHierachyJson,protoInterfCallJson,usedClsMethodJson);
}

//沿着继承层次向上检查各祖先接口以及隐含的调用关系
string searchUsedCallerByClassWithInterfAndImplicitCalls(string clsMethod,string originCls,string byCls,json &clsInterfHierachyJson,json &usedClsMethodJson){
    string methodType = getClsMethodToken(clsMethod,ClsMethodTokenMethodType);
    string sel = getClsMethodToken(clsMethod,ClsMethodTokenSel);
    if(!byCls.length() || !sel.length()){
        return "";
    }
    json supClassJson =json(json(clsInterfHierachyJson[byCls])[kKeyInterfSelDictSuperClass]);
    string clsAllocKey = string("+")+"["+originCls+" "+"alloc]";
    string byClsMethod = joinedClsMethod(!methodType.compare("-"), byCls, sel);
    if((!methodType.compare("+") || usedClsMethodJson.find(clsAllocKey)!=usedClsMethodJson.end())){
        string byClsMethodCaller = "";
        if(implicitCallStackJson.find(byClsMethod)!=implicitCallStackJson.end())
            byClsMethodCaller = implicitCallStackJson[byClsMethod];
        if(!byClsMethodCaller.length() && usedClsMethodJson.find(byClsMethod)!=usedClsMethodJson.end())
            byClsMethodCaller = usedClsMethodJson[byClsMethod];
        if(!sel.compare("alloc"))
            return clsAllocKey;
        if(byClsMethodCaller.length())
            return byClsMethodCaller;
    }
    if(!byCls.compare("NSObject"))
        return "";
    string supClass = (supClassJson.is_string()?supClassJson.get<string>():"");
    return searchUsedCallerByClassWithInterfAndImplicitCalls(joinedClsMethod(!methodType.compare("-"),supClass, sel),originCls,supClass,clsInterfHierachyJson,usedClsMethodJson);
}

//在Notification中查看调用关系
string searchUsedCallerByNotification(string& clsMethod,json& clsMethodAddNotifsJson,json& notifPostedCallersJson,json& usedClsMethodJson){
    if(clsMethodAddNotifsJson.find(clsMethod)==clsMethodAddNotifsJson.end())
        return "";
    json clsMethodNotifJson = clsMethodAddNotifsJson[clsMethod];
    for(json::iterator it = clsMethodNotifJson.begin();it!=clsMethodNotifJson.end();it++){
        string notif = it.key();
        json addNotifCallerJson = it.value();
        json notifCallersJson = notifPostedCallersJson[notif];
        for(json::iterator it = addNotifCallerJson.begin(); it!=addNotifCallerJson.end();it++){
            string addNotifCaller = it.value();
            //AddObserver caller Called
            if(usedClsMethodJson.find(addNotifCaller)!=usedClsMethodJson.end()){
                //PostObserver caller called
                for(json::iterator it = notifCallersJson.begin();it!=notifCallersJson.end();it++){
                    string postNotifCaller = it.value();
                    if(usedClsMethodJson.find(postNotifCaller)!=usedClsMethodJson.end()){
                        return postNotifCaller;
                    }
                }
            }
        }
    }
    return "";
}


int main(int argc,char *argv[]){
    if(argc!=3){
        cout<<"Usage:"<<"postanalyze your-path-of-jsonparts-for-analyzing your-appdelegate-name"<<endl;
        return -1;
    }
    string folder(argv[1]);
    json dupClsMethodJson;
    json clsMethodJson = joinJsonPartFiles(jsonPartFiles(folder,"clsMethod.jsonpart"),dupClsMethodJson);
    writeJsonToFile(clsMethodJson,folder+"/clsMethod.json");
    writeJsonToFile(dupClsMethodJson,folder+"/dupClsMethod.json");
    
    json dupClsInterfHierachyJson;
    json clsInterfHierachyJson =  joinJsonPartFiles(jsonPartFiles(folder,"clsInterfHierachy.jsonpart"),dupClsInterfHierachyJson);
    writeJsonToFile(clsInterfHierachyJson,folder+"/clsInterfHierachy.json");
    writeJsonToFile(dupClsInterfHierachyJson,folder+"/dupClsInterfHierachy.json");
    
    json dupProtoInterfHierachyJson;
    json protoInterfHierachyJson = joinJsonPartFiles(jsonPartFiles(folder,"protoInterfHierachy.jsonpart"),dupProtoInterfHierachyJson);
    writeJsonToFile(protoInterfHierachyJson,folder+"/protoInterfHierachy.json");
    writeJsonToFile(dupProtoInterfHierachyJson,folder+"/dupProtoInterfHierachy.json");
    
    json dupClsMethodAddNotifsJson;
    json clsMethodAddNotifsJson = joinJsonPartFiles(jsonPartFiles(folder,"clsMethodAddNotifs.jsonpart"),dupClsMethodAddNotifsJson);
    writeJsonToFile(clsMethodAddNotifsJson,folder+"/clsMethodAddNotifs.json");
    writeJsonToFile(dupClsMethodAddNotifsJson,folder+"/dupClsMethodAddNotifs.json");
    
    json dupNotifPostedCallersJson;
    json notifPostedCallersJson = joinJsonPartFiles(jsonPartFiles(folder,"notifPostedCallers.jsonpart"),dupNotifPostedCallersJson);
    writeJsonToFile(notifPostedCallersJson,folder+"/notifPostedCallers.json");
    writeJsonToFile(dupNotifPostedCallersJson,folder+"/dupNotifPostedCallers.json");
    
    json dupProtoInterfCallJson;
    json protoInterfCallJson =  joinJsonPartFiles(jsonPartFiles(folder,"protoInterfCall.jsonpart"),dupProtoInterfCallJson);
    writeJsonToFile(protoInterfCallJson,folder+"/protoInterfCall.json");
    writeJsonToFile(dupProtoInterfCallJson,folder+"/dupProtoInterfCall.json");
    
    json clsWithAnySrcCodeJson = analyzeClsJsonWithAnySrcCode(clsMethodJson);
    writeJsonToFile(clsWithAnySrcCodeJson,folder+"/clsWithAnySrcCode.json");
    writeJsonToFile(analyzeRepeatCodeOfClsMethodJson(clsMethodJson),folder+"/repeatCode.json");
    string appDelegateAlloc = string("+[")+argv[2]+" alloc]";
    json unusedClsMethodJson = json(clsMethodJson);
    json usedClsMethodJson = {{appDelegateAlloc,"-[UIApplication main]"},{"-[UIApplication main]","-[UIApplication main]"},
        {"+[NSObject alloc]","-[UIApplication main]"},
    };
    
    bool findAny = false;
    do{
        findAny = false;
        string clsMethod,callerClsMethod;
        for(json::iterator it = unusedClsMethodJson.begin();it!=unusedClsMethodJson.end();){
            //处理形如<UIApplicationDelegate>这种
            clsMethod = it.key();
            if(usedClsMethodJson.find(clsMethod)!=usedClsMethodJson.end()){
                it = unusedClsMethodJson.erase(it);
                cout<<"[KWLM]Erase Count Remains:"<<unusedClsMethodJson.size()<<endl;
                continue;
            }
            callerClsMethod = searchUsedCallerByClassWithProtocols(clsMethod,getClsMethodToken(clsMethod,ClsMethodTokenClass),getClsMethodToken(clsMethod,ClsMethodTokenClass),clsInterfHierachyJson,protoInterfHierachyJson,protoInterfCallJson,usedClsMethodJson);
            if(!callerClsMethod.length()){
                callerClsMethod = searchUsedCallerByClassWithInterfAndImplicitCalls(clsMethod,getClsMethodToken(clsMethod,ClsMethodTokenClass),getClsMethodToken(clsMethod,ClsMethodTokenClass),clsInterfHierachyJson,usedClsMethodJson);
            }
            if(!callerClsMethod.length()){
                callerClsMethod = searchUsedCallerByNotification(clsMethod, clsMethodAddNotifsJson,notifPostedCallersJson,usedClsMethodJson);
            }
            if(callerClsMethod.length()){
                findAny = true;
                break;
            }
            it++;
        }
        if(findAny){
            appendUsedClsMethodCall(clsMethod, callerClsMethod,clsMethodJson,clsInterfHierachyJson,clsWithAnySrcCodeJson,usedClsMethodJson,unusedClsMethodJson);
            cout<<"[KWLM]Append Count Remains:"<<unusedClsMethodJson.size()<<endl;
        }
    }while(findAny);
    writeJsonToFile(usedClsMethodJson,folder+"/usedClsMethod.json");
    filterJsonWithSrcCodeOption(unusedClsMethodJson, clsMethodJson, true);
    writeJsonToFile(unusedClsMethodJson,folder+"/unusedClsMethod.json");
    json unusedAbbrClsMethod = abbrClsMethodsJsonFromClsMethodJson(unusedClsMethodJson);
    json abbrClsMethod = abbrClsMethodsJsonFromClsMethodJson(clsMethodJson);
    json unusedClsJson;
    for(json::iterator it = unusedAbbrClsMethod.begin();it!=unusedAbbrClsMethod.end();it++){
        string unusedCls = it.key();
        json unusedMethodsJson = it.value(),allMethodsJson = abbrClsMethod[unusedCls];
        vector<string> unusedMethodVec,allMethodsVec;
        ostringstream unusedStream,allStream;
        string unusedStr,allStr;
        if(unusedMethodsJson.is_array())
            unusedMethodVec = unusedMethodsJson.get<vector<string>>();
        if(allMethodsJson.is_array())
            allMethodsVec = allMethodsJson.get<vector<string>>();
        sort(unusedMethodVec.begin(),unusedMethodVec.end());
        sort(allMethodsVec.begin(),allMethodsVec.end());
        copy(unusedMethodVec.begin(), unusedMethodVec.end(), ostream_iterator<string>(unusedStream));
        copy(allMethodsVec.begin(), allMethodsVec.end(), ostream_iterator<string>(allStream));
        if(!unusedStream.str().compare(allStream.str())){
            unusedClsJson.push_back(unusedCls);
        }
    }
    writeJsonToFile(unusedClsJson,folder+"/unusedCls.json");
    return 0;
}
