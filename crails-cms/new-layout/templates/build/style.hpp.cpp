#include <sstream>
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
ecpp_stream << "#pragma once\n#include <crails/cms/views/style.hpp>\n\nclass " << ( style_classname );
  ecpp_stream << " : public Crails::Cms::Style\n{\n  SINGLETON_IMPLEMENTATION(" << ( style_classname );
  ecpp_stream << ", Crails::Cms::Style)\n};\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string style_classname;
};

void render_layout_plugin_style_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginStyleHpp(renderer, target, vars).render();
}