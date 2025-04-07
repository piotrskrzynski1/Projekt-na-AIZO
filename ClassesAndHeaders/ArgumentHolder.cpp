#include "ArgumentHolder.h"

    ArgumentHolder::ArgumentHolder(char* arg0, const int arg1,const int arg2 = 0,const int arg3 = 0,const int arg4 = 0) : arg0(arg0), arg1(arg1),arg2(arg2),arg3(arg3),arg4(arg4) {}
ArgumentHolder::ArgumentHolder(char* arg0, const int arg2 = 0,const int arg3 = 1,const int arg4 = 100, const float arg5 = 0) : arg0(arg0), arg2(arg2),arg3(arg3),arg4(arg4),drunkLevel(arg5) {}
    std::string ArgumentHolder::GetProgramMode() const {
        return arg0;
    }
    int ArgumentHolder::GetChosenAlgorithm() const {
        return arg1;
    }
    int ArgumentHolder::GetChosenDataType() const {
        return arg2;
    }
    int ArgumentHolder::GetChosenIterationAmount() const {
        return arg3;
    }
    int ArgumentHolder::GetChosenArraySize() const {
        return arg4;
    }
    float ArgumentHolder::GetDrunkLevel() const {
        return drunkLevel;
    }
    void ArgumentHolder::SetChosenAlgorithm(const int algorithm) {
        arg1=algorithm;
    }

void ArgumentHolder::SetChosenDataType(const int data_type) {
        arg2 = data_type;
    }
void ArgumentHolder::SetChosenIterationAmount(const int iteration_amount) {
        arg3 = iteration_amount;
    }
void ArgumentHolder::SetChosenArraySize(const int array_size) {
        arg4 = array_size;
    }
    void ArgumentHolder::SetDrunkLevel(float drunkLevel) {
    if(drunkLevel >= 0.0f && drunkLevel <= 1.0f){
        this->drunkLevel = drunkLevel;
    }
}





