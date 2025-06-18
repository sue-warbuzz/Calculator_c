#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

Fl_Input* display;

std::string current = "";

void button_cb(Fl_Widget* w, void*) {
    const char* label = w->label();
    std::string text(label);

    if (text == "=") {
        // Naive eval (only supports +)
        int total = 0;
        std::stringstream ss(current);
        std::string num;
        while (getline(ss, num, '+')) {
            total += std::stoi(num);
        }
        current = std::to_string(total);
    } else if (text == "C") {
        current = "";
    } else {
        current += text;
    }

    display->value(current.c_str());
}

int main() {
    Fl_Window *win = new Fl_Window(230, 300, "C++ Calculator");

    display = new Fl_Input(20, 20, 190, 30);
    display->readonly(1);

    const char* labels[] = {"C","7","8","9","4","5","6","1","2","3","0","+","="};
    int x = 20, y = 60;

    for (int i = 0; i < 13; ++i) {
        Fl_Button* btn = new Fl_Button(x, y, 50, 40, labels[i]);
        btn->callback(button_cb);
        x += 55;
        if ((i + 1) % 3 == 0) {
            x = 20;
            y += 45;
        }
    }

    win->end();
    win->show();
    return Fl::run();
}
