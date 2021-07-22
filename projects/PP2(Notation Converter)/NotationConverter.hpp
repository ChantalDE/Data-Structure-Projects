//Chantal Espinosa

#include "NotationConverterInterface.hpp"
#include "deque.hpp"
#include <cctype>
#include <string>
#include <algorithm>
#include <iostream>

#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H


class NotationConverter : public NotationConverterInterface
{
public:

    virtual std::string postfixToInfix(std::string inStr) override{
        deque<std::string> d;
        unsigned int i = 0;

        while(i < inStr.length()){ //keeps track of str
        if(inStr[i]== ' '){
            i++;
            continue;
        }
        if (!isOperator(inStr[i]) && !std::isalpha(inStr[i])){
            throw "Invalid";
        }

            //load part of string in deque  
            if(!(isOperator(inStr[i]))){
                //convert char to Str
                char c = inStr[i];
                std::string s(1, c);
                d.insertBack(s);
                i++;
            }
            else{    char c = inStr[i];
                std::string s(1, c);
                d.insertBack(s);
            
            if(d.size() < 3){
                throw "error";
            }
            op = d.back(); d.removeBack();
            v1 = d.back(); d.removeBack();
            v2 = d.back(); d.removeBack();
            outStr = "(" + v2 + " " + op + " " + v1 + ")";

            d.insertBack(outStr);
            i++; 
        }
        }
        while(d.size() > 1){
                std::string v1 = d.back();
                d.removeBack();
                std::string v2 = d.back();
                d.removeBack();
                if ((v1.size() > 0 && v1[0] != '(') && (v2.size() > 0 && v2[0] != '('))
                    throw ("Invalid format!");
                std::string res = '(' + v2 + v1 + ')';
                d.insertBack(res);
            }
        return d.back();
    } 

    virtual std::string postfixToPrefix(std::string inStr) override{
        return infixToPrefix(postfixToInfix(inStr));
    }

    virtual std::string infixToPostfix(std::string inStr) override{
        deque<std::string> d;
        unsigned int i = 0;

        for(i = 0; i < inStr.length(); i++){ //keeps track of str
            if(inStr[i] == ' ')
                continue;
            if (!isOperator(inStr[i]) && !std::isalpha(inStr[i]) && inStr[i] != '(' && inStr[i] != ')'){
            throw "Invalid";
        }
            //load part of string in deque  
            if (inStr[i] == ')'){

                deque<std::string>d2;
                std::string c;
                while (d.back() != "("){
                    if (d.back().size() == 1 && isOperator(d.back()[0])){
                        c = d.back();
                        d.removeBack();
                    }
                    else{
                        d2.insertBack(d.back());
                        d.removeBack();
                    }
                    if (d.empty())
                        throw "Invalid format!";
                }
                d.removeBack(); //removes last bracket

                outStr = "";
                while(!(d2.empty())){
                    if(d2.size() == 1 && c == ""){
                        outStr += (d2.back());
                    }
                    else{
                        outStr += (d2.back() + " ");
                    }
                    d2.removeBack();
                }
                outStr += c;
                d.insertBack(outStr);
        }
        else{
            d.insertBack(std::string (1, inStr[i]));
        }
    }
        if (d.size() > 1){
            throw "error";
        }
        return d.back();
    }

    virtual std::string infixToPrefix(std::string inStr) override{
        deque<std::string> d;
        unsigned int i = 0;

        std::reverse(inStr.begin(), inStr.end());
        for(i = 0; i < inStr.length(); i++){ //keeps track of str
            if(inStr[i] == ' ')
                continue;

            if (!isOperator(inStr[i]) && !std::isalpha(inStr[i]) && inStr[i] != '(' && inStr[i] != ')'){
            throw "Invalid";
        }
            //load part of string in deque  
            if (inStr[i] == '('){

                deque<std::string>d2;
                std::string c;
                while (d.back() != ")"){
                    if (d.back().size() == 1 && isOperator(d.back()[0])){
                        c = d.back();
                        d.removeBack();
                    }
                    else{
                        d2.insertBack(d.back());
                        d.removeBack();
                    }
                    if (d.empty())
                        throw "Invalid format!";
                }
                d.removeBack(); //removes last bracket

                outStr = "";
                if(c != ""){
                    outStr += (c + " ");
                }
                while(!(d2.empty())){
                    if(d2.size() == 1){
                       outStr += (d2.front()); 
                    }
                    else{
                        outStr += (d2.front() + " ");
                    }
                    d2.removeFront();
                }
                d.insertBack(outStr);
        }
        else{
            d.insertBack(std::string (1, inStr[i]));
        }
    }
        if (d.size() > 1){
            throw "error";
        }
        return d.back();
    }

    virtual std::string prefixToInfix(std::string inStr) override{
        reverse(inStr.begin(), inStr.end());
        deque<std::string> d;
        unsigned int i = 0;

        while(i < inStr.length()){ //keeps track of str
            if(inStr[i] == ' '){
                i++;
                continue;
            }
            if (!isOperator(inStr[i]) && !std::isalpha(inStr[i])){
            throw "Invalid";
        }
            //load part of string in deque  
            if(!(isOperator(inStr[i]))){
                //convert char to Str
                char c = inStr[i];
                std::string s(1, c);
                d.insertBack(s);
                i++;
            }
       else{    char c = inStr[i];
                std::string s(1, c);
                d.insertBack(s);
            
            if(d.size() < 3){
                throw "error";
            }
            op = d.back(); d.removeBack();
            v1 = d.back(); d.removeBack();
            v2 = d.back(); d.removeBack();
            outStr = "(" + v1 + " " + op + " " + v2 + ")";

            d.insertBack(outStr);
            i++; 
        }
        }
        while(d.size() > 1){
                std::string v1 = d.back();
                d.removeBack();
                std::string v2 = d.back();
                d.removeBack();
                if ((v1.size() > 0 && v1[0] != '(') && (v2.size() > 0 && v2[0] != '('))
                    throw ("Invalid format!");
                std::string res = '(' + v1 + v2 + ')';
                d.insertBack(res);
            }
        return d.back();
    }
    virtual std::string prefixToPostfix(std::string inStr) override{
       std::string s1 = prefixToInfix(inStr);
       std::string s2 = infixToPostfix(s1);
       return s2; 
    }

private:
    bool isOperator(char d){
        return ((d == '*') || (d == '/') || (d == '+') || (d == '-'));
    }
    std::string v1, v2, op, outStr;

};

#endif