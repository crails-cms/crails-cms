#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_LayoutPluginLayoutCpp : public Crails::Template
{
public:
  render_LayoutPluginLayoutCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast<std::string>(vars, "project_name")), 
    layout_editor_name(Crails::cast<std::string>(vars, "layout_editor_name")), 
    assets_classname(Crails::cast<std::string>(vars, "assets_classname")), 
    style_classname(Crails::cast<std::string>(vars, "style_classname")), 
    classname( Crails::naming_convention.classnames(project_name))
  {}

  void render()
  {
ecpp_stream << "#include \"layout.hpp\"\n#include \"style.hpp\"\n#include \"lib/assets.hpp\"\n" << ( classname );
  ecpp_stream << "::" << ( classname );
  ecpp_stream << "()\n{\n  name = \"" << ( Crails::naming_convention.filenames(project_name) );
  ecpp_stream << "\";\n  type = Crails::Cms::ComponentLayoutType;\n  component_layout_name = \"" << ( layout_editor_name );
  ecpp_stream << "\";\n  stylesheets.push_back(" << ( assets_classname );
  ecpp_stream << "::layout_css);\n  editor_stylesheets.push_back(" << ( assets_classname );
  ecpp_stream << "::admin_css);\n  editor_javascripts.push_back(" << ( assets_classname );
  ecpp_stream << "::editor_js);\n}\n\nconst Crails::Cms::Style& " << ( classname );
  ecpp_stream << "::get_style() const\n{\n  static const " << ( style_classname );
  ecpp_stream << " style;\n  return style;\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
  std::string layout_editor_name;
  std::string assets_classname;
  std::string style_classname;
  std::string classname;
};

void render_layout_plugin_layout_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginLayoutCpp(renderer, target, vars).render();
}