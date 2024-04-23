#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <regex>

using namespace std;

set<string> get_usb_devices() {//вывод устройств с файла
    set<string> devices;
    string line;
    ifstream lsusb_output("lsusb_output.txt");
    regex device_regex("Bus \\d{3} Device \\d{3}: ID (\\w{4}:\\w{4}) (.*)");
    smatch match;
    if (lsusb_output.is_open()) {
        while (getline(lsusb_output, line)) {
            if (regex_search(line, match, device_regex)) {
                devices.insert(match.str(1) + " " + match.str(2));
            }
        }
        lsusb_output.close();
    }
    return devices;
}

int main() {
    set<string> old_devices = get_usb_devices();
    while (true) {
        system("lsusb > lsusb_output.txt");
        set<string> new_devices = get_usb_devices();
        for (const string& device : new_devices) {
            if (old_devices.find(device) == old_devices.end()) {
                cout << "Новое устройство подключено: " << device << endl;
                
            }
        }
        for (const string& device : old_devices) {
            if (new_devices.find(device) == new_devices.end()) {
                cout << "Устройство отключено: " << device << endl;
            }
        }

    }

    return 0;
}
