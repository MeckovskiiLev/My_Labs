#include "ArgParser.h"

namespace ArgumentParser {

    ArgParser::ArgParser(const std::string& name): parser_name(name), arguments(){}

    bool ArgParser::Parse(const std::vector<std::string>& args) {
            if (args.empty()) {
                std::cout << "Not enough arguments" << std::endl;
                return false;
            }

            
            

            for (int i = 0; i < args.size(); ++i) {
                auto arg = args[i];
                // if (arg == "--help" || arg == "-h") {
                //     std::cout << HelpDescription() << "\n";
                //     return true; 
                // }

                if (arg.find("--") == 0) {
                    std::string name_of_param = arg.substr(2);
                    auto index_of_eq = arg.find('=');
                    
                        if (index_of_eq != std::string::npos) {
                            std::string name_of_param = arg.substr(2, index_of_eq - 2);
                            std::string value = arg.substr(index_of_eq + 1);
                            if (std::find(required_args.begin(), required_args.end(), name_of_param) != required_args.end()) {
                                // if (arguments_int.find(name_of_param) != arguments_int.end()) {
                                //     if (CheckIfInt(value)) {
                                //         arguments_int[name_of_param].push_back(std::stoi(value));
                                //     } else {
                                //         std::cerr << "Value for Int argument was not an int value!";
                                //         return false;
                                //     } 
                                // } else {
                                    arguments[name_of_param].push_back(value);
                                //}
                            } else {
                                return false;
                            }
                        }  else {
                            if (std::find(no_equal.begin(), no_equal.end(), name_of_param) == no_equal.end()) {
                                if (std::find(required_flags.begin(), required_flags.end(), name_of_param) != required_flags.end()) {
                                    flags[name_of_param] = true;
                                    if (name_of_param == "help") {
                                        help_input = true;
                                    }
                                    
                                } else {
                                    return false;
                                }
                            }else if (std::find(no_equal.begin(), no_equal.end(), name_of_param) != no_equal.end()){
                                if (i + 1 < args.size()) {
                                    // if (arguments_int.find(name_of_param) != arguments_int.end()) {
                                    //     if (CheckIfInt(args[i+1])) {
                                    //         arguments_int[name_of_param].push_back(std::stoi(args[i+1]));
                                    //     } else {
                                    //         std::cerr << "Value for Int argument was not an int value!";
                                    //         return false;
                                    //     } 
                                    // } else {
                                        arguments[name_of_param].push_back(args[i+1]);
                                    //}
                                    i++;
                                } else {
                                    return false;
                                }
                                
                            } 
                            
                            else {
                                return false;
                            }
                        }
                    
                    
                } else if (arg[0] == '-' && arg.size() > 1) {
                    
                    auto index_of_eq = arg.find('=');
                    if (index_of_eq != std::string::npos) {
                        
                        auto short_arg = arg[1]; 
                        std::string value = arg.substr(index_of_eq + 1); 
                        std::string long_arg = short_to_long_map[short_arg];
                        
                        if (std::find(required_args.begin(), required_args.end(), long_arg) != required_args.end()) {
                            // if (arguments_int.find(long_arg) != arguments_int.end()) {
                            //     if (CheckIfInt(value)) {
                            //         arguments_int[long_arg].push_back(std::stoi(value));
                            //     } else {
                            //         std::cerr << "Value for Int argument was not an int value!";
                            //         return false;
                            //     } 
                            // } else {
                                arguments[long_arg].push_back(value);
                            //}
                        } else {
                            return false; 
                        }
                    } else {
                        
                        for (size_t j = 1; j < arg.size(); j++) {
                            auto short_arg = arg[j];
                            std::string long_arg = short_to_long_map[short_arg];
                            if ((std::find(no_equal.begin(), no_equal.end(), long_arg) == no_equal.end())) {
                                if (std::find(required_flags.begin(), required_flags.end(), long_arg) != required_flags.end()) {
                                    flags[long_arg] = true;
                                    if (long_arg == "help") {
                                        help_input = true; 
                                    }
                                } else {
                                    return false; 
                                }
                            } else if (std::find(no_equal.begin(), no_equal.end(), long_arg) != no_equal.end()) {
                                if (i + 1 < args.size()) {
                                    // if (arguments_int.find(long_arg) != arguments_int.end()) {
                                    //     if (CheckIfInt(args[i+1])) {
                                    //         arguments_int[long_arg].push_back(std::stoi(args[i+1]));
                                    //     } else {
                                    //         std::cerr << "Value for Int argument was not an int value!";
                                    //         return false;
                                    //     } 
                                    // } else {
                                        arguments[long_arg].push_back(args[i+1]);
                                    //}
                                    i++;
                                }
                            }
                        }
                    }
                } 
                
            
                else if (positional_check) {
                    if (CheckIfInt(args[i])) {
                        arguments[pos_arguments].push_back(args[i]);
                    }
                }
                
            }

            for (const auto& [key, value] : flags) {
                if (value == true && key == "help") {
                    std::cout << HelpDescription() << "\n";
                    return true;
                }
            }
            
            // if (multi_value_check && count >= min_arguments) {
            //     std::cout << "Enough amount of arguments was written" << "\n";
            // } else if (multi_value_check && count < min_arguments) {
            //     std::cout << "Not enough argumennts was written" << "\n";
            //     return false;
            // }

            //std::cout << "enter 1 :" << std::endl;
            if (bool_store_values) {
                for (auto now : store_values_vec) {
                if (arguments.find(now) != arguments.end()) {
                    for (const auto value : arguments[now]) {
                        if (CheckIfInt(value)) {
                            //std::cout << value << std::endl;
                            try {
                                int_arguments->push_back(stoi(value));
                            } catch (const std::invalid_argument&) {
                                std::cerr << "Invalid argument: " << value << " is not an integer!" << std::endl;
                                return false;
                            } catch (const std::out_of_range&) {
                                std::cerr << "Out of range: " << value << std::endl;
                                return false;
                            }
                            
                        }
                    }

                }
                }
            }
            
            if (arguments.find(current_key) != arguments.end()) {
                if (stored_value != nullptr) {
                    *stored_value = arguments[current_key].back();
                }
            }
            //std::cout << "enter 2 :" << std::endl;
            if (multi_value_check) {
                bool flag = true;
                for (const auto& [param, amount] : multi_vec) {
                    if (arguments[param].size() < amount) {
                        std::cerr << "Not enough arguments for " << param << ". Expected at least " << amount << ",but got " << arguments[param].size() << "\n";// << ", but got " << arguments["param1"].size() << ".\n";
                        flag = false;
                    }
                }
                if (!flag) {
                    return false;
                }
            }
            

            
            //std::cout << "enter 3 :" << std::endl;

            for (const auto& req_arg : required_args) {
                if (arguments.find(req_arg) != arguments.end()) {
                    if (arguments[req_arg].empty() && std::find(required_flags.begin(), required_flags.end(), req_arg) == required_flags.end() 
                     && !positional_check && !help_check) {//std::find(no_equal.begin(), no_equal.end(), req_arg) == no_equal.end()
                        std::cout << req_arg << std::endl;
                        return false;
                    }
                }
            }
            
            
            //std::cout << "enter 4 :" << std::endl;
            if (arguments.find("param1") == arguments.end()) {
                ArgParser::AddStringArgument("param1").Default("Hello_there))))");
            }

            
            return true;
    }

