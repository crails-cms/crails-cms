#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_ProjectConfigCmsLayoutsHpp : public Crails::Template
{
public:
  render_ProjectConfigCmsLayoutsHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <crails/cms/views/layout.hpp>\n\nclass ApplicationLayouts : public Crails::Cms::Layouts\n{\n  SINGLETON_IMPLEMENTATION(ApplicationLayouts, Crails::Cms::Layouts)\n\n  ApplicationLayouts();\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
};

void render_project_config_cms_layouts_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsLayoutsHpp(renderer, target, vars).render();
}