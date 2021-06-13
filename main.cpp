#include "Application/application.h"

int main() {
    Application::get().parser.readFromFiles();
    Application::get().run();
    Application::get().parser.writeToFiles();
}