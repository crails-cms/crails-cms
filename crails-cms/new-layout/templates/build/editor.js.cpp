#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginEditorJs : public Crails::Template
{
public:
  render_LayoutPluginEditorJs(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    layout_editor_name(Crails::cast<std::string>(vars, "layout_editor_name"))
  {}

  void render()
  {
ecpp_stream << "class " << ( layout_editor_name );
  ecpp_stream << " extends PageEditor.LayoutEditor {\n}\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string layout_editor_name;
};

void render_layout_plugin_editor_js(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginEditorJs(renderer, target, vars).render();
}