#pragma once
#include <map>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

class ConfigLoader{

private:
    //From https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
    // trim from start (in place)
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

public:
    using func_convert_t = std::function<void*(std::string&)>;
    using func_delete_t = std::function<void(void*)>;

public:
    ConfigLoader(){
    }

    ~ConfigLoader(){
        for(std::pair<std::string, func_convert_t> x: mConverterMap){
            if(mDataMap[x.first] != nullptr){
                mDeleteMap[x.first](mDataMap[x.first]);
                mDataMap[x.first] = nullptr;
            }
        }
    }

    int Load(const std::string& filename){
        std::string line;
        std::string key;
        std::string value;
        std::ifstream stream;
        stream.open(filename, std::ios::in);
        if(!stream.is_open()){
            return 1;
        }
        while(std::getline(stream, line)){
            size_t splitPos = line.find(":");
            if(splitPos !=  std::string::npos){
                key= line.substr(0, splitPos);
                value = line.substr(splitPos+1);
                trim(key);
                trim(value);
                if(mDataMap.find(key) != mDataMap.end()){
                    mDataMap[key] = mConverterMap[key](value);
                }else{
                    std::cout << "Ignoring key: " <<"(" << key << ")" << std::endl;
                }
            }
        }
        stream.close();
        return 0;
    }

    void Register(const std::string& key, func_convert_t& conv_func, func_delete_t& del_func){
        mDataMap[key] = nullptr;
        mConverterMap[key] = conv_func;
        mDeleteMap[key] = del_func;
    }

    template<typename T>
    T Fetch(const std::string& key){
        T tmp = T();
        if(mDataMap.find(key) == mDataMap.end())
            return tmp;
        if(mDataMap[key] == nullptr)
            return tmp;
        return *((T*)mDataMap[key]);
    }
    
private:
    std::map<std::string, void*> mDataMap;
    std::map<std::string, func_convert_t> mConverterMap;
    std::map<std::string, func_delete_t> mDeleteMap;
   
};

