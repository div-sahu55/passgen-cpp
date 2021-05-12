#include <iostream>
#include <cstring>
#include <fstream>
#include <random>
#include "version.h"
#include "engine.h"
void print_usage() {
    std::cout << "Usage:\n";
    std::cout << "passgen -L <length>       generates a random password with default character set of given length\n";
	std::cout << "Example: passgen -L 20    generates a random password with default character set of length 20\n";
	std::cout << "passgen -S                generates a random password with all character set of default length 8\n";
	std::cout << "passgen -S -L <length>    generates a random password with all characters set of given length\n";
	std::cout << "Example: passgen -S -L 20 generates a random password with all characters set of length 20\n";
	std::cout << "passgen -V	      prints the version of this tool\n";
}

int main(int argc, char *argv[]){

    // set a limit of the number of arguments to be passed: in argc
    if(argc > 4){
        // tell the user how to run the program
        std::cerr << "Illegal usage!\n";
        print_usage();
        return 1;
    }
    // set the length of the character set to default, which is 8.
    int length=8;
    // set symbol set
    bool symbol_set = false,gen_pass=false;
    RandomEngine r1((uint8_t)8,symbol_set);
    for(int i = 1; i<argc; i++) {
        if(strcmp(argv[i], "-S") == 0) {
            if(!symbol_set) {
                symbol_set = true;
            } else {
                std::cerr << "Illegal usage: Multiple -S flags\n";
                return 2;
            }
        } else if(strcmp(argv[i], "-L") == 0){
            if(i == argc - 1) {
                std::cerr << "Illegal usage: password length not provided with -L option\n";
                return 2;
            }
            size_t pos;
            try {
                length = std::stoi(argv[i+1], &pos);
            } catch (std::invalid_argument &e) {
                std::cerr << "Bad argument for password length\n";
                return 2;
            } catch (std::out_of_range &e) {
                std::cerr << "Integer out of range\n";
                return 2;
            }
            if(pos != strlen(argv[i+1])) {
             // This is a rare case when a string like "45jkl" is parsed to 45 and not bad input
                std::cerr << "Bad argument for password length\n";
                return 2;
            }
            if(length < 1 || length > 128) {
                std::cerr << "password length must be in the range [1,128]\n";
                return 2;
            }
            // If all goes right, we have a valid length
            gen_pass=true;
            break;
        } else if (strcmp(argv[i], "-V") == 0){
            std::cout << "passgen version: " << passgen_VERSION_MAJOR << "." << passgen_VERSION_MINOR  << "."<< passgen_VERSION_REVISION << "\n";
            break;
        } else if (strcmp(argv[i], "-H") == 0){
			print_usage();
            break;
        } else {
            std::cout << "Unknown option: " << argv[i] << std::endl;
            print_usage();
            return 2;
        }
    }
    if(gen_pass || length==8){
    //Random no. generaor:
    char seq[100];
    std::ifstream file("/dev/urandom", std::ios::in | std::ios::binary);
    if(!file) {
        std::cout << "Error opening file\n";
    }
    file.read(seq, sizeof(char)*100);
    file.close();
    
    std::seed_seq seed(seq, seq+100);
    std::mt19937_64 gen(seed);
    std::uniform_int_distribution<int64_t> dist(0, 100000);
    //password generation:
        r1.setLength(length);
        r1.setSymbolSet(symbol_set);
        std::string alpha_num="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        std::string symbols="!@#$%^&*-_";
        std::string s;
        std::string alpha_num_sym;
        int mod=62;
        if(r1.getSymbolSetStatus()==true){
            alpha_num_sym= alpha_num + symbols;
            mod=72;
        }
        else
        alpha_num_sym= alpha_num;
            for(int i=0;i<r1.getLength();i++){
                int ind=dist(gen) % mod;
                char c;
                c= alpha_num_sym[ind];
                s+=c;
            }
            r1.password=s;
            std::cout<<r1.getString()<<std::endl;
    }
    return 0;
}
