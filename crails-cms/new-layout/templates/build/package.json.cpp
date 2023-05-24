#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginPackageJson : public Crails::Template
{
public:
  render_LayoutPluginPackageJson(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "{\n  \"dependencies\": {\n    \"webpack\": \"^5.75.0\",\n    \"webpack-cli\": \"^4.10.0\",\n    \"sass\": \"^1.57.1\"\n  }\n}\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
};

void render_layout_plugin_package_json(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginPackageJson(renderer, target, vars).render();
}