#include "engine.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
// Create definitions of the RandomEngine class here
// Constructors:
RandomEngine::RandomEngine(uint8_t l){
    length = l;
}

RandomEngine::RandomEngine(bool s){
    symbl=s;
}

RandomEngine::RandomEngine(uint8_t l, bool s){
    length=l;
    symbl=s;
}

// Methods:
void RandomEngine::setLength(uint8_t l){
    length = l;
}

uint8_t RandomEngine::getLength(){
    return length;
}

void RandomEngine::setSymbolSet(bool s){
    symbl = s;
}

bool RandomEngine::getSymbolSetStatus(){
    return symbl;
}

std::string RandomEngine::getString(){

    int mod=62;
    if(getSymbolSetStatus()){
        mod=72;
    }
    //Random number generation:
    char seq[100];
    std::ifstream file("/dev/urandom", std::ios::in | std::ios::binary);
    if(!file) {
        std::cout << "Error opening file\n";
    }
    file.read(seq, sizeof(char)*100);
    file.close();
    std::seed_seq seed(seq, seq+100);
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int64_t> dist(0, mod);
    //password generation:
    std::string alpha_num="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    std::string symbols="!@#$%^&*-_";
    std::string password;
    std::string alpha_num_sym=alpha_num;
    
    if(getSymbolSetStatus()==true){
        alpha_num_sym= alpha_num + symbols;
        }
    for(int i=0;i<getLength();i++){
        int ind=dist(gen);
        password+= alpha_num_sym[ind];
        }
        
    return password;
} 