    ArgParser& ArgParser::AddStringArgument(const std::string& param) {
        current_key = param;
        required_args.push_back(param);
        no_equal.push_back(param);
        arguments[param] = {};
        return *this;
    }

    ArgParser& ArgParser::AddStringArgument(const char short_flag, const std::string& long_flag) {
        short_to_long_map.insert(std::make_pair(short_flag, long_flag));
        arguments[std::string(1, short_flag)] = {};
        required_args.push_back(long_flag);
        no_equal.push_back(long_flag);
        current_key = long_flag;
        arguments[long_flag] = {};
        return *this;
    }

    ArgParser& ArgParser::AddStringArgument(const char short_flag, const std::string& long_flag, const std::string& declaration) {
        short_to_long_map.insert(std::make_pair(short_flag, long_flag));
        arguments[std::string(1, short_flag)] = {};
        required_args.push_back(long_flag);
        no_equal.push_back(long_flag);
        current_key = long_flag;
        arguments[long_flag] = {};
        return *this;
    }
    ArgParser& ArgParser::AddIntArgument(const std::string& value) {
        current_key = value;
        required_args.push_back(value);
        no_equal.push_back(value);
        arguments[value] = {};
        return *this;
    }

    ArgParser& ArgParser::AddIntArgument(const char short_flag, const std::string& long_flag) {
        short_to_long_map.insert(std::make_pair(short_flag, long_flag));
        arguments[std::string(1, short_flag)] = {};
        arguments[long_flag] = {};
        required_args.push_back(long_flag);
        no_equal.push_back(long_flag);
        current_key = long_flag;
        
        return *this;
    }
    
