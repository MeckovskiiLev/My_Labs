#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

namespace ArgumentParser {

class ArgParser {
public:
    
    ArgParser(const std::string& program_name);
    
    bool Parse(const std::vector<std::string>& args);
    
    ArgParser& AddStringArgument(const std::string& param);
    ArgParser& AddStringArgument(const char short_flag, const std::string& long_flag);
    ArgParser& AddStringArgument(const char short_flag, const std::string& long_flag, const std::string& declaration);

    ArgParser& AddIntArgument(const std::string& value);
    ArgParser& AddIntArgument(const char short_flag, const std::string& long_flag);
    ArgParser& AddIntArgument(const std::string& first_argument, const std::string& long_argument);
    ArgParser& AddIntArgument(const char short_flag, const std::string& long_flag, const std::string& declaration);

    ArgParser& AddFlag(const std::string& flag);
    ArgParser& AddFlag(const char short_flag, const std::string& long_flag);
    ArgParser& AddFlag(const std::string flag, const std::string declaration);
    ArgParser& AddFlag(const char short_flag, const std::string& long_flag, const std::string& declaration);

    ArgParser& AddHelp(const char short_flag, const std::string& long_flag, const std::string& declaration);
    ArgParser& AddHelp(const char short_flag, const std::string& long_flag);

    ArgParser& MultiValue();
    ArgParser& MultiValue(size_t value);

    ArgParser& StoreValues(std::vector<int>& values);
    ArgParser& StoreValue(bool& check);
    ArgParser& StoreValue(std::string& value);
    
    std::string GetStringValue(const std::string& param) const;
    int GetIntValue(const std::string& param) const;
    int GetIntValue(const std::string& param, int index);
    std::vector<std::string> CoutParamValue(const std::string& param) const;

    ArgParser& Default(const bool& flag_check);
    ArgParser& Default(const char* value);

    ArgParser& Positional();
    

    bool HasArgument(const std::string& param) const;
    
    const std::map<std::string, std::vector<std::string>>& GetArguments() const;
    const std::map<std::string, std::vector<int>>& GetIntArguments() const;
    bool CheckIfInt(const std::string& name);
    bool GetFlag(const std::string& param) const;
    const std::map<std::string, bool> GetFlags() const;
    const std::vector<std::string>& GetReqArr() const;
    const std::vector<std::string>& GetReqArrInt() const;

    const std::string HelpDescription();
    bool Help();
    
private:
    std::string parser_name;
    
    std::map<char, std::string> short_to_long_map = {
        // {'p', "param1"},
        // {'a', "param2"},
        // {'f',"flag1"}
        // {'a', "flag1"},
        // {'b', "flag2"},
        // {'c', "flag3"},
        //{'n', "number"},
        //{'f', "flag"},
        //{'h', "help"},
        //{'i', "input"},
        //{'s', "flag1"},
        //{'p', "flag2"},
        //{'o', "output"}
    };
    
    std::map<std::string, std::vector<std::string>> arguments;
    std::map<std::string, std::vector<int>> arguments_int;
    std::map<std::string, bool> flags;// {"flag1", "flag2", "flag3"};
    std::map<std::string, size_t> multi_vec;
    //std::map<std::string, bool> pos_map;

    std::vector<std::string> required_flags;// = {"flag1", "flag2", "flag3","flag", "Param1", "help", };
    std::vector<std::string> no_equal;// = {"number", "input", "param1", "param2", //  "test", "output", "first", "second"};      
    std::vector<std::string> no_equal_int;                                  
    std::vector<std::string> required_args;
    std::vector<std::string> int_required_args;// = {"param1", "param2", "test", "output", "first", "second"};//"flag", "flag1", "flag2", "flag3", "Param1", "help", , "input", "number"
    std::vector<std::string> store_values_vec;
    std::vector<int>* int_arguments = nullptr;

    
    std::string* stored_value = nullptr;
    std::string pos_arguments;
    std::string current_key;

    size_t min_arguments;

    bool is_multi_value = false; 
    bool multi_value_check = false;
    bool* flag_check; 
    bool positional_check = false;
    bool help_check = false;
    bool help_input = false;
    bool bool_store_values = false;
    //bool* help_check = false;
};

}




















