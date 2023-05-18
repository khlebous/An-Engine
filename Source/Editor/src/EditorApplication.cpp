#include "Editor/EditorApplication.h"

#include "Editor/EditorLayer.h"

using namespace an::ed;

EditorApplication::EditorApplication() : Application()
{
    auto editorLayer = std::make_unique<an::ed::EditorLayer>();
    m_layerStack.pushOverlay(std::move(editorLayer));
}
