#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginFontsScss : public Crails::Template
{
public:
  render_LayoutPluginFontsScss(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast<std::string>(vars, "project_name"))
  {}

  void render()
  {
ecpp_stream << "/* \n * Example:\n * N.B: font.ttf should be stored in the stylesheets/fonts folder\n\n@font-face {\n  font-family: \"Font Family Name\";\n  src: url(\"/cms/plugins/" << ( project_name );
  ecpp_stream << "/assets/font.ttf\") format(\"truetype\");\n  font-weight: normal;\n  font-styke: normal;\n}\n*/\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
};

void render_layout_plugin_fonts_scss(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginFontsScss(renderer, target, vars).render();
}