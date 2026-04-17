#include "ecu_communication.h"

int main(){
    srand(time(nullptr));

    unique_ptr<ecu_communication> current_arch;

    while(true){
        cout << "1) Create New Architecture\n";
        cout << "2) Copy Existing Architecture\n";
        cout << "3) Exit\n";

        int ch;
        cin >> ch;

        switch(ch){
        case 1:
            current_arch = make_unique<ecu_communication>();
            current_arch->run();   
            break;

        case 2:
            if(current_arch){
                ecu_communication copy(*current_arch);
                copy.run();        
            }
            break;

        case 3:
            return 0;
        }
    }
}
