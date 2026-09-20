#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginStyleHpp : public Crails::Template
{
public:
  render_LayoutPluginStyleHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    style_classname(Crails::cast< std::string >(vars, "style_classname"))
  {}

  void render()
  {
    ecpp_stream.reserve(508);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#pragma once\n#include <crails/cms/views/style.hpp>\n\nclass " << ( style_classname );
  ecpp_stream << " : public Crails::Cms::Style\n{\n  SINGLETON_IMPLEMENTATION(" << ( style_classname );
  ecpp_stream << ", Crails::Cms::Style)\n};\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
  std::string style_classname;
};

void render_layout_plugin_style_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginStyleHpp(renderer, target, vars).render();
}