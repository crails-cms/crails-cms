#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_PluginAppRoutesCpp : public Crails::Template
{
public:
  render_PluginAppRoutesCpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
    ecpp_stream.reserve(556);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#include <crails/router.hpp>\n#include <crails/cms/routes.hpp>\n\nvoid initialize_plugin_routes()\n{\n  auto& router = Crails::Router::singleton::require();\n  auto& cms_routes = Crails::Cms::Routes::singleton::require();\n\n  // insert plugin routes here\n}\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_plugin_app_routes_cpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginAppRoutesCpp(renderer, target, vars).render();
}