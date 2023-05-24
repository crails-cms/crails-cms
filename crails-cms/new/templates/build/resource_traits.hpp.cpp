#include <sstream>
#include "crails/render_target.hpp"
#include "crails/shared_vars.hpp"
#include "crails/template.hpp"
#include <crails/utils/semantics.hpp>
#include <crails/cli/conventions.hpp>

class render_ProjectModelsResourceTraitsHpp : public Crails::Template
{
public:
  render_ProjectModelsResourceTraitsHpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars) :
    Crails::Template(renderer, target, vars), 
    resource_name(Crails::cast<std::string>(vars, "resource_name")), 
    traits_header( Crails::naming_convention.filenames("traits")), 
    traits_classname( Crails::naming_convention.classnames("application_traits")), 
    classname( Crails::naming_convention.classnames(resource_name + "_traits")), 
    model_name( Crails::naming_convention.classnames(resource_name)), 
    tag_query(Crails::cast<std::string>(vars, "tag_query",  ""))
  {}

  void render()
  {
ecpp_stream << "#pragma once\n#include \"" << ( traits_header );
  ecpp_stream << ".hpp\"\n#include \"" << ( Crails::naming_convention.filenames(resource_name) );
  ecpp_stream << ".hpp\"";
 if (tag_query.length()){
  ecpp_stream << "\n#include \"" << ( Crails::naming_convention.filenames(tag_query) );
  ecpp_stream << ".hpp\"";
 };
  ecpp_stream << "\nstruct " << ( classname );
  ecpp_stream << " : public " << ( traits_classname );
  ecpp_stream << "\n{\n  typedef " << ( model_name );
  ecpp_stream << " Model;\n  typedef " << ( model_name );
  ecpp_stream << " IndexModel;";
 if (tag_query.length()){
  ecpp_stream << "\n  typedef " << ( Crails::naming_convention.classnames(tag_query) );
  ecpp_stream << " TagModel;";
 };
  ecpp_stream << "};\n";
    this->target.set_body(ecpp_stream.str());
  }
private:
  std::stringstream ecpp_stream;
  std::string resource_name;
  std::string traits_header;
  std::string traits_classname;
  std::string classname;
  std::string model_name;
  std::string tag_query;
};

void render_project_models_resource_traits_hpp(const Crails::Renderer& renderer, Crails::RenderTarget& target, Crails::SharedVars& vars)
{
  render_ProjectModelsResourceTraitsHpp(renderer, target, vars).render();
}