#include <crails/template_stream.hpp>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_PluginPrebuildFixOdbAwk : public Crails::Template
{
public:
  render_PluginPrebuildFixOdbAwk(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
    ecpp_stream.reserve(1260);
    // BEGIN TEMPLATE BODY
ecpp_stream << "function resolves(inc,    n, dirs, i) {\n  if (system(\"test -f \\\"\" owndir \"/\" inc \"\\\"\") == 0) return 1\n  n = split(searchdirs, dirs, \" \")\n  for (i = 1; i <= n; i++)\n    if (system(\"test -f \\\"\" dirs[i] \"/\" inc \"\\\"\") == 0) return 1\n  return 0\n}\n{\n  line = $0\n  if (line ~ /^[ \\t]*#include[ \\t]*[\"<][^\">]+-odb\\.hxx[\">][ \\t]*$/) {\n    inc = line\n    sub(/^[ \\t]*#include[ \\t]*[\"<]/, \"\", inc)\n    sub(/[\">][ \\t]*$/, \"\", inc)\n    if (!resolves(inc)) next\n  }\n  print line\n  if (!inserted && line ~ /^[ \\t]*#include/) {\n    print bridge\n    inserted = 1\n  }\n}\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_plugin_prebuild_fix_odb_awk(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginPrebuildFixOdbAwk(renderer, target, vars).render();
}