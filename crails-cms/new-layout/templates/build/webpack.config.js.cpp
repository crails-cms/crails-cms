#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginWebpackConfigJs : public Crails::Template
{
public:
  render_LayoutPluginWebpackConfigJs(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
    ecpp_stream.reserve(822);
    // BEGIN TEMPLATE BODY
ecpp_stream << "const path = require(\"path\");\n\nmodule.exports = [\n  {\n    entry: [\"./javascripts/index.js\"],\n    output: {\n      path: path.resolve(__dirname, \"build/javascripts\"),\n      filename: \"bundle.js\"\n    }\n  },\n  {\n    entry: [\"./javascripts/editor.js\"],\n    output: {\n      path: path.resolve(__dirname, \"build/javascripts\"),\n      filename: \"editor.js\"\n    }\n  }\n];\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_layout_plugin_webpack_config_js(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginWebpackConfigJs(renderer, target, vars).render();
}