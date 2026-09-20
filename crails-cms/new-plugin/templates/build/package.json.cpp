#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_PluginPackageJson : public Crails::Template
{
public:
  render_PluginPackageJson(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
    ecpp_stream.reserve(232);
    // BEGIN TEMPLATE BODY
ecpp_stream << "{\n  \"dependencies\": {\n    \"webpack\": \"^5.84.0\",\n    \"webpack-cli\": \"^5.1.1\"\n  }\n}\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_plugin_package_json(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginPackageJson(renderer, target, vars).render();
}