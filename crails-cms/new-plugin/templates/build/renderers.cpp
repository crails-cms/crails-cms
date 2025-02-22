#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/cli/conventions.hpp>

class render_PluginAppRenderersCpp : public Crails::Template
{
public:
  render_PluginAppRenderersCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    project_name(Crails::cast< std::string >(vars, "project_name")), 
    html_renderer_classname(Crails::cast< std::string >(vars, "html_renderer_classname")), 
    json_renderer_classname(Crails::cast< std::string >(vars, "json_renderer_classname")), 
    html_renderer_include( Crails::naming_convention.filenames(html_renderer_classname)), 
    json_renderer_include( Crails::naming_convention.filenames(json_renderer_classname))
  {}

  void render()
  {
ecpp_stream << "#include <crails/renderer.hpp>\n#include \"lib/renderers/" << ( html_renderer_include );
  ecpp_stream << ".hpp\"\n#include \"lib/renderers/" << ( json_renderer_include );
  ecpp_stream << ".hpp\"\n#include <iostream>\n\nstatic void initialize_renderer(const Crails::Renderers& renderers, const Crails::Renderer& source)\n{\n  for (auto it = renderers.begin() ; it != renderers.end() ; ++it)\n  {\n    const Crails::Renderer* renderer = it->get();\n\n    if (*renderer->get_mimetypes().begin() == *source.get_mimetypes().begin())\n      const_cast<Crails::Renderer*>(renderer)->merge(source);\n  }\n}\n\nvoid initialize_plugin_renderers()\n{\n  auto& renderers = Crails::Renderers::singleton::require();\n  " << ( html_renderer_classname );
  ecpp_stream << " plugin_html;\n  " << ( json_renderer_classname );
  ecpp_stream << " plugin_json;\n\n  initialize_renderer(renderers, plugin_html);\n  initialize_renderer(renderers, plugin_json);\n}\n\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
  std::string project_name;
  std::string html_renderer_classname;
  std::string json_renderer_classname;
  std::string html_renderer_include;
  std::string json_renderer_include;
};

void render_plugin_app_renderers_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginAppRenderersCpp(renderer, target, vars).render();
}