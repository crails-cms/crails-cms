#include <crails/template_stream.hpp>
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
    ecpp_stream.reserve(484);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#include \"layouts.hpp\"\n\nstruct DocumentLayout : public Crails::Cms::Layout\n{\n  DocumentLayout() { name = \"document\"; }\n};\n\nApplicationLayouts::ApplicationLayouts()\n{\n  layouts.push_back(new DocumentLayout);\n}\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_project_config_cms_layouts_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectConfigCmsLayoutsCpp(renderer, target, vars).render();
}