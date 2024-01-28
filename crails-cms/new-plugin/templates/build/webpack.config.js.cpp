#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_PluginWebpackConfigJs : public Crails::Template
{
public:
  render_PluginWebpackConfigJs(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "const path = require(\"path\");\n\nmodule.exports = [\n  {\n    entry: \"./app/assets/javascripts/admin.js\",\n    output: {\n      path: path.resolve(__dirname, \"lib/\"),\n      filename: \"admin.js\"\n    }\n  },\n  {\n    entry: \"./app/assets/javascripts/application.js\",                                                                 \n    output: {\n      path: path.resolve(__dirname, \"lib/\"),\n      filename: \"application.js\"\n    }\n  }\n];\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
};

void render_plugin_webpack_config_js(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginWebpackConfigJs(renderer, target, vars).render();
}