#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_LayoutPluginLayoutHtml : public Crails::Template
{
public:
  render_LayoutPluginLayoutHtml(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    assets_classname(Crails::cast< std::string >(vars, "assets_classname")), 
    style_classname(Crails::cast< std::string >(vars, "style_classname"))
  {}

  void render()
  {
    ecpp_stream.reserve(2604);
    // BEGIN TEMPLATE BODY
ecpp_stream << "#include <crails/i18n.hpp>\n#include <crails/cms/models/settings.hpp>\n#include <crails/cms/views/menu.hpp>\n#include \"lib/assets.hpp\"\n#include \"src/style.hpp\"\n\n" << ( style_classname );
  ecpp_stream << " style;\nconst char* @yield;\nconst Crails::Cms::Settings& @settings;\nstd::string @page_title = settings.get_title();\nbool @render_footer = true;\n\n// END LINKING\n<html lang=\"<%= i18n::Settings::singleton::require().get_current_locale() %>\">\n  <head>\n    <title><%= page_title %></title>\n    <meta charset=\"utf-8\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />\n    <%= partial(\"layouts/head\") %>\n    <%= tag(\"link\", {{\"rel\",\"stylesheet\"},{\"href\", " << ( assets_classname );
  ecpp_stream << "::layout_css}}) %>\n  </head>\n  <body>\n    <header>\n      <%= Crails::Cms::RenderMenu(\"main-menu\", this)\n             .with_direction(Crails::Cms::Menu::Horizontal)\n             .with_style(&style)() yields %>\n        <h1><%= settings.get_title() %></h1>\n      <% yields-end %>\n    </header>\n\n    <main>\n      <% if (yield != nullptr) do -%>\n        <%= yield %>\n      <% end -%>\n\n      <% if (render_footer) do -%>\n        <%= settings.get_footer() %>\n      <% end -%>\n    </main>\n  </body>\n</html>\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
  std::string assets_classname;
  std::string style_classname;
};

void render_layout_plugin_layout_html(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_LayoutPluginLayoutHtml(renderer, target, vars).render();
}