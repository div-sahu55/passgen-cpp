// Define this class here.
#include <iostream>
#include <cstring>
class RandomEngine {

    private: 
        uint8_t length = 0;
        bool symbl = false;

    public:
    // Constructors:
        RandomEngine(); //default constructor
        explicit RandomEngine(uint8_t l); 
        explicit RandomEngine(bool s); 
        RandomEngine(uint8_t l, bool s);

    // Methods:
        void setLength(uint8_t); // Set the length
        void setSymbolSet(bool); // Turn on symbols
        std::string getString(); // Returns a random string with configured options
        uint8_t getLength();  // Return length of the generator
        bool getSymbolSetStatus();  // Returns true if symbols are on
};
