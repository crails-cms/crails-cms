#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_LayoutPluginMainCpp : public Crails::Template
{
public:
  render_LayoutPluginMainCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast<std::string>(vars, "project_name")), 
    assets_classname(Crails::cast<std::string>(vars, "assets_classname")), 
    renderer_classname(Crails::cast<std::string>(vars, "renderer_classname"))
  {}

  void render()
  {
ecpp_stream << "#include \"layout.hpp\"\n#include \"lib/assets.hpp\"\n#include \"lib/renderers/" << ( Crails::naming_convention.filenames(renderer_classname) );
  ecpp_stream << ".hpp\"\n\nextern \"C\"\n{\n  Crails::BuiltinAssets* get_assets()\n  {\n    static " << ( assets_classname );
  ecpp_stream << " assets;\n    return &assets;\n  }\n\n  Crails::Renderer* get_html_renderer()\n  {\n    static " << ( renderer_classname );
  ecpp_stream << " renderer;\n    return &renderer;\n  }\n\n  Crails::Cms::Layout* create_layout()\n  {\n    return new " << ( Crails::naming_convention.classnames(project_name) );
  ecpp_stream << "();\n  }\n}\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
  std::string assets_classname;
  std::string renderer_classname;
};

void render_layout_plugin_main_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginMainCpp(renderer, target, vars).render();
}