#ifndef AN_ENGINE_EDITOR_EDITOR_APPLICATION
#define AN_ENGINE_EDITOR_EDITOR_APPLICATION

#include <Engine/Application.h>

namespace an::ed
{

class EditorApplication : public an::Application
{
  public:
    EditorApplication();
};

} // namespace an::ed

std::unique_ptr<an::Application> an::createApplication()
{
    return std::make_unique<an::ed::EditorApplication>();
}

#endif // AN_ENGINE_EDITOR_EDITOR_APPLICATION