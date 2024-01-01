#include <sstream>
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
ecpp_stream << "#pragma once\n#include <crails/cms/plugins.hpp>\n\nclass ApplicationPlugins : public Crails::Cms::Plugins\n{\n  SINGLETON_IMPLEMENTATION(ApplicationPlugins, Crails::Cms::Plugins)\npublic:\n  ApplicationPlugins();\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
};

void render_project_config_cms_plugins_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsPluginsHpp(renderer, target, vars).render();
}