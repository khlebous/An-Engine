
#include "AnEngine/Application.h"

#include <Core/Logger.h>

int main()
{
    an::core::Logger::init();

    auto app = std::make_unique<an::Application>();
    app->run();
}
