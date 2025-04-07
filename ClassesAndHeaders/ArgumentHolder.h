#pragma once
#include <string>

class ArgumentHolder {
protected:
    std::string arg0;
    int arg1;
    int arg2;
    int arg3;
    int arg4;
    float drunkLevel;
public:
    ArgumentHolder(char* arg0, int arg1,int arg2,int arg3, int arg4);
    ArgumentHolder(char* arg0, int arg2,int arg3, int arg4, float arg5);
    [[nodiscard]] std::string GetProgramMode() const;
    [[nodiscard]] int GetChosenAlgorithm() const;
    [[nodiscard]] int GetChosenDataType() const;
    [[nodiscard]] int GetChosenIterationAmount() const;
    [[nodiscard]] int GetChosenArraySize() const;
    [[nodiscard]] float GetDrunkLevel() const;
                 void SetChosenAlgorithm(int algorithm);
                 void SetChosenDataType(int data_type);
                 void SetChosenArraySize(int array_size);
                 void SetChosenIterationAmount(int iteration_amount);
                 void SetDrunkLevel(float drunkLevel);
};




