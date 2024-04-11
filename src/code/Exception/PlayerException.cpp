#include "Exception/PlayerException.hpp"

NotEnoughResourceException::NotEnoughResourceException(map<string,int> &remainingResource,int &remainingMoney){
    this->message = "";
    if(remainingMoney>0){
        message += to_string(remainingMoney);
        message += " gulden";
        if(!remainingResource.empty()){
            message += ", ";
        }
    }
    for(auto it=remainingResource.cbegin(); it!=remainingResource.cend(); ++it){
        {
            message += to_string(it->second);
            message += " ";
            message += it->first;
        }
        if(it!=prev(remainingResource.cend())) message += ", "; 
    }
    replace(message.begin(),message.end(),'_',' ');
    transform(message.begin(),message.end(),message.begin(),::tolower);
}

NotEnoughResourceException::NotEnoughResourceException(){
    this->message = "Uang tidak cukup";
}

const char *NotEnoughResourceException::what() const noexcept {
    return this->message.c_str();
}

