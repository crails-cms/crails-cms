#include <crails/template_stream.hpp>
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
    ecpp_stream.reserve(954);
    // BEGIN TEMPLATE BODY
ecpp_stream << "const path = require(\"path\");\n\nmodule.exports = [\n  {\n    entry: \"./app/assets/javascripts/admin.js\",\n    output: {\n      path: path.resolve(__dirname, \"lib/\"),\n      filename: \"admin.js\"\n    }\n  },\n  {\n    entry: \"./app/assets/javascripts/application.js\",                                                                 \n    output: {\n      path: path.resolve(__dirname, \"lib/\"),\n      filename: \"application.js\"\n    }\n  }\n];\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_plugin_webpack_config_js(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginWebpackConfigJs(renderer, target, vars).render();
}