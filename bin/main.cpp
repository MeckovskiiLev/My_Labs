#include <functional>
#include <lib/ArgParser.h>

#include <iostream>
#include <numeric>

struct Options {
    bool sum = false;
    bool mult = false;
};

int main(int argc, char** argv) {
    ArgumentParser::ArgParser parser("My Arguments Parser");

    std::vector<std::string> args(argv, argv + argc);
    
    // parser.AddStringArgument('a', "param2");
    
    //std::vector<int> values;
    // parser.AddIntArgument("param2");
    
    //parser.AddIntArgument("Param1").MultiValue(0).Positional().StoreValues(values);
    //parser.AddStringArgument("param1");
    //parser.AddIntArgument("param1").MultiValue(1);//.Positional().StoreValues(values);
    //parser.AddStringArgument("param2").MultiValue(2);
    // parser.AddStringArgument('i', "input", "File path for input file");
    //parser.AddHelp('h', "help", "Some Description about program");
    //parser.AddFlag("flag");
    // parser.AddStringArgument("param1");
    // if (parser.Parse(args)) {
        
    //     std::cout << "Success!" << "\n";
    //     for (const auto& [param, values] : parser.GetArguments()) { 
    //         if (std::find(parser.GetReqArr().begin(), parser.GetReqArr().end(), param) != parser.GetReqArr().end())
    //         std::cout << "Argument: " << param << std::endl;
    //         for (const auto& value : values) {
    //             if (parser.CheckIfInt(value)){
    //                 std::cout << "  Value(int): " << value << std::endl;
    //             } else {
    //                 std::cout << "  Value(string): " << value << std::endl;
    //             }
    //         }
        
    //     }
    //     for (const auto& [flag, booly] : parser.GetFlags()) {
    //         if (booly) {
    //             std::cout << "Flag: " << flag << std::endl;
    //         }
    //     }
    // } else {
    //     std::cout << "Something went wrong ot help was declarated";
    // }
    // for (auto now : values) {
    //     std::cout << now << " ";
    // }
    
    // std::string value;
    
    // parser.StoreValue(value);
    // std::cout << "value :" << value << "\n";
    // for (const auto& value : parser.CoutParamValue("param1")) {
    //     std::cout << "param1: " << value << std::endl;
    // }




    Options opt;
    std::vector<int> values;

    //ArgumentParser::ArgParser parser("Program");
   parser.AddIntArgument("N").MultiValue(1).Positional().StoreValues(values);
   parser.AddFlag("sum", "add args").StoreValue(opt.sum);
    parser.AddFlag("mult", "multiply args").StoreValue(opt.mult);
    parser.AddHelp('h', "help", "Program accumulate arguments");

    if(!parser.Parse(args)) {
        std::cout << "Wrong argument" << std::endl;
        std::cout << parser.HelpDescription() << std::endl;
        return 1;
    }

    if(parser.Help()) {
        std::cout << parser.HelpDescription() << std::endl;
        return 0;
    }


    if(opt.sum) {
        std::cout << "Result: " << std::accumulate(values.begin(), values.end(), 0) << std::endl;
    }
    if(opt.mult) {
        std::cout << "Result: " << std::accumulate(values.begin(), values.end(), 1, std::multiplies<int>()) << std::endl;
    } else {
        std::cout << "No one options had chosen" << std::endl;
        std::cout << parser.HelpDescription();
        return 1;
    }

     return 0;

}
