#include "ClassesAndHeaders/Includes.h"
#include "ClassesAndHeaders/Tests.hpp"

void SetupArgsPijany(ArgumentHolder*& args,char* argv[],int argc){
    args = new ArgumentHolder(
            argv[argc - 5],
            std::stoi(argv[argc - 4]),
            std::stoi(argv[argc - 3]),
            std::stoi(argv[argc - 2]),
            (float)std::atof(argv[argc- 1])
    );
}

void SetupArgs(ArgumentHolder*& args,char* argv[],int argc){
    args = new ArgumentHolder(
            argv[argc - 5],
            std::stoi(argv[argc - 4]),
            std::stoi(argv[argc - 3]),
            std::stoi(argv[argc - 2]),
            std::stoi(argv[argc - 1])
    );
}

int main(int argc, char* argv[]) {
    std::cout << "DZIALA" << std::endl;

    if (argc == 2) {
        std::string arg0 = argv[argc-1];
        if (arg0 == "--help") {
            std::cout << Utilities::help << std::endl;
        }
        std::cin >> arg0;
        return 0;
    }

    std::cout << std::flush;
    Timer* timer = new Timer();
    ArgumentHolder *args;

    if (argc == 6) {
        SetupArgs(args,argv,argc);
    }

    if (argc == 6 && std::string(argv[argc-5]) == "--pijany"){
        std::cout <<"gets in";
        SetupArgsPijany(args,argv,argc);
        std::cout << args->GetDrunkLevel();
        switch (args->GetChosenDataType()) {
            case 0: Tests::ProcessPijany<int>(args, timer); break;
            case 1: Tests::ProcessPijany<float>(args, timer); break;
            case 2: Tests::ProcessPijany<double>(args, timer); break;
            case 3: Tests::ProcessPijany<char>(args, timer); break;
            default: throw std::invalid_argument("Invalid type");
        }
    }

    if (argc == 6 && std::string(argv[argc-5]) == "--pijanybadanie1"){
        std::cout <<"gets in";
        SetupArgsPijany(args,argv,argc);

        switch (args->GetChosenDataType()) {
            case 0: Tests::StudyOneDataSizePijany<int>(args, timer); break;
            case 1: Tests::StudyOneDataSizePijany<float>(args, timer); break;
            case 2: Tests::StudyOneDataSizePijany<double>(args, timer); break;
            case 3: Tests::StudyOneDataSizePijany<char>(args, timer); break;
            default: throw std::invalid_argument("Invalid type");
        }
    }

    if (argc == 6 && std::string(argv[argc-5]) == "--pijanybadanie2"){
        std::cout <<"gets in";
        SetupArgsPijany(args,argv,argc);

        switch (args->GetChosenDataType()) {
            case 0: Tests::StudyTwoInitialDistributionPijany<int>(args, timer); break;
            case 1: Tests::StudyTwoInitialDistributionPijany<float>(args, timer); break;
            case 2: Tests::StudyTwoInitialDistributionPijany<double>(args, timer); break;
            case 3: Tests::StudyTwoInitialDistributionPijany<char>(args, timer); break;
            default: throw std::invalid_argument("Invalid type");
        }
    }

    if (argc == 6 && std::string(argv[argc-5]) == "--pijanybadanie3"){
        std::cout <<"gets in";
        SetupArgsPijany(args,argv,argc);
        Tests::StudyThreeDataTypeImpactPijany(args,timer);
    }

    Tests::OpenFile();
    if (args->GetProgramMode() == "--file") {
        switch (args->GetChosenDataType()) {
            case 0: Tests::ProcessArrayFile<int>(args, timer); break;
            case 1: Tests::ProcessArrayFile<float>(args, timer); break;
            case 2: Tests::ProcessArrayFile<double>(args, timer); break;
            case 3: Tests::ProcessArrayFile<char>(args, timer); break;
            default: throw std::invalid_argument("Invalid type");
        }
    }
    if (args->GetProgramMode() == "--benchmark") {
        switch (args->GetChosenDataType()) {
            case 0: Tests::ProcessArrayBenchmark<int>(args, timer); break;
            case 1: Tests::ProcessArrayBenchmark<float>(args, timer); break;
            case 2: Tests::ProcessArrayBenchmark<double>(args, timer); break;
            case 3: Tests::ProcessArrayBenchmark<char>(args, timer); break;
            default: throw std::invalid_argument("Invalid type");
        }
    }
    if (args->GetProgramMode() == "--test") {
        for (int i = 0; i < Algorytmy<int>.size(); i++) {
            args->SetChosenAlgorithm(i);
            args->SetChosenDataType(0);Tests::ProcessArrayBenchmark<int>(args, timer);
            args->SetChosenDataType(1);Tests::ProcessArrayBenchmark<float>(args, timer);
            args->SetChosenDataType(2);Tests::ProcessArrayBenchmark<double>(args, timer);
            args->SetChosenDataType(3);Tests::ProcessArrayBenchmark<char>(args, timer);
            args->SetChosenDataType(4);Tests::ProcessArrayBenchmark<Planszowka>(args,timer);
        }
        std::cout << "\nEVERYTHING CORRECTLY SORTS!!" << std::endl;
    }
    if (args->GetProgramMode() == "--badanie1") {
        switch (args->GetChosenDataType()) {
            case 0: Tests::StudyOneDatasetSize<int>(args, timer); break;
            case 1: Tests::StudyOneDatasetSize<float>(args, timer); break;
            case 2: Tests::StudyOneDatasetSize<double>(args, timer); break;
            case 3: Tests::StudyOneDatasetSize<char>(args, timer); break;
            default: throw std::invalid_argument("Invalid type");
        }
    }
    if (args->GetProgramMode() == "--badanie2") {
        switch (args->GetChosenDataType()) {
            case 0: Tests::StudyTwoInitialDistribution<int>(args, timer); break;
            case 1: Tests::StudyTwoInitialDistribution<float>(args, timer); break;
            case 2: Tests::StudyTwoInitialDistribution<double>(args, timer); break;
            case 3: Tests::StudyTwoInitialDistribution<char>(args, timer); break;
            default: throw std::invalid_argument("Invalid type");
        }
    }
    if (args->GetProgramMode() == "--badanie3") {
        Tests::StudyThreeDataTypeImpact(args, timer);
    }

    delete args;
    delete timer;
    Tests::CloseFile();
    return 0;
}