    ArgParser& ArgParser::AddIntArgument(const char short_flag, const std::string& long_flag, const std::string& declaration) {
        short_to_long_map.insert(std::make_pair(short_flag, long_flag));
        arguments[std::string(1, short_flag)] = {};
        arguments[long_flag] = {};
        required_args.push_back(long_flag);
        no_equal.push_back(long_flag);
        current_key = long_flag;
        return *this;
    }

    ArgParser& ArgParser::AddIntArgument(const std::string& param, const std::string& declaration) {
        current_key = param;
        required_args.push_back(current_key);
        no_equal.push_back(param);
        arguments[param] = {};
        return *this;
    }

    

    ArgParser& ArgParser::AddFlag(const std::string& flag) {
        flags[flag] = false;
        required_flags.push_back(flag);
        required_args.push_back(flag);
        //arguments[flag] = "false";
        current_key = flag;
        return *this; 
    }

    ArgParser& ArgParser::AddFlag(const char short_flag, const std::string& long_flag) {
        short_to_long_map.insert(std::make_pair(short_flag, long_flag));
        arguments[std::string(1, short_flag)] = {};
        current_key = long_flag;
        required_args.push_back(long_flag);
        required_flags.push_back(long_flag);
        flags[long_flag] = false;
        arguments[long_flag] = {};
        return *this;
    }

    ArgParser& ArgParser::AddFlag(const std::string flag, const std::string declaration) {
        flags[flag] = false;
        required_flags.push_back(flag);
        required_args.push_back(flag);
        //arguments[flag] = "false";
        current_key = flag;
        return *this; 
    }

    ArgParser& ArgParser::AddFlag(const char short_flag, const std::string& long_flag, const std::string& declaration) {
        short_to_long_map.insert(std::make_pair(short_flag, long_flag));
        arguments[std::string(1, short_flag)] = {};
        current_key = long_flag;
        required_args.push_back(long_flag);
        required_flags.push_back(long_flag);
        flags[long_flag] = false;
        arguments[long_flag] = {};
        return *this;
    }

    ArgParser& ArgParser::AddHelp(const char short_flag, const std::string& long_flag, const std::string& declaration) {
        help_check = true;
        short_to_long_map.insert(std::make_pair(short_flag, long_flag));
        arguments[std::string(1, short_flag)] = {};
        current_key = long_flag;
        required_args.push_back(long_flag);
        required_flags.push_back(long_flag);
        flags[long_flag] = false;
        arguments[long_flag] = {};
        return *this;
    }

    ArgParser& ArgParser::AddHelp(const char short_flag, const std::string& long_flag) {
        help_check = true;
        short_to_long_map.insert(std::make_pair(short_flag, long_flag));
        arguments[std::string(1, short_flag)] = {};
        current_key = long_flag;
        required_args.push_back(long_flag);
        required_flags.push_back(long_flag);
        flags[long_flag] = false;
        arguments[long_flag] = {};
        return *this;
    }

