#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"

class render_PluginPrebuildSchemaAwk : public Crails::Template
{
public:
  render_PluginPrebuildSchemaAwk(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars)
  {}

  void render()
  {
ecpp_stream << "BEGIN { RS = \";\" }\n{\n  raw = $0\n  gsub(/^[ \\t\\r\\n]+/, \"\", raw)\n  gsub(/[ \\t\\r\\n]+$/, \"\", raw)\n  if (raw == \"\") next\n\n  m = 0\n  n = split(raw, arr, \"\\n\")\n  for (i = 1; i <= n; i++) {\n    l = arr[i]\n    gsub(/^[ \\t\\r]+/, \"\", l)\n    gsub(/[ \\t\\r]+$/, \"\", l)\n    if (l != \"\") { m++; clean[m] = l }\n  }\n  if (m == 0) next\n\n  is_drop = (clean[1] ~ /^DROP/)\n  if ((mode == \"install\" && is_drop) || (mode == \"uninstall\" && !is_drop)) { delete clean; next }\n\n  clean[m] = clean[m] \";\"\n\n  out = \"  database.execute(\\\"\"\n  for (i = 1; i <= m; i++) {\n    l = clean[i]\n    gsub(/\\\\/, \"\\\\\\\\\", l)\n    gsub(/\"/, \"\\\\\\\"\", l)\n    out = out (i > 1 ? \"\\\"\\n    \\\" \" : \"\") l\n  }\n  print out \"\\\");\"\n  delete clean\n}\n";
    std::string _out_buffer = ecpp_stream.str();
    _out_buffer = this->apply_post_render_filters(_out_buffer);
    this->target.set_body(_out_buffer);
  }
private:
  std::stringstream ecpp_stream;
};

void render_plugin_prebuild_schema_awk(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginPrebuildSchemaAwk(renderer, target, vars).render();
}