#include <sstream>
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
ecpp_stream << "function resolves(inc,    n, dirs, i) {\n  if (system(\"test -f \\\"\" owndir \"/\" inc \"\\\"\") == 0) return 1\n  n = split(searchdirs, dirs, \" \")\n  for (i = 1; i <= n; i++)\n    if (system(\"test -f \\\"\" dirs[i] \"/\" inc \"\\\"\") == 0) return 1\n  return 0\n}\n{\n  line = $0\n  if (line ~ /^[ \\t]*#include[ \\t]*[\"<][^\">]+-odb\\.hxx[\">][ \\t]*$/) {\n    inc = line\n    sub(/^[ \\t]*#include[ \\t]*[\"<]/, \"\", inc)\n    sub(/[\">][ \\t]*$/, \"\", inc)\n    if (!resolves(inc)) next\n  }\n  print line\n  if (!inserted && line ~ /^[ \\t]*#include/) {\n    print bridge\n    inserted = 1\n  }\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
};

void render_plugin_prebuild_fix_odb_awk(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginPrebuildFixOdbAwk(renderer, target, vars).render();
}