#include "ecu_communication.h"

/* ---------------- GLOBAL DATA ---------------- */

vehicle_type vehicle[4] = {
    {0.3, 0.45, 0.25},
    {0.35, 0.35, 0.30},
    {0.30, 0.30, 0.40},
    {0.45, 0.20, 0.35}
};

cable_type cabel[3] = {
    {35, 50, 12.5},
    {40, 65, 14.5},
    {10, 40, 13.5}
};

/* ---------------- CONSTRUCTORS ---------------- */

ecu_communication::ecu_communication()
    : a(0), b(0), c(0), ts_cost(0), tp_delay(0)
{
    cout << "New ECU architecture created\n";
}

ecu_communication::ecu_communication(const ecu_communication& other)
    : a(other.a),
      b(other.b),
      c(other.c),
      ts_cost(other.ts_cost),
      tp_delay(other.tp_delay),
      link(other.link),
      mst_link(other.mst_link),
      parent(other.parent),
      rank(other.rank),
      activeNodes(other.activeNodes),
      m(other.m)
{
    cout << "ECU architecture copied\n";
}

ecu_communication::~ecu_communication()
{
    cout << "ECU architecture destroyed\n";
}

/* ---------------- PUBLIC ENTRY ---------------- */

void ecu_communication::run()
{
    architecture_menu();
}

/* ---------------- PRIVATE MENU ---------------- */

void ecu_communication::architecture_menu()
{
    while (true) {
        cout << "\n===== ARCHITECTURE MENU =====\n";
        cout << "1) Add ECU (dummy)\n";
        cout << "2) Optimize (dummy)\n";
        cout << "3) Back to Main Menu\n";
        cout << "Select option: ";

        int ch;
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "Adding ECU (placeholder)\n";
                break;

            case 2:
                cout << "Optimizing architecture (placeholder)\n";
                break;

            case 3:
                return;

            default:
                cout << "Invalid option\n";
        }
    }
}
