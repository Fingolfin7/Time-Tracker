#pragma once
#include <iostream>
#include <string>

namespace Colours {
    std::string colours[36] = { 
           "black" , "red", 
           "green", "yellow",
           "blue" ,"magenta", 
           "cyan" ,"white" ,

           "bright black","bright red" ,
           "bright green" ,"bright yellow", 
           "bright blue" ,"bright magenta",
           "bright cyan" ,"bright white" ,

           "background black", "background red", 
           "background green" ,"background yellow" ,
           "background blue" , "background magenta",
           "background cyan" , "background white" ,

           "bright background black" , "bright background red" , 
           "bright background green" , "bright background yellow" ,
           "bright background blue" , "bright background magenta" ,
           "bright background cyan" ,"bright background white",

           "bold", "underline",
           "reversed", "reset"
       };

    std::string codes[36] = {
            "\u001b[30m",
            "\u001b[31m",
            "\u001b[32m",
            "\u001b[33m",
            "\u001b[34m",
            "\u001b[35m",
            "\u001b[36m",
            "\u001b[37m",

            "\u001b[30;1m",
            "\u001b[31;1m",
            "\u001b[32;1m",
            "\u001b[33;1m",
            "\u001b[34;1m",
            "\u001b[35;1m",
            "\u001b[36;1m",
            "\u001b[37;1m",

            "\u001b[40m",
            "\u001b[41m",
            "\u001b[42m",
            "\u001b[43m",
            "\u001b[44m",
            "\u001b[45m",
            "\u001b[46m",
            "\u001b[47m",

            "\u001b[40;1m",
            "\u001b[41;1m",
            "\u001b[42;1m",
            "\u001b[43;1m",
            "\u001b[44;1m",
            "\u001b[45;1m",
            "\u001b[46;1m",
            "\u001b[47;1m",

            "\u001b[1m",
            "\u001b[4m",
            "\u001b[7m",
            "\u001b[0m"
       
       };

    std::string colourString(std::string line) {

        for (int i = 0; i < 36; i++) {
           while(line.find("[" + colours[i] + "]") != std::string::npos) {
               line = line.replace(line.find("[" + colours[i] + "]"), std::string("[" + colours[i] + "]").length(), codes[i]);
           }
        }

        while(line.find("[_text_") != std::string::npos) {
            size_t startIndex = line.find("[_text_") + std::string("[_text_").length();
            size_t endIndex = line.find("_]");
            std::string colour_code = line.substr(startIndex, endIndex - startIndex);
            
            line = line.replace(line.find("[_text_"), std::string("[_text_" + colour_code + "_]").length(),
                   "\u001b[38;5;" + colour_code + "m");
        }

        while(line.find("[_background_") != std::string::npos) {
            size_t startIndex = line.find("[_background_") + std::string("[_background_").length();
            size_t endIndex = line.find("_]");
            std::string colour_code = line.substr(startIndex, endIndex - startIndex);
            
            line = line.replace(line.find("[_background_"), std::string("[_background_" + colour_code +"_]").length(),
                   "\u001b[48;5;" + colour_code + "m");
        }

       return line;
    }
};