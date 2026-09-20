#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginFontsScss : public Crails::Template
{
public:
  render_LayoutPluginFontsScss(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast< std::string >(vars, "project_name"))
  {}

  void render()
  {
    ecpp_stream.reserve(642);
    // BEGIN TEMPLATE BODY
ecpp_stream << "/* \n * Example:\n * N.B: font.ttf should be stored in the stylesheets/fonts folder\n\n@font-face {\n  font-family: \"Font Family Name\";\n  src: url(\"/cms/plugins/" << ( project_name );
  ecpp_stream << "/assets/font.ttf\") format(\"truetype\");\n  font-weight: normal;\n  font-style: normal;\n}\n*/\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
  std::string project_name;
};

void render_layout_plugin_fonts_scss(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginFontsScss(renderer, target, vars).render();
}