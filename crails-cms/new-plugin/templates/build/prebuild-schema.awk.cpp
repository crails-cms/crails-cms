#include <crails/template_stream.hpp>
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
    ecpp_stream.reserve(4692);
    // BEGIN TEMPLATE BODY
ecpp_stream << "BEGIN { RS = \";\"; have_table = 0 }\n\n# Emits one escaped, line-continued C++ string literal wrapped in\n# `prefix \"...\" suffix`, built from the `clean[1..m]` lines of the\n# current statement. Mirrors the exact formatting the old script used\n# (four-space-indented continuation lines) so generated diffs stay small.\nfunction emit_statement(prefix, suffix,    i, l, out) {\n  out = prefix \"\\\"\"\n  for (i = 1; i <= m; i++) {\n    l = clean[i]\n    gsub(/\\\\/, \"\\\\\\\\\", l)\n    gsub(/\"/, \"\\\\\\\"\", l)\n    out = out (i > 1 ? \"\\\"\\n    \\\" \" : \"\") l\n  }\n  print out \"\\\"\" suffix\n}\n\n{\n  raw = $0\n  gsub(/^[ \\t\\r\\n]+/, \"\", raw)\n  gsub(/[ \\t\\r\\n]+$/, \"\", raw)\n  if (raw == \"\") next\n\n  m = 0\n  n = split(raw, arr, \"\\n\")\n  for (i = 1; i <= n; i++) {\n    l = arr[i]\n    gsub(/^[ \\t\\r]+/, \"\", l)\n    gsub(/[ \\t\\r]+$/, \"\", l)\n    if (l != \"\") { m++; clean[m] = l }\n  }\n  if (m == 0) next\n\n  is_drop         = (clean[1] ~ /^DROP/)\n  is_create_table = (clean[1] ~ /^CREATE[ \\t]+TABLE[ \\t]/)\n\n  if (mode == \"install\"   &&  is_drop) { delete clean; next }\n  if (mode == \"uninstall\" && !is_drop) { delete clean; next }\n\n  clean[m] = clean[m] \";\"\n\n  if (mode == \"uninstall\") {\n    # Uninstall never goes through SchemaMigrator: it's a plain, immediate\n    # DROP, not something to diff against the live schema.\n    emit_statement(\"  database.execute(\", \");\")\n  } else if (is_create_table) {\n    emit_statement(\"  schema.push_back(Crails::Odb::SchemaMigrator::Table::from_create_query(\", \"));\")\n    have_table = 1\n  } else {\n    # Anything else in an install file (CREATE INDEX, CREATE UNIQUE INDEX,\n    # ALTER TABLE ... ADD CONSTRAINT, ...) belongs to whichever table was\n    # most recently declared in this same file, per how odb lays out its\n    # generated .sql: a table's indexes and constraints are emitted right\n    # after that table's own CREATE TABLE, before the next table starts.\n    if (!have_table) {\n      print \"prebuild-schema.awk: \" FILENAME \": statement appears before any CREATE TABLE, can't attach it to a table:\" > \"/dev/stderr\"\n      print \"  \" clean[1] > \"/dev/stderr\"\n      exit 1\n    }\n    emit_statement(\"  schema.back().extra_statements.push_back(\", \");\")\n  }\n  delete clean\n}\n";
    // END TEMPLATE BODY
    std::string _out_buffer = std::move(ecpp_stream).extract();
    this->target.set_body(this->apply_post_render_filters(std::move(_out_buffer)));
  }
private:
  Crails::TemplateStream ecpp_stream;
};

void render_plugin_prebuild_schema_awk(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_PluginPrebuildSchemaAwk(renderer, target, vars).render();
}