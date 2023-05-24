#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginWebpackConfigJson : public Crails::Template
{
public:
  render_LayoutPluginWebpackConfigJson(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "const path = require(\"path\");\n\nmodule.exports = {\n  entry: [\"./javascripts/index.js\"],\n  output: {\n    path: path.resolve(__dirname, \"build/javascripts\"),\n    filename: \"bundle.js\"\n  }\n};\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
};

void render_layout_plugin_webpack_config_json(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginWebpackConfigJson(renderer, target, vars).render();
}