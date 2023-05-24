#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginCrailsfile : public Crails::Template
{
public:
  render_LayoutPluginCrailsfile(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast<std::string>(vars, "project_name"))
  {}

  void render()
  {
ecpp_stream << "name=" << ( project_name );
  ecpp_stream << "\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
};

void render_layout_plugin_crailsfile(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginCrailsfile(renderer, target, vars).render();
}