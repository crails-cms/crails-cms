#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_ProjectConfigCmsLayoutsCpp : public Crails::Template
{
public:
  render_ProjectConfigCmsLayoutsCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "#include \"layouts.hpp\"\n\nstruct DocumentLayout : public Crails::Cms::Layout\n{\n  DocumentLayout() { name = \"document\"; }\n};\n\nApplicationLayouts::ApplicationLayouts()\n{\n  layouts.push_back(new DocumentLayout);\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
};

void render_project_config_cms_layouts_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsLayoutsCpp(renderer, target, vars).render();
}