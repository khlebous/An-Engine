#ifndef AN_ENGINE_IMGUI_LAYER
#define AN_ENGINE_IMGUI_LAYER

#include "AnEngine/Layer.h"
#include "AnEngine/Export.h"

namespace an
{

class AN_API ImguiLayer final : public Layer
{
  public:
    void onAttach() final;
    void onDetach() final;
    void onUpdate() final;

  private:
    float time = 0.0f;
};

} // namespace an

#endif // AN_ENGINE_IMGUI_LAYER