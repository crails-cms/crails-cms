#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_ProjectConfigCmsPluginsHpp : public Crails::Template
{
public:
  render_ProjectConfigCmsPluginsHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
    ecpp_stream.reserve(472);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#pragma once\n#include <crails/cms/plugins.hpp>\n\nclass ApplicationPlugins : public Crails::Cms::Plugins\n{\n  SINGLETON_IMPLEMENTATION(ApplicationPlugins, Crails::Cms::Plugins)\npublic:\n  ApplicationPlugins();\n};\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_project_config_cms_plugins_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsPluginsHpp(renderer, target, vars).render();
}