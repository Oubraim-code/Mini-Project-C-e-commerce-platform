#include "ECommercePlatform.h"
#include <iostream>

int main() {
    try {
        ECommercePlatform platform;
        platform.initialize();
        platform.run();
        platform.shutdown();
    } catch (const std::exception& e) {
        std::cerr << "Erreur fatale: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
