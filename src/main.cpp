#include "View/CLI/CLI.hpp"

int main(){
    CLI c;
    try{
        c.start();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    return 0;
}