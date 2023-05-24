#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectModelsTagQueryHpp : public Crails::Template
{
public:
  render_ProjectModelsTagQueryHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast<std::string>(vars, "resource_name")), 
    tag_query(Crails::cast<std::string>(vars, "tag_query")), 
    classname( Crails::naming_convention.classnames(resource_name))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include <string>\n#include \"" << ( Crails::naming_convention.filenames(resource_name) );
  ecpp_stream << ".hpp\"\n\n#pragma db view query(\"SELECT value, count(value) FROM \\\"" << ( classname );
  ecpp_stream << "_tags\\\" WHERE (?) GROUP BY value\")\nstruct " << ( Crails::naming_convention.classnames(tag_query) );
  ecpp_stream << "\n{\n  std::string get_database_name() const { return " << ( classname );
  ecpp_stream << "().get_database_name(); }\n  #pragma db type(\"VARCHAR\")\n  std::string value;\n  #pragma db type(\"INTEGER\")\n  size_t count;\n};\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string resource_name;
  std::string tag_query;
  std::string classname;
};

void render_project_models_tag_query_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsTagQueryHpp(renderer, target, vars).render();
}