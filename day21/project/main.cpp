#include "ecu_communication.h"

int main() {
    srand(time(nullptr));

    unique_ptr<ecu_communication> current_arch = nullptr;

    while (true) {
        cout << "\n1) Create New Architecture\n";
        cout << "2) Copy Existing Architecture\n";
        cout << "3) Exit\n";
        cout << "Select option: ";

        int ch;
        cin >> ch;

        switch (ch) {

        case 1:
            current_arch = make_unique<ecu_communication>();
            break;

        case 2: {
            if (!current_arch) {
                cout << "No architecture exists to copy\n";
                break;
            }
            ecu_communication copied(*current_arch);
            break;
        }

        case 3:
            return 0;

        default:
            cout << "Invalid choice\n";
        }
    }
}
