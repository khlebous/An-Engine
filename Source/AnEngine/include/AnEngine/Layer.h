#ifndef AN_ENGINE_LAYER
#define AN_ENGINE_LAYER

#include "AnEngine/Export.h"

namespace an
{

class AN_API Layer
{
    friend class LayerStack;

  public:
    virtual ~Layer() {};

    virtual void onUpdate() {}

  protected:
    virtual void onAttach() {}
    virtual void onDetach() {}
};

} // namespace an

#endif // AN_ENGINE_APPLICATION