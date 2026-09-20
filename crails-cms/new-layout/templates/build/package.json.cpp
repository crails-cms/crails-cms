#include <crails/template_stream.hpp>
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
    ecpp_stream.reserve(290);
    // BEGIN TEMPLATE BODY
ecpp_stream << "{\n  \"dependencies\": {\n    \"webpack\": \"^5.75.0\",\n    \"webpack-cli\": \"^4.10.0\",\n    \"sass\": \"^1.57.1\"\n  }\n}\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_layout_plugin_package_json(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginPackageJson(renderer, target, vars).render();
}