    ArgParser& ArgParser::MultiValue() {
        is_multi_value = true;
        return *this;
    }

    ArgParser& ArgParser::MultiValue(size_t value) {
        min_arguments = value;
        multi_vec.insert(std::make_pair(current_key, value));
        multi_value_check = true;
        return *this;
    }

    ArgParser& ArgParser::StoreValues(std::vector<int>& values) {
        bool_store_values = true;
        store_values_vec.push_back(current_key);
        int_arguments = &values;
        return *this;
    }

    ArgParser& ArgParser::StoreValue(std::string& value) {
        stored_value = &value;
        return *this;
    }

    ArgParser& ArgParser::StoreValue(bool& check) {
        check = true;
        return *this;
    }

    ArgParser& ArgParser::Default(const char* value) {
        arguments[current_key].push_back(std::string(value));
        return *this;
    }

    ArgParser& ArgParser::Default(const bool& flag_check) {
        if (flag_check) {
            flags[current_key] = true;
        }
        return *this;
    }
    
    std::string ArgParser::GetStringValue(const std::string& param) const {
    auto it = arguments.find(param);
    if (it != arguments.end() && !it->second.empty()) {
        return it->second.front(); 
    }
    return ""; 
    }

    bool ArgParser::GetFlag(const std::string& param) const {
        auto it = arguments.find(param);
        if (it != arguments.end()) {
            return true;
        }
        return false;
    }

    const std::map<std::string, bool> ArgParser::GetFlags() const {
        return flags;
    }

    int ArgParser::GetIntValue(const std::string& param) const {
        auto it = arguments.find(param);
        if (it != arguments.end() && !it->second.empty()) {
            try {
                return std::stoi(it->second.front());
            } 
            catch(const std::invalid_argument&) {
                std::cerr << "Invalid integer value for argument: " << param << "\n";
            }
            catch(const std::out_of_range&) {
                std::cerr << "Integer value is out of range: " << param << "\n";
            }
        }
        return 0;
    }
    
    int ArgParser::GetIntValue(const std::string& param, int index) {
        if (arguments.find(param) != arguments.end()) {
            if (CheckIfInt(arguments[param][index])) {
                if (index >= 0 && index < arguments[param].size()) {
                    return stoi(arguments[param][index]);
                }
                else {
                    std::cout << "Index of int value is out of range, try another one!" << "\n";
                    return -1;
                }
            } else {
                std::cout << "Argument is not an int!" << "\n";
                return -1;
            }
        } else {
            return -1;
        }
    }

    std::vector<std::string> ArgParser::CoutParamValue(const std::string& param) const {
    auto it = arguments.find(param);
    if (it != arguments.end()) {
        return it->second;
    }
    return {};
    }

    bool ArgParser::HasArgument(const std::string& param) const {
        return arguments.find(param) != arguments.end();
    }

    const std::map<std::string, std::vector<std::string>>& ArgParser::GetArguments() const {
        return arguments;
    }

    const std::vector<std::string>& ArgParser::GetReqArr() const{
        return required_args;
    } 

    bool ArgParser::CheckIfInt(const std::string& name) {
        try {
        std::size_t pos;
        int num = std::stoi(name, &pos);
        return pos == name.size();  
        } catch (const std::invalid_argument&) {
            return false;
        } catch (const std::out_of_range&) {
            return false;
        }
    }

    

    ArgParser& ArgParser::Positional() {
        positional_check = true;
        pos_arguments = current_key;
        return *this;
    };

    bool ArgParser::Help() {
    for (const auto& [key, value] : flags) {
        if (value) {
            if (key == "help"){
                return true;
            }
        }
    }
    return false;
    }

const std::string ArgParser::HelpDescription() {
    return "Parser Documentation\n"
    "Use this parser only for legitimate purposes\n";
}
    
}